#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include "raymarching.h"
//__global__ void render(maths::Vector3f *framebuffer, int max_x, int max_y, float fov)
//{
//	int i = threadIdx.x + blockIdx.x * blockDim.x;
//	int j = threadIdx.y + blockIdx.y * blockDim.y;
//	if ((i >= max_x) || (j >= max_y)) return;
//	int pixel_index = j * max_x + i;
//	double dir_x = (j + 0.5f) - max_x / 2.0;
//	double dir_y = -(i + 0.5f) + max_y / 2.0;
//	double dir_z = -max_y / (2.0 * tan(fov/ 2.0));
//	int pixelIndex = j * max_x + i;
//	maths::Vector3f ray_direction = maths::Vector3f(dir_x, dir_y, dir_z).Normalized();
//}
//
//int main()
//{
//	int nx = 1920;
//	int ny = 1080;
//int num_pixels = nx* ny;
////size_t fb_size = 3 * num_pixels * sizeof(float);
////
////// allocate FB
////float* frame_buffer;
////cudaError_t cudaStatus;
////cudaMallocManaged((void**)&frame_buffer, fb_size);
////
////int tx = 8;
////int ty = 8;
////
////dim3 blocks(nx / tx + 1, ny / ty + 1);
////dim3 threads(tx, ty);
////render <<<blocks, threads >>> (frame_buffer);
//
///// <summary>
///// ////////
///// </summary>
/////
//raytracing::RayMarcher raymarcher;
//
//
//std::vector<maths::Vector3f> frameBuffer(num_pixels);
//
//maths::Vector3f* d_fb;
//
//cudaMallocManaged(&d_fb, num_pixels * sizeof(maths::Vector3f));
//
//maths::Sphere sphere1(1.0f, maths::Vector3f(0.0f, 0.0f, -10.0f));
//maths::Sphere sphere2(1.0f, maths::Vector3f(3.0f, 0.0f, -10.0f));
//
//	
//std::vector<maths::Sphere> h_sphere;
//h_sphere.push_back(sphere1);
//h_sphere.push_back(sphere2);
//
//maths::Sphere* d_spheres;
//cudaMalloc(&d_spheres, h_sphere.size() * sizeof(maths::Sphere));
//
//cudaMemcpy(d_spheres, h_sphere.data(), h_sphere.size() * sizeof(maths::Sphere), cudaMemcpyHostToDevice);
//
//
//return 0;
//}
//
//
//



