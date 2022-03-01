/****************************************************************************
** Meta object code from reading C++ file 'HscMachineAnalysis.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../HsCollector/HscUI/machineAnalysis/HscMachineAnalysis.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HscMachineAnalysis.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HscMachineAnalysis_t {
    QByteArrayData data[14];
    char stringdata0[160];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HscMachineAnalysis_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HscMachineAnalysis_t qt_meta_stringdata_HscMachineAnalysis = {
    {
QT_MOC_LITERAL(0, 0, 18), // "HscMachineAnalysis"
QT_MOC_LITERAL(1, 19, 20), // "setCurrentPlotWidget"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 5), // "index"
QT_MOC_LITERAL(4, 47, 15), // "receiveResponce"
QT_MOC_LITERAL(5, 63, 6), // "buffer"
QT_MOC_LITERAL(6, 70, 19), // "setSelectPushButton"
QT_MOC_LITERAL(7, 90, 16), // "setLastShowIndex"
QT_MOC_LITERAL(8, 107, 9), // "onTimeOut"
QT_MOC_LITERAL(9, 117, 5), // "Alarm"
QT_MOC_LITERAL(10, 123, 6), // "string"
QT_MOC_LITERAL(11, 130, 10), // "detectMold"
QT_MOC_LITERAL(12, 141, 14), // "SingleMachine*"
QT_MOC_LITERAL(13, 156, 3) // "cur"

    },
    "HscMachineAnalysis\0setCurrentPlotWidget\0"
    "\0index\0receiveResponce\0buffer\0"
    "setSelectPushButton\0setLastShowIndex\0"
    "onTimeOut\0Alarm\0string\0detectMold\0"
    "SingleMachine*\0cur"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HscMachineAnalysis[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x08 /* Private */,
       4,    1,   52,    2, 0x08 /* Private */,
       6,    1,   55,    2, 0x08 /* Private */,
       7,    1,   58,    2, 0x08 /* Private */,
       8,    0,   61,    2, 0x08 /* Private */,
       9,    1,   62,    2, 0x08 /* Private */,
      11,    1,   65,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QByteArray,    5,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,    2,
    QMetaType::Void, 0x80000000 | 12,   13,

       0        // eod
};

void HscMachineAnalysis::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HscMachineAnalysis *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->setCurrentPlotWidget((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->receiveResponce((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: _t->setSelectPushButton((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setLastShowIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->onTimeOut(); break;
        case 5: _t->Alarm((*reinterpret_cast< string(*)>(_a[1]))); break;
        case 6: _t->detectMold((*reinterpret_cast< SingleMachine*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< SingleMachine* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject HscMachineAnalysis::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_HscMachineAnalysis.data,
    qt_meta_data_HscMachineAnalysis,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *HscMachineAnalysis::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HscMachineAnalysis::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HscMachineAnalysis.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int HscMachineAnalysis::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
