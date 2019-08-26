#include "Mesh.h"
#include <iostream>
#include <assimp\mesh.h>
#include <typeinfo> 
namespace Resource
{
	template <class DataClass>
	void AI3DVectortoInnerData(std::vector<DataClass> &data, aiVector3D* ai_vectors,unsigned int vector_nums)
	{
		unsigned int totalsize = vector_nums * 3;// x,y,z channel
		data.resize(static_cast<size_t>(totalsize));
		if (typeid(DataClass) == typeid(ai_vectors[0].x))
		{
			std::memcpy(data.data(), ai_vectors, static_cast<size_t>(totalsize) * sizeof(DataClass));
		}
		else
		{
			unsigned int index = 0;
			for (unsigned int i = 0; i < vector_nums; ++i)
			{
				data[index] = ai_vectors[i].x;
				++index;
				data[index] = ai_vectors[i].y;
				++index;
				data[index] = ai_vectors[i].z;
				++index;
			}
		}
	}
	template <class DataClass>
	void AIUVWtoInnerData(std::vector<DataClass>& data, aiVector3D* ai_vectors, unsigned int vector_nums, unsigned int channel)
	{
		unsigned int totalsize = vector_nums * channel;// x,y,z channel
		data.resize(static_cast<size_t>(totalsize));
		if (typeid(DataClass) == typeid(ai_vectors[0].x) && channel==3)
		{
			std::memcpy(data.data(), ai_vectors, static_cast<size_t>(totalsize) * sizeof(DataClass));
		}
		else
		{
			unsigned int index = 0;
			for (unsigned int i = 0; i < vector_nums; ++i)
			{
				data[index] = ai_vectors[i].x;
				++index;
				if (channel == 1)
					continue;
				data[index] = ai_vectors[i].y;
				++index;
				if (channel == 2)
					continue;
				data[index] = ai_vectors[i].z;
				++index;
			}
		}
	}
	template <class DataClass>
	void AI4DVectortoInnerData(std::vector<DataClass>& data, aiColor4D* ai_vectors, unsigned int vector_nums)
	{
		unsigned int totalsize = vector_nums * 4;// r,g,b,a channel
		data.resize(static_cast<size_t>(totalsize));
		if (typeid(DataClass) == typeid(ai_vectors[0].r))
		{
			std::memcpy(data.data(), ai_vectors, static_cast<size_t>(totalsize) * sizeof(DataClass));
		}
		else
		{
			unsigned int index = 0;
			for (unsigned int i = 0; i < vector_nums; ++i)
			{
				data[index] = ai_vectors[i].r;
				++index;
				data[index] = ai_vectors[i].g;
				++index;
				data[index] = ai_vectors[i].b;
				++index;
				data[index] = ai_vectors[i].a;
				++index;
			}
		}
		
	}
	template <class IndexClass>
	void AIIndextoInnerIndex(std::vector<IndexClass>& data, aiFace* ai_faces, unsigned int face_nums)
	{
		unsigned int totalsize = face_nums * 3;// triangle, we use trigalize tag, should always we 3
		data.resize(static_cast<size_t>(totalsize));
		unsigned int index = 0;
		for (unsigned int i = 0; i < face_nums; ++i)
		{
			data[index] = ai_faces[i].mIndices[0];
			++index;
			data[index] = ai_faces[i].mIndices[1];
			++index;
			data[index] = ai_faces[i].mIndices[2];
			++index;
		}
	}
	template <class DataClass, class IndexClass>
	void Mesh<DataClass, IndexClass>::loadFromAIMesh(aiMesh* mesh)
	{
		std::cout << std::string(mesh->mName.data) << std::endl;
		name_ = std::string(mesh->mName.data);
		if (mesh->HasPositions())
		{
			AI3DVectortoInnerData(positions_, mesh->mVertices, mesh->mNumVertices);
			positon_channel_ = 3;
		}
		if (mesh->HasFaces())
		{
			AIIndextoInnerIndex(indices_, mesh->mFaces, mesh->mNumFaces);
		}
		if (mesh->HasNormals())
		{
			AI3DVectortoInnerData(normals_, mesh->mNormals, mesh->mNumVertices);
			normal_channel_ = 3;
		}
		if (mesh->HasTangentsAndBitangents())
		{
			AI3DVectortoInnerData(tangents_, mesh->mTangents, mesh->mNumVertices);
			AI3DVectortoInnerData(bitangents_, mesh->mBitangents, mesh->mNumVertices);
			tagent_channel_ = 4;
			bitagent_channel_ = 4;
		}
		unsigned int total_color_sets = mesh->GetNumColorChannels();
		colors_channel_.resize(static_cast<size_t>(total_color_sets));
		colors_.resize(static_cast<size_t>(total_color_sets));
		for (unsigned int i = 0; i < total_color_sets; ++i)
		{
			AI4DVectortoInnerData(colors_[i], mesh->mColors[i], mesh->mNumVertices);
			colors_channel_[i] = 4;
		}

		unsigned int total_uvw_sets = mesh->GetNumUVChannels();
		uvws_channel_.resize(static_cast<size_t>(total_uvw_sets));
		uvws_.resize(static_cast<size_t>(total_uvw_sets));
		for (unsigned int i = 0; i < total_uvw_sets; ++i)
		{
			AIUVWtoInnerData(uvws_[i], mesh->mTextureCoords[i], mesh->mNumVertices, mesh->mNumUVComponents[i]);
			uvws_channel_[i] = mesh->GetNumColorChannels();
		}
		material_index_ = mesh->mMaterialIndex;
		
	}
	// due to c++ implementation, I need to decleare the used type here first
	template class Mesh<float,unsigned int>;
	template class Mesh<double, unsigned int>;
}