#include "Manager.h"
#include "Pipeline.h"
#include "Image.h"
#include "Model.h"
#include "File.h"
#include <chrono>
#include <iostream>
namespace Resource
{
	template<class ResourceClass>
	Manager<ResourceClass>::Manager(std::string resource_folder_path):resource_folder_path_(resource_folder_path)
	{
		startWorkingThread();
	}
	template<class ResourceClass>
	Manager<ResourceClass>::Manager(std::string resource_folder_path, unsigned int working_thread_count) : resource_folder_path_(resource_folder_path), working_thread_count_(working_thread_count)
	{
		startWorkingThread();
	}
	template<class ResourceClass>
	Manager<ResourceClass>::Manager()
	{
		startWorkingThread();
	}
	template<class ResourceClass>
	Manager<ResourceClass>::Manager(unsigned int working_thread_count):working_thread_count_(working_thread_count)
	{
		startWorkingThread();
	}
	template<class ResourceClass>
	Manager<ResourceClass>::~Manager()
	{
		stopWorkingThread();
	}
	template<class ResourceClass>
	void Manager<ResourceClass>::startWorkingThread()
	{
		running_.store(true);
		for (unsigned int i = 0; i < working_thread_count_; ++i)
		{
			working_thread_.push_back(std::move(std::thread(&Manager<ResourceClass>::working, this)));
		}
	}
	template<class ResourceClass>
	void Manager<ResourceClass>::stopWorkingThread()
	{
		running_.store(false);
		for (unsigned int i = 0; i < working_thread_count_; ++i)
		{
			if (working_thread_[i].joinable())
				working_thread_[i].join();
		}
	}
	template<class ResourceClass>
	Work<ResourceClass> Manager<ResourceClass>::generateEmptyCallbackWork(std::string full_path_name, bool cache,bool use_const)
	{
		Work<ResourceClass> work;
		work.full_path_name_ = full_path_name;
		work.use_const_ = use_const;
		if (cache && use_const) // read-only
		{
			std::lock_guard<std::mutex> lock(cache_mutex_);
			if (cache_.find(full_path_name)==cache_.end())
				cache_[full_path_name].reset(new ResourceClass(full_path_name));
			work.resource_ = cache_[full_path_name];
		}
		return work;
	}
	template<class ResourceClass>
	void Manager<ResourceClass>::addWorkToQueue(Work<ResourceClass>& work)
	{
		std::lock_guard<std::mutex> lock(queue_mutex_);
		waiting_queue_.push_back(work);
	}
	template<class ResourceClass>
	bool Manager<ResourceClass>::getWorkFromQueue(Work<ResourceClass>& work)
	{
		std::lock_guard<std::mutex> lock(queue_mutex_);
		if (waiting_queue_.size() == 0)
		{
			return false;
		}
		work = waiting_queue_.front();
		waiting_queue_.pop_front();
		return true;
	}
	template<class ResourceClass>
	void Manager<ResourceClass>::resourceLoad(Work<ResourceClass>& work)
	{
		if(!work.resource_)
			work.resource_.reset(new ResourceClass(work.full_path_name_));
		if (work.resource_->load() == State::LOADING)
		{
			addWorkToQueue(work);
		}
		if (work.resource_->load() == State::LOADED)
		{
			if (work.use_const_ && work.const_callback_)
				work.const_callback_(std::const_pointer_cast<const ResourceClass>(work.resource_));
			if (!work.use_const_ && work.callback_)
				work.callback_(work.resource_);
		}
	}
	template<class ResourceClass>
	void Manager<ResourceClass>::working()
	{
		Work<ResourceClass> work;
		while (running_.load())
		{
			if (getWorkFromQueue(work))
			{
				resourceLoad(work);
			}
			else
			{// no work, sleep for a while
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
		}
	}
	template<class ResourceClass>
	std::shared_ptr<const ResourceClass> Manager<ResourceClass>::Get(std::string file_name, std::function<void(std::shared_ptr<const ResourceClass>)> const_callback, bool immediate, bool cache)
	{
		auto work = generateEmptyCallbackWork(resource_folder_path_ + file_name, cache, true);
		work.const_callback_ = const_callback;
		if (immediate)
			resourceLoad(work);
		else
			addWorkToQueue(work);
		return work.resource_;
	}
	template<class ResourceClass>
	std::shared_ptr<ResourceClass> Manager<ResourceClass>::GetMutable(std::string file_name, std::function<void(std::shared_ptr<ResourceClass>)> callback, bool immediate)
	{
		auto work = generateEmptyCallbackWork(resource_folder_path_ + file_name, false, false);
		work.callback_ = callback;
		if (immediate)
			resourceLoad(work);
		else
			addWorkToQueue(work);
		return work.resource_;
	}

	template<class ResourceClass>
	void Manager<ResourceClass>::waitAllWorkDone()
	{
		size_t count = 0;
		do
		{
			{
				std::lock_guard<std::mutex> lock(queue_mutex_);
				count = waiting_queue_.size();
			}
		} while (count != 0);
	}
	template class Manager<Pipeline>;
	template class Manager<Image>;
	template class Manager<Model>;
	template class Manager<File>;
}