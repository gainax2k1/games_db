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
    GENRE_FPS,
    GENRE_STRAT,
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
    PLATFORM_GB,
    PLATFORM_GBC,
    PLATFORM_VBOY,
    PLATFORM_GBA,
    PLATFORM_DS,
    PLATFORM_DSI,
    PLATFORM_3DS,
    PLATFORM_PS1,
    PLATFORM_PS2,
    PLATFORM_PS3,
    PLATFORM_PS4,
    PLATFORM_PS5,
    PLATFORM_PSP,
    PLATFORM_VITA,
    PLATFORM_XBOX,
    PLATFORM_360,
    PLATFORM_ONE,
    PLATFORM_SERIES,
    PLATFORM_GENESIS,
    PLATFORM_SEGACD,
    PLATFORM_32X,
    PLATFORM_SATURN,
    PLATFORM_DC,

} platform_t;

const char* genre_to_string(genre_t genre);
const char* platform_to_string(platform_t platform);

// displays enumerated list of genres
void show_genres();

// displays enumerated list of platforms
void show_platforms();

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