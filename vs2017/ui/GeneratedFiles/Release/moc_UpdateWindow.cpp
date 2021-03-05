/****************************************************************************
** Meta object code from reading C++ file 'UpdateWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../updatewindow/UpdateWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UpdateWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__UpdateWindow_t {
    QByteArrayData data[26];
    char stringdata0[381];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__UpdateWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__UpdateWindow_t qt_meta_stringdata_ui__UpdateWindow = {
    {
QT_MOC_LITERAL(0, 0, 16), // "ui::UpdateWindow"
QT_MOC_LITERAL(1, 17, 16), // "updateNewVersion"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 25), // "signalSerUpdateInfoNotice"
QT_MOC_LITERAL(4, 61, 17), // "data::UpdateInfo&"
QT_MOC_LITERAL(5, 79, 4), // "info"
QT_MOC_LITERAL(6, 84, 23), // "signalSerDownloadUpdate"
QT_MOC_LITERAL(7, 108, 23), // "signalSerCancelDownLoad"
QT_MOC_LITERAL(8, 132, 23), // "signalSerProgressUpdate"
QT_MOC_LITERAL(9, 156, 5), // "int32"
QT_MOC_LITERAL(10, 162, 11), // "std::string"
QT_MOC_LITERAL(11, 174, 5), // "int64"
QT_MOC_LITERAL(12, 180, 16), // "signalExitClient"
QT_MOC_LITERAL(13, 197, 9), // "isrestart"
QT_MOC_LITERAL(14, 207, 8), // "onUpdate"
QT_MOC_LITERAL(15, 216, 21), // "onSerUpdateInfoNotice"
QT_MOC_LITERAL(16, 238, 19), // "onSerDownloadUpdate"
QT_MOC_LITERAL(17, 258, 3), // "err"
QT_MOC_LITERAL(18, 262, 19), // "onSerProgressUpdate"
QT_MOC_LITERAL(19, 282, 5), // "extra"
QT_MOC_LITERAL(20, 288, 8), // "progress"
QT_MOC_LITERAL(21, 297, 9), // "uilocalid"
QT_MOC_LITERAL(22, 307, 23), // "onTimerShowUpdateWindow"
QT_MOC_LITERAL(23, 331, 16), // "onCancelDownLoad"
QT_MOC_LITERAL(24, 348, 19), // "onSerCancelDownLoad"
QT_MOC_LITERAL(25, 368, 12) // "onRestartApp"

    },
    "ui::UpdateWindow\0updateNewVersion\0\0"
    "signalSerUpdateInfoNotice\0data::UpdateInfo&\0"
    "info\0signalSerDownloadUpdate\0"
    "signalSerCancelDownLoad\0signalSerProgressUpdate\0"
    "int32\0std::string\0int64\0signalExitClient\0"
    "isrestart\0onUpdate\0onSerUpdateInfoNotice\0"
    "onSerDownloadUpdate\0err\0onSerProgressUpdate\0"
    "extra\0progress\0uilocalid\0"
    "onTimerShowUpdateWindow\0onCancelDownLoad\0"
    "onSerCancelDownLoad\0onRestartApp"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__UpdateWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,
       3,    1,   85,    2, 0x06 /* Public */,
       6,    1,   88,    2, 0x06 /* Public */,
       7,    1,   91,    2, 0x06 /* Public */,
       8,    4,   94,    2, 0x06 /* Public */,
      12,    1,  103,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    0,  106,    2, 0x09 /* Protected */,
      15,    1,  107,    2, 0x09 /* Protected */,
      16,    1,  110,    2, 0x09 /* Protected */,
      18,    4,  113,    2, 0x09 /* Protected */,
      22,    0,  122,    2, 0x09 /* Protected */,
      23,    0,  123,    2, 0x09 /* Protected */,
      24,    1,  124,    2, 0x09 /* Protected */,
      25,    0,  127,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 9, 0x80000000 | 10, 0x80000000 | 11,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Bool,   13,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 9, 0x80000000 | 10, 0x80000000 | 11,   19,   20,    5,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void,

       0        // eod
};

void ui::UpdateWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UpdateWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->updateNewVersion(); break;
        case 1: _t->signalSerUpdateInfoNotice((*reinterpret_cast< data::UpdateInfo(*)>(_a[1]))); break;
        case 2: _t->signalSerDownloadUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->signalSerCancelDownLoad((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->signalSerProgressUpdate((*reinterpret_cast< int32(*)>(_a[1])),(*reinterpret_cast< int32(*)>(_a[2])),(*reinterpret_cast< const std::string(*)>(_a[3])),(*reinterpret_cast< int64(*)>(_a[4]))); break;
        case 5: _t->signalExitClient((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->onUpdate(); break;
        case 7: _t->onSerUpdateInfoNotice((*reinterpret_cast< data::UpdateInfo(*)>(_a[1]))); break;
        case 8: _t->onSerDownloadUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->onSerProgressUpdate((*reinterpret_cast< int32(*)>(_a[1])),(*reinterpret_cast< int32(*)>(_a[2])),(*reinterpret_cast< const std::string(*)>(_a[3])),(*reinterpret_cast< int64(*)>(_a[4]))); break;
        case 10: _t->onTimerShowUpdateWindow(); break;
        case 11: _t->onCancelDownLoad(); break;
        case 12: _t->onSerCancelDownLoad((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->onRestartApp(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (UpdateWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UpdateWindow::updateNewVersion)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (UpdateWindow::*)(data::UpdateInfo & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UpdateWindow::signalSerUpdateInfoNotice)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (UpdateWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UpdateWindow::signalSerDownloadUpdate)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (UpdateWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UpdateWindow::signalSerCancelDownLoad)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (UpdateWindow::*)(int32 , int32 , const std::string & , int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UpdateWindow::signalSerProgressUpdate)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (UpdateWindow::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UpdateWindow::signalExitClient)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::UpdateWindow::staticMetaObject = { {
    &BaseDialog::staticMetaObject,
    qt_meta_stringdata_ui__UpdateWindow.data,
    qt_meta_data_ui__UpdateWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::UpdateWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::UpdateWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__UpdateWindow.stringdata0))
        return static_cast<void*>(this);
    return BaseDialog::qt_metacast(_clname);
}

int ui::UpdateWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void ui::UpdateWindow::updateNewVersion()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ui::UpdateWindow::signalSerUpdateInfoNotice(data::UpdateInfo & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::UpdateWindow::signalSerDownloadUpdate(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ui::UpdateWindow::signalSerCancelDownLoad(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ui::UpdateWindow::signalSerProgressUpdate(int32 _t1, int32 _t2, const std::string & _t3, int64 _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ui::UpdateWindow::signalExitClient(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
