/****************************************************************************
** Meta object code from reading C++ file 'ChatListWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/chat/chatList/ChatListWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ChatListWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__ChatListWidget_t {
    QByteArrayData data[58];
    char stringdata0[885];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__ChatListWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__ChatListWidget_t qt_meta_stringdata_ui__ChatListWidget = {
    {
QT_MOC_LITERAL(0, 0, 18), // "ui::ChatListWidget"
QT_MOC_LITERAL(1, 19, 29), // "signalSerGetUserNoDisturbMode"
QT_MOC_LITERAL(2, 49, 0), // ""
QT_MOC_LITERAL(3, 50, 5), // "int64"
QT_MOC_LITERAL(4, 56, 4), // "int8"
QT_MOC_LITERAL(5, 61, 23), // "signalSerChatOperResult"
QT_MOC_LITERAL(6, 85, 23), // "signalSerOperateBuddyCb"
QT_MOC_LITERAL(7, 109, 13), // "data::Contact"
QT_MOC_LITERAL(8, 123, 20), // "signalSerGetUserInfo"
QT_MOC_LITERAL(9, 144, 15), // "data::UserData&"
QT_MOC_LITERAL(10, 160, 23), // "signalSerChatListNotify"
QT_MOC_LITERAL(11, 184, 5), // "flags"
QT_MOC_LITERAL(12, 190, 41), // "std::vector<CSharedPtr<data::..."
QT_MOC_LITERAL(13, 232, 27), // "signalSerChatListHeadUpdate"
QT_MOC_LITERAL(14, 260, 2), // "id"
QT_MOC_LITERAL(15, 263, 11), // "std::string"
QT_MOC_LITERAL(16, 275, 8), // "headPath"
QT_MOC_LITERAL(17, 284, 22), // "signalSerRegLastSysMsg"
QT_MOC_LITERAL(18, 307, 12), // "data::SysMsg"
QT_MOC_LITERAL(19, 320, 6), // "sysMsg"
QT_MOC_LITERAL(20, 327, 5), // "count"
QT_MOC_LITERAL(21, 333, 26), // "signalSerRegGroupRefreshCb"
QT_MOC_LITERAL(22, 360, 4), // "type"
QT_MOC_LITERAL(23, 365, 11), // "data::Group"
QT_MOC_LITERAL(24, 377, 9), // "groupInfo"
QT_MOC_LITERAL(25, 387, 9), // "startChat"
QT_MOC_LITERAL(26, 397, 27), // "CSharedPtr<data::ChatInfo>&"
QT_MOC_LITERAL(27, 425, 4), // "chat"
QT_MOC_LITERAL(28, 430, 10), // "RemoveChat"
QT_MOC_LITERAL(29, 441, 8), // "targetId"
QT_MOC_LITERAL(30, 450, 14), // "unreadMsgCount"
QT_MOC_LITERAL(31, 465, 16), // "noticeTrayMsgTip"
QT_MOC_LITERAL(32, 482, 25), // "noticeTrayMsgUpdateReaded"
QT_MOC_LITERAL(33, 508, 9), // "palySound"
QT_MOC_LITERAL(34, 518, 15), // "noticeTrayFlash"
QT_MOC_LITERAL(35, 534, 25), // "onSerGetUserNoDisturbMode"
QT_MOC_LITERAL(36, 560, 4), // "code"
QT_MOC_LITERAL(37, 565, 6), // "userId"
QT_MOC_LITERAL(38, 572, 11), // "msgMindMode"
QT_MOC_LITERAL(39, 584, 19), // "onSerChatOperResult"
QT_MOC_LITERAL(40, 604, 19), // "onSerOperateBuddyCb"
QT_MOC_LITERAL(41, 624, 7), // "contact"
QT_MOC_LITERAL(42, 632, 22), // "onSerRegGroupRefreshCb"
QT_MOC_LITERAL(43, 655, 16), // "onSerGetUserInfo"
QT_MOC_LITERAL(44, 672, 4), // "user"
QT_MOC_LITERAL(45, 677, 19), // "onSerChatListNotify"
QT_MOC_LITERAL(46, 697, 8), // "dataList"
QT_MOC_LITERAL(47, 706, 23), // "onSerChatListHeadUpdate"
QT_MOC_LITERAL(48, 730, 18), // "onSerRegLastSysMsg"
QT_MOC_LITERAL(49, 749, 17), // "onAddChatListItem"
QT_MOC_LITERAL(50, 767, 4), // "data"
QT_MOC_LITERAL(51, 772, 12), // "onItemDelete"
QT_MOC_LITERAL(52, 785, 13), // "onItemClicked"
QT_MOC_LITERAL(53, 799, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(54, 816, 4), // "item"
QT_MOC_LITERAL(55, 821, 13), // "onClickedItem"
QT_MOC_LITERAL(56, 835, 24), // "onDisturbMenuItemClicked"
QT_MOC_LITERAL(57, 860, 24) // "onChatTopMenuItemClicked"

    },
    "ui::ChatListWidget\0signalSerGetUserNoDisturbMode\0"
    "\0int64\0int8\0signalSerChatOperResult\0"
    "signalSerOperateBuddyCb\0data::Contact\0"
    "signalSerGetUserInfo\0data::UserData&\0"
    "signalSerChatListNotify\0flags\0"
    "std::vector<CSharedPtr<data::ChatData> >&\0"
    "signalSerChatListHeadUpdate\0id\0"
    "std::string\0headPath\0signalSerRegLastSysMsg\0"
    "data::SysMsg\0sysMsg\0count\0"
    "signalSerRegGroupRefreshCb\0type\0"
    "data::Group\0groupInfo\0startChat\0"
    "CSharedPtr<data::ChatInfo>&\0chat\0"
    "RemoveChat\0targetId\0unreadMsgCount\0"
    "noticeTrayMsgTip\0noticeTrayMsgUpdateReaded\0"
    "palySound\0noticeTrayFlash\0"
    "onSerGetUserNoDisturbMode\0code\0userId\0"
    "msgMindMode\0onSerChatOperResult\0"
    "onSerOperateBuddyCb\0contact\0"
    "onSerRegGroupRefreshCb\0onSerGetUserInfo\0"
    "user\0onSerChatListNotify\0dataList\0"
    "onSerChatListHeadUpdate\0onSerRegLastSysMsg\0"
    "onAddChatListItem\0data\0onItemDelete\0"
    "onItemClicked\0QListWidgetItem*\0item\0"
    "onClickedItem\0onDisturbMenuItemClicked\0"
    "onChatTopMenuItemClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__ChatListWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      29,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      15,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,  159,    2, 0x06 /* Public */,
       5,    1,  166,    2, 0x06 /* Public */,
       6,    2,  169,    2, 0x06 /* Public */,
       8,    2,  174,    2, 0x06 /* Public */,
      10,    2,  179,    2, 0x06 /* Public */,
      13,    2,  184,    2, 0x06 /* Public */,
      17,    2,  189,    2, 0x06 /* Public */,
      21,    2,  194,    2, 0x06 /* Public */,
      25,    1,  199,    2, 0x06 /* Public */,
      28,    1,  202,    2, 0x06 /* Public */,
      30,    1,  205,    2, 0x06 /* Public */,
      31,    1,  208,    2, 0x06 /* Public */,
      32,    1,  211,    2, 0x06 /* Public */,
      33,    0,  214,    2, 0x06 /* Public */,
      34,    1,  215,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      35,    3,  218,    2, 0x0a /* Public */,
      39,    1,  225,    2, 0x0a /* Public */,
      40,    2,  228,    2, 0x0a /* Public */,
      42,    2,  233,    2, 0x0a /* Public */,
      43,    2,  238,    2, 0x0a /* Public */,
      45,    2,  243,    2, 0x0a /* Public */,
      47,    2,  248,    2, 0x0a /* Public */,
      48,    2,  253,    2, 0x0a /* Public */,
      49,    1,  258,    2, 0x0a /* Public */,
      51,    1,  261,    2, 0x0a /* Public */,
      52,    1,  264,    2, 0x0a /* Public */,
      55,    1,  267,    2, 0x0a /* Public */,
      56,    0,  270,    2, 0x0a /* Public */,
      57,    0,  271,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3, 0x80000000 | 4,    2,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 9,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 12,   11,    2,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 15,   14,   16,
    QMetaType::Void, 0x80000000 | 18, QMetaType::Int,   19,   20,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 23,   22,   24,
    QMetaType::Void, 0x80000000 | 26,   27,
    QMetaType::Void, 0x80000000 | 3,   29,
    QMetaType::Void, QMetaType::Int,   20,
    QMetaType::Void, 0x80000000 | 26,   27,
    QMetaType::Void, 0x80000000 | 3,   29,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3, 0x80000000 | 4,   36,   37,   38,
    QMetaType::Void, QMetaType::Int,   36,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,   22,   41,
    QMetaType::Void, 0x80000000 | 4, 0x80000000 | 23,   22,   24,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 9,   36,   44,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 12,   11,   46,
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 15,   14,   16,
    QMetaType::Void, 0x80000000 | 18, QMetaType::Int,   19,   20,
    QMetaType::Void, 0x80000000 | 26,   50,
    QMetaType::Void, 0x80000000 | 3,   29,
    QMetaType::Void, 0x80000000 | 53,   54,
    QMetaType::Void, 0x80000000 | 3,   29,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ui::ChatListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ChatListWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerGetUserNoDisturbMode((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2])),(*reinterpret_cast< int8(*)>(_a[3]))); break;
        case 1: _t->signalSerChatOperResult((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->signalSerOperateBuddyCb((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const data::Contact(*)>(_a[2]))); break;
        case 3: _t->signalSerGetUserInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::UserData(*)>(_a[2]))); break;
        case 4: _t->signalSerChatListNotify((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<CSharedPtr<data::ChatData> >(*)>(_a[2]))); break;
        case 5: _t->signalSerChatListHeadUpdate((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2]))); break;
        case 6: _t->signalSerRegLastSysMsg((*reinterpret_cast< const data::SysMsg(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->signalSerRegGroupRefreshCb((*reinterpret_cast< int8(*)>(_a[1])),(*reinterpret_cast< const data::Group(*)>(_a[2]))); break;
        case 8: _t->startChat((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        case 9: _t->RemoveChat((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 10: _t->unreadMsgCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->noticeTrayMsgTip((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        case 12: _t->noticeTrayMsgUpdateReaded((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 13: _t->palySound(); break;
        case 14: _t->noticeTrayFlash((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 15: _t->onSerGetUserNoDisturbMode((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2])),(*reinterpret_cast< int8(*)>(_a[3]))); break;
        case 16: _t->onSerChatOperResult((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->onSerOperateBuddyCb((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const data::Contact(*)>(_a[2]))); break;
        case 18: _t->onSerRegGroupRefreshCb((*reinterpret_cast< int8(*)>(_a[1])),(*reinterpret_cast< const data::Group(*)>(_a[2]))); break;
        case 19: _t->onSerGetUserInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::UserData(*)>(_a[2]))); break;
        case 20: _t->onSerChatListNotify((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<CSharedPtr<data::ChatData> >(*)>(_a[2]))); break;
        case 21: _t->onSerChatListHeadUpdate((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2]))); break;
        case 22: _t->onSerRegLastSysMsg((*reinterpret_cast< const data::SysMsg(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 23: _t->onAddChatListItem((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        case 24: _t->onItemDelete((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 25: _t->onItemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 26: _t->onClickedItem((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 27: _t->onDisturbMenuItemClicked(); break;
        case 28: _t->onChatTopMenuItemClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ChatListWidget::*)(int , int64 , int8 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatListWidget::signalSerGetUserNoDisturbMode)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ChatListWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatListWidget::signalSerChatOperResult)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ChatListWidget::*)(int , const data::Contact & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatListWidget::signalSerOperateBuddyCb)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ChatListWidget::*)(int , data::UserData & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatListWidget::signalSerGetUserInfo)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ChatListWidget::*)(int , std::vector<CSharedPtr<data::ChatData>> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatListWidget::signalSerChatListNotify)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ChatListWidget::*)(int64 , const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatListWidget::signalSerChatListHeadUpdate)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ChatListWidget::*)(const data::SysMsg & , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatListWidget::signalSerRegLastSysMsg)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ChatListWidget::*)(int8 , const data::Group & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatListWidget::signalSerRegGroupRefreshCb)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (ChatListWidget::*)(CSharedPtr<data::ChatInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatListWidget::startChat)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (ChatListWidget::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatListWidget::RemoveChat)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (ChatListWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatListWidget::unreadMsgCount)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (ChatListWidget::*)(CSharedPtr<data::ChatInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatListWidget::noticeTrayMsgTip)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (ChatListWidget::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatListWidget::noticeTrayMsgUpdateReaded)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (ChatListWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatListWidget::palySound)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (ChatListWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatListWidget::noticeTrayFlash)) {
                *result = 14;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::ChatListWidget::staticMetaObject = { {
    &QListWidget::staticMetaObject,
    qt_meta_stringdata_ui__ChatListWidget.data,
    qt_meta_data_ui__ChatListWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::ChatListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::ChatListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__ChatListWidget.stringdata0))
        return static_cast<void*>(this);
    return QListWidget::qt_metacast(_clname);
}

int ui::ChatListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 29)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 29;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 29)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 29;
    }
    return _id;
}

// SIGNAL 0
void ui::ChatListWidget::signalSerGetUserNoDisturbMode(int _t1, int64 _t2, int8 _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::ChatListWidget::signalSerChatOperResult(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::ChatListWidget::signalSerOperateBuddyCb(int _t1, const data::Contact & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ui::ChatListWidget::signalSerGetUserInfo(int _t1, data::UserData & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ui::ChatListWidget::signalSerChatListNotify(int _t1, std::vector<CSharedPtr<data::ChatData>> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ui::ChatListWidget::signalSerChatListHeadUpdate(int64 _t1, const std::string & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ui::ChatListWidget::signalSerRegLastSysMsg(const data::SysMsg & _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ui::ChatListWidget::signalSerRegGroupRefreshCb(int8 _t1, const data::Group & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ui::ChatListWidget::startChat(CSharedPtr<data::ChatInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void ui::ChatListWidget::RemoveChat(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void ui::ChatListWidget::unreadMsgCount(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void ui::ChatListWidget::noticeTrayMsgTip(CSharedPtr<data::ChatInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void ui::ChatListWidget::noticeTrayMsgUpdateReaded(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void ui::ChatListWidget::palySound()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void ui::ChatListWidget::noticeTrayFlash(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
