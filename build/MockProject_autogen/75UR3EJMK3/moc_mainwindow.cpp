/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.2.4)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../include/view/mainwindow.h"
#include <QtGui/qtextcursor.h>
#include <QScreen>
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtNetwork/QSslError>
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.2.4. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    const uint offsetsAndSize[38];
    char stringdata0[459];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs), len 
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 10), // "MainWindow"
QT_MOC_LITERAL(11, 29), // "on_actionOpen_Audio_triggered"
QT_MOC_LITERAL(41, 0), // ""
QT_MOC_LITERAL(42, 29), // "on_actionOpen_Video_triggered"
QT_MOC_LITERAL(72, 27), // "on_actionScan_USB_triggered"
QT_MOC_LITERAL(100, 31), // "on_actionBrowseFolder_triggered"
QT_MOC_LITERAL(132, 30), // "on_mediaTreeView_doubleClicked"
QT_MOC_LITERAL(163, 11), // "QModelIndex"
QT_MOC_LITERAL(175, 5), // "index"
QT_MOC_LITERAL(181, 29), // "on_searchLineEdit_textChanged"
QT_MOC_LITERAL(211, 4), // "text"
QT_MOC_LITERAL(216, 30), // "on_actionNewPlaylist_triggered"
QT_MOC_LITERAL(247, 33), // "on_actionDeletePlaylist_trigg..."
QT_MOC_LITERAL(281, 31), // "on_actionSavePlaylist_triggered"
QT_MOC_LITERAL(313, 39), // "on_playlistComboBox_currentIn..."
QT_MOC_LITERAL(353, 30), // "on_addToPlaylistButton_clicked"
QT_MOC_LITERAL(384, 35), // "on_removeFromPlaylistButton_c..."
QT_MOC_LITERAL(420, 21), // "on_playButton_clicked"
QT_MOC_LITERAL(442, 16) // "toggleFullScreen"

    },
    "MainWindow\0on_actionOpen_Audio_triggered\0"
    "\0on_actionOpen_Video_triggered\0"
    "on_actionScan_USB_triggered\0"
    "on_actionBrowseFolder_triggered\0"
    "on_mediaTreeView_doubleClicked\0"
    "QModelIndex\0index\0on_searchLineEdit_textChanged\0"
    "text\0on_actionNewPlaylist_triggered\0"
    "on_actionDeletePlaylist_triggered\0"
    "on_actionSavePlaylist_triggered\0"
    "on_playlistComboBox_currentIndexChanged\0"
    "on_addToPlaylistButton_clicked\0"
    "on_removeFromPlaylistButton_clicked\0"
    "on_playButton_clicked\0toggleFullScreen"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
      10,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   98,    2, 0x08,    1 /* Private */,
       3,    0,   99,    2, 0x08,    2 /* Private */,
       4,    0,  100,    2, 0x08,    3 /* Private */,
       5,    0,  101,    2, 0x08,    4 /* Private */,
       6,    1,  102,    2, 0x08,    5 /* Private */,
       9,    1,  105,    2, 0x08,    7 /* Private */,
      11,    0,  108,    2, 0x08,    9 /* Private */,
      12,    0,  109,    2, 0x08,   10 /* Private */,
      13,    0,  110,    2, 0x08,   11 /* Private */,
      14,    1,  111,    2, 0x08,   12 /* Private */,
      15,    0,  114,    2, 0x08,   14 /* Private */,
      16,    0,  115,    2, 0x08,   15 /* Private */,
      17,    0,  116,    2, 0x08,   16 /* Private */,
      18,    0,  117,    2, 0x08,   17 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::QString,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->on_actionOpen_Audio_triggered(); break;
        case 1: _t->on_actionOpen_Video_triggered(); break;
        case 2: _t->on_actionScan_USB_triggered(); break;
        case 3: _t->on_actionBrowseFolder_triggered(); break;
        case 4: _t->on_mediaTreeView_doubleClicked((*reinterpret_cast< std::add_pointer_t<QModelIndex>>(_a[1]))); break;
        case 5: _t->on_searchLineEdit_textChanged((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 6: _t->on_actionNewPlaylist_triggered(); break;
        case 7: _t->on_actionDeletePlaylist_triggered(); break;
        case 8: _t->on_actionSavePlaylist_triggered(); break;
        case 9: _t->on_playlistComboBox_currentIndexChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 10: _t->on_addToPlaylistButton_clicked(); break;
        case 11: _t->on_removeFromPlaylistButton_clicked(); break;
        case 12: _t->on_playButton_clicked(); break;
        case 13: _t->toggleFullScreen(); break;
        default: ;
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_MainWindow.offsetsAndSize,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
qt_incomplete_metaTypeArray<qt_meta_stringdata_MainWindow_t
, QtPrivate::TypeAndForceComplete<MainWindow, std::true_type>
, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QModelIndex &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<const QString &, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<int, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>, QtPrivate::TypeAndForceComplete<void, std::false_type>


>,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
