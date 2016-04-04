#-------------------------------------------------
#
# Project created by QtCreator 2016-04-04T06:22:58
#
#-------------------------------------------------

QT       += widgets testlib

greaterThan(QT_MAJOR_VERSION, 4): QT += printsupport

TARGET = halgebra
TEMPLATE = lib
CONFIG += staticlib
CONFIG += console c++11
QMAKE_CXXFLAGS += -Wall
QMAKE_CXXFLAGS += -pedantic

SOURCES += \
    Function.cpp \
    numPDE/Adams.cpp \
    numPDE/Euler.cpp

HEADERS += \
    MatrixColRow.h \
    Matrix.h \
    Utils.h \
    MiscMath.h \
    Function.h \
    Halgebra.h \
    Vector.h \
    numPDE/Adams.h \
    numPDE/Euler.h \
    numPDE/NumPDE.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
