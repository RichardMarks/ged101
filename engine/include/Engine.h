
// CODESTYLE: v2.0

// Engine.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks

#ifndef __ENGINE_H__
#define __ENGINE_H__
#if 0
// add any documentation to be placed on the index page of the generated documentation here
#endif
/**
 * \mainpage
 * The Game Engine Design 101 Project. (ged101)\n\n
 * A collection of reusable classes that when used properly provide a cross-platform library of functionality to
 * implement just about any game genre you can imagine... within limits of course.\n
 * ged101 is purely 2D at this time.\n\n
 *
 * The ged101 engine is comprised of several modules that perform different functions
 * \li Graphics Module
 * \sa ENGINE::ImageResource, ENGINE::GraphicsDevice
 * \li Input Module
 * \sa ENGINE::InputDevice
 * \li Audio Module
 * \sa ENGINE::AudioSampleResource_OGG, ENGINE::AudioStreamResource_OGG
 * \li Object Module
 * \sa ENGINE::GameObject, ENGINE::GameObjectGroup, ENGINE::GameObjectGroupManager
 * \li System Module
 * \sa DEBUG::DebugReport, DEBUG::DebugReportInfo 
 */

#if 0
// add any documentation for the namespaces here
#endif
/**
 * \namespace ALBASE
 * \brief Initializes Allegro and handles setting up the main game instance.
 */

/** 
 * \namespace DEBUG
 * \brief Project Debugging Utility Library - Reusable error reporting classes and constants.
 */

/**
 * \namespace ENGINE
 * \brief The entire library of classes and constants that make up the ged101 engine.
 */

/**
 * \namespace GAME
 * \brief All the classes that make up your game. You are responsible for implementing all of this.
 */




// include the ged101 headers
#include "DebugReport.h"
#include "InputManager.h"
#include "CommunicationDevice.h"
#include "Audio.h"
#include "ImageResource.h"
#include "GameTimer.h"
#include "GameObject.h"
#include "GameObjectGroup.h"
#include "GameObjectGroupManager.h"
#include "GameStateManager.h"

#endif

