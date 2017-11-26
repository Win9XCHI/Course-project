QT += gui core sql

CONFIG += c++11 console
CONFIG -= app_bundle

PACKAGECONFIG_append_pn-qtbase = " sql-sqlite"
#LIBS += -lsqlite3
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += main.cpp \
    list.cpp \
    itemList.cpp \
    projectbd.cpp \
    route.cpp \
    searchtrain.cpp \
    timebase.cpp \
    time1.cpp

HEADERS += \
    list.h \
    itemList.h \
    projectbd.h \
    route.h \
    searchtrain.h \
    timebase.h \
    time1.h

#win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../Qt/Tools/mingw530_32/lib/ -lsqlite3

INCLUDEPATH += $$PWD/sqlite-snapshot-201710211717
DEPENDPATH += $$PWD/sqlite-snapshot-201710211717
