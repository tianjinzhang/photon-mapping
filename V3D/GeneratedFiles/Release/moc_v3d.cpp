/****************************************************************************
** Meta object code from reading C++ file 'v3d.h'
**
** Created: Fri Apr 1 17:26:24 2016
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../v3d.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'v3d.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_V3D[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      37,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
       5,    4,    4,    4, 0x0a,
      22,   20,    4,    4, 0x0a,
      39,    4,    4,    4, 0x0a,
      56,   54,    4,    4, 0x0a,
      76,   20,    4,    4, 0x0a,
      93,    4,    4,    4, 0x0a,
     108,   54,    4,    4, 0x0a,
     128,   20,    4,    4, 0x0a,
     146,    4,    4,    4, 0x0a,
     162,   54,    4,    4, 0x0a,
     183,   20,    4,    4, 0x0a,
     214,  200,    4,    4, 0x0a,
     244,    4,    4,    4, 0x0a,
     258,    4,    4,    4, 0x0a,
     270,   20,    4,    4, 0x0a,
     292,   20,    4,    4, 0x0a,
     314,   20,    4,    4, 0x0a,
     329,   20,    4,    4, 0x0a,
     345,   20,    4,    4, 0x0a,
     360,   20,    4,    4, 0x0a,
     375,   20,    4,    4, 0x0a,
     387,   20,    4,    4, 0x0a,
     408,   20,    4,    4, 0x0a,
     428,   20,    4,    4, 0x0a,
     449,   20,    4,    4, 0x0a,
     473,   20,    4,    4, 0x0a,
     498,    4,    4,    4, 0x0a,
     515,    4,    4,    4, 0x0a,
     529,    4,    4,    4, 0x0a,
     544,    4,    4,    4, 0x0a,
     555,    4,    4,    4, 0x0a,
     571,    4,    4,    4, 0x0a,
     585,  200,    4,    4, 0x0a,
     611,    4,    4,    4, 0x0a,
     632,    4,    4,    4, 0x0a,
     641,    4,    4,    4, 0x0a,
     650,   20,    4,    4, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_V3D[] = {
    "V3D\0\0setTFTexture()\0t\0setAmbientI(int)\0"
    "openAmbientC()\0c\0setAmbientC(QColor)\0"
    "setDiffuseI(int)\0openDiffuseC()\0"
    "setDiffuseC(QColor)\0setSpecularI(int)\0"
    "openSpecularC()\0setSpecularC(QColor)\0"
    "setDistance(int)\0xangle,yangle\0"
    "rotateLightModel(float,float)\0"
    "ultr3dlight()\0lightTurn()\0"
    "setSamplingCount(int)\0setGradientCount(int)\0"
    "setFPS(GLuint)\0setAOCount(int)\0"
    "setAOStep(int)\0setAORays(int)\0setSSP(int)\0"
    "setPhotonNumber(int)\0setHDRExposure(int)\0"
    "setPHDRExposure(int)\0setGammaCorrection(int)\0"
    "setLightAttenuation(int)\0setColorBox(int)\0"
    "setHDRon(int)\0setUltr3dVis()\0setTFVis()\0"
    "startUltrData()\0startCTData()\0"
    "cudalightGet(float,float)\0"
    "initialUltr3dAgain()\0saveTF()\0loadTF()\0"
    "setUseTFColors(int)\0"
};

const QMetaObject V3D::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_V3D,
      qt_meta_data_V3D, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &V3D::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *V3D::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *V3D::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_V3D))
        return static_cast<void*>(const_cast< V3D*>(this));
    return QWidget::qt_metacast(_clname);
}

int V3D::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: setTFTexture(); break;
        case 1: setAmbientI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: openAmbientC(); break;
        case 3: setAmbientC((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 4: setDiffuseI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: openDiffuseC(); break;
        case 6: setDiffuseC((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 7: setSpecularI((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: openSpecularC(); break;
        case 9: setSpecularC((*reinterpret_cast< QColor(*)>(_a[1]))); break;
        case 10: setDistance((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: rotateLightModel((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 12: ultr3dlight(); break;
        case 13: lightTurn(); break;
        case 14: setSamplingCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: setGradientCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: setFPS((*reinterpret_cast< GLuint(*)>(_a[1]))); break;
        case 17: setAOCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 18: setAOStep((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 19: setAORays((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: setSSP((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: setPhotonNumber((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 22: setHDRExposure((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: setPHDRExposure((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 24: setGammaCorrection((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: setLightAttenuation((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: setColorBox((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: setHDRon((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 28: setUltr3dVis(); break;
        case 29: setTFVis(); break;
        case 30: startUltrData(); break;
        case 31: startCTData(); break;
        case 32: cudalightGet((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 33: initialUltr3dAgain(); break;
        case 34: saveTF(); break;
        case 35: loadTF(); break;
        case 36: setUseTFColors((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 37;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
