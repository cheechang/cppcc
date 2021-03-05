/****************************************************************************
** Meta object code from reading C++ file 'CreateGroupEnterprise.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/contact/createGroup/CreateGroupEnterprise.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CreateGroupEnterprise.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__DepartmentWidget_t {
    QByteArrayData data[1];
    char stringdata0[21];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__DepartmentWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__DepartmentWidget_t qt_meta_stringdata_ui__DepartmentWidget = {
    {
QT_MOC_LITERAL(0, 0, 20) // "ui::DepartmentWidget"

    },
    "ui::DepartmentWidget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__DepartmentWidget[] = {

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

void ui::DepartmentWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ui::DepartmentWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ui__DepartmentWidget.data,
    qt_meta_data_ui__DepartmentWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::DepartmentWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::DepartmentWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__DepartmentWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ui::DepartmentWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_ui__CreateGroupEnterprise_t {
    QByteArrayData data[11];
    char stringdata0[163];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__CreateGroupEnterprise_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__CreateGroupEnterprise_t qt_meta_stringdata_ui__CreateGroupEnterprise = {
    {
QT_MOC_LITERAL(0, 0, 25), // "ui::CreateGroupEnterprise"
QT_MOC_LITERAL(1, 26, 27), // "signalSerGetVisibleOrgUsers"
QT_MOC_LITERAL(2, 54, 0), // ""
QT_MOC_LITERAL(3, 55, 33), // "std::vector<data::OrgAndUserI..."
QT_MOC_LITERAL(4, 89, 23), // "onSerGetVisibleOrgUsers"
QT_MOC_LITERAL(5, 113, 4), // "code"
QT_MOC_LITERAL(6, 118, 4), // "orgs"
QT_MOC_LITERAL(7, 123, 13), // "onItemClicked"
QT_MOC_LITERAL(8, 137, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(9, 154, 4), // "item"
QT_MOC_LITERAL(10, 159, 3) // "col"

    },
    "ui::CreateGroupEnterprise\0"
    "signalSerGetVisibleOrgUsers\0\0"
    "std::vector<data::OrgAndUserInfo>\0"
    "onSerGetVisibleOrgUsers\0code\0orgs\0"
    "onItemClicked\0QTreeWidgetItem*\0item\0"
    "col"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__CreateGroupEnterprise[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    2,   34,    2, 0x09 /* Protected */,
       7,    2,   39,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3,    5,    6,
    QMetaType::Void, 0x80000000 | 8, QMetaType::Int,    9,   10,

       0        // eod
};

void ui::CreateGroupEnterprise::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CreateGroupEnterprise *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerGetVisibleOrgUsers((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<data::OrgAndUserInfo>(*)>(_a[2]))); break;
        case 1: _t->onSerGetVisibleOrgUsers((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<data::OrgAndUserInfo>(*)>(_a[2]))); break;
        case 2: _t->onItemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CreateGroupEnterprise::*)(int , std::vector<data::OrgAndUserInfo> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CreateGroupEnterprise::signalSerGetVisibleOrgUsers)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::CreateGroupEnterprise::staticMetaObject = { {
    &TWidget::staticMetaObject,
    qt_meta_stringdata_ui__CreateGroupEnterprise.data,
    qt_meta_data_ui__CreateGroupEnterprise,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::CreateGroupEnterprise::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::CreateGroupEnterprise::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__CreateGroupEnterprise.stringdata0))
        return static_cast<void*>(this);
    return TWidget::qt_metacast(_clname);
}

int ui::CreateGroupEnterprise::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ui::CreateGroupEnterprise::signalSerGetVisibleOrgUsers(int _t1, std::vector<data::OrgAndUserInfo> _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
