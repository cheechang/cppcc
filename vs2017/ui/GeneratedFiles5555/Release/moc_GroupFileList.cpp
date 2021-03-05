/****************************************************************************
** Meta object code from reading C++ file 'GroupFileList.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../mainwindow/contact/group/GroupFileList.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'GroupFileList.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ui__GroupFileList_t {
    QByteArrayData data[34];
    char stringdata0[487];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ui__GroupFileList_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ui__GroupFileList_t qt_meta_stringdata_ui__GroupFileList = {
    {
QT_MOC_LITERAL(0, 0, 17), // "ui::GroupFileList"
QT_MOC_LITERAL(1, 18, 9), // "startChat"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 27), // "CSharedPtr<data::ChatInfo>&"
QT_MOC_LITERAL(4, 57, 22), // "signalSerGetGroupFiles"
QT_MOC_LITERAL(5, 80, 41), // "std::vector<CSharedPtr<data::..."
QT_MOC_LITERAL(6, 122, 15), // "signalSerUpfile"
QT_MOC_LITERAL(7, 138, 8), // "FilePaht"
QT_MOC_LITERAL(8, 147, 21), // "signalSerFileProgress"
QT_MOC_LITERAL(9, 169, 8), // "progress"
QT_MOC_LITERAL(10, 178, 20), // "signalSerGetProgress"
QT_MOC_LITERAL(11, 199, 5), // "int32"
QT_MOC_LITERAL(12, 205, 11), // "std::string"
QT_MOC_LITERAL(13, 217, 5), // "int64"
QT_MOC_LITERAL(14, 223, 21), // "signalSerDelGroupfile"
QT_MOC_LITERAL(15, 245, 4), // "code"
QT_MOC_LITERAL(16, 250, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(17, 267, 4), // "item"
QT_MOC_LITERAL(18, 272, 18), // "signalSerDelUiFile"
QT_MOC_LITERAL(19, 291, 17), // "signalSerSendFile"
QT_MOC_LITERAL(20, 309, 19), // "signalSerCancelFile"
QT_MOC_LITERAL(21, 329, 13), // "onSerSendFile"
QT_MOC_LITERAL(22, 343, 3), // "err"
QT_MOC_LITERAL(23, 347, 8), // "targetId"
QT_MOC_LITERAL(24, 356, 8), // "fileJson"
QT_MOC_LITERAL(25, 365, 8), // "filepath"
QT_MOC_LITERAL(26, 374, 11), // "filelocalid"
QT_MOC_LITERAL(27, 386, 18), // "onSerGetGroupFiles"
QT_MOC_LITERAL(28, 405, 5), // "files"
QT_MOC_LITERAL(29, 411, 12), // "onSerDelFile"
QT_MOC_LITERAL(30, 424, 15), // "onSerCancelFile"
QT_MOC_LITERAL(31, 440, 11), // "onSerUpFile"
QT_MOC_LITERAL(32, 452, 16), // "onSerGetProgress"
QT_MOC_LITERAL(33, 469, 17) // "onSerDelGroupfile"

    },
    "ui::GroupFileList\0startChat\0\0"
    "CSharedPtr<data::ChatInfo>&\0"
    "signalSerGetGroupFiles\0"
    "std::vector<CSharedPtr<data::FileInfo> >&\0"
    "signalSerUpfile\0FilePaht\0signalSerFileProgress\0"
    "progress\0signalSerGetProgress\0int32\0"
    "std::string\0int64\0signalSerDelGroupfile\0"
    "code\0QListWidgetItem*\0item\0"
    "signalSerDelUiFile\0signalSerSendFile\0"
    "signalSerCancelFile\0onSerSendFile\0err\0"
    "targetId\0fileJson\0filepath\0filelocalid\0"
    "onSerGetGroupFiles\0files\0onSerDelFile\0"
    "onSerCancelFile\0onSerUpFile\0"
    "onSerGetProgress\0onSerDelGroupfile"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ui__GroupFileList[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      17,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   99,    2, 0x06 /* Public */,
       4,    2,  102,    2, 0x06 /* Public */,
       6,    2,  107,    2, 0x06 /* Public */,
       8,    1,  112,    2, 0x06 /* Public */,
      10,    5,  115,    2, 0x06 /* Public */,
      14,    2,  126,    2, 0x06 /* Public */,
      18,    1,  131,    2, 0x06 /* Public */,
      19,    5,  134,    2, 0x06 /* Public */,
      20,    3,  145,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      21,    5,  152,    2, 0x0a /* Public */,
      27,    2,  163,    2, 0x0a /* Public */,
      29,    0,  168,    2, 0x0a /* Public */,
      30,    0,  169,    2, 0x0a /* Public */,
      31,    0,  170,    2, 0x0a /* Public */,
      32,    5,  171,    2, 0x0a /* Public */,
      33,    2,  182,    2, 0x0a /* Public */,
      30,    3,  187,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 5,    2,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    7,    2,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, 0x80000000 | 11, 0x80000000 | 11, 0x80000000 | 12, QMetaType::QString, 0x80000000 | 13,    2,    2,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 16,   15,   17,
    QMetaType::Void, 0x80000000 | 13,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 13, 0x80000000 | 12, QMetaType::QString, 0x80000000 | 13,    2,    2,    2,    2,    2,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 16, QMetaType::Int,    2,   17,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, 0x80000000 | 13, 0x80000000 | 12, QMetaType::QString, 0x80000000 | 13,   22,   23,   24,   25,   26,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 5,   15,   28,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11, 0x80000000 | 11, 0x80000000 | 12, QMetaType::QString, 0x80000000 | 13,    2,    2,    2,    2,    2,
    QMetaType::Void, 0x80000000 | 13, 0x80000000 | 16,   15,   17,
    QMetaType::Void, QMetaType::Int, 0x80000000 | 16, QMetaType::Int,   15,   17,    2,

       0        // eod
};

void ui::GroupFileList::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GroupFileList *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startChat((*reinterpret_cast< CSharedPtr<data::ChatInfo>(*)>(_a[1]))); break;
        case 1: _t->signalSerGetGroupFiles((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<CSharedPtr<data::FileInfo> >(*)>(_a[2]))); break;
        case 2: _t->signalSerUpfile((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->signalSerFileProgress((*reinterpret_cast< qint32(*)>(_a[1]))); break;
        case 4: _t->signalSerGetProgress((*reinterpret_cast< int32(*)>(_a[1])),(*reinterpret_cast< int32(*)>(_a[2])),(*reinterpret_cast< const std::string(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int64(*)>(_a[5]))); break;
        case 5: _t->signalSerDelGroupfile((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< QListWidgetItem*(*)>(_a[2]))); break;
        case 6: _t->signalSerDelUiFile((*reinterpret_cast< int64(*)>(_a[1]))); break;
        case 7: _t->signalSerSendFile((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2])),(*reinterpret_cast< const std::string(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int64(*)>(_a[5]))); break;
        case 8: _t->signalSerCancelFile((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QListWidgetItem*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 9: _t->onSerSendFile((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int64(*)>(_a[2])),(*reinterpret_cast< const std::string(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int64(*)>(_a[5]))); break;
        case 10: _t->onSerGetGroupFiles((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< std::vector<CSharedPtr<data::FileInfo> >(*)>(_a[2]))); break;
        case 11: _t->onSerDelFile(); break;
        case 12: _t->onSerCancelFile(); break;
        case 13: _t->onSerUpFile(); break;
        case 14: _t->onSerGetProgress((*reinterpret_cast< int32(*)>(_a[1])),(*reinterpret_cast< int32(*)>(_a[2])),(*reinterpret_cast< const std::string(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< int64(*)>(_a[5]))); break;
        case 15: _t->onSerDelGroupfile((*reinterpret_cast< int64(*)>(_a[1])),(*reinterpret_cast< QListWidgetItem*(*)>(_a[2]))); break;
        case 16: _t->onSerCancelFile((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QListWidgetItem*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (GroupFileList::*)(CSharedPtr<data::ChatInfo> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupFileList::startChat)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (GroupFileList::*)(int , std::vector<CSharedPtr<data::FileInfo>> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupFileList::signalSerGetGroupFiles)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (GroupFileList::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupFileList::signalSerUpfile)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (GroupFileList::*)(qint32 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupFileList::signalSerFileProgress)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (GroupFileList::*)(int32 , int32 , const std::string & , QString , int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupFileList::signalSerGetProgress)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (GroupFileList::*)(int64 , QListWidgetItem * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupFileList::signalSerDelGroupfile)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (GroupFileList::*)(int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupFileList::signalSerDelUiFile)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (GroupFileList::*)(int , int64 , const std::string & , QString , int64 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupFileList::signalSerSendFile)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (GroupFileList::*)(int , QListWidgetItem * , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GroupFileList::signalSerCancelFile)) {
                *result = 8;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ui::GroupFileList::staticMetaObject = { {
    &TWidget::staticMetaObject,
    qt_meta_stringdata_ui__GroupFileList.data,
    qt_meta_data_ui__GroupFileList,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ui::GroupFileList::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ui::GroupFileList::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ui__GroupFileList.stringdata0))
        return static_cast<void*>(this);
    return TWidget::qt_metacast(_clname);
}

int ui::GroupFileList::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = TWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 17)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 17;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 17)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 17;
    }
    return _id;
}

// SIGNAL 0
void ui::GroupFileList::startChat(CSharedPtr<data::ChatInfo> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ui::GroupFileList::signalSerGetGroupFiles(int _t1, std::vector<CSharedPtr<data::FileInfo>> & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ui::GroupFileList::signalSerUpfile(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ui::GroupFileList::signalSerFileProgress(qint32 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ui::GroupFileList::signalSerGetProgress(int32 _t1, int32 _t2, const std::string & _t3, QString _t4, int64 _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ui::GroupFileList::signalSerDelGroupfile(int64 _t1, QListWidgetItem * _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ui::GroupFileList::signalSerDelUiFile(int64 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ui::GroupFileList::signalSerSendFile(int _t1, int64 _t2, const std::string & _t3, QString _t4, int64 _t5)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)), const_cast<void*>(reinterpret_cast<const void*>(&_t5)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ui::GroupFileList::signalSerCancelFile(int _t1, QListWidgetItem * _t2, int _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
