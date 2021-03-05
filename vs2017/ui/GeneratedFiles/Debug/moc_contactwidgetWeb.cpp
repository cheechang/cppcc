/****************************************************************************
** Meta object code from reading C++ file 'contactwidgetWeb.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/contact/contactwidgetWeb.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'contactwidgetWeb.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__WebDlg_t {
    QByteArrayData data[6];
    char stringdata0[48];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__WebDlg_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__WebDlg_t qt_meta_stringdata_ui__WebDlg = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ui::WebDlg"
QT_MOC_LITERAL(1, 11, 9), // "sendToWeb"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 6), // "taskid"
QT_MOC_LITERAL(4, 29, 4), // "text"
QT_MOC_LITERAL(5, 34, 13) // "callQTProcess"

    },
    "ui::WebDlg\0sendToWeb\0\0taskid\0text\0"
    "callQTProcess"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__WebDlg[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    2,   29,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    4,

       0        // eod
};

void ui::WebDlg::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<WebDlg *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->sendToWeb((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->callQTProcess((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (WebDlg::*)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&WebDlg::sendToWeb)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::WebDlg::staticMetaObject = { {
    &QDialog::staticMetaObject,
    qt_meta_stringdata_ui__WebDlg.data,
    qt_meta_data_ui__WebDlg,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::WebDlg::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::WebDlg::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__WebDlg.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ui::WebDlg::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ui::WebDlg::sendToWeb(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_ui__DefaultWidgetWeb_t {
    QByteArrayData data[8];
    char stringdata0[108];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__DefaultWidgetWeb_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__DefaultWidgetWeb_t qt_meta_stringdata_ui__DefaultWidgetWeb = {
    {
QT_MOC_LITERAL(0, 0, 20), // "ui::DefaultWidgetWeb"
QT_MOC_LITERAL(1, 21, 12), // "loadFinished"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 4), // "flag"
QT_MOC_LITERAL(4, 40, 17), // "downloadRequested"
QT_MOC_LITERAL(5, 58, 23), // "QWebEngineDownloadItem*"
QT_MOC_LITERAL(6, 82, 8), // "download"
QT_MOC_LITERAL(7, 91, 16) // "downloadFinished"

    },
    "ui::DefaultWidgetWeb\0loadFinished\0\0"
    "flag\0downloadRequested\0QWebEngineDownloadItem*\0"
    "download\0downloadFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__DefaultWidgetWeb[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       4,    1,   32,    2, 0x0a /* Public */,
       7,    0,   35,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,

       0        // eod
};

void ui::DefaultWidgetWeb::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DefaultWidgetWeb *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loadFinished((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->downloadRequested((*reinterpret_cast< QWebEngineDownloadItem*(*)>(_a[1]))); break;
        case 2: _t->downloadFinished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWebEngineDownloadItem* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::DefaultWidgetWeb::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ui__DefaultWidgetWeb.data,
    qt_meta_data_ui__DefaultWidgetWeb,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::DefaultWidgetWeb::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::DefaultWidgetWeb::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__DefaultWidgetWeb.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ui::DefaultWidgetWeb::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    }
    return _id;
}
struct qt_meta_stringdata_ui__WebTitleWidget_t {
    QByteArrayData data[1];
    char stringdata0[19];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__WebTitleWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__WebTitleWidget_t qt_meta_stringdata_ui__WebTitleWidget = {
    {
QT_MOC_LITERAL(0, 0, 18) // "ui::WebTitleWidget"

    },
    "ui::WebTitleWidget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__WebTitleWidget[] = {

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

void ui::WebTitleWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ui::WebTitleWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ui__WebTitleWidget.data,
    qt_meta_data_ui__WebTitleWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::WebTitleWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::WebTitleWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__WebTitleWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ui::WebTitleWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_ui__ContactWidgetWeb_t {
    QByteArrayData data[34];
    char stringdata0[457];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__ContactWidgetWeb_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__ContactWidgetWeb_t qt_meta_stringdata_ui__ContactWidgetWeb = {
    {
QT_MOC_LITERAL(0, 0, 20), // "ui::ContactWidgetWeb"
QT_MOC_LITERAL(1, 21, 9), // "startChat"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 27), // "CSharedPtr<data::ChatInfo>&"
QT_MOC_LITERAL(4, 60, 4), // "chat"
QT_MOC_LITERAL(5, 65, 16), // "MySelectListItem"
QT_MOC_LITERAL(6, 82, 4), // "item"
QT_MOC_LITERAL(7, 87, 11), // "closeWidget"
QT_MOC_LITERAL(8, 99, 8), // "maxWiget"
QT_MOC_LITERAL(9, 108, 9), // "sendToWeb"
QT_MOC_LITERAL(10, 118, 6), // "taskid"
QT_MOC_LITERAL(11, 125, 4), // "text"
QT_MOC_LITERAL(12, 130, 14), // "GetControlInfo"
QT_MOC_LITERAL(13, 145, 8), // "loginOut"
QT_MOC_LITERAL(14, 154, 7), // "restart"
QT_MOC_LITERAL(15, 162, 20), // "signalSerGetUserInfo"
QT_MOC_LITERAL(16, 183, 15), // "data::UserData&"
QT_MOC_LITERAL(17, 199, 23), // "signalSerChatListNotify"
QT_MOC_LITERAL(18, 223, 5), // "flags"
QT_MOC_LITERAL(19, 229, 41), // "std::vector<CSharedPtr<data::..."
QT_MOC_LITERAL(20, 271, 21), // "onShowContactInfoPage"
QT_MOC_LITERAL(21, 293, 13), // "data::Contact"
QT_MOC_LITERAL(22, 307, 7), // "contact"
QT_MOC_LITERAL(23, 315, 10), // "onTurnPage"
QT_MOC_LITERAL(24, 326, 1), // "i"
QT_MOC_LITERAL(25, 328, 13), // "sendTextToCpp"
QT_MOC_LITERAL(26, 342, 16), // "OnGetControlInfo"
QT_MOC_LITERAL(27, 359, 13), // "callQTProcess"
QT_MOC_LITERAL(28, 373, 10), // "onMaxWiget"
QT_MOC_LITERAL(29, 384, 16), // "onSerGetUserInfo"
QT_MOC_LITERAL(30, 401, 19), // "onSerChatListNotify"
QT_MOC_LITERAL(31, 421, 8), // "dataList"
QT_MOC_LITERAL(32, 430, 19), // "slotAdjustWebWindow"
QT_MOC_LITERAL(33, 450, 6) // "action"

    },
    "ui::ContactWidgetWeb\0startChat\0\0"
    "CSharedPtr<data::ChatInfo>&\0chat\0"
    "MySelectListItem\0item\0closeWidget\0"
    "maxWiget\0sendToWeb\0taskid\0text\0"
    "GetControlInfo\0loginOut\0restart\0"
    "signalSerGetUserInfo\0data::UserData&\0"
    "signalSerChatListNotify\0flags\0"
    "std::vector<CSharedPtr<data::ChatData> >&\0"
    "onShowContactInfoPage\0data::Contact\0"
    "contact\0onTurnPage\0i\0sendTextToCpp\0"
    "OnGetControlInfo\0callQTProcess\0"
    "onMaxWiget\0onSerGetUserInfo\0"
    "onSerChatListNotify\0dataList\0"
    "slotAdjustWebWindow\0action"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__ContactWidgetWeb[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  104,    2, 0x06 /* Public */,
       5,    1,  107,    2, 0x06 /* Public */,
       7,    0,  110,    2, 0x06 /* Public */,
       8,    0,  111,    2, 0x06 /* Public */,
       9,    2,  112,    2, 0x06 /* Public */,
      12,    1,  117,    2, 0x06 /* Public */,
      13,    1,  120,    2, 0x06 /* Public */,
      15,    2,  123,    2, 0x06 /* Public */,
      17,    2,  128,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      20,    1,  133,    2, 0x09 /* Protected */,
      23,    1,  136,    2, 0x09 /* Protected */,
      25,    1,  139,    2, 0x0a /* Public */,
      26,    1,  142,    2, 0x0a /* Public */,
      27,    2,  145,    2, 0x0a /* Public */,
      28,    0,  150,    2, 0x0a /* Public */,
      29,    2,  151,    2, 0x09 /* Protected */,
      30,    2,  156,    2, 0x09 /* Protected */,
      32,    1,  161,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   10,   11,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 16,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 19,   18,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 21,   22,
    QMetaType::Void, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   10,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 16,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 19,   18,   31,
    QMetaType::Void, QMetaType::Int,   33,

       0        // eod
};

void ui::ContactWidgetWeb::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ContactWidgetWeb *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startChat((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        case 1: _t->MySelectListItem((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->closeWidget(); break;
        case 3: _t->maxWiget(); break;
        case 4: _t->sendToWeb((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->GetControlInfo((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->loginOut((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->signalSerGetUserInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::UserData(*)>(_a[2]))); break;
        case 8: _t->signalSerChatListNotify((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<CSharedPtr<data::ChatData> >(*)>(_a[2]))); break;
        case 9: _t->onShowContactInfoPage((*reinterpret_cast< data::Contact(*)>(_a[1]))); break;
        case 10: _t->onTurnPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->sendTextToCpp((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->OnGetControlInfo((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 13: _t->callQTProcess((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 14: _t->onMaxWiget(); break;
        case 15: _t->onSerGetUserInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::UserData(*)>(_a[2]))); break;
        case 16: _t->onSerChatListNotify((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<CSharedPtr<data::ChatData> >(*)>(_a[2]))); break;
        case 17: _t->slotAdjustWebWindow((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ContactWidgetWeb::*)(CSharedPtr<data::ChatInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContactWidgetWeb::startChat)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ContactWidgetWeb::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContactWidgetWeb::MySelectListItem)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ContactWidgetWeb::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContactWidgetWeb::closeWidget)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ContactWidgetWeb::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContactWidgetWeb::maxWiget)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ContactWidgetWeb::*)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContactWidgetWeb::sendToWeb)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ContactWidgetWeb::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContactWidgetWeb::GetControlInfo)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ContactWidgetWeb::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContactWidgetWeb::loginOut)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ContactWidgetWeb::*)(int , data::UserData & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContactWidgetWeb::signalSerGetUserInfo)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (ContactWidgetWeb::*)(int , std::vector<CSharedPtr<data::ChatData>> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContactWidgetWeb::signalSerChatListNotify)) {
                *result = 8;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::ContactWidgetWeb::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ui__ContactWidgetWeb.data,
    qt_meta_data_ui__ContactWidgetWeb,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::ContactWidgetWeb::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::ContactWidgetWeb::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__ContactWidgetWeb.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ui::ContactWidgetWeb::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void ui::ContactWidgetWeb::startChat(CSharedPtr<data::ChatInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::ContactWidgetWeb::MySelectListItem(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::ContactWidgetWeb::closeWidget()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ui::ContactWidgetWeb::maxWiget()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ui::ContactWidgetWeb::sendToWeb(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ui::ContactWidgetWeb::GetControlInfo(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ui::ContactWidgetWeb::loginOut(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ui::ContactWidgetWeb::signalSerGetUserInfo(int _t1, data::UserData & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ui::ContactWidgetWeb::signalSerChatListNotify(int _t1, std::vector<CSharedPtr<data::ChatData>> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
