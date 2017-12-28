/****************************************************************************
** Meta object code from reading C++ file 'PaintPanel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.9.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../PaintPanel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PaintPanel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.9.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PaintPanel_t {
    QByteArrayData data[16];
    char stringdata0[154];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PaintPanel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PaintPanel_t qt_meta_stringdata_PaintPanel = {
    {
QT_MOC_LITERAL(0, 0, 10), // "PaintPanel"
QT_MOC_LITERAL(1, 11, 11), // "frameChange"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 6), // "size_t"
QT_MOC_LITERAL(4, 31, 3), // "idx"
QT_MOC_LITERAL(5, 35, 15), // "onUpdateEyeData"
QT_MOC_LITERAL(6, 51, 6), // "shapes"
QT_MOC_LITERAL(7, 58, 18), // "onUpdateWorkingDir"
QT_MOC_LITERAL(8, 77, 3), // "dir"
QT_MOC_LITERAL(9, 81, 16), // "onUpdateOpenFile"
QT_MOC_LITERAL(10, 98, 13), // "SaveEyeShapes"
QT_MOC_LITERAL(11, 112, 15), // "onChangeShowEye"
QT_MOC_LITERAL(12, 128, 1), // "l"
QT_MOC_LITERAL(13, 130, 1), // "r"
QT_MOC_LITERAL(14, 132, 14), // "onChangeStatus"
QT_MOC_LITERAL(15, 147, 6) // "isDrag"

    },
    "PaintPanel\0frameChange\0\0size_t\0idx\0"
    "onUpdateEyeData\0shapes\0onUpdateWorkingDir\0"
    "dir\0onUpdateOpenFile\0SaveEyeShapes\0"
    "onChangeShowEye\0l\0r\0onChangeStatus\0"
    "isDrag"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PaintPanel[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   52,    2, 0x0a /* Public */,
       7,    1,   55,    2, 0x0a /* Public */,
       9,    0,   58,    2, 0x0a /* Public */,
      10,    0,   59,    2, 0x0a /* Public */,
      11,    2,   60,    2, 0x0a /* Public */,
      14,    1,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::VoidStar,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool,   12,   13,
    QMetaType::Void, QMetaType::Bool,   15,

       0        // eod
};

void PaintPanel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        PaintPanel *_t = static_cast<PaintPanel *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->frameChange((*reinterpret_cast< size_t(*)>(_a[1]))); break;
        case 1: _t->onUpdateEyeData((*reinterpret_cast< void*(*)>(_a[1]))); break;
        case 2: _t->onUpdateWorkingDir((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->onUpdateOpenFile(); break;
        case 4: _t->SaveEyeShapes(); break;
        case 5: _t->onChangeShowEye((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 6: _t->onChangeStatus((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (PaintPanel::*_t)(size_t );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&PaintPanel::frameChange)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject PaintPanel::staticMetaObject = {
    { &QOpenGLWidget::staticMetaObject, qt_meta_stringdata_PaintPanel.data,
      qt_meta_data_PaintPanel,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *PaintPanel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PaintPanel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PaintPanel.stringdata0))
        return static_cast<void*>(const_cast< PaintPanel*>(this));
    return QOpenGLWidget::qt_metacast(_clname);
}

int PaintPanel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
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
void PaintPanel::frameChange(size_t _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
