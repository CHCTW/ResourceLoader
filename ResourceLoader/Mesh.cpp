#include "Mesh.h"
#include <iostream>
#include <assimp\mesh.h>
#include <typeinfo> 
#include "AssimpConvert.hpp"
#include "Material.h"
namespace Resource
{
	template <class DataClass, class IndexClass>
	void Mesh<DataClass, IndexClass>::loadFromAIMesh(aiMesh* mesh)
	{
		name_ = std::string(mesh->mName.data);
		if (mesh->HasPositions())
		{
			AI3DVectortoDataClass(positions_, mesh->mVertices, mesh->mNumVertices);
			position_channel_ = 3;
		}
		if (mesh->HasFaces())
		{
			AIIndextoIndexClass(indices_, mesh->mFaces, mesh->mNumFaces);
		}
		if (mesh->HasNormals())
		{
			AI3DVectortoDataClass(normals_, mesh->mNormals, mesh->mNumVertices);
			normal_channel_ = 3;
		}
		if (mesh->HasTangentsAndBitangents())
		{
			AI3DVectortoDataClass(tangents_, mesh->mTangents, mesh->mNumVertices);
			AI3DVectortoDataClass(bitangents_, mesh->mBitangents, mesh->mNumVertices);
			tangent_channel_ = 4;
			bitangent_channel_ = 4;
		}
		unsigned int total_color_sets = mesh->GetNumColorChannels();
		colors_channel_.resize(static_cast<size_t>(total_color_sets));
		colors_.resize(static_cast<size_t>(total_color_sets));
		for (unsigned int i = 0; i < total_color_sets; ++i)
		{
			AI4DVectortoDataClass(colors_[i], mesh->mColors[i], mesh->mNumVertices);
			colors_channel_[i] = 4;
		}

		unsigned int total_uvw_sets = mesh->GetNumUVChannels();
		uvws_channel_.resize(static_cast<size_t>(total_uvw_sets));
		uvws_.resize(static_cast<size_t>(total_uvw_sets));
		for (unsigned int i = 0; i < total_uvw_sets; ++i)
		{
			AIUVWtoDataClass(uvws_[i], mesh->mTextureCoords[i], mesh->mNumVertices, mesh->mNumUVComponents[i]);
			uvws_channel_[i] = mesh->GetNumColorChannels();
		}
		material_index_ = mesh->mMaterialIndex;
		
	}
	// due to c++ implementation, I need to decleare the used type here first
	template class Mesh<float,unsigned int>;
	template class Mesh<double, unsigned int>;
}