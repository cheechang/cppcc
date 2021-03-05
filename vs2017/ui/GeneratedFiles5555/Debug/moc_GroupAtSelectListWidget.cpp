/****************************************************************************
** Meta object code from reading C++ file 'GroupAtSelectListWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../mainwindow/chat/GroupAtSelectListWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GroupAtSelectListWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__GroupAtWidgetItem_t {
    QByteArrayData data[5];
    char stringdata0[40];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__GroupAtWidgetItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__GroupAtWidgetItem_t qt_meta_stringdata_ui__GroupAtWidgetItem = {
    {
QT_MOC_LITERAL(0, 0, 21), // "ui::GroupAtWidgetItem"
QT_MOC_LITERAL(1, 22, 7), // "clicked"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 5), // "int64"
QT_MOC_LITERAL(4, 37, 2) // "id"

    },
    "ui::GroupAtWidgetItem\0clicked\0\0int64\0"
    "id"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__GroupAtWidgetItem[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void ui::GroupAtWidgetItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GroupAtWidgetItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clicked((*reinterpret_cast< int64(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GroupAtWidgetItem::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupAtWidgetItem::clicked)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::GroupAtWidgetItem::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ui__GroupAtWidgetItem.data,
    qt_meta_data_ui__GroupAtWidgetItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::GroupAtWidgetItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::GroupAtWidgetItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__GroupAtWidgetItem.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ui::GroupAtWidgetItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void ui::GroupAtWidgetItem::clicked(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_ui__GroupAtSelectListWidget_t {
    QByteArrayData data[21];
    char stringdata0[248];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__GroupAtSelectListWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__GroupAtSelectListWidget_t qt_meta_stringdata_ui__GroupAtSelectListWidget = {
    {
QT_MOC_LITERAL(0, 0, 27), // "ui::GroupAtSelectListWidget"
QT_MOC_LITERAL(1, 28, 21), // "signalSerGetGroupMems"
QT_MOC_LITERAL(2, 50, 0), // ""
QT_MOC_LITERAL(3, 51, 7), // "regText"
QT_MOC_LITERAL(4, 59, 39), // "std::vector<CSharedPtr<data::..."
QT_MOC_LITERAL(5, 99, 5), // "int64"
QT_MOC_LITERAL(6, 105, 7), // "localId"
QT_MOC_LITERAL(7, 113, 7), // "memInfo"
QT_MOC_LITERAL(8, 121, 4), // "path"
QT_MOC_LITERAL(9, 126, 10), // "dataFinish"
QT_MOC_LITERAL(10, 137, 17), // "onSerGetGroupMems"
QT_MOC_LITERAL(11, 155, 4), // "code"
QT_MOC_LITERAL(12, 160, 4), // "mems"
QT_MOC_LITERAL(13, 165, 13), // "onItemClicked"
QT_MOC_LITERAL(14, 179, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(15, 196, 4), // "item"
QT_MOC_LITERAL(16, 201, 2), // "id"
QT_MOC_LITERAL(17, 204, 12), // "onKeyPressed"
QT_MOC_LITERAL(18, 217, 7), // "QEvent*"
QT_MOC_LITERAL(19, 225, 5), // "event"
QT_MOC_LITERAL(20, 231, 16) // "onLazyLoadMember"

    },
    "ui::GroupAtSelectListWidget\0"
    "signalSerGetGroupMems\0\0regText\0"
    "std::vector<CSharedPtr<data::Member> >&\0"
    "int64\0localId\0memInfo\0path\0dataFinish\0"
    "onSerGetGroupMems\0code\0mems\0onItemClicked\0"
    "QListWidgetItem*\0item\0id\0onKeyPressed\0"
    "QEvent*\0event\0onLazyLoadMember"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__GroupAtSelectListWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   54,    2, 0x06 /* Public */,
       7,    1,   63,    2, 0x06 /* Public */,
       9,    0,   66,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    4,   67,    2, 0x09 /* Protected */,
      13,    1,   76,    2, 0x09 /* Protected */,
      13,    1,   79,    2, 0x09 /* Protected */,
      17,    1,   82,    2, 0x09 /* Protected */,
      20,    0,   85,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int, 0x80000000 | 4, 0x80000000 | 5,    3,    2,    2,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int, 0x80000000 | 4, 0x80000000 | 5,    3,   11,   12,    6,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, 0x80000000 | 5,   16,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void,

       0        // eod
};

void ui::GroupAtSelectListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GroupAtSelectListWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerGetGroupMems((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< std::vector<CSharedPtr<data::Member> >(*)>(_a[3])),(*reinterpret_cast< int64(*)>(_a[4]))); break;
        case 1: _t->memInfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->dataFinish(); break;
        case 3: _t->onSerGetGroupMems((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< std::vector<CSharedPtr<data::Member> >(*)>(_a[3])),(*reinterpret_cast< int64(*)>(_a[4]))); break;
        case 4: _t->onItemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 5: _t->onItemClicked((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 6: _t->onKeyPressed((*reinterpret_cast< QEvent*(*)>(_a[1]))); break;
        case 7: _t->onLazyLoadMember(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GroupAtSelectListWidget::*)(QString , int , std::vector<CSharedPtr<data::Member>> & , int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupAtSelectListWidget::signalSerGetGroupMems)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GroupAtSelectListWidget::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupAtSelectListWidget::memInfo)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GroupAtSelectListWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupAtSelectListWidget::dataFinish)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::GroupAtSelectListWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ui__GroupAtSelectListWidget.data,
    qt_meta_data_ui__GroupAtSelectListWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::GroupAtSelectListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::GroupAtSelectListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__GroupAtSelectListWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ui::GroupAtSelectListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void ui::GroupAtSelectListWidget::signalSerGetGroupMems(QString _t1, int _t2, std::vector<CSharedPtr<data::Member>> & _t3, int64 _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::GroupAtSelectListWidget::memInfo(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::GroupAtSelectListWidget::dataFinish()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
