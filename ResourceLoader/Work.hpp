#pragma once
#include <string>
#include <functional>
#include <memory>
// what if want to handle mutable work???
namespace Resource
{
	template<class ResourceClass>
	struct Work
	{
		std::string full_path_name_;
		std::shared_ptr<ResourceClass> resource_;
		std::function<void(std::shared_ptr<const ResourceClass>)> const_callback_;
		std::function<void(std::shared_ptr<ResourceClass>)> callback_;
		bool use_const_;
	};
}