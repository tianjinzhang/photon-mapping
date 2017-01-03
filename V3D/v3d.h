#ifndef V3D_H
#define V3D_H

#include <QtGui/QWidget>
#include <QString>
#include <QColorDialog>
#include <QColor>
#include <QFileDialog>
#include <QMessageBox>
#include <math3d.h>
#include "ui_v3d.h"
#include "ultr3d.h"
#include "tf.h"


class V3D : public QWidget
{
	Q_OBJECT

public:
	V3D(QWidget *parent = 0, Qt::WFlags flags = 0);
	~V3D();
    void keyPressEvent(QKeyEvent *e);
	void closeEvent(QCloseEvent *event);

	

private:
    ultr3D *ultr3d;
	TF *tf;

	Ui::V3DClass ui;
	
	QColorDialog AmbientC;
	QColorDialog DiffuseC;
	QColorDialog SpecularC;

	QString fileName;

    //the temp data of ultr3d
	int ultr3dLight;

public slots:
	

	void setTFTexture();

	void setAmbientI(int t);
	void openAmbientC();
	void setAmbientC(QColor c);
	void setDiffuseI(int t);
	void openDiffuseC();
	void setDiffuseC(QColor c);
	void setSpecularI(int t);
	void openSpecularC();
	void setSpecularC(QColor c);
	void setDistance(int t);
	void rotateLightModel(float xangle,float yangle);

	void ultr3dlight();
	void lightTurn();

	void setSamplingCount(int t);
	void setGradientCount(int t);
	void setFPS(GLuint t);

	void setAOCount(int t);
	void setAOStep(int t);
	void setAORays(int t);
	void setSSP(int t);
	void setPhotonNumber(int t);
	void setHDRExposure(int t);
	void setPHDRExposure(int t);
	void setGammaCorrection(int t);
	void setLightAttenuation(int t);
	void setColorBox(int);
	void setHDRon(int);

	//set ultr3d,tf visiable 
	void setUltr3dVis();
	void setTFVis();

	//read Data
	void startUltrData();
    void startCTData();

	//CUDA
	void cudalightGet(float xangle,float yangle);

	//initial ultr3d again
	void initialUltr3dAgain();

	//save tf data
	void saveTF();
	//load tf data
	void loadTF();
	//set use TF colors
	void setUseTFColors(int t);





	

};

#endif // V3D_H
