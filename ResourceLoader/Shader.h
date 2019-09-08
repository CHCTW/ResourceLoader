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
			DOMIAN,
			NONE
		};
	private:
		bool loadFromRapidJson(rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>& json);
		Type type_;
		std::string full_path_name_;
		std::string data_;
		std::string entry_point_;
	};
}