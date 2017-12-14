TEMPLATE = app
TARGET = cnc_controller

QT = core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -L/usr/lib/x86_64-linux-gnu -lboost_system -pthread

QMAKE_CXXFLAGS += -std=c++0x -pthread   #using c++11 and multithreading

SOURCES += \
    audio_connection_manager.cpp \
    connection_manager.cpp \
    datetime.cpp \
    header_arm_files.cpp \
    headerfilewindow.cpp \
    main.cpp \
    networkmanager.cpp \
    window.cpp

HEADERS += \
    audio_connection_manager.h \
    connection_manager.h \
    datetime.h \
    header_arm_files.h \
    headerfilewindow.h \
    includes.h \
    networkmanager.h \
    parameters.h \
    window.h
