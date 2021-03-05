/****************************************************************************
** Meta object code from reading C++ file 'AppAccountList.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/contact/friend/AppAccountList.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AppAccountList.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__AppAccountList_t {
    QByteArrayData data[11];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__AppAccountList_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__AppAccountList_t qt_meta_stringdata_ui__AppAccountList = {
    {
QT_MOC_LITERAL(0, 0, 18), // "ui::AppAccountList"
QT_MOC_LITERAL(1, 19, 9), // "startChat"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 27), // "CSharedPtr<data::ChatInfo>&"
QT_MOC_LITERAL(4, 58, 20), // "signalSerRemoveAppCB"
QT_MOC_LITERAL(5, 79, 19), // "onItemDoubleClicked"
QT_MOC_LITERAL(6, 99, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(7, 116, 4), // "item"
QT_MOC_LITERAL(8, 121, 23), // "onDeleteMenuItemClicked"
QT_MOC_LITERAL(9, 145, 16), // "onSerRemoveAppCB"
QT_MOC_LITERAL(10, 162, 4) // "code"

    },
    "ui::AppAccountList\0startChat\0\0"
    "CSharedPtr<data::ChatInfo>&\0"
    "signalSerRemoveAppCB\0onItemDoubleClicked\0"
    "QListWidgetItem*\0item\0onDeleteMenuItemClicked\0"
    "onSerRemoveAppCB\0code"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__AppAccountList[] = {

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
       1,    1,   39,    2, 0x06 /* Public */,
       4,    1,   42,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   45,    2, 0x0a /* Public */,
       8,    0,   48,    2, 0x0a /* Public */,
       9,    1,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,

       0        // eod
};

void ui::AppAccountList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AppAccountList *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startChat((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        case 1: _t->signalSerRemoveAppCB((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->onItemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->onDeleteMenuItemClicked(); break;
        case 4: _t->onSerRemoveAppCB((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AppAccountList::*)(CSharedPtr<data::ChatInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppAccountList::startChat)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AppAccountList::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppAccountList::signalSerRemoveAppCB)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::AppAccountList::staticMetaObject = { {
    &TWidget::staticMetaObject,
    qt_meta_stringdata_ui__AppAccountList.data,
    qt_meta_data_ui__AppAccountList,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::AppAccountList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::AppAccountList::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__AppAccountList.stringdata0))
        return static_cast<void*>(this);
    return TWidget::qt_metacast(_clname);
}

int ui::AppAccountList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TWidget::qt_metacall(_c, _id, _a);
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
void ui::AppAccountList::startChat(CSharedPtr<data::ChatInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::AppAccountList::signalSerRemoveAppCB(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
