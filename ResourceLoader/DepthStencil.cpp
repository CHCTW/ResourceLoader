#include "DepthStencil.h"
#include <rapidjson/document.h>
#include "EnumConvert.hpp"
namespace Resource
{
	bool DepthStencil::loadFromRapidJson(rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>& json)
	{
		bool ret = true;
		if (json.HasMember("DepthEnable"))
		{
			depth_enable_ = json["DepthEnable"].GetBool();
		}
		if (json.HasMember("DepthWriteMask"))
		{
			ret&=convertEnum(std::string(json["DepthWriteMask"].GetString()), depth_write_mask_);
		}
		if (json.HasMember("DepthComparison"))
		{
			ret &= convertEnum(std::string(json["DepthWriteMask"].GetString()), depth_write_mask_);
		}
		if (json.HasMember("StencilEnable"))
		{
			stencil_enable_ = json["StencilEnable"].GetBool();
		}
		if (json.HasMember("StencilReadMask"))
		{
			stencil_read_mask_ = static_cast<unsigned char>(json["StencilReadMask"].GetUint());
		}
		if (json.HasMember("StencilWriteMask"))
		{
			stencil_read_mask_ = static_cast<unsigned char>(json["StencilWriteMask"].GetUint());
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