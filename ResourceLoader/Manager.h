#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include <list>
#include <thread>
#include <deque>
#include <mutex>
#include <atomic>
#include "Work.hpp"
namespace Resource
{
	template<class ResourceClass>
	class Manager {
	public:
		Manager();
		Manager(unsigned int working_thread_count);
		Manager(std::string resource_folder_path);
		Manager(std::string resource_folder_path, unsigned int working_thread_count);
		~Manager();
		std::shared_ptr<const ResourceClass> Get(std::string file_name, std::function<void(std::shared_ptr<const ResourceClass>)> const_callback = nullptr,  bool immediate = false, bool cache = true);
		std::shared_ptr<ResourceClass> GetMutable(std::string file_name, std::function<void(std::shared_ptr<ResourceClass>)> callback = nullptr, bool immediate = false);
		void waitAllWorkDone();
	private:
		Work<ResourceClass> generateEmptyCallbackWork(std::string full_path_name, bool cache, bool use_const);
		void addWorkToQueue(Work<ResourceClass>& work);
		bool getWorkFromQueue(Work<ResourceClass>& work);
		void startWorkingThread();
		void stopWorkingThread();
		void working();
		void resourceLoad(Work<ResourceClass>& work);
		std::string resource_folder_path_ = ResourceClass::default_folder_path_;
		const unsigned int working_thread_count_ = 10;
		std::unordered_map<std::string, std::shared_ptr<ResourceClass>> cache_;
		std::deque<Work<ResourceClass>> waiting_queue_;
		std::atomic<bool> running_;
		std::vector<std::thread> working_thread_;
		std::mutex queue_mutex_;
		std::mutex cache_mutex_;
	};
}