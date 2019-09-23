#-------------------------------------------------
#
# Project created by QtCreator 2014-03-25T16:40:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ../../editor

TEMPLATE = app

SOURCES +=  main.cpp\
            mainwindow.cpp \
            fengencode.cpp \
    aboutrt.cpp


HEADERS  += mainwindow.h \
            common.h \
            fengencode.h \
    aboutrt.h


FORMS    += mainwindow.ui \
            fengencode.ui \
    aboutrt.ui


RESOURCES += \
    ressource.qrc \

OTHER_FILES += \
