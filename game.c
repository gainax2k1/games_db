#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"

static const char *genre_strings[] = { // for displaying enums. UPDATE WITH ENUMS IN GAME.H!
    "Unknown",
    "RPG", 
    "Puzzle", 
    "Sports", 
    "Rogue-like", 
    "Music/Rythm", 
    "Platformer"
};

static const char *platform_strings[] = { // for displaying enums. UPDATE WITH ENUMS IN GAME.H!
    "Unknown", 
    "NES", 
    "SNES", 
    "N64", 
    "GameCube", 
    "Wii", 
    "Wii U", 
    "Switch"
};

void show_genres(){
    printf("----- Genres -----\n");
    for (int i = 0; i < sizeof(genre_strings) / sizeof(genre_strings[0]); i++) {
        printf("[%u] %-12s", i, genre_strings[i]);
        if((i+1)%5 == 0) {
            printf("\n");
        }
    }
    printf("\n----------\n");
}
    

void show_platforms(){
    printf("----- Platforms -----\n");
    for (int i = 0; i < sizeof(platform_strings) / sizeof(platform_strings[0]); i++) {
        printf("[%u] %-12s", i, platform_strings[i]);
        if((i+1)%5 == 0) {
                printf("\n");
        }
    }
    printf("\n----------\n");
}


const char* genre_to_string(genre_t genre) {
    return genre_strings[genre];
}

const char* platform_to_string(platform_t platform) {
    return platform_strings[platform];
}

// Convert string to genre_t enum
genre_t string_to_genre(const char *genre_str) {
    for (int i = 0; i < sizeof(genre_strings) / sizeof(genre_strings[0]); i++) {
        if (strcasecmp(genre_str, genre_strings[i]) == 0) {  // Use strcasecmp for case-insensitive comparison
            return (genre_t)i;
        }
    }
    return GENRE_UNKNOWN;  // Default if no match found
}

// Convert string to platform_t enum
platform_t string_to_platform(const char *platform_str) {
    for (int i = 0; i < sizeof(platform_strings) / sizeof(platform_strings[0]); i++) {
        if (strcasecmp(platform_str, platform_strings[i]) == 0) {
            return (platform_t)i;
        }
    }
    return PLATFORM_UNKNOWN;  // Default if no match found
}

game_t *create_game(char *title, genre_t genre, platform_t platform){ //creates new game, returns pointer to game
    game_t *new_game = malloc(sizeof(game_t)); // allocate mem for new game
    if(new_game == NULL){ //error protection
        fprintf(stderr, "Failed to allocate memory for new game in create_game()\n");
        return NULL;
    }
    
    new_game->title = strdup(title);
    if (new_game->title == NULL) { // safety incase strdup() fails
        free(new_game);
        fprintf(stderr,"failed to register title in create_game()\n");
        return NULL;
    }

    new_game->genre = genre;
    new_game->platform = platform;
    return new_game;
}

void show_game(game_t *game){// displays formatted game info
    printf("Title: %-35.35s Genre: %-12s Platform: %-12s \n", game->title, genre_strings[game->genre], platform_strings[game->platform]);
    return;
}

void free_game(game_t *game){  // Frees memory allocated for a game
    free(game->title);
    free(game);
    return;
}