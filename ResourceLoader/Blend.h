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
	class Blend
	{
		friend class Pipeline;
	public:
		enum BlendFactor
		{
			ZERO,
			ONE,
			SRC_COLOR,
			INV_SRC_COLOR,
			SRC_ALPHA,
			INV_SRC_ALPHA,
			DEST_ALPHA,
			INV_DEST_ALPHA,
			DEST_COLOR,
			INV_DEST_COLOR,
			SRC_ALPHA_SAT,
			BLEND_FACTOR,
			INV_BLEND_FACTOR,
			SRC1_COLOR,
			INV_SRC1_COLOR,
			SRC1_ALPHA,
			INV_SRC1_ALPHA,
		};
		enum BlendOperation
		{
			ADD,
			SUBTRACT,
			REV_SUBTRACT,
			MIN,
			MAX,
		};
		enum LogicOperation
		{
			CLEAR,
			SET,
			COPY,
			COPY_INVERTED,
			NOOP,
			INVERT,
			AND,
			NAND,
			OR,
			NOR,
			XOR,
			EQUIV,
			AND_REVERSE,
			AND_INVERTED,
			OR_REVERSE,
			OR_INVERTED,
		};
		enum ColorWrite
		{
			RED = 1,
			GREEN = 2,
			BLUE = 4,
			ALPHA = 8,
			ALL = 15
		};
	private:
		bool loadFromRapidJson(rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>& json);
		bool blend_enable_ = false;
		bool logic_blend_enable_ = false;
		BlendFactor src_blend_ = ONE;
		BlendFactor dest_blend_ = ZERO;
		BlendOperation blend_operation_ = ADD;
		BlendFactor src_blend_alpha_ = ONE;
		BlendFactor dest_blend_alpha_ = ZERO;
		BlendOperation blend_operation_alpha_ = ADD;
		LogicOperation logic_operation_ = NOOP;
		ColorWrite render_target_write_mask_ = ALL;
	};
}