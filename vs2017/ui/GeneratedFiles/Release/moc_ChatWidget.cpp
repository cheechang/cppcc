/****************************************************************************
** Meta object code from reading C++ file 'ChatWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/chat/ChatWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ChatWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__ChatWidget_t {
    QByteArrayData data[96];
    char stringdata0[1307];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__ChatWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__ChatWidget_t qt_meta_stringdata_ui__ChatWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ui::ChatWidget"
QT_MOC_LITERAL(1, 15, 20), // "signalSerGetGroupMem"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 4), // "code"
QT_MOC_LITERAL(4, 42, 13), // "data::Member&"
QT_MOC_LITERAL(5, 56, 3), // "mem"
QT_MOC_LITERAL(6, 60, 15), // "addIsReceiptMsg"
QT_MOC_LITERAL(7, 76, 5), // "int64"
QT_MOC_LITERAL(8, 82, 25), // "signalSerSendisReceiptMsg"
QT_MOC_LITERAL(9, 108, 3), // "err"
QT_MOC_LITERAL(10, 112, 7), // "msgtime"
QT_MOC_LITERAL(11, 120, 5), // "msgid"
QT_MOC_LITERAL(12, 126, 21), // "CSharedPtr<data::Msg>"
QT_MOC_LITERAL(13, 148, 3), // "msg"
QT_MOC_LITERAL(14, 152, 19), // "sendMsgHotKeyUpdate"
QT_MOC_LITERAL(15, 172, 14), // "signalShakeWin"
QT_MOC_LITERAL(16, 187, 7), // "openUrl"
QT_MOC_LITERAL(17, 195, 11), // "std::string"
QT_MOC_LITERAL(18, 207, 3), // "url"
QT_MOC_LITERAL(19, 211, 11), // "viewBurnMsg"
QT_MOC_LITERAL(20, 223, 22), // "CSharedPtr<data::Msg>&"
QT_MOC_LITERAL(21, 246, 15), // "addChatListItem"
QT_MOC_LITERAL(22, 262, 27), // "CSharedPtr<data::ChatInfo>&"
QT_MOC_LITERAL(23, 290, 9), // "startChat"
QT_MOC_LITERAL(24, 300, 16), // "signalScreenShot"
QT_MOC_LITERAL(25, 317, 4), // "flag"
QT_MOC_LITERAL(26, 322, 15), // "signalSendImage"
QT_MOC_LITERAL(27, 338, 17), // "signalSendMsgShot"
QT_MOC_LITERAL(28, 356, 3), // "key"
QT_MOC_LITERAL(29, 360, 24), // "signalSetSecretIsvisible"
QT_MOC_LITERAL(30, 385, 27), // "signalSerGroupRefreshUpdate"
QT_MOC_LITERAL(31, 413, 4), // "int8"
QT_MOC_LITERAL(32, 418, 11), // "data::Group"
QT_MOC_LITERAL(33, 430, 19), // "signalSerGetUrlInfo"
QT_MOC_LITERAL(34, 450, 4), // "text"
QT_MOC_LITERAL(35, 455, 29), // "signalSerGroupMemCountRefresh"
QT_MOC_LITERAL(36, 485, 20), // "signalSerGetUserInfo"
QT_MOC_LITERAL(37, 506, 15), // "data::UserData&"
QT_MOC_LITERAL(38, 522, 24), // "signalSerbtnCloseSession"
QT_MOC_LITERAL(39, 547, 18), // "signalSerGetTopMsg"
QT_MOC_LITERAL(40, 566, 5), // "int32"
QT_MOC_LITERAL(41, 572, 36), // "std::vector<data::ZxTopInform..."
QT_MOC_LITERAL(42, 609, 21), // "signalSerCancelTopMsg"
QT_MOC_LITERAL(43, 631, 22), // "signalSerGetMemberInfo"
QT_MOC_LITERAL(44, 654, 12), // "std::string&"
QT_MOC_LITERAL(45, 667, 16), // "onSerGetGroupMem"
QT_MOC_LITERAL(46, 684, 21), // "onSerSendisReceiptMsg"
QT_MOC_LITERAL(47, 706, 14), // "onSendDelayMsg"
QT_MOC_LITERAL(48, 721, 4), // "time"
QT_MOC_LITERAL(49, 726, 12), // "onSendDnyMsg"
QT_MOC_LITERAL(50, 739, 8), // "fileName"
QT_MOC_LITERAL(51, 748, 10), // "onSendCard"
QT_MOC_LITERAL(52, 759, 6), // "cardId"
QT_MOC_LITERAL(53, 766, 6), // "isburn"
QT_MOC_LITERAL(54, 773, 7), // "isdelay"
QT_MOC_LITERAL(55, 781, 9), // "isreceipt"
QT_MOC_LITERAL(56, 791, 9), // "onSendMsg"
QT_MOC_LITERAL(57, 801, 9), // "imagelist"
QT_MOC_LITERAL(58, 811, 8), // "filelist"
QT_MOC_LITERAL(59, 820, 18), // "std::vector<int64>"
QT_MOC_LITERAL(60, 839, 6), // "atlist"
QT_MOC_LITERAL(61, 846, 19), // "onShowGroupAtMsgTip"
QT_MOC_LITERAL(62, 866, 15), // "onSerGetUrlInfo"
QT_MOC_LITERAL(63, 882, 5), // "title"
QT_MOC_LITERAL(64, 888, 7), // "imgPath"
QT_MOC_LITERAL(65, 896, 4), // "desc"
QT_MOC_LITERAL(66, 901, 15), // "onSetPrivateKey"
QT_MOC_LITERAL(67, 917, 8), // "QString&"
QT_MOC_LITERAL(68, 926, 9), // "pPassword"
QT_MOC_LITERAL(69, 936, 23), // "onSerGroupRefreshUpdate"
QT_MOC_LITERAL(70, 960, 19), // "onSerGetContactInfo"
QT_MOC_LITERAL(71, 980, 17), // "onShakeWinClicked"
QT_MOC_LITERAL(72, 998, 15), // "onShowRecordWin"
QT_MOC_LITERAL(73, 1014, 14), // "onRecordResult"
QT_MOC_LITERAL(74, 1029, 4), // "path"
QT_MOC_LITERAL(75, 1034, 16), // "onSerGetUserInfo"
QT_MOC_LITERAL(76, 1051, 4), // "user"
QT_MOC_LITERAL(77, 1056, 19), // "onSerChickMsgReaded"
QT_MOC_LITERAL(78, 1076, 6), // "pmsgid"
QT_MOC_LITERAL(79, 1083, 14), // "SetTileContent"
QT_MOC_LITERAL(80, 1098, 4), // "type"
QT_MOC_LITERAL(81, 1103, 8), // "MemCount"
QT_MOC_LITERAL(82, 1112, 25), // "onSerGroupMemCountRefresh"
QT_MOC_LITERAL(83, 1138, 9), // "pMemCount"
QT_MOC_LITERAL(84, 1148, 18), // "onSerSendMsgByType"
QT_MOC_LITERAL(85, 1167, 15), // "onSerMoretopMsg"
QT_MOC_LITERAL(86, 1183, 17), // "onSerCanceltopMsg"
QT_MOC_LITERAL(87, 1201, 18), // "onSerGetMemberInfo"
QT_MOC_LITERAL(88, 1220, 6), // "member"
QT_MOC_LITERAL(89, 1227, 7), // "content"
QT_MOC_LITERAL(90, 1235, 11), // "onHideAtWin"
QT_MOC_LITERAL(91, 1247, 14), // "onSerGetTopMsg"
QT_MOC_LITERAL(92, 1262, 17), // "onSerCancelTopMsg"
QT_MOC_LITERAL(93, 1280, 7), // "pageNum"
QT_MOC_LITERAL(94, 1288, 5), // "Count"
QT_MOC_LITERAL(95, 1294, 12) // "ResultTopMsg"

    },
    "ui::ChatWidget\0signalSerGetGroupMem\0"
    "\0code\0data::Member&\0mem\0addIsReceiptMsg\0"
    "int64\0signalSerSendisReceiptMsg\0err\0"
    "msgtime\0msgid\0CSharedPtr<data::Msg>\0"
    "msg\0sendMsgHotKeyUpdate\0signalShakeWin\0"
    "openUrl\0std::string\0url\0viewBurnMsg\0"
    "CSharedPtr<data::Msg>&\0addChatListItem\0"
    "CSharedPtr<data::ChatInfo>&\0startChat\0"
    "signalScreenShot\0flag\0signalSendImage\0"
    "signalSendMsgShot\0key\0signalSetSecretIsvisible\0"
    "signalSerGroupRefreshUpdate\0int8\0"
    "data::Group\0signalSerGetUrlInfo\0text\0"
    "signalSerGroupMemCountRefresh\0"
    "signalSerGetUserInfo\0data::UserData&\0"
    "signalSerbtnCloseSession\0signalSerGetTopMsg\0"
    "int32\0std::vector<data::ZxTopInformation>&\0"
    "signalSerCancelTopMsg\0signalSerGetMemberInfo\0"
    "std::string&\0onSerGetGroupMem\0"
    "onSerSendisReceiptMsg\0onSendDelayMsg\0"
    "time\0onSendDnyMsg\0fileName\0onSendCard\0"
    "cardId\0isburn\0isdelay\0isreceipt\0"
    "onSendMsg\0imagelist\0filelist\0"
    "std::vector<int64>\0atlist\0onShowGroupAtMsgTip\0"
    "onSerGetUrlInfo\0title\0imgPath\0desc\0"
    "onSetPrivateKey\0QString&\0pPassword\0"
    "onSerGroupRefreshUpdate\0onSerGetContactInfo\0"
    "onShakeWinClicked\0onShowRecordWin\0"
    "onRecordResult\0path\0onSerGetUserInfo\0"
    "user\0onSerChickMsgReaded\0pmsgid\0"
    "SetTileContent\0type\0MemCount\0"
    "onSerGroupMemCountRefresh\0pMemCount\0"
    "onSerSendMsgByType\0onSerMoretopMsg\0"
    "onSerCanceltopMsg\0onSerGetMemberInfo\0"
    "member\0content\0onHideAtWin\0onSerGetTopMsg\0"
    "onSerCancelTopMsg\0pageNum\0Count\0"
    "ResultTopMsg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__ChatWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      46,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      21,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  244,    2, 0x06 /* Public */,
       6,    1,  249,    2, 0x06 /* Public */,
       8,    4,  252,    2, 0x06 /* Public */,
      14,    1,  261,    2, 0x06 /* Public */,
      15,    0,  264,    2, 0x06 /* Public */,
      16,    1,  265,    2, 0x06 /* Public */,
      19,    1,  268,    2, 0x06 /* Public */,
      21,    1,  271,    2, 0x06 /* Public */,
      23,    1,  274,    2, 0x06 /* Public */,
      24,    1,  277,    2, 0x06 /* Public */,
      26,    1,  280,    2, 0x06 /* Public */,
      27,    1,  283,    2, 0x06 /* Public */,
      29,    2,  286,    2, 0x06 /* Public */,
      30,    2,  291,    2, 0x06 /* Public */,
      33,    6,  296,    2, 0x06 /* Public */,
      35,    2,  309,    2, 0x06 /* Public */,
      36,    2,  314,    2, 0x06 /* Public */,
      38,    1,  319,    2, 0x06 /* Public */,
      39,    4,  322,    2, 0x06 /* Public */,
      42,    4,  331,    2, 0x06 /* Public */,
      43,    3,  340,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      45,    2,  347,    2, 0x0a /* Public */,
      46,    4,  352,    2, 0x0a /* Public */,
      47,    2,  361,    2, 0x0a /* Public */,
      49,    1,  366,    2, 0x0a /* Public */,
      51,    4,  369,    2, 0x0a /* Public */,
      56,    7,  378,    2, 0x0a /* Public */,
      61,    1,  393,    2, 0x0a /* Public */,
      62,    6,  396,    2, 0x0a /* Public */,
      66,    1,  409,    2, 0x0a /* Public */,
      69,    2,  412,    2, 0x0a /* Public */,
      70,    0,  417,    2, 0x0a /* Public */,
      71,    0,  418,    2, 0x0a /* Public */,
      72,    0,  419,    2, 0x0a /* Public */,
      73,    2,  420,    2, 0x0a /* Public */,
      75,    2,  425,    2, 0x0a /* Public */,
      77,    1,  430,    2, 0x0a /* Public */,
      79,    2,  433,    2, 0x0a /* Public */,
      82,    2,  438,    2, 0x0a /* Public */,
      84,    1,  443,    2, 0x0a /* Public */,
      85,    0,  446,    2, 0x0a /* Public */,
      86,    0,  447,    2, 0x0a /* Public */,
      87,    3,  448,    2, 0x0a /* Public */,
      90,    0,  455,    2, 0x0a /* Public */,
      91,    4,  456,    2, 0x0a /* Public */,
      92,    4,  465,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7, 0x80000000 | 7, 0x80000000 | 12,    9,   10,   11,   13,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 20,   13,
    QMetaType::Void, 0x80000000 | 22,    2,
    QMetaType::Void, 0x80000000 | 22,    2,
    QMetaType::Void, QMetaType::Int,   25,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,   28,
    QMetaType::Void, QMetaType::Bool, QMetaType::Bool,    2,    2,
    QMetaType::Void, 0x80000000 | 31, 0x80000000 | 32,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, 0x80000000 | 17, 0x80000000 | 17, 0x80000000 | 17, 0x80000000 | 17,   34,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 37,    2,    2,
    QMetaType::Void, QMetaType::Bool,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 40, 0x80000000 | 40, 0x80000000 | 41,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 40, 0x80000000 | 40, 0x80000000 | 41,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4, 0x80000000 | 44,    2,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7, 0x80000000 | 7, 0x80000000 | 12,    9,   10,   11,   13,
    QMetaType::Void, 0x80000000 | 7, QMetaType::QString,   48,   34,
    QMetaType::Void, QMetaType::QString,   50,
    QMetaType::Void, 0x80000000 | 7, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,   52,   53,   54,   55,
    QMetaType::Void, QMetaType::QString, QMetaType::QStringList, QMetaType::QStringList, 0x80000000 | 59, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,   34,   57,   58,   60,   53,   54,   55,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, 0x80000000 | 17, 0x80000000 | 17, 0x80000000 | 17, 0x80000000 | 17,   34,    3,   18,   63,   64,   65,
    QMetaType::Void, 0x80000000 | 67,   68,
    QMetaType::Void, 0x80000000 | 31, 0x80000000 | 32,    2,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   74,   48,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 37,    3,   76,
    QMetaType::Void, 0x80000000 | 7,   78,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,   80,   81,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,   80,   83,
    QMetaType::Void, QMetaType::Int,   80,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4, 0x80000000 | 44,    3,   88,   89,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 40, 0x80000000 | 40, 0x80000000 | 41,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 40, 0x80000000 | 40, 0x80000000 | 41,    3,   93,   94,   95,

       0        // eod
};

void ui::ChatWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ChatWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerGetGroupMem((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::Member(*)>(_a[2]))); break;
        case 1: _t->addIsReceiptMsg((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 2: _t->signalSerSendisReceiptMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3])),(*reinterpret_cast< CSharedPtr<data::Msg>(*)>(_a[4]))); break;
        case 3: _t->sendMsgHotKeyUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->signalShakeWin(); break;
        case 5: _t->openUrl((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 6: _t->viewBurnMsg((*reinterpret_cast< CSharedPtr<data::Msg>(*)>(_a[1]))); break;
        case 7: _t->addChatListItem((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        case 8: _t->startChat((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        case 9: _t->signalScreenShot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->signalSendImage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 11: _t->signalSendMsgShot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->signalSetSecretIsvisible((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 13: _t->signalSerGroupRefreshUpdate((*reinterpret_cast< int8(*)>(_a[1])),(*reinterpret_cast< const data::Group(*)>(_a[2]))); break;
        case 14: _t->signalSerGetUrlInfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const std::string(*)>(_a[3])),(*reinterpret_cast< const std::string(*)>(_a[4])),(*reinterpret_cast< const std::string(*)>(_a[5])),(*reinterpret_cast< const std::string(*)>(_a[6]))); break;
        case 15: _t->signalSerGroupMemCountRefresh((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2]))); break;
        case 16: _t->signalSerGetUserInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::UserData(*)>(_a[2]))); break;
        case 17: _t->signalSerbtnCloseSession((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 18: _t->signalSerGetTopMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int32(*)>(_a[2])),(*reinterpret_cast< int32(*)>(_a[3])),(*reinterpret_cast< std::vector<data::ZxTopInformation>(*)>(_a[4]))); break;
        case 19: _t->signalSerCancelTopMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int32(*)>(_a[2])),(*reinterpret_cast< int32(*)>(_a[3])),(*reinterpret_cast< std::vector<data::ZxTopInformation>(*)>(_a[4]))); break;
        case 20: _t->signalSerGetMemberInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::Member(*)>(_a[2])),(*reinterpret_cast< std::string(*)>(_a[3]))); break;
        case 21: _t->onSerGetGroupMem((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::Member(*)>(_a[2]))); break;
        case 22: _t->onSerSendisReceiptMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3])),(*reinterpret_cast< CSharedPtr<data::Msg>(*)>(_a[4]))); break;
        case 23: _t->onSendDelayMsg((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 24: _t->onSendDnyMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 25: _t->onSendCard((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 26: _t->onSendMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2])),(*reinterpret_cast< QStringList(*)>(_a[3])),(*reinterpret_cast< std::vector<int64>(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6])),(*reinterpret_cast< bool(*)>(_a[7]))); break;
        case 27: _t->onShowGroupAtMsgTip((*reinterpret_cast< CSharedPtr<data::Msg>(*)>(_a[1]))); break;
        case 28: _t->onSerGetUrlInfo((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const std::string(*)>(_a[3])),(*reinterpret_cast< const std::string(*)>(_a[4])),(*reinterpret_cast< const std::string(*)>(_a[5])),(*reinterpret_cast< const std::string(*)>(_a[6]))); break;
        case 29: _t->onSetPrivateKey((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 30: _t->onSerGroupRefreshUpdate((*reinterpret_cast< int8(*)>(_a[1])),(*reinterpret_cast< const data::Group(*)>(_a[2]))); break;
        case 31: _t->onSerGetContactInfo(); break;
        case 32: _t->onShakeWinClicked(); break;
        case 33: _t->onShowRecordWin(); break;
        case 34: _t->onRecordResult((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 35: _t->onSerGetUserInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::UserData(*)>(_a[2]))); break;
        case 36: _t->onSerChickMsgReaded((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 37: _t->SetTileContent((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2]))); break;
        case 38: _t->onSerGroupMemCountRefresh((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2]))); break;
        case 39: _t->onSerSendMsgByType((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 40: _t->onSerMoretopMsg(); break;
        case 41: _t->onSerCanceltopMsg(); break;
        case 42: _t->onSerGetMemberInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::Member(*)>(_a[2])),(*reinterpret_cast< std::string(*)>(_a[3]))); break;
        case 43: _t->onHideAtWin(); break;
        case 44: _t->onSerGetTopMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int32(*)>(_a[2])),(*reinterpret_cast< int32(*)>(_a[3])),(*reinterpret_cast< std::vector<data::ZxTopInformation>(*)>(_a[4]))); break;
        case 45: _t->onSerCancelTopMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int32(*)>(_a[2])),(*reinterpret_cast< int32(*)>(_a[3])),(*reinterpret_cast< std::vector<data::ZxTopInformation>(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ChatWidget::*)(int , data::Member & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatWidget::signalSerGetGroupMem)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ChatWidget::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatWidget::addIsReceiptMsg)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ChatWidget::*)(int , int64 , int64 , CSharedPtr<data::Msg> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatWidget::signalSerSendisReceiptMsg)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ChatWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatWidget::sendMsgHotKeyUpdate)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ChatWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatWidget::signalShakeWin)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ChatWidget::*)(std::string );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatWidget::openUrl)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ChatWidget::*)(CSharedPtr<data::Msg> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatWidget::viewBurnMsg)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ChatWidget::*)(CSharedPtr<data::ChatInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatWidget::addChatListItem)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (ChatWidget::*)(CSharedPtr<data::ChatInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatWidget::startChat)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (ChatWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatWidget::signalScreenShot)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (ChatWidget::*)(const QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatWidget::signalSendImage)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (ChatWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatWidget::signalSendMsgShot)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (ChatWidget::*)(bool , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatWidget::signalSetSecretIsvisible)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (ChatWidget::*)(int8 , const data::Group & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatWidget::signalSerGroupRefreshUpdate)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (ChatWidget::*)(QString , int , const std::string & , const std::string & , const std::string & , const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatWidget::signalSerGetUrlInfo)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (ChatWidget::*)(int , int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatWidget::signalSerGroupMemCountRefresh)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (ChatWidget::*)(int , data::UserData & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatWidget::signalSerGetUserInfo)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (ChatWidget::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatWidget::signalSerbtnCloseSession)) {
                *result = 17;
                return;
            }
        }
        {
            using _t = void (ChatWidget::*)(int , int32 , int32 , std::vector<data::ZxTopInformation> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatWidget::signalSerGetTopMsg)) {
                *result = 18;
                return;
            }
        }
        {
            using _t = void (ChatWidget::*)(int , int32 , int32 , std::vector<data::ZxTopInformation> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatWidget::signalSerCancelTopMsg)) {
                *result = 19;
                return;
            }
        }
        {
            using _t = void (ChatWidget::*)(int , data::Member & , std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatWidget::signalSerGetMemberInfo)) {
                *result = 20;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::ChatWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ui__ChatWidget.data,
    qt_meta_data_ui__ChatWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::ChatWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::ChatWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__ChatWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ui::ChatWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 46)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 46;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 46)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 46;
    }
    return _id;
}

// SIGNAL 0
void ui::ChatWidget::signalSerGetGroupMem(int _t1, data::Member & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::ChatWidget::addIsReceiptMsg(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::ChatWidget::signalSerSendisReceiptMsg(int _t1, int64 _t2, int64 _t3, CSharedPtr<data::Msg> _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ui::ChatWidget::sendMsgHotKeyUpdate(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ui::ChatWidget::signalShakeWin()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void ui::ChatWidget::openUrl(std::string _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ui::ChatWidget::viewBurnMsg(CSharedPtr<data::Msg> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ui::ChatWidget::addChatListItem(CSharedPtr<data::ChatInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ui::ChatWidget::startChat(CSharedPtr<data::ChatInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void ui::ChatWidget::signalScreenShot(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void ui::ChatWidget::signalSendImage(const QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void ui::ChatWidget::signalSendMsgShot(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void ui::ChatWidget::signalSetSecretIsvisible(bool _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void ui::ChatWidget::signalSerGroupRefreshUpdate(int8 _t1, const data::Group & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void ui::ChatWidget::signalSerGetUrlInfo(QString _t1, int _t2, const std::string & _t3, const std::string & _t4, const std::string & _t5, const std::string & _t6)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void ui::ChatWidget::signalSerGroupMemCountRefresh(int _t1, int64 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void ui::ChatWidget::signalSerGetUserInfo(int _t1, data::UserData & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void ui::ChatWidget::signalSerbtnCloseSession(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}

// SIGNAL 18
void ui::ChatWidget::signalSerGetTopMsg(int _t1, int32 _t2, int32 _t3, std::vector<data::ZxTopInformation> & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 18, _a);
}

// SIGNAL 19
void ui::ChatWidget::signalSerCancelTopMsg(int _t1, int32 _t2, int32 _t3, std::vector<data::ZxTopInformation> & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 19, _a);
}

// SIGNAL 20
void ui::ChatWidget::signalSerGetMemberInfo(int _t1, data::Member & _t2, std::string & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 20, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
