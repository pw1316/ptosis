/****************************************************************************
** Meta object code from reading C++ file 'Worker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Worker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Worker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LoadAlignWorker_t {
    QByteArrayData data[5];
    char stringdata0[34];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LoadAlignWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LoadAlignWorker_t qt_meta_stringdata_LoadAlignWorker = {
    {
QT_MOC_LITERAL(0, 0, 15), // "LoadAlignWorker"
QT_MOC_LITERAL(1, 16, 4), // "Done"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 7), // "_isdone"
QT_MOC_LITERAL(4, 30, 3) // "Run"

    },
    "LoadAlignWorker\0Done\0\0_isdone\0Run"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LoadAlignWorker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void LoadAlignWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        LoadAlignWorker *_t = static_cast<LoadAlignWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Done((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->Run(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (LoadAlignWorker::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&LoadAlignWorker::Done)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject LoadAlignWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_LoadAlignWorker.data,
      qt_meta_data_LoadAlignWorker,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *LoadAlignWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LoadAlignWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LoadAlignWorker.stringdata0))
        return static_cast<void*>(const_cast< LoadAlignWorker*>(this));
    return QObject::qt_metacast(_clname);
}

int LoadAlignWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void LoadAlignWorker::Done(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_AlignWorker_t {
    QByteArrayData data[7];
    char stringdata0[50];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AlignWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AlignWorker_t qt_meta_stringdata_AlignWorker = {
    {
QT_MOC_LITERAL(0, 0, 11), // "AlignWorker"
QT_MOC_LITERAL(1, 12, 4), // "Done"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 6), // "isSucc"
QT_MOC_LITERAL(4, 25, 14), // "UpdateProgress"
QT_MOC_LITERAL(5, 40, 5), // "value"
QT_MOC_LITERAL(6, 46, 3) // "Run"

    },
    "AlignWorker\0Done\0\0isSucc\0UpdateProgress\0"
    "value\0Run"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AlignWorker[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    1,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int,    5,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void AlignWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        AlignWorker *_t = static_cast<AlignWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Done((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->UpdateProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->Run(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (AlignWorker::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AlignWorker::Done)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (AlignWorker::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&AlignWorker::UpdateProgress)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject AlignWorker::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_AlignWorker.data,
      qt_meta_data_AlignWorker,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *AlignWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AlignWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AlignWorker.stringdata0))
        return static_cast<void*>(const_cast< AlignWorker*>(this));
    return QObject::qt_metacast(_clname);
}

int AlignWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void AlignWorker::Done(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void AlignWorker::UpdateProgress(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
