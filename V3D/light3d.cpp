#include "light3d.h"


light3D::light3D(QWidget *parent , Qt::WFlags flags ):QGLWidget(parent)
{

	m3dLoadVector3(ambient,1.0,1.0,1.0);
	m3dLoadVector3(diffuse,1.0,1.0,1.0);
	m3dLoadVector3(specular,1.0,1.0,1.0);

	m3dLoadVector3(position,1.0,1.0,1.0);

	ambientIn = 0.0;
	diffuseIn = 1.0;
	specularIn = 0.0;
	distance = 2.5;
}

light3D::~light3D()
{
}


void light3D::initializeGL()
{
	GLenum err = glewInit();
	if(GLEW_OK != err)
	{

		qDebug() << "glewInit error...................."<< glewGetErrorString(err);
		return;

	}
	gltMakeCube(cubeBatch,1.0f);
	gltMakeSphere(sphereBatch,1.74f,56,56);
	

	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glEnable(GL_CULL_FACE);
	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	

	projection.SetOrthographic(-2.0f,2.0f,-2.0f,2.0f,-2.0f,2.0f);
	projectionStack.LoadMatrix(projection.GetProjectionMatrix());

	spherePipline.SetMatrixStacks(sphereModelViewStack,projectionStack);
	cubePipline.SetMatrixStacks(cubeModelViewStack,projectionStack);
	//cubeModelViewStack.RotateToWorld(90.0f,1.0f,1.0f,1.0f)

	sphereShader = gltLoadShaderPairWithAttributes("./GLSL/spherevp.c","./GLSL/spherefp.c",2,0,"vVertex",2,"vNormal");
	cubeShader = gltLoadShaderPairWithAttributes("./GLSL/cubevp.c","./GLSL/cubefp.c",1.0,"vVertex");

	
    cubeMVP = glGetUniformLocation(cubeShader,"mvp");
	sphereMVP = glGetUniformLocation(sphereShader,"mvp");
	sphereMV = glGetUniformLocation(sphereShader,"mv"); 
	Ambient = glGetUniformLocation(sphereShader,"ambient");
	Diffuse = glGetUniformLocation(sphereShader,"diffuse");
	Specular = glGetUniformLocation(sphereShader,"specular");
	AmbientI = glGetUniformLocation(sphereShader,"ambienti");
	DiffuseI = glGetUniformLocation(sphereShader,"diffusei");
	SpecularI = glGetUniformLocation(sphereShader,"speculari");
	Distance = glGetUniformLocation(sphereShader,"distance");

}

void light3D::resizeGL(int width,int height)
{
	if( 0 == height)
	{

		height = 1;
	}
	glViewport(0,0,width,height);

}

void light3D::paintGL()
{


	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	glUseProgram(cubeShader);
	glUniformMatrix4fv(cubeMVP,1,GL_FALSE,cubePipline.GetModelViewProjectionMatrix());

	cubeBatch.Draw();

	glUseProgram(sphereShader);
	glUniformMatrix4fv(sphereMVP,1,GL_FALSE,spherePipline.GetProjectionMatrix());
	glUniformMatrix4fv(sphereMV,1,GL_FALSE,spherePipline.GetModelViewMatrix());
	glUniform3fv(Ambient,1,ambient);
	glUniform3fv(Diffuse,1,diffuse);
	glUniform3fv(Specular,1,specular);
	glUniform1f(AmbientI,ambientIn);
	glUniform1f(DiffuseI,diffuseIn);
	glUniform1f(SpecularI,specularIn);
	glUniform1f(Distance,distance);

	sphereBatch.Draw();

	emit lightChange();
}
void light3D::keyPressEvent(QKeyEvent *e)
{


	
	/*switch(e ->key())
	{
	case Qt::Key_Up:
		sphereModelViewStack.RotateToWorld(0.8f,-1.0f,0.0f,0.0f);
		break;
	case Qt::Key_Down:
        sphereModelViewStack.RotateToWorld(-0.8f,-1.0f,0.0f,0.0f);
		break;
	case Qt::Key_Left:
		sphereModelViewStack.RotateToWorld(0.8f,0.0f,-1.0f,0.0f);
		break;
	case Qt::Key_Right:
		sphereModelViewStack.RotateToWorld(-0.8f,0.0f,-1.0f,0.0f);
		break;
	}
	
	updateGL();*/


}
void light3D::mouseMoveEvent(QMouseEvent *e)
{
	int deltax =  mouseOldX - e->x();
	int deltay =  mouseOldY - e->y();

//	qDebug() <<deltax<<".........."<<deltay;

	float yangle = 6.0*deltax/(this -> width());
    float xangle = 6.0*deltay/(this -> height());

	sphereModelViewStack.RotateToWorld(xangle,-1.0f,0.0f,0.0f);
	sphereModelViewStack.RotateToWorld(yangle,0.0f,-1.0f,0.0f);
	emit this ->cudalightRotate(xangle,yangle);
    updateGL();

	
}
void light3D::mousePressEvent(QMouseEvent *e)
{
	mouseOldX = e->x();
	mouseOldY = e->y();
}
