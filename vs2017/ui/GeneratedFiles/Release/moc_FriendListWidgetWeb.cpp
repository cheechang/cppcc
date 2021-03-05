/****************************************************************************
** Meta object code from reading C++ file 'FriendListWidgetWeb.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/contact/friend/FriendListWidgetWeb.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FriendListWidgetWeb.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__FriendListWidgetWeb_t {
    QByteArrayData data[12];
    char stringdata0[153];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__FriendListWidgetWeb_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__FriendListWidgetWeb_t qt_meta_stringdata_ui__FriendListWidgetWeb = {
    {
QT_MOC_LITERAL(0, 0, 23), // "ui::FriendListWidgetWeb"
QT_MOC_LITERAL(1, 24, 19), // "showContactInfoPage"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 13), // "data::Contact"
QT_MOC_LITERAL(4, 59, 13), // "onItemClicked"
QT_MOC_LITERAL(5, 73, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(6, 90, 4), // "item"
QT_MOC_LITERAL(7, 95, 14), // "onMySelectItem"
QT_MOC_LITERAL(8, 110, 6), // "itemid"
QT_MOC_LITERAL(9, 117, 12), // "onAppSortRsp"
QT_MOC_LITERAL(10, 130, 14), // "QNetworkReply*"
QT_MOC_LITERAL(11, 145, 7) // "preplay"

    },
    "ui::FriendListWidgetWeb\0showContactInfoPage\0"
    "\0data::Contact\0onItemClicked\0"
    "QListWidgetItem*\0item\0onMySelectItem\0"
    "itemid\0onAppSortRsp\0QNetworkReply*\0"
    "preplay"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__FriendListWidgetWeb[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   37,    2, 0x0a /* Public */,
       7,    1,   40,    2, 0x0a /* Public */,
       9,    1,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, 0x80000000 | 10,   11,

       0        // eod
};

void ui::FriendListWidgetWeb::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FriendListWidgetWeb *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showContactInfoPage((*reinterpret_cast< data::Contact(*)>(_a[1]))); break;
        case 1: _t->onItemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 2: _t->onMySelectItem((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onAppSortRsp((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FriendListWidgetWeb::*)(data::Contact );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FriendListWidgetWeb::showContactInfoPage)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::FriendListWidgetWeb::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ui__FriendListWidgetWeb.data,
    qt_meta_data_ui__FriendListWidgetWeb,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::FriendListWidgetWeb::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::FriendListWidgetWeb::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__FriendListWidgetWeb.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ui::FriendListWidgetWeb::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ui::FriendListWidgetWeb::showContactInfoPage(data::Contact _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
