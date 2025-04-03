#include <stdio.h>
#include <stdlib.h>
#include <csv.h>
#include "menu.h"
#include "game.h"
#include "hash.h"
#include "fileio.h"


void main(){

    char *main_menu_opts[] = {
        "List games",
        "Add videogame",
        "Edit videogame", 
        "Remove videogame", 
        "Save and exit"
    };

    // Try to load the database at startup
    hash_table_t *game_db = create_table(100); //default starting hash table, starting with 100b buckets
    char filename[100] = "gamesdb.csv"; // Default filename
    if(load_games(filename, game_db)) {
        printf("Loaded game database from %s\n", filename);
    } else {
        printf("No existing database found, creating new database\n");  
    }

    
    // printf("making menu!\n"); // debug flag
    size_t num_menu_items = sizeof(main_menu_opts) / sizeof(main_menu_opts[0]); // (amount of memory to store the array of pointers) divided by (amount of memory for each pointer)
    // printf("makiong menu part 2!\n"); // debug flag
    menu_t *main_menu = create_menu(main_menu_opts, num_menu_items);

    
    printf("\n----- GAME DATABASE -----\n"); // Simple header for initial home menu
    

    // ***** beginning live menu here *********
    bool running = true;
    int menu_choice;

    while(running) {
        show_menu(main_menu);
        printf("Enter your choice (0-%zu): ", num_menu_items - 1);

        if(scanf("%d", &menu_choice) != 1) {
            // Clear input buffer on invalid input
            while(getchar() != '\n');
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        // Clear any remaining newline in the input buffer
        while(getchar() != '\n');

        if(menu_choice < 0 || menu_choice >= num_menu_items) {
            printf("Invalid choice. Please try again.\n");
            continue;
        }

        switch(menu_choice) {
            case 0: // List games
                print_table(game_db);
                break;
            
            case 1: // Add videogame
                /*
                char title[100]; // for reading in new game title
                int genre, platform; // for genre/ platform.
                
                printf("Enter game title: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0; // Remove newline

                printf("Enter genre (0-RPG, 1-ACTION, 2-PLATFORMER, etc.): ");
                scanf("%d", &genre);
                while(getchar() != '\n'); // Clear buffer

                printf("Enter platform (0-NES, 1-SNES, 2-N64, etc.): ");
                scanf("%d", &platform);
                while(getchar() != '\n'); // Clear buffer

                game_t *new_game = create_game(title, genre, platform);
                if(new_game && insert_game(game_db, new_game)) {
                    printf("Added game: %s\n", title);
                } else {
                    printf("Failed to add game.\n");
                    if(new_game) free(new_game);
                
                */
                break;
;
            
            case 2: // Edit videogame
                /*
                printf("Enter title of game to edit: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0;
                
                game_t *game_to_edit = find_game(game_db, title);
                if(game_to_edit) {
                    printf("Found: %s (Genre: %d, Platform: %d)\n", 
                          game_to_edit->title, game_to_edit->genre, game_to_edit->platform);
                    
                    printf("Enter new genre (-1 to keep current): ");
                    scanf("%d", &genre);
                    while(getchar() != '\n');
                    
                    printf("Enter new platform (-1 to keep current): ");
                    scanf("%d", &platform);
                    while(getchar() != '\n');
                    
                    if(genre >= 0) game_to_edit->genre = genre;
                */
                break;
            
            case 3: // Remove game
                
                break;

            case 4: // save and exit program
                running = false;
                bool save_worked = save_games(filename, game_db);
                printf("saving db worked?:%s\n", save_worked ? "true" : "false");
                break;

            default: // don't think this can be reched?
                break;
            }
        }
    
    
    

    // i believe it's always safe to free at the end?
    free_table(game_db);
    free_menu(main_menu);
  
    printf("seemingly successfully freed table\n");
    return;
}