/****************************************************************************
** Meta object code from reading C++ file 'SuggestionFeedbackSend.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/suggestion/SuggestionFeedbackSend.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'SuggestionFeedbackSend.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__SuggestionFeedbackSendDialog_t {
    QByteArrayData data[12];
    char stringdata0[222];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__SuggestionFeedbackSendDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__SuggestionFeedbackSendDialog_t qt_meta_stringdata_ui__SuggestionFeedbackSendDialog = {
    {
QT_MOC_LITERAL(0, 0, 32), // "ui::SuggestionFeedbackSendDialog"
QT_MOC_LITERAL(1, 33, 27), // "signalSerGetLocalFriendInfo"
QT_MOC_LITERAL(2, 61, 0), // ""
QT_MOC_LITERAL(3, 62, 28), // "std::vector<data::ChatInfo>&"
QT_MOC_LITERAL(4, 91, 9), // "startChat"
QT_MOC_LITERAL(5, 101, 27), // "CSharedPtr<data::ChatInfo>&"
QT_MOC_LITERAL(6, 129, 11), // "onEditClear"
QT_MOC_LITERAL(7, 141, 14), // "onSearchFriend"
QT_MOC_LITERAL(8, 156, 23), // "onSerGetLocalFriendInfo"
QT_MOC_LITERAL(9, 180, 19), // "onItemDoubleClicked"
QT_MOC_LITERAL(10, 200, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(11, 217, 4) // "item"

    },
    "ui::SuggestionFeedbackSendDialog\0"
    "signalSerGetLocalFriendInfo\0\0"
    "std::vector<data::ChatInfo>&\0startChat\0"
    "CSharedPtr<data::ChatInfo>&\0onEditClear\0"
    "onSearchFriend\0onSerGetLocalFriendInfo\0"
    "onItemDoubleClicked\0QListWidgetItem*\0"
    "item"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__SuggestionFeedbackSendDialog[] = {

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
       1,    2,   44,    2, 0x06 /* Public */,
       4,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   52,    2, 0x0a /* Public */,
       7,    1,   53,    2, 0x0a /* Public */,
       8,    2,   56,    2, 0x0a /* Public */,
       9,    1,   61,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3,    2,    2,
    QMetaType::Void, 0x80000000 | 5,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 3,    2,    2,
    QMetaType::Void, 0x80000000 | 10,   11,

       0        // eod
};

void ui::SuggestionFeedbackSendDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SuggestionFeedbackSendDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSerGetLocalFriendInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<data::ChatInfo>(*)>(_a[2]))); break;
        case 1: _t->startChat((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        case 2: _t->onEditClear(); break;
        case 3: _t->onSearchFriend((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->onSerGetLocalFriendInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<data::ChatInfo>(*)>(_a[2]))); break;
        case 5: _t->onItemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SuggestionFeedbackSendDialog::*)(int , std::vector<data::ChatInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SuggestionFeedbackSendDialog::signalSerGetLocalFriendInfo)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SuggestionFeedbackSendDialog::*)(CSharedPtr<data::ChatInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SuggestionFeedbackSendDialog::startChat)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::SuggestionFeedbackSendDialog::staticMetaObject = { {
    &BaseWindow::staticMetaObject,
    qt_meta_stringdata_ui__SuggestionFeedbackSendDialog.data,
    qt_meta_data_ui__SuggestionFeedbackSendDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::SuggestionFeedbackSendDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::SuggestionFeedbackSendDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__SuggestionFeedbackSendDialog.stringdata0))
        return static_cast<void*>(this);
    return BaseWindow::qt_metacast(_clname);
}

int ui::SuggestionFeedbackSendDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseWindow::qt_metacall(_c, _id, _a);
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
void ui::SuggestionFeedbackSendDialog::signalSerGetLocalFriendInfo(int _t1, std::vector<data::ChatInfo> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::SuggestionFeedbackSendDialog::startChat(CSharedPtr<data::ChatInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
