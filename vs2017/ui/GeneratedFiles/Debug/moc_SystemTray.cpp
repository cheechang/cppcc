/****************************************************************************
** Meta object code from reading C++ file 'SystemTray.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/tray/SystemTray.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SystemTray.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__SystemTray_t {
    QByteArrayData data[16];
    char stringdata0[198];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__SystemTray_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__SystemTray_t qt_meta_stringdata_ui__SystemTray = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ui::SystemTray"
QT_MOC_LITERAL(1, 15, 10), // "showWidget"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 15), // "signalSerLogout"
QT_MOC_LITERAL(4, 43, 16), // "signalExitClient"
QT_MOC_LITERAL(5, 60, 9), // "isrestart"
QT_MOC_LITERAL(6, 70, 11), // "onActivated"
QT_MOC_LITERAL(7, 82, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(8, 116, 6), // "reason"
QT_MOC_LITERAL(9, 123, 8), // "setFlash"
QT_MOC_LITERAL(10, 132, 5), // "flash"
QT_MOC_LITERAL(11, 138, 11), // "onSerLogout"
QT_MOC_LITERAL(12, 150, 3), // "err"
QT_MOC_LITERAL(13, 154, 10), // "onLoginOff"
QT_MOC_LITERAL(14, 165, 10), // "onLoginOut"
QT_MOC_LITERAL(15, 176, 21) // "onMouseEnterIconEvent"

    },
    "ui::SystemTray\0showWidget\0\0signalSerLogout\0"
    "signalExitClient\0isrestart\0onActivated\0"
    "QSystemTrayIcon::ActivationReason\0"
    "reason\0setFlash\0flash\0onSerLogout\0err\0"
    "onLoginOff\0onLoginOut\0onMouseEnterIconEvent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__SystemTray[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    1,   70,    2, 0x06 /* Public */,
       4,    1,   73,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   76,    2, 0x0a /* Public */,
       9,    1,   79,    2, 0x0a /* Public */,
       9,    0,   82,    2, 0x2a /* Public | MethodCloned */,
      10,    0,   83,    2, 0x0a /* Public */,
      11,    1,   84,    2, 0x0a /* Public */,
      13,    0,   87,    2, 0x0a /* Public */,
      14,    0,   88,    2, 0x0a /* Public */,
      15,    0,   89,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Bool,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ui::SystemTray::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SystemTray *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showWidget(); break;
        case 1: _t->signalSerLogout((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->signalExitClient((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->onActivated((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 4: _t->setFlash((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->setFlash(); break;
        case 6: _t->flash(); break;
        case 7: _t->onSerLogout((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->onLoginOff(); break;
        case 9: _t->onLoginOut(); break;
        case 10: _t->onMouseEnterIconEvent(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SystemTray::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemTray::showWidget)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SystemTray::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemTray::signalSerLogout)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SystemTray::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemTray::signalExitClient)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::SystemTray::staticMetaObject = { {
    &QSystemTrayIcon::staticMetaObject,
    qt_meta_stringdata_ui__SystemTray.data,
    qt_meta_data_ui__SystemTray,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::SystemTray::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::SystemTray::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__SystemTray.stringdata0))
        return static_cast<void*>(this);
    return QSystemTrayIcon::qt_metacast(_clname);
}

int ui::SystemTray::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSystemTrayIcon::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void ui::SystemTray::showWidget()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ui::SystemTray::signalSerLogout(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::SystemTray::signalExitClient(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
