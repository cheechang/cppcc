/****************************************************************************
** Meta object code from reading C++ file 'MsgManagerWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/chat/MsgManagerWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'MsgManagerWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__MsgManagerWidget_t {
    QByteArrayData data[20];
    char stringdata0[332];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__MsgManagerWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__MsgManagerWidget_t qt_meta_stringdata_ui__MsgManagerWidget = {
    {
QT_MOC_LITERAL(0, 0, 20), // "ui::MsgManagerWidget"
QT_MOC_LITERAL(1, 21, 23), // "signalSerSerchGlobalMsg"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 22), // "data::MsgSearchResult&"
QT_MOC_LITERAL(4, 69, 23), // "signalSerSerchDetailMsg"
QT_MOC_LITERAL(5, 93, 28), // "data::MsgDetailSearchResult&"
QT_MOC_LITERAL(6, 122, 20), // "signalSerGetUserInfo"
QT_MOC_LITERAL(7, 143, 15), // "data::UserData&"
QT_MOC_LITERAL(8, 159, 21), // "CSharedPtr<data::Msg>"
QT_MOC_LITERAL(9, 181, 13), // "onSerSerchMsg"
QT_MOC_LITERAL(10, 195, 19), // "onSerSerchGlobalMsg"
QT_MOC_LITERAL(11, 215, 4), // "code"
QT_MOC_LITERAL(12, 220, 3), // "msg"
QT_MOC_LITERAL(13, 224, 19), // "onSerSerchDetailMsg"
QT_MOC_LITERAL(14, 244, 9), // "detailmsg"
QT_MOC_LITERAL(15, 254, 14), // "onSerClickItem"
QT_MOC_LITERAL(16, 269, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(17, 286, 16), // "onSerGetUserInfo"
QT_MOC_LITERAL(18, 303, 7), // "usrdata"
QT_MOC_LITERAL(19, 311, 20) // "onSerClearBtnClicked"

    },
    "ui::MsgManagerWidget\0signalSerSerchGlobalMsg\0"
    "\0data::MsgSearchResult&\0signalSerSerchDetailMsg\0"
    "data::MsgDetailSearchResult&\0"
    "signalSerGetUserInfo\0data::UserData&\0"
    "CSharedPtr<data::Msg>\0onSerSerchMsg\0"
    "onSerSerchGlobalMsg\0code\0msg\0"
    "onSerSerchDetailMsg\0detailmsg\0"
    "onSerClickItem\0QListWidgetItem*\0"
    "onSerGetUserInfo\0usrdata\0onSerClearBtnClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__MsgManagerWidget[] = {

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
       1,    2,   59,    2, 0x06 /* Public */,
       4,    2,   64,    2, 0x06 /* Public */,
       6,    3,   69,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   76,    2, 0x0a /* Public */,
      10,    2,   77,    2, 0x0a /* Public */,
      13,    2,   82,    2, 0x0a /* Public */,
      15,    1,   87,    2, 0x0a /* Public */,
      17,    3,   90,    2, 0x0a /* Public */,
      19,    0,   97,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 5,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7, 0x80000000 | 8,    2,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3,   11,   12,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 5,   11,   14,
    QMetaType::Void, 0x80000000 | 16,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 7, 0x80000000 | 8,   11,   18,    2,
    QMetaType::Void,

       0        // eod
};

void ui::MsgManagerWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MsgManagerWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerSerchGlobalMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::MsgSearchResult(*)>(_a[2]))); break;
        case 1: _t->signalSerSerchDetailMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::MsgDetailSearchResult(*)>(_a[2]))); break;
        case 2: _t->signalSerGetUserInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::UserData(*)>(_a[2])),(*reinterpret_cast< CSharedPtr<data::Msg>(*)>(_a[3]))); break;
        case 3: _t->onSerSerchMsg(); break;
        case 4: _t->onSerSerchGlobalMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::MsgSearchResult(*)>(_a[2]))); break;
        case 5: _t->onSerSerchDetailMsg((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::MsgDetailSearchResult(*)>(_a[2]))); break;
        case 6: _t->onSerClickItem((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 7: _t->onSerGetUserInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::UserData(*)>(_a[2])),(*reinterpret_cast< CSharedPtr<data::Msg>(*)>(_a[3]))); break;
        case 8: _t->onSerClearBtnClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MsgManagerWidget::*)(int , data::MsgSearchResult & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MsgManagerWidget::signalSerSerchGlobalMsg)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MsgManagerWidget::*)(int , data::MsgDetailSearchResult & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MsgManagerWidget::signalSerSerchDetailMsg)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MsgManagerWidget::*)(int , data::UserData & , CSharedPtr<data::Msg> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MsgManagerWidget::signalSerGetUserInfo)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::MsgManagerWidget::staticMetaObject = { {
    &BaseWindow::staticMetaObject,
    qt_meta_stringdata_ui__MsgManagerWidget.data,
    qt_meta_data_ui__MsgManagerWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::MsgManagerWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::MsgManagerWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__MsgManagerWidget.stringdata0))
        return static_cast<void*>(this);
    return BaseWindow::qt_metacast(_clname);
}

int ui::MsgManagerWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseWindow::qt_metacall(_c, _id, _a);
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
void ui::MsgManagerWidget::signalSerSerchGlobalMsg(int _t1, data::MsgSearchResult & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::MsgManagerWidget::signalSerSerchDetailMsg(int _t1, data::MsgDetailSearchResult & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::MsgManagerWidget::signalSerGetUserInfo(int _t1, data::UserData & _t2, CSharedPtr<data::Msg> _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
