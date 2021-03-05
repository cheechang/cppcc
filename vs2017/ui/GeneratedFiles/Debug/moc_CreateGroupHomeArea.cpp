/****************************************************************************
** Meta object code from reading C++ file 'CreateGroupHomeArea.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/contact/createGroup/CreateGroupHomeArea.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CreateGroupHomeArea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__CreateGroupHomeArea_t {
    QByteArrayData data[22];
    char stringdata0[318];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__CreateGroupHomeArea_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__CreateGroupHomeArea_t qt_meta_stringdata_ui__CreateGroupHomeArea = {
    {
QT_MOC_LITERAL(0, 0, 23), // "ui::CreateGroupHomeArea"
QT_MOC_LITERAL(1, 24, 15), // "addGroupClicked"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 17), // "QMap<int64,int64>"
QT_MOC_LITERAL(4, 59, 20), // "signalSerCreateGroup"
QT_MOC_LITERAL(5, 80, 5), // "int64"
QT_MOC_LITERAL(6, 86, 21), // "signalSerInviteMember"
QT_MOC_LITERAL(7, 108, 9), // "startChat"
QT_MOC_LITERAL(8, 118, 27), // "CSharedPtr<data::ChatInfo>&"
QT_MOC_LITERAL(9, 146, 4), // "chat"
QT_MOC_LITERAL(10, 151, 8), // "closeWin"
QT_MOC_LITERAL(11, 160, 17), // "signalSerGroupSet"
QT_MOC_LITERAL(12, 178, 4), // "code"
QT_MOC_LITERAL(13, 183, 14), // "onLevelChanged"
QT_MOC_LITERAL(14, 198, 5), // "index"
QT_MOC_LITERAL(15, 204, 16), // "onBtnCreateGroup"
QT_MOC_LITERAL(16, 221, 21), // "onBtnAddFriendClicked"
QT_MOC_LITERAL(17, 243, 16), // "onSerCreateGroup"
QT_MOC_LITERAL(18, 260, 7), // "groupId"
QT_MOC_LITERAL(19, 268, 17), // "onSerInviteMember"
QT_MOC_LITERAL(20, 286, 13), // "onSerGroupSet"
QT_MOC_LITERAL(21, 300, 17) // "onAddGroupClicked"

    },
    "ui::CreateGroupHomeArea\0addGroupClicked\0"
    "\0QMap<int64,int64>\0signalSerCreateGroup\0"
    "int64\0signalSerInviteMember\0startChat\0"
    "CSharedPtr<data::ChatInfo>&\0chat\0"
    "closeWin\0signalSerGroupSet\0code\0"
    "onLevelChanged\0index\0onBtnCreateGroup\0"
    "onBtnAddFriendClicked\0onSerCreateGroup\0"
    "groupId\0onSerInviteMember\0onSerGroupSet\0"
    "onAddGroupClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__CreateGroupHomeArea[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       4,    2,   82,    2, 0x06 /* Public */,
       6,    1,   87,    2, 0x06 /* Public */,
       7,    1,   90,    2, 0x06 /* Public */,
      10,    0,   93,    2, 0x06 /* Public */,
      11,    1,   94,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    1,   97,    2, 0x09 /* Protected */,
      15,    0,  100,    2, 0x09 /* Protected */,
      16,    0,  101,    2, 0x09 /* Protected */,
      17,    2,  102,    2, 0x09 /* Protected */,
      19,    1,  107,    2, 0x09 /* Protected */,
      20,    1,  110,    2, 0x09 /* Protected */,
      21,    0,  113,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 5,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 5,   12,   18,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,

       0        // eod
};

void ui::CreateGroupHomeArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CreateGroupHomeArea *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->addGroupClicked((*reinterpret_cast< QMap<int64,int64>(*)>(_a[1]))); break;
        case 1: _t->signalSerCreateGroup((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2]))); break;
        case 2: _t->signalSerInviteMember((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->startChat((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        case 4: _t->closeWin(); break;
        case 5: _t->signalSerGroupSet((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->onLevelChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->onBtnCreateGroup(); break;
        case 8: _t->onBtnAddFriendClicked(); break;
        case 9: _t->onSerCreateGroup((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2]))); break;
        case 10: _t->onSerInviteMember((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->onSerGroupSet((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->onAddGroupClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CreateGroupHomeArea::*)(QMap<int64,int64> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CreateGroupHomeArea::addGroupClicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CreateGroupHomeArea::*)(int , int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CreateGroupHomeArea::signalSerCreateGroup)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CreateGroupHomeArea::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CreateGroupHomeArea::signalSerInviteMember)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CreateGroupHomeArea::*)(CSharedPtr<data::ChatInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CreateGroupHomeArea::startChat)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (CreateGroupHomeArea::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CreateGroupHomeArea::closeWin)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (CreateGroupHomeArea::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CreateGroupHomeArea::signalSerGroupSet)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::CreateGroupHomeArea::staticMetaObject = { {
    &TWidget::staticMetaObject,
    qt_meta_stringdata_ui__CreateGroupHomeArea.data,
    qt_meta_data_ui__CreateGroupHomeArea,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::CreateGroupHomeArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::CreateGroupHomeArea::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__CreateGroupHomeArea.stringdata0))
        return static_cast<void*>(this);
    return TWidget::qt_metacast(_clname);
}

int ui::CreateGroupHomeArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}

// SIGNAL 0
void ui::CreateGroupHomeArea::addGroupClicked(QMap<int64,int64> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::CreateGroupHomeArea::signalSerCreateGroup(int _t1, int64 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::CreateGroupHomeArea::signalSerInviteMember(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ui::CreateGroupHomeArea::startChat(CSharedPtr<data::ChatInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ui::CreateGroupHomeArea::closeWin()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void ui::CreateGroupHomeArea::signalSerGroupSet(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
