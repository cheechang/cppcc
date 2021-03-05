/****************************************************************************
** Meta object code from reading C++ file 'AppStoreListItem.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/workbench/AppStoreListItem.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AppStoreListItem.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__AppStoreListItem_t {
    QByteArrayData data[9];
    char stringdata0[129];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__AppStoreListItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__AppStoreListItem_t qt_meta_stringdata_ui__AppStoreListItem = {
    {
QT_MOC_LITERAL(0, 0, 20), // "ui::AppStoreListItem"
QT_MOC_LITERAL(1, 21, 31), // "signalSerAddOrDeleteApplication"
QT_MOC_LITERAL(2, 53, 0), // ""
QT_MOC_LITERAL(3, 54, 10), // "installApp"
QT_MOC_LITERAL(4, 65, 5), // "int64"
QT_MOC_LITERAL(5, 71, 12), // "uninstallApp"
QT_MOC_LITERAL(6, 84, 27), // "onSerAddOrDeleteApplication"
QT_MOC_LITERAL(7, 112, 3), // "err"
QT_MOC_LITERAL(8, 116, 12) // "onBtnClicked"

    },
    "ui::AppStoreListItem\0"
    "signalSerAddOrDeleteApplication\0\0"
    "installApp\0int64\0uninstallApp\0"
    "onSerAddOrDeleteApplication\0err\0"
    "onBtnClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__AppStoreListItem[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       3,    4,   42,    2, 0x06 /* Public */,
       5,    1,   51,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   54,    2, 0x0a /* Public */,
       8,    0,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 4, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 4,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,

       0        // eod
};

void ui::AppStoreListItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AppStoreListItem *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerAddOrDeleteApplication((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->installApp((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 2: _t->uninstallApp((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 3: _t->onSerAddOrDeleteApplication((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->onBtnClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AppStoreListItem::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppStoreListItem::signalSerAddOrDeleteApplication)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AppStoreListItem::*)(int64 , QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppStoreListItem::installApp)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AppStoreListItem::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppStoreListItem::uninstallApp)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::AppStoreListItem::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ui__AppStoreListItem.data,
    qt_meta_data_ui__AppStoreListItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::AppStoreListItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::AppStoreListItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__AppStoreListItem.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ui::AppStoreListItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ui::AppStoreListItem::signalSerAddOrDeleteApplication(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::AppStoreListItem::installApp(int64 _t1, QString _t2, QString _t3, QString _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::AppStoreListItem::uninstallApp(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
