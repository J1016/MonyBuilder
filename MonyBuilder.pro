#-------------------------------------------------
#
# Project created by QtCreator 2018-11-07T21:53:06
#
#-------------------------------------------------

QT       += core gui network script

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MonyBuilder
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    MonyIde.cpp \
    MonyFrame.cpp \
    MonyTool.cpp \
    MonyTab.cpp \
    MonyTabScriptEditor.cpp \
    MonyButtonPane.cpp \
    MonyExecutor.cpp \
    borderlayout.cpp \
    MonyTabPageCreate.cpp \
    IMonyAgent.cpp \
    flowlayout.cpp \
    codeeditor.cpp \
    MonySyntaxHighlighter.cpp \
    IMonyButtonListener.cpp \
    MonyExecutorRegFuncs.cpp \
    MonyDatabase.cpp

HEADERS += \
    MonyFrame.h \
    MonyTool.h \
    MonyTab.h \
    MonyTabScriptEditor.h \
    MonyButtonPane.h \
    MonyExecutor.h \
    borderlayout.h \
    MonyTabPageCreate.h \
    IMonyAgent.h \
    flowlayout.h \
    codeeditor.h \
    MonySyntaxHighlighter.h \
    IMonyButtonListener.h \
    lauxlib.h \
    lua.h \
    lualib.h \
    luaconf.h \
    MonyExecutorRegFuncs.h \
    MonyDatabase.h

FORMS += \
        mainwindow.ui

CONFIG += mobility
MOBILITY =

INCLUDEPATH += D:\\TestQt\\MonyBuilder\\include

LIBS += -LD:\\TestQt\\MonyBuilder\\lib -llua
LIBS += E:\\opencv\\build\\install\\x86\\mingw\\lib\\libopencv_*






