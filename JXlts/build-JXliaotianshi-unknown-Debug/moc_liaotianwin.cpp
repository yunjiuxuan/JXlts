/****************************************************************************
** Meta object code from reading C++ file 'liaotianwin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../JXliaotianshi/liaotianwin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'liaotianwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MediaUrlModel_t {
    QByteArrayData data[1];
    char stringdata0[14];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MediaUrlModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MediaUrlModel_t qt_meta_stringdata_MediaUrlModel = {
    {
QT_MOC_LITERAL(0, 0, 13) // "MediaUrlModel"

    },
    "MediaUrlModel"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MediaUrlModel[] = {

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

void MediaUrlModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    Q_UNUSED(_o);
    Q_UNUSED(_id);
    Q_UNUSED(_c);
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject MediaUrlModel::staticMetaObject = { {
    &QSqlQueryModel::staticMetaObject,
    qt_meta_stringdata_MediaUrlModel.data,
    qt_meta_data_MediaUrlModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MediaUrlModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MediaUrlModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MediaUrlModel.stringdata0))
        return static_cast<void*>(this);
    return QSqlQueryModel::qt_metacast(_clname);
}

int MediaUrlModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSqlQueryModel::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_liaotianWin_t {
    QByteArrayData data[33];
    char stringdata0[480];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_liaotianWin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_liaotianWin_t qt_meta_stringdata_liaotianWin = {
    {
QT_MOC_LITERAL(0, 0, 11), // "liaotianWin"
QT_MOC_LITERAL(1, 12, 17), // "onMessageReceived"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 6), // "userId"
QT_MOC_LITERAL(4, 38, 7), // "message"
QT_MOC_LITERAL(5, 46, 15), // "onUserConnected"
QT_MOC_LITERAL(6, 62, 18), // "onUserDisconnected"
QT_MOC_LITERAL(7, 81, 12), // "onSendResult"
QT_MOC_LITERAL(8, 94, 7), // "success"
QT_MOC_LITERAL(9, 102, 8), // "errorMsg"
QT_MOC_LITERAL(10, 111, 15), // "onReceiveResult"
QT_MOC_LITERAL(11, 127, 14), // "onFileReceived"
QT_MOC_LITERAL(12, 142, 8), // "fileName"
QT_MOC_LITERAL(13, 151, 8), // "filePath"
QT_MOC_LITERAL(14, 160, 14), // "onFileProgress"
QT_MOC_LITERAL(15, 175, 9), // "bytesSent"
QT_MOC_LITERAL(16, 185, 10), // "totalBytes"
QT_MOC_LITERAL(17, 196, 16), // "onMediaFileAdded"
QT_MOC_LITERAL(18, 213, 15), // "onFileCancelled"
QT_MOC_LITERAL(19, 229, 22), // "onFileReceiveCancelled"
QT_MOC_LITERAL(20, 252, 22), // "onGroupMessageReceived"
QT_MOC_LITERAL(21, 275, 7), // "groupId"
QT_MOC_LITERAL(22, 283, 8), // "senderId"
QT_MOC_LITERAL(23, 292, 10), // "senderName"
QT_MOC_LITERAL(24, 303, 19), // "onSendButtonClicked"
QT_MOC_LITERAL(25, 323, 21), // "onCancelButtonClicked"
QT_MOC_LITERAL(26, 345, 23), // "onSendFileButtonClicked"
QT_MOC_LITERAL(27, 369, 17), // "onDateEditClicked"
QT_MOC_LITERAL(28, 387, 26), // "onCalendarSelectionChanged"
QT_MOC_LITERAL(29, 414, 20), // "onMediaPlayerClicked"
QT_MOC_LITERAL(30, 435, 11), // "QModelIndex"
QT_MOC_LITERAL(31, 447, 5), // "index"
QT_MOC_LITERAL(32, 453, 26) // "onMediaPlayerDoubleClicked"

    },
    "liaotianWin\0onMessageReceived\0\0userId\0"
    "message\0onUserConnected\0onUserDisconnected\0"
    "onSendResult\0success\0errorMsg\0"
    "onReceiveResult\0onFileReceived\0fileName\0"
    "filePath\0onFileProgress\0bytesSent\0"
    "totalBytes\0onMediaFileAdded\0onFileCancelled\0"
    "onFileReceiveCancelled\0onGroupMessageReceived\0"
    "groupId\0senderId\0senderName\0"
    "onSendButtonClicked\0onCancelButtonClicked\0"
    "onSendFileButtonClicked\0onDateEditClicked\0"
    "onCalendarSelectionChanged\0"
    "onMediaPlayerClicked\0QModelIndex\0index\0"
    "onMediaPlayerDoubleClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_liaotianWin[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    2,  104,    2, 0x0a /* Public */,
       5,    1,  109,    2, 0x0a /* Public */,
       6,    1,  112,    2, 0x0a /* Public */,
       7,    3,  115,    2, 0x0a /* Public */,
      10,    3,  122,    2, 0x0a /* Public */,
      11,    3,  129,    2, 0x0a /* Public */,
      14,    3,  136,    2, 0x0a /* Public */,
      17,    2,  143,    2, 0x0a /* Public */,
      18,    2,  148,    2, 0x0a /* Public */,
      19,    2,  153,    2, 0x0a /* Public */,
      20,    4,  158,    2, 0x0a /* Public */,
      24,    0,  167,    2, 0x08 /* Private */,
      25,    0,  168,    2, 0x08 /* Private */,
      26,    0,  169,    2, 0x08 /* Private */,
      27,    0,  170,    2, 0x08 /* Private */,
      28,    0,  171,    2, 0x08 /* Private */,
      29,    1,  172,    2, 0x08 /* Private */,
      32,    1,  175,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, QMetaType::QString,    3,    8,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, QMetaType::QString,    3,    8,    9,
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::QString,    3,   12,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::LongLong, QMetaType::LongLong,    3,   15,   16,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,   13,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,   12,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString, QMetaType::QString,   21,   22,   23,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 30,   31,
    QMetaType::Void, 0x80000000 | 30,   31,

       0        // eod
};

void liaotianWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<liaotianWin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onMessageReceived((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->onUserConnected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->onUserDisconnected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onSendResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 4: _t->onReceiveResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 5: _t->onFileReceived((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 6: _t->onFileProgress((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< qint64(*)>(_a[2])),(*reinterpret_cast< qint64(*)>(_a[3]))); break;
        case 7: _t->onMediaFileAdded((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 8: _t->onFileCancelled((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 9: _t->onFileReceiveCancelled((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 10: _t->onGroupMessageReceived((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])),(*reinterpret_cast< const QString(*)>(_a[4]))); break;
        case 11: _t->onSendButtonClicked(); break;
        case 12: _t->onCancelButtonClicked(); break;
        case 13: _t->onSendFileButtonClicked(); break;
        case 14: _t->onDateEditClicked(); break;
        case 15: _t->onCalendarSelectionChanged(); break;
        case 16: _t->onMediaPlayerClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 17: _t->onMediaPlayerDoubleClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject liaotianWin::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_liaotianWin.data,
    qt_meta_data_liaotianWin,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *liaotianWin::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *liaotianWin::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_liaotianWin.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int liaotianWin::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
