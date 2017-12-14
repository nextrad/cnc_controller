TEMPLATE = app
TARGET = cnc_controller

QT = core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

LIBS += -L/usr/lib/x86_64-linux-gnu -lboost_system -pthread

QMAKE_CXXFLAGS += -std=c++0x -pthread   #using c++11 and multithreading

SOURCES += \
    main.cpp \
    window.cpp \
    connection_manager.cpp \
    audio_connection_manager.cpp \
    headerfilewindow.cpp \
    networkmanager.cpp \
    datetime.cpp \
    header_arm_files.cpp

HEADERS += \
    window.h \
    connection_manager.h \
    parameters.h \
    includes.h \
    audio_connection_manager.h \
    headerfilewindow.h \
    networkmanager.h \
    datetime.h \
    header_arm_files.h
