#include "DepthStencil.h"
#include <rapidjson/document.h>
#include "EnumConvert.hpp"
#include "JsonUtility.hpp"
namespace Resource
{
	bool DepthStencil::loadFromRapidJson(rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>& json)
	{
		bool ret = true;
		if (json.HasMember("DepthEnable"))
		{
			ret &= getJsonValue("DepthEnable", json, depth_enable_);
		}
		if (json.HasMember("DepthWriteMask"))
		{
			ret&=convertEnum(std::string(json["DepthWriteMask"].GetString()), depth_write_mask_);
		}
		if (json.HasMember("DepthComparison"))
		{
			ret &= convertEnum(std::string(json["DepthComparison"].GetString()), depth_comparison_);
		}
		if (json.HasMember("StencilEnable"))
		{
			ret &= getJsonValue("StencilEnable", json, stencil_enable_);
		}
		if (json.HasMember("StencilReadMask"))
		{
			ret &= getJsonValue("StencilReadMask", json, stencil_read_mask_);
		}
		if (json.HasMember("StencilWriteMask"))
		{
			ret &= getJsonValue("StencilWriteMask", json, stencil_write_mask_);
		}
		if (json.HasMember("StencilFailOperation"))
		{
			ret &= convertEnum(std::string(json["StencilFailOperation"].GetString()), stencial_fail_operation_);
		}
		if (json.HasMember("StencilDepthFailOperation"))
		{
			ret &= convertEnum(std::string(json["StencilDepthFailOperation"].GetString()), stencial_depth_fail_operation_);
		}
		if (json.HasMember("StencilPassOperation"))
		{
			ret &= convertEnum(std::string(json["StencilPassOperation"].GetString()),stencial_pass_operation_);
		}
		if (json.HasMember("StencilComparison"))
		{
			ret &= convertEnum(std::string(json["StencilComparison"].GetString()), stencil_comparison_);
		}
		return ret;
	}
}