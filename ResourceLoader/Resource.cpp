#include "Resource.h"
#include <iostream>
#include <thread>
#include <chrono>
namespace Resource
{
	std::string Resource::getName() const
	{
		return full_path_name_;
	}
	State Resource::load()
	{
		State state(UNLOAD);
		if (!state_.compare_exchange_strong(state, LOADING))
		{
			return state_.load();
		}
		if (!loadResource())
		{
			state_.store(LOAD_FAIL);
			std::cout << full_path_name_ << " : load fail" << std::endl;
			return LOAD_FAIL;
		}
		state_.store(LOADED);
		ready_.store(true);
		return LOADED;
	}
	void Resource::waitForReady()
	{
		while (!ready_.load() && state_.load() == LOADING)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}
	void Resource::loadAsync(std::function<void(Resource&)> callback)
	{
		auto thread_loading = [&res = *this,callback]()
		{
			State state(UNLOAD);
			if (res.state_.compare_exchange_strong(state, LOADING))
			{
				if (!res.loadResource())
				{
					res.state_.store(LOAD_FAIL);
					std::cout << res.full_path_name_ << " : load fail" << std::endl;
				}
				callback(res);
				res.state_.store(LOADED);
				res.ready_.store(true);
			}
			else
			{
				std::cout << res.full_path_name_ << " : already loaded, won't execute call back" << std::endl;
			}
		};
		std::thread running_thread(thread_loading);
		running_thread.detach();
	}
}