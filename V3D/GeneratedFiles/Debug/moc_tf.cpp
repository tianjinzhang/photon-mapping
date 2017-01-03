/****************************************************************************
** Meta object code from reading C++ file 'tf.h'
**
** Created: Tue May 3 00:47:04 2016
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../tf.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tf.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TF[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
       4,    3,    3,    3, 0x05,

 // slots: signature, parameters, type, tag, flags
      15,    3,    3,    3, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_TF[] = {
    "TF\0\0tfChange()\0pointsUpdated()\0"
};

const QMetaObject TF::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_TF,
      qt_meta_data_TF, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TF::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TF::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TF::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TF))
        return static_cast<void*>(const_cast< TF*>(this));
    return QWidget::qt_metacast(_clname);
}

int TF::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: tfChange(); break;
        case 1: pointsUpdated(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void TF::tfChange()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
