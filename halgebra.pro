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

SOURCES += \
    function.cpp

HEADERS += halgebra.h \
    MatrixColRow.h \
    Matrix.h \
    Utils.h \
    function.h \
    MiscMath.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
