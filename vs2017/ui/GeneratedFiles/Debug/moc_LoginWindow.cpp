/****************************************************************************
** Meta object code from reading C++ file 'LoginWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../loginwindow/LoginWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LoginWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__MyUpdateWindow_t {
    QByteArrayData data[5];
    char stringdata0[64];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__MyUpdateWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__MyUpdateWindow_t qt_meta_stringdata_ui__MyUpdateWindow = {
    {
QT_MOC_LITERAL(0, 0, 18), // "ui::MyUpdateWindow"
QT_MOC_LITERAL(1, 19, 20), // "onSerUnicomRepResult"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 14), // "QNetworkReply*"
QT_MOC_LITERAL(4, 56, 7) // "preplay"

    },
    "ui::MyUpdateWindow\0onSerUnicomRepResult\0"
    "\0QNetworkReply*\0preplay"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__MyUpdateWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void ui::MyUpdateWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MyUpdateWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onSerUnicomRepResult((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::MyUpdateWindow::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ui__MyUpdateWindow.data,
    qt_meta_data_ui__MyUpdateWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::MyUpdateWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::MyUpdateWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__MyUpdateWindow.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ui::MyUpdateWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_ui__LoginWindow_t {
    QByteArrayData data[54];
    char stringdata0[818];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__LoginWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__LoginWindow_t qt_meta_stringdata_ui__LoginWindow = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ui::LoginWindow"
QT_MOC_LITERAL(1, 16, 12), // "loginSuccess"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 18), // "showLoginResultTip"
QT_MOC_LITERAL(4, 49, 14), // "swithAccountUI"
QT_MOC_LITERAL(5, 64, 8), // "QWidget*"
QT_MOC_LITERAL(6, 73, 14), // "lockoutAccount"
QT_MOC_LITERAL(7, 88, 13), // "activeAccount"
QT_MOC_LITERAL(8, 102, 20), // "signalSerLoginResult"
QT_MOC_LITERAL(9, 123, 3), // "err"
QT_MOC_LITERAL(10, 127, 6), // "userID"
QT_MOC_LITERAL(11, 134, 11), // "std::string"
QT_MOC_LITERAL(12, 146, 6), // "errStr"
QT_MOC_LITERAL(13, 153, 16), // "onSerLoginResult"
QT_MOC_LITERAL(14, 170, 17), // "onLoginBtnClicked"
QT_MOC_LITERAL(15, 188, 20), // "onShowLoginResultTip"
QT_MOC_LITERAL(16, 209, 7), // "tipText"
QT_MOC_LITERAL(17, 217, 21), // "onSwitchButtonClicked"
QT_MOC_LITERAL(18, 239, 20), // "onRegisterBtnClicked"
QT_MOC_LITERAL(19, 260, 18), // "onForgetBtnClicked"
QT_MOC_LITERAL(20, 279, 22), // "onRememberCheckChanged"
QT_MOC_LITERAL(21, 302, 7), // "checked"
QT_MOC_LITERAL(22, 310, 23), // "onAutoLoginCheckChanged"
QT_MOC_LITERAL(23, 334, 17), // "onAbortBtnClicked"
QT_MOC_LITERAL(24, 352, 15), // "onIconIsActived"
QT_MOC_LITERAL(25, 368, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(26, 402, 6), // "reason"
QT_MOC_LITERAL(27, 409, 21), // "onCurrentIndexChanged"
QT_MOC_LITERAL(28, 431, 4), // "name"
QT_MOC_LITERAL(29, 436, 22), // "onServerLineditFinishi"
QT_MOC_LITERAL(30, 459, 25), // "onServerLineditFinishiWeb"
QT_MOC_LITERAL(31, 485, 15), // "onSerSignResult"
QT_MOC_LITERAL(32, 501, 12), // "std::string&"
QT_MOC_LITERAL(33, 514, 3), // "ser"
QT_MOC_LITERAL(34, 518, 7), // "account"
QT_MOC_LITERAL(35, 526, 3), // "pwd"
QT_MOC_LITERAL(36, 530, 14), // "onCloseClicked"
QT_MOC_LITERAL(37, 545, 20), // "onPasswordHasChanged"
QT_MOC_LITERAL(38, 566, 18), // "onLockedOutAccount"
QT_MOC_LITERAL(39, 585, 15), // "onActiveAccount"
QT_MOC_LITERAL(40, 601, 18), // "onAccountLockedOut"
QT_MOC_LITERAL(41, 620, 19), // "onSerDealVerifyCode"
QT_MOC_LITERAL(42, 640, 14), // "QNetworkReply*"
QT_MOC_LITERAL(43, 655, 7), // "preplay"
QT_MOC_LITERAL(44, 663, 16), // "onSerIdVerifyRep"
QT_MOC_LITERAL(45, 680, 20), // "onSerUnicomRepResult"
QT_MOC_LITERAL(46, 701, 16), // "onSerSaveAccount"
QT_MOC_LITERAL(47, 718, 4), // "type"
QT_MOC_LITERAL(48, 723, 8), // "QString&"
QT_MOC_LITERAL(49, 732, 8), // "pAccount"
QT_MOC_LITERAL(50, 741, 22), // "onSerGetNextVerifyCode"
QT_MOC_LITERAL(51, 764, 22), // "onIdentityNewVerifyRsp"
QT_MOC_LITERAL(52, 787, 15), // "onAccessInfoRsp"
QT_MOC_LITERAL(53, 803, 14) // "ontelePhoneRsp"

    },
    "ui::LoginWindow\0loginSuccess\0\0"
    "showLoginResultTip\0swithAccountUI\0"
    "QWidget*\0lockoutAccount\0activeAccount\0"
    "signalSerLoginResult\0err\0userID\0"
    "std::string\0errStr\0onSerLoginResult\0"
    "onLoginBtnClicked\0onShowLoginResultTip\0"
    "tipText\0onSwitchButtonClicked\0"
    "onRegisterBtnClicked\0onForgetBtnClicked\0"
    "onRememberCheckChanged\0checked\0"
    "onAutoLoginCheckChanged\0onAbortBtnClicked\0"
    "onIconIsActived\0QSystemTrayIcon::ActivationReason\0"
    "reason\0onCurrentIndexChanged\0name\0"
    "onServerLineditFinishi\0onServerLineditFinishiWeb\0"
    "onSerSignResult\0std::string&\0ser\0"
    "account\0pwd\0onCloseClicked\0"
    "onPasswordHasChanged\0onLockedOutAccount\0"
    "onActiveAccount\0onAccountLockedOut\0"
    "onSerDealVerifyCode\0QNetworkReply*\0"
    "preplay\0onSerIdVerifyRep\0onSerUnicomRepResult\0"
    "onSerSaveAccount\0type\0QString&\0pAccount\0"
    "onSerGetNextVerifyCode\0onIdentityNewVerifyRsp\0"
    "onAccessInfoRsp\0ontelePhoneRsp"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__LoginWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      33,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  179,    2, 0x06 /* Public */,
       3,    1,  180,    2, 0x06 /* Public */,
       4,    1,  183,    2, 0x06 /* Public */,
       6,    0,  186,    2, 0x06 /* Public */,
       7,    0,  187,    2, 0x06 /* Public */,
       8,    3,  188,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    3,  195,    2, 0x0a /* Public */,
      14,    0,  202,    2, 0x0a /* Public */,
      15,    1,  203,    2, 0x0a /* Public */,
      17,    0,  206,    2, 0x0a /* Public */,
      18,    0,  207,    2, 0x0a /* Public */,
      19,    0,  208,    2, 0x0a /* Public */,
      20,    1,  209,    2, 0x0a /* Public */,
      22,    1,  212,    2, 0x0a /* Public */,
      23,    0,  215,    2, 0x0a /* Public */,
      24,    1,  216,    2, 0x0a /* Public */,
      27,    1,  219,    2, 0x0a /* Public */,
      29,    0,  222,    2, 0x0a /* Public */,
      30,    0,  223,    2, 0x0a /* Public */,
      31,    3,  224,    2, 0x0a /* Public */,
      36,    0,  231,    2, 0x0a /* Public */,
      37,    1,  232,    2, 0x0a /* Public */,
      38,    0,  235,    2, 0x0a /* Public */,
      39,    0,  236,    2, 0x0a /* Public */,
      40,    0,  237,    2, 0x0a /* Public */,
      41,    1,  238,    2, 0x0a /* Public */,
      44,    1,  241,    2, 0x0a /* Public */,
      45,    1,  244,    2, 0x0a /* Public */,
      46,    2,  247,    2, 0x0a /* Public */,
      50,    0,  252,    2, 0x0a /* Public */,
      51,    1,  253,    2, 0x0a /* Public */,
      52,    1,  256,    2, 0x0a /* Public */,
      53,    1,  259,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::LongLong, 0x80000000 | 11,    9,   10,   12,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::LongLong, 0x80000000 | 11,    9,   10,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   21,
    QMetaType::Void, QMetaType::Bool,   21,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 25,   26,
    QMetaType::Void, QMetaType::QString,   28,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 32, 0x80000000 | 32, 0x80000000 | 32,   33,   34,   35,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   35,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 42,   43,
    QMetaType::Void, 0x80000000 | 42,   43,
    QMetaType::Void, 0x80000000 | 42,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 48,   47,   49,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 42,   43,
    QMetaType::Void, 0x80000000 | 42,   43,
    QMetaType::Void, 0x80000000 | 42,   43,

       0        // eod
};

void ui::LoginWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LoginWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loginSuccess(); break;
        case 1: _t->showLoginResultTip((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->swithAccountUI((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 3: _t->lockoutAccount(); break;
        case 4: _t->activeAccount(); break;
        case 5: _t->signalSerLoginResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< long long(*)>(_a[2])),(*reinterpret_cast< const std::string(*)>(_a[3]))); break;
        case 6: _t->onSerLoginResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< long long(*)>(_a[2])),(*reinterpret_cast< const std::string(*)>(_a[3]))); break;
        case 7: _t->onLoginBtnClicked(); break;
        case 8: _t->onShowLoginResultTip((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->onSwitchButtonClicked(); break;
        case 10: _t->onRegisterBtnClicked(); break;
        case 11: _t->onForgetBtnClicked(); break;
        case 12: _t->onRememberCheckChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 13: _t->onAutoLoginCheckChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: _t->onAbortBtnClicked(); break;
        case 15: _t->onIconIsActived((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 16: _t->onCurrentIndexChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 17: _t->onServerLineditFinishi(); break;
        case 18: _t->onServerLineditFinishiWeb(); break;
        case 19: _t->onSerSignResult((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< std::string(*)>(_a[2])),(*reinterpret_cast< std::string(*)>(_a[3]))); break;
        case 20: _t->onCloseClicked(); break;
        case 21: _t->onPasswordHasChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 22: _t->onLockedOutAccount(); break;
        case 23: _t->onActiveAccount(); break;
        case 24: _t->onAccountLockedOut(); break;
        case 25: _t->onSerDealVerifyCode((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 26: _t->onSerIdVerifyRep((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 27: _t->onSerUnicomRepResult((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 28: _t->onSerSaveAccount((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 29: _t->onSerGetNextVerifyCode(); break;
        case 30: _t->onIdentityNewVerifyRsp((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 31: _t->onAccessInfoRsp((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 32: _t->ontelePhoneRsp((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        case 25:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 26:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 27:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 30:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 31:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 32:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LoginWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginWindow::loginSuccess)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LoginWindow::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginWindow::showLoginResultTip)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (LoginWindow::*)(QWidget * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginWindow::swithAccountUI)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (LoginWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginWindow::lockoutAccount)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (LoginWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginWindow::activeAccount)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (LoginWindow::*)(int , long long , const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LoginWindow::signalSerLoginResult)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::LoginWindow::staticMetaObject = { {
    &BaseDialog::staticMetaObject,
    qt_meta_stringdata_ui__LoginWindow.data,
    qt_meta_data_ui__LoginWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::LoginWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::LoginWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__LoginWindow.stringdata0))
        return static_cast<void*>(this);
    return BaseDialog::qt_metacast(_clname);
}

int ui::LoginWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 33)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 33;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 33)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 33;
    }
    return _id;
}

// SIGNAL 0
void ui::LoginWindow::loginSuccess()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ui::LoginWindow::showLoginResultTip(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::LoginWindow::swithAccountUI(QWidget * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ui::LoginWindow::lockoutAccount()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ui::LoginWindow::activeAccount()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void ui::LoginWindow::signalSerLoginResult(int _t1, long long _t2, const std::string & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
