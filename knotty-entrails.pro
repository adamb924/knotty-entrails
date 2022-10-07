QT -= gui
QT += xml

TEMPLATE = lib
DEFINES += KNOTTYENTRAILS_LIBRARY

CONFIG += c++11

SOURCES += \
    abstractparsedform.cpp \
    abstractparserlog.cpp \
    abstracttextadapter.cpp \
    abstracttextitem.cpp \
    abstracttextparser.cpp \
    abstracttextsegment.cpp \
    documenttokenizer.cpp \
    domparsedform.cpp \
    domtextitem.cpp \
    domtextsegment.cpp \
    parsedform.cpp \
    simpleparserlog.cpp \
    simpletextadapter.cpp \
    simpletextparser.cpp \
    textitem.cpp \
    textsegment.cpp \
    xmldocumentmodel.cpp \
    xmldocumentmodellevel.cpp \
    xmldocumentposition.cpp

HEADERS += \
    abstractparsedform.h \
    abstractparserlog.h \
    abstracttextadapter.h \
    abstracttextitem.h \
    abstracttextparser.h \
    abstracttextsegment.h \
    documenttokenizer.h \
    domparsedform.h \
    domtextitem.h \
    domtextsegment.h \
    knotty-entrails_global.h \
    parsedform.h \
    simpleparserlog.h \
    simpletextadapter.h \
    simpletextparser.h \
    textitem.h \
    textsegment.h \
    xmldocumentmodel.h \
    xmldocumentmodellevel.h \
    xmldocumentposition.h

# Default rules for deployment.
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target


win32-g++ {
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../build-mortal-engine-Desktop_Qt_5_15_1_MinGW_64_bit-Release/mortal-engine/release/ -lmortalengine
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../build-mortal-engine-Desktop_Qt_5_15_1_MinGW_64_bit-Debug/mortal-engine/debug/ -lmortalengine
    else:unix: LIBS += -L$$OUT_PWD/../build-mortal-engine-Desktop_Qt_5_15_1_MinGW_64_bit/mortal-engine/ -lmortalengine
}

win32-msvc* {
    win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../build-mortal-engine-Desktop_Qt_5_15_1_MSVC2019_64bit-Release/mortal-engine/release/ -lmortalengine
    else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../build-mortal-engine-Desktop_Qt_5_15_1_MSVC2019_64bit-Debug/mortal-engine/debug/ -lmortalengine
    else:unix: LIBS += -L$$OUT_PWD/../build-mortal-engine-Desktop_Qt_5_15_1_MSVC2019_64bit/mortal-engine/ -lmortalengine
}

INCLUDEPATH += $$PWD/../mortal-engine/mortal-engine
DEPENDPATH += $$PWD/../mortal-engine/mortal-engine
