#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include <list>
#include <thread>
#include <mutex>
#include <atomic>
#include "Work.hpp"
namespace Resource
{
	template<class ResourceClass>
	class Manager {
	public:
	private:
		std::unordered_map<std::string, std::shared_ptr<ResourceClass>> cache_;
		std::list<Work<ResourceClass>> waiting_queue_;
		std::atomic<bool> running_;
	};
}