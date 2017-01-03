#ifndef CU_TOOL_H
#define CU_TOOL_H
#include <helper_math.h>
#include<math_constants.h>
texture<unsigned char,cudaTextureType3D,cudaReadModeNormalizedFloat> tex;
texture<unsigned char,cudaTextureType1D,cudaReadModeNormalizedFloat> tftex;
surface<void,cudaSurfaceType2D> lightSurface;
surface<void,cudaSurfaceType2D> lightSurface2;
//contain w h d
__constant__ int size[3];
//__constant__ float step;
__constant__ float cudalightPosition[3];
//the distance and step photon forward
__constant__ float photon_dis_step[2];
//the transform matrix
__constant__ float cudaVetexTran[16];
//the invert transform matrix
__constant__ float cudaInvertVetexTran[16];

//the ambient occulation count and step
__constant__ int ao[3];

__constant__ float cudaLightPositionAfter[3];

//the project buffer with and height
__constant__ int lightSurfaceSize[2];



inline __device__
float3 toWorldCoor(float3 t)
{
	return make_float3(t.x * 2.0f - 1.0f,t.y * 2.0f - 1.0f, - t.z *2.0f + 1.0f);
}
inline __device__
float3 toTexCoor(float3 t)
{
	return make_float3((t.x + 1.0f)/2.0f,(t.y + 1.0f)/2.0f,(1.0f - t.z)/2.0f); 
}
inline __device__
float3 random(unsigned int seed)
{
    
	float u = 0.0;
	float v = 0.0;
	float x = 0.0;
	float y = 0.0;
	float z = 0.0;
	float theta = 0.0;
	float phi = 0.0;
	u = ((16807 * seed + 2531011)%33554432)/33554431.0f;
	v = (16807 * seed + 235417)%75497472/75497471.0f;
	theta = 2*3.141592*u;
	phi = acos(2*v-1);
    x = sin(theta)*sin(phi);
	y = cos(theta)*sin(phi);
	z = cos(phi);
	return make_float3(x,y,z);

}
inline __device__
float3 toTheWorldInvert(float3 t)
{
	float3 vOut;

	vOut.x = cudaInvertVetexTran[0] * t.x + cudaInvertVetexTran[4] * t.y + cudaInvertVetexTran[8] *  t.z ;	 
	vOut.y = cudaInvertVetexTran[1] * t.x + cudaInvertVetexTran[5] * t.y + cudaInvertVetexTran[9] *  t.z ;	
	vOut.z = cudaInvertVetexTran[2] * t.x + cudaInvertVetexTran[6] * t.y + cudaInvertVetexTran[10] * t.z ;

	return vOut;

}
inline __device__
float3 toTheWorld(float3 t)
{
	float3 vOut;

	vOut.x = cudaVetexTran[0] * t.x + cudaVetexTran[4] * t.y + cudaVetexTran[8] *  t.z ;	 
	vOut.y = cudaVetexTran[1] * t.x + cudaVetexTran[5] * t.y + cudaVetexTran[9] *  t.z ;	
	vOut.z = cudaVetexTran[2] * t.x + cudaVetexTran[6] * t.y + cudaVetexTran[10] * t.z ;

	return vOut;

}
inline __device__
float3 toObjectWorldCoor(float3 t)
{
	return (t * 2.0f - 1.0f);

}
inline __device__
float toTexWorldCoorAxis(float t)
{
	return (t + 1.0f)/2.0f;
}
//initialize the light volume
__global__ void
kernel_initial_light_volume(unsigned char *pbo,float *c)
{
	unsigned int x = threadIdx.x;
	unsigned int y = blockIdx.x;
	unsigned int z = blockIdx.y;
	unsigned int i = x + y * size[0] + z * size[0] * size[1];
	pbo[i] = 0;
	
	
}
//initialize the light surface
__global__ void
kernel_initial_light_surface()
{
    unsigned int x = threadIdx.x;
	unsigned int y = blockIdx.x;
	uchar1 data = make_uchar1(255);
	surf2Dwrite(data,lightSurface, x, y,cudaBoundaryModeClamp);
	surf2Dwrite(data,lightSurface2, x, y,cudaBoundaryModeClamp);
    
}
///////////////////////////////////////////////////////////////


#endif