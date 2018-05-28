/****************************************************************************
** Meta object code from reading C++ file 'unsplash_gui_old.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../unsplash_gui_old.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'unsplash_gui_old.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Unsplash_GUI_old_t {
    QByteArrayData data[15];
    char stringdata0[266];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Unsplash_GUI_old_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Unsplash_GUI_old_t qt_meta_stringdata_Unsplash_GUI_old = {
    {
QT_MOC_LITERAL(0, 0, 16), // "Unsplash_GUI_old"
QT_MOC_LITERAL(1, 17, 18), // "on_Refresh_clicked"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 14), // "on_Res_changed"
QT_MOC_LITERAL(4, 52, 19), // "on_Interval_changed"
QT_MOC_LITERAL(5, 72, 22), // "on_defaultSave_clicked"
QT_MOC_LITERAL(6, 95, 21), // "on_changeSave_clicked"
QT_MOC_LITERAL(7, 117, 15), // "on_hide_clicked"
QT_MOC_LITERAL(8, 133, 16), // "on_About_clicked"
QT_MOC_LITERAL(9, 150, 29), // "on_differentWallpaper_clicked"
QT_MOC_LITERAL(10, 180, 5), // "state"
QT_MOC_LITERAL(11, 186, 20), // "on_autoStart_clicked"
QT_MOC_LITERAL(12, 207, 17), // "trayMenuActivated"
QT_MOC_LITERAL(13, 225, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(14, 259, 6) // "reason"

    },
    "Unsplash_GUI_old\0on_Refresh_clicked\0"
    "\0on_Res_changed\0on_Interval_changed\0"
    "on_defaultSave_clicked\0on_changeSave_clicked\0"
    "on_hide_clicked\0on_About_clicked\0"
    "on_differentWallpaper_clicked\0state\0"
    "on_autoStart_clicked\0trayMenuActivated\0"
    "QSystemTrayIcon::ActivationReason\0"
    "reason"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Unsplash_GUI_old[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a /* Public */,
       3,    0,   65,    2, 0x0a /* Public */,
       4,    0,   66,    2, 0x0a /* Public */,
       5,    0,   67,    2, 0x0a /* Public */,
       6,    0,   68,    2, 0x0a /* Public */,
       7,    0,   69,    2, 0x0a /* Public */,
       8,    0,   70,    2, 0x0a /* Public */,
       9,    1,   71,    2, 0x0a /* Public */,
      11,    1,   74,    2, 0x0a /* Public */,
      12,    1,   77,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, 0x80000000 | 13,   14,

       0        // eod
};

void Unsplash_GUI_old::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Unsplash_GUI_old *_t = static_cast<Unsplash_GUI_old *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_Refresh_clicked(); break;
        case 1: _t->on_Res_changed(); break;
        case 2: _t->on_Interval_changed(); break;
        case 3: _t->on_defaultSave_clicked(); break;
        case 4: _t->on_changeSave_clicked(); break;
        case 5: _t->on_hide_clicked(); break;
        case 6: _t->on_About_clicked(); break;
        case 7: _t->on_differentWallpaper_clicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 8: _t->on_autoStart_clicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 9: _t->trayMenuActivated((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Unsplash_GUI_old::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Unsplash_GUI_old.data,
      qt_meta_data_Unsplash_GUI_old,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *Unsplash_GUI_old::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Unsplash_GUI_old::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Unsplash_GUI_old.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "unsplash::Unsplash_Wei_old"))
        return static_cast< unsplash::Unsplash_Wei_old*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int Unsplash_GUI_old::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
