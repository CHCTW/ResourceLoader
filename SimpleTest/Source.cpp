#include<iostream>
#include <utility>
#include<thread>
#include "Image.h"
#include "Model.h"
void load(Resource::Image & im)
{
	im.loadImage();
}
int main()
{
	Resource::Image image("Assets/Images/milk0001.hdr");
	//image.loadImage();
	Resource::Model model("Assets/Models/sponza.obj");
	model.LoadModel();
	/*Resource::BaseModel<double> doubleModel("Assets/Models/sponza.obj");
	doubleModel.LoadModel();*/
	//std::cout << image.height() << std::endl;
	return 0;
}