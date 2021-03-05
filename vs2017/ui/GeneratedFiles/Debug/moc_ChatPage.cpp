/****************************************************************************
** Meta object code from reading C++ file 'ChatPage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/chat/ChatPage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ChatPage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__ChatPage_t {
    QByteArrayData data[79];
    char stringdata0[1230];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__ChatPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__ChatPage_t qt_meta_stringdata_ui__ChatPage = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ui::ChatPage"
QT_MOC_LITERAL(1, 13, 14), // "unreadMsgCount"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 5), // "count"
QT_MOC_LITERAL(4, 35, 8), // "turnPage"
QT_MOC_LITERAL(5, 44, 12), // "current_page"
QT_MOC_LITERAL(6, 57, 15), // "addChatListItem"
QT_MOC_LITERAL(7, 73, 27), // "CSharedPtr<data::ChatInfo>&"
QT_MOC_LITERAL(8, 101, 4), // "chat"
QT_MOC_LITERAL(9, 106, 21), // "signalNotifyTrayFlash"
QT_MOC_LITERAL(10, 128, 5), // "flash"
QT_MOC_LITERAL(11, 134, 30), // "signalSerMemberHeadImgUpdateCb"
QT_MOC_LITERAL(12, 165, 5), // "int64"
QT_MOC_LITERAL(13, 171, 8), // "targetId"
QT_MOC_LITERAL(14, 180, 11), // "std::string"
QT_MOC_LITERAL(15, 192, 4), // "head"
QT_MOC_LITERAL(16, 197, 18), // "signalSerMsgNotify"
QT_MOC_LITERAL(17, 216, 21), // "CSharedPtr<data::Msg>"
QT_MOC_LITERAL(18, 238, 3), // "msg"
QT_MOC_LITERAL(19, 242, 15), // "signalSendImage"
QT_MOC_LITERAL(20, 258, 4), // "path"
QT_MOC_LITERAL(21, 263, 25), // "signalSerRegOperateUserCb"
QT_MOC_LITERAL(22, 289, 18), // "data::AccountInfo&"
QT_MOC_LITERAL(23, 308, 23), // "signalSerOperateBuddyCb"
QT_MOC_LITERAL(24, 332, 13), // "data::Contact"
QT_MOC_LITERAL(25, 346, 27), // "signalSerGroupRefreshNotify"
QT_MOC_LITERAL(26, 374, 4), // "int8"
QT_MOC_LITERAL(27, 379, 11), // "data::Group"
QT_MOC_LITERAL(28, 391, 17), // "signalSendMsgShot"
QT_MOC_LITERAL(29, 409, 3), // "key"
QT_MOC_LITERAL(30, 413, 28), // "signalSerGrpMemInfoRefreshCb"
QT_MOC_LITERAL(31, 442, 12), // "data::Member"
QT_MOC_LITERAL(32, 455, 11), // "viewBurnMsg"
QT_MOC_LITERAL(33, 467, 22), // "CSharedPtr<data::Msg>&"
QT_MOC_LITERAL(34, 490, 14), // "signalShakeWin"
QT_MOC_LITERAL(35, 505, 19), // "sendMsgHotKeyUpdate"
QT_MOC_LITERAL(36, 525, 21), // "signalSerCloseSession"
QT_MOC_LITERAL(37, 547, 31), // "signalSerContactHeadImgUpdateCb"
QT_MOC_LITERAL(38, 579, 32), // "signalSerNameSectorExtendedField"
QT_MOC_LITERAL(39, 612, 40), // "std::vector<data::EnterpriseD..."
QT_MOC_LITERAL(40, 653, 28), // "onSerNameSectorExtendedField"
QT_MOC_LITERAL(41, 682, 26), // "onSerMemberHeadImgUpdateCb"
QT_MOC_LITERAL(42, 709, 9), // "onOpenUrl"
QT_MOC_LITERAL(43, 719, 3), // "url"
QT_MOC_LITERAL(44, 723, 14), // "onMsgSoundPlay"
QT_MOC_LITERAL(45, 738, 6), // "isPlay"
QT_MOC_LITERAL(46, 745, 14), // "onSoundTimeOut"
QT_MOC_LITERAL(47, 760, 19), // "onSendSuggestionMsg"
QT_MOC_LITERAL(48, 780, 8), // "QString&"
QT_MOC_LITERAL(49, 789, 8), // "filePath"
QT_MOC_LITERAL(50, 798, 11), // "onStartChat"
QT_MOC_LITERAL(51, 810, 12), // "onRemoveChat"
QT_MOC_LITERAL(52, 823, 14), // "onSerMsgNotify"
QT_MOC_LITERAL(53, 838, 13), // "onScreenShoot"
QT_MOC_LITERAL(54, 852, 4), // "code"
QT_MOC_LITERAL(55, 857, 20), // "QProcess::ExitStatus"
QT_MOC_LITERAL(56, 878, 6), // "status"
QT_MOC_LITERAL(57, 885, 22), // "onScreenShotBtnClicked"
QT_MOC_LITERAL(58, 908, 4), // "flag"
QT_MOC_LITERAL(59, 913, 17), // "onStartScreenShot"
QT_MOC_LITERAL(60, 931, 21), // "onSerRegOperateUserCb"
QT_MOC_LITERAL(61, 953, 11), // "accountInfo"
QT_MOC_LITERAL(62, 965, 19), // "onSerOperateBuddyCb"
QT_MOC_LITERAL(63, 985, 4), // "type"
QT_MOC_LITERAL(64, 990, 7), // "contact"
QT_MOC_LITERAL(65, 998, 23), // "onSerGroupRefreshNotify"
QT_MOC_LITERAL(66, 1022, 5), // "group"
QT_MOC_LITERAL(67, 1028, 24), // "onSerGrpMemInfoRefreshCb"
QT_MOC_LITERAL(68, 1053, 7), // "groupId"
QT_MOC_LITERAL(69, 1061, 4), // "mems"
QT_MOC_LITERAL(70, 1066, 22), // "onStartPlayNotifySound"
QT_MOC_LITERAL(71, 1089, 14), // "onSerDelUiFile"
QT_MOC_LITERAL(72, 1104, 19), // "onSerByTargetIdChat"
QT_MOC_LITERAL(73, 1124, 8), // "targetid"
QT_MOC_LITERAL(74, 1133, 24), // "onSerCheckIsCloseSession"
QT_MOC_LITERAL(75, 1158, 27), // "onSerContactHeadImgUpdateCb"
QT_MOC_LITERAL(76, 1186, 2), // "id"
QT_MOC_LITERAL(77, 1189, 17), // "onAddIsReceiptMsg"
QT_MOC_LITERAL(78, 1207, 22) // "onMainWindowDeactivate"

    },
    "ui::ChatPage\0unreadMsgCount\0\0count\0"
    "turnPage\0current_page\0addChatListItem\0"
    "CSharedPtr<data::ChatInfo>&\0chat\0"
    "signalNotifyTrayFlash\0flash\0"
    "signalSerMemberHeadImgUpdateCb\0int64\0"
    "targetId\0std::string\0head\0signalSerMsgNotify\0"
    "CSharedPtr<data::Msg>\0msg\0signalSendImage\0"
    "path\0signalSerRegOperateUserCb\0"
    "data::AccountInfo&\0signalSerOperateBuddyCb\0"
    "data::Contact\0signalSerGroupRefreshNotify\0"
    "int8\0data::Group\0signalSendMsgShot\0"
    "key\0signalSerGrpMemInfoRefreshCb\0"
    "data::Member\0viewBurnMsg\0"
    "CSharedPtr<data::Msg>&\0signalShakeWin\0"
    "sendMsgHotKeyUpdate\0signalSerCloseSession\0"
    "signalSerContactHeadImgUpdateCb\0"
    "signalSerNameSectorExtendedField\0"
    "std::vector<data::EnterpriseDictionary>&\0"
    "onSerNameSectorExtendedField\0"
    "onSerMemberHeadImgUpdateCb\0onOpenUrl\0"
    "url\0onMsgSoundPlay\0isPlay\0onSoundTimeOut\0"
    "onSendSuggestionMsg\0QString&\0filePath\0"
    "onStartChat\0onRemoveChat\0onSerMsgNotify\0"
    "onScreenShoot\0code\0QProcess::ExitStatus\0"
    "status\0onScreenShotBtnClicked\0flag\0"
    "onStartScreenShot\0onSerRegOperateUserCb\0"
    "accountInfo\0onSerOperateBuddyCb\0type\0"
    "contact\0onSerGroupRefreshNotify\0group\0"
    "onSerGrpMemInfoRefreshCb\0groupId\0mems\0"
    "onStartPlayNotifySound\0onSerDelUiFile\0"
    "onSerByTargetIdChat\0targetid\0"
    "onSerCheckIsCloseSession\0"
    "onSerContactHeadImgUpdateCb\0id\0"
    "onAddIsReceiptMsg\0onMainWindowDeactivate"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__ChatPage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      41,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      18,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  219,    2, 0x06 /* Public */,
       4,    1,  222,    2, 0x06 /* Public */,
       6,    1,  225,    2, 0x06 /* Public */,
       9,    1,  228,    2, 0x06 /* Public */,
      11,    2,  231,    2, 0x06 /* Public */,
      16,    1,  236,    2, 0x06 /* Public */,
      19,    1,  239,    2, 0x06 /* Public */,
      21,    1,  242,    2, 0x06 /* Public */,
      23,    2,  245,    2, 0x06 /* Public */,
      25,    2,  250,    2, 0x06 /* Public */,
      28,    1,  255,    2, 0x06 /* Public */,
      30,    2,  258,    2, 0x06 /* Public */,
      32,    1,  263,    2, 0x06 /* Public */,
      34,    0,  266,    2, 0x06 /* Public */,
      35,    1,  267,    2, 0x06 /* Public */,
      36,    1,  270,    2, 0x06 /* Public */,
      37,    2,  273,    2, 0x06 /* Public */,
      38,    2,  278,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      40,    2,  283,    2, 0x0a /* Public */,
      41,    2,  288,    2, 0x0a /* Public */,
      42,    1,  293,    2, 0x0a /* Public */,
      44,    1,  296,    2, 0x0a /* Public */,
      46,    0,  299,    2, 0x0a /* Public */,
      47,    2,  300,    2, 0x0a /* Public */,
      50,    1,  305,    2, 0x0a /* Public */,
      51,    1,  308,    2, 0x0a /* Public */,
      52,    1,  311,    2, 0x0a /* Public */,
      53,    2,  314,    2, 0x0a /* Public */,
      57,    1,  319,    2, 0x0a /* Public */,
      59,    0,  322,    2, 0x0a /* Public */,
      60,    1,  323,    2, 0x0a /* Public */,
      62,    2,  326,    2, 0x0a /* Public */,
      65,    2,  331,    2, 0x0a /* Public */,
      67,    2,  336,    2, 0x0a /* Public */,
      70,    0,  341,    2, 0x0a /* Public */,
      71,    2,  342,    2, 0x0a /* Public */,
      72,    1,  347,    2, 0x0a /* Public */,
      74,    1,  350,    2, 0x0a /* Public */,
      75,    2,  353,    2, 0x0a /* Public */,
      77,    1,  358,    2, 0x0a /* Public */,
      78,    0,  361,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 14,   13,   15,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, QMetaType::QString,   20,
    QMetaType::Void, 0x80000000 | 22,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 24,    2,    2,
    QMetaType::Void, 0x80000000 | 26, 0x80000000 | 27,    2,    2,
    QMetaType::Void, QMetaType::Int,   29,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 31,    2,    2,
    QMetaType::Void, 0x80000000 | 33,   18,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 14,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 39,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 39,    2,    2,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 14,   13,   15,
    QMetaType::Void, 0x80000000 | 14,   43,
    QMetaType::Void, QMetaType::Bool,   45,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7, 0x80000000 | 48,    8,   49,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, 0x80000000 | 17,   18,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 55,   54,   56,
    QMetaType::Void, QMetaType::Int,   58,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 22,   61,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 24,   63,   64,
    QMetaType::Void, 0x80000000 | 26, 0x80000000 | 27,   63,   66,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 31,   68,   69,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 12,    2,    2,
    QMetaType::Void, 0x80000000 | 12,   73,
    QMetaType::Bool, 0x80000000 | 17,   18,
    QMetaType::Void, 0x80000000 | 12, 0x80000000 | 14,   76,   15,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,

       0        // eod
};

void ui::ChatPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ChatPage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->unreadMsgCount((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->turnPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->addChatListItem((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        case 3: _t->signalNotifyTrayFlash((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->signalSerMemberHeadImgUpdateCb((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2]))); break;
        case 5: _t->signalSerMsgNotify((*reinterpret_cast< CSharedPtr<data::Msg>(*)>(_a[1]))); break;
        case 6: _t->signalSendImage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->signalSerRegOperateUserCb((*reinterpret_cast< data::AccountInfo(*)>(_a[1]))); break;
        case 8: _t->signalSerOperateBuddyCb((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const data::Contact(*)>(_a[2]))); break;
        case 9: _t->signalSerGroupRefreshNotify((*reinterpret_cast< int8(*)>(_a[1])),(*reinterpret_cast< const data::Group(*)>(_a[2]))); break;
        case 10: _t->signalSendMsgShot((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->signalSerGrpMemInfoRefreshCb((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< const data::Member(*)>(_a[2]))); break;
        case 12: _t->viewBurnMsg((*reinterpret_cast< CSharedPtr<data::Msg>(*)>(_a[1]))); break;
        case 13: _t->signalShakeWin(); break;
        case 14: _t->sendMsgHotKeyUpdate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 15: _t->signalSerCloseSession((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 16: _t->signalSerContactHeadImgUpdateCb((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2]))); break;
        case 17: _t->signalSerNameSectorExtendedField((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<data::EnterpriseDictionary>(*)>(_a[2]))); break;
        case 18: _t->onSerNameSectorExtendedField((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<data::EnterpriseDictionary>(*)>(_a[2]))); break;
        case 19: _t->onSerMemberHeadImgUpdateCb((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2]))); break;
        case 20: _t->onOpenUrl((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 21: _t->onMsgSoundPlay((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 22: _t->onSoundTimeOut(); break;
        case 23: _t->onSendSuggestionMsg((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 24: _t->onStartChat((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        case 25: _t->onRemoveChat((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 26: _t->onSerMsgNotify((*reinterpret_cast< CSharedPtr<data::Msg>(*)>(_a[1]))); break;
        case 27: _t->onScreenShoot((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        case 28: _t->onScreenShotBtnClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 29: _t->onStartScreenShot(); break;
        case 30: _t->onSerRegOperateUserCb((*reinterpret_cast< data::AccountInfo(*)>(_a[1]))); break;
        case 31: _t->onSerOperateBuddyCb((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const data::Contact(*)>(_a[2]))); break;
        case 32: _t->onSerGroupRefreshNotify((*reinterpret_cast< int8(*)>(_a[1])),(*reinterpret_cast< const data::Group(*)>(_a[2]))); break;
        case 33: _t->onSerGrpMemInfoRefreshCb((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< const data::Member(*)>(_a[2]))); break;
        case 34: _t->onStartPlayNotifySound(); break;
        case 35: _t->onSerDelUiFile((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2]))); break;
        case 36: _t->onSerByTargetIdChat((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 37: { bool _r = _t->onSerCheckIsCloseSession((*reinterpret_cast< CSharedPtr<data::Msg>(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 38: _t->onSerContactHeadImgUpdateCb((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2]))); break;
        case 39: _t->onAddIsReceiptMsg((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 40: _t->onMainWindowDeactivate(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ChatPage::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatPage::unreadMsgCount)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ChatPage::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatPage::turnPage)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ChatPage::*)(CSharedPtr<data::ChatInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatPage::addChatListItem)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ChatPage::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatPage::signalNotifyTrayFlash)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ChatPage::*)(int64 , const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatPage::signalSerMemberHeadImgUpdateCb)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ChatPage::*)(CSharedPtr<data::Msg> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatPage::signalSerMsgNotify)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ChatPage::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatPage::signalSendImage)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ChatPage::*)(data::AccountInfo & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatPage::signalSerRegOperateUserCb)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (ChatPage::*)(int , const data::Contact & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatPage::signalSerOperateBuddyCb)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (ChatPage::*)(int8 , const data::Group & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatPage::signalSerGroupRefreshNotify)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (ChatPage::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatPage::signalSendMsgShot)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (ChatPage::*)(int64 , const data::Member & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatPage::signalSerGrpMemInfoRefreshCb)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (ChatPage::*)(CSharedPtr<data::Msg> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatPage::viewBurnMsg)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (ChatPage::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatPage::signalShakeWin)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (ChatPage::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatPage::sendMsgHotKeyUpdate)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (ChatPage::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatPage::signalSerCloseSession)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (ChatPage::*)(int64 , const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatPage::signalSerContactHeadImgUpdateCb)) {
                *result = 16;
                return;
            }
        }
        {
            using _t = void (ChatPage::*)(int , std::vector<data::EnterpriseDictionary> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatPage::signalSerNameSectorExtendedField)) {
                *result = 17;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::ChatPage::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ui__ChatPage.data,
    qt_meta_data_ui__ChatPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::ChatPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::ChatPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__ChatPage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ui::ChatPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 41)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 41;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 41)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 41;
    }
    return _id;
}

// SIGNAL 0
void ui::ChatPage::unreadMsgCount(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::ChatPage::turnPage(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::ChatPage::addChatListItem(CSharedPtr<data::ChatInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ui::ChatPage::signalNotifyTrayFlash(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ui::ChatPage::signalSerMemberHeadImgUpdateCb(int64 _t1, const std::string & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ui::ChatPage::signalSerMsgNotify(CSharedPtr<data::Msg> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ui::ChatPage::signalSendImage(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ui::ChatPage::signalSerRegOperateUserCb(data::AccountInfo & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ui::ChatPage::signalSerOperateBuddyCb(int _t1, const data::Contact & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void ui::ChatPage::signalSerGroupRefreshNotify(int8 _t1, const data::Group & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void ui::ChatPage::signalSendMsgShot(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void ui::ChatPage::signalSerGrpMemInfoRefreshCb(int64 _t1, const data::Member & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 11, _a);
}

// SIGNAL 12
void ui::ChatPage::viewBurnMsg(CSharedPtr<data::Msg> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 12, _a);
}

// SIGNAL 13
void ui::ChatPage::signalShakeWin()
{
    QMetaObject::activate(this, &staticMetaObject, 13, nullptr);
}

// SIGNAL 14
void ui::ChatPage::sendMsgHotKeyUpdate(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void ui::ChatPage::signalSerCloseSession(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void ui::ChatPage::signalSerContactHeadImgUpdateCb(int64 _t1, const std::string & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}

// SIGNAL 17
void ui::ChatPage::signalSerNameSectorExtendedField(int _t1, std::vector<data::EnterpriseDictionary> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 17, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
