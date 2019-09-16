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
		bool isDepthEnable() const
		{
			return depth_enable_;
		}
		DepthWriteMask getDepthWriteMask() const
		{
			return depth_write_mask_;
		}
		ComparisonFunction getDepthComparison() const
		{
			return depth_comparison_;
		}
		bool isStencilEnable() const
		{
			return stencil_enable_;
		}
		unsigned char getStencilReadMask() const
		{
			return stencil_read_mask_;
		}
		unsigned char getStencilWriteMask() const
		{
			return stencil_write_mask_;
		}
		StencilOperation getStencilFailOperation() const
		{
			return stencil_fail_operation_;
		}
		StencilOperation getStencilDepthFailOperation() const
		{
			return stencil_depth_fail_operation_;
		}
		StencilOperation getStencilPassOperation() const
		{
			return stencil_pass_operation_;
		}
		ComparisonFunction getStencilComparison() const
		{
			return stencil_comparison_;
		}
	private:
		bool loadFromRapidJson(rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>& json);
		bool depth_enable_ = true;
		DepthWriteMask depth_write_mask_ = DepthWriteMask::ALL;
		ComparisonFunction depth_comparison_ = ComparisonFunction::LESS;
		bool stencil_enable_ = false;
		unsigned char stencil_read_mask_ = 0xff;
		unsigned char stencil_write_mask_ = 0xff;
		StencilOperation stencil_fail_operation_ = StencilOperation::KEEP;
		StencilOperation stencil_depth_fail_operation_ = StencilOperation::KEEP;
		StencilOperation stencil_pass_operation_ = StencilOperation::KEEP;
		ComparisonFunction stencil_comparison_ = ComparisonFunction::ALWAYS;
	};
}