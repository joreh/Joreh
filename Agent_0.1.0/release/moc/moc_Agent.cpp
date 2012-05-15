/****************************************************************************
** Meta object code from reading C++ file 'Agent.h'
**
** Created: Fri May 11 01:42:14 2012
**      by: The Qt Meta Object Compiler version 63 (Qt 4.8.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Base/Agent.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Agent.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Agent[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      11,    7,    6,    6, 0x0a,
      40,    6,    6,    6, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_Agent[] = {
    "Agent\0\0msg\0messageReceived(std::string)\0"
    "disconnected()\0"
};

void Agent::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        Agent *_t = static_cast<Agent *>(_o);
        switch (_id) {
        case 0: _t->messageReceived((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 1: _t->disconnected(); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData Agent::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject Agent::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Agent,
      qt_meta_data_Agent, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Agent::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Agent::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Agent::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Agent))
        return static_cast<void*>(const_cast< Agent*>(this));
    return QObject::qt_metacast(_clname);
}

int Agent::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
