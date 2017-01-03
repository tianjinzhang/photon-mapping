/****************************************************************************
** Meta object code from reading C++ file 'ultr3d.h'
**
** Created: Fri Apr 1 17:26:24 2016
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ultr3d.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ultr3d.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ultr3D[] = {

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
      10,    8,    7,    7, 0x05,
      30,    7,    7,    7, 0x05,

       0        // eod
};

static const char qt_meta_stringdata_ultr3D[] = {
    "ultr3D\0\0,\0rotate(float,float)\0"
    "timeStart(GLuint)\0"
};

const QMetaObject ultr3D::staticMetaObject = {
    { &QGLWidget::staticMetaObject, qt_meta_stringdata_ultr3D,
      qt_meta_data_ultr3D, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ultr3D::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ultr3D::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ultr3D::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ultr3D))
        return static_cast<void*>(const_cast< ultr3D*>(this));
    return QGLWidget::qt_metacast(_clname);
}

int ultr3D::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: rotate((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2]))); break;
        case 1: timeStart((*reinterpret_cast< GLuint(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ultr3D::rotate(float _t1, float _t2)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ultr3D::timeStart(GLuint _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
