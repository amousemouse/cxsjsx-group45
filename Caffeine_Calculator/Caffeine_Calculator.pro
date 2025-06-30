QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    My.cpp \
    aboutus.cpp \
    cafresultwindow.cpp \
    dayinputdialog.cpp \
    drinkselectiondialog.cpp \
    loginwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    monthlystatistics.cpp \
    neworderwindow.cpp \
    profilewindow.cpp \
    user.cpp \
    usermanager.cpp

HEADERS += \
    My.h \
    aboutus.h \
    cafresultwindow.h \
    dayinputdialog.h \
    drinkselectiondialog.h \
    loginwindow.h \
    mainwindow.h \
    monthlystatistics.h \
    neworderwindow.h \
    profilewindow.h \
    user.h \
    usermanager.h

FORMS += \
    My.ui \
    aboutus.ui \
    cafresultwindow.ui \
    dayinputdialog.ui \
    drinkselectiondialog.ui \
    loginwindow.ui \
    mainwindow.ui \
    monthlystatistics.ui \
    neworderwindow.ui \
    profilewindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    icons/aboutus.png

RESOURCES += \
    resources.qrc
