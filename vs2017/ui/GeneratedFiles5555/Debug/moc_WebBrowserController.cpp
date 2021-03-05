/****************************************************************************
** Meta object code from reading C++ file 'WebBrowserController.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../mainwindow/workbench/WebBrowserController.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'WebBrowserController.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_WebBrowserController_t {
    QByteArrayData data[13];
    char stringdata0[136];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_WebBrowserController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_WebBrowserController_t qt_meta_stringdata_WebBrowserController = {
    {
QT_MOC_LITERAL(0, 0, 20), // "WebBrowserController"
QT_MOC_LITERAL(1, 21, 21), // "signalBtnCloseClicked"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 8), // "callback"
QT_MOC_LITERAL(4, 53, 5), // "fname"
QT_MOC_LITERAL(5, 59, 4), // "uuid"
QT_MOC_LITERAL(6, 64, 4), // "text"
QT_MOC_LITERAL(7, 69, 19), // "signalCtrlStartChat"
QT_MOC_LITERAL(8, 89, 5), // "int64"
QT_MOC_LITERAL(9, 95, 15), // "setJssdkVersion"
QT_MOC_LITERAL(10, 111, 5), // "param"
QT_MOC_LITERAL(11, 117, 8), // "openChat"
QT_MOC_LITERAL(12, 126, 9) // "paramjson"

    },
    "WebBrowserController\0signalBtnCloseClicked\0"
    "\0callback\0fname\0uuid\0text\0signalCtrlStartChat\0"
    "int64\0setJssdkVersion\0param\0openChat\0"
    "paramjson"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_WebBrowserController[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   39,    2, 0x06 /* Public */,
       3,    3,   40,    2, 0x06 /* Public */,
       7,    1,   47,    2, 0x06 /* Public */,

 // methods: name, argc, parameters, tag, flags
       9,    1,   50,    2, 0x02 /* Public */,
      11,    3,   53,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    4,    5,    6,
    QMetaType::Void, 0x80000000 | 8,    2,

 // methods: parameters
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    4,   12,    5,

       0        // eod
};

void WebBrowserController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WebBrowserController *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalBtnCloseClicked(); break;
        case 1: _t->callback((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 2: _t->signalCtrlStartChat((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 3: _t->setJssdkVersion((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->openChat((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WebBrowserController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebBrowserController::signalBtnCloseClicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (WebBrowserController::*)(const QString , const QString , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebBrowserController::callback)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (WebBrowserController::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebBrowserController::signalCtrlStartChat)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject WebBrowserController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_WebBrowserController.data,
    qt_meta_data_WebBrowserController,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *WebBrowserController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *WebBrowserController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_WebBrowserController.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int WebBrowserController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void WebBrowserController::signalBtnCloseClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void WebBrowserController::callback(const QString _t1, const QString _t2, const QString & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void WebBrowserController::signalCtrlStartChat(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
