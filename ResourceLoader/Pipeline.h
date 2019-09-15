#pragma once
#include "Resource.h"
#include <string>
#include "DepthStencil.h"
#include "Blend.h"
#include "Shader.h"
#include "Rasterize.h"
#include <unordered_map>
namespace Resource
{
	// what's going to be in side?

	// depthstencil setting
	// blendstate setting
	// shaders, code as string and entry point
	// root signatures setting ??? 
	// input foramt for graphcis pipeline, can direct get from vertex shader, not going to store here
	class Pipeline : public Resource {
	public:
		enum class Type
		{
			NONE,
			GRAPHICS,
			COMPUTE,
		};
		enum class Primitive
		{
			NONE,
			POINT,
			LINE,
			TRIANGLE,
			PATCH,
		};
		enum VertexInputLayout
		{
			NONE_SPLIT,
			SPLIT_ALL,
			CUSTOM
		};
		Pipeline() :Resource(PIPELINE), blends_(1){}
		Pipeline(std::string full_name) :Resource(PIPELINE), blends_(1) {
			setPathName(full_name);
		}
		static const std::string default_folder_path_;
	private:
		bool loadResource();
		Type type_ = Type::NONE;
		Primitive primitive_ = Primitive::NONE;
		VertexInputLayout vertex_input_layout_ = NONE_SPLIT;
		DepthStencil depth_stencil_;
		static const unsigned int max_rendertarget_ = 8;
		bool alpha_to_coverage_enable_ = false;
		bool independent_blend_enable_ = false;
		std::vector<Blend> blends_;
		std::unordered_map<Shader::Type, Shader> shaders_;
		Rasterize rasterize_;
	};
}