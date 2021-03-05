/****************************************************************************
** Meta object code from reading C++ file 'MsgStatusWin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/chat/MsgStatusWin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MsgStatusWin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__MsgStatusListWidget_t {
    QByteArrayData data[3];
    char stringdata0[42];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__MsgStatusListWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__MsgStatusListWidget_t qt_meta_stringdata_ui__MsgStatusListWidget = {
    {
QT_MOC_LITERAL(0, 0, 23), // "ui::MsgStatusListWidget"
QT_MOC_LITERAL(1, 24, 16), // "onLazyLoadMember"
QT_MOC_LITERAL(2, 41, 0) // ""

    },
    "ui::MsgStatusListWidget\0onLazyLoadMember\0"
    ""
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__MsgStatusListWidget[] = {

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
       1,    0,   19,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void ui::MsgStatusListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MsgStatusListWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onLazyLoadMember(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ui::MsgStatusListWidget::staticMetaObject = { {
    &TWidget::staticMetaObject,
    qt_meta_stringdata_ui__MsgStatusListWidget.data,
    qt_meta_data_ui__MsgStatusListWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::MsgStatusListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::MsgStatusListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__MsgStatusListWidget.stringdata0))
        return static_cast<void*>(this);
    return TWidget::qt_metacast(_clname);
}

int ui::MsgStatusListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
struct qt_meta_stringdata_ui__MsgStatusWin_t {
    QByteArrayData data[27];
    char stringdata0[444];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__MsgStatusWin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__MsgStatusWin_t qt_meta_stringdata_ui__MsgStatusWin = {
    {
QT_MOC_LITERAL(0, 0, 16), // "ui::MsgStatusWin"
QT_MOC_LITERAL(1, 17, 29), // "signalSerGetGroupMsgReadState"
QT_MOC_LITERAL(2, 47, 0), // ""
QT_MOC_LITERAL(3, 48, 42), // "std::map<std::string,std::vec..."
QT_MOC_LITERAL(4, 91, 21), // "signalSerSendShortMsg"
QT_MOC_LITERAL(5, 113, 27), // "std::map<int64,std::string>"
QT_MOC_LITERAL(6, 141, 27), // "signalSerGetGroupUnreadInfo"
QT_MOC_LITERAL(7, 169, 19), // "std::vector<int64>&"
QT_MOC_LITERAL(8, 189, 5), // "int64"
QT_MOC_LITERAL(9, 195, 22), // "signalSerGetMemberList"
QT_MOC_LITERAL(10, 218, 23), // "std::vector<MemberPtr>&"
QT_MOC_LITERAL(11, 242, 21), // "signalChangeMsgStatus"
QT_MOC_LITERAL(12, 264, 17), // "onSerSendShortMsg"
QT_MOC_LITERAL(13, 282, 4), // "code"
QT_MOC_LITERAL(14, 287, 7), // "results"
QT_MOC_LITERAL(15, 295, 23), // "onSerGetGroupUnreadInfo"
QT_MOC_LITERAL(16, 319, 7), // "ReadIds"
QT_MOC_LITERAL(17, 327, 9), // "unReadIds"
QT_MOC_LITERAL(18, 337, 9), // "onChasing"
QT_MOC_LITERAL(19, 347, 7), // "reqData"
QT_MOC_LITERAL(20, 355, 7), // "groupId"
QT_MOC_LITERAL(21, 363, 18), // "data::SnapshotInfo"
QT_MOC_LITERAL(22, 382, 4), // "info"
QT_MOC_LITERAL(23, 387, 18), // "onSerGetMemberList"
QT_MOC_LITERAL(24, 406, 4), // "mems"
QT_MOC_LITERAL(25, 411, 25), // "onSerGetGroupMsgReadState"
QT_MOC_LITERAL(26, 437, 6) // "states"

    },
    "ui::MsgStatusWin\0signalSerGetGroupMsgReadState\0"
    "\0std::map<std::string,std::vector<int64> >&\0"
    "signalSerSendShortMsg\0std::map<int64,std::string>\0"
    "signalSerGetGroupUnreadInfo\0"
    "std::vector<int64>&\0int64\0"
    "signalSerGetMemberList\0std::vector<MemberPtr>&\0"
    "signalChangeMsgStatus\0onSerSendShortMsg\0"
    "code\0results\0onSerGetGroupUnreadInfo\0"
    "ReadIds\0unReadIds\0onChasing\0reqData\0"
    "groupId\0data::SnapshotInfo\0info\0"
    "onSerGetMemberList\0mems\0"
    "onSerGetGroupMsgReadState\0states"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__MsgStatusWin[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   69,    2, 0x06 /* Public */,
       4,    2,   74,    2, 0x06 /* Public */,
       6,    4,   79,    2, 0x06 /* Public */,
       9,    2,   88,    2, 0x06 /* Public */,
      11,    2,   93,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    2,   98,    2, 0x0a /* Public */,
      15,    4,  103,    2, 0x0a /* Public */,
      18,    0,  112,    2, 0x0a /* Public */,
      19,    2,  113,    2, 0x0a /* Public */,
      23,    2,  118,    2, 0x0a /* Public */,
      25,    2,  123,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 5,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7, 0x80000000 | 7, 0x80000000 | 8,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 8,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 5,   13,   14,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7, 0x80000000 | 7, 0x80000000 | 8,    2,   16,   17,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8, 0x80000000 | 21,   20,   22,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10,   13,   24,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3,   13,   26,

       0        // eod
};

void ui::MsgStatusWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MsgStatusWin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerGetGroupMsgReadState((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::map<std::string,std::vector<int64> >(*)>(_a[2]))); break;
        case 1: _t->signalSerSendShortMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::map<int64,std::string>(*)>(_a[2]))); break;
        case 2: _t->signalSerGetGroupUnreadInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<int64>(*)>(_a[2])),(*reinterpret_cast< std::vector<int64>(*)>(_a[3])),(*reinterpret_cast< int64(*)>(_a[4]))); break;
        case 3: _t->signalSerGetMemberList((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<MemberPtr>(*)>(_a[2]))); break;
        case 4: _t->signalChangeMsgStatus((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2]))); break;
        case 5: _t->onSerSendShortMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::map<int64,std::string>(*)>(_a[2]))); break;
        case 6: _t->onSerGetGroupUnreadInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<int64>(*)>(_a[2])),(*reinterpret_cast< std::vector<int64>(*)>(_a[3])),(*reinterpret_cast< int64(*)>(_a[4]))); break;
        case 7: _t->onChasing(); break;
        case 8: _t->reqData((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< data::SnapshotInfo(*)>(_a[2]))); break;
        case 9: _t->onSerGetMemberList((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<MemberPtr>(*)>(_a[2]))); break;
        case 10: _t->onSerGetGroupMsgReadState((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::map<std::string,std::vector<int64> >(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MsgStatusWin::*)(int , std::map<std::string,std::vector<int64>> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MsgStatusWin::signalSerGetGroupMsgReadState)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MsgStatusWin::*)(int , std::map<int64,std::string> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MsgStatusWin::signalSerSendShortMsg)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MsgStatusWin::*)(int , std::vector<int64> & , std::vector<int64> & , int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MsgStatusWin::signalSerGetGroupUnreadInfo)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MsgStatusWin::*)(int , std::vector<MemberPtr> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MsgStatusWin::signalSerGetMemberList)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MsgStatusWin::*)(int , int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MsgStatusWin::signalChangeMsgStatus)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::MsgStatusWin::staticMetaObject = { {
    &BaseWindow::staticMetaObject,
    qt_meta_stringdata_ui__MsgStatusWin.data,
    qt_meta_data_ui__MsgStatusWin,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::MsgStatusWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::MsgStatusWin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__MsgStatusWin.stringdata0))
        return static_cast<void*>(this);
    return BaseWindow::qt_metacast(_clname);
}

int ui::MsgStatusWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void ui::MsgStatusWin::signalSerGetGroupMsgReadState(int _t1, std::map<std::string,std::vector<int64>> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::MsgStatusWin::signalSerSendShortMsg(int _t1, std::map<int64,std::string> _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::MsgStatusWin::signalSerGetGroupUnreadInfo(int _t1, std::vector<int64> & _t2, std::vector<int64> & _t3, int64 _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ui::MsgStatusWin::signalSerGetMemberList(int _t1, std::vector<MemberPtr> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ui::MsgStatusWin::signalChangeMsgStatus(int _t1, int64 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
