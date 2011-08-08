# ******************************************************************************
#  hello_world.pro                                                  Tao project
# ******************************************************************************
# File Description:
# Qt build file for the Hello World module
# ******************************************************************************
# This software is property of Taodyne SAS - Confidential
# Ce logiciel est la propriété de Taodyne SAS - Confidentiel
# (C) 2010 Jerome Forissier <jerome@taodyne.com>
# (C) 2010 Taodyne SAS
# ******************************************************************************

MODINSTDIR = shading

include(../modules.pri)

OTHER_FILES = shading.xl

INSTALLS    -= thismod_bin
INSTALLS    += thismod_icon
