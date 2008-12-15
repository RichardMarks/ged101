
// CODESTYLE: v2.0

// Engine.h
// Project: Game Engine Design 101 (ENGINE)
// Author: Richard Marks

/**
 * \file Engine.h
 * \brief Master Engine - Header
 * \author Richard Marks <ccpsceo@gmail.com>
 */
#ifndef __ENGINE_H__
#define __ENGINE_H__

// device interfaces
#include "GraphicsDevice.h"
#include "AudioDevice.h"
#include "InputDevice.h"

// graphics module
#include "ImageResource.h"
#include "ImageList.h"
#include "BitmapFont.h"
#include "AnimationFrame.h"
#include "AnimationSequence.h"
#include "Tile.h"
#include "TileMap.h"
#include "ColorRGB.h"

// audio module
#include "Audio_OGG.h"

// object module
#include "GameObject.h"
#include "GameObjectGroup.h"
#include "GameObjectGroupManager.h"

// system module
#include "GameTimer.h"
#include "GameStateManager.h"
#include "NameDirectory.h"

// debugging module
#include "DebugReport.h"

// scene module
#include "Scene.h"
#include "HorizontalScrollingLayer.h"
#include "VerticalScrollingLayer.h"

// math
#include "Vector.h"

#endif


