/****************************************************************************
** Meta object code from reading C++ file 'ContactTabWidgetArea.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/contact/ContactTabWidgetArea.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ContactTabWidgetArea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__ContactTabWidgetArea_t {
    QByteArrayData data[13];
    char stringdata0[182];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__ContactTabWidgetArea_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__ContactTabWidgetArea_t qt_meta_stringdata_ui__ContactTabWidgetArea = {
    {
QT_MOC_LITERAL(0, 0, 24), // "ui::ContactTabWidgetArea"
QT_MOC_LITERAL(1, 25, 9), // "startChat"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 27), // "CSharedPtr<data::ChatInfo>&"
QT_MOC_LITERAL(4, 64, 4), // "chat"
QT_MOC_LITERAL(5, 69, 19), // "showOrgUserInfoPage"
QT_MOC_LITERAL(6, 89, 20), // "data::OrgAndUserInfo"
QT_MOC_LITERAL(7, 110, 4), // "user"
QT_MOC_LITERAL(8, 115, 18), // "showGroupInforPage"
QT_MOC_LITERAL(9, 134, 5), // "int64"
QT_MOC_LITERAL(10, 140, 7), // "groupId"
QT_MOC_LITERAL(11, 148, 19), // "showContactInfoPage"
QT_MOC_LITERAL(12, 168, 13) // "data::Contact"

    },
    "ui::ContactTabWidgetArea\0startChat\0\0"
    "CSharedPtr<data::ChatInfo>&\0chat\0"
    "showOrgUserInfoPage\0data::OrgAndUserInfo\0"
    "user\0showGroupInforPage\0int64\0groupId\0"
    "showContactInfoPage\0data::Contact"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__ContactTabWidgetArea[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       5,    1,   37,    2, 0x06 /* Public */,
       8,    1,   40,    2, 0x06 /* Public */,
      11,    1,   43,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void, 0x80000000 | 12,    2,

       0        // eod
};

void ui::ContactTabWidgetArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ContactTabWidgetArea *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startChat((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        case 1: _t->showOrgUserInfoPage((*reinterpret_cast< data::OrgAndUserInfo(*)>(_a[1]))); break;
        case 2: _t->showGroupInforPage((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 3: _t->showContactInfoPage((*reinterpret_cast< data::Contact(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ContactTabWidgetArea::*)(CSharedPtr<data::ChatInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContactTabWidgetArea::startChat)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ContactTabWidgetArea::*)(data::OrgAndUserInfo );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContactTabWidgetArea::showOrgUserInfoPage)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ContactTabWidgetArea::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContactTabWidgetArea::showGroupInforPage)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ContactTabWidgetArea::*)(data::Contact );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContactTabWidgetArea::showContactInfoPage)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::ContactTabWidgetArea::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ui__ContactTabWidgetArea.data,
    qt_meta_data_ui__ContactTabWidgetArea,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::ContactTabWidgetArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::ContactTabWidgetArea::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__ContactTabWidgetArea.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ui::ContactTabWidgetArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ui::ContactTabWidgetArea::startChat(CSharedPtr<data::ChatInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::ContactTabWidgetArea::showOrgUserInfoPage(data::OrgAndUserInfo _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::ContactTabWidgetArea::showGroupInforPage(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ui::ContactTabWidgetArea::showContactInfoPage(data::Contact _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
