#include "Material.h"
#include <assimp/material.h>
#include <iostream>
namespace Resource
{
	static std::unordered_map<std::string, Material::Attributes> AiStringAttributesTable = {
		{"diffuse",Material::Attributes::DIFFUSE},
		{"opacity",Material::Attributes::OPCACITY},
		{"bumpscaling",Material::Attributes::BUMP},
		{"shininess",Material::Attributes::SHINESS},
		{"shinpercent",Material::Attributes::SHINESS_STRENGTH},
		{"reflectivity",Material::Attributes::REFLECTVIITY},
		{"refracti",Material::Attributes::REFRECTIVE},
		{"ambient",Material::Attributes::AMBIENT},
		{"specular",Material::Attributes::SPECULAR},
		{"emissive",Material::Attributes::EMISSIVE},
		{"transparent",Material::Attributes::TRANSPARENT},
		{"reflective",Material::Attributes::REFLECTIVE},
	};
	static  std::unordered_map<aiTextureType, Material::Attributes> AiTextureAttributesTable = {
		{aiTextureType_DIFFUSE,Material::Attributes::DIFFUSE},
		{aiTextureType_SPECULAR,Material::Attributes::SPECULAR},
		{aiTextureType_AMBIENT,Material::Attributes::AMBIENT},
		{aiTextureType_EMISSIVE,Material::Attributes::EMISSIVE},
		{aiTextureType_HEIGHT,Material::Attributes::HEIGHT},
		{aiTextureType_NORMALS,Material::Attributes::NORMAL},
		{aiTextureType_SHININESS,Material::Attributes::SHINESS},
		{aiTextureType_OPACITY,Material::Attributes::OPCACITY},
		{aiTextureType_DISPLACEMENT,Material::Attributes::DISPLACEMENT},
		{aiTextureType_LIGHTMAP,Material::Attributes::LIGHTMAP},
		{aiTextureType_REFLECTION,Material::Attributes::REFLECTIVE},
	};
	Material::Attributes aiValueMatKeytoAttributes(const char* pkey, unsigned int type, unsigned int index)
	{
		Material::Attributes ret(Material::Attributes::NONE);
		std::string key(pkey);
		auto find = key.find_first_of(".");
		if (find == std::string::npos)
			return ret;
		key = key.substr(find + 1);
		if (AiStringAttributesTable.find(key) != AiStringAttributesTable.end())
			ret = AiStringAttributesTable[key];
		if (ret == Material::Attributes::NONE)
			std::cout << "Can't mapped to material attributes :" << key << std::endl;
		return ret;
	}
	Material::Attributes aiValueTextKeytoAttributes(aiTextureType type)
	{
		Material::Attributes ret(Material::Attributes::NONE);
		if (AiTextureAttributesTable.find(type) != AiTextureAttributesTable.end())
			ret = AiTextureAttributesTable[type];
		if (ret == Material::Attributes::NONE)
			std::cout << "Can't mapped to material attributes :" << type << std::endl;
		return ret;
	}
	inline bool checkAiColorDefault(aiColor3D& color)
	{
		if (color.r == 0.0 && color.g == 0.0 && color.b == 0.0)
			return true;
		return false;
	}
	void Material::loadFromAIMaterial(aiMaterial* material)
	{
		aiString name;
		material->Get(AI_MATKEY_NAME, name);
		name_ = name.C_Str();
		// what if the value we read in is the same as the default one, we don't know whetether 
		// it's exist or not, we treat as none exist now
		aiColor3D color(0.f, 0.f, 0.f);
		material->Get(AI_MATKEY_COLOR_DIFFUSE, color);
		if (!checkAiColorDefault(color))
			values_[aiValueMatKeytoAttributes(AI_MATKEY_COLOR_DIFFUSE)] = { color.r,color.g,color.b };
		material->Get(AI_MATKEY_COLOR_SPECULAR, color);
		if (!checkAiColorDefault(color))
			values_[aiValueMatKeytoAttributes(AI_MATKEY_COLOR_SPECULAR)] = { color.r,color.g,color.b };
		material->Get(AI_MATKEY_COLOR_AMBIENT, color);
		if (!checkAiColorDefault(color))
			values_[aiValueMatKeytoAttributes(AI_MATKEY_COLOR_AMBIENT)] = { color.r,color.g,color.b };
		material->Get(AI_MATKEY_COLOR_EMISSIVE, color);
		if (!checkAiColorDefault(color))
			values_[aiValueMatKeytoAttributes(AI_MATKEY_COLOR_EMISSIVE)] = { color.r,color.g,color.b };
		material->Get(AI_MATKEY_COLOR_TRANSPARENT, color);
		if (!checkAiColorDefault(color))
			values_[aiValueMatKeytoAttributes(AI_MATKEY_COLOR_TRANSPARENT)] = { color.r,color.g,color.b };
		material->Get(AI_MATKEY_COLOR_REFLECTIVE, color);
		if (!checkAiColorDefault(color))
			values_[aiValueMatKeytoAttributes(AI_MATKEY_COLOR_REFLECTIVE)] = { color.r,color.g,color.b };
		bool check = false;
		material->Get(AI_MATKEY_TWOSIDED, check);
		if (check)
			face_ = BOTH;
		material->Get(AI_MATKEY_ENABLE_WIREFRAME, check);
		wireframe_ = check;
		float value;
		material->Get(AI_MATKEY_OPACITY, value);
		if (value != 1.0)
		{
			transparency_ = true;
			values_[aiValueMatKeytoAttributes(AI_MATKEY_OPACITY)] = { value };
		}
		material->Get(AI_MATKEY_BUMPSCALING, value);
		values_[aiValueMatKeytoAttributes(AI_MATKEY_BUMPSCALING)] = { value };
		material->Get(AI_MATKEY_SHININESS, value);
		values_[aiValueMatKeytoAttributes(AI_MATKEY_SHININESS)] = { value };
		material->Get(AI_MATKEY_REFLECTIVITY, value);
		values_[aiValueMatKeytoAttributes(AI_MATKEY_REFLECTIVITY)] = { value };
		material->Get(AI_MATKEY_REFRACTI, value);
		values_[aiValueMatKeytoAttributes(AI_MATKEY_REFRACTI)] = { value };
		material->Get(AI_MATKEY_SHININESS_STRENGTH, value);
		values_[aiValueMatKeytoAttributes(AI_MATKEY_SHININESS_STRENGTH)] = { value };

		for (unsigned int i = aiTextureType_DIFFUSE; i != aiTextureType_UNKNOWN; ++i)
		{
			auto type = static_cast<aiTextureType>(i);
			unsigned int counts = material->GetTextureCount(type);
			Material::Attributes att = aiValueTextKeytoAttributes(type);
			for (unsigned int j = 0; j < counts; ++j)
			{
				aiString tex_name;
				material->GetTexture(type, j, &tex_name);
				image_names_[att].push_back(tex_name.C_Str());
			}
		}
	}
}