/****************************************************************************
** Meta object code from reading C++ file 'unsplash_gui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../unsplash_gui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'unsplash_gui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Unsplash_GUI_t {
    QByteArrayData data[12];
    char stringdata0[205];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Unsplash_GUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Unsplash_GUI_t qt_meta_stringdata_Unsplash_GUI = {
    {
QT_MOC_LITERAL(0, 0, 12), // "Unsplash_GUI"
QT_MOC_LITERAL(1, 13, 18), // "on_Refresh_clicked"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 14), // "on_Res_changed"
QT_MOC_LITERAL(4, 48, 19), // "on_Interval_changed"
QT_MOC_LITERAL(5, 68, 22), // "on_defaultSave_clicked"
QT_MOC_LITERAL(6, 91, 21), // "on_changeSave_clicked"
QT_MOC_LITERAL(7, 113, 15), // "on_exit_clicked"
QT_MOC_LITERAL(8, 129, 16), // "on_About_clicked"
QT_MOC_LITERAL(9, 146, 17), // "trayMenuActivated"
QT_MOC_LITERAL(10, 164, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(11, 198, 6) // "reason"

    },
    "Unsplash_GUI\0on_Refresh_clicked\0\0"
    "on_Res_changed\0on_Interval_changed\0"
    "on_defaultSave_clicked\0on_changeSave_clicked\0"
    "on_exit_clicked\0on_About_clicked\0"
    "trayMenuActivated\0QSystemTrayIcon::ActivationReason\0"
    "reason"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Unsplash_GUI[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x0a /* Public */,
       3,    0,   55,    2, 0x0a /* Public */,
       4,    0,   56,    2, 0x0a /* Public */,
       5,    0,   57,    2, 0x0a /* Public */,
       6,    0,   58,    2, 0x0a /* Public */,
       7,    0,   59,    2, 0x0a /* Public */,
       8,    0,   60,    2, 0x0a /* Public */,
       9,    1,   61,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,

       0        // eod
};

void Unsplash_GUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Unsplash_GUI *_t = static_cast<Unsplash_GUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_Refresh_clicked(); break;
        case 1: _t->on_Res_changed(); break;
        case 2: _t->on_Interval_changed(); break;
        case 3: _t->on_defaultSave_clicked(); break;
        case 4: _t->on_changeSave_clicked(); break;
        case 5: _t->on_exit_clicked(); break;
        case 6: _t->on_About_clicked(); break;
        case 7: _t->trayMenuActivated((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject Unsplash_GUI::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_Unsplash_GUI.data,
      qt_meta_data_Unsplash_GUI,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Unsplash_GUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Unsplash_GUI::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Unsplash_GUI.stringdata0))
        return static_cast<void*>(const_cast< Unsplash_GUI*>(this));
    if (!strcmp(_clname, "unsplash::Unsplash_Wei"))
        return static_cast< unsplash::Unsplash_Wei*>(const_cast< Unsplash_GUI*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int Unsplash_GUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
