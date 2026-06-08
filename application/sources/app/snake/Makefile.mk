CFLAGS		+= -I./sources/app/snake
CPPFLAGS	+= -I./sources/app/snake

VPATH += sources/app/snake

# CPP source files
SOURCES_CPP += sources/app/snake/title.cpp
SOURCES_CPP += sources/app/snake/bitmap.cpp
SOURCES_CPP += sources/app/snake/game.cpp
SOURCES_CPP += sources/app/snake/options.cpp