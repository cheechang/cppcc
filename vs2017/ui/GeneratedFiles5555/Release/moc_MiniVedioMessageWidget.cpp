/****************************************************************************
** Meta object code from reading C++ file 'MiniVedioMessageWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/chat/bubble/MiniVedioMessageWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MiniVedioMessageWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__MiniVedioMessageWidget_t {
    QByteArrayData data[26];
    char stringdata0[345];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__MiniVedioMessageWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__MiniVedioMessageWidget_t qt_meta_stringdata_ui__MiniVedioMessageWidget = {
    {
QT_MOC_LITERAL(0, 0, 26), // "ui::MiniVedioMessageWidget"
QT_MOC_LITERAL(1, 27, 27), // "signalSerDownVedioMsgResult"
QT_MOC_LITERAL(2, 55, 0), // ""
QT_MOC_LITERAL(3, 56, 4), // "code"
QT_MOC_LITERAL(4, 61, 11), // "std::string"
QT_MOC_LITERAL(5, 73, 4), // "path"
QT_MOC_LITERAL(6, 78, 5), // "int64"
QT_MOC_LITERAL(7, 84, 8), // "senderID"
QT_MOC_LITERAL(8, 93, 8), // "isSilent"
QT_MOC_LITERAL(9, 102, 20), // "signalSerDownLoadImg"
QT_MOC_LITERAL(10, 123, 15), // "singalPlayVideo"
QT_MOC_LITERAL(11, 139, 16), // "onSerDownLoadImg"
QT_MOC_LITERAL(12, 156, 3), // "err"
QT_MOC_LITERAL(13, 160, 7), // "imgname"
QT_MOC_LITERAL(14, 168, 8), // "targetid"
QT_MOC_LITERAL(15, 177, 23), // "onSerDownVedioMsgResult"
QT_MOC_LITERAL(16, 201, 14), // "onSerPlayVideo"
QT_MOC_LITERAL(17, 216, 20), // "onCtrlSilentPlayMenu"
QT_MOC_LITERAL(18, 237, 21), // "onSerDownLoadAduioMsg"
QT_MOC_LITERAL(19, 259, 3), // "url"
QT_MOC_LITERAL(20, 263, 5), // "isSrc"
QT_MOC_LITERAL(21, 269, 10), // "PlayFinish"
QT_MOC_LITERAL(22, 280, 23), // "onFormatConvertFinished"
QT_MOC_LITERAL(23, 304, 8), // "exitCode"
QT_MOC_LITERAL(24, 313, 20), // "QProcess::ExitStatus"
QT_MOC_LITERAL(25, 334, 10) // "exitStatus"

    },
    "ui::MiniVedioMessageWidget\0"
    "signalSerDownVedioMsgResult\0\0code\0"
    "std::string\0path\0int64\0senderID\0"
    "isSilent\0signalSerDownLoadImg\0"
    "singalPlayVideo\0onSerDownLoadImg\0err\0"
    "imgname\0targetid\0onSerDownVedioMsgResult\0"
    "onSerPlayVideo\0onCtrlSilentPlayMenu\0"
    "onSerDownLoadAduioMsg\0url\0isSrc\0"
    "PlayFinish\0onFormatConvertFinished\0"
    "exitCode\0QProcess::ExitStatus\0exitStatus"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__MiniVedioMessageWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    4,   64,    2, 0x06 /* Public */,
       9,    3,   73,    2, 0x06 /* Public */,
      10,    0,   80,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    3,   81,    2, 0x0a /* Public */,
      15,    4,   88,    2, 0x0a /* Public */,
      16,    0,   97,    2, 0x0a /* Public */,
      17,    0,   98,    2, 0x0a /* Public */,
      18,    2,   99,    2, 0x0a /* Public */,
      21,    0,  104,    2, 0x0a /* Public */,
      22,    2,  105,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4, 0x80000000 | 6, QMetaType::Bool,    3,    5,    7,    8,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4, 0x80000000 | 6,    2,    2,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4, 0x80000000 | 6,   12,   13,   14,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4, 0x80000000 | 6, QMetaType::Bool,    3,    5,    7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4, QMetaType::Bool,   19,   20,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 24,   23,   25,

       0        // eod
};

void ui::MiniVedioMessageWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MiniVedioMessageWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerDownVedioMsgResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 1: _t->signalSerDownLoadImg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3]))); break;
        case 2: _t->singalPlayVideo(); break;
        case 3: _t->onSerDownLoadImg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< const int64(*)>(_a[3]))); break;
        case 4: _t->onSerDownVedioMsgResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4]))); break;
        case 5: _t->onSerPlayVideo(); break;
        case 6: _t->onCtrlSilentPlayMenu(); break;
        case 7: _t->onSerDownLoadAduioMsg((*reinterpret_cast< std::string(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 8: _t->PlayFinish(); break;
        case 9: _t->onFormatConvertFinished((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QProcess::ExitStatus(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MiniVedioMessageWidget::*)(int , const std::string & , int64 , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MiniVedioMessageWidget::signalSerDownVedioMsgResult)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MiniVedioMessageWidget::*)(int , const std::string & , int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MiniVedioMessageWidget::signalSerDownLoadImg)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MiniVedioMessageWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MiniVedioMessageWidget::singalPlayVideo)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::MiniVedioMessageWidget::staticMetaObject = { {
    &AbstractMessageWidget::staticMetaObject,
    qt_meta_stringdata_ui__MiniVedioMessageWidget.data,
    qt_meta_data_ui__MiniVedioMessageWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::MiniVedioMessageWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::MiniVedioMessageWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__MiniVedioMessageWidget.stringdata0))
        return static_cast<void*>(this);
    return AbstractMessageWidget::qt_metacast(_clname);
}

int ui::MiniVedioMessageWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractMessageWidget::qt_metacall(_c, _id, _a);
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
void ui::MiniVedioMessageWidget::signalSerDownVedioMsgResult(int _t1, const std::string & _t2, int64 _t3, bool _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::MiniVedioMessageWidget::signalSerDownLoadImg(int _t1, const std::string & _t2, int64 _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::MiniVedioMessageWidget::singalPlayVideo()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
