/****************************************************************************
** Meta object code from reading C++ file 'liaotianwin.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "liaotianwin.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'liaotianwin.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_liaotianWin_t {
    QByteArrayData data[8];
    char stringdata0[122];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_liaotianWin_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_liaotianWin_t qt_meta_stringdata_liaotianWin = {
    {
QT_MOC_LITERAL(0, 0, 11), // "liaotianWin"
QT_MOC_LITERAL(1, 12, 19), // "onSendButtonClicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 21), // "onCancelButtonClicked"
QT_MOC_LITERAL(4, 55, 11), // "onReadyRead"
QT_MOC_LITERAL(5, 67, 15), // "onNewConnection"
QT_MOC_LITERAL(6, 83, 20), // "onSocketDisconnected"
QT_MOC_LITERAL(7, 104, 17) // "onSocketConnected"

    },
    "liaotianWin\0onSendButtonClicked\0\0"
    "onCancelButtonClicked\0onReadyRead\0"
    "onNewConnection\0onSocketDisconnected\0"
    "onSocketConnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_liaotianWin[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x08 /* Private */,
       3,    0,   45,    2, 0x08 /* Private */,
       4,    0,   46,    2, 0x08 /* Private */,
       5,    0,   47,    2, 0x08 /* Private */,
       6,    0,   48,    2, 0x08 /* Private */,
       7,    0,   49,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void liaotianWin::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<liaotianWin *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->onSendButtonClicked(); break;
        case 1: _t->onCancelButtonClicked(); break;
        case 2: _t->onReadyRead(); break;
        case 3: _t->onNewConnection(); break;
        case 4: _t->onSocketDisconnected(); break;
        case 5: _t->onSocketConnected(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
