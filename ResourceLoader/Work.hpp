#pragma once
#include <string>
#include <functional>
#include <memory>
namespace Resource
{
	template<class ResourceClass>
	struct Work
	{
		Work(std::string full_path_name, std::shared_ptr<ResourceClass> resource, std::function<void(ResourceClass const&)> callback,bool cache):full_path_name_(full_path_name),resource_(resource),callback_(callback),cache_(cache){
		}
		std::string full_path_name_;
		std::shared_ptr<ResourceClass> resource_;
		bool cache_;
		std::function<void(ResourceClass const&)> callback_;
	};
}