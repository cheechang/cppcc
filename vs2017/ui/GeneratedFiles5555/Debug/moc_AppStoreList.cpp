/****************************************************************************
** Meta object code from reading C++ file 'AppStoreList.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../mainwindow/workbench/AppStoreList.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AppStoreList.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__AppStoreList_t {
    QByteArrayData data[16];
    char stringdata0[190];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__AppStoreList_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__AppStoreList_t qt_meta_stringdata_ui__AppStoreList = {
    {
QT_MOC_LITERAL(0, 0, 16), // "ui::AppStoreList"
QT_MOC_LITERAL(1, 17, 23), // "signalSerGetApplication"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 26), // "std::vector<data::AppInfo>"
QT_MOC_LITERAL(4, 69, 8), // "openLink"
QT_MOC_LITERAL(5, 78, 10), // "installApp"
QT_MOC_LITERAL(6, 89, 5), // "int64"
QT_MOC_LITERAL(7, 95, 12), // "uninstallApp"
QT_MOC_LITERAL(8, 108, 19), // "onSerGetApplication"
QT_MOC_LITERAL(9, 128, 3), // "vec"
QT_MOC_LITERAL(10, 132, 12), // "onInstallApp"
QT_MOC_LITERAL(11, 145, 6), // "iAppID"
QT_MOC_LITERAL(12, 152, 7), // "strName"
QT_MOC_LITERAL(13, 160, 7), // "strIcon"
QT_MOC_LITERAL(14, 168, 6), // "strUrl"
QT_MOC_LITERAL(15, 175, 14) // "onUninstallApp"

    },
    "ui::AppStoreList\0signalSerGetApplication\0"
    "\0std::vector<data::AppInfo>\0openLink\0"
    "installApp\0int64\0uninstallApp\0"
    "onSerGetApplication\0vec\0onInstallApp\0"
    "iAppID\0strName\0strIcon\0strUrl\0"
    "onUninstallApp"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__AppStoreList[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       4,    1,   52,    2, 0x06 /* Public */,
       5,    4,   55,    2, 0x06 /* Public */,
       7,    1,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    1,   67,    2, 0x0a /* Public */,
      10,    4,   70,    2, 0x0a /* Public */,
      15,    1,   79,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 6, QMetaType::QString, QMetaType::QString, QMetaType::QString,    2,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 6,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    9,
    QMetaType::Void, 0x80000000 | 6, QMetaType::QString, QMetaType::QString, QMetaType::QString,   11,   12,   13,   14,
    QMetaType::Void, 0x80000000 | 6,   11,

       0        // eod
};

void ui::AppStoreList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AppStoreList *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerGetApplication((*reinterpret_cast< std::vector<data::AppInfo>(*)>(_a[1]))); break;
        case 1: _t->openLink((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->installApp((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 3: _t->uninstallApp((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 4: _t->onSerGetApplication((*reinterpret_cast< std::vector<data::AppInfo>(*)>(_a[1]))); break;
        case 5: _t->onInstallApp((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 6: _t->onUninstallApp((*reinterpret_cast< int64(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (AppStoreList::*)(std::vector<data::AppInfo> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppStoreList::signalSerGetApplication)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (AppStoreList::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppStoreList::openLink)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (AppStoreList::*)(int64 , QString , QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppStoreList::installApp)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (AppStoreList::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&AppStoreList::uninstallApp)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::AppStoreList::staticMetaObject = { {
    QMetaObject::SuperData::link<QListWidget::staticMetaObject>(),
    qt_meta_stringdata_ui__AppStoreList.data,
    qt_meta_data_ui__AppStoreList,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::AppStoreList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::AppStoreList::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__AppStoreList.stringdata0))
        return static_cast<void*>(this);
    return QListWidget::qt_metacast(_clname);
}

int ui::AppStoreList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QListWidget::qt_metacall(_c, _id, _a);
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
void ui::AppStoreList::signalSerGetApplication(std::vector<data::AppInfo> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::AppStoreList::openLink(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::AppStoreList::installApp(int64 _t1, QString _t2, QString _t3, QString _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t3))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t4))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ui::AppStoreList::uninstallApp(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
