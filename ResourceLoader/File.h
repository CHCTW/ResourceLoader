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
		File() :Resource(Type::FILE) {
		}
		static const std::string default_folder_path_;
	private:
		bool loadResource();
		std::string data_;
	};
}