#pragma once
#include <vector>
#include<string>
struct aiMesh;
namespace Resource
{
	// a template class, when need new types need to add in cpp, support : 
	// <float,unsignied int>
	template <class DataClass = float, class IndexClass = unsigned int>
	class Mesh
	{
		template<typename,typename> friend class BaseModel;
	private:
		void loadFromAIMesh(aiMesh* mesh);
	public:
		std::string name_;
		std::vector<DataClass> positions_;
		std::vector<std::vector<DataClass>> colors_;
		std::vector<IndexClass> indices_;
		std::vector<std::vector<DataClass>> uvws_;
		std::vector<DataClass> normals_;
		std::vector<DataClass> tangents_;
		std::vector<DataClass> bitangents_;
		unsigned int positon_channel_ = 0;
		unsigned int material_index_ = 0;
		std::vector<unsigned int> colors_channel_;	
		std::vector<unsigned int> uvws_channel_;
		unsigned int normal_channel_ = 0;
		unsigned int tagent_channel_ = 0;
		unsigned int bitagent_channel_ = 0;
	};
}