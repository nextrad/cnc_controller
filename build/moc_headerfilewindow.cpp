/****************************************************************************
** Meta object code from reading C++ file 'headerfilewindow.h'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.7)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../src/headerfilewindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'headerfilewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.7. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_HeaderFileWindow[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      18,   17,   17,   17, 0x08,
      50,   17,   17,   17, 0x08,
      84,   17,   17,   17, 0x08,
     122,   17,   17,   17, 0x08,
     146,   17,   17,   17, 0x08,
     179,   17,   17,   17, 0x08,
     210,   17,   17,   17, 0x08,
     243,   17,   17,   17, 0x08,
     265,   17,   17,   17, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_HeaderFileWindow[] = {
    "HeaderFileWindow\0\0timingParametersButtonClicked()\0"
    "geometryParametersButtonClicked()\0"
    "targetPositionSettingsButtonClicked()\0"
    "bearingsButtonClicked()\0"
    "weatherParametersButtonClicked()\0"
    "pulseParametersButtonClicked()\0"
    "quicklookSettingsButtonClicked()\0"
    "cancelButtonClicked()\0okButtonClicked()\0"
};

void HeaderFileWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
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

const QMetaObjectExtraData HeaderFileWindow::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject HeaderFileWindow::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_HeaderFileWindow,
      qt_meta_data_HeaderFileWindow, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &HeaderFileWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *HeaderFileWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *HeaderFileWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HeaderFileWindow))
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
    }
    return _id;
}
QT_END_MOC_NAMESPACE
