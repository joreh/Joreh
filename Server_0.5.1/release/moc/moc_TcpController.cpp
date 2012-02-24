/****************************************************************************
** Meta object code from reading C++ file 'TcpController.h'
**
** Created: Mon Nov 14 14:15:13 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../CommunicationController/TcpController.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TcpController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_TcpController[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      20,   15,   14,   14, 0x08,
      61,   52,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_TcpController[] = {
    "TcpController\0\0indx\0forwardClientDisconnected(uint)\0"
    "indx,msg\0forwardMessageReceived(uint,std::string)\0"
};

const QMetaObject TcpController::staticMetaObject = {
    { &CommunicationController::staticMetaObject, qt_meta_stringdata_TcpController,
      qt_meta_data_TcpController, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &TcpController::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *TcpController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *TcpController::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_TcpController))
        return static_cast<void*>(const_cast< TcpController*>(this));
    return CommunicationController::qt_metacast(_clname);
}

int TcpController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = CommunicationController::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: forwardClientDisconnected((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 1: forwardMessageReceived((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
