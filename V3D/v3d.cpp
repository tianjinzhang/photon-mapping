#include "v3d.h"

V3D::V3D(QWidget *parent, Qt::WFlags flags)
	: QWidget(parent, flags)
{
	
	this ->tf = new TF();
	this ->ultr3d = new ultr3D("volume2g.raw");
	this ->fileName = "volume2g.raw";
	this ->ultr3d ->show();
	ui.setupUi(this);
	//temp of light choosen
	this ->ultr3dLight = 1;
	
	//this ->ultr3d ->show();
	//this ->tf ->show();

    

	memcpy(this ->tf ->count ,this ->ultr3d ->grayCount,sizeof(int)*256);
	//this ->tf ->hightCount = float((this ->ultr3d)->TexD*(this ->ultr3d)->TexH*(this ->ultr3d)->TexW);

	QObject::connect(this ->tf,SIGNAL(tfChange()),this,SLOT(setTFTexture()));
	QObject::connect(ui.ambientButton,SIGNAL(clicked()),this,SLOT(openAmbientC()));
	QObject::connect(ui.diffuseButton,SIGNAL(clicked()),this,SLOT(openDiffuseC()));
	QObject::connect(ui.specularButton,SIGNAL(clicked()),this,SLOT(openSpecularC()));

	QObject::connect(&(this ->AmbientC),SIGNAL(currentColorChanged(QColor)),this,SLOT(setAmbientC(QColor)));
	QObject::connect(&(this ->DiffuseC),SIGNAL(currentColorChanged(QColor)),this,SLOT(setDiffuseC(QColor)));
	QObject::connect(&(this ->SpecularC),SIGNAL(currentColorChanged(QColor)),this,SLOT(setSpecularC(QColor)));

	QObject::connect(ui.ambientSlider,SIGNAL(valueChanged(int)),this,SLOT(setAmbientI(int)));
	QObject::connect(ui.diffuseSlider,SIGNAL(valueChanged(int)),this,SLOT(setDiffuseI(int)));
	QObject::connect(ui.specularSlider,SIGNAL(valueChanged(int)),this,SLOT(setSpecularI(int)));
	QObject::connect(ui.distanceSlider,SIGNAL(valueChanged(int)),this,SLOT(setDistance(int)));
	QObject::connect((this ->ultr3d),SIGNAL(rotate(float,float)),this,SLOT(rotateLightModel(float,float)));
	QObject::connect(ui.light,SIGNAL(lightChange()),this,SLOT(ultr3dlight()));

	QObject::connect(ui.localLightCheck,SIGNAL(clicked()),this,SLOT(lightTurn()));
	QObject::connect(ui.noLightCheck,SIGNAL(clicked()),this,SLOT(lightTurn()));
	//QObject::connect(ui.AmbientOcclusionCheck,SIGNAL(clicked()),this,SLOT(lightTurn()));
	QObject::connect(ui.directIlluminationCheck,SIGNAL(clicked()),this,SLOT(lightTurn()));
	//QObject::connect(ui.directPhongIlluminationCheck,SIGNAL(clicked()),this,SLOT(lightTurn()));
	//QObject::connect(ui.globalIlluminationCheck,SIGNAL(clicked()),this,SLOT(lightTurn()));
	QObject::connect(ui.inDirectIlluminationCheck,SIGNAL(clicked()),this,SLOT(lightTurn()));
	QObject::connect(ui.DirectIndirectPhongCheck,SIGNAL(clicked()),this,SLOT(lightTurn()));
	//QObject::connect(ui.AmbientOcclusionPhongCheck,SIGNAL(clicked()),this,SLOT(lightTurn()));

	QObject::connect(ui.samplingCount,SIGNAL(valueChanged(int)),this,SLOT(setSamplingCount(int)));
	QObject::connect(ui.gradientCount,SIGNAL(valueChanged(int)),this,SLOT(setGradientCount(int)));
	QObject::connect((this ->ultr3d),SIGNAL(timeStart(GLuint)),this,SLOT(setFPS(GLuint)));
	
	//QObject::connect(ui.AmbientOcclusionCount,SIGNAL(valueChanged(int)),this,SLOT(setAOCount(int)));
	//QObject::connect(ui.AmbientOcclusionStep,SIGNAL(valueChanged(int)),this,SLOT(setAOStep(int)));
	//QObject::connect(ui.AmbientOcclusionRays,SIGNAL(valueChanged(int)),this,SLOT(setAORays(int)));

	QObject::connect(ui.surfaceShadingParameter,SIGNAL(valueChanged(int)),this ,SLOT(setSSP(int)));
	//photon number
	QObject::connect(ui.photonNumberSlider,SIGNAL(valueChanged(int)),this ,SLOT(setPhotonNumber(int)));
	//HDR
	QObject::connect(ui.exposureSlider,SIGNAL(valueChanged(int)),this,SLOT(setHDRExposure(int)));
	QObject::connect(ui.photonExposureSlider,SIGNAL(valueChanged(int)),this,SLOT(setPHDRExposure(int)));
	//gamma corrction
	QObject::connect(ui.gammaCorrectionSlider,SIGNAL(valueChanged(int)),this,SLOT(setGammaCorrection(int)));
	//light attenuation
	QObject::connect(ui.lightAttenuationSlider,SIGNAL(valueChanged(int)),this,SLOT(setLightAttenuation(int)));
	//HDR on
	QObject::connect(ui.HDRcheckBox,SIGNAL(stateChanged(int)),this,SLOT(setHDRon(int)));

	//CUDA LIGHT STACK
	QObject::connect(ui.light,SIGNAL(cudalightRotate(float,float)),this,SLOT(cudalightGet(float,float)));
	//color box
	QObject::connect(ui.colorBoxSlider,SIGNAL(valueChanged(int)),this,SLOT(setColorBox(int)));

	//read data
	QObject::connect(ui.readUltrButton,SIGNAL(clicked()),this,SLOT(startUltrData()));
	QObject::connect(ui.readCTButton,SIGNAL(clicked()),this,SLOT(startCTData()));
	//set Visible
	QObject::connect(ui.VIS,SIGNAL(clicked()),this,SLOT(setUltr3dVis()));
	QObject::connect(ui.TF,SIGNAL(clicked()),this,SLOT(setTFVis()));

	//save and load tf data
	QObject::connect(ui.loadTF,SIGNAL(clicked()),this,SLOT(loadTF()));
	QObject::connect(ui.saveTF,SIGNAL(clicked()),this,SLOT(saveTF()));
	//if using tf colors
	QObject::connect(ui.useTFColors,SIGNAL(stateChanged(int)),this,SLOT(setUseTFColors(int)));

	
}

V3D::~V3D()
{

	delete(this ->ultr3d);
	delete(this ->tf);

}

void V3D::keyPressEvent(QKeyEvent *e)
{

	//switch(e ->key())
	//{
	//case Qt::Key_Up:
	//	(this ->ultr3d)->modelviewStack.RotateToWorld(10.0f,-1.0f,0.0f,0.0f);
	//	break;
	//case Qt::Key_Down:
 //      (this ->ultr3d)->modelviewStack.RotateToWorld(-10.0f,-1.0f,0.0f,0.0f);
	//	break;
	//case Qt::Key_Left:
	//	(this ->ultr3d)->modelviewStack.RotateToWorld(10.0f,0.0f,-1.0f,0.0f);
	//	break;
	//case Qt::Key_Right:
	//	(this ->ultr3d)->modelviewStack.RotateToWorld(-10.0f,0.0f,-1.0f,0.0f);
	//	break;
	//}
	//(this ->ultr3d)->LPChange = true;    
	//(this ->ultr3d)->updateGL();


}
void V3D::closeEvent(QCloseEvent *event)
{
	exit(0);
}


void V3D::setTFTexture()
{
	memcpy(this ->ultr3d->tfData,this ->tf ->tfData,256 * 4);

		
  /*for(int i = 0;i < 256;i++)
   {
	   qDebug() << this ->ultr3d->tfData[i * 4 + 0]<< " "<<this ->ultr3d->tfData[i * 4 + 1] <<" "<<this ->ultr3d->tfData[i * 4 + 2] << "," << this ->ultr3d->tfData[i * 4 + 3];
   }
   qDebug() <<".......................";*/
	(this ->ultr3d)->loadTFTex();
	(this ->ultr3d)->updateGL();
}


void V3D::setAmbientI(int t)
{
	
	ui.light ->ambientIn = t/100.0;
	ui.ambiemtIL ->setText( "Ambient Instenity| " + QString::number(ui.light ->ambientIn));
	ui.light ->updateGL();
	
}
void V3D::openAmbientC()
{
	AmbientC.open();


}
void V3D::setAmbientC(QColor c)
{
	m3dLoadVector3(ui.light ->ambient,c.red()/255.0,c.green()/255.0,c.blue()/255.0);
	ui.light ->updateGL();
	//qDebug() << "    a "<<ui.light ->ambient[1];

}
void V3D::setDiffuseI(int t)
{
	ui.light ->diffuseIn = t/100.0;
	ui.diffuseIL ->setText( "Diffuse Instenity| " + QString::number(ui.light ->diffuseIn));
	ui.light ->updateGL();

}
void V3D::openDiffuseC()
{

	DiffuseC.open();
}
void V3D::setDiffuseC(QColor c)
{
	m3dLoadVector3(ui.light ->diffuse,c.red()/255.0,c.green()/255.0,c.blue()/255.0);
	ui.light ->updateGL();
	//qDebug() << "    d "<<ui.light ->diffuse[1];

}
void V3D::setSpecularI(int t)
{
	ui.light ->specularIn = t/100.0;
	ui.specularIL ->setText( "Specular Instenity| " + QString::number(ui.light ->specularIn));
	ui.light ->updateGL();
	

}
void V3D::openSpecularC()
{

	SpecularC.open();
}
void V3D::setSpecularC(QColor c)
{
	m3dLoadVector3(ui.light ->specular,c.red()/255.0,c.green()/255.0,c.blue()/255.0);
	ui.light ->updateGL();
	//qDebug() << "    s "<<ui.light ->specular[1];

}
void V3D::setDistance(int t)
{
	ui.light ->distance = t/10.0;
	ui.distanceL ->setText( "Distance| " + QString::number(ui.light ->distance));
	ui.light ->updateGL();

}
void V3D::rotateLightModel(float xangle,float yangle)
{
	ui.light ->cubeModelViewStack.RotateToWorld(xangle,-1.0f,0.0f,0.0f);
	ui.light ->cubeModelViewStack.RotateToWorld(yangle,0.0f,-1.0f,0.0f);
    ui.light ->updateGL();

}
void V3D::ultr3dlight()
{

	M3DVector3f ambient;
	M3DVector3f diffuse;
	M3DVector3f specular;
	M3DVector4f lightPosition;
	M3DVector4f _lightPosition;
	M3DVector3f temp;

	m3dCopyVector3(ambient,ui.light ->ambient);
	m3dCopyVector3(diffuse,ui.light ->diffuse);
	m3dCopyVector3(specular,ui.light ->specular);
	m3dCopyVector3(lightPosition,ui.light ->position);
	lightPosition[3] = 0.0f;
	
	m3dScaleVector3(ambient,ui.light ->ambientIn);
	m3dScaleVector3(diffuse,ui.light ->diffuseIn);
	m3dScaleVector3(specular,ui.light ->specularIn);

	m3dTransformVector4(_lightPosition,lightPosition,ui.light ->sphereModelViewStack.GetMatrix());

	temp[0] = _lightPosition[0];
	temp[1] = _lightPosition[1];
	temp[2] = _lightPosition[2];
	

	m3dNormalizeVector3(temp);
	m3dScaleVector3(temp,ui.light ->distance);

	m3dLoadVector3((this ->ultr3d)->ambient,ambient[0],ambient[1],ambient[2]); 
    m3dLoadVector3((this ->ultr3d)->diffuse,diffuse[0],diffuse[1],diffuse[2]); 
	m3dLoadVector3((this ->ultr3d)->specular,specular[0],specular[1],specular[2]); 
	m3dLoadVector3((this ->ultr3d)->lightPosition,temp[0],temp[1],temp[2]);  

	
	(this ->ultr3d)->updateGL();

}
void V3D::lightTurn()
{
	if(ui.localLightCheck ->isChecked())
		(this ->ultr3d)->light = 1;
	else if(ui.noLightCheck ->isChecked())
		(this ->ultr3d)->light = 0;
	else if(ui.directIlluminationCheck ->isChecked())
		(this ->ultr3d)->light = 2;
	else if(ui.inDirectIlluminationCheck ->isChecked())
		(this ->ultr3d)->light = 3;
	/*else if(ui.globalIlluminationCheck ->isChecked())
		(this ->ultr3d)->light = 4;*/
	/*else if(ui.directPhongIlluminationCheck ->isChecked())
		(this ->ultr3d)->light = 5;*/
	/*else if(ui.AmbientOcclusionCheck ->isChecked())
		(this ->ultr3d)->light = 6;*/
	else if(ui.DirectIndirectPhongCheck ->isChecked())
		(this ->ultr3d)->light = 7;
	/*else if(ui.AmbientOcclusionPhongCheck ->isChecked())
		(this ->ultr3d)->light = 8;*/

	this ->ultr3dLight = this ->ultr3d ->light;
	(this ->ultr3d)->updateGL();

}
void V3D::setSamplingCount(int t)
{
	(this ->ultr3d)->setSampleStep(t);
	ui.sampleCL ->setText( "Sample count| " + QString::number(t));
	(this ->ultr3d)->updateGL();


}
void V3D::setGradientCount(int t)
{
	(this ->ultr3d)->setGradientStep(t);
	ui.gradientCL ->setText( "Gradient count| " + QString::number(t));
	(this ->ultr3d)->updateGL();


}
void V3D::setFPS(GLuint t)
{

	ui.Fps ->setText(QString::number(t) + " FPS");
	

}
void V3D::setAOCount(int t)
{
	(this ->ultr3d)->setAmbientOcclusionCount(t);
	//ui.AmbientOcclusionCountL ->setText( "AmbiOcclu Count| " + QString::number(t));
	(this ->ultr3d)->updateGL();
}
void V3D::setAOStep(int t)
{
	(this ->ultr3d)->setAmbientOcclusionStep(t);
	//ui.AmbientOcclusionStepL ->setText( "AmbiOcclu Step| " + QString::number(t));
	(this ->ultr3d)->updateGL();

}
void V3D::setAORays(int t)
{
	(this ->ultr3d)->setAmbientOcclusionRays(t);
	//ui.AmbientOcclusionRaysL ->setText( "AmbiOcclu Rays| " + QString::number(t));
	(this ->ultr3d)->updateGL();
}
//CUDA
void V3D::cudalightGet(float xangle,float yangle)
{
	/*(this ->ultr3d)->cudaLightStack.RotateToWorld(xangle,-1.0f,0.0f,0.0f);
	(this ->ultr3d)->cudaLightStack.RotateToWorld(yangle,0.0f,-1.0f,0.0f);
    */
	(this ->ultr3d)->LPChange = true;

}
//set surface shading parameter
void V3D::setSSP(int t)
{
	(this ->ultr3d)->surfaceShadingParameter = t/100.0;
	ui.SSPL ->setText(QString::number(t/100.0));
	(this ->ultr3d)->updateGL();
}
//set photon number
void V3D::setPhotonNumber(int t)
{
	(this ->ultr3d)->photonNumber = t * 10000;
	ui.photonNumberL ->setText( "photon number " + QString::number(t*10000));
	(this ->ultr3d)->updateGL();
}
//set HDR
void V3D::setHDRExposure(int t)
{
	(this ->ultr3d)->exposure = t /10.0;
	ui.exposureL ->setText(QString::number(t/10.0));
	(this ->ultr3d)->updateGL();
}
//set photon HDR
void V3D::setPHDRExposure(int t)
{
	(this ->ultr3d)->photonExposure = t /100.0;
	ui.photonExposureL ->setText(QString::number(t/100.0));
	(this ->ultr3d)->updateGL();
}
//set gamma correction
void V3D::setGammaCorrection(int t)
{
	(this ->ultr3d)->gammaCorrection = t/10.0;
	ui.gammaCorrectionL ->setText(QString::number(t/10.0));
	(this ->ultr3d)->updateGL();
}
//set light attenuation
void V3D::setLightAttenuation(int t)
{
	(this ->ultr3d)->kl = t/10.0;
	ui.lightAttenuationL ->setText(QString::number(t/10.0));
	(this ->ultr3d)->updateGL();
}
//set colorBox
void V3D::setColorBox(int t)
{
	(this ->ultr3d)->colorBox = (t - 100)/100.0;
	ui.colorBoxL ->setText(QString::number((t - 100)/100.0));
	(this ->ultr3d)->updateGL();
}
//set HDR on
void V3D::setHDRon(int t)
{
	if(Qt::Unchecked == t)
		(this ->ultr3d)->hdrOn = false;
	if(Qt::Checked == t)
		(this ->ultr3d)->hdrOn = true;
	(this ->ultr3d)->updateGL();
}
//set ultr3d,tf visable
void V3D::setUltr3dVis()
{
	this ->ultr3d ->setVisible(true);
}
void V3D::setTFVis()
{
	this ->tf ->setVisible(true);

}
//read Data
void V3D::startUltrData()
{
	
	this ->fileName = QFileDialog::getOpenFileName(this,tr("Open Volume"),NULL,tr("Volumes(*.raw)"));
	//fileName.replace('/','\\');
	if(this ->fileName == "")
	{
		QMessageBox::information(NULL, "warning", "open file cann't be null", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return;
	}
	else
	{
		
		std::string s = (this ->fileName).toStdString();
		
		delete(this ->ultr3d);
		this ->ultr3d = NULL;
		this ->ultr3d = new ultr3D(s.c_str());
		this ->initialUltr3dAgain();
		(this ->ultr3d) ->show();
		
	}
}
void V3D::startCTData()
{
	int width = 0,height = 0,depth  = 0;
	this ->fileName = QFileDialog::getOpenFileName(this,tr("Open Volume"),NULL,tr("Volumes(*.raw)"));
	//fileName.replace('/','\\');
   
	if(this ->fileName == "")
	{
		QMessageBox::information(NULL, "warning", "open file cann't be null", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return;
	}
	else
	{
		//read .txt to width,height,depth
		QString domain = this ->fileName;
		domain.replace(".raw",".txt");
        std::string d = domain.toStdString();
		
		FILE *fp;
		fp = fopen(d.c_str(),"r");
	    if(NULL == fp)
	    {
			QMessageBox::information(NULL, "warning", "please note the width height depth in .txt in the same file with same name at .raw", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
			return;
	     }

		fscanf(fp,"%d",&width);
		fscanf(fp,"%d",&height);
		fscanf(fp,"%d",&depth);
		qDebug() << width<<","<<height<<","<<depth;
		fclose(fp);
	    fp = NULL;

        std::string s = (this ->fileName).toStdString();
		delete(this ->ultr3d);
		this ->ultr3d = NULL;
		this ->ultr3d = new ultr3D(s.c_str(),width,height,depth);
		this ->initialUltr3dAgain();
		(this ->ultr3d) ->show();

	}
}
//initial another ultr3D again
void V3D::initialUltr3dAgain()
{	
	memcpy(this ->tf ->count ,this ->ultr3d ->grayCount,sizeof(int)*256);
	this ->tf ->resizeEvent(NULL);
    QObject::connect((this ->ultr3d),SIGNAL(rotate(float,float)),this,SLOT(rotateLightModel(float,float)));
    QObject::connect((this ->ultr3d),SIGNAL(timeStart(GLuint)),this,SLOT(setFPS(GLuint)));


	(this ->ultr3d)->setSampleStep(ui.samplingCount ->value());
	(this ->ultr3d)->setGradientStep(ui.gradientCount ->value());
	//(this ->ultr3d)->setAmbientOcclusionCount(ui.AmbientOcclusionCount ->value());
	//(this ->ultr3d)->setAmbientOcclusionStep(ui.AmbientOcclusionStep ->value());
	//(this ->ultr3d)->setAmbientOcclusionRays(ui.AmbientOcclusionRays ->value());
	(this ->ultr3d)->surfaceShadingParameter = ui.surfaceShadingParameter ->value()/100.0;
	(this ->ultr3d)->photonNumber = ui.photonNumberSlider ->value() * 10000;
	(this ->ultr3d)->exposure = ui.exposureSlider ->value() /10.0;
	(this ->ultr3d)->photonExposure = ui.photonExposureSlider ->value() /100.0;
	(this ->ultr3d)->gammaCorrection = ui.gammaCorrectionSlider ->value()/10.0;
	(this ->ultr3d)->kl = ui.lightAttenuationSlider ->value()/10.0;
	(this ->ultr3d)->colorBox = (ui.colorBoxSlider ->value() - 100)/100.0;
	if(Qt::Unchecked == ui.HDRcheckBox->checkState())
		(this ->ultr3d)->hdrOn = false;
	if(Qt::Checked == ui.HDRcheckBox->checkState())
		(this ->ultr3d)->hdrOn = true;
	if(Qt::Unchecked == ui.useTFColors ->checkState())
		(this ->ultr3d)->useTFColors = false;
	if(Qt::Checked == ui.useTFColors ->checkState())
		(this ->ultr3d)->useTFColors = true;
	

	(this ->ultr3d)->updateGL();

	(this ->ultr3d)->light = this ->ultr3dLight;
	qDebug() <<  this ->ultr3dLight<<"..........................";
	this ->setTFTexture();
	this ->ultr3dlight();


}
//save tf data and load tf data
void V3D::saveTF()
{
	QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("hh_mm_ss");
	QString tempfile = this ->fileName;
	tempfile.replace(".raw",current_date);
	QString str = tempfile + ".tf";
	qDebug() << str;
	std::string s = str.toStdString();
	this ->tf ->saveData(s.c_str());
	

}
void V3D::loadTF()
{
	QString str = QFileDialog::getOpenFileName(this,tr("Open tf data"),NULL,tr("Volumes(*.tf)"));
	str.replace('/','\\');

	if(str == "")
	{
		QMessageBox::information(NULL, "warning", "open tf file cann't be null", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return;
	}
	else
	{
		
		std::string s = str.toStdString();
		this ->tf ->loadData(s.c_str());
		
	}

}

//set if using TF colors
void V3D::setUseTFColors(int t)
{

	if(Qt::Unchecked == t)
		(this ->ultr3d)->useTFColors = false;
	if(Qt::Checked == t)
		(this ->ultr3d)->useTFColors = true;
	(this ->ultr3d)->updateGL();

}