/****************************************************************************
** Meta object code from reading C++ file 'CustomProtocolBaseTcp.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../HsCollector/HscUI/service/CustomProtocolBaseTcp.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CustomProtocolBaseTcp.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CustomProtocolBaseTcp_t {
    QByteArrayData data[7];
    char stringdata0[101];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CustomProtocolBaseTcp_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CustomProtocolBaseTcp_t qt_meta_stringdata_CustomProtocolBaseTcp = {
    {
QT_MOC_LITERAL(0, 0, 21), // "CustomProtocolBaseTcp"
QT_MOC_LITERAL(1, 22, 25), // "receiveResponceFromServer"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 3), // "buf"
QT_MOC_LITERAL(4, 53, 9), // "ReadError"
QT_MOC_LITERAL(5, 63, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(6, 92, 8) // "ReadData"

    },
    "CustomProtocolBaseTcp\0receiveResponceFromServer\0"
    "\0buf\0ReadError\0QAbstractSocket::SocketError\0"
    "ReadData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CustomProtocolBaseTcp[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   32,    2, 0x08 /* Private */,
       6,    0,   35,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void,

       0        // eod
};

void CustomProtocolBaseTcp::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CustomProtocolBaseTcp *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->receiveResponceFromServer((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 1: _t->ReadError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 2: _t->ReadData(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CustomProtocolBaseTcp::*)(QByteArray );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CustomProtocolBaseTcp::receiveResponceFromServer)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CustomProtocolBaseTcp::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_CustomProtocolBaseTcp.data,
    qt_meta_data_CustomProtocolBaseTcp,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CustomProtocolBaseTcp::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CustomProtocolBaseTcp::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CustomProtocolBaseTcp.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int CustomProtocolBaseTcp::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CustomProtocolBaseTcp::receiveResponceFromServer(QByteArray _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
