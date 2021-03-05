/****************************************************************************
** Meta object code from reading C++ file 'MessageTopWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/chat/MessageTopWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MessageTopWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__MsgListWidgetItem_t {
    QByteArrayData data[6];
    char stringdata0[94];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__MsgListWidgetItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__MsgListWidgetItem_t qt_meta_stringdata_ui__MsgListWidgetItem = {
    {
QT_MOC_LITERAL(0, 0, 21), // "ui::MsgListWidgetItem"
QT_MOC_LITERAL(1, 22, 21), // "signalSerCancelTopMsg"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 23), // "data::ZxTopInformation&"
QT_MOC_LITERAL(4, 69, 5), // "m_msg"
QT_MOC_LITERAL(5, 75, 18) // "onCancelTopMessage"

    },
    "ui::MsgListWidgetItem\0signalSerCancelTopMsg\0"
    "\0data::ZxTopInformation&\0m_msg\0"
    "onCancelTopMessage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__MsgListWidgetItem[] = {

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
       5,    0,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void ui::MsgListWidgetItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MsgListWidgetItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerCancelTopMsg((*reinterpret_cast< data::ZxTopInformation(*)>(_a[1]))); break;
        case 1: _t->onCancelTopMessage(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MsgListWidgetItem::*)(data::ZxTopInformation & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MsgListWidgetItem::signalSerCancelTopMsg)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::MsgListWidgetItem::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ui__MsgListWidgetItem.data,
    qt_meta_data_ui__MsgListWidgetItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::MsgListWidgetItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::MsgListWidgetItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__MsgListWidgetItem.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ui::MsgListWidgetItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void ui::MsgListWidgetItem::signalSerCancelTopMsg(data::ZxTopInformation & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_ui__MessageTopWidget_t {
    QByteArrayData data[14];
    char stringdata0[179];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__MessageTopWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__MessageTopWidget_t qt_meta_stringdata_ui__MessageTopWidget = {
    {
QT_MOC_LITERAL(0, 0, 20), // "ui::MessageTopWidget"
QT_MOC_LITERAL(1, 21, 21), // "signalSerCancelTopMsg"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 21), // "signalSercppccTopInfo"
QT_MOC_LITERAL(4, 66, 11), // "std::string"
QT_MOC_LITERAL(5, 78, 5), // "int64"
QT_MOC_LITERAL(6, 84, 2), // "id"
QT_MOC_LITERAL(7, 87, 17), // "onSercppccTopInfo"
QT_MOC_LITERAL(8, 105, 4), // "code"
QT_MOC_LITERAL(9, 110, 8), // "strError"
QT_MOC_LITERAL(10, 119, 17), // "onSerCancelTopMsg"
QT_MOC_LITERAL(11, 137, 23), // "data::ZxTopInformation&"
QT_MOC_LITERAL(12, 161, 9), // "cancelMsg"
QT_MOC_LITERAL(13, 171, 7) // "onClose"

    },
    "ui::MessageTopWidget\0signalSerCancelTopMsg\0"
    "\0signalSercppccTopInfo\0std::string\0"
    "int64\0id\0onSercppccTopInfo\0code\0"
    "strError\0onSerCancelTopMsg\0"
    "data::ZxTopInformation&\0cancelMsg\0"
    "onClose"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__MessageTopWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    3,   40,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    3,   47,    2, 0x0a /* Public */,
      10,    1,   54,    2, 0x0a /* Public */,
      13,    0,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4, 0x80000000 | 5,    2,    2,    6,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4, 0x80000000 | 5,    8,    9,    6,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,

       0        // eod
};

void ui::MessageTopWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MessageTopWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerCancelTopMsg(); break;
        case 1: _t->signalSercppccTopInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3]))); break;
        case 2: _t->onSercppccTopInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3]))); break;
        case 3: _t->onSerCancelTopMsg((*reinterpret_cast< data::ZxTopInformation(*)>(_a[1]))); break;
        case 4: _t->onClose(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MessageTopWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MessageTopWidget::signalSerCancelTopMsg)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MessageTopWidget::*)(int , const std::string & , int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MessageTopWidget::signalSercppccTopInfo)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::MessageTopWidget::staticMetaObject = { {
    &BaseWindow::staticMetaObject,
    qt_meta_stringdata_ui__MessageTopWidget.data,
    qt_meta_data_ui__MessageTopWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::MessageTopWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::MessageTopWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__MessageTopWidget.stringdata0))
        return static_cast<void*>(this);
    return BaseWindow::qt_metacast(_clname);
}

int ui::MessageTopWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseWindow::qt_metacall(_c, _id, _a);
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
void ui::MessageTopWidget::signalSerCancelTopMsg()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ui::MessageTopWidget::signalSercppccTopInfo(int _t1, const std::string & _t2, int64 _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
