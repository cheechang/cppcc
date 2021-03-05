/****************************************************************************
** Meta object code from reading C++ file 'SelectHeadImgWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/SelectHeadImgWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SelectHeadImgWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__SelectHeadImgWidget_t {
    QByteArrayData data[18];
    char stringdata0[238];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__SelectHeadImgWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__SelectHeadImgWidget_t qt_meta_stringdata_ui__SelectHeadImgWidget = {
    {
QT_MOC_LITERAL(0, 0, 23), // "ui::SelectHeadImgWidget"
QT_MOC_LITERAL(1, 24, 16), // "signalSerSetHead"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 11), // "std::string"
QT_MOC_LITERAL(4, 54, 24), // "signalSerSetUserInfoHead"
QT_MOC_LITERAL(5, 79, 4), // "code"
QT_MOC_LITERAL(6, 84, 24), // "signalSerModifyGroupHead"
QT_MOC_LITERAL(7, 109, 12), // "std::string&"
QT_MOC_LITERAL(8, 122, 18), // "signalUserHeadSucc"
QT_MOC_LITERAL(9, 141, 7), // "file400"
QT_MOC_LITERAL(10, 149, 10), // "onBtnClose"
QT_MOC_LITERAL(11, 160, 7), // "onBtnOK"
QT_MOC_LITERAL(12, 168, 11), // "onMouseMove"
QT_MOC_LITERAL(13, 180, 1), // "p"
QT_MOC_LITERAL(14, 182, 13), // "onClipImgSucc"
QT_MOC_LITERAL(15, 196, 7), // "file150"
QT_MOC_LITERAL(16, 204, 12), // "onSerSetHead"
QT_MOC_LITERAL(17, 217, 20) // "onSerSetUserInfoHead"

    },
    "ui::SelectHeadImgWidget\0signalSerSetHead\0"
    "\0std::string\0signalSerSetUserInfoHead\0"
    "code\0signalSerModifyGroupHead\0"
    "std::string&\0signalUserHeadSucc\0file400\0"
    "onBtnClose\0onBtnOK\0onMouseMove\0p\0"
    "onClipImgSucc\0file150\0onSerSetHead\0"
    "onSerSetUserInfoHead"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__SelectHeadImgWidget[] = {

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
       1,    3,   64,    2, 0x06 /* Public */,
       4,    1,   71,    2, 0x06 /* Public */,
       6,    1,   74,    2, 0x06 /* Public */,
       8,    1,   77,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   80,    2, 0x0a /* Public */,
      11,    0,   81,    2, 0x0a /* Public */,
      12,    1,   82,    2, 0x0a /* Public */,
      14,    2,   85,    2, 0x0a /* Public */,
      16,    3,   90,    2, 0x0a /* Public */,
      17,    1,   97,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3, 0x80000000 | 3,    2,    2,    2,
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void, 0x80000000 | 7,    2,
    QMetaType::Void, QMetaType::QString,    9,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPoint,   13,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    9,   15,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3, 0x80000000 | 3,    2,    2,    2,
    QMetaType::Void, QMetaType::Int,    5,

       0        // eod
};

void ui::SelectHeadImgWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SelectHeadImgWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerSetHead((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< const std::string(*)>(_a[3]))); break;
        case 1: _t->signalSerSetUserInfoHead((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->signalSerModifyGroupHead((*reinterpret_cast< std::string(*)>(_a[1]))); break;
        case 3: _t->signalUserHeadSucc((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->onBtnClose(); break;
        case 5: _t->onBtnOK(); break;
        case 6: _t->onMouseMove((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        case 7: _t->onClipImgSucc((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 8: _t->onSerSetHead((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< const std::string(*)>(_a[3]))); break;
        case 9: _t->onSerSetUserInfoHead((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SelectHeadImgWidget::*)(int , const std::string & , const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SelectHeadImgWidget::signalSerSetHead)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SelectHeadImgWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SelectHeadImgWidget::signalSerSetUserInfoHead)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SelectHeadImgWidget::*)(std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SelectHeadImgWidget::signalSerModifyGroupHead)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (SelectHeadImgWidget::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SelectHeadImgWidget::signalUserHeadSucc)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::SelectHeadImgWidget::staticMetaObject = { {
    &TWindow::staticMetaObject,
    qt_meta_stringdata_ui__SelectHeadImgWidget.data,
    qt_meta_data_ui__SelectHeadImgWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::SelectHeadImgWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::SelectHeadImgWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__SelectHeadImgWidget.stringdata0))
        return static_cast<void*>(this);
    return TWindow::qt_metacast(_clname);
}

int ui::SelectHeadImgWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TWindow::qt_metacall(_c, _id, _a);
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
void ui::SelectHeadImgWidget::signalSerSetHead(int _t1, const std::string & _t2, const std::string & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::SelectHeadImgWidget::signalSerSetUserInfoHead(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::SelectHeadImgWidget::signalSerModifyGroupHead(std::string & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ui::SelectHeadImgWidget::signalUserHeadSucc(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
