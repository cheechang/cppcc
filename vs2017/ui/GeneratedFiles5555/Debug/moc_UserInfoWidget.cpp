/****************************************************************************
** Meta object code from reading C++ file 'UserInfoWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../mainwindow/UserInfoWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UserInfoWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__UserInfoWidget_t {
    QByteArrayData data[13];
    char stringdata0[165];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__UserInfoWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__UserInfoWidget_t qt_meta_stringdata_ui__UserInfoWidget = {
    {
QT_MOC_LITERAL(0, 0, 18), // "ui::UserInfoWidget"
QT_MOC_LITERAL(1, 19, 14), // "signalWinClose"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 11), // "signalOrgID"
QT_MOC_LITERAL(4, 47, 5), // "int64"
QT_MOC_LITERAL(5, 53, 2), // "id"
QT_MOC_LITERAL(6, 56, 18), // "signalUserHeadSucc"
QT_MOC_LITERAL(7, 75, 7), // "headImg"
QT_MOC_LITERAL(8, 83, 21), // "signalEditInfoClicked"
QT_MOC_LITERAL(9, 105, 16), // "onHeadImgClicked"
QT_MOC_LITERAL(10, 122, 14), // "onUserHeadSucc"
QT_MOC_LITERAL(11, 137, 22), // "onUpdateUserInfoResult"
QT_MOC_LITERAL(12, 160, 4) // "code"

    },
    "ui::UserInfoWidget\0signalWinClose\0\0"
    "signalOrgID\0int64\0id\0signalUserHeadSucc\0"
    "headImg\0signalEditInfoClicked\0"
    "onHeadImgClicked\0onUserHeadSucc\0"
    "onUpdateUserInfoResult\0code"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__UserInfoWidget[] = {

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
       1,    0,   49,    2, 0x06 /* Public */,
       3,    1,   50,    2, 0x06 /* Public */,
       6,    1,   53,    2, 0x06 /* Public */,
       8,    0,   56,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   57,    2, 0x0a /* Public */,
      10,    1,   58,    2, 0x0a /* Public */,
      11,    1,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    7,
    QMetaType::Void, QMetaType::Int,   12,

       0        // eod
};

void ui::UserInfoWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UserInfoWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalWinClose(); break;
        case 1: _t->signalOrgID((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 2: _t->signalUserHeadSucc((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->signalEditInfoClicked(); break;
        case 4: _t->onHeadImgClicked(); break;
        case 5: _t->onUserHeadSucc((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->onUpdateUserInfoResult((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (UserInfoWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UserInfoWidget::signalWinClose)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (UserInfoWidget::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UserInfoWidget::signalOrgID)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (UserInfoWidget::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UserInfoWidget::signalUserHeadSucc)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (UserInfoWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UserInfoWidget::signalEditInfoClicked)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::UserInfoWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<BaseDialog::staticMetaObject>(),
    qt_meta_stringdata_ui__UserInfoWidget.data,
    qt_meta_data_ui__UserInfoWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::UserInfoWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::UserInfoWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__UserInfoWidget.stringdata0))
        return static_cast<void*>(this);
    return BaseDialog::qt_metacast(_clname);
}

int ui::UserInfoWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseDialog::qt_metacall(_c, _id, _a);
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
void ui::UserInfoWidget::signalWinClose()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ui::UserInfoWidget::signalOrgID(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::UserInfoWidget::signalUserHeadSucc(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ui::UserInfoWidget::signalEditInfoClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
