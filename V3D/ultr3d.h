#ifndef ULTR3D_H
#define ULTR3D_H
//opengl lib
#pragma comment(lib,"glew32.lib")
#pragma comment(lib,"gltools.lib")
//CUDA Runtime,Interop
#pragma comment(lib,"cudart.lib")
#include <GL/glew.h>
#include <GLTools.h>
#include <GLBatch.h>
#include <GLMatrixStack.h>
#include <GLFrustum.h>
#include <GLGeometryTransform.h>
#include <GLFrame.h>
#include <stdio.h>
//Qt lib
#include <QGLWidget>
#include <QDebug>
#include <QKeyEvent>
#include <QVector>
#include <QTime>
#include <QImage>
#include <QRgb>
#include <QIcon>

#include <cuda_runtime.h>
#include <cuda_gl_interop.h>
//CUDA utilities
#include <helper_cuda.h>

class ultr3D : public QGLWidget
{
	Q_OBJECT

public:
	ultr3D(QWidget *parent = 0, Qt::WFlags flags = 0);
	ultr3D(const char* File,QWidget *parent = 0, Qt::WFlags flags = 0);
	ultr3D(const char* File,int width,int height,int depth,QWidget *parent = 0, Qt::WFlags flags = 0);
	 ~ultr3D();



    GLBatch cube;
	GLMatrixStack modelviewStack;
	GLFrustum projection;
	GLMatrixStack projectionStack;
	GLGeometryTransform mvpPipline;
	GLFrame mymodelview;


	GLuint  ultr;
	//getBack Shader /////////////////////////
	GLuint getBack;
	GLuint framebuffer;
	GLuint texColorbuffer;
	GLuint rbo;
	GLint getBackMVP;
  
	GLint MVP;
	GLint MV;
	GLint TEX;
	GLint BACKTEX;
	GLint STEP;
	GLint WIDTH;
	GLint HEIGHT;

	//photons Shader////////////////////////
	GLuint photonShader;
	GLuint photon_framebuffer;
	GLuint photon_texBuffer;
	GLuint photon_rbo;
	
	GLint photon_MVP;
	GLint photon_MV;
	GLint photon_TEX;
	GLint photon_TF;
	GLint photon_BACKTEX;
	GLint photon_STEP;
	GLint photon_WIDTH;
	GLint photon_HEIGHT;
	GLint photon_INDIRECTILLTEX;
	GLint photon_COLORTEX;
	GLint photon_DIRECTILLTEX;


	//tramsform function parameter loc
	GLint MIN;
	GLint MAX;

	//transform function parameter
	float Min;
    float Max;
	int Step;

	int gradientStep;
	GLint GradientStep;
	
	float rotXOld;
	float rotYOld;

	//the quantity of every gray level in the texture
	int* grayCount;
	//count the grayCount
	void getGrayCount();
    //the h,w,d of volume tex
	GLint TexH;
	GLint TexW;
	GLint TexD;

	// phong - light model
	M3DVector3f ambient;
	M3DVector3f diffuse;
	M3DVector3f specular;
	M3DVector3f lightPosition;

	GLint Ambient;
	GLint Diffuse;
	GLint Specular;
	GLint LightPosition;

	//turn on the light
	int light;
	GLint Light;

	//CUDA LIGHT POSITION
	GLMatrixStack cudaLightStack;

	//surface shading parameter
	float surfaceShadingParameter;
	GLint SSP;


public:

	//read raw data
	void readRawFile(char *File);
	void readUltrRawFile(const char *File);
    void readCTRawFile(const char *File,int width,int height,int depth);
	//set oneDimon func
	void set1DFunc(float _Min,float _Max){Min = _Min;Max = _Max;}
	//set sample step
	void setSampleStep(int _Step){Step = _Step;}
	//set gradient step
	void setGradientStep(int _gradientStep){gradientStep = _gradientStep;}

	//set Ambient Occlusion step and count
	int ambientOcclusionStep;
	int ambientOcclusionCount;
	int ambientOcclusionRays;
	void setAmbientOcclusionStep(int _ambientOcculsionStep){ ambientOcclusionStep = _ambientOcculsionStep; this ->cudaAOParaChange();
	}
	void setAmbientOcclusionCount(int _ambientOcclusionCount){ ambientOcclusionCount = _ambientOcclusionCount; this ->cudaAOParaChange();
	}
	void setAmbientOcclusionRays(int _ambientOcclusionRays){ ambientOcclusionRays = _ambientOcclusionRays;this ->cudaAOParaChange();
	}




	//transform function texture;
	GLubyte* tfData;
	bool loadTFTex();
	//color mapping texture;
	GLubyte* colorData;
	bool loadColorTex();
	GLuint ColorTex;
	GLint COLORTEX;


	bool TFChange;
	bool LPChange;
	//useTF colors 
	GLint USETFCOLORS;
	GLint photons_USETFCOLORS;
	bool useTFColors;

	//photon number;
	unsigned int photonNumber;
    //HDR is on/off
    GLint HDRon;
	bool hdrOn;
	//HDR exposure parameter
	GLint EXPOSURE;
	float exposure;
	//Photon HDR exposure parameter
	GLint PHOTONEXPOSURE;
	float photonExposure;
	//Gamma correction
	GLint GAMMACORRECTION;
	float gammaCorrection;

	//light attenuation
	GLint KL;
	float kl;
	//color Box
	GLint COLORBOX;
	GLint PHOTON_COLORBOX;
	float colorBox;
private:

	
	//tf Texture
	GLuint TFTex;
	GLint TF;

	//gradient Texture
	GLuint GradientTex;
	GLint GTEX;


	
   //Volume Texture
	GLubyte* data;
	unsigned int dataSize;

	//	GLint Tex;
	GLuint TexObj;
	//mouse event
	int mouseOldX;
	int mouseOldY;

	

	float scale;
	
	//query FPS
	GLuint queryFPS;
	unsigned int fps;

	//for scale the image
	bool leftMouse;
	bool rightMouse;

	//use to produce the global texture
	GLuint DirectIllTexPBO;
    GLuint InDirectIllTexPBO;

	//used to produce the photons map
	GLuint photonsPBO;
	void* photons;


	GLuint DirectIllTex;
	GLint DIRECTILLTEX;
	GLuint InDirectIllTex;
	GLint INDIRECTILLTEX;
	//Illumination volume size
	int IllVolumeWidth;
	int IllVolumeHeight;
	int IllVolumeDepth;
	int IllVolumeType;
	unsigned int IllVolumeSize;
	unsigned int IllVolumeSizeOfByte;

	//use to produce the AO texture;
	GLuint AOTexPBO;
    //ambient occulation texture;
	bool loadAOTex();
	GLuint AOTex;
	GLint AOTEX;



	//CUDA VOlUME DATA
	cudaArray *cuArray;
	cudaArray *tfArray;
	cudaArray *surfaceArray;
	cudaArray *surfaceArray2;
	int surfaceSize[2];

	cudaGraphicsResource *resource;
	cudaGraphicsResource *inResource;
	cudaGraphicsResource *photonResource;
	cudaGraphicsResource *aoResource;

	//alpha volume used for global illumination calculate
	M3DVector3f lightPositionChange;

	//clear the pbo of photon map
	void *dataTemp;

	//photon size
	unsigned int photonSize;


protected:

	void initializeGL();
	void paintGL();
	void resizeGL(int width,int height);
   
	void makeCube();

	bool load3DTex();
	bool loadGradientTex();

	//initial ultr3D
	void initialUltr3DData();
	//delete ultr3D
	void deleteUltr3DData();


	void mousePressEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void closeEvent(QCloseEvent *event);
	//void keyPressEvent(QKeyEvent *e);

	//produce global illuminaton
	void InitGetGlobalIllum();

	//CUDA LIGHT CHANGE
	void cudaLightChange();
	//CUDA VECTOR CHANGE
	void cudaVertexChange();
	//CUDA TF CHANGE
	void cudaTFChange();
	//CUDA AO PARA CHANGE;
	void cudaAOParaChange();
	//get Ambient Occlusion Tex
	void getAOTex(float*c);
signals:
	void rotate(float,float);
	void timeStart(GLuint);
//CUDA FUNCTION
private:
   //update the texture data
   void updateCudaTranData(void* tfdata,int offset = 0,int length = 256);

   //set the light position
   void calculateDirectI(float*c);

   //cuda run the indirect illumination
   void calculateIndirectI(unsigned int count,float*c);
   
   //cuda run to produce the photon map
   void calculatePhoton(float*c);

   //cuda run to calculate ambient occulation
   void calculateAO(float*c);

   
	
};

#endif 
