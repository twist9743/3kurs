QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
CONFIG += console

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    acclist.cpp \
    addacc.cpp \
    crypt.cpp \
    customwidget.cpp \
    dbmodel.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    acclist.h \
    addacc.h \
    crypt.h \
    customwidget.h \
    dbmodel.h \
    mainwindow.h

FORMS += \
    acclist.ui \
    addacc.ui \
    customwidget.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
*.debug=true
include($$PWD/../Qt-Secret/src/Qt-Secret.pri)
