/****************************************************************************
** Meta object code from reading C++ file 'ChatTilte.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/chat/ChatTilte.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ChatTilte.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__ChatTitle_t {
    QByteArrayData data[22];
    char stringdata0[325];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__ChatTitle_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__ChatTitle_t qt_meta_stringdata_ui__ChatTitle = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ui::ChatTitle"
QT_MOC_LITERAL(1, 14, 19), // "signalSerMoretopMsg"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 9), // "startChat"
QT_MOC_LITERAL(4, 45, 27), // "CSharedPtr<data::ChatInfo>&"
QT_MOC_LITERAL(5, 73, 4), // "chat"
QT_MOC_LITERAL(6, 78, 12), // "onAddContact"
QT_MOC_LITERAL(7, 91, 11), // "onDispGroup"
QT_MOC_LITERAL(8, 103, 10), // "onShowMenu"
QT_MOC_LITERAL(9, 114, 9), // "onShowDoc"
QT_MOC_LITERAL(10, 124, 12), // "onShowSpeech"
QT_MOC_LITERAL(11, 137, 11), // "onSerMsgTop"
QT_MOC_LITERAL(12, 149, 23), // "data::ZxTopInformation&"
QT_MOC_LITERAL(13, 173, 17), // "onShowSpeechCount"
QT_MOC_LITERAL(14, 191, 19), // "onShowSpeechSummary"
QT_MOC_LITERAL(15, 211, 17), // "onShowEssenceArea"
QT_MOC_LITERAL(16, 229, 16), // "onShowReadingDoc"
QT_MOC_LITERAL(17, 246, 13), // "onHttpInfoRsp"
QT_MOC_LITERAL(18, 260, 14), // "QNetworkReply*"
QT_MOC_LITERAL(19, 275, 7), // "preplay"
QT_MOC_LITERAL(20, 283, 20), // "onHttpInfoBookingRsp"
QT_MOC_LITERAL(21, 304, 20) // "onHttpInfoSubjectRsp"

    },
    "ui::ChatTitle\0signalSerMoretopMsg\0\0"
    "startChat\0CSharedPtr<data::ChatInfo>&\0"
    "chat\0onAddContact\0onDispGroup\0onShowMenu\0"
    "onShowDoc\0onShowSpeech\0onSerMsgTop\0"
    "data::ZxTopInformation&\0onShowSpeechCount\0"
    "onShowSpeechSummary\0onShowEssenceArea\0"
    "onShowReadingDoc\0onHttpInfoRsp\0"
    "QNetworkReply*\0preplay\0onHttpInfoBookingRsp\0"
    "onHttpInfoSubjectRsp"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__ChatTitle[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   89,    2, 0x06 /* Public */,
       3,    1,   90,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   93,    2, 0x09 /* Protected */,
       7,    0,   94,    2, 0x09 /* Protected */,
       8,    0,   95,    2, 0x09 /* Protected */,
       9,    0,   96,    2, 0x09 /* Protected */,
      10,    0,   97,    2, 0x09 /* Protected */,
      11,    1,   98,    2, 0x09 /* Protected */,
      13,    0,  101,    2, 0x09 /* Protected */,
      14,    0,  102,    2, 0x09 /* Protected */,
      15,    0,  103,    2, 0x09 /* Protected */,
      16,    0,  104,    2, 0x09 /* Protected */,
      17,    1,  105,    2, 0x0a /* Public */,
      20,    1,  108,    2, 0x0a /* Public */,
      21,    1,  111,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 12,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, 0x80000000 | 18,   19,

       0        // eod
};

void ui::ChatTitle::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ChatTitle *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerMoretopMsg(); break;
        case 1: _t->startChat((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        case 2: _t->onAddContact(); break;
        case 3: _t->onDispGroup(); break;
        case 4: _t->onShowMenu(); break;
        case 5: _t->onShowDoc(); break;
        case 6: _t->onShowSpeech(); break;
        case 7: _t->onSerMsgTop((*reinterpret_cast< data::ZxTopInformation(*)>(_a[1]))); break;
        case 8: _t->onShowSpeechCount(); break;
        case 9: _t->onShowSpeechSummary(); break;
        case 10: _t->onShowEssenceArea(); break;
        case 11: _t->onShowReadingDoc(); break;
        case 12: _t->onHttpInfoRsp((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 13: _t->onHttpInfoBookingRsp((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        case 14: _t->onHttpInfoSubjectRsp((*reinterpret_cast< QNetworkReply*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 12:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 13:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QNetworkReply* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ChatTitle::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatTitle::signalSerMoretopMsg)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ChatTitle::*)(CSharedPtr<data::ChatInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatTitle::startChat)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::ChatTitle::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ui__ChatTitle.data,
    qt_meta_data_ui__ChatTitle,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::ChatTitle::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::ChatTitle::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__ChatTitle.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ui::ChatTitle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void ui::ChatTitle::signalSerMoretopMsg()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ui::ChatTitle::startChat(CSharedPtr<data::ChatInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
