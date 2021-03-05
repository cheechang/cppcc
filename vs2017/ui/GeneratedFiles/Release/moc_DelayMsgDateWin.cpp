/****************************************************************************
** Meta object code from reading C++ file 'DelayMsgDateWin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/chat/DelayMsgDateWin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DelayMsgDateWin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__DelayMsgDateWin_t {
    QByteArrayData data[12];
    char stringdata0[172];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__DelayMsgDateWin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__DelayMsgDateWin_t qt_meta_stringdata_ui__DelayMsgDateWin = {
    {
QT_MOC_LITERAL(0, 0, 19), // "ui::DelayMsgDateWin"
QT_MOC_LITERAL(1, 20, 18), // "signalSendDelayMsg"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 5), // "int64"
QT_MOC_LITERAL(4, 46, 4), // "time"
QT_MOC_LITERAL(5, 51, 4), // "text"
QT_MOC_LITERAL(6, 56, 18), // "onBtnCancelClicked"
QT_MOC_LITERAL(7, 75, 14), // "onBtnOKClicked"
QT_MOC_LITERAL(8, 90, 24), // "onDayCurrentIndexChanged"
QT_MOC_LITERAL(9, 115, 5), // "index"
QT_MOC_LITERAL(10, 121, 25), // "onHourCurrentIndexChanged"
QT_MOC_LITERAL(11, 147, 24) // "onMinCurrentIndexChanged"

    },
    "ui::DelayMsgDateWin\0signalSendDelayMsg\0"
    "\0int64\0time\0text\0onBtnCancelClicked\0"
    "onBtnOKClicked\0onDayCurrentIndexChanged\0"
    "index\0onHourCurrentIndexChanged\0"
    "onMinCurrentIndexChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__DelayMsgDateWin[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   49,    2, 0x0a /* Public */,
       7,    0,   50,    2, 0x0a /* Public */,
       8,    1,   51,    2, 0x0a /* Public */,
      10,    1,   54,    2, 0x0a /* Public */,
      11,    1,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QString,    4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::Int,    9,

       0        // eod
};

void ui::DelayMsgDateWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DelayMsgDateWin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSendDelayMsg((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 1: _t->onBtnCancelClicked(); break;
        case 2: _t->onBtnOKClicked(); break;
        case 3: _t->onDayCurrentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->onHourCurrentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->onMinCurrentIndexChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DelayMsgDateWin::*)(int64 , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DelayMsgDateWin::signalSendDelayMsg)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::DelayMsgDateWin::staticMetaObject = { {
    &BaseDialog::staticMetaObject,
    qt_meta_stringdata_ui__DelayMsgDateWin.data,
    qt_meta_data_ui__DelayMsgDateWin,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::DelayMsgDateWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::DelayMsgDateWin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__DelayMsgDateWin.stringdata0))
        return static_cast<void*>(this);
    return BaseDialog::qt_metacast(_clname);
}

int ui::DelayMsgDateWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ui::DelayMsgDateWin::signalSendDelayMsg(int64 _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
