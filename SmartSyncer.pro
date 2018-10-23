#-------------------------------------------------
#
# Project created by QtCreator 2018-10-22T10:57:57
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartSyncer
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

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    qrcoder.cpp \
    utilities.cpp \
    command.cpp \
    result.cpp \
    syncserver.cpp \
    syncthread.cpp

HEADERS += \
        mainwindow.h \
    qrcoder.h \
    utilities.h \
    command.h \
    result.h \
    syncserver.h \
    syncthread.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

macx: LIBS += -L$$PWD/qzxing-master/build-QZXing-Desktop_Qt_5_11_1_clang_64bit-Debug/ -lQZXing.2.3.0

INCLUDEPATH += $$PWD/qzxing-master/src
DEPENDPATH += $$PWD/qzxing-master/src

RESOURCES += \
    smartsyncer.qrc
