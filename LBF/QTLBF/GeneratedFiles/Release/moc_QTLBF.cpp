/****************************************************************************
** Meta object code from reading C++ file 'QTLBF.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../QTLBF.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'QTLBF.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_QTLBF_t {
    QByteArrayData data[13];
    char stringdata0[168];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_QTLBF_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_QTLBF_t qt_meta_stringdata_QTLBF = {
    {
QT_MOC_LITERAL(0, 0, 5), // "QTLBF"
QT_MOC_LITERAL(1, 6, 11), // "LoadCascade"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 19), // "LoadCascadeFromFile"
QT_MOC_LITERAL(4, 39, 13), // "UnloadCascade"
QT_MOC_LITERAL(5, 53, 15), // "CheatPreProcess"
QT_MOC_LITERAL(6, 69, 10), // "PreProcess"
QT_MOC_LITERAL(7, 80, 21), // "onLoadAlignThreadDone"
QT_MOC_LITERAL(8, 102, 6), // "isdone"
QT_MOC_LITERAL(9, 109, 21), // "onUpdateProcessButton"
QT_MOC_LITERAL(10, 131, 10), // "canProcess"
QT_MOC_LITERAL(11, 142, 19), // "onUpdateProgressBar"
QT_MOC_LITERAL(12, 162, 5) // "value"

    },
    "QTLBF\0LoadCascade\0\0LoadCascadeFromFile\0"
    "UnloadCascade\0CheatPreProcess\0PreProcess\0"
    "onLoadAlignThreadDone\0isdone\0"
    "onUpdateProcessButton\0canProcess\0"
    "onUpdateProgressBar\0value"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_QTLBF[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    0,   55,    2, 0x0a /* Public */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x0a /* Public */,
       7,    1,   59,    2, 0x0a /* Public */,
       9,    1,   62,    2, 0x0a /* Public */,
      11,    1,   65,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    8,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, QMetaType::Int,   12,

       0        // eod
};

void QTLBF::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        QTLBF *_t = static_cast<QTLBF *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->LoadCascade(); break;
        case 1: _t->LoadCascadeFromFile(); break;
        case 2: _t->UnloadCascade(); break;
        case 3: _t->CheatPreProcess(); break;
        case 4: _t->PreProcess(); break;
        case 5: _t->onLoadAlignThreadDone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->onUpdateProcessButton((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->onUpdateProgressBar((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject QTLBF::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_QTLBF.data,
      qt_meta_data_QTLBF,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *QTLBF::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *QTLBF::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_QTLBF.stringdata0))
        return static_cast<void*>(const_cast< QTLBF*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int QTLBF::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
