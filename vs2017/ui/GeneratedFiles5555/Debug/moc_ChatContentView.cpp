/****************************************************************************
** Meta object code from reading C++ file 'ChatContentView.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../mainwindow/chat/ChatContentView.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ChatContentView.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__SendMsgFailureWidgetPrivate_t {
    QByteArrayData data[6];
    char stringdata0[73];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__SendMsgFailureWidgetPrivate_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__SendMsgFailureWidgetPrivate_t qt_meta_stringdata_ui__SendMsgFailureWidgetPrivate = {
    {
QT_MOC_LITERAL(0, 0, 31), // "ui::SendMsgFailureWidgetPrivate"
QT_MOC_LITERAL(1, 32, 7), // "clicked"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 19), // "GeneralMessageItem*"
QT_MOC_LITERAL(4, 61, 3), // "msg"
QT_MOC_LITERAL(5, 65, 7) // "onClick"

    },
    "ui::SendMsgFailureWidgetPrivate\0clicked\0"
    "\0GeneralMessageItem*\0msg\0onClick"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__SendMsgFailureWidgetPrivate[] = {

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
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void ui::SendMsgFailureWidgetPrivate::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SendMsgFailureWidgetPrivate *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clicked((*reinterpret_cast< GeneralMessageItem*(*)>(_a[1]))); break;
        case 1: _t->onClick(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SendMsgFailureWidgetPrivate::*)(GeneralMessageItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SendMsgFailureWidgetPrivate::clicked)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::SendMsgFailureWidgetPrivate::staticMetaObject = { {
    QMetaObject::SuperData::link<QToolButton::staticMetaObject>(),
    qt_meta_stringdata_ui__SendMsgFailureWidgetPrivate.data,
    qt_meta_data_ui__SendMsgFailureWidgetPrivate,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::SendMsgFailureWidgetPrivate::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::SendMsgFailureWidgetPrivate::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__SendMsgFailureWidgetPrivate.stringdata0))
        return static_cast<void*>(this);
    return QToolButton::qt_metacast(_clname);
}

int ui::SendMsgFailureWidgetPrivate::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolButton::qt_metacall(_c, _id, _a);
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
void ui::SendMsgFailureWidgetPrivate::clicked(GeneralMessageItem * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_ui__ChatContentView_t {
    QByteArrayData data[109];
    char stringdata0[1744];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__ChatContentView_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__ChatContentView_t qt_meta_stringdata_ui__ChatContentView = {
    {
QT_MOC_LITERAL(0, 0, 19), // "ui::ChatContentView"
QT_MOC_LITERAL(1, 20, 20), // "signalSerGetGroupMem"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 4), // "code"
QT_MOC_LITERAL(4, 47, 13), // "data::Member&"
QT_MOC_LITERAL(5, 61, 3), // "mem"
QT_MOC_LITERAL(6, 65, 9), // "oldAvatar"
QT_MOC_LITERAL(7, 75, 27), // "signalSerGetBatchMemberByID"
QT_MOC_LITERAL(8, 103, 39), // "std::vector<CSharedPtr<data::..."
QT_MOC_LITERAL(9, 143, 15), // "addIsReceiptMsg"
QT_MOC_LITERAL(10, 159, 5), // "int64"
QT_MOC_LITERAL(11, 165, 20), // "noticeInputEditFocus"
QT_MOC_LITERAL(12, 186, 11), // "downLoadImg"
QT_MOC_LITERAL(13, 198, 12), // "std::string&"
QT_MOC_LITERAL(14, 211, 16), // "signalSerSendMsg"
QT_MOC_LITERAL(15, 228, 27), // "signalSerGetGroupMemberList"
QT_MOC_LITERAL(16, 256, 20), // "signalSerGetMessages"
QT_MOC_LITERAL(17, 277, 36), // "std::vector<CSharedPtr<data::..."
QT_MOC_LITERAL(18, 314, 26), // "CSharedPtr<data::ChatInfo>"
QT_MOC_LITERAL(19, 341, 15), // "addChatListItem"
QT_MOC_LITERAL(20, 357, 27), // "CSharedPtr<data::ChatInfo>&"
QT_MOC_LITERAL(21, 385, 17), // "groupAtMessageTip"
QT_MOC_LITERAL(22, 403, 21), // "CSharedPtr<data::Msg>"
QT_MOC_LITERAL(23, 425, 19), // "signalSerGetAppInfo"
QT_MOC_LITERAL(24, 445, 15), // "data::UserData&"
QT_MOC_LITERAL(25, 461, 22), // "signalSerDeleteMsgById"
QT_MOC_LITERAL(26, 484, 20), // "messageAvatarClicked"
QT_MOC_LITERAL(27, 505, 9), // "startChat"
QT_MOC_LITERAL(28, 515, 11), // "viewBurnMsg"
QT_MOC_LITERAL(29, 527, 22), // "CSharedPtr<data::Msg>&"
QT_MOC_LITERAL(30, 550, 3), // "msg"
QT_MOC_LITERAL(31, 554, 23), // "signalSerGetDecryptMsgs"
QT_MOC_LITERAL(32, 578, 7), // "openUrl"
QT_MOC_LITERAL(33, 586, 11), // "std::string"
QT_MOC_LITERAL(34, 598, 25), // "signalSerSearchGetMessage"
QT_MOC_LITERAL(35, 624, 31), // "signalSerSearchSendedGetMessage"
QT_MOC_LITERAL(36, 656, 8), // "targetid"
QT_MOC_LITERAL(37, 665, 4), // "msgs"
QT_MOC_LITERAL(38, 670, 18), // "signalSerMsgReaded"
QT_MOC_LITERAL(39, 689, 19), // "signalSerRecallEdit"
QT_MOC_LITERAL(40, 709, 8), // "QString&"
QT_MOC_LITERAL(41, 718, 20), // "signalSerGetUserInfo"
QT_MOC_LITERAL(42, 739, 2), // "id"
QT_MOC_LITERAL(43, 742, 4), // "name"
QT_MOC_LITERAL(44, 747, 6), // "avatar"
QT_MOC_LITERAL(45, 754, 15), // "signalSerMsgTop"
QT_MOC_LITERAL(46, 770, 23), // "data::ZxTopInformation&"
QT_MOC_LITERAL(47, 794, 21), // "signalSerCancelMsgTop"
QT_MOC_LITERAL(48, 816, 21), // "signalSercppccTopInfo"
QT_MOC_LITERAL(49, 838, 18), // "signalSerDeleteMsg"
QT_MOC_LITERAL(50, 857, 9), // "hideAtWin"
QT_MOC_LITERAL(51, 867, 33), // "signalSerGetGroupMsgUnreadCou..."
QT_MOC_LITERAL(52, 901, 36), // "std::vector<data::MsgUnreadCo..."
QT_MOC_LITERAL(53, 938, 29), // "signalSerGetContractMaxReadId"
QT_MOC_LITERAL(54, 968, 24), // "std::vector<MsgDataPtr>&"
QT_MOC_LITERAL(55, 993, 29), // "onSerGetGroupMsgUnreadCounter"
QT_MOC_LITERAL(56, 1023, 7), // "groupId"
QT_MOC_LITERAL(57, 1031, 8), // "counters"
QT_MOC_LITERAL(58, 1040, 25), // "onSerGetContractMaxReadId"
QT_MOC_LITERAL(59, 1066, 8), // "targetId"
QT_MOC_LITERAL(60, 1075, 8), // "maxMsgId"
QT_MOC_LITERAL(61, 1084, 16), // "onSerGetGroupMem"
QT_MOC_LITERAL(62, 1101, 21), // "onSerSearchGetMessage"
QT_MOC_LITERAL(63, 1123, 27), // "onSerSearchSendedGetMessage"
QT_MOC_LITERAL(64, 1151, 15), // "onRevokeMsgItem"
QT_MOC_LITERAL(65, 1167, 15), // "onRemoveMsgItem"
QT_MOC_LITERAL(66, 1183, 15), // "onEventFiltered"
QT_MOC_LITERAL(67, 1199, 7), // "QEvent*"
QT_MOC_LITERAL(68, 1207, 5), // "event"
QT_MOC_LITERAL(69, 1213, 13), // "onSizeChanged"
QT_MOC_LITERAL(70, 1227, 23), // "onSerGetGroupMemberList"
QT_MOC_LITERAL(71, 1251, 3), // "err"
QT_MOC_LITERAL(72, 1255, 10), // "memberlist"
QT_MOC_LITERAL(73, 1266, 16), // "onSerGetMessages"
QT_MOC_LITERAL(74, 1283, 6), // "chatid"
QT_MOC_LITERAL(75, 1290, 7), // "msglist"
QT_MOC_LITERAL(76, 1298, 11), // "unreadcount"
QT_MOC_LITERAL(77, 1310, 4), // "chat"
QT_MOC_LITERAL(78, 1315, 9), // "ishisflag"
QT_MOC_LITERAL(79, 1325, 15), // "onGetHistoryMsg"
QT_MOC_LITERAL(80, 1341, 18), // "onMsgStatusChanged"
QT_MOC_LITERAL(81, 1360, 9), // "uilocalid"
QT_MOC_LITERAL(82, 1370, 15), // "onGetMemberlist"
QT_MOC_LITERAL(83, 1386, 15), // "onSerGetAppInfo"
QT_MOC_LITERAL(84, 1402, 4), // "data"
QT_MOC_LITERAL(85, 1407, 18), // "onReSendMsgClicked"
QT_MOC_LITERAL(86, 1426, 19), // "GeneralMessageItem*"
QT_MOC_LITERAL(87, 1446, 19), // "onSerGetDecryptMsgs"
QT_MOC_LITERAL(88, 1466, 5), // "Rcode"
QT_MOC_LITERAL(89, 1472, 12), // "DecryptMsgId"
QT_MOC_LITERAL(90, 1485, 12), // "DecryMsgList"
QT_MOC_LITERAL(91, 1498, 12), // "onDecryptMsg"
QT_MOC_LITERAL(92, 1511, 19), // "onUpdateSendMsgTime"
QT_MOC_LITERAL(93, 1531, 7), // "localId"
QT_MOC_LITERAL(94, 1539, 4), // "time"
QT_MOC_LITERAL(95, 1544, 18), // "onSerDeleteMsgById"
QT_MOC_LITERAL(96, 1563, 20), // "onShowUserInfoWidget"
QT_MOC_LITERAL(97, 1584, 16), // "onSerGetUserInfo"
QT_MOC_LITERAL(98, 1601, 15), // "onSerTopMsginfo"
QT_MOC_LITERAL(99, 1617, 10), // "topInfoMsg"
QT_MOC_LITERAL(100, 1628, 17), // "onSercppccTopInfo"
QT_MOC_LITERAL(101, 1646, 8), // "strError"
QT_MOC_LITERAL(102, 1655, 16), // "onSerHistoryChat"
QT_MOC_LITERAL(103, 1672, 14), // "onSerDeleteMsg"
QT_MOC_LITERAL(104, 1687, 23), // "onSerGetBatchMemberByID"
QT_MOC_LITERAL(105, 1711, 4), // "mems"
QT_MOC_LITERAL(106, 1716, 17), // "onChangeMsgStatus"
QT_MOC_LITERAL(107, 1734, 3), // "cnt"
QT_MOC_LITERAL(108, 1738, 5) // "msgid"

    },
    "ui::ChatContentView\0signalSerGetGroupMem\0"
    "\0code\0data::Member&\0mem\0oldAvatar\0"
    "signalSerGetBatchMemberByID\0"
    "std::vector<CSharedPtr<data::Member> >&\0"
    "addIsReceiptMsg\0int64\0noticeInputEditFocus\0"
    "downLoadImg\0std::string&\0signalSerSendMsg\0"
    "signalSerGetGroupMemberList\0"
    "signalSerGetMessages\0"
    "std::vector<CSharedPtr<data::Msg> >&\0"
    "CSharedPtr<data::ChatInfo>\0addChatListItem\0"
    "CSharedPtr<data::ChatInfo>&\0"
    "groupAtMessageTip\0CSharedPtr<data::Msg>\0"
    "signalSerGetAppInfo\0data::UserData&\0"
    "signalSerDeleteMsgById\0messageAvatarClicked\0"
    "startChat\0viewBurnMsg\0CSharedPtr<data::Msg>&\0"
    "msg\0signalSerGetDecryptMsgs\0openUrl\0"
    "std::string\0signalSerSearchGetMessage\0"
    "signalSerSearchSendedGetMessage\0"
    "targetid\0msgs\0signalSerMsgReaded\0"
    "signalSerRecallEdit\0QString&\0"
    "signalSerGetUserInfo\0id\0name\0avatar\0"
    "signalSerMsgTop\0data::ZxTopInformation&\0"
    "signalSerCancelMsgTop\0signalSercppccTopInfo\0"
    "signalSerDeleteMsg\0hideAtWin\0"
    "signalSerGetGroupMsgUnreadCounter\0"
    "std::vector<data::MsgUnreadCounter>&\0"
    "signalSerGetContractMaxReadId\0"
    "std::vector<MsgDataPtr>&\0"
    "onSerGetGroupMsgUnreadCounter\0groupId\0"
    "counters\0onSerGetContractMaxReadId\0"
    "targetId\0maxMsgId\0onSerGetGroupMem\0"
    "onSerSearchGetMessage\0onSerSearchSendedGetMessage\0"
    "onRevokeMsgItem\0onRemoveMsgItem\0"
    "onEventFiltered\0QEvent*\0event\0"
    "onSizeChanged\0onSerGetGroupMemberList\0"
    "err\0memberlist\0onSerGetMessages\0chatid\0"
    "msglist\0unreadcount\0chat\0ishisflag\0"
    "onGetHistoryMsg\0onMsgStatusChanged\0"
    "uilocalid\0onGetMemberlist\0onSerGetAppInfo\0"
    "data\0onReSendMsgClicked\0GeneralMessageItem*\0"
    "onSerGetDecryptMsgs\0Rcode\0DecryptMsgId\0"
    "DecryMsgList\0onDecryptMsg\0onUpdateSendMsgTime\0"
    "localId\0time\0onSerDeleteMsgById\0"
    "onShowUserInfoWidget\0onSerGetUserInfo\0"
    "onSerTopMsginfo\0topInfoMsg\0onSercppccTopInfo\0"
    "strError\0onSerHistoryChat\0onSerDeleteMsg\0"
    "onSerGetBatchMemberByID\0mems\0"
    "onChangeMsgStatus\0cnt\0msgid"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__ChatContentView[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      57,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      29,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,  299,    2, 0x06 /* Public */,
       7,    2,  306,    2, 0x06 /* Public */,
       9,    1,  311,    2, 0x06 /* Public */,
      11,    0,  314,    2, 0x06 /* Public */,
      12,    5,  315,    2, 0x06 /* Public */,
      14,    0,  326,    2, 0x06 /* Public */,
      15,    3,  327,    2, 0x06 /* Public */,
      16,    7,  334,    2, 0x06 /* Public */,
      19,    1,  349,    2, 0x06 /* Public */,
      21,    1,  352,    2, 0x06 /* Public */,
      23,    2,  355,    2, 0x06 /* Public */,
      25,    1,  360,    2, 0x06 /* Public */,
      26,    0,  363,    2, 0x06 /* Public */,
      27,    1,  364,    2, 0x06 /* Public */,
      28,    1,  367,    2, 0x06 /* Public */,
      31,    3,  370,    2, 0x06 /* Public */,
      32,    1,  377,    2, 0x06 /* Public */,
      34,    3,  380,    2, 0x06 /* Public */,
      35,    3,  387,    2, 0x06 /* Public */,
      38,    1,  394,    2, 0x06 /* Public */,
      39,    1,  397,    2, 0x06 /* Public */,
      41,    5,  400,    2, 0x06 /* Public */,
      45,    1,  411,    2, 0x06 /* Public */,
      47,    0,  414,    2, 0x06 /* Public */,
      48,    3,  415,    2, 0x06 /* Public */,
      49,    1,  422,    2, 0x06 /* Public */,
      50,    0,  425,    2, 0x06 /* Public */,
      51,    3,  426,    2, 0x06 /* Public */,
      53,    4,  433,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      55,    3,  442,    2, 0x08 /* Private */,
      58,    4,  449,    2, 0x08 /* Private */,
      61,    3,  458,    2, 0x08 /* Private */,
      62,    3,  465,    2, 0x08 /* Private */,
      63,    3,  472,    2, 0x08 /* Private */,
      64,    1,  479,    2, 0x08 /* Private */,
      65,    1,  482,    2, 0x08 /* Private */,
      66,    1,  485,    2, 0x08 /* Private */,
      69,    0,  488,    2, 0x08 /* Private */,
      70,    3,  489,    2, 0x08 /* Private */,
      73,    7,  496,    2, 0x08 /* Private */,
      79,    0,  511,    2, 0x08 /* Private */,
      80,    2,  512,    2, 0x08 /* Private */,
      82,    1,  517,    2, 0x08 /* Private */,
      83,    2,  520,    2, 0x08 /* Private */,
      85,    1,  525,    2, 0x08 /* Private */,
      87,    3,  528,    2, 0x08 /* Private */,
      91,    1,  535,    2, 0x08 /* Private */,
      92,    2,  538,    2, 0x08 /* Private */,
      95,    1,  543,    2, 0x08 /* Private */,
      96,    3,  546,    2, 0x08 /* Private */,
      97,    5,  553,    2, 0x08 /* Private */,
      98,    1,  564,    2, 0x08 /* Private */,
     100,    3,  567,    2, 0x08 /* Private */,
     102,    0,  574,    2, 0x08 /* Private */,
     103,    1,  575,    2, 0x08 /* Private */,
     104,    2,  578,    2, 0x08 /* Private */,
     106,    2,  583,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4, QMetaType::QString,    3,    5,    6,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 8,    2,    2,
    QMetaType::Void, 0x80000000 | 10,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 10, 0x80000000 | 13, 0x80000000 | 13, QMetaType::Bool,    2,    2,    2,    2,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 8, QMetaType::LongLong,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10, 0x80000000 | 17, 0x80000000 | 10, QMetaType::Int, 0x80000000 | 18, QMetaType::Bool,    2,    2,    2,    2,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 20,    2,
    QMetaType::Void, 0x80000000 | 22,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 24,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 20,    2,
    QMetaType::Void, 0x80000000 | 29,   30,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10, 0x80000000 | 17,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 33,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10, 0x80000000 | 17,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10, 0x80000000 | 17,    3,   36,   37,
    QMetaType::Void, 0x80000000 | 10,    2,
    QMetaType::Void, 0x80000000 | 40,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 24, 0x80000000 | 10, QMetaType::QString, QMetaType::QString,    2,    2,   42,   43,   44,
    QMetaType::Void, 0x80000000 | 46,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 33, 0x80000000 | 46,    2,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10, QMetaType::Int, 0x80000000 | 52,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 54, QMetaType::Int, 0x80000000 | 10,    2,    2,    2,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 10, QMetaType::Int, 0x80000000 | 52,   56,    3,   57,
    QMetaType::Void, 0x80000000 | 10, 0x80000000 | 54, QMetaType::Int, 0x80000000 | 10,   59,   37,    3,   60,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4, QMetaType::QString,    3,    5,    6,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10, 0x80000000 | 17,    3,   36,   37,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10, 0x80000000 | 17,    3,   36,   37,
    QMetaType::Void, 0x80000000 | 10,   42,
    QMetaType::Void, 0x80000000 | 10,   42,
    QMetaType::Void, 0x80000000 | 67,   68,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 8, QMetaType::LongLong,   71,   72,   36,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10, 0x80000000 | 17, 0x80000000 | 10, QMetaType::Int, 0x80000000 | 18, QMetaType::Bool,   71,   74,   75,   36,   76,   77,   78,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::LongLong,   71,   81,
    QMetaType::Void, QMetaType::LongLong,   36,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 24,    3,   84,
    QMetaType::Void, 0x80000000 | 86,   30,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10, 0x80000000 | 17,   88,   89,   90,
    QMetaType::Void, 0x80000000 | 40,    2,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,   93,   94,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 10, QMetaType::QString, QMetaType::QString,   42,   43,   44,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 24, 0x80000000 | 10, QMetaType::QString, QMetaType::QString,    2,    2,   42,   43,   44,
    QMetaType::Void, 0x80000000 | 46,   99,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 33, 0x80000000 | 46,    3,  101,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 8,    3,  105,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10,  107,  108,

       0        // eod
};

void ui::ChatContentView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ChatContentView *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerGetGroupMem((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::Member(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->signalSerGetBatchMemberByID((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<CSharedPtr<data::Member> >(*)>(_a[2]))); break;
        case 2: _t->addIsReceiptMsg((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 3: _t->noticeInputEditFocus(); break;
        case 4: _t->downLoadImg((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2])),(*reinterpret_cast< std::string(*)>(_a[3])),(*reinterpret_cast< std::string(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        case 5: _t->signalSerSendMsg(); break;
        case 6: _t->signalSerGetGroupMemberList((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<CSharedPtr<data::Member> >(*)>(_a[2])),(*reinterpret_cast< qint64(*)>(_a[3]))); break;
        case 7: _t->signalSerGetMessages((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2])),(*reinterpret_cast< std::vector<CSharedPtr<data::Msg> >(*)>(_a[3])),(*reinterpret_cast< int64(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[6])),(*reinterpret_cast< bool(*)>(_a[7]))); break;
        case 8: _t->addChatListItem((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        case 9: _t->groupAtMessageTip((*reinterpret_cast< CSharedPtr<data::Msg>(*)>(_a[1]))); break;
        case 10: _t->signalSerGetAppInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::UserData(*)>(_a[2]))); break;
        case 11: _t->signalSerDeleteMsgById((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->messageAvatarClicked(); break;
        case 13: _t->startChat((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        case 14: _t->viewBurnMsg((*reinterpret_cast< CSharedPtr<data::Msg>(*)>(_a[1]))); break;
        case 15: _t->signalSerGetDecryptMsgs((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2])),(*reinterpret_cast< std::vector<CSharedPtr<data::Msg> >(*)>(_a[3]))); break;
        case 16: _t->openUrl((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 17: _t->signalSerSearchGetMessage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2])),(*reinterpret_cast< std::vector<CSharedPtr<data::Msg> >(*)>(_a[3]))); break;
        case 18: _t->signalSerSearchSendedGetMessage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2])),(*reinterpret_cast< std::vector<CSharedPtr<data::Msg> >(*)>(_a[3]))); break;
        case 19: _t->signalSerMsgReaded((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 20: _t->signalSerRecallEdit((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 21: _t->signalSerGetUserInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::UserData(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 22: _t->signalSerMsgTop((*reinterpret_cast< data::ZxTopInformation(*)>(_a[1]))); break;
        case 23: _t->signalSerCancelMsgTop(); break;
        case 24: _t->signalSercppccTopInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< data::ZxTopInformation(*)>(_a[3]))); break;
        case 25: _t->signalSerDeleteMsg((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->hideAtWin(); break;
        case 27: _t->signalSerGetGroupMsgUnreadCounter((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< std::vector<data::MsgUnreadCounter>(*)>(_a[3]))); break;
        case 28: _t->signalSerGetContractMaxReadId((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< std::vector<MsgDataPtr>(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int64(*)>(_a[4]))); break;
        case 29: _t->onSerGetGroupMsgUnreadCounter((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< std::vector<data::MsgUnreadCounter>(*)>(_a[3]))); break;
        case 30: _t->onSerGetContractMaxReadId((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< std::vector<MsgDataPtr>(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< int64(*)>(_a[4]))); break;
        case 31: _t->onSerGetGroupMem((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::Member(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 32: _t->onSerSearchGetMessage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2])),(*reinterpret_cast< std::vector<CSharedPtr<data::Msg> >(*)>(_a[3]))); break;
        case 33: _t->onSerSearchSendedGetMessage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2])),(*reinterpret_cast< std::vector<CSharedPtr<data::Msg> >(*)>(_a[3]))); break;
        case 34: _t->onRevokeMsgItem((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 35: _t->onRemoveMsgItem((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 36: _t->onEventFiltered((*reinterpret_cast< QEvent*(*)>(_a[1]))); break;
        case 37: _t->onSizeChanged(); break;
        case 38: _t->onSerGetGroupMemberList((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<CSharedPtr<data::Member> >(*)>(_a[2])),(*reinterpret_cast< qint64(*)>(_a[3]))); break;
        case 39: _t->onSerGetMessages((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2])),(*reinterpret_cast< std::vector<CSharedPtr<data::Msg> >(*)>(_a[3])),(*reinterpret_cast< int64(*)>(_a[4])),(*reinterpret_cast< int(*)>(_a[5])),(*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[6])),(*reinterpret_cast< bool(*)>(_a[7]))); break;
        case 40: _t->onGetHistoryMsg(); break;
        case 41: _t->onMsgStatusChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 42: _t->onGetMemberlist((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 43: _t->onSerGetAppInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::UserData(*)>(_a[2]))); break;
        case 44: _t->onReSendMsgClicked((*reinterpret_cast< GeneralMessageItem*(*)>(_a[1]))); break;
        case 45: _t->onSerGetDecryptMsgs((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2])),(*reinterpret_cast< std::vector<CSharedPtr<data::Msg> >(*)>(_a[3]))); break;
        case 46: _t->onDecryptMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 47: _t->onUpdateSendMsgTime((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 48: _t->onSerDeleteMsgById((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 49: _t->onShowUserInfoWidget((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 50: _t->onSerGetUserInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::UserData(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 51: _t->onSerTopMsginfo((*reinterpret_cast< data::ZxTopInformation(*)>(_a[1]))); break;
        case 52: _t->onSercppccTopInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< data::ZxTopInformation(*)>(_a[3]))); break;
        case 53: _t->onSerHistoryChat(); break;
        case 54: _t->onSerDeleteMsg((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 55: _t->onSerGetBatchMemberByID((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<CSharedPtr<data::Member> >(*)>(_a[2]))); break;
        case 56: _t->onChangeMsgStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ChatContentView::*)(int , data::Member & , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatContentView::signalSerGetGroupMem)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ChatContentView::*)(int , std::vector<CSharedPtr<data::Member> > & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatContentView::signalSerGetBatchMemberByID)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ChatContentView::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatContentView::addIsReceiptMsg)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ChatContentView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatContentView::noticeInputEditFocus)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ChatContentView::*)(int64 , int64 , std::string & , std::string & , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatContentView::downLoadImg)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ChatContentView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatContentView::signalSerSendMsg)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ChatContentView::*)(int , std::vector<CSharedPtr<data::Member>> & , qint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatContentView::signalSerGetGroupMemberList)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ChatContentView::*)(int , int64 , std::vector<CSharedPtr<data::Msg>> & , int64 , int , CSharedPtr<data::ChatInfo> , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatContentView::signalSerGetMessages)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (ChatContentView::*)(CSharedPtr<data::ChatInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatContentView::addChatListItem)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (ChatContentView::*)(CSharedPtr<data::Msg> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatContentView::groupAtMessageTip)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (ChatContentView::*)(int , data::UserData & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatContentView::signalSerGetAppInfo)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (ChatContentView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatContentView::signalSerDeleteMsgById)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (ChatContentView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatContentView::messageAvatarClicked)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (ChatContentView::*)(CSharedPtr<data::ChatInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatContentView::startChat)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (ChatContentView::*)(CSharedPtr<data::Msg> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatContentView::viewBurnMsg)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (ChatContentView::*)(int , int64 , std::vector<CSharedPtr<data::Msg>> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatContentView::signalSerGetDecryptMsgs)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (ChatContentView::*)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatContentView::openUrl)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (ChatContentView::*)(int , int64 , std::vector<CSharedPtr<data::Msg>> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatContentView::signalSerSearchGetMessage)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (ChatContentView::*)(int , int64 , std::vector<CSharedPtr<data::Msg>> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatContentView::signalSerSearchSendedGetMessage)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (ChatContentView::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatContentView::signalSerMsgReaded)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (ChatContentView::*)(QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatContentView::signalSerRecallEdit)) {
                *result = 20;
                return;
            }
        }
        {
            using _t = void (ChatContentView::*)(int , data::UserData & , int64 , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatContentView::signalSerGetUserInfo)) {
                *result = 21;
                return;
            }
        }
        {
            using _t = void (ChatContentView::*)(data::ZxTopInformation & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatContentView::signalSerMsgTop)) {
                *result = 22;
                return;
            }
        }
        {
            using _t = void (ChatContentView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatContentView::signalSerCancelMsgTop)) {
                *result = 23;
                return;
            }
        }
        {
            using _t = void (ChatContentView::*)(int , const std::string & , data::ZxTopInformation & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatContentView::signalSercppccTopInfo)) {
                *result = 24;
                return;
            }
        }
        {
            using _t = void (ChatContentView::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatContentView::signalSerDeleteMsg)) {
                *result = 25;
                return;
            }
        }
        {
            using _t = void (ChatContentView::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatContentView::hideAtWin)) {
                *result = 26;
                return;
            }
        }
        {
            using _t = void (ChatContentView::*)(int64 , int , std::vector<data::MsgUnreadCounter> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatContentView::signalSerGetGroupMsgUnreadCounter)) {
                *result = 27;
                return;
            }
        }
        {
            using _t = void (ChatContentView::*)(int64 , std::vector<MsgDataPtr> & , int , int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatContentView::signalSerGetContractMaxReadId)) {
                *result = 28;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::ChatContentView::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ui__ChatContentView.data,
    qt_meta_data_ui__ChatContentView,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::ChatContentView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::ChatContentView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__ChatContentView.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ui::ChatContentView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 57)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 57;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 57)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 57;
    }
    return _id;
}

// SIGNAL 0
void ui::ChatContentView::signalSerGetGroupMem(int _t1, data::Member & _t2, QString _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::ChatContentView::signalSerGetBatchMemberByID(int _t1, std::vector<CSharedPtr<data::Member> > & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::ChatContentView::addIsReceiptMsg(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ui::ChatContentView::noticeInputEditFocus()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ui::ChatContentView::downLoadImg(int64 _t1, int64 _t2, std::string & _t3, std::string & _t4, bool _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ui::ChatContentView::signalSerSendMsg()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}

// SIGNAL 6
void ui::ChatContentView::signalSerGetGroupMemberList(int _t1, std::vector<CSharedPtr<data::Member>> & _t2, qint64 _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ui::ChatContentView::signalSerGetMessages(int _t1, int64 _t2, std::vector<CSharedPtr<data::Msg>> & _t3, int64 _t4, int _t5, CSharedPtr<data::ChatInfo> _t6, bool _t7)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t6))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t7))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ui::ChatContentView::addChatListItem(CSharedPtr<data::ChatInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void ui::ChatContentView::groupAtMessageTip(CSharedPtr<data::Msg> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void ui::ChatContentView::signalSerGetAppInfo(int _t1, data::UserData & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void ui::ChatContentView::signalSerDeleteMsgById(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void ui::ChatContentView::messageAvatarClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void ui::ChatContentView::startChat(CSharedPtr<data::ChatInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void ui::ChatContentView::viewBurnMsg(CSharedPtr<data::Msg> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void ui::ChatContentView::signalSerGetDecryptMsgs(int _t1, int64 _t2, std::vector<CSharedPtr<data::Msg>> & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void ui::ChatContentView::openUrl(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void ui::ChatContentView::signalSerSearchGetMessage(int _t1, int64 _t2, std::vector<CSharedPtr<data::Msg>> & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void ui::ChatContentView::signalSerSearchSendedGetMessage(int _t1, int64 _t2, std::vector<CSharedPtr<data::Msg>> & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void ui::ChatContentView::signalSerMsgReaded(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void ui::ChatContentView::signalSerRecallEdit(QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}

// SIGNAL 21
void ui::ChatContentView::signalSerGetUserInfo(int _t1, data::UserData & _t2, int64 _t3, QString _t4, QString _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 21, _a);
}

// SIGNAL 22
void ui::ChatContentView::signalSerMsgTop(data::ZxTopInformation & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 22, _a);
}

// SIGNAL 23
void ui::ChatContentView::signalSerCancelMsgTop()
{
    QMetaObject::activate(this, &staticMetaObject, 23, nullptr);
}

// SIGNAL 24
void ui::ChatContentView::signalSercppccTopInfo(int _t1, const std::string & _t2, data::ZxTopInformation & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 24, _a);
}

// SIGNAL 25
void ui::ChatContentView::signalSerDeleteMsg(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 25, _a);
}

// SIGNAL 26
void ui::ChatContentView::hideAtWin()
{
    QMetaObject::activate(this, &staticMetaObject, 26, nullptr);
}

// SIGNAL 27
void ui::ChatContentView::signalSerGetGroupMsgUnreadCounter(int64 _t1, int _t2, std::vector<data::MsgUnreadCounter> & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 27, _a);
}

// SIGNAL 28
void ui::ChatContentView::signalSerGetContractMaxReadId(int64 _t1, std::vector<MsgDataPtr> & _t2, int _t3, int64 _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 28, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
