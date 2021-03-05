/****************************************************************************
** Meta object code from reading C++ file 'ActivationAccount.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../loginwindow/ActivationAccount.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ActivationAccount.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__ActivationAccount_t {
    QByteArrayData data[14];
    char stringdata0[203];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__ActivationAccount_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__ActivationAccount_t qt_meta_stringdata_ui__ActivationAccount = {
    {
QT_MOC_LITERAL(0, 0, 21), // "ui::ActivationAccount"
QT_MOC_LITERAL(1, 22, 24), // "signalSerGetPasswordRule"
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 3), // "err"
QT_MOC_LITERAL(4, 52, 4), // "rule"
QT_MOC_LITERAL(5, 57, 16), // "signalHasChanged"
QT_MOC_LITERAL(6, 74, 3), // "pwd"
QT_MOC_LITERAL(7, 78, 29), // "signalSerChangePasswordResult"
QT_MOC_LITERAL(8, 108, 6), // "result"
QT_MOC_LITERAL(9, 115, 14), // "signalLoginOut"
QT_MOC_LITERAL(10, 130, 20), // "onSerGetPasswordRule"
QT_MOC_LITERAL(11, 151, 25), // "onSerChangePasswordResult"
QT_MOC_LITERAL(12, 177, 14), // "onBtnOkClicked"
QT_MOC_LITERAL(13, 192, 10) // "onLoginOut"

    },
    "ui::ActivationAccount\0signalSerGetPasswordRule\0"
    "\0err\0rule\0signalHasChanged\0pwd\0"
    "signalSerChangePasswordResult\0result\0"
    "signalLoginOut\0onSerGetPasswordRule\0"
    "onSerChangePasswordResult\0onBtnOkClicked\0"
    "onLoginOut"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__ActivationAccount[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,
       5,    1,   59,    2, 0x06 /* Public */,
       7,    1,   62,    2, 0x06 /* Public */,
       9,    1,   65,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    2,   68,    2, 0x0a /* Public */,
      11,    1,   73,    2, 0x0a /* Public */,
      12,    0,   76,    2, 0x0a /* Public */,
      13,    1,   77,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void ui::ActivationAccount::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ActivationAccount *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerGetPasswordRule((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->signalHasChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->signalSerChangePasswordResult((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->signalLoginOut((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->onSerGetPasswordRule((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 5: _t->onSerChangePasswordResult((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->onBtnOkClicked(); break;
        case 7: _t->onLoginOut((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ActivationAccount::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ActivationAccount::signalSerGetPasswordRule)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ActivationAccount::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ActivationAccount::signalHasChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ActivationAccount::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ActivationAccount::signalSerChangePasswordResult)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ActivationAccount::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ActivationAccount::signalLoginOut)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::ActivationAccount::staticMetaObject = { {
    &BaseWindow::staticMetaObject,
    qt_meta_stringdata_ui__ActivationAccount.data,
    qt_meta_data_ui__ActivationAccount,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::ActivationAccount::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::ActivationAccount::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__ActivationAccount.stringdata0))
        return static_cast<void*>(this);
    return BaseWindow::qt_metacast(_clname);
}

int ui::ActivationAccount::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ui::ActivationAccount::signalSerGetPasswordRule(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::ActivationAccount::signalHasChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::ActivationAccount::signalSerChangePasswordResult(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ui::ActivationAccount::signalLoginOut(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
