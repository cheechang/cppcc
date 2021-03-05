/****************************************************************************
** Meta object code from reading C++ file 'LocalSearchListWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/contact/localsearch/LocalSearchListWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LocalSearchListWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__LocalSearchListWidget_t {
    QByteArrayData data[21];
    char stringdata0[292];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__LocalSearchListWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__LocalSearchListWidget_t qt_meta_stringdata_ui__LocalSearchListWidget = {
    {
QT_MOC_LITERAL(0, 0, 25), // "ui::LocalSearchListWidget"
QT_MOC_LITERAL(1, 26, 24), // "signalSerSearchFromLocal"
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 28), // "std::vector<data::ChatInfo>&"
QT_MOC_LITERAL(4, 81, 9), // "startChat"
QT_MOC_LITERAL(5, 91, 27), // "CSharedPtr<data::ChatInfo>&"
QT_MOC_LITERAL(6, 119, 4), // "chat"
QT_MOC_LITERAL(7, 124, 19), // "hideLocalSearchList"
QT_MOC_LITERAL(8, 144, 20), // "onSerSearchFromLocal"
QT_MOC_LITERAL(9, 165, 4), // "code"
QT_MOC_LITERAL(10, 170, 4), // "list"
QT_MOC_LITERAL(11, 175, 13), // "onHeadClicked"
QT_MOC_LITERAL(12, 189, 5), // "int64"
QT_MOC_LITERAL(13, 195, 2), // "id"
QT_MOC_LITERAL(14, 198, 12), // "resetTipItem"
QT_MOC_LITERAL(15, 211, 19), // "onItemDoubleClicked"
QT_MOC_LITERAL(16, 231, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(17, 248, 4), // "item"
QT_MOC_LITERAL(18, 253, 13), // "onItemClicked"
QT_MOC_LITERAL(19, 267, 15), // "onInfoStartChat"
QT_MOC_LITERAL(20, 283, 8) // "chatInfo"

    },
    "ui::LocalSearchListWidget\0"
    "signalSerSearchFromLocal\0\0"
    "std::vector<data::ChatInfo>&\0startChat\0"
    "CSharedPtr<data::ChatInfo>&\0chat\0"
    "hideLocalSearchList\0onSerSearchFromLocal\0"
    "code\0list\0onHeadClicked\0int64\0id\0"
    "resetTipItem\0onItemDoubleClicked\0"
    "QListWidgetItem*\0item\0onItemClicked\0"
    "onInfoStartChat\0chatInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__LocalSearchListWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   64,    2, 0x06 /* Public */,
       4,    1,   69,    2, 0x06 /* Public */,
       7,    0,   72,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    2,   73,    2, 0x09 /* Protected */,
      11,    1,   78,    2, 0x09 /* Protected */,
      14,    0,   81,    2, 0x09 /* Protected */,
      15,    1,   82,    2, 0x09 /* Protected */,
      18,    1,   85,    2, 0x09 /* Protected */,
       4,    1,   88,    2, 0x09 /* Protected */,
      19,    1,   91,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3,    2,    2,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3,    9,   10,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 16,    2,
    QMetaType::Void, 0x80000000 | 16,   17,
    QMetaType::Void, 0x80000000 | 5,   20,

       0        // eod
};

void ui::LocalSearchListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LocalSearchListWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerSearchFromLocal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<data::ChatInfo>(*)>(_a[2]))); break;
        case 1: _t->startChat((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        case 2: _t->hideLocalSearchList(); break;
        case 3: _t->onSerSearchFromLocal((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<data::ChatInfo>(*)>(_a[2]))); break;
        case 4: _t->onHeadClicked((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 5: _t->resetTipItem(); break;
        case 6: _t->onItemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 7: _t->onItemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 8: _t->startChat((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 9: _t->onInfoStartChat((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (LocalSearchListWidget::*)(int , std::vector<data::ChatInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LocalSearchListWidget::signalSerSearchFromLocal)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (LocalSearchListWidget::*)(CSharedPtr<data::ChatInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LocalSearchListWidget::startChat)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (LocalSearchListWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&LocalSearchListWidget::hideLocalSearchList)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::LocalSearchListWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ui__LocalSearchListWidget.data,
    qt_meta_data_ui__LocalSearchListWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::LocalSearchListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::LocalSearchListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__LocalSearchListWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ui::LocalSearchListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void ui::LocalSearchListWidget::signalSerSearchFromLocal(int _t1, std::vector<data::ChatInfo> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::LocalSearchListWidget::startChat(CSharedPtr<data::ChatInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::LocalSearchListWidget::hideLocalSearchList()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
