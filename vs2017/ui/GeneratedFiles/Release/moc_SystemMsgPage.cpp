/****************************************************************************
** Meta object code from reading C++ file 'SystemMsgPage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/systemmsg/SystemMsgPage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SystemMsgPage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__SystemMsgPage_t {
    QByteArrayData data[30];
    char stringdata0[457];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__SystemMsgPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__SystemMsgPage_t qt_meta_stringdata_ui__SystemMsgPage = {
    {
QT_MOC_LITERAL(0, 0, 17), // "ui::SystemMsgPage"
QT_MOC_LITERAL(1, 18, 21), // "signalSerGetAllSysMsg"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 3), // "err"
QT_MOC_LITERAL(4, 45, 26), // "std::vector<data::SysMsg>&"
QT_MOC_LITERAL(5, 72, 6), // "sysMsg"
QT_MOC_LITERAL(6, 79, 22), // "signalSerSetSysMsgRead"
QT_MOC_LITERAL(7, 102, 21), // "signalSerRemoveSysMsg"
QT_MOC_LITERAL(8, 124, 22), // "signalSerRegLastSysMsg"
QT_MOC_LITERAL(9, 147, 12), // "data::SysMsg"
QT_MOC_LITERAL(10, 160, 5), // "count"
QT_MOC_LITERAL(11, 166, 21), // "signalSerAddBuddyResp"
QT_MOC_LITERAL(12, 188, 21), // "signalSerAddGroupResp"
QT_MOC_LITERAL(13, 210, 16), // "signalSerSendMsg"
QT_MOC_LITERAL(14, 227, 5), // "int64"
QT_MOC_LITERAL(15, 233, 7), // "msgtime"
QT_MOC_LITERAL(16, 241, 5), // "msgid"
QT_MOC_LITERAL(17, 247, 18), // "signalSerRegSysMsg"
QT_MOC_LITERAL(18, 266, 15), // "onDelBtnClicked"
QT_MOC_LITERAL(19, 282, 5), // "msgId"
QT_MOC_LITERAL(20, 288, 14), // "onAgreeClicked"
QT_MOC_LITERAL(21, 303, 15), // "onIgnoreClicked"
QT_MOC_LITERAL(22, 319, 17), // "onSerGetAllSysMsg"
QT_MOC_LITERAL(23, 337, 18), // "onSerSetSysMsgRead"
QT_MOC_LITERAL(24, 356, 17), // "onSerRemoveSysMsg"
QT_MOC_LITERAL(25, 374, 18), // "onSerRegLastSysMsg"
QT_MOC_LITERAL(26, 393, 17), // "onSerAddBuddyResp"
QT_MOC_LITERAL(27, 411, 17), // "onSerAddGroupResp"
QT_MOC_LITERAL(28, 429, 12), // "onSerSendMsg"
QT_MOC_LITERAL(29, 442, 14) // "onSerRegSysMsg"

    },
    "ui::SystemMsgPage\0signalSerGetAllSysMsg\0"
    "\0err\0std::vector<data::SysMsg>&\0sysMsg\0"
    "signalSerSetSysMsgRead\0signalSerRemoveSysMsg\0"
    "signalSerRegLastSysMsg\0data::SysMsg\0"
    "count\0signalSerAddBuddyResp\0"
    "signalSerAddGroupResp\0signalSerSendMsg\0"
    "int64\0msgtime\0msgid\0signalSerRegSysMsg\0"
    "onDelBtnClicked\0msgId\0onAgreeClicked\0"
    "onIgnoreClicked\0onSerGetAllSysMsg\0"
    "onSerSetSysMsgRead\0onSerRemoveSysMsg\0"
    "onSerRegLastSysMsg\0onSerAddBuddyResp\0"
    "onSerAddGroupResp\0onSerSendMsg\0"
    "onSerRegSysMsg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__SystemMsgPage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      19,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  109,    2, 0x06 /* Public */,
       6,    1,  114,    2, 0x06 /* Public */,
       7,    1,  117,    2, 0x06 /* Public */,
       8,    2,  120,    2, 0x06 /* Public */,
      11,    1,  125,    2, 0x06 /* Public */,
      12,    1,  128,    2, 0x06 /* Public */,
      13,    3,  131,    2, 0x06 /* Public */,
      17,    1,  138,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      18,    1,  141,    2, 0x0a /* Public */,
      20,    1,  144,    2, 0x0a /* Public */,
      21,    1,  147,    2, 0x0a /* Public */,
      22,    2,  150,    2, 0x0a /* Public */,
      23,    1,  155,    2, 0x0a /* Public */,
      24,    1,  158,    2, 0x0a /* Public */,
      25,    2,  161,    2, 0x0a /* Public */,
      26,    1,  166,    2, 0x0a /* Public */,
      27,    1,  169,    2, 0x0a /* Public */,
      28,    3,  172,    2, 0x0a /* Public */,
      29,    1,  179,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 9, QMetaType::Int,    5,   10,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 14, 0x80000000 | 14,    3,   15,   16,
    QMetaType::Void, 0x80000000 | 9,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 14,   19,
    QMetaType::Void, 0x80000000 | 14,   19,
    QMetaType::Void, 0x80000000 | 14,   19,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 9, QMetaType::Int,    5,   10,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 14, 0x80000000 | 14,    3,   15,   16,
    QMetaType::Void, 0x80000000 | 9,    5,

       0        // eod
};

void ui::SystemMsgPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SystemMsgPage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerGetAllSysMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<data::SysMsg>(*)>(_a[2]))); break;
        case 1: _t->signalSerSetSysMsgRead((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->signalSerRemoveSysMsg((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->signalSerRegLastSysMsg((*reinterpret_cast< const data::SysMsg(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->signalSerAddBuddyResp((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->signalSerAddGroupResp((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->signalSerSendMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3]))); break;
        case 7: _t->signalSerRegSysMsg((*reinterpret_cast< const data::SysMsg(*)>(_a[1]))); break;
        case 8: _t->onDelBtnClicked((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 9: _t->onAgreeClicked((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 10: _t->onIgnoreClicked((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 11: _t->onSerGetAllSysMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<data::SysMsg>(*)>(_a[2]))); break;
        case 12: _t->onSerSetSysMsgRead((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 13: _t->onSerRemoveSysMsg((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->onSerRegLastSysMsg((*reinterpret_cast< const data::SysMsg(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 15: _t->onSerAddBuddyResp((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 16: _t->onSerAddGroupResp((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 17: _t->onSerSendMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3]))); break;
        case 18: _t->onSerRegSysMsg((*reinterpret_cast< const data::SysMsg(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SystemMsgPage::*)(int , std::vector<data::SysMsg> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemMsgPage::signalSerGetAllSysMsg)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SystemMsgPage::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemMsgPage::signalSerSetSysMsgRead)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SystemMsgPage::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemMsgPage::signalSerRemoveSysMsg)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SystemMsgPage::*)(const data::SysMsg & , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemMsgPage::signalSerRegLastSysMsg)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (SystemMsgPage::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemMsgPage::signalSerAddBuddyResp)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (SystemMsgPage::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemMsgPage::signalSerAddGroupResp)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (SystemMsgPage::*)(int , int64 , int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemMsgPage::signalSerSendMsg)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (SystemMsgPage::*)(const data::SysMsg & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SystemMsgPage::signalSerRegSysMsg)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::SystemMsgPage::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ui__SystemMsgPage.data,
    qt_meta_data_ui__SystemMsgPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::SystemMsgPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::SystemMsgPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__SystemMsgPage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ui::SystemMsgPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 19)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 19;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 19)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 19;
    }
    return _id;
}

// SIGNAL 0
void ui::SystemMsgPage::signalSerGetAllSysMsg(int _t1, std::vector<data::SysMsg> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::SystemMsgPage::signalSerSetSysMsgRead(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::SystemMsgPage::signalSerRemoveSysMsg(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ui::SystemMsgPage::signalSerRegLastSysMsg(const data::SysMsg & _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ui::SystemMsgPage::signalSerAddBuddyResp(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ui::SystemMsgPage::signalSerAddGroupResp(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ui::SystemMsgPage::signalSerSendMsg(int _t1, int64 _t2, int64 _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ui::SystemMsgPage::signalSerRegSysMsg(const data::SysMsg & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
