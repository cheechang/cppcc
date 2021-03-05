/****************************************************************************
** Meta object code from reading C++ file 'AvatarArea.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../mainwindow/AvatarArea.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AvatarArea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__AvatarArea_t {
    QByteArrayData data[24];
    char stringdata0[298];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__AvatarArea_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__AvatarArea_t qt_meta_stringdata_ui__AvatarArea = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ui::AvatarArea"
QT_MOC_LITERAL(1, 15, 5), // "click"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 3), // "pos"
QT_MOC_LITERAL(4, 26, 19), // "signalSerHeadUpdate"
QT_MOC_LITERAL(5, 46, 5), // "int64"
QT_MOC_LITERAL(6, 52, 11), // "std::string"
QT_MOC_LITERAL(7, 64, 22), // "signalSerSetUserVerify"
QT_MOC_LITERAL(8, 87, 3), // "err"
QT_MOC_LITERAL(9, 91, 21), // "signalSerNetChangedCb"
QT_MOC_LITERAL(10, 113, 18), // "signalSerReLoginCb"
QT_MOC_LITERAL(11, 132, 20), // "signalSerUserAccount"
QT_MOC_LITERAL(12, 153, 18), // "data::AccountInfo&"
QT_MOC_LITERAL(13, 172, 16), // "onSerUserAccount"
QT_MOC_LITERAL(14, 189, 7), // "account"
QT_MOC_LITERAL(15, 197, 15), // "onSerHeadUpdate"
QT_MOC_LITERAL(16, 213, 8), // "targetID"
QT_MOC_LITERAL(17, 222, 6), // "avatar"
QT_MOC_LITERAL(18, 229, 18), // "onSerSetUserVerify"
QT_MOC_LITERAL(19, 248, 17), // "onSerNetChangedCb"
QT_MOC_LITERAL(20, 266, 4), // "flag"
QT_MOC_LITERAL(21, 271, 14), // "onSerReLoginCb"
QT_MOC_LITERAL(22, 286, 4), // "code"
QT_MOC_LITERAL(23, 291, 6) // "userId"

    },
    "ui::AvatarArea\0click\0\0pos\0signalSerHeadUpdate\0"
    "int64\0std::string\0signalSerSetUserVerify\0"
    "err\0signalSerNetChangedCb\0signalSerReLoginCb\0"
    "signalSerUserAccount\0data::AccountInfo&\0"
    "onSerUserAccount\0account\0onSerHeadUpdate\0"
    "targetID\0avatar\0onSerSetUserVerify\0"
    "onSerNetChangedCb\0flag\0onSerReLoginCb\0"
    "code\0userId"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__AvatarArea[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    2,   72,    2, 0x06 /* Public */,
       7,    1,   77,    2, 0x06 /* Public */,
       9,    1,   80,    2, 0x06 /* Public */,
      10,    2,   83,    2, 0x06 /* Public */,
      11,    1,   88,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    1,   91,    2, 0x0a /* Public */,
      15,    2,   94,    2, 0x0a /* Public */,
      18,    1,   99,    2, 0x0a /* Public */,
      19,    1,  102,    2, 0x0a /* Public */,
      21,    2,  105,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPoint,    3,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 6,    2,    2,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 5,    2,    2,
    QMetaType::Void, 0x80000000 | 12,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 12,   14,
    QMetaType::Void, 0x80000000 | 5, 0x80000000 | 6,   16,   17,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 5,   22,   23,

       0        // eod
};

void ui::AvatarArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AvatarArea *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->click((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 1: _t->signalSerHeadUpdate((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2]))); break;
        case 2: _t->signalSerSetUserVerify((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->signalSerNetChangedCb((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->signalSerReLoginCb((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2]))); break;
        case 5: _t->signalSerUserAccount((*reinterpret_cast< data::AccountInfo(*)>(_a[1]))); break;
        case 6: _t->onSerUserAccount((*reinterpret_cast< data::AccountInfo(*)>(_a[1]))); break;
        case 7: _t->onSerHeadUpdate((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2]))); break;
        case 8: _t->onSerSetUserVerify((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->onSerNetChangedCb((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->onSerReLoginCb((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AvatarArea::*)(QPoint );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AvatarArea::click)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AvatarArea::*)(int64 , const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AvatarArea::signalSerHeadUpdate)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AvatarArea::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AvatarArea::signalSerSetUserVerify)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (AvatarArea::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AvatarArea::signalSerNetChangedCb)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (AvatarArea::*)(int , int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AvatarArea::signalSerReLoginCb)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (AvatarArea::*)(data::AccountInfo & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AvatarArea::signalSerUserAccount)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::AvatarArea::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ui__AvatarArea.data,
    qt_meta_data_ui__AvatarArea,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::AvatarArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::AvatarArea::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__AvatarArea.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ui::AvatarArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void ui::AvatarArea::click(QPoint _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::AvatarArea::signalSerHeadUpdate(int64 _t1, const std::string & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::AvatarArea::signalSerSetUserVerify(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ui::AvatarArea::signalSerNetChangedCb(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ui::AvatarArea::signalSerReLoginCb(int _t1, int64 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ui::AvatarArea::signalSerUserAccount(data::AccountInfo & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
