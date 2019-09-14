#pragma once
#include <string>
#include "Resource.h"
namespace Resource
{
	class File :public Resource
	{
	public:
		explicit File(std::string full_name) :Resource(Type::FILE) {
			setPathName(full_name);
		}
	private:
		bool loadResource();
		std::string data_;
	};
}