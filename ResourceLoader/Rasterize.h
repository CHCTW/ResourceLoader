#pragma once
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
		Fill fill_ = SOLID;
		Cull cull_ = FRONT;
		bool fron_counter_clock_wise_ = false;
		int depth_bias_ = 0;
		float depth_bias_clamp_ = 0.f;
		float slope_scaled_depth_bias_ = 0.f;
		bool depth_clip_enable_ = true;
		bool multisample_enable_ = false;
		bool antialiased_line_enable_ = false;
		unsigned int forced_sample_count_ = 0;
		bool conservation_raster_ = false;
	};
}