#pragma once
namespace Resource
{
	class Blend
	{
		friend class Pipeline;
	public:
		enum BlendParamteres
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
		enum Operation
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
	private:
		bool blend
	};
}