QT += core
QT -= gui

TARGET = classify-linear-regression
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

HEADERS += \
    csv.h \
    classify.h \
    linear_regression.h

