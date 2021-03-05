/****************************************************************************
** Meta object code from reading C++ file 'SearchResultListWidgetItem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/contact/searchcontact/SearchResultListWidgetItem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SearchResultListWidgetItem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__SearchResultListWidgetItem_t {
    QByteArrayData data[7];
    char stringdata0[101];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__SearchResultListWidgetItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__SearchResultListWidgetItem_t qt_meta_stringdata_ui__SearchResultListWidgetItem = {
    {
QT_MOC_LITERAL(0, 0, 30), // "ui::SearchResultListWidgetItem"
QT_MOC_LITERAL(1, 31, 26), // "signalAddContactBtnClicked"
QT_MOC_LITERAL(2, 58, 0), // ""
QT_MOC_LITERAL(3, 59, 5), // "int64"
QT_MOC_LITERAL(4, 65, 8), // "targetId"
QT_MOC_LITERAL(5, 74, 10), // "itemWidget"
QT_MOC_LITERAL(6, 85, 15) // "onAddBtnClicked"

    },
    "ui::SearchResultListWidgetItem\0"
    "signalAddContactBtnClicked\0\0int64\0"
    "targetId\0itemWidget\0onAddBtnClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__SearchResultListWidgetItem[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   29,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::VoidStar,    4,    5,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void ui::SearchResultListWidgetItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SearchResultListWidgetItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalAddContactBtnClicked((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< void*(*)>(_a[2]))); break;
        case 1: _t->onAddBtnClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SearchResultListWidgetItem::*)(int64 , void * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SearchResultListWidgetItem::signalAddContactBtnClicked)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::SearchResultListWidgetItem::staticMetaObject = { {
    &TWidget::staticMetaObject,
    qt_meta_stringdata_ui__SearchResultListWidgetItem.data,
    qt_meta_data_ui__SearchResultListWidgetItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::SearchResultListWidgetItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::SearchResultListWidgetItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__SearchResultListWidgetItem.stringdata0))
        return static_cast<void*>(this);
    return TWidget::qt_metacast(_clname);
}

int ui::SearchResultListWidgetItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ui::SearchResultListWidgetItem::signalAddContactBtnClicked(int64 _t1, void * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
