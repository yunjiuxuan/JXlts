/****************************************************************************
** Meta object code from reading C++ file 'chatworker.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.8)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../副本/JXlts/JXliaotianshi/chatworker.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'chatworker.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.8. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ChatWorker_t {
    QByteArrayData data[30];
    char stringdata0[377];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ChatWorker_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ChatWorker_t qt_meta_stringdata_ChatWorker = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ChatWorker"
QT_MOC_LITERAL(1, 11, 15), // "messageReceived"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 12), // "targetUserId"
QT_MOC_LITERAL(4, 41, 11), // "jsonMessage"
QT_MOC_LITERAL(5, 53, 9), // "connected"
QT_MOC_LITERAL(6, 63, 12), // "disconnected"
QT_MOC_LITERAL(7, 76, 13), // "errorOccurred"
QT_MOC_LITERAL(8, 90, 5), // "error"
QT_MOC_LITERAL(9, 96, 10), // "sendResult"
QT_MOC_LITERAL(10, 107, 7), // "success"
QT_MOC_LITERAL(11, 115, 8), // "errorMsg"
QT_MOC_LITERAL(12, 124, 17), // "handshakeReceived"
QT_MOC_LITERAL(13, 142, 9), // "oldUserId"
QT_MOC_LITERAL(14, 152, 13), // "newRealUserId"
QT_MOC_LITERAL(15, 166, 11), // "sendMessage"
QT_MOC_LITERAL(16, 178, 7), // "message"
QT_MOC_LITERAL(17, 186, 11), // "messageType"
QT_MOC_LITERAL(18, 198, 18), // "disconnectFromHost"
QT_MOC_LITERAL(19, 217, 13), // "sendHandshake"
QT_MOC_LITERAL(20, 231, 18), // "updateTargetUserId"
QT_MOC_LITERAL(21, 250, 9), // "newUserId"
QT_MOC_LITERAL(22, 260, 11), // "onReadyRead"
QT_MOC_LITERAL(23, 272, 11), // "onConnected"
QT_MOC_LITERAL(24, 284, 14), // "onDisconnected"
QT_MOC_LITERAL(25, 299, 15), // "onErrorOccurred"
QT_MOC_LITERAL(26, 315, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(27, 344, 11), // "socketError"
QT_MOC_LITERAL(28, 356, 14), // "onBytesWritten"
QT_MOC_LITERAL(29, 371, 5) // "bytes"

    },
    "ChatWorker\0messageReceived\0\0targetUserId\0"
    "jsonMessage\0connected\0disconnected\0"
    "errorOccurred\0error\0sendResult\0success\0"
    "errorMsg\0handshakeReceived\0oldUserId\0"
    "newRealUserId\0sendMessage\0message\0"
    "messageType\0disconnectFromHost\0"
    "sendHandshake\0updateTargetUserId\0"
    "newUserId\0onReadyRead\0onConnected\0"
    "onDisconnected\0onErrorOccurred\0"
    "QAbstractSocket::SocketError\0socketError\0"
    "onBytesWritten\0bytes"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ChatWorker[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   94,    2, 0x06 /* Public */,
       5,    1,   99,    2, 0x06 /* Public */,
       6,    1,  102,    2, 0x06 /* Public */,
       7,    2,  105,    2, 0x06 /* Public */,
       9,    3,  110,    2, 0x06 /* Public */,
      12,    3,  117,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      15,    2,  124,    2, 0x0a /* Public */,
      15,    1,  129,    2, 0x2a /* Public | MethodCloned */,
      18,    0,  132,    2, 0x0a /* Public */,
      19,    0,  133,    2, 0x0a /* Public */,
      20,    1,  134,    2, 0x0a /* Public */,
      22,    0,  137,    2, 0x08 /* Private */,
      23,    0,  138,    2, 0x08 /* Private */,
      24,    0,  139,    2, 0x08 /* Private */,
      25,    1,  140,    2, 0x08 /* Private */,
      28,    1,  143,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    4,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int, QMetaType::QString,    3,    8,
    QMetaType::Void, QMetaType::Int, QMetaType::Bool, QMetaType::QString,    3,   10,   11,
    QMetaType::Void, QMetaType::Int, QMetaType::Int, QMetaType::QString,   13,   14,    4,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   16,   17,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 26,   27,
    QMetaType::Void, QMetaType::LongLong,   29,

       0        // eod
};

void ChatWorker::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ChatWorker *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->messageReceived((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 1: _t->connected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->disconnected((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->errorOccurred((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->sendResult((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 5: _t->handshakeReceived((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 6: _t->sendMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 7: _t->sendMessage((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->disconnectFromHost(); break;
        case 9: _t->sendHandshake(); break;
        case 10: _t->updateTargetUserId((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->onReadyRead(); break;
        case 12: _t->onConnected(); break;
        case 13: _t->onDisconnected(); break;
        case 14: _t->onErrorOccurred((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 15: _t->onBytesWritten((*reinterpret_cast< qint64(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 14:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ChatWorker::*)(int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatWorker::messageReceived)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ChatWorker::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatWorker::connected)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ChatWorker::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatWorker::disconnected)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ChatWorker::*)(int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatWorker::errorOccurred)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ChatWorker::*)(int , bool , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatWorker::sendResult)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ChatWorker::*)(int , int , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ChatWorker::handshakeReceived)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ChatWorker::staticMetaObject = { {
    &QObject::staticMetaObject,
    qt_meta_stringdata_ChatWorker.data,
    qt_meta_data_ChatWorker,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ChatWorker::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ChatWorker::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ChatWorker.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QRunnable"))
        return static_cast< QRunnable*>(this);
    return QObject::qt_metacast(_clname);
}

int ChatWorker::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void ChatWorker::messageReceived(int _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ChatWorker::connected(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ChatWorker::disconnected(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ChatWorker::errorOccurred(int _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ChatWorker::sendResult(int _t1, bool _t2, const QString & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ChatWorker::handshakeReceived(int _t1, int _t2, const QString & _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
