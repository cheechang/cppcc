/****************************************************************************
** Meta object code from reading C++ file 'CardMessageWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../mainwindow/chat/bubble/CardMessageWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CardMessageWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_CardMessageWidget_t {
    QByteArrayData data[11];
    char stringdata0[144];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CardMessageWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CardMessageWidget_t qt_meta_stringdata_CardMessageWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "CardMessageWidget"
QT_MOC_LITERAL(1, 18, 20), // "signalSerGetUserInfo"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 15), // "data::UserData&"
QT_MOC_LITERAL(4, 56, 18), // "showUserInfoWidget"
QT_MOC_LITERAL(5, 75, 5), // "int64"
QT_MOC_LITERAL(6, 81, 21), // "signalSerShowUserInfo"
QT_MOC_LITERAL(7, 103, 16), // "onSerGetUserInfo"
QT_MOC_LITERAL(8, 120, 4), // "code"
QT_MOC_LITERAL(9, 125, 4), // "user"
QT_MOC_LITERAL(10, 130, 13) // "onHeadClicked"

    },
    "CardMessageWidget\0signalSerGetUserInfo\0"
    "\0data::UserData&\0showUserInfoWidget\0"
    "int64\0signalSerShowUserInfo\0"
    "onSerGetUserInfo\0code\0user\0onHeadClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CardMessageWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,
       4,    3,   44,    2, 0x06 /* Public */,
       6,    3,   51,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    2,   58,    2, 0x09 /* Protected */,
      10,    0,   63,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3,    2,    2,
    QMetaType::Void, 0x80000000 | 5, QMetaType::QString, QMetaType::QString,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 5, QMetaType::QString, QMetaType::QString,    2,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3,    8,    9,
    QMetaType::Void,

       0        // eod
};

void CardMessageWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CardMessageWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerGetUserInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::UserData(*)>(_a[2]))); break;
        case 1: _t->showUserInfoWidget((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 2: _t->signalSerShowUserInfo((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 3: _t->onSerGetUserInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::UserData(*)>(_a[2]))); break;
        case 4: _t->onHeadClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CardMessageWidget::*)(int , data::UserData & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CardMessageWidget::signalSerGetUserInfo)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CardMessageWidget::*)(int64 , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CardMessageWidget::showUserInfoWidget)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CardMessageWidget::*)(int64 , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CardMessageWidget::signalSerShowUserInfo)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CardMessageWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractMessageWidget::staticMetaObject>(),
    qt_meta_stringdata_CardMessageWidget.data,
    qt_meta_data_CardMessageWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CardMessageWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CardMessageWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CardMessageWidget.stringdata0))
        return static_cast<void*>(this);
    return AbstractMessageWidget::qt_metacast(_clname);
}

int CardMessageWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractMessageWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void CardMessageWidget::signalSerGetUserInfo(int _t1, data::UserData & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void CardMessageWidget::showUserInfoWidget(int64 _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void CardMessageWidget::signalSerShowUserInfo(int64 _t1, QString _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
