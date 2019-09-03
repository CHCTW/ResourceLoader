#pragma once
#include <string>
namespace Resource
{
	class Shader
	{
		friend class Pipeline;
	public:
		enum Type
		{
			VERTEX,
			PIXEL,
			GEOMETRY,
			COMPUTE,
			HULL,
			DOMIAN
		};
	private:
		Type type_;
		std::string full_path_name_;
		std::string data_;
		std::string entry_point_;
	};
}