/****************************************************************************
** Meta object code from reading C++ file 'BurnMsgWin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../mainwindow/chat/bubble/BurnMsgWin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'BurnMsgWin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__BurnImage_t {
    QByteArrayData data[11];
    char stringdata0[120];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__BurnImage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__BurnImage_t qt_meta_stringdata_ui__BurnImage = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ui::BurnImage"
QT_MOC_LITERAL(1, 14, 20), // "signalSerDownloadImg"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 3), // "err"
QT_MOC_LITERAL(4, 40, 11), // "std::string"
QT_MOC_LITERAL(5, 52, 7), // "imgName"
QT_MOC_LITERAL(6, 60, 5), // "int64"
QT_MOC_LITERAL(7, 66, 5), // "tarid"
QT_MOC_LITERAL(8, 72, 17), // "downloadImgFinish"
QT_MOC_LITERAL(9, 90, 16), // "onSerDownloadImg"
QT_MOC_LITERAL(10, 107, 12) // "onViewBigImg"

    },
    "ui::BurnImage\0signalSerDownloadImg\0\0"
    "err\0std::string\0imgName\0int64\0tarid\0"
    "downloadImgFinish\0onSerDownloadImg\0"
    "onViewBigImg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__BurnImage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   34,    2, 0x06 /* Public */,
       8,    0,   41,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    3,   42,    2, 0x0a /* Public */,
      10,    0,   49,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4, 0x80000000 | 6,    3,    5,    7,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4, 0x80000000 | 6,    3,    5,    7,
    QMetaType::Void,

       0        // eod
};

void ui::BurnImage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BurnImage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerDownloadImg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3]))); break;
        case 1: _t->downloadImgFinish(); break;
        case 2: _t->onSerDownloadImg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3]))); break;
        case 3: _t->onViewBigImg(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BurnImage::*)(int , const std::string & , int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BurnImage::signalSerDownloadImg)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BurnImage::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BurnImage::downloadImgFinish)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::BurnImage::staticMetaObject = { {
    QMetaObject::SuperData::link<ClickLabel::staticMetaObject>(),
    qt_meta_stringdata_ui__BurnImage.data,
    qt_meta_data_ui__BurnImage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::BurnImage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::BurnImage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__BurnImage.stringdata0))
        return static_cast<void*>(this);
    return ClickLabel::qt_metacast(_clname);
}

int ui::BurnImage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ClickLabel::qt_metacall(_c, _id, _a);
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
void ui::BurnImage::signalSerDownloadImg(int _t1, const std::string & _t2, int64 _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::BurnImage::downloadImgFinish()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
struct qt_meta_stringdata_ui__BurnMsgWin_t {
    QByteArrayData data[16];
    char stringdata0[190];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__BurnMsgWin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__BurnMsgWin_t qt_meta_stringdata_ui__BurnMsgWin = {
    {
QT_MOC_LITERAL(0, 0, 14), // "ui::BurnMsgWin"
QT_MOC_LITERAL(1, 15, 20), // "signalSerGetUserInfo"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 15), // "data::UserData&"
QT_MOC_LITERAL(4, 53, 5), // "int64"
QT_MOC_LITERAL(5, 59, 2), // "id"
QT_MOC_LITERAL(6, 62, 4), // "name"
QT_MOC_LITERAL(7, 67, 6), // "avatar"
QT_MOC_LITERAL(8, 74, 9), // "startChat"
QT_MOC_LITERAL(9, 84, 27), // "CSharedPtr<data::ChatInfo>&"
QT_MOC_LITERAL(10, 112, 9), // "onBurnMsg"
QT_MOC_LITERAL(11, 122, 15), // "onTimerInterval"
QT_MOC_LITERAL(12, 138, 16), // "onSerGetUserInfo"
QT_MOC_LITERAL(13, 155, 17), // "onSerShowUserInfo"
QT_MOC_LITERAL(14, 173, 11), // "onStartChat"
QT_MOC_LITERAL(15, 185, 4) // "chat"

    },
    "ui::BurnMsgWin\0signalSerGetUserInfo\0"
    "\0data::UserData&\0int64\0id\0name\0avatar\0"
    "startChat\0CSharedPtr<data::ChatInfo>&\0"
    "onBurnMsg\0onTimerInterval\0onSerGetUserInfo\0"
    "onSerShowUserInfo\0onStartChat\0chat"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__BurnMsgWin[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    5,   49,    2, 0x06 /* Public */,
       8,    1,   60,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   63,    2, 0x09 /* Protected */,
      11,    0,   64,    2, 0x09 /* Protected */,
      12,    5,   65,    2, 0x09 /* Protected */,
      13,    3,   76,    2, 0x09 /* Protected */,
      14,    1,   83,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3, 0x80000000 | 4, QMetaType::QString, QMetaType::QString,    2,    2,    5,    6,    7,
    QMetaType::Void, 0x80000000 | 9,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3, 0x80000000 | 4, QMetaType::QString, QMetaType::QString,    2,    2,    5,    6,    7,
    QMetaType::Void, 0x80000000 | 4, QMetaType::QString, QMetaType::QString,    5,    6,    7,
    QMetaType::Void, 0x80000000 | 9,   15,

       0        // eod
};

void ui::BurnMsgWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BurnMsgWin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerGetUserInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::UserData(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 1: _t->startChat((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        case 2: _t->onBurnMsg(); break;
        case 3: _t->onTimerInterval(); break;
        case 4: _t->onSerGetUserInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::UserData(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5]))); break;
        case 5: _t->onSerShowUserInfo((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 6: _t->onStartChat((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BurnMsgWin::*)(int , data::UserData & , int64 , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BurnMsgWin::signalSerGetUserInfo)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BurnMsgWin::*)(CSharedPtr<data::ChatInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BurnMsgWin::startChat)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::BurnMsgWin::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_ui__BurnMsgWin.data,
    qt_meta_data_ui__BurnMsgWin,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::BurnMsgWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::BurnMsgWin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__BurnMsgWin.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int ui::BurnMsgWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void ui::BurnMsgWin::signalSerGetUserInfo(int _t1, data::UserData & _t2, int64 _t3, QString _t4, QString _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::BurnMsgWin::startChat(CSharedPtr<data::ChatInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
