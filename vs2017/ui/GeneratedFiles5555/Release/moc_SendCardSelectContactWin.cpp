/****************************************************************************
** Meta object code from reading C++ file 'SendCardSelectContactWin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/chat/SendCardSelectContactWin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SendCardSelectContactWin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__SendCardSelectContactWin_t {
    QByteArrayData data[10];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__SendCardSelectContactWin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__SendCardSelectContactWin_t qt_meta_stringdata_ui__SendCardSelectContactWin = {
    {
QT_MOC_LITERAL(0, 0, 28), // "ui::SendCardSelectContactWin"
QT_MOC_LITERAL(1, 29, 12), // "signalSendId"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 5), // "int64"
QT_MOC_LITERAL(4, 49, 17), // "onClearBtnClicked"
QT_MOC_LITERAL(5, 67, 13), // "onTextChanged"
QT_MOC_LITERAL(6, 81, 4), // "text"
QT_MOC_LITERAL(7, 86, 13), // "onClickedItem"
QT_MOC_LITERAL(8, 100, 27), // "CSharedPtr<data::ChatInfo>&"
QT_MOC_LITERAL(9, 128, 4) // "chat"

    },
    "ui::SendCardSelectContactWin\0signalSendId\0"
    "\0int64\0onClearBtnClicked\0onTextChanged\0"
    "text\0onClickedItem\0CSharedPtr<data::ChatInfo>&\0"
    "chat"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__SendCardSelectContactWin[] = {

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
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   37,    2, 0x09 /* Protected */,
       5,    1,   38,    2, 0x09 /* Protected */,
       7,    1,   41,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

void ui::SendCardSelectContactWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SendCardSelectContactWin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSendId((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 1: _t->onClearBtnClicked(); break;
        case 2: _t->onTextChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->onClickedItem((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SendCardSelectContactWin::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SendCardSelectContactWin::signalSendId)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::SendCardSelectContactWin::staticMetaObject = { {
    &BaseWindow::staticMetaObject,
    qt_meta_stringdata_ui__SendCardSelectContactWin.data,
    qt_meta_data_ui__SendCardSelectContactWin,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::SendCardSelectContactWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::SendCardSelectContactWin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__SendCardSelectContactWin.stringdata0))
        return static_cast<void*>(this);
    return BaseWindow::qt_metacast(_clname);
}

int ui::SendCardSelectContactWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseWindow::qt_metacall(_c, _id, _a);
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
void ui::SendCardSelectContactWin::signalSendId(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
