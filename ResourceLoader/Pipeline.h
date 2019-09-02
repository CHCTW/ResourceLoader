#pragma once
#include "Resource.h"
#include <string>
#include <nlohmann/json.hpp>
#include "DepthStencil.h"
namespace Resource
{
	// what's going to be in side?

	// depthstencil setting
	// blendstate setting
	// shaders, code as string and entry point
	// root signatures setting
	// input foramt for graphcis pipeline, can direct get from vertex shader, not going to store here

	class Pipeline : public Resource {
	public:
		enum Type
		{
			GRAPHICS,
			COMPUTE,
		};
		Pipeline() :Resource(PIPELINE) {}
		explicit Pipeline(std::string full_name) :Resource(PIPELINE) {
			setPathName(full_name);
		}
	private:
		nlohmann::json data_;
		DepthStencil depth_stencil_;
	};
}