/****************************************************************************
** Meta object code from reading C++ file 'GroupInforWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/contact/group/GroupInforWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GroupInforWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__GroupInforWidget_t {
    QByteArrayData data[23];
    char stringdata0[319];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__GroupInforWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__GroupInforWidget_t qt_meta_stringdata_ui__GroupInforWidget = {
    {
QT_MOC_LITERAL(0, 0, 20), // "ui::GroupInforWidget"
QT_MOC_LITERAL(1, 21, 9), // "startChat"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 27), // "CSharedPtr<data::ChatInfo>&"
QT_MOC_LITERAL(4, 60, 4), // "chat"
QT_MOC_LITERAL(5, 65, 18), // "signalSerDelUiFile"
QT_MOC_LITERAL(6, 84, 5), // "int64"
QT_MOC_LITERAL(7, 90, 20), // "signalSerUpgroupInfo"
QT_MOC_LITERAL(8, 111, 18), // "signalSerUpSuccess"
QT_MOC_LITERAL(9, 130, 19), // "signalSerGetMemInfo"
QT_MOC_LITERAL(10, 150, 13), // "data::Member&"
QT_MOC_LITERAL(11, 164, 11), // "onStartChat"
QT_MOC_LITERAL(12, 176, 13), // "onEditProfile"
QT_MOC_LITERAL(13, 190, 14), // "onSerDelUiFile"
QT_MOC_LITERAL(14, 205, 15), // "onSerModifyHead"
QT_MOC_LITERAL(15, 221, 15), // "onGroupHeadSucc"
QT_MOC_LITERAL(16, 237, 12), // "std::string&"
QT_MOC_LITERAL(17, 250, 7), // "headUrl"
QT_MOC_LITERAL(18, 258, 16), // "onSerUpgroupInfo"
QT_MOC_LITERAL(19, 275, 4), // "code"
QT_MOC_LITERAL(20, 280, 14), // "onUserHeadSucc"
QT_MOC_LITERAL(21, 295, 7), // "headImg"
QT_MOC_LITERAL(22, 303, 15) // "onSerGetMemInfo"

    },
    "ui::GroupInforWidget\0startChat\0\0"
    "CSharedPtr<data::ChatInfo>&\0chat\0"
    "signalSerDelUiFile\0int64\0signalSerUpgroupInfo\0"
    "signalSerUpSuccess\0signalSerGetMemInfo\0"
    "data::Member&\0onStartChat\0onEditProfile\0"
    "onSerDelUiFile\0onSerModifyHead\0"
    "onGroupHeadSucc\0std::string&\0headUrl\0"
    "onSerUpgroupInfo\0code\0onUserHeadSucc\0"
    "headImg\0onSerGetMemInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__GroupInforWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x06 /* Public */,
       5,    2,   82,    2, 0x06 /* Public */,
       7,    1,   87,    2, 0x06 /* Public */,
       8,    1,   90,    2, 0x06 /* Public */,
       9,    2,   93,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   98,    2, 0x09 /* Protected */,
      12,    0,   99,    2, 0x09 /* Protected */,
      13,    1,  100,    2, 0x09 /* Protected */,
      14,    0,  103,    2, 0x09 /* Protected */,
      15,    1,  104,    2, 0x09 /* Protected */,
      18,    1,  107,    2, 0x09 /* Protected */,
      20,    1,  110,    2, 0x09 /* Protected */,
      22,    2,  113,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 6,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    2,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, QMetaType::Int,   19,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 10,    2,    2,

       0        // eod
};

void ui::GroupInforWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GroupInforWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startChat((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        case 1: _t->signalSerDelUiFile((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2]))); break;
        case 2: _t->signalSerUpgroupInfo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->signalSerUpSuccess((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->signalSerGetMemInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::Member(*)>(_a[2]))); break;
        case 5: _t->onStartChat(); break;
        case 6: _t->onEditProfile(); break;
        case 7: _t->onSerDelUiFile((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 8: _t->onSerModifyHead(); break;
        case 9: _t->onGroupHeadSucc((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 10: _t->onSerUpgroupInfo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->onUserHeadSucc((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 12: _t->onSerGetMemInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::Member(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GroupInforWidget::*)(CSharedPtr<data::ChatInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupInforWidget::startChat)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GroupInforWidget::*)(int64 , int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupInforWidget::signalSerDelUiFile)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GroupInforWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupInforWidget::signalSerUpgroupInfo)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GroupInforWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupInforWidget::signalSerUpSuccess)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GroupInforWidget::*)(int , data::Member & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupInforWidget::signalSerGetMemInfo)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::GroupInforWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ui__GroupInforWidget.data,
    qt_meta_data_ui__GroupInforWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::GroupInforWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::GroupInforWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__GroupInforWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ui::GroupInforWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void ui::GroupInforWidget::startChat(CSharedPtr<data::ChatInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::GroupInforWidget::signalSerDelUiFile(int64 _t1, int64 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::GroupInforWidget::signalSerUpgroupInfo(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ui::GroupInforWidget::signalSerUpSuccess(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ui::GroupInforWidget::signalSerGetMemInfo(int _t1, data::Member & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
