#pragma once
#include <string>
struct aiMaterial;
namespace Resource
{
	class Material
	{
		template<typename, typename> friend class BaseModel;
	private:
		
		void loadFromAIMaterial(aiMaterial* mesh);
	public:
		std::string name_;
	};
}