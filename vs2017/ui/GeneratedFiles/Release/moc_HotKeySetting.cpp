/****************************************************************************
** Meta object code from reading C++ file 'HotKeySetting.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/systemsetting/HotKeySetting.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HotKeySetting.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__HotKeySetting_t {
    QByteArrayData data[15];
    char stringdata0[214];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__HotKeySetting_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__HotKeySetting_t qt_meta_stringdata_ui__HotKeySetting = {
    {
QT_MOC_LITERAL(0, 0, 17), // "ui::HotKeySetting"
QT_MOC_LITERAL(1, 18, 19), // "signalSendMsgHotKey"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 3), // "key"
QT_MOC_LITERAL(4, 43, 19), // "signalHotKeySetting"
QT_MOC_LITERAL(5, 63, 5), // "scren"
QT_MOC_LITERAL(6, 69, 3), // "msg"
QT_MOC_LITERAL(7, 73, 14), // "signalCloseWin"
QT_MOC_LITERAL(8, 88, 20), // "onRadioButtonClicked"
QT_MOC_LITERAL(9, 109, 23), // "onDefaultSettingClicekd"
QT_MOC_LITERAL(10, 133, 14), // "onOKBtnClicked"
QT_MOC_LITERAL(11, 148, 18), // "onCancelBtnClicked"
QT_MOC_LITERAL(12, 167, 15), // "showConflictErr"
QT_MOC_LITERAL(13, 183, 11), // "hasConfilct"
QT_MOC_LITERAL(14, 195, 18) // "onSetHotKeySuccess"

    },
    "ui::HotKeySetting\0signalSendMsgHotKey\0"
    "\0key\0signalHotKeySetting\0scren\0msg\0"
    "signalCloseWin\0onRadioButtonClicked\0"
    "onDefaultSettingClicekd\0onOKBtnClicked\0"
    "onCancelBtnClicked\0showConflictErr\0"
    "hasConfilct\0onSetHotKeySuccess"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__HotKeySetting[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       4,    2,   62,    2, 0x06 /* Public */,
       7,    0,   67,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       8,    0,   68,    2, 0x0a /* Public */,
       9,    0,   69,    2, 0x0a /* Public */,
      10,    0,   70,    2, 0x0a /* Public */,
      11,    0,   71,    2, 0x0a /* Public */,
      12,    1,   72,    2, 0x0a /* Public */,
      14,    0,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,    6,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void,

       0        // eod
};

void ui::HotKeySetting::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HotKeySetting *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSendMsgHotKey((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->signalHotKeySetting((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->signalCloseWin(); break;
        case 3: _t->onRadioButtonClicked(); break;
        case 4: _t->onDefaultSettingClicekd(); break;
        case 5: _t->onOKBtnClicked(); break;
        case 6: _t->onCancelBtnClicked(); break;
        case 7: _t->showConflictErr((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->onSetHotKeySuccess(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (HotKeySetting::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HotKeySetting::signalSendMsgHotKey)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (HotKeySetting::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HotKeySetting::signalHotKeySetting)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (HotKeySetting::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&HotKeySetting::signalCloseWin)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::HotKeySetting::staticMetaObject = { {
    &TWidget::staticMetaObject,
    qt_meta_stringdata_ui__HotKeySetting.data,
    qt_meta_data_ui__HotKeySetting,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::HotKeySetting::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::HotKeySetting::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__HotKeySetting.stringdata0))
        return static_cast<void*>(this);
    return TWidget::qt_metacast(_clname);
}

int ui::HotKeySetting::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ui::HotKeySetting::signalSendMsgHotKey(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::HotKeySetting::signalHotKeySetting(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::HotKeySetting::signalCloseWin()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
