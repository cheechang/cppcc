/****************************************************************************
** Meta object code from reading C++ file 'abstractmessagewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/chat/bubble/abstractmessagewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'abstractmessagewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AbstractMessageWidget_t {
    QByteArrayData data[52];
    char stringdata0[679];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AbstractMessageWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AbstractMessageWidget_t qt_meta_stringdata_AbstractMessageWidget = {
    {
QT_MOC_LITERAL(0, 0, 21), // "AbstractMessageWidget"
QT_MOC_LITERAL(1, 22, 5), // "shake"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 11), // "sizechanged"
QT_MOC_LITERAL(4, 41, 7), // "SendMsg"
QT_MOC_LITERAL(5, 49, 22), // "CSharedPtr<data::Msg>&"
QT_MOC_LITERAL(6, 72, 3), // "msg"
QT_MOC_LITERAL(7, 76, 11), // "downLoadImg"
QT_MOC_LITERAL(8, 88, 12), // "std::string&"
QT_MOC_LITERAL(9, 101, 16), // "signalSerSendMsg"
QT_MOC_LITERAL(10, 118, 16), // "msgStatusChanged"
QT_MOC_LITERAL(11, 135, 19), // "signalGetMemberlist"
QT_MOC_LITERAL(12, 155, 23), // "signalSerForwardMessage"
QT_MOC_LITERAL(13, 179, 5), // "int64"
QT_MOC_LITERAL(14, 185, 9), // "deleteMsg"
QT_MOC_LITERAL(15, 195, 2), // "id"
QT_MOC_LITERAL(16, 198, 9), // "revokeMsg"
QT_MOC_LITERAL(17, 208, 13), // "updateMsgTime"
QT_MOC_LITERAL(18, 222, 7), // "localId"
QT_MOC_LITERAL(19, 230, 4), // "time"
QT_MOC_LITERAL(20, 235, 18), // "signalSerCloudDisk"
QT_MOC_LITERAL(21, 254, 19), // "signalSerRecallEdit"
QT_MOC_LITERAL(22, 274, 15), // "signalSerMsgTop"
QT_MOC_LITERAL(23, 290, 23), // "data::ZxTopInformation&"
QT_MOC_LITERAL(24, 314, 19), // "signalSerGetTopUser"
QT_MOC_LITERAL(25, 334, 15), // "data::UserData&"
QT_MOC_LITERAL(26, 350, 20), // "signalSerGetGroupMem"
QT_MOC_LITERAL(27, 371, 4), // "code"
QT_MOC_LITERAL(28, 376, 13), // "data::Member&"
QT_MOC_LITERAL(29, 390, 3), // "mem"
QT_MOC_LITERAL(30, 394, 5), // "isRev"
QT_MOC_LITERAL(31, 400, 21), // "signalChangeMsgStatus"
QT_MOC_LITERAL(32, 422, 17), // "onChangeMsgStatus"
QT_MOC_LITERAL(33, 440, 12), // "onSerSendMsg"
QT_MOC_LITERAL(34, 453, 3), // "err"
QT_MOC_LITERAL(35, 457, 7), // "msgtime"
QT_MOC_LITERAL(36, 465, 5), // "msgid"
QT_MOC_LITERAL(37, 471, 9), // "uiLocalId"
QT_MOC_LITERAL(38, 481, 16), // "onForwardMessage"
QT_MOC_LITERAL(39, 498, 15), // "onDeleteMessage"
QT_MOC_LITERAL(40, 514, 15), // "onRevokeMessage"
QT_MOC_LITERAL(41, 530, 25), // "onGetForwardMsgToIdResult"
QT_MOC_LITERAL(42, 556, 4), // "toId"
QT_MOC_LITERAL(43, 561, 5), // "msgId"
QT_MOC_LITERAL(44, 567, 19), // "onSerForwardMessage"
QT_MOC_LITERAL(45, 587, 15), // "onMessageStatus"
QT_MOC_LITERAL(46, 603, 15), // "onSaveCloudDisk"
QT_MOC_LITERAL(47, 619, 12), // "onRecallEdit"
QT_MOC_LITERAL(48, 632, 8), // "onMsgTop"
QT_MOC_LITERAL(49, 641, 15), // "onSerGetTopUser"
QT_MOC_LITERAL(50, 657, 4), // "user"
QT_MOC_LITERAL(51, 662, 16) // "onSerGetGroupMem"

    },
    "AbstractMessageWidget\0shake\0\0sizechanged\0"
    "SendMsg\0CSharedPtr<data::Msg>&\0msg\0"
    "downLoadImg\0std::string&\0signalSerSendMsg\0"
    "msgStatusChanged\0signalGetMemberlist\0"
    "signalSerForwardMessage\0int64\0deleteMsg\0"
    "id\0revokeMsg\0updateMsgTime\0localId\0"
    "time\0signalSerCloudDisk\0signalSerRecallEdit\0"
    "signalSerMsgTop\0data::ZxTopInformation&\0"
    "signalSerGetTopUser\0data::UserData&\0"
    "signalSerGetGroupMem\0code\0data::Member&\0"
    "mem\0isRev\0signalChangeMsgStatus\0"
    "onChangeMsgStatus\0onSerSendMsg\0err\0"
    "msgtime\0msgid\0uiLocalId\0onForwardMessage\0"
    "onDeleteMessage\0onRevokeMessage\0"
    "onGetForwardMsgToIdResult\0toId\0msgId\0"
    "onSerForwardMessage\0onMessageStatus\0"
    "onSaveCloudDisk\0onRecallEdit\0onMsgTop\0"
    "onSerGetTopUser\0user\0onSerGetGroupMem"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AbstractMessageWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      30,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      17,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,  164,    2, 0x06 /* Public */,
       3,    0,  165,    2, 0x06 /* Public */,
       4,    1,  166,    2, 0x06 /* Public */,
       7,    5,  169,    2, 0x06 /* Public */,
       9,    4,  180,    2, 0x06 /* Public */,
      10,    2,  189,    2, 0x06 /* Public */,
      11,    1,  194,    2, 0x06 /* Public */,
      12,    3,  197,    2, 0x06 /* Public */,
      14,    1,  204,    2, 0x06 /* Public */,
      16,    1,  207,    2, 0x06 /* Public */,
      17,    2,  210,    2, 0x06 /* Public */,
      20,    0,  215,    2, 0x06 /* Public */,
      21,    0,  216,    2, 0x06 /* Public */,
      22,    1,  217,    2, 0x06 /* Public */,
      24,    2,  220,    2, 0x06 /* Public */,
      26,    3,  225,    2, 0x06 /* Public */,
      31,    2,  232,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      32,    2,  237,    2, 0x0a /* Public */,
      33,    4,  242,    2, 0x0a /* Public */,
      38,    0,  251,    2, 0x0a /* Public */,
      39,    0,  252,    2, 0x0a /* Public */,
      40,    0,  253,    2, 0x0a /* Public */,
      41,    2,  254,    2, 0x0a /* Public */,
      44,    3,  259,    2, 0x0a /* Public */,
      45,    0,  266,    2, 0x0a /* Public */,
      46,    0,  267,    2, 0x0a /* Public */,
      47,    0,  268,    2, 0x0a /* Public */,
      48,    0,  269,    2, 0x0a /* Public */,
      49,    2,  270,    2, 0x0a /* Public */,
      51,    3,  275,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong, 0x80000000 | 8, 0x80000000 | 8, QMetaType::Bool,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::LongLong, QMetaType::LongLong, QMetaType::LongLong,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::LongLong,    2,    2,
    QMetaType::Void, QMetaType::LongLong,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 13, 0x80000000 | 13,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 13,   15,
    QMetaType::Void, 0x80000000 | 13,   15,
    QMetaType::Void, QMetaType::LongLong, QMetaType::LongLong,   18,   19,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 23,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 25,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 28, QMetaType::Bool,   27,   29,   30,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 13,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 13,    2,    2,
    QMetaType::Void, QMetaType::Int, QMetaType::LongLong, QMetaType::LongLong, QMetaType::LongLong,   34,   35,   36,   37,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 13,   42,   43,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 13, 0x80000000 | 13,   27,   19,   43,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 25,   27,   50,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 28, QMetaType::Bool,   27,   29,   30,

       0        // eod
};

void AbstractMessageWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AbstractMessageWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->shake(); break;
        case 1: _t->sizechanged(); break;
        case 2: _t->SendMsg((*reinterpret_cast< CSharedPtr<data::Msg>(*)>(_a[1]))); break;
        case 3: _t->downLoadImg((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< std::string(*)>(_a[3])),(*reinterpret_cast< std::string(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        case 4: _t->signalSerSendMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< qint64(*)>(_a[3])),(*reinterpret_cast< qint64(*)>(_a[4]))); break;
        case 5: _t->msgStatusChanged((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 6: _t->signalGetMemberlist((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        case 7: _t->signalSerForwardMessage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3]))); break;
        case 8: _t->deleteMsg((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 9: _t->revokeMsg((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 10: _t->updateMsgTime((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2]))); break;
        case 11: _t->signalSerCloudDisk(); break;
        case 12: _t->signalSerRecallEdit(); break;
        case 13: _t->signalSerMsgTop((*reinterpret_cast< data::ZxTopInformation(*)>(_a[1]))); break;
        case 14: _t->signalSerGetTopUser((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::UserData(*)>(_a[2]))); break;
        case 15: _t->signalSerGetGroupMem((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::Member(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 16: _t->signalChangeMsgStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2]))); break;
        case 17: _t->onChangeMsgStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2]))); break;
        case 18: _t->onSerSendMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< qint64(*)>(_a[3])),(*reinterpret_cast< qint64(*)>(_a[4]))); break;
        case 19: _t->onForwardMessage(); break;
        case 20: _t->onDeleteMessage(); break;
        case 21: _t->onRevokeMessage(); break;
        case 22: _t->onGetForwardMsgToIdResult((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2]))); break;
        case 23: _t->onSerForwardMessage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3]))); break;
        case 24: _t->onMessageStatus(); break;
        case 25: _t->onSaveCloudDisk(); break;
        case 26: _t->onRecallEdit(); break;
        case 27: _t->onMsgTop(); break;
        case 28: _t->onSerGetTopUser((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::UserData(*)>(_a[2]))); break;
        case 29: _t->onSerGetGroupMem((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::Member(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AbstractMessageWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AbstractMessageWidget::shake)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AbstractMessageWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AbstractMessageWidget::sizechanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AbstractMessageWidget::*)(CSharedPtr<data::Msg> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AbstractMessageWidget::SendMsg)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (AbstractMessageWidget::*)(qint64 , qint64 , std::string & , std::string & , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AbstractMessageWidget::downLoadImg)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (AbstractMessageWidget::*)(int , qint64 , qint64 , qint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AbstractMessageWidget::signalSerSendMsg)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (AbstractMessageWidget::*)(int , qint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AbstractMessageWidget::msgStatusChanged)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (AbstractMessageWidget::*)(qint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AbstractMessageWidget::signalGetMemberlist)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (AbstractMessageWidget::*)(int , int64 , int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AbstractMessageWidget::signalSerForwardMessage)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (AbstractMessageWidget::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AbstractMessageWidget::deleteMsg)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (AbstractMessageWidget::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AbstractMessageWidget::revokeMsg)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (AbstractMessageWidget::*)(qint64 , qint64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AbstractMessageWidget::updateMsgTime)) {
                *result = 10;
                return;
            }
        }
        {
            using _t = void (AbstractMessageWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AbstractMessageWidget::signalSerCloudDisk)) {
                *result = 11;
                return;
            }
        }
        {
            using _t = void (AbstractMessageWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AbstractMessageWidget::signalSerRecallEdit)) {
                *result = 12;
                return;
            }
        }
        {
            using _t = void (AbstractMessageWidget::*)(data::ZxTopInformation & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AbstractMessageWidget::signalSerMsgTop)) {
                *result = 13;
                return;
            }
        }
        {
            using _t = void (AbstractMessageWidget::*)(int , data::UserData & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AbstractMessageWidget::signalSerGetTopUser)) {
                *result = 14;
                return;
            }
        }
        {
            using _t = void (AbstractMessageWidget::*)(int , data::Member & , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AbstractMessageWidget::signalSerGetGroupMem)) {
                *result = 15;
                return;
            }
        }
        {
            using _t = void (AbstractMessageWidget::*)(int , int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AbstractMessageWidget::signalChangeMsgStatus)) {
                *result = 16;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject AbstractMessageWidget::staticMetaObject = { {
    &SpeechBubbleWidget::staticMetaObject,
    qt_meta_stringdata_AbstractMessageWidget.data,
    qt_meta_data_AbstractMessageWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AbstractMessageWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AbstractMessageWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AbstractMessageWidget.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "MsgItemBase"))
        return static_cast< MsgItemBase*>(this);
    return SpeechBubbleWidget::qt_metacast(_clname);
}

int AbstractMessageWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = SpeechBubbleWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 30)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 30;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 30)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 30;
    }
    return _id;
}

// SIGNAL 0
void AbstractMessageWidget::shake()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void AbstractMessageWidget::sizechanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void AbstractMessageWidget::SendMsg(CSharedPtr<data::Msg> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void AbstractMessageWidget::downLoadImg(qint64 _t1, qint64 _t2, std::string & _t3, std::string & _t4, bool _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void AbstractMessageWidget::signalSerSendMsg(int _t1, qint64 _t2, qint64 _t3, qint64 _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void AbstractMessageWidget::msgStatusChanged(int _t1, qint64 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void AbstractMessageWidget::signalGetMemberlist(qint64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void AbstractMessageWidget::signalSerForwardMessage(int _t1, int64 _t2, int64 _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void AbstractMessageWidget::deleteMsg(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void AbstractMessageWidget::revokeMsg(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void AbstractMessageWidget::updateMsgTime(qint64 _t1, qint64 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}

// SIGNAL 11
void AbstractMessageWidget::signalSerCloudDisk()
{
    QMetaObject::activate(this, &staticMetaObject, 11, nullptr);
}

// SIGNAL 12
void AbstractMessageWidget::signalSerRecallEdit()
{
    QMetaObject::activate(this, &staticMetaObject, 12, nullptr);
}

// SIGNAL 13
void AbstractMessageWidget::signalSerMsgTop(data::ZxTopInformation & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 13, _a);
}

// SIGNAL 14
void AbstractMessageWidget::signalSerGetTopUser(int _t1, data::UserData & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 14, _a);
}

// SIGNAL 15
void AbstractMessageWidget::signalSerGetGroupMem(int _t1, data::Member & _t2, bool _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 15, _a);
}

// SIGNAL 16
void AbstractMessageWidget::signalChangeMsgStatus(int _t1, int64 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 16, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
