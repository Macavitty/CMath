# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = CompMath

QT += charts

HEADERS = \
   $$PWD/algos/IntegrationSolver.h \
   $$PWD/algos/InterpolationSolver.h \
   $$PWD/algos/LinearSystemSolver.h \
   $$PWD/algos/ODESolver.h \
   $$PWD/gui/IntegrationTab.h \
   $$PWD/gui/InterpolationTab.h \
   $$PWD/gui/LAbsTabs.h \
   $$PWD/gui/LinearSystemTab.h \
   $$PWD/gui/ODETab.h \
   $$PWD/helpers/Function.h

SOURCES = \
   $$PWD/algos/IntegrationSolver.cpp \
   $$PWD/algos/InterpolationSolver.cpp \
   $$PWD/algos/LinearSystemSolver.cpp \
   $$PWD/algos/ODESolver.cpp \
   $$PWD/gui/IntegrationTab.cpp \
   $$PWD/gui/InterpolationTab.cpp \
   $$PWD/gui/LAbsTabs.cpp \
   $$PWD/gui/LinearSystemTab.cpp \
   $$PWD/gui/ODETab.cpp \
   $$PWD/helpers/Function.cpp \
   $$PWD/main.cpp \

INCLUDEPATH = \
    $$PWD/algos \
    $$PWD/gui \
    $$PWD/gui/img \
    $$PWD/gui/ico \
    $$PWD/helpers
CONFIG += qt

#DEFINES = 

DISTFILES +=

