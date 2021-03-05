/****************************************************************************
** Meta object code from reading C++ file 'SendMsgButton.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../controls/SendMsgButton.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SendMsgButton.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__SendMsgButton_t {
    QByteArrayData data[7];
    char stringdata0[99];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__SendMsgButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__SendMsgButton_t qt_meta_stringdata_ui__SendMsgButton = {
    {
QT_MOC_LITERAL(0, 0, 17), // "ui::SendMsgButton"
QT_MOC_LITERAL(1, 18, 20), // "signalSetSendShorcut"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 4), // "int&"
QT_MOC_LITERAL(4, 45, 20), // "onEnterActionClicked"
QT_MOC_LITERAL(5, 66, 7), // "checked"
QT_MOC_LITERAL(6, 74, 24) // "onCtrlEnterActionClicked"

    },
    "ui::SendMsgButton\0signalSetSendShorcut\0"
    "\0int&\0onEnterActionClicked\0checked\0"
    "onCtrlEnterActionClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__SendMsgButton[] = {

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
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   32,    2, 0x0a /* Public */,
       6,    1,   35,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    5,
    QMetaType::Void, QMetaType::Bool,    5,

       0        // eod
};

void ui::SendMsgButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SendMsgButton *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSetSendShorcut((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->onEnterActionClicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->onCtrlEnterActionClicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SendMsgButton::*)(int & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SendMsgButton::signalSetSendShorcut)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::SendMsgButton::staticMetaObject = { {
    &QToolButton::staticMetaObject,
    qt_meta_stringdata_ui__SendMsgButton.data,
    qt_meta_data_ui__SendMsgButton,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::SendMsgButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::SendMsgButton::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__SendMsgButton.stringdata0))
        return static_cast<void*>(this);
    return QToolButton::qt_metacast(_clname);
}

int ui::SendMsgButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolButton::qt_metacall(_c, _id, _a);
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
void ui::SendMsgButton::signalSetSendShorcut(int & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
