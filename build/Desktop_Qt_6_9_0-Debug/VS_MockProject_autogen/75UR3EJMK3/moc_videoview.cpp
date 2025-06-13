/****************************************************************************
** Meta object code from reading C++ file 'videoview.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../include/view/videoview.h"
#include <QtGui/qtextcursor.h>
#include <QtGui/qscreen.h>
#include <QtNetwork/QSslPreSharedKeyAuthenticator>
#include <QtNetwork/QSslError>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'videoview.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN9VideoViewE_t {};
} // unnamed namespace

template <> constexpr inline auto VideoView::qt_create_metaobjectdata<qt_meta_tag_ZN9VideoViewE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "VideoView",
        "handleDurationChanged",
        "",
        "duration",
        "handlePositionChanged",
        "position",
        "on_horizontalSlider_Duration_valueChanged",
        "value",
        "on_pushButton_Play_Pause_clicked",
        "on_pushButton_Stop_clicked",
        "on_pushButton_Seek_Forward_clicked",
        "on_pushButton_Seek_Backward_clicked",
        "on_horizontalSlider_Volume_valueChanged",
        "on_pushButton_Volume_clicked",
        "toggleFullScreen"
    };

    QtMocHelpers::UintData qt_methods {
        // Slot 'handleDurationChanged'
        QtMocHelpers::SlotData<void(qint64)>(1, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::LongLong, 3 },
        }}),
        // Slot 'handlePositionChanged'
        QtMocHelpers::SlotData<void(qint64)>(4, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::LongLong, 5 },
        }}),
        // Slot 'on_horizontalSlider_Duration_valueChanged'
        QtMocHelpers::SlotData<void(int)>(6, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 7 },
        }}),
        // Slot 'on_pushButton_Play_Pause_clicked'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_Stop_clicked'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_Seek_Forward_clicked'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_Seek_Backward_clicked'
        QtMocHelpers::SlotData<void()>(11, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_horizontalSlider_Volume_valueChanged'
        QtMocHelpers::SlotData<void(int)>(12, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 7 },
        }}),
        // Slot 'on_pushButton_Volume_clicked'
        QtMocHelpers::SlotData<void()>(13, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'toggleFullScreen'
        QtMocHelpers::SlotData<void()>(14, 2, QMC::AccessPrivate, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<VideoView, qt_meta_tag_ZN9VideoViewE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject VideoView::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9VideoViewE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9VideoViewE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN9VideoViewE_t>.metaTypes,
    nullptr
} };

void VideoView::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<VideoView *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
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

const QMetaObject *VideoView::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VideoView::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9VideoViewE_t>.strings))
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
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
