/****************************************************************************
** Meta object code from reading C++ file 'PasswordReset.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/systemsetting/PasswordReset.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'PasswordReset.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__PasswordReset_t {
    QByteArrayData data[12];
    char stringdata0[189];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__PasswordReset_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__PasswordReset_t qt_meta_stringdata_ui__PasswordReset = {
    {
QT_MOC_LITERAL(0, 0, 17), // "ui::PasswordReset"
QT_MOC_LITERAL(1, 18, 24), // "signalSerGetPasswordRule"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 3), // "err"
QT_MOC_LITERAL(4, 48, 4), // "rule"
QT_MOC_LITERAL(5, 53, 29), // "signalSerChangePasswordResult"
QT_MOC_LITERAL(6, 83, 6), // "result"
QT_MOC_LITERAL(7, 90, 14), // "signalCloseWin"
QT_MOC_LITERAL(8, 105, 20), // "onSerGetPasswordRule"
QT_MOC_LITERAL(9, 126, 25), // "onSerChangePasswordResult"
QT_MOC_LITERAL(10, 152, 14), // "onBtnOkClicked"
QT_MOC_LITERAL(11, 167, 21) // "onBtnBlackListClicked"

    },
    "ui::PasswordReset\0signalSerGetPasswordRule\0"
    "\0err\0rule\0signalSerChangePasswordResult\0"
    "result\0signalCloseWin\0onSerGetPasswordRule\0"
    "onSerChangePasswordResult\0onBtnOkClicked\0"
    "onBtnBlackListClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__PasswordReset[] = {

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
       1,    2,   49,    2, 0x06 /* Public */,
       5,    1,   54,    2, 0x06 /* Public */,
       7,    0,   57,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    2,   58,    2, 0x0a /* Public */,
       9,    1,   63,    2, 0x0a /* Public */,
      10,    0,   66,    2, 0x0a /* Public */,
      11,    0,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::Int,    3,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ui::PasswordReset::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PasswordReset *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerGetPasswordRule((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 1: _t->signalSerChangePasswordResult((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->signalCloseWin(); break;
        case 3: _t->onSerGetPasswordRule((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->onSerChangePasswordResult((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->onBtnOkClicked(); break;
        case 6: _t->onBtnBlackListClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PasswordReset::*)(int , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PasswordReset::signalSerGetPasswordRule)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (PasswordReset::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PasswordReset::signalSerChangePasswordResult)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (PasswordReset::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PasswordReset::signalCloseWin)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::PasswordReset::staticMetaObject = { {
    &TWidget::staticMetaObject,
    qt_meta_stringdata_ui__PasswordReset.data,
    qt_meta_data_ui__PasswordReset,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::PasswordReset::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::PasswordReset::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__PasswordReset.stringdata0))
        return static_cast<void*>(this);
    return TWidget::qt_metacast(_clname);
}

int ui::PasswordReset::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TWidget::qt_metacall(_c, _id, _a);
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
void ui::PasswordReset::signalSerGetPasswordRule(int _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::PasswordReset::signalSerChangePasswordResult(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::PasswordReset::signalCloseWin()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
