#include "File.h"
#include <fstream>
#include <iostream>
namespace Resource
{
	bool File::loadResource()
	{
		std::ifstream ifs(full_path_name_);
		if (!ifs)
		{
			std::cout << "Fail to open file : " << full_path_name_ << std::endl;
			return false;
		}
		std::string file_contents{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };
		data_ = file_contents;
		return true;
	}
}