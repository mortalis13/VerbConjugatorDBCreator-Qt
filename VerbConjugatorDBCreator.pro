#-------------------------------------------------
#
# Project created by QtCreator 2016-03-17T09:30:55
#
#-------------------------------------------------

QT       += core gui sql webkit

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += console

TARGET = VC_DBCreator
TEMPLATE = app
QMAKE_CXXFLAGS += -std=c++11


SOURCES += main.cpp\
        mainwindow.cpp\
    database.cpp\
    dbcreators/dbcreator_es.cpp \
    dbcreators/dbcreator_en.cpp \
    dbcreators/dbcreator_de.cpp \
    dbcreators/dbcreator_fr.cpp \
    dbcreators/dbcreator_it.cpp \
    dbcreators/dbcreator_la.cpp \
    dbcreators/idbcreator.cpp \
    databases/database_en.cpp \
    databases/database_es.cpp \
    databases/database_de.cpp \
    databases/database_fr.cpp \
    databases/database_it.cpp \
    databases/database_la.cpp \

HEADERS  += mainwindow.h\
database.h \
    base.h \
    dbcreators/dbcreator_es.h \
    dbcreators/dbcreator_en.h \
    dbcreators/dbcreator_de.h \
    dbcreators/dbcreator_fr.h \
    dbcreators/dbcreator_it.h \
    dbcreators/dbcreator_la.h \
    dbcreators/idbcreator.h \
    databases/database_en.h \
    databases/database_es.h \
    databases/database_de.h \
    databases/database_fr.h \
    databases/database_it.h \
    databases/database_la.h \
    verbitems/verbitem_es.h \
    verbitems/verbitem_en.h \
    verbitems/verbitem_de.h \
    verbitems/verbitem_fr.h \
    verbitems/verbitem_it.h \
    verbitems/verbitem_la.h \

FORMS    += mainwindow.ui \
