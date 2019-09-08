#include "Shader.h"
#include "EnumConvert.cpp"
#include "rapidjson/document.h"
#include <sstream>
#include <fstream>
namespace Resource
{
	bool Shader::loadFromRapidJson(rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>& json)
	{


		convertEnum(std::string(json["Type"].GetString()), type_);
		if (json.HasMember("FullPathName"))
		{
			full_path_name_ = json["FullPathName"].GetString();
		}
		std::ifstream ifs(full_path_name_);
		if (!ifs)
		{
			std::cout << "Fail to open file : " << full_path_name_ << std::endl;
			return false;
		}
		data_ = (static_cast<std::stringstream const&>(std::stringstream() << ifs.rdbuf()).str());
		if (json.HasMember("EntryPoint"))
		{
			entry_point_ = json["EntryPoint"].GetString();
		}
		
		return true;
	}
}