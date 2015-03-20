include(../excalendarwidget.pri)

TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS = library/excalendarwidget-library.pro

equals(BUILD_EXAMPLE, "YES") {
    SUBDIRS += example/excalendarwidget-example.pro
}
