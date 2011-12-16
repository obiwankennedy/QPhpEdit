QT += webkit network
TARGET = ../bin/QPhpEdit
TEMPLATE = app
include(Style/Style.pri)
include(projects/projects.pri)
include(options/options.pri)
include(editwidget/editwidget.pri)
include(textEditor/textEditor.pri)
include(NewDialog/NewDialog.pri)
include(filebrowser/filebrowser.pri)
INCLUDEPATH += Style \
    options \
    editwidget \
    NewDialog \
    textEditor \
    filebrowser \
    projects
DEPENDPATH= Style \
	options \
	editwidget \
	NewDialog \
	textEditor \
	filebrowser \
	projects
SOURCES += main.cpp \
    mainwindow.cpp \
    misc.cpp
HEADERS += mainwindow.h \
    misc.h
MOC_DIR = ../bin
OBJECTS_DIR = ../bin
RESOURCES += ../qphpedit.qrc
