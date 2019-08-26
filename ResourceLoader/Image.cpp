#include "Image.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
namespace Resource
{
	bool Image::load()
	{
		State state(UNLOAD);
		if (!state_.compare_exchange_strong(state, LOADING))
		{
			std::cout << full_path_name_ << " : is already loading or loaded " << std::endl;
			return false;
		}
		void* temp(nullptr);
		if (full_path_name_[full_path_name_.size() - 3] == 'h' && full_path_name_[full_path_name_.size() - 2] == 'd' && full_path_name_[full_path_name_.size() - 2] == 'r') // hdr file
		{
			float* temphdr = stbi_loadf(full_path_name_.c_str(), &width_, &height_, &channels_, 0);
			hdr_ = true;
			temp = static_cast<void*>(temphdr);
			elemnt_size_ = channels_*4;
		}
		else
		{
			unsigned char* templdr = stbi_load(full_path_name_.c_str(), &width_, &height_, &channels_, 0);
			hdr_ = true;
			temp = static_cast<void*>(templdr);
			elemnt_size_ = channels_;
		}
		if (!temp)
		{
			std::cout << full_path_name_  << ": can't load image " << std::endl;
			state_.store(LOAD_FAIL);
			return false;
		}
		depth_ = 1;
		int total_size = width_ * height_ * depth_ * elemnt_size_;
		data_.resize(static_cast<size_t>(total_size));
		std::memcpy(data_.data(), temp, static_cast<size_t>(total_size));
		state_.store(LOADED);
		ready_.store(true);
		stbi_image_free(temp);
		return true;
	}
}