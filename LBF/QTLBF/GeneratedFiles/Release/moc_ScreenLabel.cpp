/****************************************************************************
** Meta object code from reading C++ file 'ScreenLabel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../ScreenLabel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ScreenLabel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ScreenLabel_t {
    QByteArrayData data[23];
    char stringdata0[268];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScreenLabel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScreenLabel_t qt_meta_stringdata_ScreenLabel = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ScreenLabel"
QT_MOC_LITERAL(1, 12, 19), // "UpdateProcessButton"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 10), // "canProcess"
QT_MOC_LITERAL(4, 44, 17), // "UpdateProgressBar"
QT_MOC_LITERAL(5, 62, 5), // "value"
QT_MOC_LITERAL(6, 68, 13), // "UpdateEyeData"
QT_MOC_LITERAL(7, 82, 6), // "shapes"
QT_MOC_LITERAL(8, 89, 16), // "UpdateWorkingDir"
QT_MOC_LITERAL(9, 106, 3), // "dir"
QT_MOC_LITERAL(10, 110, 14), // "UpdateOpenFile"
QT_MOC_LITERAL(11, 125, 8), // "OpenFile"
QT_MOC_LITERAL(12, 134, 14), // "SaveFaceShapes"
QT_MOC_LITERAL(13, 149, 7), // "Process"
QT_MOC_LITERAL(14, 157, 12), // "CheatProcess"
QT_MOC_LITERAL(15, 170, 16), // "onProgressUpdate"
QT_MOC_LITERAL(16, 187, 11), // "onAlignDone"
QT_MOC_LITERAL(17, 199, 6), // "isSucc"
QT_MOC_LITERAL(18, 206, 20), // "onSelectFrameChanged"
QT_MOC_LITERAL(19, 227, 6), // "size_t"
QT_MOC_LITERAL(20, 234, 3), // "idx"
QT_MOC_LITERAL(21, 238, 23), // "onShowPlotShapesChanged"
QT_MOC_LITERAL(22, 262, 5) // "state"

    },
    "ScreenLabel\0UpdateProcessButton\0\0"
    "canProcess\0UpdateProgressBar\0value\0"
    "UpdateEyeData\0shapes\0UpdateWorkingDir\0"
    "dir\0UpdateOpenFile\0OpenFile\0SaveFaceShapes\0"
    "Process\0CheatProcess\0onProgressUpdate\0"
    "onAlignDone\0isSucc\0onSelectFrameChanged\0"
    "size_t\0idx\0onShowPlotShapesChanged\0"
    "state"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScreenLabel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       4,    1,   82,    2, 0x06 /* Public */,
       6,    1,   85,    2, 0x06 /* Public */,
       8,    1,   88,    2, 0x06 /* Public */,
      10,    0,   91,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   92,    2, 0x0a /* Public */,
      12,    0,   93,    2, 0x0a /* Public */,
      13,    0,   94,    2, 0x0a /* Public */,
      14,    0,   95,    2, 0x0a /* Public */,
      15,    1,   96,    2, 0x0a /* Public */,
      16,    1,   99,    2, 0x0a /* Public */,
      18,    1,  102,    2, 0x0a /* Public */,
      21,    1,  105,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, QMetaType::VoidStar,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Bool,   17,
    QMetaType::Void, 0x80000000 | 19,   20,
    QMetaType::Void, QMetaType::Int,   22,

       0        // eod
};

void ScreenLabel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ScreenLabel *_t = static_cast<ScreenLabel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->UpdateProcessButton((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->UpdateProgressBar((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->UpdateEyeData((*reinterpret_cast< void*(*)>(_a[1]))); break;
        case 3: _t->UpdateWorkingDir((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->UpdateOpenFile(); break;
        case 5: _t->OpenFile(); break;
        case 6: _t->SaveFaceShapes(); break;
        case 7: _t->Process(); break;
        case 8: _t->CheatProcess(); break;
        case 9: _t->onProgressUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->onAlignDone((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 11: _t->onSelectFrameChanged((*reinterpret_cast< size_t(*)>(_a[1]))); break;
        case 12: _t->onShowPlotShapesChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ScreenLabel::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScreenLabel::UpdateProcessButton)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ScreenLabel::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScreenLabel::UpdateProgressBar)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ScreenLabel::*_t)(void * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScreenLabel::UpdateEyeData)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ScreenLabel::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScreenLabel::UpdateWorkingDir)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (ScreenLabel::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScreenLabel::UpdateOpenFile)) {
                *result = 4;
                return;
            }
        }
    }
}

const QMetaObject ScreenLabel::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_ScreenLabel.data,
      qt_meta_data_ScreenLabel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ScreenLabel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScreenLabel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ScreenLabel.stringdata0))
        return static_cast<void*>(const_cast< ScreenLabel*>(this));
    return QLabel::qt_metacast(_clname);
}

int ScreenLabel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void ScreenLabel::UpdateProcessButton(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ScreenLabel::UpdateProgressBar(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ScreenLabel::UpdateEyeData(void * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ScreenLabel::UpdateWorkingDir(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ScreenLabel::UpdateOpenFile()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
