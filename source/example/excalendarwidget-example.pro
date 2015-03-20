include(../../excalendarwidget.pri)

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app

INCLUDEPATH += \
    $$EXCALENDARWIDGET_LIB_DIR/source

LIBS += \
    -L$$EXCALENDARWIDGET_LIB_DIR -l$$EXCALENDARWIDGET_LIB_NAME

SOURCES = \
    main.cpp
