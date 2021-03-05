/****************************************************************************
** Meta object code from reading C++ file 'FriendInfoWidgetWeb.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../mainwindow/contact/friend/FriendInfoWidgetWeb.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FriendInfoWidgetWeb.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__FriendInfoWidgetWeb_t {
    QByteArrayData data[9];
    char stringdata0[147];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__FriendInfoWidgetWeb_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__FriendInfoWidgetWeb_t qt_meta_stringdata_ui__FriendInfoWidgetWeb = {
    {
QT_MOC_LITERAL(0, 0, 23), // "ui::FriendInfoWidgetWeb"
QT_MOC_LITERAL(1, 24, 23), // "signalSerGetOrgUserInfo"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 34), // "std::vector<data::OrgAndUserI..."
QT_MOC_LITERAL(4, 84, 13), // "slotStartChat"
QT_MOC_LITERAL(5, 98, 19), // "onSerGetOrgUserInfo"
QT_MOC_LITERAL(6, 118, 4), // "code"
QT_MOC_LITERAL(7, 123, 5), // "users"
QT_MOC_LITERAL(8, 129, 17) // "onSerShowMoreInfo"

    },
    "ui::FriendInfoWidgetWeb\0signalSerGetOrgUserInfo\0"
    "\0std::vector<data::OrgAndUserInfo>&\0"
    "slotStartChat\0onSerGetOrgUserInfo\0"
    "code\0users\0onSerShowMoreInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__FriendInfoWidgetWeb[] = {

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
       1,    2,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   39,    2, 0x09 /* Protected */,
       5,    2,   40,    2, 0x09 /* Protected */,
       8,    0,   45,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3,    6,    7,
    QMetaType::Void,

       0        // eod
};

void ui::FriendInfoWidgetWeb::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FriendInfoWidgetWeb *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerGetOrgUserInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<data::OrgAndUserInfo>(*)>(_a[2]))); break;
        case 1: _t->slotStartChat(); break;
        case 2: _t->onSerGetOrgUserInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<data::OrgAndUserInfo>(*)>(_a[2]))); break;
        case 3: _t->onSerShowMoreInfo(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FriendInfoWidgetWeb::*)(int , std::vector<data::OrgAndUserInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FriendInfoWidgetWeb::signalSerGetOrgUserInfo)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::FriendInfoWidgetWeb::staticMetaObject = { {
    QMetaObject::SuperData::link<EnterpriseInfoWidget::staticMetaObject>(),
    qt_meta_stringdata_ui__FriendInfoWidgetWeb.data,
    qt_meta_data_ui__FriendInfoWidgetWeb,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::FriendInfoWidgetWeb::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::FriendInfoWidgetWeb::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__FriendInfoWidgetWeb.stringdata0))
        return static_cast<void*>(this);
    return EnterpriseInfoWidget::qt_metacast(_clname);
}

int ui::FriendInfoWidgetWeb::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = EnterpriseInfoWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ui::FriendInfoWidgetWeb::signalSerGetOrgUserInfo(int _t1, std::vector<data::OrgAndUserInfo> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
