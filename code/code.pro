QT += widgets
CONFIG += release qscintilla2

HEADERS += window.h editor.h
SOURCES += main.cpp window.cpp editor.cpp

MOC_DIR = .moc
RCC_DIR = .rcc
OBJECTS_DIR = .obj
