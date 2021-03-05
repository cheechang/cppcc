/****************************************************************************
** Meta object code from reading C++ file 'AppInfoWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/contact/friend/AppInfoWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AppInfoWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__AppInfoWidget_t {
    QByteArrayData data[9];
    char stringdata0[117];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__AppInfoWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__AppInfoWidget_t qt_meta_stringdata_ui__AppInfoWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "ui::AppInfoWidget"
QT_MOC_LITERAL(1, 18, 19), // "signalSerGetAppInfo"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 17), // "data::EntAppinfo&"
QT_MOC_LITERAL(4, 57, 15), // "onSerGetAppInfo"
QT_MOC_LITERAL(5, 73, 4), // "code"
QT_MOC_LITERAL(6, 78, 4), // "data"
QT_MOC_LITERAL(7, 83, 13), // "slotStartChat"
QT_MOC_LITERAL(8, 97, 19) // "onBtnViewHistoryMsg"

    },
    "ui::AppInfoWidget\0signalSerGetAppInfo\0"
    "\0data::EntAppinfo&\0onSerGetAppInfo\0"
    "code\0data\0slotStartChat\0onBtnViewHistoryMsg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__AppInfoWidget[] = {

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
       1,    2,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    2,   39,    2, 0x09 /* Protected */,
       7,    0,   44,    2, 0x09 /* Protected */,
       8,    0,   45,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3,    5,    6,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ui::AppInfoWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AppInfoWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerGetAppInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::EntAppinfo(*)>(_a[2]))); break;
        case 1: _t->onSerGetAppInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::EntAppinfo(*)>(_a[2]))); break;
        case 2: _t->slotStartChat(); break;
        case 3: _t->onBtnViewHistoryMsg(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AppInfoWidget::*)(int , data::EntAppinfo & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppInfoWidget::signalSerGetAppInfo)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::AppInfoWidget::staticMetaObject = { {
    &EnterpriseInfoWidget::staticMetaObject,
    qt_meta_stringdata_ui__AppInfoWidget.data,
    qt_meta_data_ui__AppInfoWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::AppInfoWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::AppInfoWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__AppInfoWidget.stringdata0))
        return static_cast<void*>(this);
    return EnterpriseInfoWidget::qt_metacast(_clname);
}

int ui::AppInfoWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = EnterpriseInfoWidget::qt_metacall(_c, _id, _a);
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
void ui::AppInfoWidget::signalSerGetAppInfo(int _t1, data::EntAppinfo & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
