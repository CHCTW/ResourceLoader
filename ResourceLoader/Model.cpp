#include "Model.h"
#include <assimp\ai_assert.h>
#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <assimp\mesh.h>
#include <iostream>
namespace Resource
{ 
	template<class DataClass, class IndexClass>
	bool BaseModel<DataClass, IndexClass>::load()
	{
		State state(UNLOAD);
		if (!state_.compare_exchange_strong(state, LOADING))
		{
			std::cout << full_path_name_ << " : is already loading or loaded " << std::endl;
			return false;
		}
		Assimp::Importer importer;
		importer.ReadFile(full_path_name_.c_str(), aiProcess_CalcTangentSpace | aiProcess_Triangulate | aiProcess_FlipUVs);
		aiScene const* scene = importer.GetScene();
		if (!scene)
		{
			std::cout << full_path_name_ << ": can't load model " << std::endl;
			importer.FreeScene();
			state_.store(LOAD_FAIL);
			return false;
		}
		mesh_list_.resize(scene->mNumMeshes);
		for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
		{
			mesh_list_[i].loadFromAIMesh(scene->mMeshes[i]);
		}
		importer.FreeScene();
		state_.store(LOADED);
		ready_.store(true);
		return true;
	}
	template class BaseModel<float, unsigned int>;
	template class BaseModel<double, unsigned int>;
}