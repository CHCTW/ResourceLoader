#include "Blend.h"
#include <rapidjson/document.h>
#include "EnumConvert.hpp"
namespace Resource
{
	bool Blend::loadFromRapidJson(rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>& json)
	{
		bool ret = true;
		if (json.HasMember("BlendEnable"))
		{
			blend_enable_ = json["BlendEnable"].GetBool();
		}
		if (json.HasMember("LogicBlendEnable"))
		{
			logic_blend_enable_ = json["LogicBlendEnable"].GetBool();
		}
		if (json.HasMember("SourceBlend"))
		{
			ret &= convertEnum(std::string(json["SourceBlend"].GetString()), src_blend_);
		}
		if (json.HasMember("DestinationBlend"))
		{
			ret &= convertEnum(std::string(json["DestinationBlend"].GetString()), dest_blend_);
		}
		if (json.HasMember("BlendOperation"))
		{
			ret &= convertEnum(std::string(json["BlendOperation"].GetString()), blend_operation_);
		}
		if (json.HasMember("SourceBlendAlpha"))
		{
			ret &= convertEnum(std::string(json["SourceBlendAlpha"].GetString()), src_blend_alpha_);
		}
		if (json.HasMember("DestinationBlendAlpha"))
		{
			ret &= convertEnum(std::string(json["DestinationBlendAlpha"].GetString()), dest_blend_alpha_);
		}
		if (json.HasMember("BlendOperationAlpha"))
		{
			ret &= convertEnum(std::string(json["BlendOperationAlpha"].GetString()), blend_operation_alpha_);
		}
		if (json.HasMember("LogicOperation"))
		{
			ret &= convertEnum(std::string(json["LogicOperation"].GetString()), logic_operation_);
		}
		if (json.HasMember("RenderTargetWriteMask"))
		{
			ret &= convertEnum(std::string(json["RenderTargetWriteMask"].GetString()), render_target_write_mask_);
		}
		return ret;
	}
}