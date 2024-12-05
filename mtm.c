#include "raylib.h"
#include "data_types.h"
#include <stdlib.h>
#include <time.h>

// Global variables
int score = 0;
const int max_score = 10;
game_status status = RUNNING;

int getRandomInt(int min, int max)
{
	return (rand() % max) + min;
}

// Initialize the game grid with empty tiles and walls. Player and goal tiles are not added here.
void initialize_game_grid(game_tile game_grid[][48], int width, int height)
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			game_grid[x][y].x = x;
			game_grid[x][y].y = y;
			if (y < 2)
			{
				game_grid[x][y].type = EMPTY;
			}
			else
			{
				game_grid[x][y].type = GRASS;
			}
		}
	}

	// Add walls
	for (int x = 0; x < width; x++)
	{
		game_grid[x][2].type = WALL; // Uppermost wall just below the EMPTY tiles
		game_grid[x][height - 1].type = WALL;
	}

	for (int y = 2; y < height; y++)
	{
		game_grid[0][y].type = WALL;
		game_grid[width - 1][y].type = WALL;
	}
}

void update_grid(game_tile game_grid[][48], player_head *player)
{
	// get current x and y
	int previous_x = player->x;
	int previous_y = player->y;

	// Move the player
	switch (player->direction)
	{
	case UP:
		player->y--;
		break;
	case DOWN:
		player->y++;
		break;
	case LEFT:
		player->x--;
		break;
	case RIGHT:
		player->x++;
		break;
	}

	// if hit wall or body, game over
	if (game_grid[player->x][player->y].type == WALL || game_grid[player->x][player->y].type == PLAYER_BODY)
	{
		TraceLog(LOG_INFO, "Game over. Hit wall or body");
		status = GAME_OVER;
	}
	// check if player has reached the goal
	else if (game_grid[player->x][player->y].type == GOAL)
	{
		score++;
		if (score == max_score)
		{
			status = WIN;
		}
		else
		{
			if (player->next == NULL) {
				player_body *new_body = (player_body *)malloc(sizeof(player_body));
				new_body->x = previous_x;
				new_body->y = previous_y;
				new_body->next = NULL;
				player->next = new_body;
			} 
			// else {
			// 	player_body *current = player->next;
			// 	while (current->next != NULL)
			// 	{
			// 		current = current->next;
			// 	}

			// 	player_body *new_body = (player_body *)malloc(sizeof(player_body));
			// 	new_body->x = current->x;
			// 	new_body->y = current->y;
			// 	new_body->next = NULL;
			// 	current->next = new_body;
			// }

			// // find the last body part
			// player_body *current = player->next;
			// while (current->next != NULL)
			// {
			// 	current = current->next;

			// 	player_body *new_body = (player_body *)malloc(sizeof(player_body));
			// 	new_body->x = previous_x;
			// 	new_body->y = previous_y;
			// 	new_body->next = NULL;
			// 	player->next = new_body;
			// }
		}
	}

	// set player's new position to grid
	game_grid[player->x][player->y].type = PLAYER_HEAD;

	// set previous position to GRASS
	game_grid[previous_x][previous_y].type = GRASS;
}

void check_goal_and_add_if_missing(game_tile game_grid[][48], int game_grid_width_in_tiles, int game_grid_height_in_tiles)
{
	// Check if goal is present
	bool goal_present = false;
	for (int x = 0; x < game_grid_width_in_tiles; x++)
	{
		for (int y = 0; y < game_grid_height_in_tiles; y++)
		{
			if (game_grid[x][y].type == GOAL)
			{
				goal_present = true;
				break;
			}
		}
	}

	// If goal is not present, add it
	while (!goal_present)
	{
		int goal_x = getRandomInt(1, game_grid_width_in_tiles - 1);
		int goal_y = getRandomInt(3, game_grid_height_in_tiles - 1);

		if (game_grid[goal_x][goal_y].type == GRASS)
		{
			goal_present = true;
		}

		game_grid[goal_x][goal_y].type = GOAL;
	}
}

int main(void)
{
	const int screenWidth = 1024;
	const int screenHeight = 768;

	const int game_grid_width_in_tiles = 64;
	const int game_grid_height_in_tiles = 48;

	const int game_area_actual_width = 1024;

	const int tile_width = screenWidth / game_grid_width_in_tiles;
	const int tile_height = screenHeight / game_grid_height_in_tiles;

	// Declare a fixed-size 2D array
	game_tile game_grid[game_grid_width_in_tiles][game_grid_height_in_tiles];

	initialize_game_grid(game_grid, game_grid_width_in_tiles, game_grid_height_in_tiles);

	// initialize player
	// todo: randomize start position etc.
	player_head player = {5, 5, RIGHT, NULL};
	game_grid[player.x][player.y].type = PLAYER_HEAD;

	srand(time(NULL));

	InitWindow(screenWidth, screenHeight, "Miia the Maggot");

	// Load the grass texture
	Texture2D grassTexture = LoadTexture("grass_1.png");
	// Load the goal texture
	Texture2D goalTexture = LoadTexture("goal_1.png");

	SetTargetFPS(60);

	double seconds_elapsed = 0.0;
	const double increment_seconds = 0.1;

	while (!WindowShouldClose())
	{
		// check game status. If game over or win, break out of the loop
		if (status == GAME_OVER || status == WIN)
		{
			break;
		}

		// if goal is not present, add it
		check_goal_and_add_if_missing(game_grid, game_grid_width_in_tiles, game_grid_height_in_tiles);

		// Listen for direction keys and prevent 180-degree turns
		if (IsKeyDown(KEY_UP) && player.direction != DOWN)
		{
			TraceLog(LOG_INFO, "Up. Player direction: %d", player.direction);
			player.direction = UP;
		}
		if (IsKeyDown(KEY_DOWN) && player.direction != UP)
		{
			TraceLog(LOG_INFO, "Down. Player direction: %d", player.direction);
			player.direction = DOWN;
		}
		if (IsKeyDown(KEY_LEFT) && player.direction != RIGHT)
		{
			TraceLog(LOG_INFO, "Left. Player direction: %d", player.direction);
			player.direction = LEFT;
		}
		if (IsKeyDown(KEY_RIGHT) && player.direction != LEFT)
		{
			TraceLog(LOG_INFO, "Right. Player direction: %d", player.direction);
			player.direction = RIGHT;
		}

		// Update the game state based on the elapsed time
		seconds_elapsed += GetFrameTime();
		if (seconds_elapsed > 0.05)
		{
			seconds_elapsed = 0.0;
			update_grid(game_grid, &player);
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);

		// Draw the background texture
		DrawTexture(grassTexture, 0, 0, WHITE);

		// Draw the game grid. Currently just use colors to fill the tiles. Empty is light green, wall is brown.
		for (int x = 0; x < game_grid_width_in_tiles; x++)
		{
			for (int y = 0; y < game_grid_height_in_tiles; y++)
			{
				switch (game_grid[x][y].type)
				{
				case EMPTY:
					DrawRectangle(x * tile_width, y * tile_height, tile_width, tile_height, BLACK);
					break;
				case GRASS:
					DrawTexture(grassTexture, x * tile_width, y * tile_height, WHITE);
					break;
				case WALL:
					DrawRectangle(x * tile_width, y * tile_height, tile_width, tile_height, BROWN);
					break;
				case PLAYER_HEAD:
					DrawRectangle(x * tile_width, y * tile_height, tile_width, tile_height, BLUE);
					break;
				case PLAYER_BODY:
					DrawRectangle(x * tile_width, y * tile_height, tile_width, tile_height, BLUE);
					break;
				case GOAL:
					// DrawRectangle(x * tile_width, y * tile_height, tile_width, tile_height, RED);
					DrawTexture(goalTexture, x * tile_width, y * tile_height, WHITE);
					break;
				}
			}
		}
		const char *text = TextFormat("Score %d/%d", score, max_score);
		DrawText(text, 190, 5, 20, LIGHTGRAY);
		EndDrawing();
	}

	// if game over, show game over screen
	if (status == GAME_OVER)
	{
		// todo: show popup game over
	}
	else if (status == WIN)
	{
		// todo: transform maggot to butterfly
	}
}
