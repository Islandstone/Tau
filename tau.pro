######################################################################
# Automatically generated by qmake (2.01a) s�n. okt. 14 15:42:42 2012
######################################################################

QT += opengl
CONFIG += debug

TEMPLATE = app
TARGET = 
DEPENDPATH += . include interface src src/engine 
INCLUDEPATH += . include interface src src/include

# Input
HEADERS += include/base.h \
           include/engine.h \
           include/game_systems.h \
           include/window.h \
           interface/input.h \
           interface/sound.h \
           interface/timer.h \
		   include/vector.h \
		   src/include/blob.h \
		   interface/physics.h

SOURCES += src/blob.cpp \
           src/game.cpp \
           src/player.cpp \
           src/engine/engine.cpp \
           src/engine/input.cpp \
           src/engine/main.cpp \
           src/engine/sound.cpp \
           src/engine/timer.cpp \
           src/engine/physics.cpp \
           src/engine/window.cpp \
		   src/engine/console.cpp

LIBS += -lrt -lGLU

OBJECTS_DIR = .obj

#Release:DESTDIR = release
#Release:OBJECTS_DIR = release/.obj
#Release:MOC_DIR = release/.moc
#Release:RCC_DIR = release/.rcc
#Release:UI_DIR = release/.ui
#
#Debug:DESTDIR = debug
#Debug:OBJECTS_DIR = debug/.obj
#Debug:MOC_DIR = debug/.moc
#Debug:RCC_DIR = debug/.rcc
#Debug:UI_DIR = debug/.ui
