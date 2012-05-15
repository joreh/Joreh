/****************************************************************************
** Meta object code from reading C++ file 'Connection.h'
**
** Created: Mon May 14 03:32:48 2012
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Connection/Connection.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Connection.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_Connection[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: signature, parameters, type, tag, flags
      16,   12,   11,   11, 0x05,
      52,   45,   11,   11, 0x05,

 // slots: signature, parameters, type, tag, flags
      82,   11,   11,   11, 0x08,
      98,   11,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_Connection[] = {
    "Connection\0\0msg\0messageReceived(std::string)\0"
    "client\0handleConnection(QTcpSocket*)\0"
    "newConnection()\0readyRead()\0"
};

const QMetaObject Connection::staticMetaObject = {
    { &QTcpServer::staticMetaObject, qt_meta_stringdata_Connection,
      qt_meta_data_Connection, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &Connection::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *Connection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *Connection::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_Connection))
        return static_cast<void*>(const_cast< Connection*>(this));
    return QTcpServer::qt_metacast(_clname);
}

int Connection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTcpServer::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: messageReceived((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 1: handleConnection((*reinterpret_cast< QTcpSocket*(*)>(_a[1]))); break;
        case 2: newConnection(); break;
        case 3: readyRead(); break;
        default: ;
        }
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void Connection::messageReceived(std::string _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Connection::handleConnection(QTcpSocket * _t1)
{
    void *_a[] = { 0, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
