cmake_minimum_required(VERSION 3.16)

project(knotty-entrails LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_DEBUG_POSTFIX d)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets Sql Xml)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets Sql Xml)

add_library(knotty-entrails SHARED
    abstractparsedform.cpp 
    abstractparserlog.cpp 
    abstracttextadapter.cpp 
    abstracttextitem.cpp 
    abstracttextparser.cpp 
    abstracttextsegment.cpp 
    documenttokenizer.cpp 
    domparsedform.cpp 
    domtextitem.cpp 
    domtextsegment.cpp 
    parsedform.cpp 
    simpleparserlog.cpp 
    simpletextadapter.cpp 
    simpletextparser.cpp 
    textitem.cpp 
    textsegment.cpp 
    xmldocumentmodel.cpp 
    xmldocumentmodellevel.cpp 
    xmldocumentposition.cpp
)

# Use generator expressions to add the "d" suffix in Debug mode
find_library(MORTALENGINE_LIB_RELEASE NAMES mortalengine)
find_library(MORTALENGINE_LIB_DEBUG NAMES mortalengined)

message(STATUS "MORTALENGINE_LIB_RELEASE = ${MORTALENGINE_LIB_RELEASE}")
message(STATUS "MORTALENGINE_LIB_DEBUG = ${MORTALENGINE_LIB_DEBUG}")

target_include_directories(knotty-entrails
    PUBLIC
    ${CMAKE_SOURCE_DIR}/rude-mechanicals
    ${CMAKE_SOURCE_DIR}/rude-mechanicals/tagform
    ${CMAKE_PREFIX_PATH}/include/mortal-engine
)

target_link_libraries(knotty-entrails PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
    Qt${QT_VERSION_MAJOR}::Xml
    $<$<CONFIG:Debug>:${MORTALENGINE_LIB_DEBUG}>
    $<$<NOT:$<CONFIG:Debug>>:${MORTALENGINE_LIB_RELEASE}> )

target_compile_definitions(knotty-entrails PRIVATE KNOTTYENTRAILS_LIBRARY)

install(TARGETS knotty-entrails
    LIBRARY DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
    RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin
    ARCHIVE DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
)

# this installs some non-public headers, but so be it
install(DIRECTORY "${CMAKE_SOURCE_DIR}/knotty-entrails"
        DESTINATION ${CMAKE_INSTALL_PREFIX}/include
        FILES_MATCHING
        PATTERN "*.h"
)
