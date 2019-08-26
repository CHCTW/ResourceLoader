#pragma once
#include "Resource.h"
#include "Mesh.h"
#include <string>
namespace Resource
{ 
	// a template class, when need new types need to add in cpp, support : 
	// <float,unsignied int>
	using Model = BaseModel<float, unsigned int>;
	template<class DataClass = float, class IndexClass = unsigned int>
	class BaseModel : public Resource {
	public:
		BaseModel():Resource(MODEL) {}
		explicit BaseModel(std::string full_name) :Resource(MODEL) {
			setPathName(full_name);
		}
		bool LoadModel() {
			return load();
		}
	private:
		bool load();
		std::vector<Mesh<DataClass, IndexClass>> mesh_list_;
		std::vector<std::string> texture_list_;
	};
}