TEMPLATE = app
INCLUDEPATH += .

HEADERS     = bookwindow.h initdb.h
RESOURCES   = books.qrc
SOURCES     = main.cpp bookwindow.cpp
FORMS       = bookwindow.ui

QT += sql widgets widgets

target.path = $$[QT_INSTALL_EXAMPLES]/sql/books
INSTALLS += target
