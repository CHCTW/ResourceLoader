#pragma once
#include <vector>
#include<string>
struct aiMesh;
namespace Resource
{
	// a template class, when need new types need to add in cpp, support : 
	// <float,unsignied int>
	// <double,unsignied int>
	template <class DataClass = float, class IndexClass = unsigned int>
	class Mesh
	{
		template<typename,typename> friend class BaseModel;
	public:
		std::string getName() const
		{
			return name_;
		}
		const std::vector<DataClass>& getPositions() const
		{
			return positions_;
		}
		const std::vector<std::vector<DataClass>>& getColors() const
		{
			return colors_;
		}
		const std::vector<IndexClass>& getIndices() const
		{
			return indices_;
		}
		const std::vector<std::vector<DataClass>> & getUVWs() const
		{
			return uvws_;
		}
		const std::vector<DataClass>& getNormals() const
		{
			return normals_;
		}
		const std::vector<DataClass>& getTangents_() const
		{
			return tangents_;
		}
		const std::vector<DataClass>& getBitangents_() const
		{
			return bitangents_;
		}
		unsigned int getPositionChannel() const
		{
			return position_channel_;
		}
		unsigned int getMaterialIndex() const
		{
			return material_index_;
		}
		const std::vector<unsigned int>& getColorsChannel() const
		{
			return colors_channel_;
		}
		const std::vector<unsigned int>& getUVWsChannel() const
		{
			return uvws_channel_;
		}
		unsigned int getNormalChannel() const
		{
			return normal_channel_;
		}
		unsigned int getTangentChannel() const
		{
			return tangent_channel_;
		}
		unsigned int getBitangentChannel() const
		{
			return bitangent_channel_;
		}
	private:
		void loadFromAIMesh(aiMesh* mesh);
		std::string name_;
		std::vector<DataClass> positions_;
		std::vector<std::vector<DataClass>> colors_;
		std::vector<IndexClass> indices_;
		std::vector<std::vector<DataClass>> uvws_;
		std::vector<DataClass> normals_;
		std::vector<DataClass> tangents_;
		std::vector<DataClass> bitangents_;
		unsigned int position_channel_ = 0;
		unsigned int material_index_ = 0;
		std::vector<unsigned int> colors_channel_;
		std::vector<unsigned int> uvws_channel_;
		unsigned int normal_channel_ = 0;
		unsigned int tangent_channel_ = 0;
		unsigned int bitangent_channel_ = 0;
	public:
	};
}