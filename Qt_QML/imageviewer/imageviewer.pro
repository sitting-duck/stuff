QT += widgets
requires(qtConfig(filedialog))
qtHaveModule(printsupport): QT += printsupport

HEADERS       = imageviewer.h

SOURCES       = imageviewer.cpp \
                main.cpp

INCLUDEPATH += "/usr/local/include/"
LIB += -L"usr/local/lib/"

