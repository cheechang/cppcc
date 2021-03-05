/****************************************************************************
** Meta object code from reading C++ file 'GroupListWidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/contact/group/GroupListWidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GroupListWidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__GroupListWidget_t {
    QByteArrayData data[46];
    char stringdata0[782];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__GroupListWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__GroupListWidget_t qt_meta_stringdata_ui__GroupListWidget = {
    {
QT_MOC_LITERAL(0, 0, 19), // "ui::GroupListWidget"
QT_MOC_LITERAL(1, 20, 9), // "startChat"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 27), // "CSharedPtr<data::ChatInfo>&"
QT_MOC_LITERAL(4, 59, 4), // "chat"
QT_MOC_LITERAL(5, 64, 18), // "showGroupInforPage"
QT_MOC_LITERAL(6, 83, 5), // "int64"
QT_MOC_LITERAL(7, 89, 7), // "groupId"
QT_MOC_LITERAL(8, 97, 24), // "signalSerGroupListNotify"
QT_MOC_LITERAL(9, 122, 42), // "std::vector<CSharedPtr<data::..."
QT_MOC_LITERAL(10, 165, 27), // "signalSerGroupHeadImgNotify"
QT_MOC_LITERAL(11, 193, 11), // "std::string"
QT_MOC_LITERAL(12, 205, 27), // "signalSerGroupOpertorNotify"
QT_MOC_LITERAL(13, 233, 27), // "signalSerGroupRefreshNotify"
QT_MOC_LITERAL(14, 261, 4), // "int8"
QT_MOC_LITERAL(15, 266, 11), // "data::Group"
QT_MOC_LITERAL(16, 278, 28), // "signalSerTransferGroupNotify"
QT_MOC_LITERAL(17, 307, 20), // "onSerGroupListNotify"
QT_MOC_LITERAL(18, 328, 6), // "groups"
QT_MOC_LITERAL(19, 335, 23), // "onSerGroupHeadImgNotify"
QT_MOC_LITERAL(20, 359, 4), // "head"
QT_MOC_LITERAL(21, 364, 23), // "onSerGroupOpertorNotify"
QT_MOC_LITERAL(22, 388, 4), // "code"
QT_MOC_LITERAL(23, 393, 23), // "onSerGroupRefreshNotify"
QT_MOC_LITERAL(24, 417, 4), // "type"
QT_MOC_LITERAL(25, 422, 5), // "group"
QT_MOC_LITERAL(26, 428, 24), // "onSerTransferGroupNotify"
QT_MOC_LITERAL(27, 453, 9), // "creatorId"
QT_MOC_LITERAL(28, 463, 11), // "creatorName"
QT_MOC_LITERAL(29, 475, 9), // "groupName"
QT_MOC_LITERAL(30, 485, 24), // "updateItemAndSelItemInfo"
QT_MOC_LITERAL(31, 510, 7), // "DataPtr"
QT_MOC_LITERAL(32, 518, 4), // "data"
QT_MOC_LITERAL(33, 523, 13), // "onItemClicked"
QT_MOC_LITERAL(34, 537, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(35, 554, 4), // "item"
QT_MOC_LITERAL(36, 559, 19), // "onItemDoubleClicked"
QT_MOC_LITERAL(37, 579, 19), // "onExistGroupClicked"
QT_MOC_LITERAL(38, 599, 22), // "onTransferGroupClicked"
QT_MOC_LITERAL(39, 622, 25), // "onDissolutionGroupClicked"
QT_MOC_LITERAL(40, 648, 21), // "onSerSetVGroupClicked"
QT_MOC_LITERAL(41, 670, 24), // "onSerCancelVGroupClicked"
QT_MOC_LITERAL(42, 695, 22), // "onSerSetVGroupCallback"
QT_MOC_LITERAL(43, 718, 5), // "Error"
QT_MOC_LITERAL(44, 724, 15), // "onGetVGroupSign"
QT_MOC_LITERAL(45, 740, 41) // "std::vector<CSharedPtr<data::..."

    },
    "ui::GroupListWidget\0startChat\0\0"
    "CSharedPtr<data::ChatInfo>&\0chat\0"
    "showGroupInforPage\0int64\0groupId\0"
    "signalSerGroupListNotify\0"
    "std::vector<CSharedPtr<data::TinyGroup> >&\0"
    "signalSerGroupHeadImgNotify\0std::string\0"
    "signalSerGroupOpertorNotify\0"
    "signalSerGroupRefreshNotify\0int8\0"
    "data::Group\0signalSerTransferGroupNotify\0"
    "onSerGroupListNotify\0groups\0"
    "onSerGroupHeadImgNotify\0head\0"
    "onSerGroupOpertorNotify\0code\0"
    "onSerGroupRefreshNotify\0type\0group\0"
    "onSerTransferGroupNotify\0creatorId\0"
    "creatorName\0groupName\0updateItemAndSelItemInfo\0"
    "DataPtr\0data\0onItemClicked\0QListWidgetItem*\0"
    "item\0onItemDoubleClicked\0onExistGroupClicked\0"
    "onTransferGroupClicked\0onDissolutionGroupClicked\0"
    "onSerSetVGroupClicked\0onSerCancelVGroupClicked\0"
    "onSerSetVGroupCallback\0Error\0"
    "onGetVGroupSign\0"
    "std::vector<CSharedPtr<data::TinyGroup> >"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__GroupListWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      22,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  124,    2, 0x06 /* Public */,
       5,    1,  127,    2, 0x06 /* Public */,
       8,    1,  130,    2, 0x06 /* Public */,
      10,    2,  133,    2, 0x06 /* Public */,
      12,    1,  138,    2, 0x06 /* Public */,
      13,    2,  141,    2, 0x06 /* Public */,
      16,    4,  146,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      17,    1,  155,    2, 0x0a /* Public */,
      19,    2,  158,    2, 0x0a /* Public */,
      21,    1,  163,    2, 0x0a /* Public */,
      23,    2,  166,    2, 0x0a /* Public */,
      26,    4,  171,    2, 0x0a /* Public */,
      30,    1,  180,    2, 0x0a /* Public */,
      33,    1,  183,    2, 0x0a /* Public */,
      36,    1,  186,    2, 0x0a /* Public */,
      37,    0,  189,    2, 0x0a /* Public */,
      38,    0,  190,    2, 0x0a /* Public */,
      39,    0,  191,    2, 0x0a /* Public */,
      40,    0,  192,    2, 0x0a /* Public */,
      41,    0,  193,    2, 0x0a /* Public */,
      42,    1,  194,    2, 0x0a /* Public */,
      44,    1,  197,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 11,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, 0x80000000 | 14, 0x80000000 | 15,    2,    2,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 11, 0x80000000 | 6, 0x80000000 | 11,    2,    2,    2,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 9,   18,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 11,    7,   20,
    QMetaType::Void, QMetaType::Int,   22,
    QMetaType::Void, 0x80000000 | 14, 0x80000000 | 15,   24,   25,
    QMetaType::Void, 0x80000000 | 6, 0x80000000 | 11, 0x80000000 | 6, 0x80000000 | 11,   27,   28,    7,   29,
    QMetaType::Void, 0x80000000 | 31,   32,
    QMetaType::Void, 0x80000000 | 34,   35,
    QMetaType::Void, 0x80000000 | 34,   35,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   43,
    QMetaType::Void, 0x80000000 | 45,   18,

       0        // eod
};

void ui::GroupListWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GroupListWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startChat((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        case 1: _t->showGroupInforPage((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 2: _t->signalSerGroupListNotify((*reinterpret_cast< std::vector<CSharedPtr<data::TinyGroup> >(*)>(_a[1]))); break;
        case 3: _t->signalSerGroupHeadImgNotify((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2]))); break;
        case 4: _t->signalSerGroupOpertorNotify((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->signalSerGroupRefreshNotify((*reinterpret_cast< int8(*)>(_a[1])),(*reinterpret_cast< const data::Group(*)>(_a[2]))); break;
        case 6: _t->signalSerTransferGroupNotify((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3])),(*reinterpret_cast< const std::string(*)>(_a[4]))); break;
        case 7: _t->onSerGroupListNotify((*reinterpret_cast< std::vector<CSharedPtr<data::TinyGroup> >(*)>(_a[1]))); break;
        case 8: _t->onSerGroupHeadImgNotify((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2]))); break;
        case 9: _t->onSerGroupOpertorNotify((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->onSerGroupRefreshNotify((*reinterpret_cast< int8(*)>(_a[1])),(*reinterpret_cast< const data::Group(*)>(_a[2]))); break;
        case 11: _t->onSerTransferGroupNotify((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< const std::string(*)>(_a[2])),(*reinterpret_cast< int64(*)>(_a[3])),(*reinterpret_cast< const std::string(*)>(_a[4]))); break;
        case 12: _t->updateItemAndSelItemInfo((*reinterpret_cast< DataPtr(*)>(_a[1]))); break;
        case 13: _t->onItemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 14: _t->onItemDoubleClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 15: _t->onExistGroupClicked(); break;
        case 16: _t->onTransferGroupClicked(); break;
        case 17: _t->onDissolutionGroupClicked(); break;
        case 18: _t->onSerSetVGroupClicked(); break;
        case 19: _t->onSerCancelVGroupClicked(); break;
        case 20: _t->onSerSetVGroupCallback((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 21: _t->onGetVGroupSign((*reinterpret_cast< std::vector<CSharedPtr<data::TinyGroup> >(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GroupListWidget::*)(CSharedPtr<data::ChatInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupListWidget::startChat)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GroupListWidget::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupListWidget::showGroupInforPage)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GroupListWidget::*)(std::vector<CSharedPtr<data::TinyGroup> > & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupListWidget::signalSerGroupListNotify)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GroupListWidget::*)(int64 , const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupListWidget::signalSerGroupHeadImgNotify)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GroupListWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupListWidget::signalSerGroupOpertorNotify)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (GroupListWidget::*)(int8 , const data::Group & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupListWidget::signalSerGroupRefreshNotify)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (GroupListWidget::*)(int64 , const std::string & , int64 , const std::string & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupListWidget::signalSerTransferGroupNotify)) {
                *result = 6;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::GroupListWidget::staticMetaObject = { {
    &TWidget::staticMetaObject,
    qt_meta_stringdata_ui__GroupListWidget.data,
    qt_meta_data_ui__GroupListWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::GroupListWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::GroupListWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__GroupListWidget.stringdata0))
        return static_cast<void*>(this);
    return TWidget::qt_metacast(_clname);
}

int ui::GroupListWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 22)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 22;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 22)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 22;
    }
    return _id;
}

// SIGNAL 0
void ui::GroupListWidget::startChat(CSharedPtr<data::ChatInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::GroupListWidget::showGroupInforPage(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::GroupListWidget::signalSerGroupListNotify(std::vector<CSharedPtr<data::TinyGroup> > & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ui::GroupListWidget::signalSerGroupHeadImgNotify(int64 _t1, const std::string & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ui::GroupListWidget::signalSerGroupOpertorNotify(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ui::GroupListWidget::signalSerGroupRefreshNotify(int8 _t1, const data::Group & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ui::GroupListWidget::signalSerTransferGroupNotify(int64 _t1, const std::string & _t2, int64 _t3, const std::string & _t4)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
