/****************************************************************************
** Meta object code from reading C++ file 'headerfilewindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/headerfilewindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'headerfilewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_HeaderFileWindow_t {
    QByteArrayData data[11];
    char stringdata[266];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_HeaderFileWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_HeaderFileWindow_t qt_meta_stringdata_HeaderFileWindow = {
    {
QT_MOC_LITERAL(0, 0, 16),
QT_MOC_LITERAL(1, 17, 29),
QT_MOC_LITERAL(2, 47, 0),
QT_MOC_LITERAL(3, 48, 31),
QT_MOC_LITERAL(4, 80, 35),
QT_MOC_LITERAL(5, 116, 21),
QT_MOC_LITERAL(6, 138, 30),
QT_MOC_LITERAL(7, 169, 28),
QT_MOC_LITERAL(8, 198, 30),
QT_MOC_LITERAL(9, 229, 19),
QT_MOC_LITERAL(10, 249, 15)
    },
    "HeaderFileWindow\0timingParametersButtonClicked\0"
    "\0geometryParametersButtonClicked\0"
    "targetPositionSettingsButtonClicked\0"
    "bearingsButtonClicked\0"
    "weatherParametersButtonClicked\0"
    "pulseParametersButtonClicked\0"
    "quicklookSettingsButtonClicked\0"
    "cancelButtonClicked\0okButtonClicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HeaderFileWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   59,    2, 0x08,
       3,    0,   60,    2, 0x08,
       4,    0,   61,    2, 0x08,
       5,    0,   62,    2, 0x08,
       6,    0,   63,    2, 0x08,
       7,    0,   64,    2, 0x08,
       8,    0,   65,    2, 0x08,
       9,    0,   66,    2, 0x08,
      10,    0,   67,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void HeaderFileWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HeaderFileWindow *_t = static_cast<HeaderFileWindow *>(_o);
        switch (_id) {
        case 0: _t->timingParametersButtonClicked(); break;
        case 1: _t->geometryParametersButtonClicked(); break;
        case 2: _t->targetPositionSettingsButtonClicked(); break;
        case 3: _t->bearingsButtonClicked(); break;
        case 4: _t->weatherParametersButtonClicked(); break;
        case 5: _t->pulseParametersButtonClicked(); break;
        case 6: _t->quicklookSettingsButtonClicked(); break;
        case 7: _t->cancelButtonClicked(); break;
        case 8: _t->okButtonClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject HeaderFileWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_HeaderFileWindow.data,
      qt_meta_data_HeaderFileWindow,  qt_static_metacall, 0, 0}
};


const QMetaObject *HeaderFileWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HeaderFileWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HeaderFileWindow.stringdata))
        return static_cast<void*>(const_cast< HeaderFileWindow*>(this));
    return QDialog::qt_metacast(_clname);
}

int HeaderFileWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
