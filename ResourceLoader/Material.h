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
		const std::unordered_map < Attributes, std::vector<std::string>>& getAllImageNames() const
		{
			return image_names_;
		}
		const std::unordered_map < Attributes, std::vector<float>>& getAllValues() const
		{
			return values_;
		}
		bool isTransparency() const
		{
			return transparency_;
		}
		bool isWireFrame() const
		{
			return wireframe_;
		}
		Face getFace() const
		{
			return face_;
		}
		std::string getName() const
		{
			return name_;
		}
		const std::vector<std::string>& getImageList(Attributes attribute) const
		{
			return image_names_.at(attribute);
		}
		const std::vector<float>& getValueList(Attributes attribute) const
		{
			return values_.at(attribute);
		}
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