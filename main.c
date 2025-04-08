#include <stdio.h>
#include <stdlib.h>
#include <csv.h>
#include "menu.h"
#include "game.h"
#include "hash.h"
#include "fileio.h"
#include "colors.h"

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

    
    printf("\n-----%s GAME DATABASE %s-----\n", STYLE_INVERSE, STYLE_RESET); // Simple header for initial home menu

    // ***** beginning live menu here *********
    bool running = true;
    int menu_choice;
                    
    char title[100]; // for reading in new game title
    int platform;
    int genre; // for genre/ platform.

    char confirm[16];
    
    while(running) {
        printf("\n-------%s MAIN MENU %s-------\n", STYLE_BOLD, STYLE_RESET);
        show_menu(main_menu);
        printf("%sEnter your choice (0-%zu): %s", STYLE_BOLD, num_menu_items - 1, STYLE_RESET);

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
                printf("\n"); // friendly blank line
                print_table(game_db);
                break;
            
            case 1: // Add videogame

                
                printf("Enter game title: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0; // Remove newline
                
                show_genres();
                printf("Enter number for genre (0-Unknown, 1-RPG, etc.): ");
                scanf("%d", &genre);
                while(getchar() != '\n'); // Clear buffer

                show_platforms();
                printf("Enter number platform (0-Unknwon, 1-NES, etc.): ");
                scanf("%d", &platform);
                while(getchar() != '\n'); // Clear buffer
                
                game_t *new_game = create_game(title, genre, platform);
                if(new_game && insert_game(game_db, new_game)) {
                    printf("Added game: %s\n", title);
                } else {
                    printf("Failed to add game.\n");
                    if(new_game) free(new_game);
                
                
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
            
            case 3:{ // Remove game
                printf("Enter title of game to remove: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0;

                game_t *game_to_remove = find_game(game_db, title);
                if(game_to_remove) {
                    printf("Found: %s (Genre: %d, Platform: %d)\n", 
                          game_to_remove->title, game_to_remove->genre, game_to_remove->platform);
                    
                    printf("%sEnter 'REMOVE' to remove (anything else will return to main menu):%s ", COLOR_RED, COLOR_WHITE);
                    scanf("%15s", confirm);
                    while(getchar() != '\n');
                    printf("%d\n", (strcmp(confirm, "REMOVE")));
                    if(strcmp(confirm, "REMOVE") == 0 ){ 
                        remove_game(game_db, game_to_remove->title);
                        break;
                    }
                    printf("Remove game cancelled\n");
                    break;
                }
                printf("Game '%s' not found.\n", title);
                break;
            }

            case 4: // save and exit program
                running = false;
                bool save_worked = save_games(filename, game_db);
                printf("saving db worked?:%s\n", save_worked ? "true" : "false");
                break;

            default: // don't think this can be reched?
                break;
            }
        }
    
    }
    

    // i believe it's always safe to free at the end?
    free_table(game_db);
    free_menu(main_menu);
  
    return;
}

