#pragma once
#include "Resource.h"
#include <vector>
#include <string>
#include <iostream>
namespace Resource
{
	class Image : public Resource
	{
	public:
		Image() :Resource(Type::IMAGE),width_(0), height_(0), depth_(0), mips_(0), channels_(0), elemnt_size_(0),hdr_(false){}
		explicit Image(std::string full_name):Resource(Type::IMAGE), width_(0), height_(0), depth_(0), mips_(0), channels_(0), elemnt_size_(0), hdr_(false) {
			setPathName(full_name);
		}
		~Image() {
			release();
		}
		const std::vector<unsigned char>&  getData() const { return data_; }
		unsigned int getWidth() const { return static_cast<unsigned int>(width_); }
		unsigned int getHeight() const { return static_cast<unsigned int>(height_); }
		unsigned int getElementSize() const { return static_cast<unsigned int>(elemnt_size_); }
		unsigned int getChannel() const{return static_cast<unsigned int>(channels_);}
		static const std::string default_folder_path_;
	private:
		std::vector<unsigned char> data_;
		int width_;
		int height_;
		int depth_;
		int elemnt_size_;// byte
		int mips_;
		int channels_;
		bool hdr_;
		bool loadResource();
	};
}
