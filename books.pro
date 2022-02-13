TEMPLATE = app
INCLUDEPATH += .

HEADERS     = bookwindow.h initdb.h \
    compositionwindow.h \
    editdatawindow.h \
    inputdatawindow.h \
    mainmenu.h \
    perfomancewindow.h \
    ratingwindow.h \
    showwindow.h \
    showwindow2.h
RESOURCES   = books.qrc
SOURCES     = main.cpp bookwindow.cpp \
    compositionwindow.cpp \
    editdatawindow.cpp \
    inputdatawindow.cpp \
    mainmenu.cpp \
    perfomancewindow.cpp \
    ratingwindow.cpp \
    showwindow.cpp \
    showwindow2.cpp
FORMS       = bookwindow.ui \
    compositionwindow.ui \
    editdatawindow.ui \
    inputdatawindow.ui \
    mainmenu.ui \
    perfomancewindow.ui \
    ratingwindow.ui \
    showwindow.ui \
    showwindow2.ui

QT += sql widgets widgets

target.path = $$[QT_INSTALL_EXAMPLES]/sql/books
INSTALLS += target
