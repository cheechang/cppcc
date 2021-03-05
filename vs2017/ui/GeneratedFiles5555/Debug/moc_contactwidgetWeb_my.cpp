/****************************************************************************
** Meta object code from reading C++ file 'contactwidgetWeb_my.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../mainwindow/contact/contactwidgetWeb_my.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'contactwidgetWeb_my.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__ContactWidgetWeb_my_t {
    QByteArrayData data[22];
    char stringdata0[261];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__ContactWidgetWeb_my_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__ContactWidgetWeb_my_t qt_meta_stringdata_ui__ContactWidgetWeb_my = {
    {
QT_MOC_LITERAL(0, 0, 23), // "ui::ContactWidgetWeb_my"
QT_MOC_LITERAL(1, 24, 9), // "startChat"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 27), // "CSharedPtr<data::ChatInfo>&"
QT_MOC_LITERAL(4, 63, 4), // "chat"
QT_MOC_LITERAL(5, 68, 16), // "MySelectListItem"
QT_MOC_LITERAL(6, 85, 4), // "item"
QT_MOC_LITERAL(7, 90, 11), // "closeWidget"
QT_MOC_LITERAL(8, 102, 8), // "maxWiget"
QT_MOC_LITERAL(9, 111, 9), // "sendToWeb"
QT_MOC_LITERAL(10, 121, 6), // "taskid"
QT_MOC_LITERAL(11, 128, 4), // "text"
QT_MOC_LITERAL(12, 133, 14), // "GetControlInfo"
QT_MOC_LITERAL(13, 148, 21), // "onShowContactInfoPage"
QT_MOC_LITERAL(14, 170, 13), // "data::Contact"
QT_MOC_LITERAL(15, 184, 7), // "contact"
QT_MOC_LITERAL(16, 192, 10), // "onTurnPage"
QT_MOC_LITERAL(17, 203, 1), // "i"
QT_MOC_LITERAL(18, 205, 13), // "sendTextToCpp"
QT_MOC_LITERAL(19, 219, 16), // "OnGetControlInfo"
QT_MOC_LITERAL(20, 236, 13), // "callQTProcess"
QT_MOC_LITERAL(21, 250, 10) // "onMaxWiget"

    },
    "ui::ContactWidgetWeb_my\0startChat\0\0"
    "CSharedPtr<data::ChatInfo>&\0chat\0"
    "MySelectListItem\0item\0closeWidget\0"
    "maxWiget\0sendToWeb\0taskid\0text\0"
    "GetControlInfo\0onShowContactInfoPage\0"
    "data::Contact\0contact\0onTurnPage\0i\0"
    "sendTextToCpp\0OnGetControlInfo\0"
    "callQTProcess\0onMaxWiget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__ContactWidgetWeb_my[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       5,    1,   77,    2, 0x06 /* Public */,
       7,    0,   80,    2, 0x06 /* Public */,
       8,    0,   81,    2, 0x06 /* Public */,
       9,    2,   82,    2, 0x06 /* Public */,
      12,    1,   87,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      13,    1,   90,    2, 0x09 /* Protected */,
      16,    1,   93,    2, 0x09 /* Protected */,
      18,    1,   96,    2, 0x0a /* Public */,
      19,    1,   99,    2, 0x0a /* Public */,
      20,    2,  102,    2, 0x0a /* Public */,
      21,    0,  107,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   10,   11,
    QMetaType::Void, QMetaType::QString,   11,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 14,   15,
    QMetaType::Void, QMetaType::Int,   17,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString,   11,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   10,   11,
    QMetaType::Void,

       0        // eod
};

void ui::ContactWidgetWeb_my::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ContactWidgetWeb_my *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startChat((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        case 1: _t->MySelectListItem((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->closeWidget(); break;
        case 3: _t->maxWiget(); break;
        case 4: _t->sendToWeb((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->GetControlInfo((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->onShowContactInfoPage((*reinterpret_cast< data::Contact(*)>(_a[1]))); break;
        case 7: _t->onTurnPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->sendTextToCpp((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->OnGetControlInfo((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 10: _t->callQTProcess((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 11: _t->onMaxWiget(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ContactWidgetWeb_my::*)(CSharedPtr<data::ChatInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContactWidgetWeb_my::startChat)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ContactWidgetWeb_my::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContactWidgetWeb_my::MySelectListItem)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ContactWidgetWeb_my::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContactWidgetWeb_my::closeWidget)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ContactWidgetWeb_my::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContactWidgetWeb_my::maxWiget)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ContactWidgetWeb_my::*)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContactWidgetWeb_my::sendToWeb)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ContactWidgetWeb_my::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContactWidgetWeb_my::GetControlInfo)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::ContactWidgetWeb_my::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ui__ContactWidgetWeb_my.data,
    qt_meta_data_ui__ContactWidgetWeb_my,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::ContactWidgetWeb_my::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::ContactWidgetWeb_my::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__ContactWidgetWeb_my.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ui::ContactWidgetWeb_my::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void ui::ContactWidgetWeb_my::startChat(CSharedPtr<data::ChatInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::ContactWidgetWeb_my::MySelectListItem(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::ContactWidgetWeb_my::closeWidget()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ui::ContactWidgetWeb_my::maxWiget()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ui::ContactWidgetWeb_my::sendToWeb(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ui::ContactWidgetWeb_my::GetControlInfo(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
