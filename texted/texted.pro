QT += widgets
CONFIG += release

HEADERS = textedit.h highlighter.h mainwindow.h
SOURCES = main.cpp textedit.cpp highlighter.cpp mainwindow.cpp
RESOURCES = texted.qrc

MOC_DIR = .moc
RCC_DIR = .rcc
OBJECTS_DIR = .obj