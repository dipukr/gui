QT += core gui widgets
CONFIG += qscintilla2
HEADERS += window.h editor.h
SOURCES += main.cpp window.cpp editor.cpp
RESOURCES += open.qrc
MOC_DIR = .moc
RCC_DIR = .rcc
OBJECTS_DIR = .obj
target.path = "D:\Code\usr"
INSTALLS += target