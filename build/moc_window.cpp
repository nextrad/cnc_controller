/****************************************************************************
** Meta object code from reading C++ file 'window.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.2.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/window.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.2.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Window_t {
    QByteArrayData data[17];
    char stringdata[340];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    offsetof(qt_meta_stringdata_Window_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData) \
    )
static const qt_meta_stringdata_Window_t qt_meta_stringdata_Window = {
    {
QT_MOC_LITERAL(0, 0, 6),
QT_MOC_LITERAL(1, 7, 27),
QT_MOC_LITERAL(2, 35, 0),
QT_MOC_LITERAL(3, 36, 18),
QT_MOC_LITERAL(4, 55, 14),
QT_MOC_LITERAL(5, 70, 13),
QT_MOC_LITERAL(6, 84, 32),
QT_MOC_LITERAL(7, 117, 27),
QT_MOC_LITERAL(8, 145, 12),
QT_MOC_LITERAL(9, 158, 33),
QT_MOC_LITERAL(10, 192, 28),
QT_MOC_LITERAL(11, 221, 15),
QT_MOC_LITERAL(12, 237, 20),
QT_MOC_LITERAL(13, 258, 11),
QT_MOC_LITERAL(14, 270, 22),
QT_MOC_LITERAL(15, 293, 24),
QT_MOC_LITERAL(16, 318, 20)
    },
    "Window\0connectionTestButtonClicked\0\0"
    "updateCountDownLCD\0startRecording\0"
    "stopRecording\0abortAudioRecordingButtonClicked\0"
    "editHeaderFileButtonClicked\0openMainMenu\0"
    "receiveNodePositionsButtonClicked\0"
    "receiveBearingsButtonClicked\0"
    "goButtonClicked\0goLaterButtonClicked\0"
    "closeServer\0showVideoButtonClicked\0"
    "runNextlookButtonClicked\0abortGoButtonClicked\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Window[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x08,
       3,    0,   90,    2, 0x08,
       4,    0,   91,    2, 0x08,
       5,    0,   92,    2, 0x08,
       6,    0,   93,    2, 0x08,
       7,    0,   94,    2, 0x08,
       8,    0,   95,    2, 0x08,
       9,    0,   96,    2, 0x08,
      10,    0,   97,    2, 0x08,
      11,    0,   98,    2, 0x08,
      12,    0,   99,    2, 0x08,
      13,    0,  100,    2, 0x08,
      14,    0,  101,    2, 0x08,
      15,    0,  102,    2, 0x08,
      16,    0,  103,    2, 0x08,

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
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void Window::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Window *_t = static_cast<Window *>(_o);
        switch (_id) {
        case 0: _t->connectionTestButtonClicked(); break;
        case 1: _t->updateCountDownLCD(); break;
        case 2: _t->startRecording(); break;
        case 3: _t->stopRecording(); break;
        case 4: _t->abortAudioRecordingButtonClicked(); break;
        case 5: _t->editHeaderFileButtonClicked(); break;
        case 6: _t->openMainMenu(); break;
        case 7: _t->receiveNodePositionsButtonClicked(); break;
        case 8: _t->receiveBearingsButtonClicked(); break;
        case 9: _t->goButtonClicked(); break;
        case 10: _t->goLaterButtonClicked(); break;
        case 11: _t->closeServer(); break;
        case 12: _t->showVideoButtonClicked(); break;
        case 13: _t->runNextlookButtonClicked(); break;
        case 14: _t->abortGoButtonClicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject Window::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_Window.data,
      qt_meta_data_Window,  qt_static_metacall, 0, 0}
};


const QMetaObject *Window::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Window::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Window.stringdata))
        return static_cast<void*>(const_cast< Window*>(this));
    return QWidget::qt_metacast(_clname);
}

int Window::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
