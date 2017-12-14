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
    QByteArrayData data[20];
    char stringdata[462];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_HeaderFileWindow_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_HeaderFileWindow_t qt_meta_stringdata_HeaderFileWindow = {
    {
QT_MOC_LITERAL(0, 0, 16),
QT_MOC_LITERAL(1, 17, 26),
QT_MOC_LITERAL(2, 44, 0),
QT_MOC_LITERAL(3, 45, 29),
QT_MOC_LITERAL(4, 75, 26),
QT_MOC_LITERAL(5, 102, 35),
QT_MOC_LITERAL(6, 138, 25),
QT_MOC_LITERAL(7, 164, 28),
QT_MOC_LITERAL(8, 193, 19),
QT_MOC_LITERAL(9, 213, 15),
QT_MOC_LITERAL(10, 229, 21),
QT_MOC_LITERAL(11, 251, 8),
QT_MOC_LITERAL(12, 260, 16),
QT_MOC_LITERAL(13, 277, 18),
QT_MOC_LITERAL(14, 296, 7),
QT_MOC_LITERAL(15, 304, 34),
QT_MOC_LITERAL(16, 339, 35),
QT_MOC_LITERAL(17, 375, 36),
QT_MOC_LITERAL(18, 412, 21),
QT_MOC_LITERAL(19, 434, 26)
    },
    "HeaderFileWindow\0calibSettingsButtonClicked\0"
    "\0exportParametersButtonClicked\0"
    "radarSettingsButtonClicked\0"
    "targetPositionSettingsButtonClicked\0"
    "polarisationButtonClicked\0"
    "pulseParametersButtonClicked\0"
    "cancelButtonClicked\0okButtonClicked\0"
    "RxSwitchButtonClicked\0switchID\0"
    "adcButtonClicked\0pulseButtonClicked\0"
    "pulseID\0exportPulseParametersButtonClicked\0"
    "exportSampleParametersButtonClicked\0"
    "environmentalParametersButtonClicked\0"
    "bearingsButtonClicked\0gpsParametersButtonClicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HeaderFileWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x08,
       3,    0,   95,    2, 0x08,
       4,    0,   96,    2, 0x08,
       5,    0,   97,    2, 0x08,
       6,    0,   98,    2, 0x08,
       7,    0,   99,    2, 0x08,
       8,    0,  100,    2, 0x08,
       9,    0,  101,    2, 0x08,
      10,    1,  102,    2, 0x08,
      12,    0,  105,    2, 0x08,
      13,    1,  106,    2, 0x08,
      15,    0,  109,    2, 0x08,
      16,    0,  110,    2, 0x08,
      17,    0,  111,    2, 0x08,
      18,    0,  112,    2, 0x08,
      19,    0,  113,    2, 0x08,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,
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
        case 0: _t->calibSettingsButtonClicked(); break;
        case 1: _t->exportParametersButtonClicked(); break;
        case 2: _t->radarSettingsButtonClicked(); break;
        case 3: _t->targetPositionSettingsButtonClicked(); break;
        case 4: _t->polarisationButtonClicked(); break;
        case 5: _t->pulseParametersButtonClicked(); break;
        case 6: _t->cancelButtonClicked(); break;
        case 7: _t->okButtonClicked(); break;
        case 8: _t->RxSwitchButtonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->adcButtonClicked(); break;
        case 10: _t->pulseButtonClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->exportPulseParametersButtonClicked(); break;
        case 12: _t->exportSampleParametersButtonClicked(); break;
        case 13: _t->environmentalParametersButtonClicked(); break;
        case 14: _t->bearingsButtonClicked(); break;
        case 15: _t->gpsParametersButtonClicked(); break;
        default: ;
        }
    }
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
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
