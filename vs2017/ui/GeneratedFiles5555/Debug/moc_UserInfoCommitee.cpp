/****************************************************************************
** Meta object code from reading C++ file 'UserInfoCommitee.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../controls/UserInfoCommitee.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UserInfoCommitee.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__UserInfoCommitee_t {
    QByteArrayData data[15];
    char stringdata0[269];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__UserInfoCommitee_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__UserInfoCommitee_t qt_meta_stringdata_ui__UserInfoCommitee = {
    {
QT_MOC_LITERAL(0, 0, 20), // "ui::UserInfoCommitee"
QT_MOC_LITERAL(1, 21, 9), // "startChat"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 27), // "CSharedPtr<data::ChatInfo>&"
QT_MOC_LITERAL(4, 60, 10), // "addContact"
QT_MOC_LITERAL(5, 71, 23), // "data::SearchResultInfo&"
QT_MOC_LITERAL(6, 95, 34), // "signalSerGetBuddyInfoFromNetR..."
QT_MOC_LITERAL(7, 130, 14), // "data::Contact&"
QT_MOC_LITERAL(8, 145, 25), // "signalSerAddContactResult"
QT_MOC_LITERAL(9, 171, 12), // "onAddClicked"
QT_MOC_LITERAL(10, 184, 18), // "onStartChatClicked"
QT_MOC_LITERAL(11, 203, 21), // "onSerAddContactResult"
QT_MOC_LITERAL(12, 225, 4), // "code"
QT_MOC_LITERAL(13, 230, 30), // "onSerGetBuddyInfoFromNetResult"
QT_MOC_LITERAL(14, 261, 7) // "contact"

    },
    "ui::UserInfoCommitee\0startChat\0\0"
    "CSharedPtr<data::ChatInfo>&\0addContact\0"
    "data::SearchResultInfo&\0"
    "signalSerGetBuddyInfoFromNetResult\0"
    "data::Contact&\0signalSerAddContactResult\0"
    "onAddClicked\0onStartChatClicked\0"
    "onSerAddContactResult\0code\0"
    "onSerGetBuddyInfoFromNetResult\0contact"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__UserInfoCommitee[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,
       6,    2,   60,    2, 0x06 /* Public */,
       8,    1,   65,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   68,    2, 0x0a /* Public */,
      10,    0,   69,    2, 0x0a /* Public */,
      11,    1,   70,    2, 0x0a /* Public */,
      13,    2,   73,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, 0x80000000 | 5,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,   12,   14,

       0        // eod
};

void ui::UserInfoCommitee::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UserInfoCommitee *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startChat((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        case 1: _t->addContact((*reinterpret_cast< data::SearchResultInfo(*)>(_a[1]))); break;
        case 2: _t->signalSerGetBuddyInfoFromNetResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::Contact(*)>(_a[2]))); break;
        case 3: _t->signalSerAddContactResult((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->onAddClicked(); break;
        case 5: _t->onStartChatClicked(); break;
        case 6: _t->onSerAddContactResult((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->onSerGetBuddyInfoFromNetResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::Contact(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (UserInfoCommitee::*)(CSharedPtr<data::ChatInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UserInfoCommitee::startChat)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (UserInfoCommitee::*)(data::SearchResultInfo & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UserInfoCommitee::addContact)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (UserInfoCommitee::*)(int , data::Contact & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UserInfoCommitee::signalSerGetBuddyInfoFromNetResult)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (UserInfoCommitee::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UserInfoCommitee::signalSerAddContactResult)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::UserInfoCommitee::staticMetaObject = { {
    QMetaObject::SuperData::link<TWidget::staticMetaObject>(),
    qt_meta_stringdata_ui__UserInfoCommitee.data,
    qt_meta_data_ui__UserInfoCommitee,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::UserInfoCommitee::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::UserInfoCommitee::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__UserInfoCommitee.stringdata0))
        return static_cast<void*>(this);
    return TWidget::qt_metacast(_clname);
}

int ui::UserInfoCommitee::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ui::UserInfoCommitee::startChat(CSharedPtr<data::ChatInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::UserInfoCommitee::addContact(data::SearchResultInfo & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::UserInfoCommitee::signalSerGetBuddyInfoFromNetResult(int _t1, data::Contact & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ui::UserInfoCommitee::signalSerAddContactResult(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
