/****************************************************************************
** Meta object code from reading C++ file 'FriendListWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/contact/friend/FriendListWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FriendListWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__FriendListWidget_t {
    QByteArrayData data[46];
    char stringdata0[760];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__FriendListWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__FriendListWidget_t qt_meta_stringdata_ui__FriendListWidget = {
    {
QT_MOC_LITERAL(0, 0, 20), // "ui::FriendListWidget"
QT_MOC_LITERAL(1, 21, 9), // "startChat"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 27), // "CSharedPtr<data::ChatInfo>&"
QT_MOC_LITERAL(4, 60, 4), // "chat"
QT_MOC_LITERAL(5, 65, 20), // "signalSerBuddyListCb"
QT_MOC_LITERAL(6, 86, 27), // "std::vector<data::Contact>&"
QT_MOC_LITERAL(7, 114, 23), // "signalSerOperateBuddyCb"
QT_MOC_LITERAL(8, 138, 13), // "data::Contact"
QT_MOC_LITERAL(9, 152, 24), // "signalSerRemoveContactCb"
QT_MOC_LITERAL(10, 177, 4), // "code"
QT_MOC_LITERAL(11, 182, 21), // "signalUpdateContactCb"
QT_MOC_LITERAL(12, 204, 19), // "showContactInfoPage"
QT_MOC_LITERAL(13, 224, 25), // "signalSerBuddyOnlineState"
QT_MOC_LITERAL(14, 250, 17), // "data::OnlineState"
QT_MOC_LITERAL(15, 268, 31), // "signalSerContactHeadImgUpdateCb"
QT_MOC_LITERAL(16, 300, 5), // "int64"
QT_MOC_LITERAL(17, 306, 11), // "std::string"
QT_MOC_LITERAL(18, 318, 23), // "signalSerGetBuddyOnline"
QT_MOC_LITERAL(19, 342, 31), // "std::vector<data::OnlineState>&"
QT_MOC_LITERAL(20, 374, 12), // "signalRemark"
QT_MOC_LITERAL(21, 387, 19), // "onSerGetBuddyOnline"
QT_MOC_LITERAL(22, 407, 6), // "states"
QT_MOC_LITERAL(23, 414, 21), // "onSerBuddyOnlineState"
QT_MOC_LITERAL(24, 436, 5), // "state"
QT_MOC_LITERAL(25, 442, 20), // "onSerRemoveContactCb"
QT_MOC_LITERAL(26, 463, 16), // "onSerBuddyListCb"
QT_MOC_LITERAL(27, 480, 4), // "type"
QT_MOC_LITERAL(28, 485, 8), // "contacts"
QT_MOC_LITERAL(29, 494, 19), // "onSerOperateBuddyCb"
QT_MOC_LITERAL(30, 514, 4), // "data"
QT_MOC_LITERAL(31, 519, 13), // "onItemClicked"
QT_MOC_LITERAL(32, 533, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(33, 550, 4), // "item"
QT_MOC_LITERAL(34, 555, 19), // "onItemDoubleClicked"
QT_MOC_LITERAL(35, 575, 23), // "onDeleteMenuItemClicked"
QT_MOC_LITERAL(36, 599, 23), // "onRemarkMenuItemClicked"
QT_MOC_LITERAL(37, 623, 20), // "onVipMenuItemClicked"
QT_MOC_LITERAL(38, 644, 21), // "onShowRemarkWinResult"
QT_MOC_LITERAL(39, 666, 6), // "remark"
QT_MOC_LITERAL(40, 673, 27), // "onSerContactHeadImgUpdateCb"
QT_MOC_LITERAL(41, 701, 2), // "id"
QT_MOC_LITERAL(42, 704, 4), // "head"
QT_MOC_LITERAL(43, 709, 29), // "onListWidgetCurrentRowChanged"
QT_MOC_LITERAL(44, 739, 3), // "row"
QT_MOC_LITERAL(45, 743, 16) // "onLazyLoadMember"

    },
    "ui::FriendListWidget\0startChat\0\0"
    "CSharedPtr<data::ChatInfo>&\0chat\0"
    "signalSerBuddyListCb\0std::vector<data::Contact>&\0"
    "signalSerOperateBuddyCb\0data::Contact\0"
    "signalSerRemoveContactCb\0code\0"
    "signalUpdateContactCb\0showContactInfoPage\0"
    "signalSerBuddyOnlineState\0data::OnlineState\0"
    "signalSerContactHeadImgUpdateCb\0int64\0"
    "std::string\0signalSerGetBuddyOnline\0"
    "std::vector<data::OnlineState>&\0"
    "signalRemark\0onSerGetBuddyOnline\0"
    "states\0onSerBuddyOnlineState\0state\0"
    "onSerRemoveContactCb\0onSerBuddyListCb\0"
    "type\0contacts\0onSerOperateBuddyCb\0"
    "data\0onItemClicked\0QListWidgetItem*\0"
    "item\0onItemDoubleClicked\0"
    "onDeleteMenuItemClicked\0onRemarkMenuItemClicked\0"
    "onVipMenuItemClicked\0onShowRemarkWinResult\0"
    "remark\0onSerContactHeadImgUpdateCb\0"
    "id\0head\0onListWidgetCurrentRowChanged\0"
    "row\0onLazyLoadMember"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__FriendListWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      24,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  134,    2, 0x06 /* Public */,
       5,    2,  137,    2, 0x06 /* Public */,
       7,    2,  142,    2, 0x06 /* Public */,
       9,    1,  147,    2, 0x06 /* Public */,
      11,    1,  150,    2, 0x06 /* Public */,
      12,    1,  153,    2, 0x06 /* Public */,
      13,    1,  156,    2, 0x06 /* Public */,
      15,    2,  159,    2, 0x06 /* Public */,
      18,    2,  164,    2, 0x06 /* Public */,
      20,    1,  169,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      21,    2,  172,    2, 0x0a /* Public */,
      23,    1,  177,    2, 0x0a /* Public */,
      25,    1,  180,    2, 0x0a /* Public */,
      26,    2,  183,    2, 0x0a /* Public */,
      29,    2,  188,    2, 0x0a /* Public */,
      31,    1,  193,    2, 0x0a /* Public */,
      34,    1,  196,    2, 0x0a /* Public */,
      35,    0,  199,    2, 0x0a /* Public */,
      36,    0,  200,    2, 0x0a /* Public */,
      37,    0,  201,    2, 0x0a /* Public */,
      38,    1,  202,    2, 0x0a /* Public */,
      40,    2,  205,    2, 0x0a /* Public */,
      43,    1,  210,    2, 0x0a /* Public */,
      45,    0,  213,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 6,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 8,    2,    2,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, 0x80000000 | 8,    2,
    QMetaType::Void, 0x80000000 | 14,    2,
    QMetaType::Void, 0x80000000 | 16, 0x80000000 | 17,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 19,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 19,   10,   22,
    QMetaType::Void, 0x80000000 | 14,   24,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 6,   27,   28,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 8,   27,   30,
    QMetaType::Void, 0x80000000 | 32,   33,
    QMetaType::Void, 0x80000000 | 32,   33,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   39,
    QMetaType::Void, 0x80000000 | 16, 0x80000000 | 17,   41,   42,
    QMetaType::Void, QMetaType::Int,   44,
    QMetaType::Void,

       0        // eod
};

void ui::FriendListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FriendListWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startChat((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        case 1: _t->signalSerBuddyListCb((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<data::Contact>(*)>(_a[2]))); break;
        case 2: _t->signalSerOperateBuddyCb((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const data::Contact(*)>(_a[2]))); break;
        case 3: _t->signalSerRemoveContactCb((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->signalUpdateContactCb((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->showContactInfoPage((*reinterpret_cast< data::Contact(*)>(_a[1]))); break;
        case 6: _t->signalSerBuddyOnlineState((*reinterpret_cast< const data::OnlineState(*)>(_a[1]))); break;
        case 7: _t->signalSerContactHeadImgUpdateCb((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2]))); break;
        case 8: _t->signalSerGetBuddyOnline((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<data::OnlineState>(*)>(_a[2]))); break;
        case 9: _t->signalRemark((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->onSerGetBuddyOnline((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<data::OnlineState>(*)>(_a[2]))); break;
        case 11: _t->onSerBuddyOnlineState((*reinterpret_cast< const data::OnlineState(*)>(_a[1]))); break;
        case 12: _t->onSerRemoveContactCb((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->onSerBuddyListCb((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<data::Contact>(*)>(_a[2]))); break;
        case 14: _t->onSerOperateBuddyCb((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const data::Contact(*)>(_a[2]))); break;
        case 15: _t->onItemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 16: _t->onItemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 17: _t->onDeleteMenuItemClicked(); break;
        case 18: _t->onRemarkMenuItemClicked(); break;
        case 19: _t->onVipMenuItemClicked(); break;
        case 20: _t->onShowRemarkWinResult((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: _t->onSerContactHeadImgUpdateCb((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2]))); break;
        case 22: _t->onListWidgetCurrentRowChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 23: _t->onLazyLoadMember(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FriendListWidget::*)(CSharedPtr<data::ChatInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FriendListWidget::startChat)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FriendListWidget::*)(int , std::vector<data::Contact> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FriendListWidget::signalSerBuddyListCb)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FriendListWidget::*)(int , const data::Contact & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FriendListWidget::signalSerOperateBuddyCb)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (FriendListWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FriendListWidget::signalSerRemoveContactCb)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (FriendListWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FriendListWidget::signalUpdateContactCb)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (FriendListWidget::*)(data::Contact );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FriendListWidget::showContactInfoPage)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (FriendListWidget::*)(const data::OnlineState & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FriendListWidget::signalSerBuddyOnlineState)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (FriendListWidget::*)(int64 , const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FriendListWidget::signalSerContactHeadImgUpdateCb)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (FriendListWidget::*)(int , std::vector<data::OnlineState> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FriendListWidget::signalSerGetBuddyOnline)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (FriendListWidget::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FriendListWidget::signalRemark)) {
                *result = 9;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::FriendListWidget::staticMetaObject = { {
    &TWidget::staticMetaObject,
    qt_meta_stringdata_ui__FriendListWidget.data,
    qt_meta_data_ui__FriendListWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::FriendListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::FriendListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__FriendListWidget.stringdata0))
        return static_cast<void*>(this);
    return TWidget::qt_metacast(_clname);
}

int ui::FriendListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 24)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 24;
    }
    return _id;
}

// SIGNAL 0
void ui::FriendListWidget::startChat(CSharedPtr<data::ChatInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::FriendListWidget::signalSerBuddyListCb(int _t1, std::vector<data::Contact> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::FriendListWidget::signalSerOperateBuddyCb(int _t1, const data::Contact & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ui::FriendListWidget::signalSerRemoveContactCb(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ui::FriendListWidget::signalUpdateContactCb(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ui::FriendListWidget::showContactInfoPage(data::Contact _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ui::FriendListWidget::signalSerBuddyOnlineState(const data::OnlineState & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ui::FriendListWidget::signalSerContactHeadImgUpdateCb(int64 _t1, const std::string & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ui::FriendListWidget::signalSerGetBuddyOnline(int _t1, std::vector<data::OnlineState> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void ui::FriendListWidget::signalRemark(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
