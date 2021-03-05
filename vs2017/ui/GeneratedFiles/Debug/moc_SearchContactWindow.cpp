/****************************************************************************
** Meta object code from reading C++ file 'SearchContactWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/contact/searchcontact/SearchContactWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SearchContactWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__SearchContactWindow_t {
    QByteArrayData data[9];
    char stringdata0[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__SearchContactWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__SearchContactWindow_t qt_meta_stringdata_ui__SearchContactWindow = {
    {
QT_MOC_LITERAL(0, 0, 23), // "ui::SearchContactWindow"
QT_MOC_LITERAL(1, 24, 18), // "onSearchBtnClicked"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 17), // "onLineEditChanged"
QT_MOC_LITERAL(4, 62, 4), // "text"
QT_MOC_LITERAL(5, 67, 20), // "onClearKeyBtnClicked"
QT_MOC_LITERAL(6, 88, 12), // "onAddContact"
QT_MOC_LITERAL(7, 101, 22), // "data::SearchResultInfo"
QT_MOC_LITERAL(8, 124, 4) // "data"

    },
    "ui::SearchContactWindow\0onSearchBtnClicked\0"
    "\0onLineEditChanged\0text\0onClearKeyBtnClicked\0"
    "onAddContact\0data::SearchResultInfo\0"
    "data"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__SearchContactWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   34,    2, 0x09 /* Protected */,
       3,    1,   35,    2, 0x09 /* Protected */,
       5,    0,   38,    2, 0x09 /* Protected */,
       6,    1,   39,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,

       0        // eod
};

void ui::SearchContactWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SearchContactWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onSearchBtnClicked(); break;
        case 1: _t->onLineEditChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->onClearKeyBtnClicked(); break;
        case 3: _t->onAddContact((*reinterpret_cast< const data::SearchResultInfo(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::SearchContactWindow::staticMetaObject = { {
    &BaseDialog::staticMetaObject,
    qt_meta_stringdata_ui__SearchContactWindow.data,
    qt_meta_data_ui__SearchContactWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::SearchContactWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::SearchContactWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__SearchContactWindow.stringdata0))
        return static_cast<void*>(this);
    return BaseDialog::qt_metacast(_clname);
}

int ui::SearchContactWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseDialog::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
