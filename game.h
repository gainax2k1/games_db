#pragma once // compiler directive to only include once, even if included elsewhere
#include <stddef.h>

typedef enum Genre { // genres, to be expanded manually as neccessary
    GENRE_UNKNOWN,
    GENRE_RPG,
    GENRE_PUZZLE,
    GENRE_SPORTS,
    GENRE_ROGUE,
    GENRE_MUSIC,
    GENRE_PLATFORMER,
} genre_t;

typedef enum Platform{ // more to be added, starting with Nintendo only
    PLATFORM_UNKNOWN,
    PLATFORM_NES,
    PLATFORM_SNES,
    PLATFORM_N64,
    PLATFORM_GC,
    PLATFORM_WII,
    PLATFORM_WIIU,
    PLATFORM_SWITCH,
} platform_t;

const char* genre_to_string(genre_t genre);
const char* platform_to_string(platform_t platform);

// Convert string to genre enum
genre_t string_to_genre(const char *genre_str);

// Convert string to platform enum
platform_t string_to_platform(const char *platform_str);

typedef struct Game {
    genre_t genre;
    platform_t platform;
    char *title; 
} game_t;

game_t *create_game(char *title, genre_t genre, platform_t platform); //creates new game, returns pointer to game
void show_game(game_t *game); // displays formatted game info
void free_game(game_t *game);  // Frees memory allocated for a game