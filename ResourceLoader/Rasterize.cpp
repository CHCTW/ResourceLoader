#include "Rasterize.h"
#include "EnumConvert.hpp"
#include "rapidjson/document.h"
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
			fron_counter_clockwise_ = json["FrontCounterClockwise"].GetBool();
		}
		if (json.HasMember("DepthBias"))
		{
			depth_bias_ = json["DepthBias"].GetInt();
		}
		if (json.HasMember("DepthBiasClamp"))
		{
			depth_bias_clamp_ = json["DepthBiasClamp"].GetFloat();
		}
		if (json.HasMember("DepthBiasClamp"))
		{
			depth_bias_clamp_ = json["DepthBiasClamp"].GetFloat();
		}
		if (json.HasMember("SlopeScaledDepthBias"))
		{
			slope_scaled_depth_bias_ = json["SlopeScaledDepthBias"].GetFloat();
		}
		if (json.HasMember("DepthClipEnable"))
		{
			depth_clip_enable_ = json["DepthClipEnable"].GetBool();
		}
		if (json.HasMember("MultisampleEnable"))
		{
			multisample_enable_ = json["MultisampleEnable"].GetBool();
		}
		if (json.HasMember("AntialiasedLineEnable"))
		{
			antialiased_line_enable_ = json["AntialiasedLineEnable"].GetBool();
		}
		if (json.HasMember("ForcedSampleCount"))
		{
			forced_sample_count_ = json["ForcedSampleCount"].GetInt();
		}
		if (json.HasMember("ConservativeRaster"))
		{
			conservative_raster_ = json["ConservativeRaster"].GetBool();
		}
		return ret;
	}
}