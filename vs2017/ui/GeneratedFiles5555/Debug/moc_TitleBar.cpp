/****************************************************************************
** Meta object code from reading C++ file 'TitleBar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../controls/TitleBar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'TitleBar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_uicontrols__TitleBar_t {
    QByteArrayData data[10];
    char stringdata0[133];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_uicontrols__TitleBar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_uicontrols__TitleBar_t qt_meta_stringdata_uicontrols__TitleBar = {
    {
QT_MOC_LITERAL(0, 0, 20), // "uicontrols::TitleBar"
QT_MOC_LITERAL(1, 21, 9), // "signalMin"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 9), // "signalMax"
QT_MOC_LITERAL(4, 42, 11), // "signalClose"
QT_MOC_LITERAL(5, 54, 21), // "signalMaxStateChanged"
QT_MOC_LITERAL(6, 76, 5), // "isMax"
QT_MOC_LITERAL(7, 82, 23), // "signalWindowSizeChanged"
QT_MOC_LITERAL(8, 106, 16), // "signalAdvanceSet"
QT_MOC_LITERAL(9, 123, 9) // "onClicked"

    },
    "uicontrols::TitleBar\0signalMin\0\0"
    "signalMax\0signalClose\0signalMaxStateChanged\0"
    "isMax\0signalWindowSizeChanged\0"
    "signalAdvanceSet\0onClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_uicontrols__TitleBar[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    0,   51,    2, 0x06 /* Public */,
       5,    1,   52,    2, 0x06 /* Public */,
       7,    0,   55,    2, 0x06 /* Public */,
       8,    0,   56,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   57,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    6,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void uicontrols::TitleBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<TitleBar *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalMin(); break;
        case 1: _t->signalMax(); break;
        case 2: _t->signalClose(); break;
        case 3: _t->signalMaxStateChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->signalWindowSizeChanged(); break;
        case 5: _t->signalAdvanceSet(); break;
        case 6: _t->onClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (TitleBar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TitleBar::signalMin)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (TitleBar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TitleBar::signalMax)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (TitleBar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TitleBar::signalClose)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (TitleBar::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TitleBar::signalMaxStateChanged)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (TitleBar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TitleBar::signalWindowSizeChanged)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (TitleBar::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&TitleBar::signalAdvanceSet)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject uicontrols::TitleBar::staticMetaObject = { {
    QMetaObject::SuperData::link<ui::TWidget::staticMetaObject>(),
    qt_meta_stringdata_uicontrols__TitleBar.data,
    qt_meta_data_uicontrols__TitleBar,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *uicontrols::TitleBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *uicontrols::TitleBar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_uicontrols__TitleBar.stringdata0))
        return static_cast<void*>(this);
    return ui::TWidget::qt_metacast(_clname);
}

int uicontrols::TitleBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ui::TWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void uicontrols::TitleBar::signalMin()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void uicontrols::TitleBar::signalMax()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void uicontrols::TitleBar::signalClose()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void uicontrols::TitleBar::signalMaxStateChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void uicontrols::TitleBar::signalWindowSizeChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void uicontrols::TitleBar::signalAdvanceSet()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
