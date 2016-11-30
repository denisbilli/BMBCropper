/****************************************************************************
** Meta object code from reading C++ file 'reportageframegenerator.h'
**
** Created: Wed Nov 30 18:11:43 2016
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "reportageframegenerator.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'reportageframegenerator.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_ReportageFrameGenerator[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // enums: name, flags, count, data

 // enum data: key, value

       0        // eod
};

static const char qt_meta_stringdata_ReportageFrameGenerator[] = {
    "ReportageFrameGenerator\0"
};

const QMetaObject ReportageFrameGenerator::staticMetaObject = {
    { &FrameGenerator::staticMetaObject, qt_meta_stringdata_ReportageFrameGenerator,
      qt_meta_data_ReportageFrameGenerator, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &ReportageFrameGenerator::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *ReportageFrameGenerator::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *ReportageFrameGenerator::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_ReportageFrameGenerator))
        return static_cast<void*>(const_cast< ReportageFrameGenerator*>(this));
    return FrameGenerator::qt_metacast(_clname);
}

int ReportageFrameGenerator::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = FrameGenerator::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    return _id;
}
QT_END_MOC_NAMESPACE
