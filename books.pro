TEMPLATE = app
INCLUDEPATH += .

HEADERS     = bookwindow.h initdb.h \
    mainmenu.h
RESOURCES   = books.qrc
SOURCES     = main.cpp bookwindow.cpp \
    mainmenu.cpp
FORMS       = bookwindow.ui \
    mainmenu.ui

QT += sql widgets widgets

target.path = $$[QT_INSTALL_EXAMPLES]/sql/books
INSTALLS += target
