#pragma once
#include <assimp\mesh.h>
#include <typeinfo> 
#include <vector>
#include <unordered_map>
#include <iostream>
namespace Resource
{
	static std::vector<std::string> ai_attribute_keys = {

	};
	template <class DataClass>
	void AI3DVectortoDataClass(std::vector<DataClass>& data, aiVector3D* ai_vectors, unsigned int vector_nums)
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
	void AIUVWtoDataClass(std::vector<DataClass>& data, aiVector3D* ai_vectors, unsigned int vector_nums, unsigned int channel)
	{
		unsigned int totalsize = vector_nums * channel;// x,y,z channel
		data.resize(static_cast<size_t>(totalsize));
		if (typeid(DataClass) == typeid(ai_vectors[0].x) && channel == 3)
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
	void AI4DVectortoDataClass(std::vector<DataClass>& data, aiColor4D* ai_vectors, unsigned int vector_nums)
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
	void AIIndextoIndexClass(std::vector<IndexClass>& data, aiFace* ai_faces, unsigned int face_nums)
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
};