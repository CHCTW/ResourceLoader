#include<iostream>
#include <utility>
#include<thread>
#include <chrono>
#include "Image.h"
#include "Model.h"
#include "Pipeline.h"
#include "Manager.h"

void load(Resource::Resource& resource,unsigned int sleep_ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(sleep_ms));
	resource.load();
}
template<class ResourceClass>
void managerload(Resource::Manager<ResourceClass>& manager, unsigned int sleep_ms)
{
	manager.Get("sponza.obj", [](std::shared_ptr<const ResourceClass> resource) {
		std::cout<<"Thread calling : " << resource->getName() << std::endl;
		});
}
int main()
{
	Resource::Image image("Assets/Images/milk0001.hdr");
	Resource::Image image2;
	
	Resource::BaseModel<float> model("Assets/Models/sponza.obj");

	model.loadAsync([](Resource::Resource& res) {
		std::cout << "Load done from async";
		auto m = static_cast<Resource::BaseModel<float,unsigned int>*>(&res);
		std::cout << "Has mesh total : " << m->getMeshList().size() << std::endl;
		});
	model.waitForReady();
	Resource::Pipeline pipeline("Assets/Pipelines/pipeline.json");
	std::vector<std::thread> threads;
	for (int i = 0; i < 100; ++i)
		threads.push_back(std::move(std::thread(load, std::ref(pipeline),i*4)));
	for (int i = 0; i < 100; ++i)
	{
		if (threads[i].joinable())
			threads[i].join();
	}
	threads.clear();
	Resource::Manager<Resource::BaseModel<float>> manager;
	for (int i = 0; i < 100; ++i)
	{
		threads.push_back(std::move(std::thread(managerload<Resource::BaseModel<float>>, std::ref(manager), i * 4)));
		manager.Get("sponza.obj", [](std::shared_ptr<const Resource::BaseModel<float>> resource) {
			std::cout << resource->getName() << std::endl; });
	}
	for (int i = 0; i < 100; ++i)
	{
		if (threads[i].joinable())
			threads[i].join();
	}
	auto image_ptr = manager.GetMutable("sponza.obj", [](std::shared_ptr<Resource::BaseModel<float>> resource) {
		std::cout << resource->getName() << std::endl; });
	std::cout << "Start to wait" << std::endl;
	manager.waitAllWorkDone();
	return 0;
}