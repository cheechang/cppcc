/****************************************************************************
** Meta object code from reading C++ file 'EnterpriseAccountList.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../mainwindow/contact/friend/EnterpriseAccountList.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'EnterpriseAccountList.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__EnterpriseAccountList_t {
    QByteArrayData data[12];
    char stringdata0[208];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__EnterpriseAccountList_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__EnterpriseAccountList_t qt_meta_stringdata_ui__EnterpriseAccountList = {
    {
QT_MOC_LITERAL(0, 0, 25), // "ui::EnterpriseAccountList"
QT_MOC_LITERAL(1, 26, 9), // "startChat"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 27), // "CSharedPtr<data::ChatInfo>&"
QT_MOC_LITERAL(4, 65, 24), // "signalSerGetEntAccountCb"
QT_MOC_LITERAL(5, 90, 37), // "std::vector<data::EnterpriseA..."
QT_MOC_LITERAL(6, 128, 19), // "onItemDoubleClicked"
QT_MOC_LITERAL(7, 148, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(8, 165, 4), // "item"
QT_MOC_LITERAL(9, 170, 20), // "onSerGetEntAccountCb"
QT_MOC_LITERAL(10, 191, 4), // "code"
QT_MOC_LITERAL(11, 196, 11) // "entAccounts"

    },
    "ui::EnterpriseAccountList\0startChat\0"
    "\0CSharedPtr<data::ChatInfo>&\0"
    "signalSerGetEntAccountCb\0"
    "std::vector<data::EnterpriseAccount>&\0"
    "onItemDoubleClicked\0QListWidgetItem*\0"
    "item\0onSerGetEntAccountCb\0code\0"
    "entAccounts"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__EnterpriseAccountList[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    2,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   42,    2, 0x0a /* Public */,
       9,    2,   45,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 5,    2,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 5,   10,   11,

       0        // eod
};

void ui::EnterpriseAccountList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EnterpriseAccountList *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startChat((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        case 1: _t->signalSerGetEntAccountCb((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<data::EnterpriseAccount>(*)>(_a[2]))); break;
        case 2: _t->onItemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 3: _t->onSerGetEntAccountCb((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<data::EnterpriseAccount>(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (EnterpriseAccountList::*)(CSharedPtr<data::ChatInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EnterpriseAccountList::startChat)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (EnterpriseAccountList::*)(int , std::vector<data::EnterpriseAccount> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EnterpriseAccountList::signalSerGetEntAccountCb)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::EnterpriseAccountList::staticMetaObject = { {
    QMetaObject::SuperData::link<TWidget::staticMetaObject>(),
    qt_meta_stringdata_ui__EnterpriseAccountList.data,
    qt_meta_data_ui__EnterpriseAccountList,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::EnterpriseAccountList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::EnterpriseAccountList::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__EnterpriseAccountList.stringdata0))
        return static_cast<void*>(this);
    return TWidget::qt_metacast(_clname);
}

int ui::EnterpriseAccountList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TWidget::qt_metacall(_c, _id, _a);
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
void ui::EnterpriseAccountList::startChat(CSharedPtr<data::ChatInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::EnterpriseAccountList::signalSerGetEntAccountCb(int _t1, std::vector<data::EnterpriseAccount> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
