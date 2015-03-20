include(../../excalendarwidget.pri)

QT = core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = lib
TARGET = $$EXCALENDARWIDGET_LIB_NAME

VERSION = $$EXCALENDARWIDGET_LIB_VERSION

CONFIG += $$EXCALENDARWIDGET_CONFIG

DEFINES += EXCALENDARWIDGET_LIB

INCLUDEPATH += \
    source/

EXCALENDARWIDGET_PUBLIC_HEADERS = \
    source/excalendarwidget/excalendarwidget_common.h \
    source/excalendarwidget/excalendarwidget.h

EXCALENDARWIDGET_PRIVATE_HEADERS = \
    source/excalendarwidget/excalendarwidget_p.h \
    source/excalendarwidget/excalendarview.h \
    source/excalendarwidget/excalendarmonthview.h \
    source/excalendarwidget/excalendaryearview.h \
    source/excalendarwidget/excalendardecadeview.h \
    source/excalendarwidget/excalendarnavigator.h

EXCALENDARWIDGET_SOURCES = \
    source/excalendarwidget.cpp \
    source/excalendarwidget_p.cpp \
    source/excalendarview.cpp \
    source/excalendarmonthview.cpp \
    source/excalendaryearview.cpp \
    source/excalendardecadeview.cpp \
    source/excalendarnavigator.cpp

HEADERS = \
    $$EXCALENDARWIDGET_PUBLIC_HEADERS \
    $$EXCALENDARWIDGET_PRIVATE_HEADERS

SOURCES = \
    $$EXCALENDARWIDGET_SOURCES

INSTALL_HEADERS = \
    $$EXCALENDARWIDGET_PUBLIC_HEADERS

target.path = $$INSTALL_LIBS_DIR

header.files =  $$INSTALL_HEADERS
header.path = $$INSTALL_INCLUDES_DIR

INSTALLS = target header
