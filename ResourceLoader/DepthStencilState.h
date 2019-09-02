#pragma once
namespace Resource
{
	class DepthStencil
	{
		friend class Pipeline;
	public:
		// basicly dx12 style enum, may change later
		enum DepthWriteMask
		{
			ALL,
			ZERO,
		};
		enum ComparisonFunction
		{
			NEVER,
			LESS,
			LESS_EQUAL,
			GREATER,
			NOT_EQUAL,
			GREATER_EQUAL,
			ALWAYS,
		};
		enum StencilOperation
		{
			KEEP,
			ZERO,
			REPLACE,
			INCR_SAT,
			DECR_SAT,
			INVERT,
			INCR,
			DECR,
		};
	private:
		bool depth_enable_ = true;
		DepthWriteMask depth_write_mask_ = ALL;
		ComparisonFunction depth_comparison_ = LESS;
		bool stencil_enable_ = false;
		unsigned char stencil_read_mask_ = 0xff;
		unsigned char stencil_write_mask_ = 0xff;
		StencilOperation stencial_fail_operation_ = KEEP;
		StencilOperation stencial_depth_fail_operation_ = KEEP;
		StencilOperation stencial_pass_operation_ ;
		ComparisonFunction stencil_comparison_;

	};
}