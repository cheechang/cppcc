/****************************************************************************
** Meta object code from reading C++ file 'LockoutAccount.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../loginwindow/LockoutAccount.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LockoutAccount.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__LockoutAccount_t {
    QByteArrayData data[12];
    char stringdata0[179];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__LockoutAccount_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__LockoutAccount_t qt_meta_stringdata_ui__LockoutAccount = {
    {
QT_MOC_LITERAL(0, 0, 18), // "ui::LockoutAccount"
QT_MOC_LITERAL(1, 19, 13), // "signalLockout"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 21), // "signalDoLockoutResult"
QT_MOC_LITERAL(4, 56, 3), // "err"
QT_MOC_LITERAL(5, 60, 11), // "std::string"
QT_MOC_LITERAL(6, 72, 7), // "codeUrl"
QT_MOC_LITERAL(7, 80, 22), // "signalSerGetVerifyCode"
QT_MOC_LITERAL(8, 103, 17), // "onSerGetNextImage"
QT_MOC_LITERAL(9, 121, 18), // "onSerLockoutResult"
QT_MOC_LITERAL(10, 140, 19), // "onBtnLockOutClicekd"
QT_MOC_LITERAL(11, 160, 18) // "onSerGetVerifyCode"

    },
    "ui::LockoutAccount\0signalLockout\0\0"
    "signalDoLockoutResult\0err\0std::string\0"
    "codeUrl\0signalSerGetVerifyCode\0"
    "onSerGetNextImage\0onSerLockoutResult\0"
    "onBtnLockOutClicekd\0onSerGetVerifyCode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__LockoutAccount[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    2,   50,    2, 0x06 /* Public */,
       7,    2,   55,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   60,    2, 0x0a /* Public */,
       9,    2,   61,    2, 0x0a /* Public */,
      10,    0,   66,    2, 0x0a /* Public */,
      11,    2,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 5,    4,    6,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 5,    4,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 5,    4,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 5,    4,    6,

       0        // eod
};

void ui::LockoutAccount::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LockoutAccount *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalLockout(); break;
        case 1: _t->signalDoLockoutResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2]))); break;
        case 2: _t->signalSerGetVerifyCode((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2]))); break;
        case 3: _t->onSerGetNextImage(); break;
        case 4: _t->onSerLockoutResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2]))); break;
        case 5: _t->onBtnLockOutClicekd(); break;
        case 6: _t->onSerGetVerifyCode((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LockoutAccount::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LockoutAccount::signalLockout)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LockoutAccount::*)(int , const std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LockoutAccount::signalDoLockoutResult)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (LockoutAccount::*)(int , const std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LockoutAccount::signalSerGetVerifyCode)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::LockoutAccount::staticMetaObject = { {
    &BaseWindow::staticMetaObject,
    qt_meta_stringdata_ui__LockoutAccount.data,
    qt_meta_data_ui__LockoutAccount,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::LockoutAccount::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::LockoutAccount::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__LockoutAccount.stringdata0))
        return static_cast<void*>(this);
    return BaseWindow::qt_metacast(_clname);
}

int ui::LockoutAccount::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void ui::LockoutAccount::signalLockout()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ui::LockoutAccount::signalDoLockoutResult(int _t1, const std::string _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::LockoutAccount::signalSerGetVerifyCode(int _t1, const std::string _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
