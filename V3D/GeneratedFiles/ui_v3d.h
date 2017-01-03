/********************************************************************************
** Form generated from reading UI file 'v3d.ui'
**
** Created: Tue May 3 00:47:13 2016
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_V3D_H
#define UI_V3D_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSlider>
#include <QtGui/QWidget>
#include "light3d.h"

QT_BEGIN_NAMESPACE

class Ui_V3DClass
{
public:
    light3D *light;
    QLabel *Fps;
    QPushButton *readUltrButton;
    QPushButton *readCTButton;
    QGroupBox *groupBox_8;
    QLabel *Label;
    QSlider *gammaCorrectionSlider;
    QLabel *gammaCorrectionL;
    QPushButton *TF;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGroupBox *groupBox_6;
    QLabel *photonNumberL;
    QSlider *photonNumberSlider;
    QSlider *photonExposureSlider;
    QLabel *photonExposureL;
    QLabel *photonNumberL_2;
    QGroupBox *groupBox_3;
    QSlider *samplingCount;
    QLabel *sampleCL;
    QSlider *gradientCount;
    QLabel *gradientCL;
    QGroupBox *groupBox_2;
    QLabel *ambiemtIL;
    QSlider *ambientSlider;
    QPushButton *ambientButton;
    QLabel *diffuseIL;
    QSlider *diffuseSlider;
    QPushButton *diffuseButton;
    QLabel *specularIL;
    QSlider *specularSlider;
    QPushButton *specularButton;
    QLabel *distanceL;
    QSlider *distanceSlider;
    QGroupBox *groupBox_5;
    QSlider *exposureSlider;
    QLabel *exposureL;
    QCheckBox *HDRcheckBox;
    QGroupBox *groupBox_4;
    QRadioButton *localLightCheck;
    QRadioButton *noLightCheck;
    QRadioButton *directIlluminationCheck;
    QRadioButton *inDirectIlluminationCheck;
    QRadioButton *DirectIndirectPhongCheck;
    QLabel *Label_2;
    QLabel *lightAttenuationL;
    QSlider *lightAttenuationSlider;
    QSlider *surfaceShadingParameter;
    QLabel *SSPL;
    QLabel *Label_3;
    QGroupBox *groupBox_7;
    QLabel *colorBox;
    QSlider *colorBoxSlider;
    QLabel *colorBoxL;
    QPushButton *VIS;
    QPushButton *loadTF;
    QPushButton *saveTF;
    QCheckBox *useTFColors;

    void setupUi(QWidget *V3DClass)
    {
        if (V3DClass->objectName().isEmpty())
            V3DClass->setObjectName(QString::fromUtf8("V3DClass"));
        V3DClass->resize(556, 745);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(V3DClass->sizePolicy().hasHeightForWidth());
        V3DClass->setSizePolicy(sizePolicy);
        V3DClass->setMinimumSize(QSize(0, 0));
        V3DClass->setMaximumSize(QSize(556, 745));
        V3DClass->setStyleSheet(QString::fromUtf8(""));
        light = new light3D(V3DClass);
        light->setObjectName(QString::fromUtf8("light"));
        light->setGeometry(QRect(10, 90, 301, 281));
        light->setFocusPolicy(Qt::StrongFocus);
        Fps = new QLabel(V3DClass);
        Fps->setObjectName(QString::fromUtf8("Fps"));
        Fps->setGeometry(QRect(70, 50, 171, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        Fps->setFont(font);
        Fps->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
""));
        readUltrButton = new QPushButton(V3DClass);
        readUltrButton->setObjectName(QString::fromUtf8("readUltrButton"));
        readUltrButton->setGeometry(QRect(10, 10, 81, 31));
        readCTButton = new QPushButton(V3DClass);
        readCTButton->setObjectName(QString::fromUtf8("readCTButton"));
        readCTButton->setGeometry(QRect(100, 10, 81, 31));
        readCTButton->setStyleSheet(QString::fromUtf8(""));
        groupBox_8 = new QGroupBox(V3DClass);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setGeometry(QRect(10, 380, 301, 71));
        Label = new QLabel(groupBox_8);
        Label->setObjectName(QString::fromUtf8("Label"));
        Label->setGeometry(QRect(10, 20, 101, 16));
        gammaCorrectionSlider = new QSlider(groupBox_8);
        gammaCorrectionSlider->setObjectName(QString::fromUtf8("gammaCorrectionSlider"));
        gammaCorrectionSlider->setGeometry(QRect(10, 40, 251, 19));
        gammaCorrectionSlider->setFocusPolicy(Qt::NoFocus);
        gammaCorrectionSlider->setMinimum(1);
        gammaCorrectionSlider->setMaximum(26);
        gammaCorrectionSlider->setSingleStep(1);
        gammaCorrectionSlider->setPageStep(1);
        gammaCorrectionSlider->setValue(16);
        gammaCorrectionSlider->setOrientation(Qt::Horizontal);
        gammaCorrectionL = new QLabel(groupBox_8);
        gammaCorrectionL->setObjectName(QString::fromUtf8("gammaCorrectionL"));
        gammaCorrectionL->setGeometry(QRect(270, 40, 21, 16));
        TF = new QPushButton(V3DClass);
        TF->setObjectName(QString::fromUtf8("TF"));
        TF->setGeometry(QRect(330, 10, 41, 31));
        scrollArea = new QScrollArea(V3DClass);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(10, 510, 531, 231));
        scrollArea->setMinimumSize(QSize(0, 0));
        scrollArea->setStyleSheet(QString::fromUtf8("QScrollArea{border:0px solid #555;}"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 514, 700));
        scrollAreaWidgetContents->setMinimumSize(QSize(0, 700));
        groupBox_6 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(0, 20, 511, 111));
        photonNumberL = new QLabel(groupBox_6);
        photonNumberL->setObjectName(QString::fromUtf8("photonNumberL"));
        photonNumberL->setGeometry(QRect(10, 20, 191, 16));
        photonNumberSlider = new QSlider(groupBox_6);
        photonNumberSlider->setObjectName(QString::fromUtf8("photonNumberSlider"));
        photonNumberSlider->setGeometry(QRect(10, 40, 491, 19));
        photonNumberSlider->setFocusPolicy(Qt::NoFocus);
        photonNumberSlider->setMinimum(50);
        photonNumberSlider->setMaximum(1500);
        photonNumberSlider->setSingleStep(10);
        photonNumberSlider->setPageStep(10);
        photonNumberSlider->setValue(400);
        photonNumberSlider->setOrientation(Qt::Horizontal);
        photonExposureSlider = new QSlider(groupBox_6);
        photonExposureSlider->setObjectName(QString::fromUtf8("photonExposureSlider"));
        photonExposureSlider->setGeometry(QRect(10, 80, 491, 19));
        photonExposureSlider->setMouseTracking(true);
        photonExposureSlider->setFocusPolicy(Qt::NoFocus);
        photonExposureSlider->setMinimum(0);
        photonExposureSlider->setMaximum(200);
        photonExposureSlider->setSingleStep(1);
        photonExposureSlider->setPageStep(1);
        photonExposureSlider->setValue(100);
        photonExposureSlider->setOrientation(Qt::Horizontal);
        photonExposureL = new QLabel(groupBox_6);
        photonExposureL->setObjectName(QString::fromUtf8("photonExposureL"));
        photonExposureL->setGeometry(QRect(180, 60, 31, 16));
        photonNumberL_2 = new QLabel(groupBox_6);
        photonNumberL_2->setObjectName(QString::fromUtf8("photonNumberL_2"));
        photonNumberL_2->setGeometry(QRect(10, 60, 191, 16));
        groupBox_3 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(0, 140, 511, 121));
        samplingCount = new QSlider(groupBox_3);
        samplingCount->setObjectName(QString::fromUtf8("samplingCount"));
        samplingCount->setGeometry(QRect(10, 40, 491, 19));
        samplingCount->setMinimum(100);
        samplingCount->setMaximum(3000);
        samplingCount->setSingleStep(1);
        samplingCount->setValue(1000);
        samplingCount->setSliderPosition(1000);
        samplingCount->setOrientation(Qt::Horizontal);
        sampleCL = new QLabel(groupBox_3);
        sampleCL->setObjectName(QString::fromUtf8("sampleCL"));
        sampleCL->setGeometry(QRect(10, 20, 131, 16));
        gradientCount = new QSlider(groupBox_3);
        gradientCount->setObjectName(QString::fromUtf8("gradientCount"));
        gradientCount->setGeometry(QRect(10, 80, 491, 19));
        gradientCount->setMinimum(100);
        gradientCount->setMaximum(3000);
        gradientCount->setSingleStep(1);
        gradientCount->setValue(1000);
        gradientCount->setOrientation(Qt::Horizontal);
        gradientCL = new QLabel(groupBox_3);
        gradientCL->setObjectName(QString::fromUtf8("gradientCL"));
        gradientCL->setGeometry(QRect(10, 60, 131, 16));
        groupBox_2 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(0, 270, 511, 211));
        ambiemtIL = new QLabel(groupBox_2);
        ambiemtIL->setObjectName(QString::fromUtf8("ambiemtIL"));
        ambiemtIL->setGeometry(QRect(10, 30, 191, 16));
        ambientSlider = new QSlider(groupBox_2);
        ambientSlider->setObjectName(QString::fromUtf8("ambientSlider"));
        ambientSlider->setGeometry(QRect(10, 50, 431, 19));
        ambientSlider->setFocusPolicy(Qt::NoFocus);
        ambientSlider->setMaximum(100);
        ambientSlider->setSingleStep(1);
        ambientSlider->setPageStep(10);
        ambientSlider->setValue(0);
        ambientSlider->setOrientation(Qt::Horizontal);
        ambientButton = new QPushButton(groupBox_2);
        ambientButton->setObjectName(QString::fromUtf8("ambientButton"));
        ambientButton->setGeometry(QRect(450, 50, 51, 16));
        diffuseIL = new QLabel(groupBox_2);
        diffuseIL->setObjectName(QString::fromUtf8("diffuseIL"));
        diffuseIL->setGeometry(QRect(10, 70, 171, 16));
        diffuseSlider = new QSlider(groupBox_2);
        diffuseSlider->setObjectName(QString::fromUtf8("diffuseSlider"));
        diffuseSlider->setGeometry(QRect(10, 90, 431, 19));
        diffuseSlider->setFocusPolicy(Qt::NoFocus);
        diffuseSlider->setMaximum(100);
        diffuseSlider->setValue(100);
        diffuseSlider->setOrientation(Qt::Horizontal);
        diffuseButton = new QPushButton(groupBox_2);
        diffuseButton->setObjectName(QString::fromUtf8("diffuseButton"));
        diffuseButton->setGeometry(QRect(450, 90, 51, 16));
        specularIL = new QLabel(groupBox_2);
        specularIL->setObjectName(QString::fromUtf8("specularIL"));
        specularIL->setGeometry(QRect(10, 110, 181, 16));
        specularSlider = new QSlider(groupBox_2);
        specularSlider->setObjectName(QString::fromUtf8("specularSlider"));
        specularSlider->setGeometry(QRect(10, 130, 431, 19));
        specularSlider->setFocusPolicy(Qt::NoFocus);
        specularSlider->setMaximum(100);
        specularSlider->setOrientation(Qt::Horizontal);
        specularButton = new QPushButton(groupBox_2);
        specularButton->setObjectName(QString::fromUtf8("specularButton"));
        specularButton->setGeometry(QRect(450, 130, 51, 16));
        distanceL = new QLabel(groupBox_2);
        distanceL->setObjectName(QString::fromUtf8("distanceL"));
        distanceL->setGeometry(QRect(10, 150, 141, 16));
        distanceSlider = new QSlider(groupBox_2);
        distanceSlider->setObjectName(QString::fromUtf8("distanceSlider"));
        distanceSlider->setGeometry(QRect(10, 170, 381, 19));
        distanceSlider->setFocusPolicy(Qt::NoFocus);
        distanceSlider->setMinimum(0);
        distanceSlider->setMaximum(100);
        distanceSlider->setValue(25);
        distanceSlider->setOrientation(Qt::Horizontal);
        scrollArea->setWidget(scrollAreaWidgetContents);
        groupBox_5 = new QGroupBox(V3DClass);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 460, 521, 51));
        exposureSlider = new QSlider(groupBox_5);
        exposureSlider->setObjectName(QString::fromUtf8("exposureSlider"));
        exposureSlider->setGeometry(QRect(30, 20, 441, 20));
        exposureSlider->setFocusPolicy(Qt::NoFocus);
        exposureSlider->setMinimum(0);
        exposureSlider->setMaximum(50);
        exposureSlider->setSingleStep(2);
        exposureSlider->setPageStep(2);
        exposureSlider->setValue(25);
        exposureSlider->setOrientation(Qt::Horizontal);
        exposureL = new QLabel(groupBox_5);
        exposureL->setObjectName(QString::fromUtf8("exposureL"));
        exposureL->setGeometry(QRect(480, 20, 21, 16));
        HDRcheckBox = new QCheckBox(groupBox_5);
        HDRcheckBox->setObjectName(QString::fromUtf8("HDRcheckBox"));
        HDRcheckBox->setGeometry(QRect(10, 20, 16, 16));
        HDRcheckBox->setChecked(true);
        groupBox_4 = new QGroupBox(V3DClass);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(320, 90, 221, 361));
        localLightCheck = new QRadioButton(groupBox_4);
        localLightCheck->setObjectName(QString::fromUtf8("localLightCheck"));
        localLightCheck->setGeometry(QRect(10, 40, 181, 51));
        localLightCheck->setChecked(true);
        localLightCheck->setAutoRepeat(false);
        noLightCheck = new QRadioButton(groupBox_4);
        noLightCheck->setObjectName(QString::fromUtf8("noLightCheck"));
        noLightCheck->setGeometry(QRect(10, 20, 131, 31));
        noLightCheck->setChecked(false);
        directIlluminationCheck = new QRadioButton(groupBox_4);
        directIlluminationCheck->setObjectName(QString::fromUtf8("directIlluminationCheck"));
        directIlluminationCheck->setGeometry(QRect(10, 80, 181, 31));
        directIlluminationCheck->setChecked(false);
        inDirectIlluminationCheck = new QRadioButton(groupBox_4);
        inDirectIlluminationCheck->setObjectName(QString::fromUtf8("inDirectIlluminationCheck"));
        inDirectIlluminationCheck->setGeometry(QRect(10, 110, 191, 31));
        inDirectIlluminationCheck->setChecked(false);
        DirectIndirectPhongCheck = new QRadioButton(groupBox_4);
        DirectIndirectPhongCheck->setObjectName(QString::fromUtf8("DirectIndirectPhongCheck"));
        DirectIndirectPhongCheck->setGeometry(QRect(10, 140, 201, 31));
        DirectIndirectPhongCheck->setChecked(false);
        Label_2 = new QLabel(groupBox_4);
        Label_2->setObjectName(QString::fromUtf8("Label_2"));
        Label_2->setGeometry(QRect(10, 210, 121, 16));
        lightAttenuationL = new QLabel(groupBox_4);
        lightAttenuationL->setObjectName(QString::fromUtf8("lightAttenuationL"));
        lightAttenuationL->setGeometry(QRect(200, 240, 21, 16));
        lightAttenuationSlider = new QSlider(groupBox_4);
        lightAttenuationSlider->setObjectName(QString::fromUtf8("lightAttenuationSlider"));
        lightAttenuationSlider->setGeometry(QRect(10, 240, 181, 19));
        lightAttenuationSlider->setFocusPolicy(Qt::NoFocus);
        lightAttenuationSlider->setMinimum(0);
        lightAttenuationSlider->setMaximum(40);
        lightAttenuationSlider->setSingleStep(1);
        lightAttenuationSlider->setPageStep(1);
        lightAttenuationSlider->setValue(0);
        lightAttenuationSlider->setOrientation(Qt::Horizontal);
        surfaceShadingParameter = new QSlider(groupBox_4);
        surfaceShadingParameter->setObjectName(QString::fromUtf8("surfaceShadingParameter"));
        surfaceShadingParameter->setGeometry(QRect(10, 190, 181, 20));
        surfaceShadingParameter->setFocusPolicy(Qt::NoFocus);
        surfaceShadingParameter->setMinimum(0);
        surfaceShadingParameter->setMaximum(100);
        surfaceShadingParameter->setSingleStep(10);
        surfaceShadingParameter->setValue(100);
        surfaceShadingParameter->setOrientation(Qt::Horizontal);
        SSPL = new QLabel(groupBox_4);
        SSPL->setObjectName(QString::fromUtf8("SSPL"));
        SSPL->setGeometry(QRect(200, 190, 21, 16));
        Label_3 = new QLabel(groupBox_4);
        Label_3->setObjectName(QString::fromUtf8("Label_3"));
        Label_3->setGeometry(QRect(10, 170, 121, 16));
        groupBox_7 = new QGroupBox(groupBox_4);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(0, 280, 221, 91));
        colorBox = new QLabel(groupBox_7);
        colorBox->setObjectName(QString::fromUtf8("colorBox"));
        colorBox->setGeometry(QRect(10, 50, 201, 21));
        colorBox->setStyleSheet(QString::fromUtf8("image: url(:/V3D/Resources/colobox.png);"));
        colorBoxSlider = new QSlider(groupBox_7);
        colorBoxSlider->setObjectName(QString::fromUtf8("colorBoxSlider"));
        colorBoxSlider->setGeometry(QRect(10, 30, 201, 19));
        colorBoxSlider->setMaximum(200);
        colorBoxSlider->setPageStep(1);
        colorBoxSlider->setValue(100);
        colorBoxSlider->setOrientation(Qt::Horizontal);
        colorBoxL = new QLabel(groupBox_7);
        colorBoxL->setObjectName(QString::fromUtf8("colorBoxL"));
        colorBoxL->setGeometry(QRect(10, 20, 31, 16));
        VIS = new QPushButton(V3DClass);
        VIS->setObjectName(QString::fromUtf8("VIS"));
        VIS->setGeometry(QRect(10, 50, 41, 31));
        loadTF = new QPushButton(V3DClass);
        loadTF->setObjectName(QString::fromUtf8("loadTF"));
        loadTF->setGeometry(QRect(390, 10, 71, 31));
        saveTF = new QPushButton(V3DClass);
        saveTF->setObjectName(QString::fromUtf8("saveTF"));
        saveTF->setGeometry(QRect(470, 10, 71, 31));
        useTFColors = new QCheckBox(V3DClass);
        useTFColors->setObjectName(QString::fromUtf8("useTFColors"));
        useTFColors->setGeometry(QRect(340, 50, 101, 31));

        retranslateUi(V3DClass);

        QMetaObject::connectSlotsByName(V3DClass);
    } // setupUi

    void retranslateUi(QWidget *V3DClass)
    {
        V3DClass->setWindowTitle(QApplication::translate("V3DClass", "V3D", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        V3DClass->setToolTip(QString());
#endif // QT_NO_TOOLTIP
        Fps->setText(QString());
        readUltrButton->setText(QApplication::translate("V3DClass", "HeadFile", 0, QApplication::UnicodeUTF8));
        readCTButton->setText(QApplication::translate("V3DClass", "NoHead", 0, QApplication::UnicodeUTF8));
        groupBox_8->setTitle(QApplication::translate("V3DClass", "Gamma", 0, QApplication::UnicodeUTF8));
        Label->setText(QApplication::translate("V3DClass", "Gamma Correction", 0, QApplication::UnicodeUTF8));
        gammaCorrectionL->setText(QApplication::translate("V3DClass", "1.6", 0, QApplication::UnicodeUTF8));
        TF->setText(QApplication::translate("V3DClass", "TF", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QApplication::translate("V3DClass", "Photon Mapping", 0, QApplication::UnicodeUTF8));
        photonNumberL->setText(QApplication::translate("V3DClass", "photon number 4000000", 0, QApplication::UnicodeUTF8));
        photonExposureL->setText(QString());
        photonNumberL_2->setText(QApplication::translate("V3DClass", "photon mapping HDR Exposure", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("V3DClass", "Sampling", 0, QApplication::UnicodeUTF8));
        sampleCL->setText(QApplication::translate("V3DClass", "Sample Count  1000", 0, QApplication::UnicodeUTF8));
        gradientCL->setText(QApplication::translate("V3DClass", "Gradient Count 1000", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("V3DClass", "lighting Source", 0, QApplication::UnicodeUTF8));
        ambiemtIL->setText(QApplication::translate("V3DClass", "Ambient Instenity   0.0", 0, QApplication::UnicodeUTF8));
        ambientButton->setText(QApplication::translate("V3DClass", "Color", 0, QApplication::UnicodeUTF8));
        diffuseIL->setText(QApplication::translate("V3DClass", "Diffuse Instenity   1.0", 0, QApplication::UnicodeUTF8));
        diffuseButton->setText(QApplication::translate("V3DClass", "Color", 0, QApplication::UnicodeUTF8));
        specularIL->setText(QApplication::translate("V3DClass", "Specular Instenity 0.0", 0, QApplication::UnicodeUTF8));
        specularButton->setText(QApplication::translate("V3DClass", "Color", 0, QApplication::UnicodeUTF8));
        distanceL->setText(QApplication::translate("V3DClass", "Distance  2.5", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("V3DClass", " HDR exposure", 0, QApplication::UnicodeUTF8));
        exposureL->setText(QApplication::translate("V3DClass", "2.5", 0, QApplication::UnicodeUTF8));
        HDRcheckBox->setText(QString());
        groupBox_4->setTitle(QApplication::translate("V3DClass", "Illumination Choosen", 0, QApplication::UnicodeUTF8));
        localLightCheck->setText(QApplication::translate("V3DClass", "Local Illumination(Phong)", 0, QApplication::UnicodeUTF8));
        noLightCheck->setText(QApplication::translate("V3DClass", "Not Illumination", 0, QApplication::UnicodeUTF8));
        directIlluminationCheck->setText(QApplication::translate("V3DClass", "Direct Illumination", 0, QApplication::UnicodeUTF8));
        inDirectIlluminationCheck->setText(QApplication::translate("V3DClass", "Photon InDirect Illumination", 0, QApplication::UnicodeUTF8));
        DirectIndirectPhongCheck->setText(QApplication::translate("V3DClass", "Direct + InDirect Illumination", 0, QApplication::UnicodeUTF8));
        Label_2->setText(QApplication::translate("V3DClass", "Light Attenuation", 0, QApplication::UnicodeUTF8));
        lightAttenuationL->setText(QApplication::translate("V3DClass", "0.2", 0, QApplication::UnicodeUTF8));
        SSPL->setText(QApplication::translate("V3DClass", "1.0", 0, QApplication::UnicodeUTF8));
        Label_3->setText(QApplication::translate("V3DClass", "Surface parameter", 0, QApplication::UnicodeUTF8));
        groupBox_7->setTitle(QApplication::translate("V3DClass", "Skin Model", 0, QApplication::UnicodeUTF8));
        colorBox->setText(QString());
        colorBoxL->setText(QApplication::translate("V3DClass", "0.0", 0, QApplication::UnicodeUTF8));
        VIS->setText(QApplication::translate("V3DClass", "VIS", 0, QApplication::UnicodeUTF8));
        loadTF->setText(QApplication::translate("V3DClass", "Load TF", 0, QApplication::UnicodeUTF8));
        saveTF->setText(QApplication::translate("V3DClass", "Save TF", 0, QApplication::UnicodeUTF8));
        useTFColors->setText(QApplication::translate("V3DClass", "Use TF Color", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class V3DClass: public Ui_V3DClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_V3D_H
