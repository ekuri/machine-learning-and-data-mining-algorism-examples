TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    randomforest.cpp \
    main.cpp \
    generaterandomdata.cpp

HEADERS += \
    data.h \
    decisiontree.h \
    comparefile.h \
    split.h \
    merge.h
    decisiontree.h
