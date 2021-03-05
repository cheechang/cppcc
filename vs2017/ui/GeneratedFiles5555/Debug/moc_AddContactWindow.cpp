/****************************************************************************
** Meta object code from reading C++ file 'AddContactWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../mainwindow/contact/searchcontact/AddContactWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AddContactWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__AddContactWindow_t {
    QByteArrayData data[16];
    char stringdata0[267];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__AddContactWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__AddContactWindow_t qt_meta_stringdata_ui__AddContactWindow = {
    {
QT_MOC_LITERAL(0, 0, 20), // "ui::AddContactWindow"
QT_MOC_LITERAL(1, 21, 26), // "signalSerGetUserVerifyType"
QT_MOC_LITERAL(2, 48, 0), // ""
QT_MOC_LITERAL(3, 49, 3), // "err"
QT_MOC_LITERAL(4, 53, 24), // "data::ContactVerifyType&"
QT_MOC_LITERAL(5, 78, 10), // "verifyType"
QT_MOC_LITERAL(6, 89, 19), // "signalSerAddContact"
QT_MOC_LITERAL(7, 109, 27), // "signalSerGetGroupVerifyType"
QT_MOC_LITERAL(8, 137, 4), // "int8"
QT_MOC_LITERAL(9, 142, 8), // "isInvite"
QT_MOC_LITERAL(10, 151, 18), // "signalSerAddFriden"
QT_MOC_LITERAL(11, 170, 14), // "onOkBtnClicked"
QT_MOC_LITERAL(12, 185, 18), // "onCancelBtnClicked"
QT_MOC_LITERAL(13, 204, 22), // "onSerGetUserVerifyType"
QT_MOC_LITERAL(14, 227, 15), // "onSerAddContact"
QT_MOC_LITERAL(15, 243, 23) // "onSerGetGroupVerifyType"

    },
    "ui::AddContactWindow\0signalSerGetUserVerifyType\0"
    "\0err\0data::ContactVerifyType&\0verifyType\0"
    "signalSerAddContact\0signalSerGetGroupVerifyType\0"
    "int8\0isInvite\0signalSerAddFriden\0"
    "onOkBtnClicked\0onCancelBtnClicked\0"
    "onSerGetUserVerifyType\0onSerAddContact\0"
    "onSerGetGroupVerifyType"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__AddContactWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x06 /* Public */,
       6,    1,   64,    2, 0x06 /* Public */,
       7,    3,   67,    2, 0x06 /* Public */,
      10,    0,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   75,    2, 0x09 /* Protected */,
      12,    0,   76,    2, 0x09 /* Protected */,
      13,    2,   77,    2, 0x09 /* Protected */,
      14,    1,   82,    2, 0x09 /* Protected */,
      15,    3,   85,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 8, 0x80000000 | 8,    3,    5,    9,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 8, 0x80000000 | 8,    3,    5,    9,

       0        // eod
};

void ui::AddContactWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AddContactWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerGetUserVerifyType((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::ContactVerifyType(*)>(_a[2]))); break;
        case 1: _t->signalSerAddContact((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->signalSerGetGroupVerifyType((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int8(*)>(_a[2])),(*reinterpret_cast< int8(*)>(_a[3]))); break;
        case 3: _t->signalSerAddFriden(); break;
        case 4: _t->onOkBtnClicked(); break;
        case 5: _t->onCancelBtnClicked(); break;
        case 6: _t->onSerGetUserVerifyType((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::ContactVerifyType(*)>(_a[2]))); break;
        case 7: _t->onSerAddContact((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->onSerGetGroupVerifyType((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int8(*)>(_a[2])),(*reinterpret_cast< int8(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AddContactWindow::*)(int , data::ContactVerifyType & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AddContactWindow::signalSerGetUserVerifyType)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AddContactWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AddContactWindow::signalSerAddContact)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AddContactWindow::*)(int , int8 , int8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AddContactWindow::signalSerGetGroupVerifyType)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (AddContactWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AddContactWindow::signalSerAddFriden)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::AddContactWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseDialog::staticMetaObject>(),
    qt_meta_stringdata_ui__AddContactWindow.data,
    qt_meta_data_ui__AddContactWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::AddContactWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::AddContactWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__AddContactWindow.stringdata0))
        return static_cast<void*>(this);
    return BaseDialog::qt_metacast(_clname);
}

int ui::AddContactWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void ui::AddContactWindow::signalSerGetUserVerifyType(int _t1, data::ContactVerifyType & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::AddContactWindow::signalSerAddContact(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::AddContactWindow::signalSerGetGroupVerifyType(int _t1, int8 _t2, int8 _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ui::AddContactWindow::signalSerAddFriden()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
