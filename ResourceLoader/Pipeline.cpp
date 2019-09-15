#include "Pipeline.h"
#include <magic_enum.hpp>
#include "EnumConvert.hpp"
#include <fstream>
#include <iostream>
#include <rapidjson/rapidjson.h>
#include "rapidjson/document.h"
#include <nlohmann/json.hpp>
#include "JsonUtility.hpp"
namespace Resource
{
	const std::string Pipeline::default_folder_path_ = "Assets/Pipelines/";
	bool Pipeline::loadResource()
	{
		bool ret = true;
		std::ifstream ifs(full_path_name_);
		if (!ifs)
		{
			std::cout << "Fail to open file : " << full_path_name_ << std::endl;
			return false;
		}
		std::string file_contents{ std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>() };
		rapidjson::Document doc;
		doc.Parse(file_contents.c_str());
		if(doc.HasMember("Type"))
			ret&=convertEnum(std::string(doc["Type"].GetString()), type_);
		if (doc.HasMember("Primitive"))
			ret &= convertEnum(std::string(doc["Primitive"].GetString()), primitive_);
		if (doc.HasMember("VertexInputLayout"))
			ret &= convertEnum(std::string(doc["VertexInputLayout"].GetString()), vertex_input_layout_);
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
							ret &= shaders_[shader_type].loadFromRapidJson(shader);
						}	
					}
				}
			}
		}
		if (doc.HasMember("DepthStencil"))
		{
			ret &= depth_stencil_.loadFromRapidJson(doc["DepthStencil"]);
		}
		if (doc.HasMember("Rasterize"))
		{
			ret &= rasterize_.loadFromRapidJson(doc["Rasterize"]);
		}
		if (doc.HasMember("Blends"))
		{
			rapidjson::Value& blends = doc["Blends"];
			if (blends.IsArray())
			{
				blends_.resize(blends.Size());

				for (unsigned int i = 0; i < blends.Size(); ++i)
				{
					ret &= blends_[i].loadFromRapidJson(blends[i]);
				}
			}
		}
		if (doc.HasMember("AlphaToCoverageEnable"))
		{
			ret &= getJsonValue("AlphaToCoverageEnable", doc, alpha_to_coverage_enable_);
		}
		if (doc.HasMember("IndependentBlendEnable"))
		{
			ret &= getJsonValue("IndependentBlendEnable", doc, independent_blend_enable_);
		}
		return ret;
	}

}