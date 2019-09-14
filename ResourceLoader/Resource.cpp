#include "Resource.h"
#include <iostream>
namespace Resource
{
	State Resource::load()
	{
		State state(UNLOAD);
		if (!state_.compare_exchange_strong(state, LOADING))
		{
			std::cout << full_path_name_ << " : is already loading or loaded " << std::endl;
			return LOADING;
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