/****************************************************************************
** Meta object code from reading C++ file 'ListWidgetItem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/chat/chatList/ListWidgetItem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ListWidgetItem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__ListWidgetItem_t {
    QByteArrayData data[8];
    char stringdata0[81];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__ListWidgetItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__ListWidgetItem_t qt_meta_stringdata_ui__ListWidgetItem = {
    {
QT_MOC_LITERAL(0, 0, 18), // "ui::ListWidgetItem"
QT_MOC_LITERAL(1, 19, 13), // "signalDelItem"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 5), // "int64"
QT_MOC_LITERAL(4, 40, 8), // "targetId"
QT_MOC_LITERAL(5, 49, 13), // "signalClicked"
QT_MOC_LITERAL(6, 63, 9), // "onClicked"
QT_MOC_LITERAL(7, 73, 7) // "isClick"

    },
    "ui::ListWidgetItem\0signalDelItem\0\0"
    "int64\0targetId\0signalClicked\0onClicked\0"
    "isClick"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__ListWidgetItem[] = {

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
       1,    1,   29,    2, 0x06 /* Public */,
       5,    1,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    7,

       0        // eod
};

void ui::ListWidgetItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ListWidgetItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalDelItem((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 1: _t->signalClicked((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 2: _t->onClicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ListWidgetItem::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ListWidgetItem::signalDelItem)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ListWidgetItem::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ListWidgetItem::signalClicked)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::ListWidgetItem::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ui__ListWidgetItem.data,
    qt_meta_data_ui__ListWidgetItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::ListWidgetItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::ListWidgetItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__ListWidgetItem.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ui::ListWidgetItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void ui::ListWidgetItem::signalDelItem(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::ListWidgetItem::signalClicked(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
