#pragma once
#include <string>
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
	class DepthStencil
	{
		friend class Pipeline;
	public:
		// basicly dx12 style, may change later
		enum class DepthWriteMask
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
		enum class StencilOperation
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
		bool loadFromRapidJson(rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>& json);
		bool depth_enable_ = true;
		DepthWriteMask depth_write_mask_ = DepthWriteMask::ALL;
		ComparisonFunction depth_comparison_ = ComparisonFunction::LESS;
		bool stencil_enable_ = false;
		unsigned char stencil_read_mask_ = 0xff;
		unsigned char stencil_write_mask_ = 0xff;
		StencilOperation stencial_fail_operation_ = StencilOperation::KEEP;
		StencilOperation stencial_depth_fail_operation_ = StencilOperation::KEEP;
		StencilOperation stencial_pass_operation_ = StencilOperation::KEEP;
		ComparisonFunction stencil_comparison_ = ComparisonFunction::ALWAYS;
	};
}