#include"Material.h"
#include <assimp/material.h>
//#include <assimp/scene.h>
#include<iostream>
namespace Resource
{
	void Material::loadFromAIMaterial(aiMaterial* material)
	{
		aiString name;
		material->Get(AI_MATKEY_NAME, name);
		name_ = name.C_Str();
		std::cout<<"Material : " << name_ << std::endl<<std::flush;
		aiColor4D color(0.f, 0.f, 0.f,0.f);
		aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &color);

		aiString tex;
		aiTextureMapMode mode;
		unsigned int unindex = 0;
		float blend = 0.5f;
		material->GetTexture(aiTextureType_DIFFUSE, 0, &tex, nullptr, nullptr, nullptr, nullptr, &mode);
		std::cout << color.r << " " << color.g << "  " << color.b << "  "<<color.a << std::endl;
		std::cout << std::string(tex.C_Str()) << "   " << (unsigned int)mode << "    " << blend << std::endl;
	}
}