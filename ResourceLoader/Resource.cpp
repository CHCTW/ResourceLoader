#include "Resource.h"
#include <iostream>
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
}