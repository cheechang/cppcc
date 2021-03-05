/****************************************************************************
** Meta object code from reading C++ file 'CombineMessageWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../mainwindow/chat/bubble/CombineMessageWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CombineMessageWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CombineMessageItem_t {
    QByteArrayData data[1];
    char stringdata0[19];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CombineMessageItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CombineMessageItem_t qt_meta_stringdata_CombineMessageItem = {
    {
QT_MOC_LITERAL(0, 0, 18) // "CombineMessageItem"

    },
    "CombineMessageItem"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CombineMessageItem[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void CombineMessageItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject CombineMessageItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_CombineMessageItem.data,
    qt_meta_data_CombineMessageItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CombineMessageItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CombineMessageItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CombineMessageItem.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CombineMessageItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_CombineMessageWidgetPrivate_t {
    QByteArrayData data[8];
    char stringdata0[103];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CombineMessageWidgetPrivate_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CombineMessageWidgetPrivate_t qt_meta_stringdata_CombineMessageWidgetPrivate = {
    {
QT_MOC_LITERAL(0, 0, 27), // "CombineMessageWidgetPrivate"
QT_MOC_LITERAL(1, 28, 21), // "signalSerGetUserInfor"
QT_MOC_LITERAL(2, 50, 0), // ""
QT_MOC_LITERAL(3, 51, 15), // "data::UserData&"
QT_MOC_LITERAL(4, 67, 7), // "clicked"
QT_MOC_LITERAL(5, 75, 17), // "onSerGetUserInfor"
QT_MOC_LITERAL(6, 93, 4), // "code"
QT_MOC_LITERAL(7, 98, 4) // "data"

    },
    "CombineMessageWidgetPrivate\0"
    "signalSerGetUserInfor\0\0data::UserData&\0"
    "clicked\0onSerGetUserInfor\0code\0data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CombineMessageWidgetPrivate[] = {

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
       1,    2,   29,    2, 0x06 /* Public */,
       4,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    2,   35,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3,    2,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3,    6,    7,

       0        // eod
};

void CombineMessageWidgetPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CombineMessageWidgetPrivate *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerGetUserInfor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::UserData(*)>(_a[2]))); break;
        case 1: _t->clicked(); break;
        case 2: _t->onSerGetUserInfor((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::UserData(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CombineMessageWidgetPrivate::*)(int , data::UserData & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CombineMessageWidgetPrivate::signalSerGetUserInfor)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CombineMessageWidgetPrivate::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CombineMessageWidgetPrivate::clicked)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CombineMessageWidgetPrivate::staticMetaObject = { {
    QMetaObject::SuperData::link<ui::TWidget::staticMetaObject>(),
    qt_meta_stringdata_CombineMessageWidgetPrivate.data,
    qt_meta_data_CombineMessageWidgetPrivate,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CombineMessageWidgetPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CombineMessageWidgetPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CombineMessageWidgetPrivate.stringdata0))
        return static_cast<void*>(this);
    return ui::TWidget::qt_metacast(_clname);
}

int CombineMessageWidgetPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void CombineMessageWidgetPrivate::signalSerGetUserInfor(int _t1, data::UserData & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CombineMessageWidgetPrivate::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
struct qt_meta_stringdata_CombineMessageWidget_t {
    QByteArrayData data[3];
    char stringdata0[35];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CombineMessageWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CombineMessageWidget_t qt_meta_stringdata_CombineMessageWidget = {
    {
QT_MOC_LITERAL(0, 0, 20), // "CombineMessageWidget"
QT_MOC_LITERAL(1, 21, 12), // "onShowMsgWin"
QT_MOC_LITERAL(2, 34, 0) // ""

    },
    "CombineMessageWidget\0onShowMsgWin\0"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CombineMessageWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   19,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void CombineMessageWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CombineMessageWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onShowMsgWin(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject CombineMessageWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractMessageWidget::staticMetaObject>(),
    qt_meta_stringdata_CombineMessageWidget.data,
    qt_meta_data_CombineMessageWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CombineMessageWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CombineMessageWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CombineMessageWidget.stringdata0))
        return static_cast<void*>(this);
    return AbstractMessageWidget::qt_metacast(_clname);
}

int CombineMessageWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractMessageWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
