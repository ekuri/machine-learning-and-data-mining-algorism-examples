QT += core
QT -= gui

TARGET = classify-linear-regression
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    classify.cpp \
    regression.cpp \
    test.cpp

HEADERS += \
    csv.h \
    classify.h \
    linear_regression.h \
    linear_regression_runner.h \
    global_variable.h

