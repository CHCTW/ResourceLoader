#pragma once
#include "Resource.h"
#include <string>
#include <nlohmann/json.hpp>
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
		Pipeline() :Resource(PIPELINE), render_target_blends_(1){}
		explicit Pipeline(std::string full_name) :Resource(PIPELINE), render_target_blends_(1) {
			setPathName(full_name);
		}
		bool loadPipeline()
		{
			return load();
		}
	private:
		bool load();
		Type type_ = Type::NONE;
		Primitive render_primitive_ = Primitive::NONE;
		nlohmann::json data_;
		DepthStencil depth_stencil_;
		static const unsigned int max_rendertarget_ = 8;
		bool alpha_to_coverage_enable_ = false;
		bool independent_blend_enable_ = false;
		std::vector<Blend> render_target_blends_;
		std::unordered_map<Shader::Type, Shader> shaders_;
		Rasterize rasterize_;
	};
}