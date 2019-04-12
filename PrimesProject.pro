TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    readxml.cpp \
    tag.cpp \
    primenumfunc.cpp \
    findprimes.cpp \
    intervalsoutput.cpp \
    primesconsoleoutput.cpp \
    primenumbersvector.cpp \
    primesfileoutput.cpp

HEADERS += \
    readxml.h \
    tag.h \
    interval.hpp \
    primenumfunc.h \
    findprimes.h \
    intervalsoutput.h \
    xml_output.hpp \
    primesoutput.hpp \
    primesconsoleoutput.h \
    primenumbersvector.h \
    primesfileoutput.h
