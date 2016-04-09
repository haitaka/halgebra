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
    numPDE/Euler.cpp \
    Ploter/Axis.cpp \
    Ploter/Ploter.cpp \
    Utils.cpp \
    numPDE/RungeKutta.cpp \
    numeth/Integr.cpp \
    ReportTools/TextTable.cpp \
    Utils.cpp

HEADERS += \
    MatrixColRow.h \
    Matrix.h \
    Utils.h \
    MiscMath.h \
    Function.h \
    Halgebra.h \
    Vector.h \
    numPDE/Euler.h \
    numPDE/NumPDE.h \
    Ploter/Axis.h \
    Ploter/Plot.h \
    Ploter/Ploter.h \
    numPDE/RungeKutta.h \
    numeth/Integr.h \
    ReportTools/TextTable.h \
    VectorFunc.h \
    numPDE/adams.h \
    numPDE/Adams.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
