#include "Pipeline.h"
#include <magic_enum.hpp>
#include "EnumConvert.cpp"
#include <fstream>
#include <iostream>
#include <rapidjson/rapidjson.h>
#include "rapidjson/document.h"
#include <nlohmann/json.hpp>
namespace Resource
{
	bool Pipeline::load()
	{
		std::ifstream ifs(full_path_name_);
		if (!ifs)
		{
			std::cout << "Fail to open file : " << full_path_name_ << std::endl;
			return false;
		}
		std::string file_contents{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };
		rapidjson::Document doc;
		//rapidjson::Value
		doc.Parse(file_contents.c_str());
		if(doc.HasMember("Type"))
			convertEnum(std::string(doc["Type"].GetString()), type_);
		if (doc.HasMember("Primitive"))
			convertEnum(std::string(doc["Primitive"].GetString()), primitive_);
		if (doc.HasMember("VertexInputLayout"))
			convertEnum(std::string(doc["VertexInputLayout"].GetString()), vertex_input_layout_);
		if (doc.HasMember("Shaders"))
		{
			rapidjson::Value& shaders = doc["Shaders"];
			if (shaders.IsArray())
			{
				for (auto& shader : shaders.GetArray())
				{
					if (shader.HasMember("Type"))
					{
						Shader::Type shader_type = Shader::Type::NONE;
						if (convertEnum(std::string(shader["Type"].GetString()), shader_type))
						{
							shaders_[shader_type].loadFromRapidJson(shader);
						}	
					}
				}
			}
		}
		return true;
	}

}