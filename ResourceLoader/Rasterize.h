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
		Fill getFill() const
		{
			return fill_;
		}
		Cull getCull() const
		{
			return cull_;
		}
		bool isFrontCounterClockwise() const
		{
			return front_counter_clockwise_;
		}
		int getDepthBias() const
		{
			return depth_bias_;
		}
		float getDepthBiasClamp() const
		{
			return depth_bias_clamp_;
		}
		float getSlopeScaledDepthBias() const
		{
			return slope_scaled_depth_bias_;
		}
		bool isDpethClipEnable() const
		{
			return depth_clip_enable_;
		}
		bool isMultisampleEnable() const
		{
			return multisample_enable_;
		}
		bool isAntialiasedLineEnable() const
		{
			return antialiased_line_enable_;
		}
		unsigned int getForcedSampleCount() const
		{
			return forced_sample_count_;
		}
		bool isConservativeRaster() const
		{
			return conservative_raster_;
		}
	private:
		bool loadFromRapidJson(rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>& json);
		Fill fill_ = SOLID;
		Cull cull_ = FRONT;
		bool front_counter_clockwise_ = false;
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