/****************************************************************************
** Meta object code from reading C++ file 'filemessagewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../mainwindow/chat/bubble/filemessagewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'filemessagewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FileMessageItem_t {
    QByteArrayData data[16];
    char stringdata0[199];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FileMessageItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FileMessageItem_t qt_meta_stringdata_FileMessageItem = {
    {
QT_MOC_LITERAL(0, 0, 15), // "FileMessageItem"
QT_MOC_LITERAL(1, 16, 19), // "signalSerProgressCb"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 11), // "std::string"
QT_MOC_LITERAL(4, 49, 21), // "signalSerDownLoadFile"
QT_MOC_LITERAL(5, 71, 5), // "int64"
QT_MOC_LITERAL(6, 77, 20), // "signalDownfileFinish"
QT_MOC_LITERAL(7, 98, 8), // "openFile"
QT_MOC_LITERAL(8, 107, 11), // "openFileDir"
QT_MOC_LITERAL(9, 119, 12), // "downloadFile"
QT_MOC_LITERAL(10, 132, 10), // "saveAsFile"
QT_MOC_LITERAL(11, 143, 15), // "onSerProgressCb"
QT_MOC_LITERAL(12, 159, 17), // "onSerDownLoadFile"
QT_MOC_LITERAL(13, 177, 3), // "err"
QT_MOC_LITERAL(14, 181, 8), // "filepath"
QT_MOC_LITERAL(15, 190, 8) // "targetId"

    },
    "FileMessageItem\0signalSerProgressCb\0"
    "\0std::string\0signalSerDownLoadFile\0"
    "int64\0signalDownfileFinish\0openFile\0"
    "openFileDir\0downloadFile\0saveAsFile\0"
    "onSerProgressCb\0onSerDownLoadFile\0err\0"
    "filepath\0targetId"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FileMessageItem[] = {

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
       1,    4,   59,    2, 0x06 /* Public */,
       4,    3,   68,    2, 0x06 /* Public */,
       6,    0,   75,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   76,    2, 0x08 /* Private */,
       8,    0,   77,    2, 0x08 /* Private */,
       9,    0,   78,    2, 0x08 /* Private */,
      10,    0,   79,    2, 0x08 /* Private */,
      11,    4,   80,    2, 0x08 /* Private */,
      12,    3,   89,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::LongLong, QMetaType::Int, QMetaType::Int, 0x80000000 | 3,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3, 0x80000000 | 5,    2,    2,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::LongLong, QMetaType::Int, QMetaType::Int, 0x80000000 | 3,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3, 0x80000000 | 5,   13,   14,   15,

       0        // eod
};

void FileMessageItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FileMessageItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerProgressCb((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3])),(*reinterpret_cast< const std::string(*)>(_a[4]))); break;
        case 1: _t->signalSerDownLoadFile((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3]))); break;
        case 2: _t->signalDownfileFinish(); break;
        case 3: _t->openFile(); break;
        case 4: _t->openFileDir(); break;
        case 5: _t->downloadFile(); break;
        case 6: _t->saveAsFile(); break;
        case 7: _t->onSerProgressCb((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< qint32(*)>(_a[3])),(*reinterpret_cast< const std::string(*)>(_a[4]))); break;
        case 8: _t->onSerDownLoadFile((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FileMessageItem::*)(qint64 , qint32 , qint32 , const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileMessageItem::signalSerProgressCb)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (FileMessageItem::*)(int , const std::string & , int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileMessageItem::signalSerDownLoadFile)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (FileMessageItem::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileMessageItem::signalDownfileFinish)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FileMessageItem::staticMetaObject = { {
    QMetaObject::SuperData::link<ui::TWidget::staticMetaObject>(),
    qt_meta_stringdata_FileMessageItem.data,
    qt_meta_data_FileMessageItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FileMessageItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FileMessageItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FileMessageItem.stringdata0))
        return static_cast<void*>(this);
    return ui::TWidget::qt_metacast(_clname);
}

int FileMessageItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ui::TWidget::qt_metacall(_c, _id, _a);
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
void FileMessageItem::signalSerProgressCb(qint64 _t1, qint32 _t2, qint32 _t3, const std::string & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void FileMessageItem::signalSerDownLoadFile(int _t1, const std::string & _t2, int64 _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void FileMessageItem::signalDownfileFinish()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
struct qt_meta_stringdata_FileMessageWidget_t {
    QByteArrayData data[10];
    char stringdata0[111];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FileMessageWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FileMessageWidget_t qt_meta_stringdata_FileMessageWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "FileMessageWidget"
QT_MOC_LITERAL(1, 18, 15), // "onSaveCloudDisk"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 12), // "onSerSendMsg"
QT_MOC_LITERAL(4, 48, 3), // "err"
QT_MOC_LITERAL(5, 52, 7), // "msgtime"
QT_MOC_LITERAL(6, 60, 5), // "msgid"
QT_MOC_LITERAL(7, 66, 9), // "uiLocalId"
QT_MOC_LITERAL(8, 76, 14), // "onSerCloudDisk"
QT_MOC_LITERAL(9, 91, 19) // "onSerDownfileFinish"

    },
    "FileMessageWidget\0onSaveCloudDisk\0\0"
    "onSerSendMsg\0err\0msgtime\0msgid\0uiLocalId\0"
    "onSerCloudDisk\0onSerDownfileFinish"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FileMessageWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    4,   35,    2, 0x09 /* Protected */,
       8,    0,   44,    2, 0x09 /* Protected */,
       9,    0,   45,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::LongLong, QMetaType::LongLong, QMetaType::LongLong,    4,    5,    6,    7,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FileMessageWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FileMessageWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onSaveCloudDisk(); break;
        case 1: _t->onSerSendMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< qint64(*)>(_a[3])),(*reinterpret_cast< qint64(*)>(_a[4]))); break;
        case 2: _t->onSerCloudDisk(); break;
        case 3: _t->onSerDownfileFinish(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (FileMessageWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&FileMessageWidget::onSaveCloudDisk)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FileMessageWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<AbstractMessageWidget::staticMetaObject>(),
    qt_meta_stringdata_FileMessageWidget.data,
    qt_meta_data_FileMessageWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FileMessageWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FileMessageWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FileMessageWidget.stringdata0))
        return static_cast<void*>(this);
    return AbstractMessageWidget::qt_metacast(_clname);
}

int FileMessageWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractMessageWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void FileMessageWidget::onSaveCloudDisk()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
