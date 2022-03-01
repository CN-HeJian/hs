/****************************************************************************
** Meta object code from reading C++ file 'getMessage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../task/getMessage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'getMessage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GetMessageW_t {
    QByteArrayData data[10];
    char stringdata0[161];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GetMessageW_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GetMessageW_t qt_meta_stringdata_GetMessageW = {
    {
QT_MOC_LITERAL(0, 0, 11), // "GetMessageW"
QT_MOC_LITERAL(1, 12, 32), // "MachineDataTimeUpdate_GetMessage"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 25), // "waveDataUpdate_getMessage"
QT_MOC_LITERAL(4, 72, 12), // "restart_getM"
QT_MOC_LITERAL(5, 85, 19), // "getInjectionMessage"
QT_MOC_LITERAL(6, 105, 21), // "MachineDataTimeUpdate"
QT_MOC_LITERAL(7, 127, 18), // "addOneCmdIntoQueue"
QT_MOC_LITERAL(8, 146, 6), // "string"
QT_MOC_LITERAL(9, 153, 7) // "restart"

    },
    "GetMessageW\0MachineDataTimeUpdate_GetMessage\0"
    "\0waveDataUpdate_getMessage\0restart_getM\0"
    "getInjectionMessage\0MachineDataTimeUpdate\0"
    "addOneCmdIntoQueue\0string\0restart"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GetMessageW[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x06 /* Public */,
       3,    2,   54,    2, 0x06 /* Public */,
       4,    1,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   62,    2, 0x08 /* Private */,
       6,    2,   63,    2, 0x08 /* Private */,
       7,    1,   68,    2, 0x08 /* Private */,
       9,    1,   71,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    2,    2,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void GetMessageW::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GetMessageW *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->MachineDataTimeUpdate_GetMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->waveDataUpdate_getMessage((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->restart_getM((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->getInjectionMessage(); break;
        case 4: _t->MachineDataTimeUpdate((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->addOneCmdIntoQueue((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 6: _t->restart((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GetMessageW::*)(QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GetMessageW::MachineDataTimeUpdate_GetMessage)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GetMessageW::*)(QString , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GetMessageW::waveDataUpdate_getMessage)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GetMessageW::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GetMessageW::restart_getM)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject GetMessageW::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_GetMessageW.data,
    qt_meta_data_GetMessageW,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GetMessageW::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GetMessageW::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GetMessageW.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GetMessageW::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void GetMessageW::MachineDataTimeUpdate_GetMessage(QString _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GetMessageW::waveDataUpdate_getMessage(QString _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GetMessageW::restart_getM(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
