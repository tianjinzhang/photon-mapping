#ifndef LIGHT3D_H
#define LIGHT3D_H

//opengl lib
#pragma comment(lib,"glew32.lib")
#pragma comment(lib,"gltools.lib")

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


class light3D:public QGLWidget
{

	Q_OBJECT
public:
	light3D(QWidget *parent = 0, Qt::WFlags flags = 0);
	~light3D();

	void initializeGL();
	void paintGL();
	void resizeGL(int width,int height);

public:
	float ambientIn;
	float diffuseIn;
	float specularIn;
	float distance;

	M3DVector3f ambient;
	M3DVector3f diffuse;
	M3DVector3f specular;

	GLint Ambient;
	GLint Diffuse;
	GLint Specular;
	GLint Distance;

	GLint AmbientI;
	GLint DiffuseI;
	GLint SpecularI;

    M3DVector3f position;



	GLFrustum projection;
	GLMatrixStack projectionStack;
	GLMatrixStack sphereModelViewStack;
	GLMatrixStack cubeModelViewStack;
    GLGeometryTransform spherePipline;
	GLGeometryTransform cubePipline;

	GLTriangleBatch sphereBatch;
	GLBatch cubeBatch;

	




protected:

	GLuint sphereShader;
	GLuint cubeShader;

	GLint sphereMVP;
	GLint sphereMV;
	GLint normalMV;
	GLint cubeMVP;
	void keyPressEvent(QKeyEvent *e);
	void mousePressEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);

	int mouseOldX;
	int mouseOldY;



signals:
	void lightChange();
	void cudalightRotate(float xangle,float yangle);

};

#endif