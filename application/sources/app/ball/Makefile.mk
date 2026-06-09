CFLAGS		+= -I./sources/app/ball
CPPFLAGS	+= -I./sources/app/ball

VPATH += sources/app/ball

# CPP source files
SOURCES_CPP += sources/app/ball/title.cpp
SOURCES_CPP += sources/app/ball/bitmap.cpp
SOURCES_CPP += sources/app/ball/game.cpp
SOURCES_CPP += sources/app/ball/options.cpp