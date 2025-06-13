/****************************************************************************
** Meta object code from reading C++ file 'playlistview.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/view/playlistview.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtNetwork/QSslError>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'playlistview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_PlaylistView_t {
    const uint offsetsAndSize[48];
    char stringdata0[410];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_PlaylistView_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_PlaylistView_t qt_meta_stringdata_PlaylistView = {
    {
QT_MOC_LITERAL(0, 12), // "PlaylistView"
QT_MOC_LITERAL(13, 21), // "on_playButton_clicked"
QT_MOC_LITERAL(35, 0), // ""
QT_MOC_LITERAL(36, 21), // "on_nextButton_clicked"
QT_MOC_LITERAL(58, 25), // "on_previousButton_clicked"
QT_MOC_LITERAL(84, 21), // "on_stopButton_clicked"
QT_MOC_LITERAL(106, 28), // "on_volumeSlider_valueChanged"
QT_MOC_LITERAL(135, 5), // "value"
QT_MOC_LITERAL(141, 29), // "on_positionSlider_sliderMoved"
QT_MOC_LITERAL(171, 8), // "position"
QT_MOC_LITERAL(180, 29), // "on_playlistView_doubleClicked"
QT_MOC_LITERAL(210, 11), // "QModelIndex"
QT_MOC_LITERAL(222, 5), // "index"
QT_MOC_LITERAL(228, 14), // "updateDuration"
QT_MOC_LITERAL(243, 8), // "duration"
QT_MOC_LITERAL(252, 14), // "updatePosition"
QT_MOC_LITERAL(267, 14), // "updateMetadata"
QT_MOC_LITERAL(282, 24), // "handleMediaStatusChanged"
QT_MOC_LITERAL(307, 25), // "QMediaPlayer::MediaStatus"
QT_MOC_LITERAL(333, 6), // "status"
QT_MOC_LITERAL(340, 18), // "handleStateChanged"
QT_MOC_LITERAL(359, 27), // "QMediaPlayer::PlaybackState"
QT_MOC_LITERAL(387, 5), // "state"
QT_MOC_LITERAL(393, 16) // "toggleFullScreen"

    },
    "PlaylistView\0on_playButton_clicked\0\0"
    "on_nextButton_clicked\0on_previousButton_clicked\0"
    "on_stopButton_clicked\0"
    "on_volumeSlider_valueChanged\0value\0"
    "on_positionSlider_sliderMoved\0position\0"
    "on_playlistView_doubleClicked\0QModelIndex\0"
    "index\0updateDuration\0duration\0"
    "updatePosition\0updateMetadata\0"
    "handleMediaStatusChanged\0"
    "QMediaPlayer::MediaStatus\0status\0"
    "handleStateChanged\0QMediaPlayer::PlaybackState\0"
    "state\0toggleFullScreen"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_PlaylistView[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   92,    2, 0x08,    1 /* Private */,
       3,    0,   93,    2, 0x08,    2 /* Private */,
       4,    0,   94,    2, 0x08,    3 /* Private */,
       5,    0,   95,    2, 0x08,    4 /* Private */,
       6,    1,   96,    2, 0x08,    5 /* Private */,
       8,    1,   99,    2, 0x08,    7 /* Private */,
      10,    1,  102,    2, 0x08,    9 /* Private */,
      13,    1,  105,    2, 0x08,   11 /* Private */,
      15,    1,  108,    2, 0x08,   13 /* Private */,
      16,    0,  111,    2, 0x08,   15 /* Private */,
      17,    1,  112,    2, 0x08,   16 /* Private */,
      20,    1,  115,    2, 0x08,   18 /* Private */,
      23,    0,  118,    2, 0x08,   20 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, QMetaType::LongLong,   14,
    QMetaType::Void, QMetaType::LongLong,    9,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 18,   19,
    QMetaType::Void, 0x80000000 | 21,   22,
    QMetaType::Void,

       0        // eod
};

void PlaylistView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PlaylistView *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_playButton_clicked(); break;
        case 1: _t->on_nextButton_clicked(); break;
        case 2: _t->on_previousButton_clicked(); break;
        case 3: _t->on_stopButton_clicked(); break;
        case 4: _t->on_volumeSlider_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 5: _t->on_positionSlider_sliderMoved((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 6: _t->on_playlistView_doubleClicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 7: _t->updateDuration((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        case 8: _t->updatePosition((*reinterpret_cast< std::add_pointer_t<qint64>>(_a[1]))); break;
        case 9: _t->updateMetadata(); break;
        case 10: _t->handleMediaStatusChanged((*reinterpret_cast< std::add_pointer_t<QMediaPlayer::MediaStatus>>(_a[1]))); break;
        case 11: _t->handleStateChanged((*reinterpret_cast< std::add_pointer_t<QMediaPlayer::PlaybackState>>(_a[1]))); break;
        case 12: _t->toggleFullScreen(); break;
        default: ;
        }
    }
}

const QMetaObject PlaylistView::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_PlaylistView.offsetsAndSize,
    qt_meta_data_PlaylistView,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_PlaylistView_t
, QtPrivate::TypeAndForceComplete<PlaylistView, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<qint64, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<qint64, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMediaPlayer::MediaStatus, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<QMediaPlayer::PlaybackState, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *PlaylistView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PlaylistView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_PlaylistView.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int PlaylistView::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
