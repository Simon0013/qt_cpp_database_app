TEMPLATE = app
INCLUDEPATH += .

HEADERS     = bookwindow.h initdb.h \
    compositionwindow.h \
    editdatawindow.h \
    mainmenu.h \
    showwindow.h
RESOURCES   = books.qrc
SOURCES     = main.cpp bookwindow.cpp \
    compositionwindow.cpp \
    editdatawindow.cpp \
    mainmenu.cpp \
    showwindow.cpp
FORMS       = bookwindow.ui \
    compositionwindow.ui \
    editdatawindow.ui \
    mainmenu.ui \
    showwindow.ui

QT += sql widgets widgets

target.path = $$[QT_INSTALL_EXAMPLES]/sql/books
INSTALLS += target
