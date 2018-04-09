TEMPLATE = app
DESTDIR = $$PWD/../bin
TARGET = Gobang
QT += widgets

SOURCES += \
    main.cpp \
    chessboard.cpp \
    chessboardwidget.cpp \
    chessjudge.cpp \
    mainwindow.cpp \
    chessarena.cpp \
    playermanager.cpp \
    playerloader.cpp

HEADERS += \
    ichessboard.h \
    chessboard.h \
    chessboardwidget.h \
    chessjudge.h \
    ichessplayer.h \
    mainwindow.h \
    chessarena.h \
    playermanager.h \
    playerloader.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    resources.qrc
