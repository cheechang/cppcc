/****************************************************************************
** Meta object code from reading C++ file 'enterpriseinfowidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/enterprise/enterpriseinfowidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'enterpriseinfowidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__UserExtendInfoWidgetItem_t {
    QByteArrayData data[1];
    char stringdata0[29];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__UserExtendInfoWidgetItem_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__UserExtendInfoWidgetItem_t qt_meta_stringdata_ui__UserExtendInfoWidgetItem = {
    {
QT_MOC_LITERAL(0, 0, 28) // "ui::UserExtendInfoWidgetItem"

    },
    "ui::UserExtendInfoWidgetItem"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__UserExtendInfoWidgetItem[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void ui::UserExtendInfoWidgetItem::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ui::UserExtendInfoWidgetItem::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ui__UserExtendInfoWidgetItem.data,
    qt_meta_data_ui__UserExtendInfoWidgetItem,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::UserExtendInfoWidgetItem::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::UserExtendInfoWidgetItem::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__UserExtendInfoWidgetItem.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ui::UserExtendInfoWidgetItem::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_ui__EnterpriseInfoWidget_t {
    QByteArrayData data[18];
    char stringdata0[311];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__EnterpriseInfoWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__EnterpriseInfoWidget_t qt_meta_stringdata_ui__EnterpriseInfoWidget = {
    {
QT_MOC_LITERAL(0, 0, 24), // "ui::EnterpriseInfoWidget"
QT_MOC_LITERAL(1, 25, 9), // "startChat"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 27), // "CSharedPtr<data::ChatInfo>&"
QT_MOC_LITERAL(4, 64, 4), // "chat"
QT_MOC_LITERAL(5, 69, 26), // "signalSerGetUserExtendInfo"
QT_MOC_LITERAL(6, 96, 5), // "int64"
QT_MOC_LITERAL(7, 102, 6), // "userId"
QT_MOC_LITERAL(8, 109, 40), // "std::vector<data::EnterpriseD..."
QT_MOC_LITERAL(9, 150, 21), // "signalSerShowMoreInfo"
QT_MOC_LITERAL(10, 172, 20), // "signalSerGetUserInfo"
QT_MOC_LITERAL(11, 193, 15), // "data::UserData&"
QT_MOC_LITERAL(12, 209, 13), // "slotStartChat"
QT_MOC_LITERAL(13, 223, 20), // "onBtnViewExtendsInfo"
QT_MOC_LITERAL(14, 244, 20), // "onBtnBackToBasicInfo"
QT_MOC_LITERAL(15, 265, 22), // "onSerGetUserExtendInfo"
QT_MOC_LITERAL(16, 288, 5), // "infos"
QT_MOC_LITERAL(17, 294, 16) // "onSerGetUserInfo"

    },
    "ui::EnterpriseInfoWidget\0startChat\0\0"
    "CSharedPtr<data::ChatInfo>&\0chat\0"
    "signalSerGetUserExtendInfo\0int64\0"
    "userId\0std::vector<data::EnterpriseDictionary>&\0"
    "signalSerShowMoreInfo\0signalSerGetUserInfo\0"
    "data::UserData&\0slotStartChat\0"
    "onBtnViewExtendsInfo\0onBtnBackToBasicInfo\0"
    "onSerGetUserExtendInfo\0infos\0"
    "onSerGetUserInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__EnterpriseInfoWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       5,    2,   62,    2, 0x06 /* Public */,
       9,    0,   67,    2, 0x06 /* Public */,
      10,    2,   68,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,   73,    2, 0x09 /* Protected */,
      13,    0,   74,    2, 0x09 /* Protected */,
      14,    0,   75,    2, 0x09 /* Protected */,
      15,    2,   76,    2, 0x09 /* Protected */,
      17,    2,   81,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 8,    7,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 11,    2,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 8,    7,   16,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 11,    2,    2,

       0        // eod
};

void ui::EnterpriseInfoWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<EnterpriseInfoWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startChat((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        case 1: _t->signalSerGetUserExtendInfo((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< std::vector<data::EnterpriseDictionary>(*)>(_a[2]))); break;
        case 2: _t->signalSerShowMoreInfo(); break;
        case 3: _t->signalSerGetUserInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::UserData(*)>(_a[2]))); break;
        case 4: _t->slotStartChat(); break;
        case 5: _t->onBtnViewExtendsInfo(); break;
        case 6: _t->onBtnBackToBasicInfo(); break;
        case 7: _t->onSerGetUserExtendInfo((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< std::vector<data::EnterpriseDictionary>(*)>(_a[2]))); break;
        case 8: _t->onSerGetUserInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< data::UserData(*)>(_a[2]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (EnterpriseInfoWidget::*)(CSharedPtr<data::ChatInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EnterpriseInfoWidget::startChat)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (EnterpriseInfoWidget::*)(int64 , std::vector<data::EnterpriseDictionary> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EnterpriseInfoWidget::signalSerGetUserExtendInfo)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (EnterpriseInfoWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EnterpriseInfoWidget::signalSerShowMoreInfo)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (EnterpriseInfoWidget::*)(int , data::UserData & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&EnterpriseInfoWidget::signalSerGetUserInfo)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::EnterpriseInfoWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ui__EnterpriseInfoWidget.data,
    qt_meta_data_ui__EnterpriseInfoWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::EnterpriseInfoWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::EnterpriseInfoWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__EnterpriseInfoWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ui::EnterpriseInfoWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void ui::EnterpriseInfoWidget::startChat(CSharedPtr<data::ChatInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::EnterpriseInfoWidget::signalSerGetUserExtendInfo(int64 _t1, std::vector<data::EnterpriseDictionary> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::EnterpriseInfoWidget::signalSerShowMoreInfo()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ui::EnterpriseInfoWidget::signalSerGetUserInfo(int _t1, data::UserData & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
