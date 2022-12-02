#-------------------------------------------------
#
# Project created by QtCreator 2017-08-09T00:27:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Speech_v_test
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    speechtotext.cpp

HEADERS  += mainwindow.h \
    speechtotext.h

FORMS    += mainwindow.ui

# settings the flag for the Voice
QMAKE_CXXFLAGS += -DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\" `pkg-config --cflags --libs pocketsphinx sphinxbase`
LIBS += -DMODELDIR=\"`pkg-config --variable=modeldir pocketsphinx`\" `pkg-config --cflags --libs pocketsphinx sphinxbase`


QT       += concurrent
