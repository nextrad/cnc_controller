#-------------------------------------------------
#
# Project created by QtCreator 2018-02-06T15:14:51
#
#-------------------------------------------------

QT       += core gui widgets



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cnc_controller
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += -L/usr/lib/x86_64-linux-gnu -lboost_system -pthread

QMAKE_CXXFLAGS += -std=c++0x -pthread   #using c++11 and multithreading

SOURCES += audio_connection_manager.cpp \
    connection_manager.cpp \
    datetime.cpp \
    header_arm_files.cpp \
    headerfilewindow.cpp \
    main.cpp \
    mainwindow.cpp \
    networkmanager.cpp \
    timingdialog.cpp \
    pulsedialog.cpp \
    targetdialog.cpp \
    bearingsdialog.cpp \
    weatherdialog.cpp \
    geometrydialog.cpp \
    quicklookdialog.cpp


HEADERS  +=  audio_connection_manager.h \
    connection_manager.h \
    datetime.h \
    header_arm_files.h \
    headerfilewindow.h \
    includes.h \
    mainwindow.h \
    networkmanager.h \
    parameters.h \
    timingdialog.h \
    pulsedialog.h \
    targetdialog.h \
    bearingsdialog.h \
    ../build/ui_headerfilewindow.h \
    ../build/ui_mainwindow.h \
    ../build/ui_bearingsdialog.h \
    ../build/ui_pulsedialog.h \
    ../build/ui_targetdialog.h \
    ../build/ui_timingdialog.h \
    weatherdialog.h \
    geometrydialog.h \
    quicklookdialog.h

FORMS    += mainwindow.ui \
    headerfilewindow.ui \
    timingdialog.ui \
    pulsedialog.ui \
    targetdialog.ui \
    bearingsdialog.ui \
    weatherdialog.ui \
    geometrydialog.ui \
    quicklookdialog.ui
