/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created: Wed Nov 30 18:06:31 2016
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_MainWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      12,   11,   11,   11, 0x08,
      38,   11,   11,   11, 0x08,
      80,   74,   11,   11, 0x08,
     113,   74,   11,   11, 0x08,
     146,   74,   11,   11, 0x08,
     181,   11,   11,   11, 0x08,
     206,   11,   11,   11, 0x08,
     233,   11,   11,   11, 0x08,
     271,  248,   11,   11, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_MainWindow[] = {
    "MainWindow\0\0on_actionApri_triggered()\0"
    "on_actionGenera_Cornici_triggered()\0"
    "index\0on_listView_clicked(QModelIndex)\0"
    "on_listView_pressed(QModelIndex)\0"
    "on_listView_activated(QModelIndex)\0"
    "on_radioButton_clicked()\0"
    "on_radioButton_2_clicked()\0slot_onTimer()\0"
    "optionName,optionValue\0"
    "slot_onOptionChanged(QString,QVariant)\0"
};

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow,
      qt_meta_data_MainWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &MainWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_actionApri_triggered(); break;
        case 1: on_actionGenera_Cornici_triggered(); break;
        case 2: on_listView_clicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 3: on_listView_pressed((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 4: on_listView_activated((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 5: on_radioButton_clicked(); break;
        case 6: on_radioButton_2_clicked(); break;
        case 7: slot_onTimer(); break;
        case 8: slot_onOptionChanged((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QVariant(*)>(_a[2]))); break;
        default: ;
        }
        _id -= 9;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
