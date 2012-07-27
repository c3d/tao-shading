# ******************************************************************************
#  shading.pro                                                      Tao project
# ******************************************************************************
# File Description:
# Qt build file for the Shading module
# ******************************************************************************
# This software is property of Taodyne SAS - Confidential
# Ce logiciel est la propriété de Taodyne SAS - Confidentiel
# (C) 2010 Jerome Forissier <jerome@taodyne.com>
# (C) 2010 Taodyne SAS
# ******************************************************************************

MODINSTDIR = shading

include(../modules.pri)

DEFINES     += GLEW_STATIC

INCLUDEPATH += $${TAOTOPSRC}/tao/include/tao/
HEADERS = \
    shading.h \
    shading_factory.h \
    cel_shading.h \
    gooch_shading.h

SOURCES = shading.cpp $${TAOTOPSRC}/tao/include/tao/GL/glew.c \
    shading_factory.cpp \
    cel_shading.cpp \
    gooch_shading.cpp

TBL_SOURCES  = shading.tbl

OTHER_FILES = shading.xl shading.tbl traces.tbl
QT          += core \
               gui \
               opengl

INSTALLS    += thismod_icon

LICENSE_FILES = shading.taokey.notsigned
include(../licenses.pri)

QMAKE_SUBSTITUTES = doc/Doxyfile.in
DOXYFILE = doc/Doxyfile
DOXYLANG = en,fr
include(../modules_doc.pri)




