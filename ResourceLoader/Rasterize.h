#pragma once
// The pay for using delceartion complex class, wish when nlohmnjson is back, it won't get so ugly
namespace rapidjson
{
	class CrtAllocator;
	template<typename T> class MemoryPoolAllocator;
	template<typename T> struct UTF8;
	template <typename Encoding, typename Allocator>
	class GenericValue;
}
namespace Resource
{
	class Rasterize
	{
		friend class Pipeline;
	public:
		enum Fill
		{
			WIREFRAME,
			SOLID,
		};
		enum Cull
		{
			NONE,
			FRONT,
			BACK,
		};
	private:
		bool loadFromRapidJson(rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>& json);
		Fill fill_ = SOLID;
		Cull cull_ = FRONT;
		bool fron_counter_clockwise_ = false;
		int depth_bias_ = 0;
		float depth_bias_clamp_ = 0.f;
		float slope_scaled_depth_bias_ = 0.f;
		bool depth_clip_enable_ = true;
		bool multisample_enable_ = false;
		bool antialiased_line_enable_ = false;
		unsigned int forced_sample_count_ = 0;
		bool conservative_raster_ = false;
	};
}