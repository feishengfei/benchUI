/****************************************************************************
** Meta object code from reading C++ file 'run_page.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.14.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../basebench/run_page.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'run_page.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.14.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_run_Page_t {
    QByteArrayData data[5];
    char stringdata0[83];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_run_Page_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_run_Page_t qt_meta_stringdata_run_Page = {
    {
QT_MOC_LITERAL(0, 0, 8), // "run_Page"
QT_MOC_LITERAL(1, 9, 23), // "on_runFinishBtn_clicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 23), // "on_runFolderBtn_clicked"
QT_MOC_LITERAL(4, 58, 24) // "on_runSummaryBtn_clicked"

    },
    "run_Page\0on_runFinishBtn_clicked\0\0"
    "on_runFolderBtn_clicked\0"
    "on_runSummaryBtn_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_run_Page[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x08 /* Private */,
       3,    0,   30,    2, 0x08 /* Private */,
       4,    0,   31,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void run_Page::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<run_Page *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_runFinishBtn_clicked(); break;
        case 1: _t->on_runFolderBtn_clicked(); break;
        case 2: _t->on_runSummaryBtn_clicked(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject run_Page::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_run_Page.data,
    qt_meta_data_run_Page,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *run_Page::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *run_Page::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_run_Page.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int run_Page::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
