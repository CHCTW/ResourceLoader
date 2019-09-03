#include "Pipeline.h"
//#include <magic_enum.hpp>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
namespace Resource
{
	bool Pipeline::load()
	{
		std::ifstream ifs(full_path_name_);
		if (!ifs)
		{
			std::cout << "Fail to open file : " << full_path_name_ << std::endl;
		}
		nlohmann::json data;
		return true;
	}
}