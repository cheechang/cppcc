/****************************************************************************
** Meta object code from reading C++ file 'pictextmessageitem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../mainwindow/chat/bubble/pictextmessageitem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pictextmessageitem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PicTextDelegate_t {
    QByteArrayData data[11];
    char stringdata0[106];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PicTextDelegate_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PicTextDelegate_t qt_meta_stringdata_PicTextDelegate = {
    {
QT_MOC_LITERAL(0, 0, 15), // "PicTextDelegate"
QT_MOC_LITERAL(1, 16, 20), // "signalSerDownLoadImg"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 3), // "err"
QT_MOC_LITERAL(4, 42, 11), // "std::string"
QT_MOC_LITERAL(5, 54, 7), // "imgname"
QT_MOC_LITERAL(6, 62, 5), // "int64"
QT_MOC_LITERAL(7, 68, 8), // "targetid"
QT_MOC_LITERAL(8, 77, 7), // "openUrl"
QT_MOC_LITERAL(9, 85, 3), // "url"
QT_MOC_LITERAL(10, 89, 16) // "onSerDownLoadImg"

    },
    "PicTextDelegate\0signalSerDownLoadImg\0"
    "\0err\0std::string\0imgname\0int64\0targetid\0"
    "openUrl\0url\0onSerDownLoadImg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PicTextDelegate[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   29,    2, 0x06 /* Public */,
       8,    1,   36,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    3,   39,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4, 0x80000000 | 6,    3,    5,    7,
    QMetaType::Void, 0x80000000 | 4,    9,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4, 0x80000000 | 6,    3,    5,    7,

       0        // eod
};

void PicTextDelegate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PicTextDelegate *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerDownLoadImg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3]))); break;
        case 1: _t->openUrl((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 2: _t->onSerDownLoadImg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PicTextDelegate::*)(int , const std::string & , int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PicTextDelegate::signalSerDownLoadImg)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PicTextDelegate::*)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PicTextDelegate::openUrl)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PicTextDelegate::staticMetaObject = { {
    QMetaObject::SuperData::link<ui::TWidget::staticMetaObject>(),
    qt_meta_stringdata_PicTextDelegate.data,
    qt_meta_data_PicTextDelegate,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PicTextDelegate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PicTextDelegate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PicTextDelegate.stringdata0))
        return static_cast<void*>(this);
    return ui::TWidget::qt_metacast(_clname);
}

int PicTextDelegate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ui::TWidget::qt_metacall(_c, _id, _a);
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
void PicTextDelegate::signalSerDownLoadImg(int _t1, const std::string & _t2, int64 _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void PicTextDelegate::openUrl(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_PicTextMessageItem_t {
    QByteArrayData data[8];
    char stringdata0[80];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PicTextMessageItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PicTextMessageItem_t qt_meta_stringdata_PicTextMessageItem = {
    {
QT_MOC_LITERAL(0, 0, 18), // "PicTextMessageItem"
QT_MOC_LITERAL(1, 19, 7), // "openUrl"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 11), // "std::string"
QT_MOC_LITERAL(4, 40, 3), // "url"
QT_MOC_LITERAL(5, 44, 13), // "onItemClicked"
QT_MOC_LITERAL(6, 58, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(7, 75, 4) // "item"

    },
    "PicTextMessageItem\0openUrl\0\0std::string\0"
    "url\0onItemClicked\0QListWidgetItem*\0"
    "item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PicTextMessageItem[] = {

 // content:
       8,       // revision
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
       5,    1,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void PicTextMessageItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PicTextMessageItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->openUrl((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 1: _t->onItemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PicTextMessageItem::*)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PicTextMessageItem::openUrl)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PicTextMessageItem::staticMetaObject = { {
    QMetaObject::SuperData::link<ui::TWidget::staticMetaObject>(),
    qt_meta_stringdata_PicTextMessageItem.data,
    qt_meta_data_PicTextMessageItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PicTextMessageItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PicTextMessageItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PicTextMessageItem.stringdata0))
        return static_cast<void*>(this);
    return ui::TWidget::qt_metacast(_clname);
}

int PicTextMessageItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ui::TWidget::qt_metacall(_c, _id, _a);
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
void PicTextMessageItem::openUrl(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
