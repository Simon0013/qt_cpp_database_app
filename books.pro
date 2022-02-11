TEMPLATE = app
INCLUDEPATH += .

HEADERS     = bookwindow.h initdb.h \
    compositionwindow.h \
    editdatawindow.h \
    mainmenu.h \
    ratingwindow.h \
    showwindow.h \
    showwindow2.h
RESOURCES   = books.qrc
SOURCES     = main.cpp bookwindow.cpp \
    compositionwindow.cpp \
    editdatawindow.cpp \
    mainmenu.cpp \
    ratingwindow.cpp \
    showwindow.cpp \
    showwindow2.cpp
FORMS       = bookwindow.ui \
    compositionwindow.ui \
    editdatawindow.ui \
    mainmenu.ui \
    ratingwindow.ui \
    showwindow.ui \
    showwindow2.ui

QT += sql widgets widgets

target.path = $$[QT_INSTALL_EXAMPLES]/sql/books
INSTALLS += target
