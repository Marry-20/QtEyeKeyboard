QT       += core gui qml quickwidgets charts  sql texttospeech
#QT += declarative

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
COPIES += python
python.files = someFunction.py
python.path = $$OUT_PWD
CONFIG += c++11
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
#INCLUDEPATH += C:/Users/mirbagherim_admin/anaconda3/Lib/site-packages/nltk
INCLUDEPATH += C:/Users/mirbagherim/Downloads/boost_1_76_0/boost_1_76_0/
INCLUDEPATH += C:/Users/mirbagherim/Downloads/tet-cpp-client-master/tet-cpp-client-master/src/
LIBS += "-LC:/Users/mirbagherim/Downloads/boost_1_76_0/boost_1_76_0/stage/lib/"

SOURCES += \
    ../tet-cpp-client-master/tet-cpp-client-master/src/gazeapi.cpp \
    ../tet-cpp-client-master/tet-cpp-client-master/src/gazeapi_parser.cpp \
    ../tet-cpp-client-master/tet-cpp-client-master/src/gazeapi_socket.cpp \
    main.cpp \
    mainwindow.cpp \
    mygaze.cpp \
    scrape.cpp \
    sqlcontactmodel.cpp \
    sqlconversationmodel.cpp \
    widget.cpp

HEADERS += \
    ../tet-cpp-client-master/tet-cpp-client-master/include/gazeapi.h \
    ../tet-cpp-client-master/tet-cpp-client-master/include/gazeapi_interfaces.h \
    ../tet-cpp-client-master/tet-cpp-client-master/include/gazeapi_types.h \
    ../tet-cpp-client-master/tet-cpp-client-master/src/gazeapi.hpp\
    ../tet-cpp-client-master/tet-cpp-client-master/src/gazeapi_parser.hpp \
    ../tet-cpp-client-master/tet-cpp-client-master/src/gazeapi_socket.hpp \
    mainwindow.h \
    mygaze.h \
    scrape.h \
    sqlcontactmodel.h \
    sqlconversationmodel.h \
    widget.h

#FORMS += \
 #   mainwindow.ui

RESOURCES += \
     qml.qrc \
     shared/shared.qrc

DISTFILES += \
    someFunction.py

