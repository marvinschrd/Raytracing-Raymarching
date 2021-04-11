#include "gtest/gtest.h"


#include "raymarching.h"


namespace raytracing
{
	
TEST(Raymarching, Image_output)
{
	maths::Vector3f blue(0.0f, 0.0f, 255.0f);
	maths::Vector3f red(255.0f, 0.0f, 0.0f);
	maths::Vector3f green(0.0f, 128.0f, 0.0f);
	maths::Vector3f white(255.0f, 255.0f, 0.0f);


	Material material_test(0.2f, red);
	Material material_test2(0.1f, blue);
	Material material_test3(0.0f, green);
	Material material_test4(0.0f, white);

	int width = 1920;
	int heigth = 1080;
	float fov = 51.52f;
	double bias = 1e-4;

	maths::Plane plane(maths::Vector3f(0.0f, -20.0f, 0.0f), maths::Vector3f(0.0f, 1.0f, 0.0f));
	plane.SetMaterial(material_test4);

	maths::Sphere sphere1(6.0f, maths::Vector3f(-5.0f, 0.0f, -16.0f));
	maths::Sphere sphere3(2.0f, maths::Vector3f(4.0f, 0.0f, -8.0f));
	maths::Sphere sphere4(3.0f, maths::Vector3f(8.0f, 0.0f, -5.0f));
	maths::Sphere sphere5(75.0f, maths::Vector3f(0.0f, -84.0f, -10.0f));


	sphere1.set_material(material_test);
	sphere3.set_material(material_test2);
	sphere4.set_material(material_test3);
	sphere5.set_material(material_test4);


	PointLight light;
	std::vector<maths::Sphere> spheres;
	//spheres.push_back(sphere4);
	//spheres.push_back(sphere3);
	spheres.push_back(sphere1);
	//spheres.push_back(sphere5);

	std::vector<maths::Plane> planes;

	/*RayTracer raytracer;
	raytracer.SetScene(spheres, planes, light, heigth, width, fov, bias);
	raytracer.Render();*/

	RayMarcher raymarcher;
	raymarcher.SetScene(spheres, planes, light, heigth, width, fov, bias);
	raymarcher.Render();
}

	
}
