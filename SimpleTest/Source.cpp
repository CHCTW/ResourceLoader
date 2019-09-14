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
int main()
{
	Resource::Image image("Assets/Images/milk0001.hdr");
	Resource::BaseModel<float> model("Assets/Models/sponza.obj");
	Resource::Pipeline pipeline("Assets/Pipelines/pipeline.json");
	std::vector<std::thread> threads;
	for (int i = 0; i < 100; ++i)
		threads.push_back(std::move(std::thread(load, std::ref(pipeline),i*4)));
	for (int i = 0; i < 100; ++i)
	{
		if (threads[i].joinable())
			threads[i].join();
	}
	Resource::Manager<Resource::Pipeline> pipeline_manager;
	return 0;
}