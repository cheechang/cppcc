/****************************************************************************
** Meta object code from reading C++ file 'AppList.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/workbench/AppList.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AppList.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__AppList_t {
    QByteArrayData data[18];
    char stringdata0[210];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__AppList_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__AppList_t qt_meta_stringdata_ui__AppList = {
    {
QT_MOC_LITERAL(0, 0, 11), // "ui::AppList"
QT_MOC_LITERAL(1, 12, 23), // "signalSerGetApplication"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 26), // "std::vector<data::AppInfo>"
QT_MOC_LITERAL(4, 64, 8), // "openLink"
QT_MOC_LITERAL(5, 73, 19), // "onSerGetApplication"
QT_MOC_LITERAL(6, 93, 3), // "vec"
QT_MOC_LITERAL(7, 97, 20), // "onCurrentItemChanged"
QT_MOC_LITERAL(8, 118, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(9, 135, 4), // "item"
QT_MOC_LITERAL(10, 140, 12), // "onInstallApp"
QT_MOC_LITERAL(11, 153, 5), // "int64"
QT_MOC_LITERAL(12, 159, 6), // "iAppID"
QT_MOC_LITERAL(13, 166, 7), // "strName"
QT_MOC_LITERAL(14, 174, 7), // "strIcon"
QT_MOC_LITERAL(15, 182, 6), // "strUrl"
QT_MOC_LITERAL(16, 189, 14), // "onUninstallApp"
QT_MOC_LITERAL(17, 204, 5) // "appID"

    },
    "ui::AppList\0signalSerGetApplication\0"
    "\0std::vector<data::AppInfo>\0openLink\0"
    "onSerGetApplication\0vec\0onCurrentItemChanged\0"
    "QListWidgetItem*\0item\0onInstallApp\0"
    "int64\0iAppID\0strName\0strIcon\0strUrl\0"
    "onUninstallApp\0appID"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__AppList[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   50,    2, 0x0a /* Public */,
       7,    1,   53,    2, 0x0a /* Public */,
      10,    4,   56,    2, 0x0a /* Public */,
      16,    1,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    6,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 11, QMetaType::QString, QMetaType::QString, QMetaType::QString,   12,   13,   14,   15,
    QMetaType::Void, 0x80000000 | 11,   17,

       0        // eod
};

void ui::AppList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AppList *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerGetApplication((*reinterpret_cast< std::vector<data::AppInfo>(*)>(_a[1]))); break;
        case 1: _t->openLink((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->onSerGetApplication((*reinterpret_cast< std::vector<data::AppInfo>(*)>(_a[1]))); break;
        case 3: _t->onCurrentItemChanged((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->onInstallApp((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 5: _t->onUninstallApp((*reinterpret_cast< int64(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AppList::*)(std::vector<data::AppInfo> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppList::signalSerGetApplication)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AppList::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppList::openLink)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::AppList::staticMetaObject = { {
    &QListWidget::staticMetaObject,
    qt_meta_stringdata_ui__AppList.data,
    qt_meta_data_ui__AppList,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::AppList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::AppList::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__AppList.stringdata0))
        return static_cast<void*>(this);
    return QListWidget::qt_metacast(_clname);
}

int ui::AppList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
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
void ui::AppList::signalSerGetApplication(std::vector<data::AppInfo> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::AppList::openLink(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
