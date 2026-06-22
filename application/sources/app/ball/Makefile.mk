CFLAGS		+= -I./sources/app/ball
CPPFLAGS	+= -I./sources/app/ball

VPATH += sources/app/ball

# CPP source files
SOURCES_CPP += sources/app/ball/scr_title.cpp
SOURCES_CPP += sources/app/ball/bitmap.cpp
SOURCES_CPP += sources/app/ball/scr_game.cpp
SOURCES_CPP += sources/app/ball/scr_settings.cpp
SOURCES_CPP += sources/app/ball/scr_game_over.cpp