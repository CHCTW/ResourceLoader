#include "Model.h"
#include <assimp\ai_assert.h>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <iostream>
namespace Resource
{ 
	template<class DataClass, class IndexClass>
	bool BaseModel<DataClass, IndexClass>::loadResource()
	{
		State state(UNLOAD);
		Assimp::Importer importer;
		importer.ReadFile(full_path_name_.c_str(), aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_FlipUVs);
		aiScene const* scene = importer.GetScene();
		if (!scene)
		{
			std::cout << full_path_name_ << ": can't load model " << std::endl;
			importer.FreeScene();
			return false;
		}
		mesh_list_.resize(scene->mNumMeshes);
		for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
		{
			mesh_list_[i].loadFromAIMesh(scene->mMeshes[i]);
		}
		material_list_.resize(scene->mNumMaterials);
		for (unsigned int i = 0; i < scene->mNumMaterials; ++i)
		{
			material_list_[i].loadFromAIMaterial(scene->mMaterials[i]);
		}
		importer.FreeScene();
		return true;
	}
	template class BaseModel<float, unsigned int>;
	template class BaseModel<double, unsigned int>;
}