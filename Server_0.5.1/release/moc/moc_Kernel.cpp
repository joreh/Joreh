/****************************************************************************
** Meta object code from reading C++ file 'Kernel.h'
**
** Created: Thu Feb 2 15:37:20 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Kernel/Kernel.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Kernel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Kernel[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      17,    8,    7,    7, 0x08,
      56,    8,    7,    7, 0x08,
     102,   97,    7,    7, 0x08,
     123,   97,    7,    7, 0x08,
     146,   97,    7,    7, 0x08,
     170,   97,    7,    7, 0x08,
     196,    7,    7,    7, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Kernel[] = {
    "Kernel\0\0indx,msg\0"
    "agentMessageReceived(uint,std::string)\0"
    "monitorMessageReceived(uint,std::string)\0"
    "indx\0agentConnected(uint)\0"
    "monitorConnected(uint)\0agentDisconnected(uint)\0"
    "monitorDisconnected(uint)\0newCycle()\0"
};

const QMetaObject Kernel::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Kernel,
      qt_meta_data_Kernel, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Kernel::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Kernel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Kernel::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Kernel))
        return static_cast<void*>(const_cast< Kernel*>(this));
    return QObject::qt_metacast(_clname);
}

int Kernel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: agentMessageReceived((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2]))); break;
        case 1: monitorMessageReceived((*reinterpret_cast< uint(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2]))); break;
        case 2: agentConnected((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 3: monitorConnected((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 4: agentDisconnected((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 5: monitorDisconnected((*reinterpret_cast< uint(*)>(_a[1]))); break;
        case 6: newCycle(); break;
        default: ;
        }
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
