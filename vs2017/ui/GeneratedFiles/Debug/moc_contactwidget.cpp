/****************************************************************************
** Meta object code from reading C++ file 'contactwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/contact/contactwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'contactwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__ContactWidget_t {
    QByteArrayData data[22];
    char stringdata0[316];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__ContactWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__ContactWidget_t qt_meta_stringdata_ui__ContactWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "ui::ContactWidget"
QT_MOC_LITERAL(1, 18, 9), // "startChat"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 27), // "CSharedPtr<data::ChatInfo>&"
QT_MOC_LITERAL(4, 57, 4), // "chat"
QT_MOC_LITERAL(5, 62, 18), // "signalSerDelUiFile"
QT_MOC_LITERAL(6, 81, 5), // "int64"
QT_MOC_LITERAL(7, 87, 21), // "onShowOrgUserInfoPage"
QT_MOC_LITERAL(8, 109, 20), // "data::OrgAndUserInfo"
QT_MOC_LITERAL(9, 130, 4), // "user"
QT_MOC_LITERAL(10, 135, 20), // "onShowGroupInforPage"
QT_MOC_LITERAL(11, 156, 7), // "groupId"
QT_MOC_LITERAL(12, 164, 21), // "onShowContactInfoPage"
QT_MOC_LITERAL(13, 186, 13), // "data::Contact"
QT_MOC_LITERAL(14, 200, 7), // "contact"
QT_MOC_LITERAL(15, 208, 29), // "onShowAddContactOrCreateGroup"
QT_MOC_LITERAL(16, 238, 4), // "type"
QT_MOC_LITERAL(17, 243, 15), // "onBtnAddClicked"
QT_MOC_LITERAL(18, 259, 16), // "onBtnCreateGroup"
QT_MOC_LITERAL(19, 276, 20), // "onBtnAddFrindOrGroup"
QT_MOC_LITERAL(20, 297, 14), // "onShowUserInfo"
QT_MOC_LITERAL(21, 312, 3) // "uid"

    },
    "ui::ContactWidget\0startChat\0\0"
    "CSharedPtr<data::ChatInfo>&\0chat\0"
    "signalSerDelUiFile\0int64\0onShowOrgUserInfoPage\0"
    "data::OrgAndUserInfo\0user\0"
    "onShowGroupInforPage\0groupId\0"
    "onShowContactInfoPage\0data::Contact\0"
    "contact\0onShowAddContactOrCreateGroup\0"
    "type\0onBtnAddClicked\0onBtnCreateGroup\0"
    "onBtnAddFrindOrGroup\0onShowUserInfo\0"
    "uid"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__ContactWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       5,    2,   67,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   72,    2, 0x09 /* Protected */,
      10,    1,   75,    2, 0x09 /* Protected */,
      12,    1,   78,    2, 0x09 /* Protected */,
      15,    1,   81,    2, 0x09 /* Protected */,
      17,    0,   84,    2, 0x09 /* Protected */,
      18,    0,   85,    2, 0x09 /* Protected */,
      19,    0,   86,    2, 0x09 /* Protected */,
      20,    1,   87,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 6,    2,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 6,   11,
    QMetaType::Void, 0x80000000 | 13,   14,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,   21,

       0        // eod
};

void ui::ContactWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ContactWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startChat((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        case 1: _t->signalSerDelUiFile((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2]))); break;
        case 2: _t->onShowOrgUserInfoPage((*reinterpret_cast< data::OrgAndUserInfo(*)>(_a[1]))); break;
        case 3: _t->onShowGroupInforPage((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 4: _t->onShowContactInfoPage((*reinterpret_cast< data::Contact(*)>(_a[1]))); break;
        case 5: _t->onShowAddContactOrCreateGroup((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->onBtnAddClicked(); break;
        case 7: _t->onBtnCreateGroup(); break;
        case 8: _t->onBtnAddFrindOrGroup(); break;
        case 9: _t->onShowUserInfo((*reinterpret_cast< int64(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ContactWidget::*)(CSharedPtr<data::ChatInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContactWidget::startChat)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ContactWidget::*)(int64 , int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ContactWidget::signalSerDelUiFile)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::ContactWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_ui__ContactWidget.data,
    qt_meta_data_ui__ContactWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::ContactWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::ContactWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__ContactWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ui::ContactWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ui::ContactWidget::startChat(CSharedPtr<data::ChatInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::ContactWidget::signalSerDelUiFile(int64 _t1, int64 _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
