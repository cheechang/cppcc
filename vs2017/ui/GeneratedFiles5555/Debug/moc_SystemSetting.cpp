/****************************************************************************
** Meta object code from reading C++ file 'SystemSetting.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../mainwindow/systemsetting/SystemSetting.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SystemSetting.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__SystemSetting_t {
    QByteArrayData data[13];
    char stringdata0[155];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__SystemSetting_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__SystemSetting_t qt_meta_stringdata_ui__SystemSetting = {
    {
QT_MOC_LITERAL(0, 0, 17), // "ui::SystemSetting"
QT_MOC_LITERAL(1, 18, 19), // "signalHotKeySetting"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 6), // "screen"
QT_MOC_LITERAL(4, 46, 3), // "msg"
QT_MOC_LITERAL(5, 50, 16), // "setSendMsgHotKey"
QT_MOC_LITERAL(6, 67, 4), // "type"
QT_MOC_LITERAL(7, 72, 17), // "hotKeyHasConflict"
QT_MOC_LITERAL(8, 90, 8), // "conflict"
QT_MOC_LITERAL(9, 99, 16), // "setMsgSoundState"
QT_MOC_LITERAL(10, 116, 15), // "signalPlaySound"
QT_MOC_LITERAL(11, 132, 13), // "hotKeySuccess"
QT_MOC_LITERAL(12, 146, 8) // "winClose"

    },
    "ui::SystemSetting\0signalHotKeySetting\0"
    "\0screen\0msg\0setSendMsgHotKey\0type\0"
    "hotKeyHasConflict\0conflict\0setMsgSoundState\0"
    "signalPlaySound\0hotKeySuccess\0winClose"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__SystemSetting[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   49,    2, 0x06 /* Public */,
       5,    1,   54,    2, 0x06 /* Public */,
       7,    1,   57,    2, 0x06 /* Public */,
       9,    1,   60,    2, 0x06 /* Public */,
      10,    1,   63,    2, 0x06 /* Public */,
      11,    0,   66,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void ui::SystemSetting::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SystemSetting *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalHotKeySetting((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->setSendMsgHotKey((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->hotKeyHasConflict((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->setMsgSoundState((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->signalPlaySound((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->hotKeySuccess(); break;
        case 6: _t->winClose(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SystemSetting::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemSetting::signalHotKeySetting)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SystemSetting::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemSetting::setSendMsgHotKey)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SystemSetting::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemSetting::hotKeyHasConflict)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SystemSetting::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemSetting::setMsgSoundState)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SystemSetting::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemSetting::signalPlaySound)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SystemSetting::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemSetting::hotKeySuccess)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::SystemSetting::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseWindow::staticMetaObject>(),
    qt_meta_stringdata_ui__SystemSetting.data,
    qt_meta_data_ui__SystemSetting,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::SystemSetting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::SystemSetting::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__SystemSetting.stringdata0))
        return static_cast<void*>(this);
    return BaseWindow::qt_metacast(_clname);
}

int ui::SystemSetting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ui::SystemSetting::signalHotKeySetting(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::SystemSetting::setSendMsgHotKey(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::SystemSetting::hotKeyHasConflict(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ui::SystemSetting::setMsgSoundState(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ui::SystemSetting::signalPlaySound(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ui::SystemSetting::hotKeySuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
