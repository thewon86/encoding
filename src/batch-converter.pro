#-------------------------------------------------
#
# Project created by QtCreator 2014-11-14T11:27:04
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#TARGET = batch-converter
TEMPLATE = app
DEFINES += _MAPPDEBUG CONF_XML#CONF_INI#

SOURCES += main.cpp\
		   dialog.cpp \
    identifyencoding.cpp \
    mlistwidget.cpp

HEADERS  += dialog.h \
    identifyencoding.h \
    mlistwidget.h \
    mtypesdef.h \
    mappver.h

FORMS    +=

APPVERSION = 1.0.2
message("APP VERSION $${APPVERSION} $${VERSION}")
CONFIG(debug, debug|release) {
	TARGET = debug-converter-$${APPVERSION}
} else {
	TARGET = release-converter-$${APPVERSION}
}

RC_FILE += res/icon.rc

OTHER_FILES += \
    res/icon.rc
