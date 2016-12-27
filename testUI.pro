#-------------------------------------------------
#
# Project created by QtCreator 2016-12-19T14:07:01
#
#-------------------------------------------------

QT       += core gui multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testUI
TEMPLATE = app

INCLUDEPATH += /usr/include/opencv
INCLUDEPATH += /usr/include/opencv2

LIBS += -L/usr/lib -lopencv_core -lopencv_highgui -lopencv_imgproc



SOURCES += main.cpp\
        dialog.cpp \
    mythread.cpp \
    videothread.cpp \
    contourthread.cpp

HEADERS  += dialog.h \
    mythread.h \
    videothread.h \
    contourthread.h

FORMS    += dialog.ui
