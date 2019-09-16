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
		Type getType() const
		{
			return type_;
		}
		std::string getFullPathName() const
		{
			return full_path_name_;
		}
		const std::string& getData() const
		{
			return data_;
		}
		std::string getEntryPoint() const
		{
			return entry_point_;
		}
	private:
		bool loadFromRapidJson(rapidjson::GenericValue<rapidjson::UTF8<char>, rapidjson::MemoryPoolAllocator<rapidjson::CrtAllocator>>& json);
		Type type_;
		std::string full_path_name_;
		std::string data_;
		std::string entry_point_;
	};
}