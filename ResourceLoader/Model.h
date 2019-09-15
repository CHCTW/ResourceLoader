#pragma once
#include "Resource.h"
#include "Mesh.h"
#include "Material.h"
#include <string>
namespace Resource
{ 
	// a template class, when need new types need to add in cpp, support : 
	// <float,unsigned int>
	// <double, unsiegned int>
	//using Model = BaseModel<float, unsigned int>;
	typedef BaseModel<float, unsigned int> Model;
	template<class DataClass = float, class IndexClass = unsigned int>
	class BaseModel : public Resource {
	public:
		BaseModel():Resource(MODEL) {}
		explicit BaseModel(std::string full_name) :Resource(MODEL) {
			setPathName(full_name);
		}
		static const std::string default_folder_path_;
	private:
		bool loadResource();
		std::vector<Mesh<DataClass, IndexClass>> mesh_list_;
		std::vector<Material> material_list_;
		std::vector<std::string> texture_list_;
	};
}