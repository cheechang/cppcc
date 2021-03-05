/****************************************************************************
** Meta object code from reading C++ file 'DrawShapeWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../DrawShapeWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DrawShapeWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GraphicsViewWidget_t {
    QByteArrayData data[1];
    char stringdata0[19];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GraphicsViewWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GraphicsViewWidget_t qt_meta_stringdata_GraphicsViewWidget = {
    {
QT_MOC_LITERAL(0, 0, 18) // "GraphicsViewWidget"

    },
    "GraphicsViewWidget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GraphicsViewWidget[] = {

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

void GraphicsViewWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject GraphicsViewWidget::staticMetaObject = { {
    &QGraphicsView::staticMetaObject,
    qt_meta_stringdata_GraphicsViewWidget.data,
    qt_meta_data_GraphicsViewWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *GraphicsViewWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GraphicsViewWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GraphicsViewWidget.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsView::qt_metacast(_clname);
}

int GraphicsViewWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsView::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_PaintWidgetScene_t {
    QByteArrayData data[13];
    char stringdata0[147];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_PaintWidgetScene_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_PaintWidgetScene_t qt_meta_stringdata_PaintWidgetScene = {
    {
QT_MOC_LITERAL(0, 0, 16), // "PaintWidgetScene"
QT_MOC_LITERAL(1, 17, 20), // "signalLeftBtnPressed"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 19), // "slotSetCurrentShape"
QT_MOC_LITERAL(4, 59, 11), // "Shape::Code"
QT_MOC_LITERAL(5, 71, 1), // "s"
QT_MOC_LITERAL(6, 73, 3), // "pen"
QT_MOC_LITERAL(7, 77, 15), // "slotDelLastDraw"
QT_MOC_LITERAL(8, 93, 13), // "slotSetCurPen"
QT_MOC_LITERAL(9, 107, 14), // "slotSetCurFont"
QT_MOC_LITERAL(10, 122, 4), // "font"
QT_MOC_LITERAL(11, 127, 11), // "slotAddText"
QT_MOC_LITERAL(12, 139, 7) // "content"

    },
    "PaintWidgetScene\0signalLeftBtnPressed\0"
    "\0slotSetCurrentShape\0Shape::Code\0s\0"
    "pen\0slotDelLastDraw\0slotSetCurPen\0"
    "slotSetCurFont\0font\0slotAddText\0content"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PaintWidgetScene[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    2,   49,    2, 0x0a /* Public */,
       7,    0,   54,    2, 0x0a /* Public */,
       8,    1,   55,    2, 0x0a /* Public */,
       9,    2,   58,    2, 0x0a /* Public */,
      11,    1,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPointF, QMetaType::Bool,    2,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4, QMetaType::QPen,    5,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QPen,    6,
    QMetaType::Void, QMetaType::QPen, QMetaType::QFont,    6,   10,
    QMetaType::Void, QMetaType::QString,   12,

       0        // eod
};

void PaintWidgetScene::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PaintWidgetScene *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalLeftBtnPressed((*reinterpret_cast< QPointF(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->slotSetCurrentShape((*reinterpret_cast< Shape::Code(*)>(_a[1])),(*reinterpret_cast< QPen(*)>(_a[2]))); break;
        case 2: _t->slotDelLastDraw(); break;
        case 3: _t->slotSetCurPen((*reinterpret_cast< QPen(*)>(_a[1]))); break;
        case 4: _t->slotSetCurFont((*reinterpret_cast< QPen(*)>(_a[1])),(*reinterpret_cast< QFont(*)>(_a[2]))); break;
        case 5: _t->slotAddText((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (PaintWidgetScene::*)(QPointF , bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&PaintWidgetScene::signalLeftBtnPressed)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject PaintWidgetScene::staticMetaObject = { {
    &QGraphicsScene::staticMetaObject,
    qt_meta_stringdata_PaintWidgetScene.data,
    qt_meta_data_PaintWidgetScene,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *PaintWidgetScene::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PaintWidgetScene::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PaintWidgetScene.stringdata0))
        return static_cast<void*>(this);
    return QGraphicsScene::qt_metacast(_clname);
}

int PaintWidgetScene::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QGraphicsScene::qt_metacall(_c, _id, _a);
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
void PaintWidgetScene::signalLeftBtnPressed(QPointF _t1, bool _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_CustomColorButton_t {
    QByteArrayData data[5];
    char stringdata0[48];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CustomColorButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CustomColorButton_t qt_meta_stringdata_CustomColorButton = {
    {
QT_MOC_LITERAL(0, 0, 17), // "CustomColorButton"
QT_MOC_LITERAL(1, 18, 7), // "Clicked"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 5), // "index"
QT_MOC_LITERAL(4, 33, 14) // "slotBtnClicked"

    },
    "CustomColorButton\0Clicked\0\0index\0"
    "slotBtnClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CustomColorButton[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   27,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void CustomColorButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<CustomColorButton *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Clicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->slotBtnClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (CustomColorButton::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&CustomColorButton::Clicked)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject CustomColorButton::staticMetaObject = { {
    &QToolButton::staticMetaObject,
    qt_meta_stringdata_CustomColorButton.data,
    qt_meta_data_CustomColorButton,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CustomColorButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CustomColorButton::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CustomColorButton.stringdata0))
        return static_cast<void*>(this);
    return QToolButton::qt_metacast(_clname);
}

int CustomColorButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QToolButton::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void CustomColorButton::Clicked(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_SelectColorWidget_t {
    QByteArrayData data[11];
    char stringdata0[170];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SelectColorWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SelectColorWidget_t qt_meta_stringdata_SelectColorWidget = {
    {
QT_MOC_LITERAL(0, 0, 17), // "SelectColorWidget"
QT_MOC_LITERAL(1, 18, 18), // "signalSelectChange"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 22), // "signalSelectFontChange"
QT_MOC_LITERAL(4, 61, 19), // "slotColorBtnClicked"
QT_MOC_LITERAL(5, 81, 5), // "index"
QT_MOC_LITERAL(6, 87, 19), // "slotThinLineClicked"
QT_MOC_LITERAL(7, 107, 22), // "slotMediateLineClicked"
QT_MOC_LITERAL(8, 130, 18), // "slotBigLineClicked"
QT_MOC_LITERAL(9, 149, 15), // "slotFontChanged"
QT_MOC_LITERAL(10, 165, 4) // "font"

    },
    "SelectColorWidget\0signalSelectChange\0"
    "\0signalSelectFontChange\0slotColorBtnClicked\0"
    "index\0slotThinLineClicked\0"
    "slotMediateLineClicked\0slotBigLineClicked\0"
    "slotFontChanged\0font"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SelectColorWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,
       3,    2,   52,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   57,    2, 0x09 /* Protected */,
       6,    0,   60,    2, 0x09 /* Protected */,
       7,    0,   61,    2, 0x09 /* Protected */,
       8,    0,   62,    2, 0x09 /* Protected */,
       9,    1,   63,    2, 0x09 /* Protected */,

 // signals: parameters
    QMetaType::Void, QMetaType::QPen,    2,
    QMetaType::Void, QMetaType::QPen, QMetaType::QFont,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   10,

       0        // eod
};

void SelectColorWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SelectColorWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalSelectChange((*reinterpret_cast< QPen(*)>(_a[1]))); break;
        case 1: _t->signalSelectFontChange((*reinterpret_cast< QPen(*)>(_a[1])),(*reinterpret_cast< QFont(*)>(_a[2]))); break;
        case 2: _t->slotColorBtnClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->slotThinLineClicked(); break;
        case 4: _t->slotMediateLineClicked(); break;
        case 5: _t->slotBigLineClicked(); break;
        case 6: _t->slotFontChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (SelectColorWidget::*)(QPen );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SelectColorWidget::signalSelectChange)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (SelectColorWidget::*)(QPen , QFont );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&SelectColorWidget::signalSelectFontChange)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SelectColorWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_SelectColorWidget.data,
    qt_meta_data_SelectColorWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SelectColorWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SelectColorWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SelectColorWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SelectColorWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void SelectColorWidget::signalSelectChange(QPen _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SelectColorWidget::signalSelectFontChange(QPen _t1, QFont _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_CustomTextEditWidget_t {
    QByteArrayData data[1];
    char stringdata0[21];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CustomTextEditWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CustomTextEditWidget_t qt_meta_stringdata_CustomTextEditWidget = {
    {
QT_MOC_LITERAL(0, 0, 20) // "CustomTextEditWidget"

    },
    "CustomTextEditWidget"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CustomTextEditWidget[] = {

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

void CustomTextEditWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject CustomTextEditWidget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_CustomTextEditWidget.data,
    qt_meta_data_CustomTextEditWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *CustomTextEditWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CustomTextEditWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CustomTextEditWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int CustomTextEditWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
