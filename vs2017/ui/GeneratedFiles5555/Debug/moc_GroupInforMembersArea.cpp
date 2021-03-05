/****************************************************************************
** Meta object code from reading C++ file 'GroupInforMembersArea.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../mainwindow/contact/group/GroupInforMembersArea.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GroupInforMembersArea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__GroupInforMembersArea_t {
    QByteArrayData data[48];
    char stringdata0[798];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__GroupInforMembersArea_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__GroupInforMembersArea_t qt_meta_stringdata_ui__GroupInforMembersArea = {
    {
QT_MOC_LITERAL(0, 0, 25), // "ui::GroupInforMembersArea"
QT_MOC_LITERAL(1, 26, 9), // "startChat"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 27), // "CSharedPtr<data::ChatInfo>&"
QT_MOC_LITERAL(4, 65, 11), // "itemClicked"
QT_MOC_LITERAL(5, 77, 22), // "signalSerGetMemberList"
QT_MOC_LITERAL(6, 100, 39), // "std::vector<CSharedPtr<data::..."
QT_MOC_LITERAL(7, 140, 17), // "signalSerCallBack"
QT_MOC_LITERAL(8, 158, 24), // "signalSerGrpMemRefreshCb"
QT_MOC_LITERAL(9, 183, 5), // "int64"
QT_MOC_LITERAL(10, 189, 21), // "signalSerRemoveMember"
QT_MOC_LITERAL(11, 211, 23), // "signalSerSetAdminResult"
QT_MOC_LITERAL(12, 235, 24), // "signalSerSetRemarkResult"
QT_MOC_LITERAL(13, 260, 28), // "signalSerTransferGroupResult"
QT_MOC_LITERAL(14, 289, 28), // "signalSerGrpMemInfoRefreshCb"
QT_MOC_LITERAL(15, 318, 12), // "data::Member"
QT_MOC_LITERAL(16, 331, 20), // "signalSerGetUserInfo"
QT_MOC_LITERAL(17, 352, 15), // "data::UserData&"
QT_MOC_LITERAL(18, 368, 2), // "id"
QT_MOC_LITERAL(19, 371, 4), // "name"
QT_MOC_LITERAL(20, 376, 6), // "avatar"
QT_MOC_LITERAL(21, 383, 16), // "onSerGetUserInfo"
QT_MOC_LITERAL(22, 400, 24), // "onSerGrpMemInfoRefreshCb"
QT_MOC_LITERAL(23, 425, 7), // "groupId"
QT_MOC_LITERAL(24, 433, 10), // "memberInfo"
QT_MOC_LITERAL(25, 444, 18), // "onSerGetMemberList"
QT_MOC_LITERAL(26, 463, 4), // "code"
QT_MOC_LITERAL(27, 468, 4), // "mems"
QT_MOC_LITERAL(28, 473, 13), // "onItemClicked"
QT_MOC_LITERAL(29, 487, 19), // "onItemDoubleClicked"
QT_MOC_LITERAL(30, 507, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(31, 524, 4), // "item"
QT_MOC_LITERAL(32, 529, 13), // "onInviteGroup"
QT_MOC_LITERAL(33, 543, 17), // "onMenuItemClicked"
QT_MOC_LITERAL(34, 561, 22), // "onMenuItemAdminClicked"
QT_MOC_LITERAL(35, 584, 23), // "onMenuItemRemarkClicked"
QT_MOC_LITERAL(36, 608, 25), // "onMenuItemTransferClicked"
QT_MOC_LITERAL(37, 634, 10), // "onGroupSet"
QT_MOC_LITERAL(38, 645, 4), // "int8"
QT_MOC_LITERAL(39, 650, 11), // "verify_type"
QT_MOC_LITERAL(40, 662, 8), // "is_allow"
QT_MOC_LITERAL(41, 671, 20), // "onSerGrpMemRefreshCb"
QT_MOC_LITERAL(42, 692, 4), // "type"
QT_MOC_LITERAL(43, 697, 17), // "onSerRemoveMember"
QT_MOC_LITERAL(44, 715, 19), // "onSerSetAdminResult"
QT_MOC_LITERAL(45, 735, 20), // "onSerSetRemarkResult"
QT_MOC_LITERAL(46, 756, 24), // "onSerTransferGroupResult"
QT_MOC_LITERAL(47, 781, 16) // "onLazyLoadMember"

    },
    "ui::GroupInforMembersArea\0startChat\0"
    "\0CSharedPtr<data::ChatInfo>&\0itemClicked\0"
    "signalSerGetMemberList\0"
    "std::vector<CSharedPtr<data::Member> >&\0"
    "signalSerCallBack\0signalSerGrpMemRefreshCb\0"
    "int64\0signalSerRemoveMember\0"
    "signalSerSetAdminResult\0"
    "signalSerSetRemarkResult\0"
    "signalSerTransferGroupResult\0"
    "signalSerGrpMemInfoRefreshCb\0data::Member\0"
    "signalSerGetUserInfo\0data::UserData&\0"
    "id\0name\0avatar\0onSerGetUserInfo\0"
    "onSerGrpMemInfoRefreshCb\0groupId\0"
    "memberInfo\0onSerGetMemberList\0code\0"
    "mems\0onItemClicked\0onItemDoubleClicked\0"
    "QListWidgetItem*\0item\0onInviteGroup\0"
    "onMenuItemClicked\0onMenuItemAdminClicked\0"
    "onMenuItemRemarkClicked\0"
    "onMenuItemTransferClicked\0onGroupSet\0"
    "int8\0verify_type\0is_allow\0"
    "onSerGrpMemRefreshCb\0type\0onSerRemoveMember\0"
    "onSerSetAdminResult\0onSerSetRemarkResult\0"
    "onSerTransferGroupResult\0onLazyLoadMember"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__GroupInforMembersArea[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      28,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  154,    2, 0x06 /* Public */,
       4,    1,  157,    2, 0x06 /* Public */,
       5,    2,  160,    2, 0x06 /* Public */,
       7,    1,  165,    2, 0x06 /* Public */,
       8,    3,  168,    2, 0x06 /* Public */,
      10,    1,  175,    2, 0x06 /* Public */,
      11,    1,  178,    2, 0x06 /* Public */,
      12,    1,  181,    2, 0x06 /* Public */,
      13,    1,  184,    2, 0x06 /* Public */,
      14,    2,  187,    2, 0x06 /* Public */,
      16,    5,  192,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      21,    5,  203,    2, 0x0a /* Public */,
      22,    2,  214,    2, 0x0a /* Public */,
      25,    2,  219,    2, 0x0a /* Public */,
      28,    0,  224,    2, 0x0a /* Public */,
      29,    1,  225,    2, 0x0a /* Public */,
      32,    0,  228,    2, 0x0a /* Public */,
      33,    0,  229,    2, 0x0a /* Public */,
      34,    0,  230,    2, 0x0a /* Public */,
      35,    0,  231,    2, 0x0a /* Public */,
      36,    0,  232,    2, 0x0a /* Public */,
      37,    3,  233,    2, 0x0a /* Public */,
      41,    3,  240,    2, 0x0a /* Public */,
      43,    1,  247,    2, 0x0a /* Public */,
      44,    1,  250,    2, 0x0a /* Public */,
      45,    1,  253,    2, 0x0a /* Public */,
      46,    1,  256,    2, 0x0a /* Public */,
      47,    0,  259,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 6,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 9, 0x80000000 | 6,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 15,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 17, 0x80000000 | 9, QMetaType::QString, QMetaType::QString,    2,    2,   18,   19,   20,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 17, 0x80000000 | 9, QMetaType::QString, QMetaType::QString,    2,    2,   18,   19,   20,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 15,   23,   24,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 6,   26,   27,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 30,   31,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 38, 0x80000000 | 38,   26,   39,   40,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 9, 0x80000000 | 6,   42,   23,   27,
    QMetaType::Void, 0x80000000 | 9,   26,
    QMetaType::Void, QMetaType::Int,   26,
    QMetaType::Void, QMetaType::Int,   26,
    QMetaType::Void, QMetaType::Int,   26,
    QMetaType::Void,

       0        // eod
};

void ui::GroupInforMembersArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GroupInforMembersArea *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startChat((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        case 1: _t->itemClicked((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 2: _t->signalSerGetMemberList((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<CSharedPtr<data::Member> >(*)>(_a[2]))); break;
        case 3: _t->signalSerCallBack((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->signalSerGrpMemRefreshCb((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2])),(*reinterpret_cast< std::vector<CSharedPtr<data::Member> >(*)>(_a[3]))); break;
        case 5: _t->signalSerRemoveMember((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 6: _t->signalSerSetAdminResult((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->signalSerSetRemarkResult((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->signalSerTransferGroupResult((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->signalSerGrpMemInfoRefreshCb((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< const data::Member(*)>(_a[2]))); break;
        case 10: _t->signalSerGetUserInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::UserData(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 11: _t->onSerGetUserInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::UserData(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 12: _t->onSerGrpMemInfoRefreshCb((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< const data::Member(*)>(_a[2]))); break;
        case 13: _t->onSerGetMemberList((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<CSharedPtr<data::Member> >(*)>(_a[2]))); break;
        case 14: _t->onItemClicked(); break;
        case 15: _t->onItemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 16: _t->onInviteGroup(); break;
        case 17: _t->onMenuItemClicked(); break;
        case 18: _t->onMenuItemAdminClicked(); break;
        case 19: _t->onMenuItemRemarkClicked(); break;
        case 20: _t->onMenuItemTransferClicked(); break;
        case 21: _t->onGroupSet((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int8(*)>(_a[2])),(*reinterpret_cast< int8(*)>(_a[3]))); break;
        case 22: _t->onSerGrpMemRefreshCb((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2])),(*reinterpret_cast< std::vector<CSharedPtr<data::Member> >(*)>(_a[3]))); break;
        case 23: _t->onSerRemoveMember((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 24: _t->onSerSetAdminResult((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 25: _t->onSerSetRemarkResult((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 26: _t->onSerTransferGroupResult((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: _t->onLazyLoadMember(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GroupInforMembersArea::*)(CSharedPtr<data::ChatInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupInforMembersArea::startChat)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GroupInforMembersArea::*)(QPoint );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupInforMembersArea::itemClicked)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GroupInforMembersArea::*)(int , std::vector<CSharedPtr<data::Member> > & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupInforMembersArea::signalSerGetMemberList)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GroupInforMembersArea::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupInforMembersArea::signalSerCallBack)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GroupInforMembersArea::*)(int , int64 , std::vector<CSharedPtr<data::Member> > & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupInforMembersArea::signalSerGrpMemRefreshCb)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (GroupInforMembersArea::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupInforMembersArea::signalSerRemoveMember)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (GroupInforMembersArea::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupInforMembersArea::signalSerSetAdminResult)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (GroupInforMembersArea::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupInforMembersArea::signalSerSetRemarkResult)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (GroupInforMembersArea::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupInforMembersArea::signalSerTransferGroupResult)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (GroupInforMembersArea::*)(int64 , const data::Member & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupInforMembersArea::signalSerGrpMemInfoRefreshCb)) {
                *result = 9;
                return;
            }
        }
        {
            using _t = void (GroupInforMembersArea::*)(int , data::UserData & , int64 , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupInforMembersArea::signalSerGetUserInfo)) {
                *result = 10;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::GroupInforMembersArea::staticMetaObject = { {
    QMetaObject::SuperData::link<TWidget::staticMetaObject>(),
    qt_meta_stringdata_ui__GroupInforMembersArea.data,
    qt_meta_data_ui__GroupInforMembersArea,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::GroupInforMembersArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::GroupInforMembersArea::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__GroupInforMembersArea.stringdata0))
        return static_cast<void*>(this);
    return TWidget::qt_metacast(_clname);
}

int ui::GroupInforMembersArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 28)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 28;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 28)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 28;
    }
    return _id;
}

// SIGNAL 0
void ui::GroupInforMembersArea::startChat(CSharedPtr<data::ChatInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::GroupInforMembersArea::itemClicked(QPoint _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::GroupInforMembersArea::signalSerGetMemberList(int _t1, std::vector<CSharedPtr<data::Member> > & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ui::GroupInforMembersArea::signalSerCallBack(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ui::GroupInforMembersArea::signalSerGrpMemRefreshCb(int _t1, int64 _t2, std::vector<CSharedPtr<data::Member> > & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ui::GroupInforMembersArea::signalSerRemoveMember(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ui::GroupInforMembersArea::signalSerSetAdminResult(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ui::GroupInforMembersArea::signalSerSetRemarkResult(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ui::GroupInforMembersArea::signalSerTransferGroupResult(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void ui::GroupInforMembersArea::signalSerGrpMemInfoRefreshCb(int64 _t1, const data::Member & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void ui::GroupInforMembersArea::signalSerGetUserInfo(int _t1, data::UserData & _t2, int64 _t3, QString _t4, QString _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
