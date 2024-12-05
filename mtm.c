#include "raylib.h"
#include "data_types.h"

// Initialize the game grid with empty tiles and walls. Player and goal tiles are not added here.
void initialize_game_grid(game_tile game_grid[][48], int width, int height)
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			game_grid[x][y].x = x;
			game_grid[x][y].y = y;
			game_grid[x][y].type = EMPTY;
		}
	}
	
	// Add walls
	for (int x = 0; x < width; x++)
	{
		game_grid[x][0].type = WALL;
		game_grid[x][height - 1].type = WALL;
	}
	
	for (int y = 0; y < height; y++)
	{
		game_grid[0][y].type = WALL;
		game_grid[width - 1][y].type = WALL;
	}		
}

int main(void)
{
	const int screenWidth = 1024;
	const int screenHeight = 768;

	const int game_grid_width_in_tiles = 64;
	const int game_grid_height_in_tiles = 48;
	
	const int tile_width = screenWidth / game_grid_width_in_tiles;
	const int tile_height = screenHeight / game_grid_height_in_tiles;
	
	// Declare a fixed-size 2D array
    game_tile game_grid[game_grid_width_in_tiles][game_grid_height_in_tiles];

	initialize_game_grid(game_grid, game_grid_width_in_tiles, game_grid_height_in_tiles);
	
	InitWindow(screenWidth, screenHeight, "Miia the Maggot");

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		//DrawText("Onneksi olkoon, sait tehtyä ensimmäisen ikkunan!", 190, 200, 20, LIGHTGRAY);

		// Draw the game grid. Currently just use colors to fill the tiles. Empty is light green, wall is brown.
		for (int x = 0; x < game_grid_width_in_tiles; x++)
		{
			for (int y = 0; y < game_grid_height_in_tiles; y++)
			{
				switch (game_grid[x][y].type)
				{
					case EMPTY:
						DrawRectangle(x * tile_width, y * tile_height, tile_width, tile_height, GREEN);
						break;
					case WALL:
						DrawRectangle(x * tile_width, y * tile_height, tile_width, tile_height, BROWN);
						break;
					case PLAYER:
						DrawRectangle(x * tile_width, y * tile_height, tile_width, tile_height, BLUE);
						break;
					case GOAL:
						DrawRectangle(x * tile_width, y * tile_height, tile_width, tile_height, RED);
						break;
				}
			}
		}
		EndDrawing();

		// wait for 500ms
		WaitTime(0.5);

	}
}
