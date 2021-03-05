/****************************************************************************
** Meta object code from reading C++ file 'imagemessagewidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/chat/bubble/imagemessagewidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'imagemessagewidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ImageMessageWidget_t {
    QByteArrayData data[21];
    char stringdata0[248];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ImageMessageWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ImageMessageWidget_t qt_meta_stringdata_ImageMessageWidget = {
    {
QT_MOC_LITERAL(0, 0, 18), // "ImageMessageWidget"
QT_MOC_LITERAL(1, 19, 20), // "signalSerDownLoadImg"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 11), // "std::string"
QT_MOC_LITERAL(4, 53, 5), // "int64"
QT_MOC_LITERAL(5, 59, 5), // "isSrc"
QT_MOC_LITERAL(6, 65, 19), // "signalSerGetImgMsgs"
QT_MOC_LITERAL(7, 85, 28), // "std::map<int64,data::MsgImg>"
QT_MOC_LITERAL(8, 114, 19), // "signalSerProgressCb"
QT_MOC_LITERAL(9, 134, 5), // "int32"
QT_MOC_LITERAL(10, 140, 9), // "onCopyMsg"
QT_MOC_LITERAL(11, 150, 15), // "onSerGetImgMsgs"
QT_MOC_LITERAL(12, 166, 4), // "code"
QT_MOC_LITERAL(13, 171, 3), // "msg"
QT_MOC_LITERAL(14, 175, 16), // "onSerDownLoadImg"
QT_MOC_LITERAL(15, 192, 3), // "err"
QT_MOC_LITERAL(16, 196, 7), // "imgname"
QT_MOC_LITERAL(17, 204, 8), // "targetid"
QT_MOC_LITERAL(18, 213, 7), // "localid"
QT_MOC_LITERAL(19, 221, 10), // "encrptykey"
QT_MOC_LITERAL(20, 232, 15) // "onSerProgressCb"

    },
    "ImageMessageWidget\0signalSerDownLoadImg\0"
    "\0std::string\0int64\0isSrc\0signalSerGetImgMsgs\0"
    "std::map<int64,data::MsgImg>\0"
    "signalSerProgressCb\0int32\0onCopyMsg\0"
    "onSerGetImgMsgs\0code\0msg\0onSerDownLoadImg\0"
    "err\0imgname\0targetid\0localid\0encrptykey\0"
    "onSerProgressCb"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ImageMessageWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    6,   49,    2, 0x06 /* Public */,
       6,    2,   62,    2, 0x06 /* Public */,
       8,    4,   67,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   76,    2, 0x0a /* Public */,
      11,    2,   77,    2, 0x0a /* Public */,
      14,    6,   82,    2, 0x0a /* Public */,
      20,    4,   95,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3, 0x80000000 | 4, 0x80000000 | 4, 0x80000000 | 3, QMetaType::Bool,    2,    2,    2,    2,    2,    5,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,    2,    2,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 9, 0x80000000 | 3, 0x80000000 | 4,    2,    2,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7,   12,   13,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3, 0x80000000 | 4, 0x80000000 | 4, 0x80000000 | 3, QMetaType::Bool,   15,   16,   17,   18,   19,    5,
    QMetaType::Void, 0x80000000 | 9, 0x80000000 | 9, 0x80000000 | 3, 0x80000000 | 4,    2,    2,    2,    2,

       0        // eod
};

void ImageMessageWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ImageMessageWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerDownLoadImg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3])),(*reinterpret_cast< int64(*)>(_a[4])),(*reinterpret_cast< const std::string(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6]))); break;
        case 1: _t->signalSerGetImgMsgs((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::map<int64,data::MsgImg>(*)>(_a[2]))); break;
        case 2: _t->signalSerProgressCb((*reinterpret_cast< int32(*)>(_a[1])),(*reinterpret_cast< int32(*)>(_a[2])),(*reinterpret_cast< const std::string(*)>(_a[3])),(*reinterpret_cast< int64(*)>(_a[4]))); break;
        case 3: _t->onCopyMsg(); break;
        case 4: _t->onSerGetImgMsgs((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::map<int64,data::MsgImg>(*)>(_a[2]))); break;
        case 5: _t->onSerDownLoadImg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3])),(*reinterpret_cast< int64(*)>(_a[4])),(*reinterpret_cast< const std::string(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6]))); break;
        case 6: _t->onSerProgressCb((*reinterpret_cast< int32(*)>(_a[1])),(*reinterpret_cast< int32(*)>(_a[2])),(*reinterpret_cast< const std::string(*)>(_a[3])),(*reinterpret_cast< int64(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ImageMessageWidget::*)(int , const std::string & , int64 , int64 , const std::string & , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ImageMessageWidget::signalSerDownLoadImg)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ImageMessageWidget::*)(int , std::map<int64,data::MsgImg> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ImageMessageWidget::signalSerGetImgMsgs)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ImageMessageWidget::*)(int32 , int32 , const std::string & , int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ImageMessageWidget::signalSerProgressCb)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ImageMessageWidget::staticMetaObject = { {
    &TextMessageWidget::staticMetaObject,
    qt_meta_stringdata_ImageMessageWidget.data,
    qt_meta_data_ImageMessageWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ImageMessageWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ImageMessageWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ImageMessageWidget.stringdata0))
        return static_cast<void*>(this);
    return TextMessageWidget::qt_metacast(_clname);
}

int ImageMessageWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TextMessageWidget::qt_metacall(_c, _id, _a);
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
void ImageMessageWidget::signalSerDownLoadImg(int _t1, const std::string & _t2, int64 _t3, int64 _t4, const std::string & _t5, bool _t6)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)), const_cast<void*>(reinterpret_cast<const void*>(&_t6)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ImageMessageWidget::signalSerGetImgMsgs(int _t1, std::map<int64,data::MsgImg> _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ImageMessageWidget::signalSerProgressCb(int32 _t1, int32 _t2, const std::string & _t3, int64 _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
