#-------------------------------------------------
#
# Project created by QtCreator 2019-11-01T11:56:24
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = scapes
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11



SOURCES += \
        AddStmt.cpp \
	CodeEditor.cpp \
        CompStmt.cpp \
	DeclArrStmt.cpp \
        DeclIntStmt.cpp \
        EndStmt.cpp \
	JEqStmt.cpp \
	JLessStmt.cpp \
        JMoreStmt.cpp \
        JumpStmt.cpp \
        Label.cpp \
        Main.cpp \
        Mainwindow.cpp \
	MovStmt.cpp \
        Operand.cpp \
        PrintStmt.cpp \
        Program.cpp \
        ReadStmt.cpp \
        Statement.cpp \
        Variable.cpp \
        IntVariable.cpp \
        ArrayVariable.cpp \

HEADERS += \
    	AddStmt.h \
	CodeEditor.h \
        CompStmt.h \
    	DeclArrStmt.h \
        DeclIntStmt.h \
        EndStmt.h \
	JEqStmt.h \
	JLessStmt.h \
        JMoreStmt.h \
        JumpStmt.h \
        Label.h \
    	LineNumberArea.h \
        Mainwindow.h \
    	MovStmt.h \
        Operand.h \
        PrintStmt.h \
        Program.h \
        ReadStmt.h \
        Statement.h \
        Variable.h \
        IntVariable.h \
        ArrayVariable.h \

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
