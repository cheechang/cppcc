/****************************************************************************
** Meta object code from reading C++ file 'GroupNotice.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/contact/group/GroupNotice.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GroupNotice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__GroupNotice_t {
    QByteArrayData data[17];
    char stringdata0[278];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__GroupNotice_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__GroupNotice_t qt_meta_stringdata_ui__GroupNotice = {
    {
QT_MOC_LITERAL(0, 0, 15), // "ui::GroupNotice"
QT_MOC_LITERAL(1, 16, 9), // "startChat"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 27), // "CSharedPtr<data::ChatInfo>&"
QT_MOC_LITERAL(4, 55, 21), // "signalSerGetGroupInfo"
QT_MOC_LITERAL(5, 77, 24), // "CSharedPtr<data::Group>&"
QT_MOC_LITERAL(6, 102, 25), // "signalSerNoticePushResult"
QT_MOC_LITERAL(7, 128, 20), // "signalSerGetGroupMem"
QT_MOC_LITERAL(8, 149, 4), // "code"
QT_MOC_LITERAL(9, 154, 13), // "data::Member&"
QT_MOC_LITERAL(10, 168, 3), // "mem"
QT_MOC_LITERAL(11, 172, 14), // "onMaxChatCheck"
QT_MOC_LITERAL(12, 187, 15), // "onSerPushNotice"
QT_MOC_LITERAL(13, 203, 20), // "onSerCancelNoticeBtn"
QT_MOC_LITERAL(14, 224, 14), // "onSerNoticeBtn"
QT_MOC_LITERAL(15, 239, 21), // "onSerNoticePushResult"
QT_MOC_LITERAL(16, 261, 16) // "onSerGetGroupMem"

    },
    "ui::GroupNotice\0startChat\0\0"
    "CSharedPtr<data::ChatInfo>&\0"
    "signalSerGetGroupInfo\0CSharedPtr<data::Group>&\0"
    "signalSerNoticePushResult\0"
    "signalSerGetGroupMem\0code\0data::Member&\0"
    "mem\0onMaxChatCheck\0onSerPushNotice\0"
    "onSerCancelNoticeBtn\0onSerNoticeBtn\0"
    "onSerNoticePushResult\0onSerGetGroupMem"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__GroupNotice[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    2,   67,    2, 0x06 /* Public */,
       6,    1,   72,    2, 0x06 /* Public */,
       7,    2,   75,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   80,    2, 0x0a /* Public */,
      12,    0,   81,    2, 0x0a /* Public */,
      13,    0,   82,    2, 0x0a /* Public */,
      14,    0,   83,    2, 0x0a /* Public */,
      15,    1,   84,    2, 0x0a /* Public */,
      16,    2,   87,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 5,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 9,    8,   10,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 9,    8,   10,

       0        // eod
};

void ui::GroupNotice::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GroupNotice *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startChat((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        case 1: _t->signalSerGetGroupInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< CSharedPtr<data::Group>(*)>(_a[2]))); break;
        case 2: _t->signalSerNoticePushResult((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->signalSerGetGroupMem((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::Member(*)>(_a[2]))); break;
        case 4: _t->onMaxChatCheck(); break;
        case 5: _t->onSerPushNotice(); break;
        case 6: _t->onSerCancelNoticeBtn(); break;
        case 7: _t->onSerNoticeBtn(); break;
        case 8: _t->onSerNoticePushResult((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->onSerGetGroupMem((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::Member(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GroupNotice::*)(CSharedPtr<data::ChatInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupNotice::startChat)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GroupNotice::*)(int , CSharedPtr<data::Group> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupNotice::signalSerGetGroupInfo)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GroupNotice::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupNotice::signalSerNoticePushResult)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GroupNotice::*)(int , data::Member & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupNotice::signalSerGetGroupMem)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::GroupNotice::staticMetaObject = { {
    &TWidget::staticMetaObject,
    qt_meta_stringdata_ui__GroupNotice.data,
    qt_meta_data_ui__GroupNotice,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::GroupNotice::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::GroupNotice::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__GroupNotice.stringdata0))
        return static_cast<void*>(this);
    return TWidget::qt_metacast(_clname);
}

int ui::GroupNotice::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void ui::GroupNotice::startChat(CSharedPtr<data::ChatInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::GroupNotice::signalSerGetGroupInfo(int _t1, CSharedPtr<data::Group> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::GroupNotice::signalSerNoticePushResult(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ui::GroupNotice::signalSerGetGroupMem(int _t1, data::Member & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
