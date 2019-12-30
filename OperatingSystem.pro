#-------------------------------------------------
#
# Project created by QtCreator 2019-12-25T10:02:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OperatingSystem
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
        cglobal.cpp \
        data_define.cpp \
        dialog_delete_data.cpp \
        dialog_gen_data.cpp \
        disk_manager.cpp \
        disk_monitor.cpp \
        folder_manager.cpp \
        gendatathread.cpp \
        main.cpp \
        mainwindow.cpp \
        memory_manager.cpp \
        memory_monitor.cpp \
        process_manager.cpp \
        systemwindow.cpp \
        window_exe_data.cpp

HEADERS += \
        cglobal.h \
        data_define.h \
        dialog_delete_data.h \
        dialog_gen_data.h \
        disk_manager.h \
        disk_monitor.h \
        folder_manager.h \
        gendatathread.h \
        memory_manager.h \
        memory_monitor.h \
        process_manager.h \
        systemwindow.h \
        widget.h \
        mainwindow.h \
        window_exe_data.h

FORMS += \
        dialog_delete_data.ui \
        dialog_gen_data.ui \
        disk_monitor.ui \
        mainwindow.ui \
        memory_monitor.ui \
        systemwindow.ui \
        window_del_data.ui \
        window_exe_data.ui \
        window_gen_data.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
