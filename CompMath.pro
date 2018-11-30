#TARGET = CompMath

QT += charts
requires(qtConfig(combobox))

HEADERS = \
   $$PWD/algos/IntegrationSolver.h \
   $$PWD/algos/ApproximationSolver.h \
   $$PWD/algos/LinearSystemSolver.h \
   $$PWD/algos/ODESolver.h \
   $$PWD/gui/IntegrationTab.h \
   $$PWD/gui/ApproximationTab.h \
   $$PWD/gui/LabsTabs.h \
   $$PWD/gui/LinearSystemTab.h \
   $$PWD/gui/ODETab.h \
   $$PWD/helpers/Function.h

SOURCES = \
   $$PWD/algos/IntegrationSolver.cpp \
   $$PWD/algos/ApproximationSolver.cpp \
   $$PWD/algos/LinearSystemSolver.cpp \
   $$PWD/algos/ODESolver.cpp \
   $$PWD/gui/IntegrationTab.cpp \
   $$PWD/gui/ApproximationTab.cpp \
   $$PWD/gui/LabsTabs.cpp \
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

DISTFILES +=

