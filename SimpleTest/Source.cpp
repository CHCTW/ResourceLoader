#include<iostream>
#include <utility>
#include<thread>
#include <chrono>
#include "Image.h"
#include "Model.h"
#include "Pipeline.h"
void load(Resource::BaseModel<float>& model,unsigned int sleep_ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(sleep_ms));
	model.loadModel();
}
int main()
{
	Resource::Image image("Assets/Images/milk0001.hdr");
	image.loadImage();
	Resource::BaseModel<float> model("Assets/Models/sponza.obj");
	//load(model);
	//model.LoadModel();
	std::vector<std::thread> threads;
	for (int i = 0; i < 100; ++i)
		threads.push_back(std::move(std::thread(load, std::ref(model),i*4)));
	for (int i = 0; i < 100; ++i)
	{
		if (threads[i].joinable())
			threads[i].join();
	}
	Resource::Pipeline pipeline("Assests/Pipelines/pipline.json");
	pipeline.loadPipeline();
	/*Resource::BaseModel<double> doubleModel("Assets/Models/sponza.obj");
	doubleModel.LoadModel();*/
	//std::cout << image.height() << std::endl;
	return 0;
}