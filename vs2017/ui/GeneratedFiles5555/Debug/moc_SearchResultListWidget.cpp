/****************************************************************************
** Meta object code from reading C++ file 'SearchResultListWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../mainwindow/contact/searchcontact/SearchResultListWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SearchResultListWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__SearchResultListWidget_t {
    QByteArrayData data[16];
    char stringdata0[254];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__SearchResultListWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__SearchResultListWidget_t qt_meta_stringdata_ui__SearchResultListWidget = {
    {
QT_MOC_LITERAL(0, 0, 26), // "ui::SearchResultListWidget"
QT_MOC_LITERAL(1, 27, 22), // "signalSerSearchFromNet"
QT_MOC_LITERAL(2, 50, 0), // ""
QT_MOC_LITERAL(3, 51, 3), // "err"
QT_MOC_LITERAL(4, 55, 36), // "std::vector<data::SearchResul..."
QT_MOC_LITERAL(5, 92, 6), // "result"
QT_MOC_LITERAL(6, 99, 16), // "signalAddContact"
QT_MOC_LITERAL(7, 116, 22), // "data::SearchResultInfo"
QT_MOC_LITERAL(8, 139, 4), // "data"
QT_MOC_LITERAL(9, 144, 22), // "signalSerAddAppContact"
QT_MOC_LITERAL(10, 167, 18), // "onSerSearchFromNet"
QT_MOC_LITERAL(11, 186, 22), // "onAddContactBtnClicked"
QT_MOC_LITERAL(12, 209, 5), // "int64"
QT_MOC_LITERAL(13, 215, 8), // "targetId"
QT_MOC_LITERAL(14, 224, 10), // "itemWidget"
QT_MOC_LITERAL(15, 235, 18) // "onSerAddAppContact"

    },
    "ui::SearchResultListWidget\0"
    "signalSerSearchFromNet\0\0err\0"
    "std::vector<data::SearchResultInfo>&\0"
    "result\0signalAddContact\0data::SearchResultInfo\0"
    "data\0signalSerAddAppContact\0"
    "onSerSearchFromNet\0onAddContactBtnClicked\0"
    "int64\0targetId\0itemWidget\0onSerAddAppContact"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__SearchResultListWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,
       6,    1,   49,    2, 0x06 /* Public */,
       9,    1,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    2,   55,    2, 0x0a /* Public */,
      11,    2,   60,    2, 0x0a /* Public */,
      15,    1,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 4,    3,    5,
    QMetaType::Void, 0x80000000 | 12, QMetaType::VoidStar,   13,   14,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void ui::SearchResultListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SearchResultListWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerSearchFromNet((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<data::SearchResultInfo>(*)>(_a[2]))); break;
        case 1: _t->signalAddContact((*reinterpret_cast< const data::SearchResultInfo(*)>(_a[1]))); break;
        case 2: _t->signalSerAddAppContact((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onSerSearchFromNet((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<data::SearchResultInfo>(*)>(_a[2]))); break;
        case 4: _t->onAddContactBtnClicked((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< void*(*)>(_a[2]))); break;
        case 5: _t->onSerAddAppContact((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SearchResultListWidget::*)(int , std::vector<data::SearchResultInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchResultListWidget::signalSerSearchFromNet)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SearchResultListWidget::*)(const data::SearchResultInfo );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchResultListWidget::signalAddContact)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (SearchResultListWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchResultListWidget::signalSerAddAppContact)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::SearchResultListWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<TWidget::staticMetaObject>(),
    qt_meta_stringdata_ui__SearchResultListWidget.data,
    qt_meta_data_ui__SearchResultListWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::SearchResultListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::SearchResultListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__SearchResultListWidget.stringdata0))
        return static_cast<void*>(this);
    return TWidget::qt_metacast(_clname);
}

int ui::SearchResultListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TWidget::qt_metacall(_c, _id, _a);
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
void ui::SearchResultListWidget::signalSerSearchFromNet(int _t1, std::vector<data::SearchResultInfo> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::SearchResultListWidget::signalAddContact(const data::SearchResultInfo _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::SearchResultListWidget::signalSerAddAppContact(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
