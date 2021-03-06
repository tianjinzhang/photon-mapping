#ifndef _GETLIGHTVOLUME_CU
#define _GETLIGHTVOLUME_CU

#include <helper_cuda.h>
#include <curand_kernel.h>
#include <cuda_runtime.h>


#include "cu_tool.h"
//get direct illumination//////////////////
///////////////////////////////////////
//render the volume
__global__ void
kernel_calDirect_x(unsigned char *pbo,unsigned int x,unsigned int lastx,float*c)
{
	unsigned int y = threadIdx.x;
	unsigned int z = blockIdx.x;
	unsigned int w =  size[0] - 1;
	unsigned int h =  size[1] - 1;
	unsigned int d =  size[2] - 1;
	unsigned int i =  x + y * (w + 1) + z * (h + 1) * (w + 1);
	float3 ObjectCoor = make_float3(x*1.0/w,y*1.0/h,z*1.0/d);
	
	ObjectCoor = toObjectWorldCoor(ObjectCoor);
	float3 lightCoor = make_float3(cudaLightPositionAfter[0],cudaLightPositionAfter[1],cudaLightPositionAfter[2]);
	//set the light style
	//float3 ObjectToLightV =  normalize(lightCoor - ObjectCoor);
	float3 ObjectToLightV =  normalize(lightCoor);
	float cosine = int(lastx - x)*ObjectToLightV.x;
	unsigned int target_y =  toTexWorldCoorAxis(ObjectToLightV.y /cosine/w  + ObjectCoor.y) * h ;
	unsigned int target_z =  toTexWorldCoorAxis(ObjectToLightV.z /cosine/w  + ObjectCoor.z) * d ;
    float alpha = tex1D(tftex,tex3D(tex,lastx*1.0f/w,target_y*1.0f/h,target_z*1.0f/d));
	
	uchar1 data;
	surf2Dread(&data,lightSurface, target_y , target_z,cudaBoundaryModeClamp);
    
	data.x = (1.0f - alpha)*data.x;
	surf2Dwrite(data,lightSurface2,target_y, target_z,cudaBoundaryModeClamp);
	
	float weight = 1.0f - 2.0f * acosf(cosine)/CUDART_PI_F;

	pbo[i] += data.x * weight;
	

}
__global__ void
kernel_calDirect_swap_x(unsigned char *pbo,unsigned int x,unsigned int lastx,float*c)
{

	unsigned int y = threadIdx.x;
	unsigned int z = blockIdx.x;
	unsigned int w =  size[0] - 1;
	unsigned int h =  size[1] - 1;
	unsigned int d =  size[2] - 1;
	unsigned int i =  x + y * (w + 1) + z * (h + 1) * (w + 1);
	float3 ObjectCoor = make_float3(x*1.0/w,y*1.0/h,z*1.0/d);
	
	ObjectCoor = toObjectWorldCoor( ObjectCoor);
	float3 lightCoor = make_float3(cudaLightPositionAfter[0],cudaLightPositionAfter[1],cudaLightPositionAfter[2]);
	//set the light style
	//float3 ObjectToLightV =  normalize(lightCoor - ObjectCoor);
	float3 ObjectToLightV =  normalize(lightCoor);
	float cosine = int(lastx - x)*ObjectToLightV.x;
	unsigned int target_y =  toTexWorldCoorAxis(ObjectToLightV.y /cosine/w  + ObjectCoor.y) * h ;
	unsigned int target_z =  toTexWorldCoorAxis(ObjectToLightV.z /cosine/w  + ObjectCoor.z) * d ;
    float alpha = tex1D(tftex,tex3D(tex,lastx*1.0f/w,target_y*1.0f/h,target_z*1.0f/d));
	
	uchar1 data;
	surf2Dread(&data,lightSurface2, target_y , target_z,cudaBoundaryModeClamp);
   
	data.x = (1.0f - alpha)*data.x;
	surf2Dwrite(data,lightSurface,target_y , target_z,cudaBoundaryModeClamp);
	
	float weight = 1.0f - 2.0f * acosf(cosine)/CUDART_PI_F;
	
	pbo[i] += data.x * weight;
	

}
///////////////////////////////////////////////////////////////
__global__ void
kernel_calDirect_y(unsigned char *pbo,unsigned int y,unsigned int lasty,float*c)
{
	
	unsigned int x = threadIdx.x;
	unsigned int z = blockIdx.x;
	unsigned int w =  size[0] - 1;
	unsigned int h =  size[1] - 1;
	unsigned int d =  size[2] - 1;
	unsigned int i =  x + y * (w + 1) + z * (h + 1) * (w + 1);
	float3 ObjectCoor = make_float3(x*1.0/w,y*1.0/h,z*1.0/d);
	
	ObjectCoor = toObjectWorldCoor(ObjectCoor);

	float3 lightCoor = make_float3(cudaLightPositionAfter[0],cudaLightPositionAfter[1],cudaLightPositionAfter[2]);
	//float3 ObjectToLightV =  normalize(lightCoor - ObjectCoor);
	float3 ObjectToLightV =  normalize(lightCoor);
	float cosine = int(lasty - y)*ObjectToLightV.y;
	unsigned int target_x =   toTexWorldCoorAxis(ObjectToLightV.x /cosine/h + ObjectCoor.x ) * w ;
	unsigned int target_z =   toTexWorldCoorAxis(ObjectToLightV.z /cosine/h  + ObjectCoor.z ) * d ;
    float alpha = tex1D(tftex,tex3D(tex,target_x*1.0f/w,lasty*1.0f/h,target_z*1.0f/d));

	uchar1 data;
	surf2Dread(&data,lightSurface, target_x , target_z,cudaBoundaryModeClamp);
	
    data.x = (1.0f - alpha)*data.x;
	surf2Dwrite(data,lightSurface2,target_x , target_z,cudaBoundaryModeClamp);

    float weight = 1.0f - 2.0f * acosf(cosine)/CUDART_PI_F;
	
	pbo[i] += data.x * weight;
	


	
}
__global__ void
kernel_calDirect_swap_y(unsigned char *pbo,unsigned int y,unsigned int lasty,float*c)
{
	
	unsigned int x = threadIdx.x;
	unsigned int z = blockIdx.x;
	unsigned int w =  size[0] - 1;
	unsigned int h =  size[1] - 1;
	unsigned int d =  size[2] - 1;
	unsigned int i =  x + y * (w + 1) + z * (h + 1) * (w + 1);
	float3 ObjectCoor = make_float3(x*1.0/w,y*1.0/h,z*1.0/d);
	
	ObjectCoor = toObjectWorldCoor(ObjectCoor);
	
	float3 lightCoor = make_float3(cudaLightPositionAfter[0],cudaLightPositionAfter[1],cudaLightPositionAfter[2]);
	//float3 ObjectToLightV =  normalize(lightCoor - ObjectCoor);
	float3 ObjectToLightV =  normalize(lightCoor);
	float cosine = int(lasty - y)*ObjectToLightV.y;
	unsigned int target_x =   toTexWorldCoorAxis(ObjectToLightV.x /cosine/h + ObjectCoor.x ) * w ;
	unsigned int target_z =   toTexWorldCoorAxis(ObjectToLightV.z /cosine/h  + ObjectCoor.z ) * d ;
    float alpha = tex1D(tftex,tex3D(tex,target_x*1.0f/w,lasty*1.0f/h,target_z*1.0f/d));

	uchar1 data;
	surf2Dread(&data,lightSurface2, target_x, target_z,cudaBoundaryModeClamp);
	
    data.x = (1.0f - alpha)*data.x;
	surf2Dwrite(data,lightSurface,target_x, target_z,cudaBoundaryModeClamp);

	float weight = 1.0f - 2.0f * acosf(cosine)/CUDART_PI_F;

	pbo[i] += data.x * weight;
	

	
}
////////////////////////////////////////////////////////////////
__global__ void
kernel_calDirect_z(unsigned char *pbo,unsigned int z,unsigned int lastz,float*c)
{

	unsigned int x = threadIdx.x ;
	unsigned int y = blockIdx.x ;
	unsigned int w =  size[0] - 1;
	unsigned int h =  size[1] - 1;
	unsigned int d =  size[2] - 1 ;
	unsigned int i =  x + y * (w + 1) + z * (h + 1) * (w + 1);
	float3 ObjectCoor = make_float3(x*1.0/w,y*1.0/h,z*1.0/d);
	
	ObjectCoor = toObjectWorldCoor(ObjectCoor);
   
	float3 lightCoor = make_float3(cudaLightPositionAfter[0],cudaLightPositionAfter[1],cudaLightPositionAfter[2]);
	//float3 ObjectToLightV =  normalize(lightCoor - ObjectCoor);
	float3 ObjectToLightV =  normalize(lightCoor);

	float cosine = int(lastz - z)*ObjectToLightV.z;
	unsigned int target_y =  toTexWorldCoorAxis(ObjectToLightV.y /cosine/d  + ObjectCoor.y ) * h ;
	unsigned int target_x =  toTexWorldCoorAxis(ObjectToLightV.x /cosine/d + ObjectCoor.x ) * w;
    float alpha = tex1D(tftex,tex3D(tex,target_x*1.0f/w,target_y*1.0f/h,lastz*1.0f/d));
	
	uchar1 data;
	surf2Dread(&data,lightSurface, target_x , target_y,cudaBoundaryModeClamp);

	data.x = (1.0f - alpha)*data.x;
	surf2Dwrite(data,lightSurface2,target_x , target_y,cudaBoundaryModeClamp);

    float weight = 1.0f - 2.0f * acosf(cosine)/CUDART_PI_F;
	
	pbo[i] += data.x * weight;
	
	
  
	
}
__global__ void
kernel_calDirect_swap_z(unsigned char *pbo,unsigned int z,unsigned int lastz,float*c)
{

	unsigned int x = threadIdx.x ;
	unsigned int y = blockIdx.x ;
	unsigned int w =  size[0] - 1;
	unsigned int h =  size[1] - 1;
	unsigned int d =  size[2] - 1 ;
	unsigned int i =  x + y * (w + 1) + z * (h + 1) * (w + 1);
	float3 ObjectCoor = make_float3(x*1.0/w,y*1.0/h,z*1.0/d);
	
	ObjectCoor = toObjectWorldCoor(ObjectCoor);
   
	float3 lightCoor = make_float3(cudaLightPositionAfter[0],cudaLightPositionAfter[1],cudaLightPositionAfter[2]);
	//float3 ObjectToLightV =  normalize(lightCoor - ObjectCoor);
	float3 ObjectToLightV =  normalize(lightCoor);
	float cosine = int(lastz - z)*ObjectToLightV.z;
	unsigned int target_y =  toTexWorldCoorAxis(ObjectToLightV.y /cosine/d  + ObjectCoor.y ) * h ;
	unsigned int target_x =  toTexWorldCoorAxis(ObjectToLightV.x /cosine/d + ObjectCoor.x ) * w;

    float alpha = tex1D(tftex,tex3D(tex,target_x*1.0f/w,target_y*1.0f/h,lastz*1.0f/d));
	

	uchar1 data;
	surf2Dread(&data,lightSurface2, target_x, target_y,cudaBoundaryModeClamp);
	
	data.x = (1.0f - alpha)*data.x;
	surf2Dwrite(data,lightSurface,target_x, target_y,cudaBoundaryModeClamp);
	
	float weight = 1.0f - 2.0f * acosf(cosine)/CUDART_PI_F;
	
	pbo[i] += data.x * weight;
	

	
}
///////////////////////////////////////////////////////////////
void render_Kernel_DI(dim3 grid,dim3 block,unsigned char* pbo,float *lightPosition,int * surfaceSize,float*c)
{
	//initialize light volume
	kernel_initial_light_volume<<<grid,block>>>(pbo,c);
	checkCudaErrors(cudaDeviceSynchronize());
    dim3 surfaceGrid(surfaceSize[1]);
    dim3 surfaceBlock(surfaceSize[0]);
	
	int w = block.x;
	int h = grid.x;
	int d = grid.y;

	dim3 x(w);
    dim3 y(h);
	dim3 z(d);
	float _lightPosition[3] = {0.0};
	if(lightPosition[0] < 0.0)
	{
		_lightPosition[0] = - lightPosition[0];
		
	}
	if(lightPosition[0] > 0.0)
	{
		_lightPosition[0] =  lightPosition[0];
		
	}
	if(lightPosition[1] > 0.0)
	{
		_lightPosition[1] =  lightPosition[1];
		
	}
	if(lightPosition[1] < 0.0)
	{
		_lightPosition[1] = - lightPosition[1];
		
	}
	if(lightPosition[2] < 0.0)
	{
		_lightPosition[2] = - lightPosition[2];
		
	}
	if(lightPosition[2] > 0.0)
	{
		_lightPosition[2] =  lightPosition[2];
		
	}

    checkCudaErrors(cudaDeviceSynchronize());

	//frame of rendering /////////////////////////////////////////
	for(int times = 0;times < 2;times++)
	{
		//initialize the buffer 
		kernel_initial_light_surface<<<surfaceGrid,surfaceBlock>>>();
		checkCudaErrors(cudaDeviceSynchronize());

		if(_lightPosition[0] >= _lightPosition[1] && _lightPosition[0] > _lightPosition[2])
		{
			if(lightPosition[0] > 0)
			{
				for(int i = w - 1;i >= 0;i--)
				{ 
					if(i%2 == 0)
					{
						kernel_calDirect_x<<<z,y>>>(pbo,i,i + 1,c);
						checkCudaErrors(cudaDeviceSynchronize());
					}
					else
					{
						kernel_calDirect_swap_x<<<z,y>>>(pbo,i,i + 1,c);
						checkCudaErrors(cudaDeviceSynchronize());
					}
				
				}

			}else
			{
				for(int i = 0;i < w;i++)
				{
					if(i%2 == 0)
					{
						kernel_calDirect_x<<<z,y>>>(pbo,i,i - 1,c);
						checkCudaErrors(cudaDeviceSynchronize());
					}
					else
					{
						kernel_calDirect_swap_x<<<z,y>>>(pbo,i,i - 1,c);
						checkCudaErrors(cudaDeviceSynchronize());
					}
				}		
			
			}
			_lightPosition[0] = 0;

		}
		else if(_lightPosition[1] > _lightPosition[0] && _lightPosition[1] > _lightPosition[2])
		{
			if(lightPosition[1] > 0)
			{
				for(int i = h - 1;i >= 0;i--)
				{
					if(i%2 == 0)
					{
						kernel_calDirect_y<<<z,x>>>(pbo,i,i + 1,c);
						checkCudaErrors(cudaDeviceSynchronize());
					}
					else
					{
						kernel_calDirect_swap_y<<<z,x>>>(pbo,i,i + 1,c);
						checkCudaErrors(cudaDeviceSynchronize());
					}	
				}
	
			}else
			{
				for(int i = 0;i < h ;i++)
				{
					if(i%2 == 0)
					{
						kernel_calDirect_y<<<z,x>>>(pbo,i,i - 1,c);
						checkCudaErrors(cudaDeviceSynchronize());
					}
					else
					{
						kernel_calDirect_swap_y<<<z,x>>>(pbo,i,i - 1,c);
						checkCudaErrors(cudaDeviceSynchronize());
					}
				
				}
			
			}
			_lightPosition[1] = 0;

		}else
		{
			if(lightPosition[2] > 0)
			{
				for(int i = d - 1;i >= 0;i--)
				{
					if(i%2 == 0)
					{
						kernel_calDirect_z<<<y,x>>>(pbo,i,i + 1,c);
						checkCudaErrors(cudaDeviceSynchronize());
					}
					else
					{
						kernel_calDirect_swap_z<<<y,x>>>(pbo,i,i + 1,c);
						checkCudaErrors(cudaDeviceSynchronize());
					}		
				
				}			
						
			}
			else
			{
				for(int i = 0;i < d ;i++)
				{
					if(i%2 == 0)
					{
						kernel_calDirect_z<<<y,x>>>(pbo,i,i - 1,c);
						checkCudaErrors(cudaDeviceSynchronize());
					}
					else
					{
						kernel_calDirect_swap_z<<<y,x>>>(pbo,i,i - 1,c);
						checkCudaErrors(cudaDeviceSynchronize());
					}
				
				}
			
			}
			_lightPosition[2] = 0;

		}
    }

	

}

/////////////////////////////////////////////////////
//get indirect illumination
/////////////////////////////////////////////////////
__global__ void
kernel_calInDirect(unsigned char* pbo,float*c)
{
	
	unsigned int i = threadIdx.x + blockIdx.x * blockDim.x;

	unsigned int w = size[0] - 1;
	unsigned int h = size[1] - 1;
	unsigned int d = size[2] - 1 ;
	//unsigned int sizeData= w*h*d;
	float3 begin = make_float3(cudalightPosition[0],cudalightPosition[1],cudalightPosition[2]);
    float3 getTex;
	float alpha;
	int count = 0;
    int loction = 0;
	float3 direction = normalize(random(i));
	float Max = photon_dis_step[0];
	float Step = photon_dis_step[1];
    float j;
	for(j = Step;j <= Max;j += Step)
	{
		begin = begin + direction*Step;
	    getTex = toTexCoor(toTheWorldInvert(begin));
		if(getTex.x <= 0||getTex.x >= 1||getTex.y <= 0||getTex.y >= 1||getTex.z <= 0||getTex.z >= 1)
		{
			continue;
		}
		else
		{
			alpha = tex1D(tftex,tex3D(tex,getTex.x,getTex.y,getTex.z));
			if(0 == alpha)
			{
				continue;
			}else if(alpha > 0.0)
			{
				if(count != 0)
				{
				  
                   loction = (getTex.x * w + w * getTex.y * h + w * h * getTex.z * d);
				   pbo[loction] = 255;
				    loction = (getTex.x * w + 1 + w * getTex.y * h + w * h * getTex.z * d);
				   pbo[loction] = 255;
				    loction = (getTex.x * w - 1 + w * getTex.y * h + w * h * getTex.z * d);
				   pbo[loction] = 255;
				    loction = (getTex.x * w + w * (getTex.y * h + 1) + w * h * getTex.z * d);
				   pbo[loction] = 255;
				    loction = (getTex.x * w + w * (getTex.y * h - 1)+ w * h * getTex.z * d);
				   pbo[loction] = 255;
				    loction = (getTex.x * w + w * getTex.y * h + w * h * (getTex.z * d + 1));
				   pbo[loction] = 255;
				    loction = (getTex.x * w + w * getTex.y * h + w * h * (getTex.z * d - 1));
				   pbo[loction] = 255;

                    i = i*168017%33554432;  
					direction = normalize(random(i));
				}
				count++;
			
			}
		}
	}
	
}

void render_Kernel_InDI(unsigned int count,unsigned char* pbo,float*c)
{
	
	dim3 grid(count/1024 + 1);
	dim3 block(1024);
	
	kernel_calInDirect<<<grid,block>>>(pbo,c);

}
/////////////////////////////////////////////////////
//get the photon map
/////////////////////////////////////////////////////
__global__ void
kernel_calPhotonMapHor(unsigned char* pbo,unsigned char* photons,unsigned int with,unsigned int heigh,float*c)
{
	unsigned int y = threadIdx.x;
	unsigned int x = blockIdx.x;
	unsigned int w = with;
	unsigned int i = x + w * y;
	unsigned int location;
	unsigned int MAX = with * heigh - 1;
	float4 result;
	
	float kernel[11] = {11,10,9,8,7,6,5,4,3,2,1};
    result.x = pbo[i*4 + 0] * kernel[0];
	result.y = pbo[i*4 + 1] * kernel[0];
	result.z = pbo[i*4 + 2] * kernel[0];
	for(int step = 1;step < 11;step++)
	{
		location = i + step;
		if(location > MAX)
			continue;
		result.x += pbo[location*4 + 0] * kernel[step];
		result.y += pbo[location*4 + 1] * kernel[step];
		result.z += pbo[location*4 + 2] * kernel[step];

		location = i - step;
		if(location > MAX)
			continue;
		result.x += pbo[location*4 + 0] * kernel[step];
		result.y += pbo[location*4 + 1] * kernel[step];
		result.z += pbo[location*4 + 2] * kernel[step];

	}
	photons[i*4 + 0] = result.x/121;
	photons[i*4 + 1] = result.y/121;
	photons[i*4 + 2] = result.z/121;

}
__global__ void 
kernel_calPhotonMapVer(unsigned char* pbo,unsigned char* photons,unsigned int with,unsigned int heigh,float*c)
{
	unsigned int y = threadIdx.x;
	unsigned int x = blockIdx.x;
	unsigned int w = with;
	unsigned int i = x + w * y;
	unsigned int MAX = with * heigh - 1;
	float4 result;
	unsigned int location;
	float kernel[11] = {11,10,9,8,7,6,5,4,3,2,1};
    result.x = photons[i*4 + 0] * kernel[0];
	result.y = photons[i*4 + 1] * kernel[0];
	result.z = photons[i*4 + 2] * kernel[0];
	for(int step = 1;step < 11;step++)
	{
		location = x + w * (y + step);
		if(location > MAX)
			continue;
		result.x += photons[location*4 + 0] * kernel[step];
		result.y += photons[location*4 + 1] * kernel[step];
		result.z += photons[location*4 + 2] * kernel[step];

		location = x + w * (y - step);
		if(location > MAX)
			continue;
		result.x += photons[location*4 + 0] * kernel[step];
		result.y += photons[location*4 + 1] * kernel[step];
		result.z += photons[location*4 + 2] * kernel[step];

	}
	pbo[i*4 + 0] = result.x/121;
	pbo[i*4 + 1] = result.y/121;
	pbo[i*4 + 2] = result.z/121;

}
void render_Kernel_PhotonMap(unsigned int with,unsigned int heigh,unsigned char* pbo,unsigned char* photons,float*c)
{
	dim3 grid(with);
	dim3 block(heigh);
    for(int i = 0;i<2;i++)
    {
	   kernel_calPhotonMapHor<<<grid,block>>>(pbo,photons,with,heigh,c);
	   checkCudaErrors(cudaThreadSynchronize());
	   kernel_calPhotonMapVer<<<grid,block>>>(pbo,photons,with,heigh,c);
    }
}
/////////////////////////////////////////////////////
//render ambient occulation map
/////////////////////////////////////////////////////
__global__ void
kernel_calAO(unsigned char* pbo,float *c)
{
	unsigned int _x = threadIdx.x;
	unsigned int _y = blockIdx.x;
	unsigned int _z = blockIdx.y;
    unsigned int w = size[0] - 1;
	unsigned int h = size[1] - 1;
	unsigned int d = size[2] - 1;
	float x = _x*1.0/w;
	float y = _y*1.0/h;
	float z = _z*1.0/d;
	
	float alpha = tex1D(tftex,tex3D(tex,x,y,z));
	float3 begin = make_float3(x,y,z);
	float3 direction;
	float result = 0;
	float _result = 0;
	float attenuate;
	unsigned int i = _x + _y * (w + 1) + _z * (h + 1) * (w + 1);
	unsigned int r = i;
    int aoCount = ao[0];
	int aoStep = ao[1];
    int rays = ao[2];
	float _step = 1.0 * aoStep/1000;
	_result = 1.0/aoCount;
	
   
	for(int j = 0;j < rays;j++)
	{ 
		r = r*j*j*168017%33554432; 
		direction = normalize(random(r)) * _step; 
		//direction = make_float3(0.0,1.0,0.0) * _step;
		attenuate = 1.0;
		for(int k = 0;k < aoCount;k++)
		{
			begin += direction;
			if(begin.x < 0||begin.x > 1 ||begin.y < 0||begin.y > 1||begin.z < 0||begin.z > 1)
				break;
			alpha = tex1D(tftex,tex3D(tex,begin.x,begin.y,begin.z));
			attenuate *= (1 - alpha);
            result += attenuate*_result;

		}

	}
   
	{
		 pbo[i] = (result/rays*255);
	}

}
void render_kernel_AOMap(dim3 grid,dim3 block,unsigned char*pbo,float*c)
{
	kernel_calAO<<<grid,block>>>(pbo,c);
}
//initialize the data of volume
cudaArray* InitialCudaData(void*data,unsigned int w,unsigned int h,unsigned int d)
{
	cudaArray *cuArray;
	cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc(8,0,0,0,cudaChannelFormatKindUnsigned);
	cudaExtent extent;
	extent.width = w;
	extent.height = h;
	extent.depth = d;
	checkCudaErrors(cudaMalloc3DArray(&cuArray,&channelDesc,extent));
    
	cudaMemcpy3DParms copyParams = {0};
	copyParams.srcPtr = make_cudaPitchedPtr((void*)data,w,w,h);
	copyParams.dstArray = cuArray;
	copyParams.extent = extent;
	copyParams.kind = cudaMemcpyHostToDevice;
	cudaMemcpy3D(&copyParams);
    //texture with float coordinate,with Liner filter;
	tex.filterMode = cudaFilterModeLinear;
	tex.normalized = true;
	tex.addressMode[0] = cudaAddressModeClamp;
	tex.addressMode[1] = cudaAddressModeClamp;
	tex.addressMode[2] = cudaAddressModeClamp;
	tex.channelDesc = channelDesc;
	checkCudaErrors(cudaBindTextureToArray(tex,cuArray,channelDesc));

	return cuArray;

}
//initialize the data of transform function
cudaArray* InitialCudaTranData(void* tfdata)
{
	cudaArray *cuArray;
	cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc(8,0,0,0,cudaChannelFormatKindUnsigned);
	checkCudaErrors(cudaMallocArray(&cuArray,&channelDesc,256,1));

	checkCudaErrors(cudaMemcpyToArray(cuArray,0,0,tfdata,256,cudaMemcpyHostToDevice));

	tftex.filterMode = cudaFilterModeLinear;
	tftex.normalized = true;
	tftex.addressMode[0] = cudaAddressModeClamp;
	tftex.channelDesc = channelDesc;
	checkCudaErrors(cudaBindTextureToArray(tftex,cuArray,channelDesc));


	return cuArray;

}
//set the light position
void setLightPosition(float* position)
{
	checkCudaErrors(cudaMemcpyToSymbol(cudalightPosition,position,sizeof(float)*3));

}

//set the light position after transform,scaling matrix
void setLightPositionAfter(float* position)
{
	checkCudaErrors(cudaMemcpyToSymbol(cudaLightPositionAfter,position,sizeof(float)*3));
}

//initial light surface
void initialLightSurface(int width,int height,int bits,cudaArray * surfaceArray,cudaArray * surfaceArray2)
{
	//lightSurface
	cudaChannelFormatDesc channelDesc = cudaCreateChannelDesc(bits,0,0,0,cudaChannelFormatKindUnsigned);
	cudaMallocArray(&surfaceArray,&channelDesc,width,height,cudaArraySurfaceLoadStore);
	cudaBindSurfaceToArray(lightSurface,surfaceArray);
	//lightSurface2 for swap
	cudaMallocArray(&surfaceArray2,&channelDesc,width,height,cudaArraySurfaceLoadStore);
	cudaBindSurfaceToArray(lightSurface2,surfaceArray2);

	int size[2];
	size[0] = width;
	size[1] = height;
    checkCudaErrors(cudaMemcpyToSymbol(lightSurfaceSize,size,sizeof(int)*2));
}
//set the other parameters
void setSizeParameters(int w,int h,int d)
{
	int _size[3];
	_size[0] = w;
	_size[1] = h;
	_size[2] = d;
	checkCudaErrors(cudaMemcpyToSymbol(size,_size,sizeof(_size)));

}
//set the photon parameters
void setPhotonParameters(float*_photon_dis_step)
{
		
	checkCudaErrors(cudaMemcpyToSymbol(photon_dis_step,_photon_dis_step,2*sizeof(float)));
	
}
//set the vertex transform matrix
void setVertextTran(float* transMatrix)
{
	checkCudaErrors(cudaMemcpyToSymbol(cudaVetexTran,transMatrix,sizeof(float)*16));

}
void setInvertVertextTran(float* transMatrix)
{
	checkCudaErrors(cudaMemcpyToSymbol(cudaInvertVetexTran,transMatrix,sizeof(float)*16));

}

//set ambient occulation count and step
void setAOParameters(int count,int step,int rays)
{
	int _ao[3];
	_ao[0] = count;
	_ao[1] = step;
	_ao[2] = rays;
	checkCudaErrors(cudaMemcpyToSymbol(ao,_ao,sizeof(_ao)));
}
#endif

