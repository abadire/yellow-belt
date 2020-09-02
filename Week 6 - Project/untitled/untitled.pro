TEMPLATE = app
QMAKE_CXXFLAGS += -DLOCAL
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../a.cpp \
    ../condition_parser.cpp \
    ../condition_parser_test.cpp \
    ../database.cpp \
    ../database_test.cpp \
    ../date.cpp \
    ../date_test.cpp \
    ../node.cpp \
    ../token.cpp

DISTFILES += \
    ../Project.rar \
    ../Week 6 - Project.rar \
    ../a.exe \
    ../input.txt \
    ../output.txt \
    .gitignore

HEADERS += \
    ../condition_parser.h \
    ../database.h \
    ../date.h \
    ../node.h \
    ../test_db.h \
    ../test_runner.h \
    ../token.h
