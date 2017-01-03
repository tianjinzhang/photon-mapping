/****************************************************************************
** Meta object code from reading C++ file 'light3d.h'
**
** Created: Tue May 3 00:47:05 2016
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../light3d.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'light3d.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_light3D[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
       9,    8,    8,    8, 0x05,
      37,   23,    8,    8, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_light3D[] = {
    "light3D\0\0lightChange()\0xangle,yangle\0"
    "cudalightRotate(float,float)\0"
};

const QMetaObject light3D::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_light3D,
      qt_meta_data_light3D, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &light3D::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *light3D::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *light3D::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_light3D))
        return static_cast<void*>(const_cast< light3D*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int light3D::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: lightChange(); break;
        case 1: cudalightRotate((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void light3D::lightChange()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}

// SIGNAL 1
void light3D::cudalightRotate(float _t1, float _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
