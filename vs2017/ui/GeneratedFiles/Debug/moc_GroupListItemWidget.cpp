/****************************************************************************
** Meta object code from reading C++ file 'GroupListItemWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/contact/group/GroupListItemWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GroupListItemWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__GroupListItemWidget_t {
    QByteArrayData data[8];
    char stringdata0[87];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__GroupListItemWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__GroupListItemWidget_t qt_meta_stringdata_ui__GroupListItemWidget = {
    {
QT_MOC_LITERAL(0, 0, 23), // "ui::GroupListItemWidget"
QT_MOC_LITERAL(1, 24, 18), // "showGroupInforPage"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 5), // "int64"
QT_MOC_LITERAL(4, 50, 7), // "groupId"
QT_MOC_LITERAL(5, 58, 11), // "headClicked"
QT_MOC_LITERAL(6, 70, 2), // "id"
QT_MOC_LITERAL(7, 73, 13) // "onHeadClicked"

    },
    "ui::GroupListItemWidget\0showGroupInforPage\0"
    "\0int64\0groupId\0headClicked\0id\0"
    "onHeadClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__GroupListItemWidget[] = {

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
       7,    0,   35,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    6,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void ui::GroupListItemWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GroupListItemWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showGroupInforPage((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 1: _t->headClicked((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 2: _t->onHeadClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GroupListItemWidget::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupListItemWidget::showGroupInforPage)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GroupListItemWidget::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupListItemWidget::headClicked)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::GroupListItemWidget::staticMetaObject = { {
    &TWidget::staticMetaObject,
    qt_meta_stringdata_ui__GroupListItemWidget.data,
    qt_meta_data_ui__GroupListItemWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::GroupListItemWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::GroupListItemWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__GroupListItemWidget.stringdata0))
        return static_cast<void*>(this);
    return TWidget::qt_metacast(_clname);
}

int ui::GroupListItemWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TWidget::qt_metacall(_c, _id, _a);
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
void ui::GroupListItemWidget::showGroupInforPage(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::GroupListItemWidget::headClicked(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
