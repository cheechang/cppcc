/****************************************************************************
** Meta object code from reading C++ file 'GroupFileListItem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../mainwindow/contact/group/GroupFileListItem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GroupFileListItem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__GroupFileListItem_t {
    QByteArrayData data[17];
    char stringdata0[223];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__GroupFileListItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__GroupFileListItem_t qt_meta_stringdata_ui__GroupFileListItem = {
    {
QT_MOC_LITERAL(0, 0, 21), // "ui::GroupFileListItem"
QT_MOC_LITERAL(1, 22, 18), // "showGroupInforPage"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 5), // "int64"
QT_MOC_LITERAL(4, 48, 7), // "groupId"
QT_MOC_LITERAL(5, 56, 21), // "signalSerDownLoadFile"
QT_MOC_LITERAL(6, 78, 11), // "std::string"
QT_MOC_LITERAL(7, 90, 19), // "signalSerProgressCb"
QT_MOC_LITERAL(8, 110, 12), // "downloadFile"
QT_MOC_LITERAL(9, 123, 11), // "openFileDir"
QT_MOC_LITERAL(10, 135, 17), // "onSerDownLoadFile"
QT_MOC_LITERAL(11, 153, 3), // "err"
QT_MOC_LITERAL(12, 157, 8), // "filepath"
QT_MOC_LITERAL(13, 166, 8), // "targetId"
QT_MOC_LITERAL(14, 175, 15), // "onSerProgressCb"
QT_MOC_LITERAL(15, 191, 19), // "onSerFileUpProGress"
QT_MOC_LITERAL(16, 211, 11) // "onSerSetTip"

    },
    "ui::GroupFileListItem\0showGroupInforPage\0"
    "\0int64\0groupId\0signalSerDownLoadFile\0"
    "std::string\0signalSerProgressCb\0"
    "downloadFile\0openFileDir\0onSerDownLoadFile\0"
    "err\0filepath\0targetId\0onSerProgressCb\0"
    "onSerFileUpProGress\0onSerSetTip"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__GroupFileListItem[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       5,    3,   62,    2, 0x06 /* Public */,
       7,    4,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   78,    2, 0x0a /* Public */,
       9,    0,   79,    2, 0x0a /* Public */,
      10,    3,   80,    2, 0x0a /* Public */,
      14,    4,   87,    2, 0x0a /* Public */,
      15,    1,   96,    2, 0x0a /* Public */,
      16,    0,   99,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 6, 0x80000000 | 3,    2,    2,    2,
    QMetaType::Void, QMetaType::LongLong, QMetaType::Int, QMetaType::Int, 0x80000000 | 6,    2,    2,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 6, 0x80000000 | 3,   11,   12,   13,
    QMetaType::Void, QMetaType::LongLong, QMetaType::Int, QMetaType::Int, 0x80000000 | 6,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

       0        // eod
};

void ui::GroupFileListItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GroupFileListItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->showGroupInforPage((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 1: _t->signalSerDownLoadFile((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3]))); break;
        case 2: _t->signalSerProgressCb((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3])),(*reinterpret_cast< const std::string(*)>(_a[4]))); break;
        case 3: _t->downloadFile(); break;
        case 4: _t->openFileDir(); break;
        case 5: _t->onSerDownLoadFile((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3]))); break;
        case 6: _t->onSerProgressCb((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3])),(*reinterpret_cast< const std::string(*)>(_a[4]))); break;
        case 7: _t->onSerFileUpProGress((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 8: _t->onSerSetTip(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GroupFileListItem::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupFileListItem::showGroupInforPage)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GroupFileListItem::*)(int , const std::string & , int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupFileListItem::signalSerDownLoadFile)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GroupFileListItem::*)(qint64 , qint32 , qint32 , const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupFileListItem::signalSerProgressCb)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::GroupFileListItem::staticMetaObject = { {
    QMetaObject::SuperData::link<TWidget::staticMetaObject>(),
    qt_meta_stringdata_ui__GroupFileListItem.data,
    qt_meta_data_ui__GroupFileListItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::GroupFileListItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::GroupFileListItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__GroupFileListItem.stringdata0))
        return static_cast<void*>(this);
    return TWidget::qt_metacast(_clname);
}

int ui::GroupFileListItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void ui::GroupFileListItem::showGroupInforPage(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::GroupFileListItem::signalSerDownLoadFile(int _t1, const std::string & _t2, int64 _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::GroupFileListItem::signalSerProgressCb(qint64 _t1, qint32 _t2, qint32 _t3, const std::string & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
