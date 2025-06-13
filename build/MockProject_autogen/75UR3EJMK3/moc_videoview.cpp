/****************************************************************************
** Meta object code from reading C++ file 'videoview.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/view/videoview.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtNetwork/QSslError>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'videoview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VideoView_t {
    const uint offsetsAndSize[30];
    char stringdata0[338];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_VideoView_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_VideoView_t qt_meta_stringdata_VideoView = {
    {
QT_MOC_LITERAL(0, 9), // "VideoView"
QT_MOC_LITERAL(10, 21), // "handleDurationChanged"
QT_MOC_LITERAL(32, 0), // ""
QT_MOC_LITERAL(33, 8), // "duration"
QT_MOC_LITERAL(42, 21), // "handlePositionChanged"
QT_MOC_LITERAL(64, 8), // "position"
QT_MOC_LITERAL(73, 41), // "on_horizontalSlider_Duration_..."
QT_MOC_LITERAL(115, 5), // "value"
QT_MOC_LITERAL(121, 32), // "on_pushButton_Play_Pause_clicked"
QT_MOC_LITERAL(154, 26), // "on_pushButton_Stop_clicked"
QT_MOC_LITERAL(181, 34), // "on_pushButton_Seek_Forward_cl..."
QT_MOC_LITERAL(216, 35), // "on_pushButton_Seek_Backward_c..."
QT_MOC_LITERAL(252, 39), // "on_horizontalSlider_Volume_va..."
QT_MOC_LITERAL(292, 28), // "on_pushButton_Volume_clicked"
QT_MOC_LITERAL(321, 16) // "toggleFullScreen"

    },
    "VideoView\0handleDurationChanged\0\0"
    "duration\0handlePositionChanged\0position\0"
    "on_horizontalSlider_Duration_valueChanged\0"
    "value\0on_pushButton_Play_Pause_clicked\0"
    "on_pushButton_Stop_clicked\0"
    "on_pushButton_Seek_Forward_clicked\0"
    "on_pushButton_Seek_Backward_clicked\0"
    "on_horizontalSlider_Volume_valueChanged\0"
    "on_pushButton_Volume_clicked\0"
    "toggleFullScreen"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VideoView[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   74,    2, 0x08,    1 /* Private */,
       4,    1,   77,    2, 0x08,    3 /* Private */,
       6,    1,   80,    2, 0x08,    5 /* Private */,
       8,    0,   83,    2, 0x08,    7 /* Private */,
       9,    0,   84,    2, 0x08,    8 /* Private */,
      10,    0,   85,    2, 0x08,    9 /* Private */,
      11,    0,   86,    2, 0x08,   10 /* Private */,
      12,    1,   87,    2, 0x08,   11 /* Private */,
      13,    0,   90,    2, 0x08,   13 /* Private */,
      14,    0,   91,    2, 0x08,   14 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::LongLong,    3,
    QMetaType::Void, QMetaType::LongLong,    5,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VideoView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VideoView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->handleDurationChanged((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        case 1: _t->handlePositionChanged((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        case 2: _t->on_horizontalSlider_Duration_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 3: _t->on_pushButton_Play_Pause_clicked(); break;
        case 4: _t->on_pushButton_Stop_clicked(); break;
        case 5: _t->on_pushButton_Seek_Forward_clicked(); break;
        case 6: _t->on_pushButton_Seek_Backward_clicked(); break;
        case 7: _t->on_horizontalSlider_Volume_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 8: _t->on_pushButton_Volume_clicked(); break;
        case 9: _t->toggleFullScreen(); break;
        default: ;
        }
    }
}

const QMetaObject VideoView::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_VideoView.offsetsAndSize,
    qt_meta_data_VideoView,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_VideoView_t
, QtPrivate::TypeAndForceComplete<VideoView, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<qint64, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<qint64, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *VideoView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VideoView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VideoView.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int VideoView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
