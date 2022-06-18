QT += widgets
CONFIG += release

HEADERS = textedit.h mainwindow.h
SOURCES = main.cpp textedit.cpp mainwindow.cpp
RESOURCES = open.qrc

MOC_DIR = .moc
RCC_DIR = .rcc
OBJECTS_DIR = .obj

target.path = "D:\Code\usr"
INSTALLS += target