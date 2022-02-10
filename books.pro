TEMPLATE = app
INCLUDEPATH += .

HEADERS     = bookwindow.h initdb.h \
    editdatawindow.h \
    mainmenu.h \
    showwindow.h
RESOURCES   = books.qrc
SOURCES     = main.cpp bookwindow.cpp \
    editdatawindow.cpp \
    mainmenu.cpp \
    showwindow.cpp
FORMS       = bookwindow.ui \
    editdatawindow.ui \
    mainmenu.ui \
    showwindow.ui

QT += sql widgets widgets

target.path = $$[QT_INSTALL_EXAMPLES]/sql/books
INSTALLS += target
