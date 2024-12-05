#include "raylib.h"
#include "data_types.h"

int main(void)
{
	const int screenWidth = 1024;
	const int screenHeight = 768;

	const int game_grid_width_in_tiles = 64;
	const int game_grid_height_in_tiles = 48;

	InitWindow(screenWidth, screenHeight, "Miia the Maggot");

	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(RAYWHITE);

		//DrawText("Onneksi olkoon, sait tehtyä ensimmäisen ikkunan!", 190, 200, 20, LIGHTGRAY);

		EndDrawing();
	}
}
