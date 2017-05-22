#-------------------------------------------------
#
# Project created by QtCreator 2017-05-22T23:30:15
#
#-------------------------------------------------

QT       += core gui sql
# 2 添加mysql链接库
LIBS += -LC:\Myprogram\MySQL\lib -llibmysql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = management_file
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


SOURCES += main.cpp\
        mainwindow.cpp \
    admin.cpp \
    admin_manage_window.cpp \
    file.cpp \
    file_add_dlg.cpp \
    guest.cpp \
    guest_add_dlg.cpp \
    page.cpp \
    sqltools.cpp

HEADERS  += mainwindow.h \
    admin.h \
    admin_manage_window.h \
    file.h \
    file_add_dlg.h \
    global_header.h \
    guest.h \
    guest_add_dlg.h \
    page.h \
    sqltools.h

SUBDIRS += \
    demo.pro

DISTFILES += \
    question.txt \
    readme.txt \
    file_management.sql
