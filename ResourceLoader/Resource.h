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
		FILE,
		COUNT
	};
	enum State
	{
		UNLOAD,
		LOADING,
		LOADED,
		LOAD_FAIL
	};
	// To add new resource class, inherit from Resource and implement the loadResource method
	// The class should be thread safe
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
		Resource& operator=(Resource const & ref)
		{
			full_path_name_ = ref.full_path_name_;
			state_.store(ref.state_.load());
			ready_.store(ref.ready_.load());
			type_ = ref.type_;
			return *this;
		}
		std::string getName() const;
	protected:
		virtual bool loadResource() = 0;
		std::string full_path_name_;
		std::atomic<State> state_;
		std::atomic<bool> ready_;
		Type type_;
	};
}
