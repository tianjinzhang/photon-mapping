#include "ultr3d.h"
//CUDA FUNCTION///////////////////////
cudaArray* InitialCudaData(void*data,unsigned int w,unsigned int h,unsigned int d);
cudaArray* InitialCudaTranData(void* tfdata);
void setLightPosition(float* position);
void setSizeParameters(int w,int h,int d);
void setPhotonParameters(float*_photon_dis_step);
void setVertextTran(float* transMatrix);
void setInvertVertextTran(float* transMatrix);
void setAOParameters(int count,int step,int Rays);

void setLightPositionAfter(float* position);
//initial light surface
void initialLightSurface(int width,int height,int bits,cudaArray * surfaceArray,cudaArray * surfaceArray2);
void render_Kernel_DI(dim3 grid,dim3 block,unsigned char * pbo,float *lightPosition,int * surfaceSize,float*c);

void render_Kernel_InDI(unsigned int count,unsigned char* pbo,float*c);
void render_Kernel_PhotonMap(unsigned int with,unsigned int heigh,unsigned char* pbo,unsigned char* photons,float*c);
void render_kernel_AOMap(dim3 grid,dim3 block,unsigned char*pbo,float*c);
//////////////////////////////////////

#define IllVolDataFormat GL_UNSIGNED_BYTE 
const float SCALEIllVOLUME = 1;
const float photonVolumeScale = 1;
ultr3D::ultr3D(const char* File,QWidget *parent, Qt::WFlags flags)
: QGLWidget(parent)
{
	//set windows
	 QIcon icon("/faicon.png");
	 setWindowIcon(icon);
	 setWindowTitle("ultr3d");
     setEnabled(true);
     setGeometry(QRect(10, 10, 600, 600));
     setFocusPolicy(Qt::ClickFocus);
	 this ->initialUltr3DData(); 
	
	 //load data
 	 this ->readUltrRawFile(File);
  
}
ultr3D::ultr3D(const char* File,int width,int height,int depth,QWidget *parent, Qt::WFlags flags)
{
	//set windows
	 QIcon icon("/faicon.png");
	 setWindowIcon(icon);
	 setObjectName(QString::fromUtf8("ultr3d"));
     setEnabled(true);
     setGeometry(QRect(10, 10, 600, 600));
     setFocusPolicy(Qt::ClickFocus);
	
	 this ->initialUltr3DData(); 
	
	 //load data
	 this ->readCTRawFile(File,width,height,depth);
}
ultr3D::~ultr3D()
{	
	this ->deleteUltr3DData();
	
}
/*******************************************************/
//initial Ultr3d Data
/********************************************************/
void ultr3D::initialUltr3DData()
{
	//initialize queryFPS
	this ->rotXOld = 0.0f;
	this ->rotYOld = 0.0f;

	this ->leftMouse = false;
	this ->rightMouse = false;

	this ->data = NULL;
	this ->tfData = NULL;
	this ->colorData = NULL;
	this ->TFTex = 0;
	this ->ColorTex = 0;
	this ->AOTexPBO = 0;
	this ->AOTex = 0;
	this ->DirectIllTexPBO = 0;
	this ->InDirectIllTexPBO = 0;
	this ->DirectIllTex = 0;
	this ->InDirectIllTex = 0;
	this ->cuArray = NULL;
	this ->tfArray = NULL;

	this ->surfaceArray = NULL;
	this ->surfaceArray2 = NULL;


	//Illumination Volume size
	this ->IllVolumeWidth = 0;
	this ->IllVolumeHeight = 0;
	this ->IllVolumeDepth = 0;
	this ->IllVolumeSize = 0;
	this ->IllVolumeSizeOfByte = 0;

	if(IllVolDataFormat ==   GL_UNSIGNED_BYTE )
		this ->IllVolumeType = 1;
	if(IllVolDataFormat ==  GL_UNSIGNED_SHORT )
	    this ->IllVolumeType = 2;

	this ->dataTemp = NULL;
	this ->photons = NULL;
	
	//CUDA change which 0 is not change 1 is light change,2 is tf change;
	this ->TFChange = false;
	this ->LPChange = false;

	this ->scale = 0.0;
	this ->light = 1;
	this ->dataSize = 0;
	this ->surfaceShadingParameter = 1.0;

	
	//this->set1DFunc(0.35f,0.75f);
	this->setSampleStep(1000);
	this->setGradientStep(1000);

	//set ambient occlusion parameters
	this ->setAmbientOcclusionCount(5);
	this ->setAmbientOcclusionStep(1);
	this ->setAmbientOcclusionRays(8);

	//photon number
	this ->photonNumber = 4000000;
	//HDR on
	this ->hdrOn = true;

	//use tf colors
	this ->useTFColors = false;
	//HDR exposure
	this ->exposure = 2.5;
	this ->photonExposure = 1.0;
	this ->gammaCorrection = 1.6;
	//light attenuation
	this ->kl = 0.0;
	//color box
	this ->colorBox = 0.0;

	//initiaize the light
	m3dLoadVector3(ambient,0.0,0.0,0.0);
	m3dLoadVector3(diffuse,1.0,1.0,1.0);
	m3dLoadVector3(specular,0.0,0.0,0.0);

	m3dLoadVector3(lightPosition,1.0,1.0,1.0);
	m3dNormalizeVector3(lightPosition);
	m3dScaleVector3(lightPosition,2.5);


	//QVector initialize to 0
    this ->grayCount = (int*)malloc(256*sizeof(int));
	memset(this ->grayCount, 0, sizeof(int)*256);
	//qDebug() <<" "<<grayCount[255];
	//load TF
	this ->tfData = (GLubyte*)malloc(256 * 4);
  
}
/*******************************************************/
//delete Ultr3d Data
/********************************************************/
void ultr3D::deleteUltr3DData()
{

	if(0 != this ->TexObj)
	{
		glDeleteTextures(1,&this ->TexObj);
		this ->TexObj = 0;
	}
	if(0 != this ->GradientTex)
	{
		glDeleteTextures(1,&this ->GradientTex);
		this ->GradientTex = 0;
	}
	if(0 != this ->ColorTex)
	{
		glDeleteTextures(1,&this ->ColorTex);
		this ->ColorTex = 0;
	}
	if(0 != this ->AOTex)
	{
		glDeleteTextures(1,&this ->AOTex);
		this ->AOTex = 0;
	}
	if(0 != this ->AOTexPBO)
	{
		glDeleteTextures(1,&this ->AOTexPBO);
		this ->AOTexPBO = 0;
	}
	if(0 != this ->TFTex)
	{
		glDeleteTextures(1,&this ->TFTex);
		this ->TFTex = 0;
	}
	if(0 != this ->DirectIllTexPBO)
	{
		glDeleteBuffers(1,&this ->DirectIllTexPBO);
		this ->DirectIllTexPBO = 0;
	}
	if(0 != this ->InDirectIllTexPBO)
	{
		glDeleteBuffers(1,&this ->InDirectIllTexPBO);
		this ->InDirectIllTexPBO = 0;
	}
	if(0 != this ->photonsPBO)
	{
		glDeleteBuffers(1,&this ->photonsPBO);
		this ->photonsPBO = 0;
	}
	if(0 != this ->DirectIllTex)
	{
		glDeleteTextures(1,&this ->DirectIllTex);
		this ->DirectIllTex = 0;
	}
	if(0 != this ->InDirectIllTex)
	{
		glDeleteTextures(1,&this ->InDirectIllTex);
		this ->InDirectIllTex = 0;
	}
	if(0 != this ->texColorbuffer)
	{
		glDeleteTextures(1,&this ->texColorbuffer);
		this ->texColorbuffer = 0;
	}
	if(0 != this ->photon_texBuffer)
	{
		glDeleteTextures(1,&this ->photon_texBuffer);
		this ->photon_texBuffer = 0;
	}
	if(0 != this ->ultr)
	{
		glDeleteProgram(this ->ultr);
		this ->ultr = 0;
	}
	if(0 != this ->getBack)
	{
		glDeleteProgram(this ->getBack);
		this ->getBack = 0;
	}
	if(0 != this ->photonShader)
	{
		glDeleteProgram(this ->photonShader);
		this ->photonShader = 0;
	}
	if(0 != this ->framebuffer)
	{
		glDeleteFramebuffers(1,&this ->framebuffer);
		this ->framebuffer = 0;
	}
	if(0 != this ->photon_framebuffer)
	{
		glDeleteFramebuffers(1,&this ->framebuffer);
		this ->photon_framebuffer = 0;
	}
	if(0 != this ->rbo)
	{
		glDeleteRenderbuffers(1,&this ->rbo);
		this ->rbo = 0;
	}
	if(0 != this ->photon_rbo)
	{
		glDeleteRenderbuffers(1,&this ->photon_rbo);
		this ->photon_rbo = 0;
	}
	if(0 != this ->queryFPS)
	{
		glDeleteQueries(1,&this ->queryFPS);
		this ->queryFPS = 0;
	}

	if(NULL != this ->tfData)
	{
		free(this ->tfData);
		this ->tfData = NULL;

	}
	if(NULL != this ->data)
	{
		free(this ->data);
		this ->data = NULL;

	}
	if(NULL != this ->grayCount)
	{
		free(this ->grayCount);
		this ->grayCount = NULL;
	}

	if(NULL != this ->dataTemp);
	{
		free(this ->dataTemp);
		this ->dataTemp = NULL;
	}
    //FREE CUDA MEMORY AND EXIT
	if(NULL != this ->cuArray)
	{
		checkCudaErrors(cudaFreeArray(this ->cuArray));
		this ->cuArray = NULL;

	}
	if(NULL != this ->tfArray)
	{
		checkCudaErrors(cudaFreeArray(this ->tfArray));
		this ->tfArray = NULL;
	}
	if(NULL != this ->photons)
	{
		checkCudaErrors(cudaFree(this ->photons));
		this ->photons = NULL;
	}

	if(NULL != this ->surfaceArray)
	{
		checkCudaErrors(cudaFreeArray(this ->surfaceArray));
		this ->surfaceArray = NULL;
	}
	if(NULL != this ->surfaceArray2)
	{
		checkCudaErrors(cudaFreeArray(this ->surfaceArray2));
		this ->surfaceArray2 = NULL;
	}

	checkCudaErrors(cudaDeviceReset());
}
/*******************************************************/
//initializeGL opengl win
/********************************************************/
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
void ultr3D::initializeGL()
{
	GLenum err = glewInit();
	if(GLEW_OK != err)
	{

		qDebug() << "glewInit error...................."<< glewGetErrorString(err);
		return;

	}

	glGenQueries(1,&this ->queryFPS);

	
	//load ultr3d texture
	this ->load3DTex();
	//load Color Texture
	this ->loadColorTex();
	//load tf texture
    this ->loadTFTex();
	//load global texture
	this ->InitGetGlobalIllum();
	
/////////////////////////////////////////

	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);

	if(gltIsExtSupported("GL_EXT_texture_filter_anisotropic"))
	{
		GLfloat fLargest;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT,&fLargest);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAX_ANISOTROPY_EXT,fLargest);
		glTexParameterf(GL_TEXTURE_3D,GL_TEXTURE_MAX_ANISOTROPY_EXT,fLargest);

	}
	
	projection.SetOrthographic(-1.8f,1.8f,-1.8f,1.8f,-10.0f,10.0f);
	//projection.SetPerspective(40.0f,this ->width()/this ->height(),0.0f,15.0f);
	projectionStack.LoadMatrix(projection.GetProjectionMatrix());
	//odelviewStack.TranslateToWorld(0.0f,0.0f,-10.0f);
	mvpPipline.SetMatrixStacks(modelviewStack,projectionStack);
	makeCube();
    //getBackface///////////////////////////////////
	
	glGenFramebuffers(1, &framebuffer);
    glBindFramebuffer(GL_FRAMEBUFFER, framebuffer); 

    glGenTextures(1,&texColorbuffer);
	glBindTexture(GL_TEXTURE_2D,texColorbuffer);
	
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,this->width(),this->height(),0,GL_RGBA,GL_UNSIGNED_BYTE,NULL);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texColorbuffer, 0);

    
	 
    glGenRenderbuffers(1, &rbo);
    glBindRenderbuffer(GL_RENDERBUFFER, rbo); 
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, this->width(), this->height()); 
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rbo);
	
	gltCheckErrors();



	glBindFramebuffer(GL_FRAMEBUFFER,0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D,0);
	///////////////////////////////////////////////
	//photons map

	glGenFramebuffers(1, &(this ->photon_framebuffer));
	glBindFramebuffer(GL_FRAMEBUFFER, this ->photon_framebuffer); 

	glGenTextures(1,&(this ->photon_texBuffer));
	glBindTexture(GL_TEXTURE_2D,this ->photon_texBuffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
    glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,this->width(),this->height(),0,GL_RGBA,GL_UNSIGNED_BYTE,NULL);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, this ->photon_texBuffer, 0);

	glGenRenderbuffers(1, &(this ->photon_rbo));
	glBindRenderbuffer(GL_RENDERBUFFER, this ->photon_rbo); 
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, this->width(), this->height()); 
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, this ->photon_rbo);
	
	gltCheckErrors();

	glBindFramebuffer(GL_FRAMEBUFFER,0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D,0);
	///////////////////////////////////////////////
    this ->getBack = gltLoadShaderPairWithAttributes("./GLSL/getBackv.c","./GLSL/getBackf.c",2,0,"vVertex",1,"vColor");
	this ->getBackMVP = glGetUniformLocation(getBack,"mvp");
	//////////////////////////////////////////////
	this ->photonShader = gltLoadShaderPairWithAttributes("./GLSL/photonv.c","./GLSL/photonf.c",2,0,"vVertex",1,"vColor");
	this ->photon_MVP = glGetUniformLocation(photonShader,"mvp");
	this ->photon_MV = glGetUniformLocation(photonShader,"mv");
	this ->photon_TEX = glGetUniformLocation(photonShader,"tex");
	this ->photon_TF = glGetUniformLocation(photonShader,"tf");
	this ->photon_BACKTEX = glGetUniformLocation(photonShader,"backtex");
	this ->photon_STEP = glGetUniformLocation(photonShader,"step");
	this ->photon_WIDTH = glGetUniformLocation(photonShader,"width");
	this ->photon_HEIGHT = glGetUniformLocation(photonShader,"height");
	this ->photon_DIRECTILLTEX = glGetUniformLocation(photonShader,"directIllTex");
	this ->photon_INDIRECTILLTEX = glGetUniformLocation(photonShader,"inDirectIllTex");
	this ->photon_COLORTEX = glGetUniformLocation(photonShader,"colortex");
	this ->PHOTONEXPOSURE = glGetUniformLocation(photonShader,"exposure");
	this ->PHOTON_COLORBOX = glGetUniformLocation(photonShader,"colorBox");
	this ->photons_USETFCOLORS = glGetUniformLocation(photonShader,"useTFColors");


	//////////////////////////////////////////////
	this ->ultr = gltLoadShaderPairWithAttributes("./GLSL/ultr3Dv.c","./GLSL/ultr3Df.c",2, 0,"vVertex",1,"vColor");
    this ->MVP = glGetUniformLocation(ultr,"mvp");
	this ->MV = glGetUniformLocation(ultr,"mv");
	this ->TEX = glGetUniformLocation(ultr,"tex");
	this ->BACKTEX = glGetUniformLocation(ultr,"backtex");
	this ->MIN = glGetUniformLocation(ultr,"min");
	this ->MAX = glGetUniformLocation(ultr,"max");
	this ->STEP = glGetUniformLocation(ultr,"step");
	this ->WIDTH = glGetUniformLocation(ultr,"width");
	this ->HEIGHT = glGetUniformLocation(ultr,"height");
	this ->TF = glGetUniformLocation(ultr,"tf");
	//this ->GTEX = glGetUniformLocation(ultr,"gtex");
	this ->Ambient = glGetUniformLocation(ultr,"ambient");
	this ->Diffuse = glGetUniformLocation(ultr,"diffuse");
	this ->Specular = glGetUniformLocation(ultr,"specular");
	this ->LightPosition = glGetUniformLocation(ultr,"lightPosition");
	this ->Light = glGetUniformLocation(ultr,"light");
	this ->GradientStep = glGetUniformLocation(ultr,"gradientStep");
	this ->COLORTEX = glGetUniformLocation(ultr,"colortex");
	this ->AOTEX = glGetUniformLocation(ultr,"aotex");
	this ->DIRECTILLTEX = glGetUniformLocation(ultr,"directIllTex");
	this ->INDIRECTILLTEX = glGetUniformLocation(ultr,"inDirectIllTex");
	this ->SSP = glGetUniformLocation(ultr,"surfaceShadingParameter");
	this ->EXPOSURE = glGetUniformLocation(ultr,"exposure");
	this ->GAMMACORRECTION = glGetUniformLocation(ultr,"gammaCorrection");
	this ->KL = glGetUniformLocation(ultr,"KL");
	this ->COLORBOX = glGetUniformLocation(ultr,"colorBox");
	this ->HDRon = glGetUniformLocation(ultr,"hdrOn");
	this ->USETFCOLORS = glGetUniformLocation(ultr,"useTFColors");
}
////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/*****************************************************************************/
//resize opengl win ,every time,upadate(),first call this fun
/*****************************************************************************/
void ultr3D::resizeGL(int width,int height)
{

	if(0 == height)
	{
		height = 1;
	 }
	glViewport(0,0,width,height);

	
	glBindTexture(GL_TEXTURE_2D,texColorbuffer);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,this->width(),this->height(),0,GL_RGBA,GL_UNSIGNED_BYTE,NULL);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo); 
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT32, this->width(), this->height()); 


}
/**************************************************************************/
//paint the opengl win
/**************************************************************************/
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
void ultr3D::paintGL()
{	 
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_3D,this ->TexObj);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D,this ->texColorbuffer);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_1D,this ->TFTex);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D,this ->ColorTex);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_3D,this ->AOTex);
	glActiveTexture(GL_TEXTURE5);
	glBindTexture(GL_TEXTURE_3D,this ->DirectIllTex);
	glActiveTexture(GL_TEXTURE6);
	glBindTexture(GL_TEXTURE_3D,this ->InDirectIllTex);
	glActiveTexture(GL_TEXTURE7);
	glBindTexture(GL_TEXTURE_2D,this ->photon_texBuffer);

	//set time start for FPS
	glBeginQuery(GL_TIME_ELAPSED,this ->queryFPS);

	//Change CUDA 
	if(this ->LPChange)
	{
		this ->cudaLightChange();
		this ->cudaVertexChange();
		this ->LPChange = false;
	}
	if(this ->TFChange)
	{
		this ->cudaTFChange();
		this ->TFChange = false;
	}
	
	glBindBuffer(GL_PIXEL_PACK_BUFFER,this ->InDirectIllTexPBO);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBufferData(GL_PIXEL_PACK_BUFFER,this ->dataSize,dataTemp,GL_DYNAMIC_DRAW);
    glBindBuffer(GL_PIXEL_PACK_BUFFER,0);

	//CUDA CALCULATE THE GLOBAL LIGHT/////////////////////////////

	float*c = (float*)malloc(sizeof(float)*10);
    c[0] = 0;c[1] = 0;c[2] = 0;
	//direct illumination
	if(2 == this ->light || 4 == this ->light || 5 == this ->light || 7 == this ->light || 3 == this ->light)
	{
        this ->calculateDirectI(c);
	}
    //indirect illumination
	if(3 == this ->light || 4 == this ->light || 7 == this ->light)
	{
		this ->calculateIndirectI(this ->photonNumber,c);
	}

	if(6 == this ->light || 8 == this ->light)
	{
		this ->getAOTex(c);
	}
	//qDebug()<<c[0] <<c[1] <<c[2]<<"..........................";
	free(c);
	

	
	///////////////////////////////////////////////////////////////
	//update PBO and direction illumination texture
    if(2 == this ->light || 4 == this ->light || 5 == this ->light || 7 == this ->light)
	{
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,this ->DirectIllTexPBO);
		glActiveTexture(GL_TEXTURE5);
		glBindTexture(GL_TEXTURE_3D,this ->DirectIllTex);
		glTexImage3D(GL_TEXTURE_3D,0,GL_ALPHA,this ->IllVolumeWidth,this ->IllVolumeHeight,this ->IllVolumeDepth,0,GL_ALPHA,IllVolDataFormat,NULL);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,0);
	}
	//update PBO and indirection illumination texture
	if(3 == this ->light || 4 == this ->light || 7 == this ->light)
	{
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,this ->InDirectIllTexPBO);
		glActiveTexture(GL_TEXTURE6);
		glBindTexture(GL_TEXTURE_3D,this ->InDirectIllTex);
		glTexImage3D(GL_TEXTURE_3D,0,GL_ALPHA,this ->TexW * photonVolumeScale,this ->TexH * photonVolumeScale,this ->TexD * photonVolumeScale,0,GL_ALPHA,GL_UNSIGNED_BYTE,NULL);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,0);
	}

    //render the back of cube
	glBindFramebuffer(GL_FRAMEBUFFER,framebuffer);
	glCullFace(GL_FRONT);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    glUseProgram(getBack);
	glUniformMatrix4fv(getBackMVP,1,GL_FALSE,mvpPipline.GetModelViewProjectionMatrix());
	cube.Draw();
	glBindFramebuffer(GL_FRAMEBUFFER,0);

	glCullFace(GL_BACK);
    //render the photon map
	if(3 == this ->light || 4 == this ->light || 7 == this -> light)
	{
		glBindFramebuffer(GL_FRAMEBUFFER,this ->photon_framebuffer);
		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glUseProgram(this ->photonShader);
		glUniformMatrix4fv(this ->photon_MVP,1,GL_FALSE,mvpPipline.GetModelViewProjectionMatrix());
		glUniformMatrix4fv(this ->photon_MV,1,GL_FALSE,mvpPipline.GetModelViewMatrix());
		glUniform1i(this ->photon_TEX,0);
		glUniform1i(this ->photon_TF,2);
		glUniform1i(this ->photon_BACKTEX,1);
		glUniform1i(this ->photon_WIDTH,this->width());
		glUniform1i(this ->photon_HEIGHT,this->height());
		glUniform1i(this ->photon_STEP,Step);
		glUniform1i(this ->photon_DIRECTILLTEX,5);
		glUniform1i(this ->photon_INDIRECTILLTEX,6);
		glUniform1i(this ->photon_COLORTEX,3);
		glUniform1f(this ->PHOTONEXPOSURE,this ->photonExposure);
		glUniform1f(this ->PHOTON_COLORBOX ,this ->colorBox);
		glUniform1i(this ->photons_USETFCOLORS,this ->useTFColors);
		
		cube.Draw();
	
		glBindBuffer(GL_PIXEL_PACK_BUFFER,this ->photonsPBO);
		glReadBuffer(GL_COLOR_ATTACHMENT0);
		glPixelStorei(GL_PACK_ALIGNMENT, 1);
		glReadPixels(0, 0, this ->width(), this ->height(), GL_RGBA, GL_UNSIGNED_BYTE, 0);   
		glBindFramebuffer(GL_FRAMEBUFFER,0);

		c = (float*)malloc(sizeof(float)*10);
		c[0] = 0;c[1] = 0;c[2] = 0;
		calculatePhoton(c);
		//qDebug()<<c[0] <<c[1] <<c[2]<<"..........................";
		free(c);
		//update PBO and photon map texture
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,this ->photonsPBO);
		glActiveTexture(GL_TEXTURE7);
		glBindTexture(GL_TEXTURE_2D,this ->photon_texBuffer);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,this->width(),this->height(),0,GL_RGBA,GL_UNSIGNED_BYTE,NULL);
		glBindBuffer(GL_PIXEL_UNPACK_BUFFER,0);
	}
	//render
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glUseProgram(ultr);
	glUniformMatrix4fv(MVP,1,GL_FALSE,mvpPipline.GetModelViewProjectionMatrix());
	glUniformMatrix4fv(MV,1,GL_FALSE,mvpPipline.GetModelViewMatrix());
	glUniform1i(this ->TEX,0);
	glUniform1i(this ->BACKTEX,1);
	glUniform1i(this ->WIDTH,this->width());
	glUniform1i(this ->HEIGHT,this->height());
	glUniform1f(this ->MIN,Min);
	glUniform1f(this ->MAX,Max);
	glUniform1i(this ->STEP,Step);
	glUniform1i(this ->TF,2);
	//glUniform1i(GTEX,3);
	glUniform3fv(this ->Ambient,1,ambient);
	glUniform3fv(this ->Diffuse,1,diffuse);
	glUniform3fv(this ->Specular,1,specular);
	glUniform3fv(this ->LightPosition,1,lightPosition);
	glUniform1i(this ->Light,light);
	glUniform1i(this ->GradientStep,gradientStep);
	glUniform1i(this ->COLORTEX,3);
	glUniform1i(this ->AOTEX,4);
	glUniform1i(this ->DIRECTILLTEX,5);
	glUniform1i(this ->INDIRECTILLTEX,7);
	glUniform1f(this ->SSP,this ->surfaceShadingParameter);
	glUniform1f(this ->EXPOSURE,this ->exposure);
	glUniform1f(this ->GAMMACORRECTION,this ->gammaCorrection);
	glUniform1f(this ->KL,this ->kl);
	glUniform1f(this ->COLORBOX ,this ->colorBox);
	glUniform1i(this ->HDRon,this ->hdrOn);
	glUniform1i(this ->USETFCOLORS,this ->useTFColors);
	cube.Draw();

	//set the time end of Rendering and calculate the FPS
	glEndQuery(GL_TIME_ELAPSED);
	glGetQueryObjectuiv(this ->queryFPS,GL_QUERY_RESULT,&this ->fps);
	emit this ->timeStart(1000000000.0/this ->fps);

}
////////////////////////////////////////////////////////////////////////////////	
/////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
/**************************************************/
//read .raw file
/*************************************************/
//read ultr file
void ultr3D::readUltrRawFile(const char *File )
{

	FILE *fp;
	fp= fopen(File,"rb");
	if(NULL == fp)
	{
		qDebug() << "....................................................read ultrfile error";
		
		return;
	}
	qDebug() <<"file :"<<File;
	fread(&this ->TexW,sizeof(int),1,fp);
	fread(&this ->TexH,sizeof(int),1,fp);
	fread(&this ->TexD,sizeof(int),1,fp);

	this ->dataSize = this ->TexW * this ->TexH * this ->TexD;
    qDebug()<<"w:"<<TexW<<"h:"<<TexH<<"d:"<<TexD;
	data = (GLubyte*)malloc(this ->dataSize);
    fread(data,TexW*TexH*TexD,1,fp);
	fclose(fp);
	fp = NULL;

	//get gray count//////////////////////////////
	getGrayCount();

	//set the illumination volume size
	this ->IllVolumeWidth = this ->TexW * SCALEIllVOLUME;
	this ->IllVolumeHeight = this ->TexH * SCALEIllVOLUME;
	this ->IllVolumeDepth = this ->TexD * SCALEIllVOLUME;
	//this ->IllVolumeType = 1;//1 for unsigne char ,2 for ...
	this ->IllVolumeSize = this ->IllVolumeDepth * this ->IllVolumeHeight * this ->IllVolumeWidth;
	this ->IllVolumeSizeOfByte = this ->IllVolumeSize * this ->IllVolumeType;



}
//read CT file
void  ultr3D::readCTRawFile(const char *File,int width,int height,int depth)
{
	FILE *fp;
	fp= fopen(File,"rb");
	if(NULL == fp)
	{
		qDebug() << "....................................................read CTfile error";
		return;
	}
	
	this ->TexW = width;
	this ->TexH = height;
	this ->TexD = depth;

	this ->dataSize = this ->TexW * this ->TexH * this ->TexD;

	data = (GLubyte*)malloc(this ->dataSize);
    fread(data,TexW*TexH*TexD,1,fp);
	fclose(fp);
	fp = NULL;


	//get gray count//////////////////////////////
	getGrayCount();

	//set the illumination volume size
	this ->IllVolumeWidth = this ->TexW * SCALEIllVOLUME;
	this ->IllVolumeHeight = this ->TexH * SCALEIllVOLUME;
	this ->IllVolumeDepth = this ->TexD * SCALEIllVOLUME;
	//this ->IllVolumeType = 1;//1 for unsigne char ,2 for ...
	this ->IllVolumeSize = this ->IllVolumeDepth * this ->IllVolumeHeight * this ->IllVolumeWidth;
	this ->IllVolumeSizeOfByte = this ->IllVolumeSize  * this ->IllVolumeType;


}
/************************************************/
//load3DTexture
/************************************************/
bool ultr3D::load3DTex()
{

	
	glGenTextures(1,&TexObj);
	glBindTexture(GL_TEXTURE_3D,TexObj);
	
	glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_WRAP_R,GL_CLAMP);

	glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);


	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage3D(GL_TEXTURE_3D,0,GL_ALPHA,TexW,TexH,TexD,0,GL_ALPHA,GL_UNSIGNED_BYTE,data);

	
	return true;
}

/*************************************************/
//mouseEvent , keyEvent and closeEvent
/*************************************************/
void ultr3D::mousePressEvent(QMouseEvent *e)
{
	mouseOldX = e->x();
	mouseOldY = e->y();
	if(e ->button() == Qt::LeftButton)
	{
		this ->leftMouse = true;
		this ->rightMouse = false;
	}else if(e ->button() == Qt::RightButton)
	{
		this ->leftMouse = false;
		this ->rightMouse = true;
	}
	
}
void ultr3D::closeEvent(QCloseEvent *event)
{
	this ->hide();
}
void ultr3D::mouseMoveEvent(QMouseEvent *e)
{
	
	int deltax =  mouseOldX - e->x();
	int deltay =  mouseOldY - e->y();
	if(true == this ->leftMouse)
	{
		//	qDebug() <<deltax<<".........."<<deltay;

		float yangle = 11*deltax/(this -> width());
		float xangle = 11*deltay/(this -> height());

		modelviewStack.RotateToWorld(xangle,-1.0f,0.0f,0.0f);
		modelviewStack.RotateToWorld(yangle,0.0f,-1.0f,0.0f);
		this ->cudaLightStack.RotateToWorldInvert(xangle,-1.0f,0.0f,0.0f);
		this ->cudaLightStack.RotateToWorldInvert(yangle,0.0f,-1.0f,0.0f);
		
		this ->LPChange = true;
		emit rotate(xangle,yangle);
	}else if(true == this ->rightMouse)
	{
		if(deltay > 0)
		{
			modelviewStack.ScaleToWorld(1.01f,1.01f,1.01f);
		}else
		{
			modelviewStack.ScaleToWorld(1/1.01f,1/1.01f,1/1.01f);
		}
		updateGL();
	}

}
/*
void ultr3D::keyPressEvent(QKeyEvent *e)
{
	switch(e ->key())
	{
	
	case Qt::Key_Q:
		
		break;
	case Qt::Key_W:
		
		break;
	}
}
*/
/**************************************************/
//make a cube
/**************************************************/
void ultr3D::makeCube()
{	
	cube.Begin(GL_QUADS,24,0);
	    cube.Color4f(0.0f,1.0f,0.0f,1.0f);
	    cube.Vertex3f(-1.0f,1.0f,1.0f);		
        cube.Color4f(0.0f,0.0f,0.0f,1.0f);
		cube.Vertex3f(-1.0f,-1.0f,1.0f);
        cube.Color4f(1.0f,0.0f,0.0f,1.0f);
		cube.Vertex3f(1.0f,-1.0f,1.0f);	
        cube.Color4f(1.0f,1.0f,0.0f,1.0f);
        cube.Vertex3f(1.0f,1.0f,1.0f);
/////////////////////////////////////////////////////
        cube.Color4f(1.0f,1.0f,0.0f,1.0f);
		cube.Vertex3f(1.0f,1.0f,1.0f);	
        cube.Color4f(1.0f,0.0f,0.0f,1.0f);
		cube.Vertex3f(1.0f,-1.0f,1.0f);
        cube.Color4f(1.0f,0.0f,1.0f,1.0f);
		cube.Vertex3f(1.0f,-1.0f,-1.0f);
        cube.Color4f(1.0f,1.0f,1.0f,1.0f);
		cube.Vertex3f(1.0f,1.0f,-1.0f);		
/////////////////////////////////////////////////////		
		cube.Color4f(1.0f,1.0f,1.0f,1.0f);
		cube.Vertex3f(1.0f,1.0f,-1.0f);		
        cube.Color4f(1.0f,0.0f,1.0f,1.0f);
		cube.Vertex3f(1.0f,-1.0f,-1.0f);	
        cube.Color4f(0.0f,0.0f,1.0f,1.0f);
		cube.Vertex3f(-1.0f,-1.0f,-1.0f);		
        cube.Color4f(0.0f,1.0f,1.0f,1.0f);
		cube.Vertex3f(-1.0f,1.0f,-1.0f);		
////////////////////////////////////////////////////
        cube.Color4f(0.0f,1.0f,1.0f,1.0f);
		cube.Vertex3f(-1.0f,1.0f,-1.0f);	
        cube.Color4f(0.0f,0.0f,1.0f,1.0f);
		cube.Vertex3f(-1.0f,-1.0f,-1.0f);
        cube.Color4f(0.0f,0.0f,0.0f,1.0f);
		cube.Vertex3f(-1.0f,-1.0f,1.0f);
        cube.Color4f(0.0f,1.0f,0.0f,1.0f);
		cube.Vertex3f(-1.0f,1.0f,1.0f);
/////////////////////////////////////////////////////
        cube.Color4f(0.0f,1.0f,1.0f,1.0f);
		cube.Vertex3f(-1.0f,1.0f,-1.0f);
        cube.Color4f(0.0f,1.0f,0.0f,1.0f);
		cube.Vertex3f(-1.0f,1.0f,1.0f);
        cube.Color4f(1.0f,1.0f,0.0f,1.0f);
		cube.Vertex3f(1.0f,1.0f,1.0f);
        cube.Color4f(1.0f,1.0f,1.0f,1.0f);
		cube.Vertex3f(1.0f,1.0f,-1.0f);	
/////////////////////////////////////////////////////
        cube.Color4f(0.0f,0.0f,0.0f,1.0f);
		cube.Vertex3f(-1.0f,-1.0f,1.0f);
        cube.Color4f(0.0f,0.0f,1.0f,1.0f);
		cube.Vertex3f(-1.0f,-1.0f,-1.0f);
        cube.Color4f(1.0f,0.0f,1.0f,1.0f);
		cube.Vertex3f(1.0f,-1.0f,-1.0f);
        cube.Color4f(1.0f,0.0f,0.0f,1.0f);
		cube.Vertex3f(1.0f,-1.0f,1.0f);	
////////////////////////////////////////////////////
	cube.End();
}
/************************************************************/
//get graycount in the texture
/***********************************************************/
void ultr3D::getGrayCount()
{
	for(int i = 0; i < TexH*TexW*TexD; i++)
	{	
		grayCount[((GLubyte*)data)[i]]++;
	}


}
/**************************************************/
//load transform function texture
/**************************************************/
bool ultr3D::loadTFTex()
{



    if( 0 == this ->TFTex)
    {
		glGenTextures(1,&this ->TFTex);
		glBindTexture(GL_TEXTURE_1D,this ->TFTex);

		glTexParameteri(GL_TEXTURE_1D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_1D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_1D,GL_TEXTURE_WRAP_S,GL_CLAMP);
		glPixelStorei(GL_UNPACK_ALIGNMENT,1);
		glTexImage1D(GL_TEXTURE_1D,0,GL_RGBA,256,0,GL_RGBA,GL_UNSIGNED_BYTE,this ->tfData);
		
	}else
	{
		glBindTexture(GL_TEXTURE_1D,this ->TFTex);
		glTexImage1D(GL_TEXTURE_1D,0,GL_RGBA,256,0,GL_RGBA,GL_UNSIGNED_BYTE,this ->tfData);

		this ->TFChange = true;

	}
	return true;
}


/**************************************************/
//load gradient texture
/**************************************************/
bool ultr3D::loadGradientTex()
{
	return true;
}
/**************************************************/
//load color map
/**************************************************/
bool ultr3D::loadColorTex()
{

	QImage color("color.png");
	if(color.isNull())
	{
		qDebug() <<"that have a error in load color texture";
		return false;

	}
	int height = color.height();
	int width = color.width();
	
	//colorData = (GLubyte*)malloc(height * width * 4);
	colorData = (GLubyte*)color.bits();

	if(0 == this ->ColorTex)
	{
		glGenTextures(1,&this ->ColorTex);
		glBindTexture(GL_TEXTURE_2D,this ->ColorTex);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);
		glPixelStorei(GL_UNPACK_ALIGNMENT,1);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,colorData);

		

	}else
	{
		glBindTexture(GL_TEXTURE_2D,this ->ColorTex);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,colorData);
	}

	return true;
}
/**************************************************/
//get ambient occulsion texture
/**************************************************/
void ultr3D::getAOTex(float*c)
{


	this ->calculateAO(c);

	glBindBuffer(GL_PIXEL_UNPACK_BUFFER,this ->AOTexPBO);
	glActiveTexture(GL_TEXTURE4);
	glBindTexture(GL_TEXTURE_3D,this ->AOTex);
	glTexImage3D(GL_TEXTURE_3D,0,GL_ALPHA,this ->TexW,this ->TexH,this ->TexD,0,GL_ALPHA,GL_UNSIGNED_BYTE,NULL);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER,0);

}
/**************************************************/
//Initialize PBO use cuda to produce the direct illumination and indirect illumination
/**************************************************/
void ultr3D::InitGetGlobalIllum()
{
	dataTemp = (void*)malloc(this ->dataSize);
	memset(dataTemp,0,this ->dataSize);
	//direct illumination Texture;
	glGenBuffers(1,&this ->DirectIllTexPBO);
	glBindBuffer(GL_PIXEL_PACK_BUFFER,this ->DirectIllTexPBO);
	glBufferData(GL_PIXEL_PACK_BUFFER,this ->IllVolumeSizeOfByte,NULL,GL_DYNAMIC_DRAW);
    glBindBuffer(GL_PIXEL_PACK_BUFFER,0);

	//direct illumination Texture
	glGenTextures(1,&this ->DirectIllTex);
	glBindTexture(GL_TEXTURE_3D,this ->DirectIllTex);
	glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_WRAP_R,GL_CLAMP);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage3D(GL_TEXTURE_3D,0,GL_ALPHA,this ->IllVolumeWidth,this ->IllVolumeHeight,this ->IllVolumeDepth,0,GL_ALPHA,IllVolDataFormat,NULL);


	glBindTexture(GL_TEXTURE_3D,0);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER,0);
    //////////////////////////////////////////////////////////////////////////
	//indirect illumination PBO
	glGenBuffers(1,&this ->InDirectIllTexPBO);
	glBindBuffer(GL_PIXEL_PACK_BUFFER,this ->InDirectIllTexPBO);
	glBufferData(GL_PIXEL_PACK_BUFFER,this ->dataSize,dataTemp,GL_DYNAMIC_DRAW);
    glBindBuffer(GL_PIXEL_PACK_BUFFER,0);
	//indirect illuminaton Texture
	glGenTextures(1,&this ->InDirectIllTex);
	glBindTexture(GL_TEXTURE_3D,this ->InDirectIllTex);
	glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_WRAP_R,GL_CLAMP);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage3D(GL_TEXTURE_3D,0,GL_ALPHA,this ->TexW* photonVolumeScale,this ->TexH* photonVolumeScale,this ->TexD * photonVolumeScale,0,GL_ALPHA,GL_UNSIGNED_BYTE,NULL);

	glBindTexture(GL_TEXTURE_3D,0);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER,0);
	//////////////////////////////////////////////////////////////////////////
    //ambient illumination PBO
	glGenBuffers(1,&this ->AOTexPBO);
	glBindBuffer(GL_PIXEL_PACK_BUFFER,this ->AOTexPBO);
	glBufferData(GL_PIXEL_PACK_BUFFER,this ->dataSize,dataTemp,GL_DYNAMIC_DRAW);
	glBindBuffer(GL_PIXEL_PACK_BUFFER,0);
	//ambient illumination Texture
	glGenTextures(1,&this ->AOTex);
	glBindTexture(GL_TEXTURE_3D,this ->AOTex);
	glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_WRAP_S,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_WRAP_T,GL_CLAMP);
	glTexParameteri(GL_TEXTURE_3D,GL_TEXTURE_WRAP_R,GL_CLAMP);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glTexImage3D(GL_TEXTURE_3D,0,GL_ALPHA,this ->TexW,this ->TexH,this ->TexD,0,GL_ALPHA,GL_UNSIGNED_BYTE,NULL);

	glBindTexture(GL_TEXTURE_3D,0);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER,0);

	//////////////////////////////////////////////////////////////////////////
	//INITIAL THE MEMORY OF CUDA//////////////////////////////////////////////
	this ->cuArray = InitialCudaData(this ->data,this ->TexW,this ->TexH,this ->TexD);
    GLubyte* _tfdata = (GLubyte*)malloc(256);
	for(int i = 0;i < 256;i++)
	{	
		_tfdata[i] = this ->tfData[i*4+3];
	}
	this ->tfArray = InitialCudaTranData(_tfdata);
	free(_tfdata);
	_tfdata = NULL;

	setSizeParameters(this ->TexW,this ->TexH,this ->TexD);
	/////////////////////////////////////////////////////////////////////////
	//initialize the position of light and object and ao paratemeter
	this ->cudaLightChange();
	this ->cudaVertexChange();
	this ->cudaAOParaChange();
	/////////////////////////////////////////////////////////////////////////
	//used to produce photon map
	this ->photonSize = this ->width() * this ->height() * 4 ;
	glGenBuffers(1,&this ->photonsPBO);
	glBindBuffer(GL_PIXEL_UNPACK_BUFFER,this ->photonsPBO);
	glBufferData(GL_PIXEL_UNPACK_BUFFER,this ->photonSize,NULL,GL_DYNAMIC_DRAW);
    glBindBuffer(GL_PIXEL_UNPACK_BUFFER,0);
	//allocate vectors in device memory
	checkCudaErrors(cudaMalloc((void**)&(this ->photons),this ->photonSize));

		//used for the light surface
	int most;
	if(this ->IllVolumeWidth >= this ->IllVolumeHeight && this ->IllVolumeWidth >= this ->IllVolumeDepth)
		most = this ->IllVolumeWidth;
	else if(this ->IllVolumeHeight >= this ->IllVolumeWidth && this ->IllVolumeHeight >= this ->IllVolumeDepth)
		most = this ->IllVolumeHeight;
	else
		most = this ->IllVolumeDepth;
	initialLightSurface( most,most,sizeof(unsigned char)  * 8,this ->surfaceArray,this ->surfaceArray2);
	(this ->surfaceSize)[0] = most;
	(this ->surfaceSize)[1] = most;
}

/**************************************************/
//CUDA LIGHTPOSITION CHANGE
/**************************************************/
void ultr3D::cudaLightChange()
{
	
	M3DVector3f lightP;
	float distance =  m3dGetVectorLength3(this ->lightPosition);
	setLightPosition(this ->lightPosition);

	float _photon_dis_step[2];
	_photon_dis_step[0] = distance + 4.0;
	_photon_dis_step[1] = distance/50.0;
	setPhotonParameters(_photon_dis_step);

	M3DMatrix44f result,modelviewStackInvert;
	//store the final light position
	M3DVector3f temp;
	M3DVector3f _lightPositionAfter;
	M3DVector3f screenVector,_screenVector;

	M3DVector4f lightPosition4;
	lightPosition4[0] = (this ->lightPosition)[0];
	lightPosition4[1] = (this ->lightPosition)[1];
	lightPosition4[2] = (this ->lightPosition)[2];
	lightPosition4[3] = 0.0;

	
	m3dInvertMatrix44(modelviewStackInvert,this ->modelviewStack.GetMatrix());
	m3dTransformVector4(_lightPositionAfter,lightPosition4,modelviewStackInvert);
	temp[0] = _lightPositionAfter[0];
	temp[1] = _lightPositionAfter[1];
	temp[2] = _lightPositionAfter[2];
	temp[2] = - temp[2];

	lightPositionChange[0] = temp[0];
	lightPositionChange[1] = temp[1];
	lightPositionChange[2] = temp[2];
////////////////////////////////////////////////////
	

    lightPosition4[0] = 0.0f;
	lightPosition4[1] = 0.0f;
	lightPosition4[2] = 1.0f;
	lightPosition4[3] = 0.0f;

	m3dTransformVector4(_screenVector,lightPosition4,modelviewStackInvert);

	screenVector[0] = _screenVector[0];
	screenVector[1] = _screenVector[1];
	screenVector[2] = _screenVector[2];
	m3dNormalizeVector3(screenVector);
	screenVector[2] = - screenVector[2];

	setLightPositionAfter(temp);
	
}
/**************************************************/
//CUDA VERTEX CHANGE
/**************************************************/
void ultr3D::cudaVertexChange()
{
    M3DMatrix44f Tran,invertTran;
	m3dCopyMatrix44(Tran,this ->modelviewStack.GetMatrix());	
	m3dInvertMatrix44(invertTran,Tran);
    setInvertVertextTran(invertTran);
	setVertextTran(Tran);
}

/************************************************/
//CUDA TRANSFORM FUCNTION CHANGE
/************************************************/
void ultr3D::cudaTFChange()
{
	GLubyte* tfdata = (GLubyte*)malloc(256);
	for(int i = 0;i < 256;i++)
	{
		tfdata[i] = this ->tfData[i*4+3];
	}
    this ->updateCudaTranData(tfdata);
	free(tfdata);

}
/************************************************/
//CUDA AO COUNT AND STEP CHANGE
/************************************************/
void ultr3D::cudaAOParaChange()
{
	setAOParameters(this ->ambientOcclusionCount,this ->ambientOcclusionStep,this ->ambientOcclusionRays);
}
/********************************************************************************/
//CUDA FUNCTION
/********************************************************************************/
/***********************************************/
//update the texture data
/***********************************************/
void ultr3D::updateCudaTranData(void* tfdata,int offset ,int length)
{
	checkCudaErrors(cudaMemcpyToArray(this ->tfArray,offset,0,tfdata,length,cudaMemcpyHostToDevice));
}
/***********************************************/
//cuda run the direction illumination
/***********************************************/
void ultr3D::calculateDirectI(float*c)
{
	////////////////test////////////
	float *dev_c = 0;
	checkCudaErrors(cudaMalloc((void**)&dev_c,10 * sizeof(float)));
	///////////////////////////////////
	
    checkCudaErrors(cudaSetDevice(0));
	dim3 block(this ->IllVolumeWidth);
	dim3 grid(this ->IllVolumeHeight,this ->IllVolumeDepth);

	cudaGraphicsGLRegisterBuffer(&resource,this ->DirectIllTexPBO,cudaGraphicsMapFlagsNone);
	unsigned char *pbo;
	cudaGraphicsMapResources(1,&resource,NULL);
	cudaGraphicsResourceGetMappedPointer((void**)&pbo,&(this ->IllVolumeSizeOfByte),resource);

	render_Kernel_DI(grid,block,pbo,this ->lightPositionChange,this ->surfaceSize,dev_c);
    ////////////////test////////////
	checkCudaErrors(cudaMemcpy(c,dev_c,10* sizeof(float),cudaMemcpyDeviceToHost));
	///////////////////////////////////
    cudaGraphicsUnmapResources(1,&resource,NULL);
    cudaGraphicsUnregisterResource(resource);
   ////////////////test////////////
	cudaFree(dev_c);
   ///////////////////////////////////

}
/*****************************************************/
//cuda run the indirect illumination
/***********************************************/
void ultr3D::calculateIndirectI(unsigned int count,float*c)
{
	////////////////test////////////
	float *dev_c = 0;
	checkCudaErrors(cudaMalloc((void**)&dev_c,10 * sizeof(float)));
	///////////////////////////////////
	unsigned int photonsVolume = int(this ->TexD * photonVolumeScale) * int(this ->TexH * photonVolumeScale) * int(this ->TexW * photonVolumeScale); 
    checkCudaErrors(cudaSetDevice(0));

	cudaGraphicsGLRegisterBuffer(&inResource,this ->InDirectIllTexPBO,cudaGraphicsMapFlagsNone);
	unsigned char* pbo;
	cudaGraphicsMapResources(1,&inResource,NULL);
	cudaGraphicsResourceGetMappedPointer((void**)&pbo,&(photonsVolume),inResource);

	render_Kernel_InDI(count,pbo,dev_c);
    checkCudaErrors(cudaThreadSynchronize());
    ////////////////test////////////
	checkCudaErrors(cudaMemcpy(c,dev_c,10* sizeof(float),cudaMemcpyDeviceToHost));
	///////////////////////////////////


    cudaGraphicsUnmapResources(1,&inResource,NULL);
    cudaGraphicsUnregisterResource(inResource);
   ////////////////test////////////
	cudaFree(dev_c);
   ///////////////////////////////////
}
/*****************************************************/
//cuda run to produce the photon map
/***********************************************/
void ultr3D::calculatePhoton(float *c)
{
	////////////////test////////////
	float *dev_c = 0;
	checkCudaErrors(cudaMalloc((void**)&dev_c,10 * sizeof(float)));
	///////////////////////////////////
    checkCudaErrors(cudaSetDevice(0));

	cudaGraphicsGLRegisterBuffer(&(this ->photonResource),this ->photonsPBO,cudaGraphicsMapFlagsNone);
	unsigned char* pbo;
	cudaGraphicsMapResources(1,&(this ->photonResource),NULL);
	cudaGraphicsResourceGetMappedPointer((void**)&pbo,&(this ->photonSize),this ->photonResource);

	render_Kernel_PhotonMap(this ->width(),this ->height(),pbo,(unsigned char*)photons,dev_c);

    checkCudaErrors(cudaThreadSynchronize());

    ////////////////test////////////
	checkCudaErrors(cudaMemcpy(c,dev_c,10* sizeof(float),cudaMemcpyDeviceToHost));
	///////////////////////////////////

	cudaGraphicsUnmapResources(1,&(this ->photonResource),NULL);
	cudaGraphicsUnregisterResource(this ->photonResource);
   ////////////////test////////////
	cudaFree(dev_c);
   ///////////////////////////////////

}
/***********************************************/
//cuda run to calculate the ambient occulation 
/***********************************************/
void ultr3D::calculateAO(float *c)
{
	///////////////test//////////
	float *dev_c = 0;
	checkCudaErrors(cudaMalloc((void**)&dev_c,10 * sizeof(float)));
	checkCudaErrors(cudaSetDevice(0));

	cudaGraphicsGLRegisterBuffer(&(this ->aoResource),this ->AOTexPBO,cudaGraphicsMapFlagsNone);
	unsigned char* pbo;
	cudaGraphicsMapResources(1,&(this ->aoResource),NULL);
	cudaGraphicsResourceGetMappedPointer((void**)&pbo,&(this ->dataSize),this ->aoResource);

	dim3 block(this ->TexW);
	dim3 grid(this ->TexH,this ->TexD);

	render_kernel_AOMap(grid,block,pbo,dev_c);

	checkCudaErrors(cudaThreadSynchronize());

	//////////////test/////////////////
	checkCudaErrors(cudaMemcpy(c,dev_c,10* sizeof(float),cudaMemcpyDeviceToHost));
	//////////////////////////////////

	cudaGraphicsUnmapResources(1,&this ->aoResource,NULL);
	cudaGraphicsUnregisterResource(this ->aoResource);

	/////////////////test//////////////
	cudaFree(dev_c);
	//////////////////////////////////

}


