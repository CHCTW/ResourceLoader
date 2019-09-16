#include "Rasterize.h"
#include "EnumConvert.hpp"
#include "rapidjson/document.h"
#include "JsonUtility.hpp"
namespace Resource
{
	bool Rasterize::loadFromRapidJson(rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>& json)
	{
		bool ret = true;
		if (json.HasMember("Fill"))
		{
			ret &= convertEnum(std::string(json["Fill"].GetString()), fill_);
		}
		if (json.HasMember("Cull"))
		{
			ret &= convertEnum(std::string(json["Cull"].GetString()), cull_);
		}
		if (json.HasMember("FrontCounterClockwise"))
		{
			ret &= getJsonValue("FrontCounterClockwise", json, front_counter_clockwise_);
		}
		if (json.HasMember("DepthBias"))
		{
			ret &= getJsonValue("DepthBias", json, depth_bias_);
		}
		if (json.HasMember("DepthBiasClamp"))
		{
			ret &= getJsonValue("DepthBiasClamp", json, depth_bias_clamp_);
		}
		if (json.HasMember("SlopeScaledDepthBias"))
		{
			ret &= getJsonValue("SlopeScaledDepthBias", json, slope_scaled_depth_bias_);
		}
		if (json.HasMember("DepthClipEnable"))
		{
			ret &= getJsonValue("DepthClipEnable", json, depth_clip_enable_);
		}
		if (json.HasMember("MultisampleEnable"))
		{
			ret &= getJsonValue("MultisampleEnable", json, multisample_enable_);
		}
		if (json.HasMember("AntialiasedLineEnable"))
		{
			ret &= getJsonValue("AntialiasedLineEnable", json, antialiased_line_enable_);
		}
		if (json.HasMember("ForcedSampleCount"))
		{
			ret &= getJsonValue("ForcedSampleCount", json, forced_sample_count_);
		}
		if (json.HasMember("ConservativeRaster"))
		{
			ret &= getJsonValue("ConservativeRaster", json, conservative_raster_);
		}
		return ret;
	}
}