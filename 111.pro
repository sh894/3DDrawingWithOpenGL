#-------------------------------------------------
#
# Project created by QtCreator 2015-04-03T17:30:06
#
#-------------------------------------------------

QT       += core

QT       -= gui


QT       +=opengl


TARGET = 111
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    glwidget.cpp \
    loadobj.cpp \
    mainwindow.cpp



mac: LIBS += -framework GLUT
else:unix|win32: LIBS += -lGLUT

mac: LIBS += -framework GLKit
else:unix|win32: LIBS += -lGLKit

HEADERS += \
    platonicsolid.h \
    glwidget.h \
    loadobj.h \
    mainwindow.h
