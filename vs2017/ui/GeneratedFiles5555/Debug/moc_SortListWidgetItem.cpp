/****************************************************************************
** Meta object code from reading C++ file 'SortListWidgetItem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../controls/SortListWidgetItem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SortListWidgetItem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_uicontrols__SortListWidgetItem_t {
    QByteArrayData data[11];
    char stringdata0[151];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_uicontrols__SortListWidgetItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_uicontrols__SortListWidgetItem_t qt_meta_stringdata_uicontrols__SortListWidgetItem = {
    {
QT_MOC_LITERAL(0, 0, 30), // "uicontrols::SortListWidgetItem"
QT_MOC_LITERAL(1, 31, 12), // "signalRemove"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 5), // "int64"
QT_MOC_LITERAL(4, 51, 2), // "id"
QT_MOC_LITERAL(5, 54, 20), // "signalCheckedChanged"
QT_MOC_LITERAL(6, 75, 17), // "signalHeadClicked"
QT_MOC_LITERAL(7, 93, 15), // "onDelBtnClicked"
QT_MOC_LITERAL(8, 109, 22), // "onCheckBoxStateChanged"
QT_MOC_LITERAL(9, 132, 15), // "onAvatarClicked"
QT_MOC_LITERAL(10, 148, 2) // "pt"

    },
    "uicontrols::SortListWidgetItem\0"
    "signalRemove\0\0int64\0id\0signalCheckedChanged\0"
    "signalHeadClicked\0onDelBtnClicked\0"
    "onCheckBoxStateChanged\0onAvatarClicked\0"
    "pt"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_uicontrols__SortListWidgetItem[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       5,    1,   47,    2, 0x06 /* Public */,
       6,    1,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   53,    2, 0x09 /* Protected */,
       8,    0,   54,    2, 0x09 /* Protected */,
       9,    1,   55,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   10,

       0        // eod
};

void uicontrols::SortListWidgetItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SortListWidgetItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalRemove((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 1: _t->signalCheckedChanged((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 2: _t->signalHeadClicked((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 3: _t->onDelBtnClicked(); break;
        case 4: _t->onCheckBoxStateChanged(); break;
        case 5: _t->onAvatarClicked((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SortListWidgetItem::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SortListWidgetItem::signalRemove)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SortListWidgetItem::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SortListWidgetItem::signalCheckedChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SortListWidgetItem::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SortListWidgetItem::signalHeadClicked)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject uicontrols::SortListWidgetItem::staticMetaObject = { {
    QMetaObject::SuperData::link<ui::TWidget::staticMetaObject>(),
    qt_meta_stringdata_uicontrols__SortListWidgetItem.data,
    qt_meta_data_uicontrols__SortListWidgetItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *uicontrols::SortListWidgetItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *uicontrols::SortListWidgetItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_uicontrols__SortListWidgetItem.stringdata0))
        return static_cast<void*>(this);
    return ui::TWidget::qt_metacast(_clname);
}

int uicontrols::SortListWidgetItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ui::TWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void uicontrols::SortListWidgetItem::signalRemove(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void uicontrols::SortListWidgetItem::signalCheckedChanged(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void uicontrols::SortListWidgetItem::signalHeadClicked(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
struct qt_meta_stringdata_uicontrols__SortListWidgetTeamItem_t {
    QByteArrayData data[1];
    char stringdata0[35];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_uicontrols__SortListWidgetTeamItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_uicontrols__SortListWidgetTeamItem_t qt_meta_stringdata_uicontrols__SortListWidgetTeamItem = {
    {
QT_MOC_LITERAL(0, 0, 34) // "uicontrols::SortListWidgetTea..."

    },
    "uicontrols::SortListWidgetTeamItem"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_uicontrols__SortListWidgetTeamItem[] = {

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

void uicontrols::SortListWidgetTeamItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject uicontrols::SortListWidgetTeamItem::staticMetaObject = { {
    QMetaObject::SuperData::link<ui::TWidget::staticMetaObject>(),
    qt_meta_stringdata_uicontrols__SortListWidgetTeamItem.data,
    qt_meta_data_uicontrols__SortListWidgetTeamItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *uicontrols::SortListWidgetTeamItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *uicontrols::SortListWidgetTeamItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_uicontrols__SortListWidgetTeamItem.stringdata0))
        return static_cast<void*>(this);
    return ui::TWidget::qt_metacast(_clname);
}

int uicontrols::SortListWidgetTeamItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ui::TWidget::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
