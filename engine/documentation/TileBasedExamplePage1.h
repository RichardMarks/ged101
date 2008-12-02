
// CODESTYLE: v2.0

// TileBasedExamplePage1.h
// Project: Game Engine Design (ENGINE)
// Author: Richard Marks

/**
 * \file TileBasedExamplePage1.h
 * \brief Documentation

 * \page TileBasedExamplePage1 Tile-based Examples
 * In the example below, we create a simple 2D tile-map demonstration.\n
 * Please note that this is not full-source, and will not compile by itself. 
 * It is intended that you will use the code in the proper places in your project.
 *
 * \section Example1Section1 Creating a Tileset
 * First we should create a tileset. A tileset is a list of images that we can refer to by name.
 * \code

// create the Tileset instance
Tileset* ts = new Tileset();

// add a black tile that is 16x16 pixels in size as the first tile, so that maps with tiles that have a value of 0 will use the null tile
ts["null"] = new ImageResource(16, 16, ColorRGB(0, 0, 0).Get());

// add the grass tile using array-notation
ts["grass"] = new ImageResource("grass.png");

// add a dirt tile using a member-function
ts->Add("dirt", new ImageResource("dirt.png"));

// add a sand tile using a member-function
ts->Add("sand", new ImageResource("sand.png"));

// add 4 water tiles using a member-function 
// the tiles will be stored named as water0 water1 water2 water3
ts->AddRange("water", 4, 
	new ImageResource("water.png", 0, 0, 16, 16),
	new ImageResource("water.png", 16, 0, 16, 16),
	new ImageResource("water.png", 32, 0, 16, 16),
	new ImageResource("water.png", 48, 0, 16, 16));

// add 6 mountain tiles using variable-argument-function notation
ts("mountain", 6, 
	new ImageResource("mountain.png", 0, 0, 16, 16),
	new ImageResource("mountain.png", 16, 0, 16, 16),
	new ImageResource("mountain.png", 32, 0, 16, 16),
	new ImageResource("mountain.png", 48, 0, 16, 16),
	new ImageResource("mountain.png", 64, 0, 16, 16),
	new ImageResource("mountain.png", 80, 0, 16, 16));

 * \endcode
 * 
 * \section Example1Section2 Creating a TileMap
 * We need to create a tilemap. A tilemap is a 2D array of tiles that define each tile that makes up the game world.
 * \code

const int MAP_WIDTH = 10;
const int MAP_HEIGHT = 10;

TileMap* world = new TileMap(MAP_WIDTH, MAP_HEIGHT);

// get the index for our water tile
unsigned int waterIndex = ts->GetIndex("water0");

for (int y = 0; y < MAP_HEIGHT; y++)
{
	for (int x = 0; x < MAP_WIDTH; x++)
	{
		unsigned int tile = static_cast<unsigned int>(rand() % ts->Count());
		
		// if the tile value is larger than the index of the water tile, then the tile will be set to be solid.
		world->SetTile(x, y, &Tile(tile, (tile > waterIndex) ? true : false ));
	}
}

 * \endcode
 *
 * \section Example1Section3 Rendering a TileMap
 * In order to render the tilemap, we need to get a pointer to our display buffer, then create a TileMapRenderer object, then we
 * begin the scene, and tell the TileMapRenderer to render to our display buffer, and finally end the scene.
 * \code


ImageResource* display = GraphicsDevice->GetSecondaryDisplayBuffer();
 
TileMapRenderer worldRenderer(world, ts, display);

GraphicsDevice->BeginScene();

worldRenderer.Render();

GraphicsDevice->EndScene();
 * \endcode
 *
 * \section Example1Section4 Cleaning up after ourselves
 * It is important to remember to delete the pointers we allocate when we are finished using them, so that we avoid memory leaks.
 * \code
 
delete world;
delete ts;

 * \endcode
 *
 * \sa ENGINE::Tile
 * \sa ENGINE::TileMap
 * \sa ENGINE::Tileset
 * \sa ENGINE::TileMapRenderer
 * \sa ENGINE::ImageResource
 * \sa ENGINE::ColorRGB
 * \sa ENGINE::GraphicsDeviceSingleton
 *
 */

