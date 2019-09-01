#pragma once
#include <string>
#include <unordered_map>
#include <vector>
struct aiMaterial;
namespace Resource
{
	class Material
	{
		template<typename, typename> friend class BaseModel;
	public:
		enum Attributes
		{
			DIFFUSE,
			SPECULAR,
			REFLECTIVE,
			REFLECTVIITY,
			REFRECTIVE,
			AMBIENT,
			EMISSIVE,
			TRANSPARENT,
			NORMAL,
			SHINESS,
			SHINESS_STRENGTH,
			BUMP,
			HEIGHT,
			DISPLACEMENT,
			OPCACITY,
			LIGHTMAP,
			NONE,
		};
		enum Face
		{
			FRONT,
			BACK,
			BOTH,
		};
	private:
		std::unordered_map < Attributes, std::vector<std::string>> image_names_;
		std::unordered_map < Attributes, std::vector<float>> values_;
		void loadFromAIMaterial(aiMaterial* mesh);
		bool transparency_ = false;
		bool wireframe_ = false;
		Face face_ = FRONT;
		std::string name_;
	};
}