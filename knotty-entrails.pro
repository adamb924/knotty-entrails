QT -= gui
QT += xml

TEMPLATE = lib
DEFINES += KNOTTYENTRAILS_LIBRARY

CONFIG += c++11

CONFIG(debug, debug|release) {
    mac: TARGET = $$join(TARGET,,,_debug)
    win32: TARGET = $$join(TARGET,,,d)
}

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
win32:target.path = $$[QT_INSTALL_LIBS]
unix {
    target.path = /usr/lib
}
!isEmpty(target.path): INSTALLS += target

win32 {
    CONFIG(release, debug|release): LIBS += -l$$[QT_INSTALL_LIBS]/mortalengine
    CONFIG(debug, debug|release): LIBS += -l$$[QT_INSTALL_LIBS]/mortalengined
}

unix: LIBS += -L/opt/ -lmortalengine


INCLUDEPATH += $$PWD/../mortal-engine/mortal-engine
DEPENDPATH += $$PWD/../mortal-engine/mortal-engine

