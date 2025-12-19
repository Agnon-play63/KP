QT       += core gui sql charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    clientmanager.cpp \
    main.cpp \
    mainwindow.cpp \
    namevalidator.cpp \
    schedulemanager.cpp \
    statisticsmanager.cpp \
    subscriptionmanager.cpp \
    trainermanager.cpp

HEADERS += \
    clientmanager.h \
    mainwindow.h \
    namevalidator.h \
    schedulemanager.h \
    statisticsmanager.h \
    subscriptionmanager.h \
    trainermanager.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    ars_kyrsach_ru_RU.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
