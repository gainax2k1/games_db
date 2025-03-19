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
    printf("Title: %s \n", game->title);
    printf("Genre: %s \n", genre_strings[game->genre]);
    printf("Platform: %s \n", platform_strings[game->platform]);

    return;
}

void free_game(game_t *game){  // Frees memory allocated for a game
    free(game->title);
    free(game);
    return;
}