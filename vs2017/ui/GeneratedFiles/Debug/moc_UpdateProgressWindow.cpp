/****************************************************************************
** Meta object code from reading C++ file 'UpdateProgressWindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../updatewindow/UpdateProgressWindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'UpdateProgressWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__UpdateProgressWindow_t {
    QByteArrayData data[9];
    char stringdata0[123];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__UpdateProgressWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__UpdateProgressWindow_t qt_meta_stringdata_ui__UpdateProgressWindow = {
    {
QT_MOC_LITERAL(0, 0, 24), // "ui::UpdateProgressWindow"
QT_MOC_LITERAL(1, 25, 14), // "CancelDownLoad"
QT_MOC_LITERAL(2, 40, 0), // ""
QT_MOC_LITERAL(3, 41, 10), // "ReDownLoad"
QT_MOC_LITERAL(4, 52, 11), // "ShowErrInfo"
QT_MOC_LITERAL(5, 64, 10), // "ShowWindow"
QT_MOC_LITERAL(6, 75, 17), // "onBtnCloseClicked"
QT_MOC_LITERAL(7, 93, 6), // "onShow"
QT_MOC_LITERAL(8, 100, 22) // "onBtnReDownLoadClicked"

    },
    "ui::UpdateProgressWindow\0CancelDownLoad\0"
    "\0ReDownLoad\0ShowErrInfo\0ShowWindow\0"
    "onBtnCloseClicked\0onShow\0"
    "onBtnReDownLoadClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__UpdateProgressWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    0,   50,    2, 0x06 /* Public */,
       4,    1,   51,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   54,    2, 0x0a /* Public */,
       6,    0,   55,    2, 0x0a /* Public */,
       7,    0,   56,    2, 0x0a /* Public */,
       8,    0,   57,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ui::UpdateProgressWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<UpdateProgressWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->CancelDownLoad(); break;
        case 1: _t->ReDownLoad(); break;
        case 2: _t->ShowErrInfo((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->ShowWindow(); break;
        case 4: _t->onBtnCloseClicked(); break;
        case 5: _t->onShow(); break;
        case 6: _t->onBtnReDownLoadClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (UpdateProgressWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UpdateProgressWindow::CancelDownLoad)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (UpdateProgressWindow::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UpdateProgressWindow::ReDownLoad)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (UpdateProgressWindow::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&UpdateProgressWindow::ShowErrInfo)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::UpdateProgressWindow::staticMetaObject = { {
    &BaseDialog::staticMetaObject,
    qt_meta_stringdata_ui__UpdateProgressWindow.data,
    qt_meta_data_ui__UpdateProgressWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::UpdateProgressWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::UpdateProgressWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__UpdateProgressWindow.stringdata0))
        return static_cast<void*>(this);
    return BaseDialog::qt_metacast(_clname);
}

int ui::UpdateProgressWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void ui::UpdateProgressWindow::CancelDownLoad()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ui::UpdateProgressWindow::ReDownLoad()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ui::UpdateProgressWindow::ShowErrInfo(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
