#
# SConstruct
# scons build script

################################################################################
# these are the libraries needed to link the demos
# adjust this list for your operating system as needed.
# this list is for Ubuntu 8.04 Linux

gameLibraries = Split("""
	alleg-4.2.2
    m
    Xxf86vm
    Xcursor
    Xpm
    Xext
    X11
    pthread
    dl
    ogg
    vorbis
    vorbisfile
    engine
	""")
	
################################################################################
# these are the include directories to be searched when compiling
# adjust as needed for your operating system
# this list is for Ubuntu 8.04 Linux

gameIncludes = Split("""
	.
	./engine/include
	""")

game = ['game', 
	Split("""
	Game.cpp
	GameState_Title.cpp
	GameState_Credits.cpp
	GameState_PlayGame.cpp
	"""),
	gameLibraries,
	gameIncludes]

################################################################################
# build the game executable into the dist folder
#
# game[0] is the name of the executable
# game[1] is the list of sources to be compiled
# game[2] is the list of libraries to be linked against
# game[3] is the list of include paths to search through
#
################################################################################

buildEnv = Environment(CCFLAGS = '-g')
import os
buildEnv.Program('./dist/' + os.name + '/' + game[0], 
	game[1], 
	LIBS = game[2], 
	LIBPATH = './engine/lib/' + os.name,
	CPPPATH = game[3])

################################################################################





