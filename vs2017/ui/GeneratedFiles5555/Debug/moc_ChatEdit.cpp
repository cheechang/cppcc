/****************************************************************************
** Meta object code from reading C++ file 'ChatEdit.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../controls/ChatEdit.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ChatEdit.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__ChatEdit_t {
    QByteArrayData data[18];
    char stringdata0[206];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__ChatEdit_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__ChatEdit_t qt_meta_stringdata_ui__ChatEdit = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ui::ChatEdit"
QT_MOC_LITERAL(1, 13, 7), // "clicked"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 8), // "keyPress"
QT_MOC_LITERAL(4, 31, 7), // "QEvent*"
QT_MOC_LITERAL(5, 39, 20), // "noticeInputEditFocus"
QT_MOC_LITERAL(6, 60, 7), // "SendMsg"
QT_MOC_LITERAL(7, 68, 18), // "std::vector<int64>"
QT_MOC_LITERAL(8, 87, 9), // "onAnimate"
QT_MOC_LITERAL(9, 97, 1), // "a"
QT_MOC_LITERAL(10, 99, 9), // "onSendMsg"
QT_MOC_LITERAL(11, 109, 13), // "ontextChanged"
QT_MOC_LITERAL(12, 123, 17), // "onContentsChanged"
QT_MOC_LITERAL(13, 141, 19), // "onSetSendMsgShorcut"
QT_MOC_LITERAL(14, 161, 3), // "val"
QT_MOC_LITERAL(15, 165, 12), // "onInserAtImg"
QT_MOC_LITERAL(16, 178, 7), // "imgPath"
QT_MOC_LITERAL(17, 186, 19) // "onGroupAtDataFinish"

    },
    "ui::ChatEdit\0clicked\0\0keyPress\0QEvent*\0"
    "noticeInputEditFocus\0SendMsg\0"
    "std::vector<int64>\0onAnimate\0a\0onSendMsg\0"
    "ontextChanged\0onContentsChanged\0"
    "onSetSendMsgShorcut\0val\0onInserAtImg\0"
    "imgPath\0onGroupAtDataFinish"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__ChatEdit[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x06 /* Public */,
       3,    1,   70,    2, 0x06 /* Public */,
       5,    0,   73,    2, 0x06 /* Public */,
       6,    7,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   89,    2, 0x0a /* Public */,
      10,    0,   92,    2, 0x0a /* Public */,
      11,    0,   93,    2, 0x0a /* Public */,
      12,    0,   94,    2, 0x0a /* Public */,
      13,    1,   95,    2, 0x0a /* Public */,
      15,    1,   98,    2, 0x0a /* Public */,
      17,    0,  101,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QStringList, QMetaType::QStringList, 0x80000000 | 7, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,    2,    2,    2,    2,    2,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void,

       0        // eod
};

void ui::ChatEdit::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ChatEdit *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->clicked(); break;
        case 1: _t->keyPress((*reinterpret_cast< QEvent*(*)>(_a[1]))); break;
        case 2: _t->noticeInputEditFocus(); break;
        case 3: _t->SendMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QStringList(*)>(_a[2])),(*reinterpret_cast< QStringList(*)>(_a[3])),(*reinterpret_cast< std::vector<int64>(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5])),(*reinterpret_cast< bool(*)>(_a[6])),(*reinterpret_cast< bool(*)>(_a[7]))); break;
        case 4: _t->onAnimate((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->onSendMsg(); break;
        case 6: _t->ontextChanged(); break;
        case 7: _t->onContentsChanged(); break;
        case 8: _t->onSetSendMsgShorcut((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->onInserAtImg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 10: _t->onGroupAtDataFinish(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ChatEdit::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatEdit::clicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ChatEdit::*)(QEvent * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatEdit::keyPress)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ChatEdit::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatEdit::noticeInputEditFocus)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ChatEdit::*)(QString , QStringList , QStringList , std::vector<int64> , bool , bool , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatEdit::SendMsg)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::ChatEdit::staticMetaObject = { {
    QMetaObject::SuperData::link<QTextEdit::staticMetaObject>(),
    qt_meta_stringdata_ui__ChatEdit.data,
    qt_meta_data_ui__ChatEdit,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::ChatEdit::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::ChatEdit::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__ChatEdit.stringdata0))
        return static_cast<void*>(this);
    return QTextEdit::qt_metacast(_clname);
}

int ui::ChatEdit::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTextEdit::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void ui::ChatEdit::clicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ui::ChatEdit::keyPress(QEvent * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::ChatEdit::noticeInputEditFocus()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ui::ChatEdit::SendMsg(QString _t1, QStringList _t2, QStringList _t3, std::vector<int64> _t4, bool _t5, bool _t6, bool _t7)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t5))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t6))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t7))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
