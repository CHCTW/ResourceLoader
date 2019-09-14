#include "Resource.h"
#include <iostream>
namespace Resource
{
	bool Resource::load()
	{
		State state(UNLOAD);
		if (!state_.compare_exchange_strong(state, LOADING))
		{
			std::cout << full_path_name_ << " : is already loading or loaded " << std::endl;
			return false;
		}
		if (!loadResource())
		{
			state_.store(LOAD_FAIL);
			std::cout << full_path_name_ << " : load fail" << std::endl;
			return false;
		}
		state_.store(LOADED);
		ready_.store(true);
		return true;
	}
}