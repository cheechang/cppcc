/****************************************************************************
** Meta object code from reading C++ file 'Workbench.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/workbench/Workbench.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'Workbench.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__Workbench_t {
    QByteArrayData data[19];
    char stringdata0[254];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__Workbench_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__Workbench_t qt_meta_stringdata_ui__Workbench = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ui::Workbench"
QT_MOC_LITERAL(1, 14, 23), // "signalSerOpenChatWidget"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 5), // "int64"
QT_MOC_LITERAL(4, 45, 8), // "targetid"
QT_MOC_LITERAL(5, 54, 23), // "signalSerDownFileFinish"
QT_MOC_LITERAL(6, 78, 5), // "int32"
QT_MOC_LITERAL(7, 84, 2), // "id"
QT_MOC_LITERAL(8, 87, 10), // "onOpenLink"
QT_MOC_LITERAL(9, 98, 3), // "url"
QT_MOC_LITERAL(10, 102, 19), // "onSerOpenChatWidget"
QT_MOC_LITERAL(11, 122, 15), // "onSerNewWebView"
QT_MOC_LITERAL(12, 138, 11), // "AppWebView*"
QT_MOC_LITERAL(13, 150, 17), // "onSerdownloadJump"
QT_MOC_LITERAL(14, 168, 23), // "QWebEngineDownloadItem*"
QT_MOC_LITERAL(15, 192, 12), // "softdownload"
QT_MOC_LITERAL(16, 205, 12), // "removeSubTab"
QT_MOC_LITERAL(17, 218, 19), // "onSerDownFileFinish"
QT_MOC_LITERAL(18, 238, 15) // "onSerTabClicked"

    },
    "ui::Workbench\0signalSerOpenChatWidget\0"
    "\0int64\0targetid\0signalSerDownFileFinish\0"
    "int32\0id\0onOpenLink\0url\0onSerOpenChatWidget\0"
    "onSerNewWebView\0AppWebView*\0"
    "onSerdownloadJump\0QWebEngineDownloadItem*\0"
    "softdownload\0removeSubTab\0onSerDownFileFinish\0"
    "onSerTabClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__Workbench[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       5,    1,   62,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   65,    2, 0x0a /* Public */,
      10,    1,   68,    2, 0x0a /* Public */,
      11,    1,   71,    2, 0x0a /* Public */,
      13,    1,   74,    2, 0x0a /* Public */,
      16,    1,   77,    2, 0x0a /* Public */,
      17,    1,   80,    2, 0x0a /* Public */,
      18,    1,   83,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Int,    2,

       0        // eod
};

void ui::Workbench::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Workbench *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerOpenChatWidget((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 1: _t->signalSerDownFileFinish((*reinterpret_cast< int32(*)>(_a[1]))); break;
        case 2: _t->onOpenLink((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->onSerOpenChatWidget((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 4: _t->onSerNewWebView((*reinterpret_cast< AppWebView*(*)>(_a[1]))); break;
        case 5: _t->onSerdownloadJump((*reinterpret_cast< QWebEngineDownloadItem*(*)>(_a[1]))); break;
        case 6: _t->removeSubTab((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->onSerDownFileFinish((*reinterpret_cast< int32(*)>(_a[1]))); break;
        case 8: _t->onSerTabClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< AppWebView* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Workbench::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Workbench::signalSerOpenChatWidget)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Workbench::*)(int32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Workbench::signalSerDownFileFinish)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::Workbench::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ui__Workbench.data,
    qt_meta_data_ui__Workbench,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::Workbench::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::Workbench::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__Workbench.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ui::Workbench::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void ui::Workbench::signalSerOpenChatWidget(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::Workbench::signalSerDownFileFinish(int32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
