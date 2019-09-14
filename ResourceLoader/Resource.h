#pragma once
#include <atomic>
#include <string>
namespace Resource
{
	enum Type
	{
		RESOURCE,
		IMAGE,
		PIPELINE,
		MODEL,
		COUNT
	};
	enum State
	{
		UNLOAD,
		LOADING,
		LOADED,
		LOAD_FAIL
	};
	class Resource
	{
	public:
		explicit Resource(Type type) :type_(type), state_(UNLOAD), ready_(false){}
		void setPathName(std::string full_path_name)
		{
			full_path_name_ = full_path_name;
		}
		virtual void release() {
			state_.store(UNLOAD);
			ready_.store(false);
		}
		State load();
		virtual ~Resource() { release(); }
	protected:
		virtual bool loadResource() = 0;
		std::string full_path_name_;
		std::atomic<State> state_;
		std::atomic<bool> ready_;
		Type type_;
	};
}
