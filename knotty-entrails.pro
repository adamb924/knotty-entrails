QT -= gui
QT += xml

TEMPLATE = lib
DEFINES += KNOTTYENTRAILS_LIBRARY

CONFIG += c++11

SOURCES += \
    abstractparsedform.cpp \
    abstracttextadapter.cpp \
    abstracttextitem.cpp \
    abstracttextsegment.cpp \
    domparsedform.cpp \
    domtextitem.cpp \
    domtextsegment.cpp \
    parsedform.cpp \
    simpletextadapter.cpp \
    textitem.cpp \
    textsegment.cpp

HEADERS += \
    abstractparsedform.h \
    abstracttextadapter.h \
    abstracttextitem.h \
    abstracttextsegment.h \
    domparsedform.h \
    domtextitem.h \
    domtextsegment.h \
    knotty-entrails_global.h \
    parsedform.h \
    simpletextadapter.h \
    textitem.h \
    textsegment.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../build-mortal-engine-Desktop_Qt_5_15_1_MinGW_64_bit-Release/mortal-engine/release/ -lmortalengine
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../build-mortal-engine-Desktop_Qt_5_15_1_MinGW_64_bit-Debug/mortal-engine/debug/ -lmortalengine
else:unix: LIBS += -L$$PWD/../build-mortal-engine-Desktop_Qt_5_15_1_MinGW_64_bit-Release/mortal-engine/mortal-engine/ -lmortalengine

INCLUDEPATH += $$PWD/../mortal-engine/mortal-engine
DEPENDPATH += $$PWD/../mortal-engine/mortal-engine
