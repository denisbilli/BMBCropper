/****************************************************************************
** Meta object code from reading C++ file 'frameoption.h'
**
** Created: Wed Nov 30 18:06:33 2016
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "frameoption.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'frameoption.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FrameOption[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: signature, parameters, type, tag, flags
      13,   12,   12,   12, 0x05,

 // slots: signature, parameters, type, tag, flags
      29,   12,   12,   12, 0x0a,

       0        // eod
};

static const char qt_meta_stringdata_FrameOption[] = {
    "FrameOption\0\0optionChanged()\0"
    "slot_onValueChangedFromExt()\0"
};

const QMetaObject FrameOption::staticMetaObject = {
    { &AbstractOption::staticMetaObject, qt_meta_stringdata_FrameOption,
      qt_meta_data_FrameOption, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FrameOption::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FrameOption::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FrameOption::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FrameOption))
        return static_cast<void*>(const_cast< FrameOption*>(this));
    return AbstractOption::qt_metacast(_clname);
}

int FrameOption::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = AbstractOption::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: optionChanged(); break;
        case 1: slot_onValueChangedFromExt(); break;
        default: ;
        }
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void FrameOption::optionChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, 0);
}
QT_END_MOC_NAMESPACE
