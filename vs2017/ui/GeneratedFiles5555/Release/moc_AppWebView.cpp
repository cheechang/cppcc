/****************************************************************************
** Meta object code from reading C++ file 'AppWebView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/workbench/AppWebView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AppWebView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__AppWebPage_t {
    QByteArrayData data[1];
    char stringdata0[15];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__AppWebPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__AppWebPage_t qt_meta_stringdata_ui__AppWebPage = {
    {
QT_MOC_LITERAL(0, 0, 14) // "ui::AppWebPage"

    },
    "ui::AppWebPage"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__AppWebPage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void ui::AppWebPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ui::AppWebPage::staticMetaObject = { {
    &QWebEnginePage::staticMetaObject,
    qt_meta_stringdata_ui__AppWebPage.data,
    qt_meta_data_ui__AppWebPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::AppWebPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::AppWebPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__AppWebPage.stringdata0))
        return static_cast<void*>(this);
    return QWebEnginePage::qt_metacast(_clname);
}

int ui::AppWebPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWebEnginePage::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_ui__AppWebView_t {
    QByteArrayData data[19];
    char stringdata0[274];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__AppWebView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__AppWebView_t qt_meta_stringdata_ui__AppWebView = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ui::AppWebView"
QT_MOC_LITERAL(1, 15, 23), // "signalSerOpenChatWidget"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 5), // "int64"
QT_MOC_LITERAL(4, 46, 19), // "signalSerNewWebView"
QT_MOC_LITERAL(5, 66, 11), // "AppWebView*"
QT_MOC_LITERAL(6, 78, 23), // "signaldownloadRequested"
QT_MOC_LITERAL(7, 102, 23), // "QWebEngineDownloadItem*"
QT_MOC_LITERAL(8, 126, 12), // "softdownload"
QT_MOC_LITERAL(9, 139, 11), // "dataChanged"
QT_MOC_LITERAL(10, 151, 30), // "populateJavaScriptWindowObject"
QT_MOC_LITERAL(11, 182, 11), // "onLoadStart"
QT_MOC_LITERAL(12, 194, 10), // "onFinished"
QT_MOC_LITERAL(13, 205, 2), // "ok"
QT_MOC_LITERAL(14, 208, 14), // "onLoadProgress"
QT_MOC_LITERAL(15, 223, 8), // "progress"
QT_MOC_LITERAL(16, 232, 19), // "onSerOpenChatWidget"
QT_MOC_LITERAL(17, 252, 8), // "setValue"
QT_MOC_LITERAL(18, 261, 12) // "downloadJump"

    },
    "ui::AppWebView\0signalSerOpenChatWidget\0"
    "\0int64\0signalSerNewWebView\0AppWebView*\0"
    "signaldownloadRequested\0QWebEngineDownloadItem*\0"
    "softdownload\0dataChanged\0"
    "populateJavaScriptWindowObject\0"
    "onLoadStart\0onFinished\0ok\0onLoadProgress\0"
    "progress\0onSerOpenChatWidget\0setValue\0"
    "downloadJump"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__AppWebView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    1,   72,    2, 0x06 /* Public */,
       6,    1,   75,    2, 0x06 /* Public */,
       9,    2,   78,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   83,    2, 0x0a /* Public */,
      11,    0,   84,    2, 0x0a /* Public */,
      12,    1,   85,    2, 0x0a /* Public */,
      14,    1,   88,    2, 0x0a /* Public */,
      16,    1,   91,    2, 0x0a /* Public */,
      17,    1,   94,    2, 0x0a /* Public */,
      18,    1,   97,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   13,
    QMetaType::Void, QMetaType::Int,   15,
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void ui::AppWebView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AppWebView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerOpenChatWidget((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 1: _t->signalSerNewWebView((*reinterpret_cast< AppWebView*(*)>(_a[1]))); break;
        case 2: _t->signaldownloadRequested((*reinterpret_cast< QWebEngineDownloadItem*(*)>(_a[1]))); break;
        case 3: _t->dataChanged((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 4: _t->populateJavaScriptWindowObject(); break;
        case 5: _t->onLoadStart(); break;
        case 6: _t->onFinished((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->onLoadProgress((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->onSerOpenChatWidget((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 9: _t->setValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->downloadJump((*reinterpret_cast< QWebEngineDownloadItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
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
            using _t = void (AppWebView::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppWebView::signalSerOpenChatWidget)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AppWebView::*)(AppWebView * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppWebView::signalSerNewWebView)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AppWebView::*)(QWebEngineDownloadItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppWebView::signaldownloadRequested)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (AppWebView::*)(qint64 , qint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppWebView::dataChanged)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::AppWebView::staticMetaObject = { {
    &QWebEngineView::staticMetaObject,
    qt_meta_stringdata_ui__AppWebView.data,
    qt_meta_data_ui__AppWebView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::AppWebView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::AppWebView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__AppWebView.stringdata0))
        return static_cast<void*>(this);
    return QWebEngineView::qt_metacast(_clname);
}

int ui::AppWebView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWebEngineView::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void ui::AppWebView::signalSerOpenChatWidget(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::AppWebView::signalSerNewWebView(AppWebView * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::AppWebView::signaldownloadRequested(QWebEngineDownloadItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ui::AppWebView::dataChanged(qint64 _t1, qint64 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
