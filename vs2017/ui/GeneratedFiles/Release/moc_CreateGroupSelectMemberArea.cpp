/****************************************************************************
** Meta object code from reading C++ file 'CreateGroupSelectMemberArea.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/contact/createGroup/CreateGroupSelectMemberArea.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'CreateGroupSelectMemberArea.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__CreateGroupSelectMemberArea_t {
    QByteArrayData data[16];
    char stringdata0[239];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__CreateGroupSelectMemberArea_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__CreateGroupSelectMemberArea_t qt_meta_stringdata_ui__CreateGroupSelectMemberArea = {
    {
QT_MOC_LITERAL(0, 0, 31), // "ui::CreateGroupSelectMemberArea"
QT_MOC_LITERAL(1, 32, 11), // "backClicked"
QT_MOC_LITERAL(2, 44, 0), // ""
QT_MOC_LITERAL(3, 45, 8), // "closeWin"
QT_MOC_LITERAL(4, 54, 14), // "selectMemsBack"
QT_MOC_LITERAL(5, 69, 33), // "std::vector<data::UserBasicDa..."
QT_MOC_LITERAL(6, 103, 4), // "mems"
QT_MOC_LITERAL(7, 108, 9), // "startChat"
QT_MOC_LITERAL(8, 118, 27), // "CSharedPtr<data::ChatInfo>&"
QT_MOC_LITERAL(9, 146, 4), // "chat"
QT_MOC_LITERAL(10, 151, 14), // "onBtnOKClicked"
QT_MOC_LITERAL(11, 166, 18), // "onTabCurentChanged"
QT_MOC_LITERAL(12, 185, 5), // "index"
QT_MOC_LITERAL(13, 191, 14), // "onSerHighSerch"
QT_MOC_LITERAL(14, 206, 20), // "onSerHighSerchResult"
QT_MOC_LITERAL(15, 227, 11) // "onStartChat"

    },
    "ui::CreateGroupSelectMemberArea\0"
    "backClicked\0\0closeWin\0selectMemsBack\0"
    "std::vector<data::UserBasicData>&\0"
    "mems\0startChat\0CSharedPtr<data::ChatInfo>&\0"
    "chat\0onBtnOKClicked\0onTabCurentChanged\0"
    "index\0onSerHighSerch\0onSerHighSerchResult\0"
    "onStartChat"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__CreateGroupSelectMemberArea[] = {

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
       1,    0,   59,    2, 0x06 /* Public */,
       3,    0,   60,    2, 0x06 /* Public */,
       4,    1,   61,    2, 0x06 /* Public */,
       7,    1,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      10,    0,   67,    2, 0x09 /* Protected */,
      11,    1,   68,    2, 0x09 /* Protected */,
      13,    0,   71,    2, 0x09 /* Protected */,
      14,    0,   72,    2, 0x09 /* Protected */,
      15,    1,   73,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 8,    9,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,

       0        // eod
};

void ui::CreateGroupSelectMemberArea::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CreateGroupSelectMemberArea *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->backClicked(); break;
        case 1: _t->closeWin(); break;
        case 2: _t->selectMemsBack((*reinterpret_cast< std::vector<data::UserBasicData>(*)>(_a[1]))); break;
        case 3: _t->startChat((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        case 4: _t->onBtnOKClicked(); break;
        case 5: _t->onTabCurentChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->onSerHighSerch(); break;
        case 7: _t->onSerHighSerchResult(); break;
        case 8: _t->onStartChat((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CreateGroupSelectMemberArea::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CreateGroupSelectMemberArea::backClicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (CreateGroupSelectMemberArea::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CreateGroupSelectMemberArea::closeWin)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (CreateGroupSelectMemberArea::*)(std::vector<data::UserBasicData> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CreateGroupSelectMemberArea::selectMemsBack)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (CreateGroupSelectMemberArea::*)(CSharedPtr<data::ChatInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CreateGroupSelectMemberArea::startChat)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::CreateGroupSelectMemberArea::staticMetaObject = { {
    &TWidget::staticMetaObject,
    qt_meta_stringdata_ui__CreateGroupSelectMemberArea.data,
    qt_meta_data_ui__CreateGroupSelectMemberArea,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::CreateGroupSelectMemberArea::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::CreateGroupSelectMemberArea::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__CreateGroupSelectMemberArea.stringdata0))
        return static_cast<void*>(this);
    return TWidget::qt_metacast(_clname);
}

int ui::CreateGroupSelectMemberArea::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TWidget::qt_metacall(_c, _id, _a);
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
void ui::CreateGroupSelectMemberArea::backClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ui::CreateGroupSelectMemberArea::closeWin()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ui::CreateGroupSelectMemberArea::selectMemsBack(std::vector<data::UserBasicData> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ui::CreateGroupSelectMemberArea::startChat(CSharedPtr<data::ChatInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
