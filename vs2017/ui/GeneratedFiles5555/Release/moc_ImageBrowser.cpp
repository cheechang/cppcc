/****************************************************************************
** Meta object code from reading C++ file 'ImageBrowser.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/imageBrowser/ImageBrowser.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ImageBrowser.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__ImageBrowser_t {
    QByteArrayData data[14];
    char stringdata0[148];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__ImageBrowser_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__ImageBrowser_t qt_meta_stringdata_ui__ImageBrowser = {
    {
QT_MOC_LITERAL(0, 0, 16), // "ui::ImageBrowser"
QT_MOC_LITERAL(1, 17, 10), // "onDownload"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 8), // "onZoomIn"
QT_MOC_LITERAL(4, 38, 9), // "onZoomOut"
QT_MOC_LITERAL(5, 48, 8), // "onRotate"
QT_MOC_LITERAL(6, 57, 9), // "onBtnLeft"
QT_MOC_LITERAL(7, 67, 10), // "onBtnRight"
QT_MOC_LITERAL(8, 78, 5), // "onMin"
QT_MOC_LITERAL(9, 84, 7), // "onClose"
QT_MOC_LITERAL(10, 92, 5), // "onMax"
QT_MOC_LITERAL(11, 98, 20), // "onSetRightBtnTooltip"
QT_MOC_LITERAL(12, 119, 19), // "onSetLeftBtnTooltip"
QT_MOC_LITERAL(13, 139, 8) // "showPags"

    },
    "ui::ImageBrowser\0onDownload\0\0onZoomIn\0"
    "onZoomOut\0onRotate\0onBtnLeft\0onBtnRight\0"
    "onMin\0onClose\0onMax\0onSetRightBtnTooltip\0"
    "onSetLeftBtnTooltip\0showPags"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__ImageBrowser[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x09 /* Protected */,
       3,    0,   75,    2, 0x09 /* Protected */,
       4,    0,   76,    2, 0x09 /* Protected */,
       5,    0,   77,    2, 0x09 /* Protected */,
       6,    0,   78,    2, 0x09 /* Protected */,
       7,    0,   79,    2, 0x09 /* Protected */,
       8,    0,   80,    2, 0x09 /* Protected */,
       9,    0,   81,    2, 0x09 /* Protected */,
      10,    0,   82,    2, 0x09 /* Protected */,
      11,    0,   83,    2, 0x09 /* Protected */,
      12,    0,   84,    2, 0x09 /* Protected */,
      13,    0,   85,    2, 0x09 /* Protected */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ui::ImageBrowser::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ImageBrowser *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onDownload(); break;
        case 1: _t->onZoomIn(); break;
        case 2: _t->onZoomOut(); break;
        case 3: _t->onRotate(); break;
        case 4: _t->onBtnLeft(); break;
        case 5: _t->onBtnRight(); break;
        case 6: _t->onMin(); break;
        case 7: _t->onClose(); break;
        case 8: _t->onMax(); break;
        case 9: _t->onSetRightBtnTooltip(); break;
        case 10: _t->onSetLeftBtnTooltip(); break;
        case 11: _t->showPags(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject ui::ImageBrowser::staticMetaObject = { {
    &BaseDialog::staticMetaObject,
    qt_meta_stringdata_ui__ImageBrowser.data,
    qt_meta_data_ui__ImageBrowser,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::ImageBrowser::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::ImageBrowser::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__ImageBrowser.stringdata0))
        return static_cast<void*>(this);
    return BaseDialog::qt_metacast(_clname);
}

int ui::ImageBrowser::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = BaseDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
