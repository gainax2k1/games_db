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
        "Save and exit",
        "Exit without saving"
    };

    char *edit_menu_opts[] = {
        "Change name",
        "Change genre",
        "Change platform",
        "Return to Maine Menu"
    };
    
    // Try to load the database at startup
    hash_table_t *game_db = create_table(100); //default starting hash table, starting with 100b buckets
    char filename[100] = "gamesdb.csv"; // Default filename
    if(load_games(filename, game_db)) {
        printf("Loaded game database from %s\n", filename);
    } else {
        printf("No existing database found, creating new database\n");  
    }

    
    // setting up main menu
    size_t main_menu_items = sizeof(main_menu_opts) / sizeof(main_menu_opts[0]); // (amount of memory to store the array of pointers) divided by (amount of memory for each pointer)
    menu_t *main_menu = create_menu(main_menu_opts, main_menu_items);

    // setting up edit game menu
    size_t edit_menu_items = sizeof(edit_menu_opts) / sizeof(edit_menu_opts[0]); 
    menu_t *edit_menu = create_menu(edit_menu_opts, edit_menu_items);
    
    printf("\n-----%s GAME DATABASE %s-----\n", STYLE_INVERSE, STYLE_RESET); // Simple header for initial home menu

    // ***** beginning live menu here *********
    bool running_main = true;
    bool running_edit = true;
    int menu_choice; // main menu
    int edit_choice; // edit menu
                    
    char title[100]; // for reading in new game title
    int platform;
    int genre; // for genre/ platform.

    char confirm[16];
    
    while(running_main) {
        printf("\n-------%s MAIN MENU %s-------\n", STYLE_BOLD, STYLE_RESET);
        show_menu(main_menu);
        printf("%sEnter your choice (0-%zu): %s", STYLE_BOLD, main_menu_items - 1, STYLE_RESET);

        if(scanf("%d", &menu_choice) != 1) {
            // Clear input buffer on invalid input
            while(getchar() != '\n');
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        // Clear any remaining newline in the input buffer
        while(getchar() != '\n');

        if(menu_choice < 0 || menu_choice >= main_menu_items) {
            printf("Invalid choice. Please try again.\n");
            continue;
        }

        switch(menu_choice) {
            
            case 0: // List games
                
                printf("\n-------%s GAMES LIST %s-------\n", STYLE_BOLD, STYLE_RESET);
                printf("\n"); // friendly blank line
                print_table(game_db);
                break;
            
            case 1: // Add videogame

                
                printf("\n-------%s ADD GAME %s-------\n", STYLE_BOLD, STYLE_RESET);
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
                
                printf("\n-------%s EDIT GAME %s-------\n", STYLE_BOLD, STYLE_RESET);

                printf("\nEnter title of game to edit: ");
                fgets(title, sizeof(title), stdin);
                title[strcspn(title, "\n")] = 0;
                
                game_t *game_to_edit = find_game(game_db, title);
                if(game_to_edit) {
                    printf("Found-\n");
                    show_game(game_to_edit);
                } else {
                    printf("%s not found.\n", title);
                    break;
                }
                while(running_edit){

                    // BEGIN EDIT MENU
                show_menu(edit_menu);
                printf("%sEnter your choice (0-%zu): %s", STYLE_BOLD, edit_menu_items - 1, STYLE_RESET);

                if(scanf("%d", &edit_choice) != 1) {
                    // Clear input buffer on invalid input
                    while(getchar() != '\n');
                    printf("Invalid input. Please enter a number.\n");
                    continue;
                }
        
                // Clear any remaining newline in the input buffer
                while(getchar() != '\n');
        
                if(edit_choice < 0 || edit_choice >= edit_menu_items) {
                    printf("Invalid choice. Please try again.\n");
                    continue;
                }

                switch(edit_choice) {
            
                    case 0: // Change name
                        printf("Enter new game title: ");
                        fgets(title, sizeof(title), stdin);
                        title[strcspn(title, "\n")] = 0; // Remove newline
                        
                        //process name change here ***********************
                        genre = game_to_edit->genre;// copy old genre
                        platform = game_to_edit->platform; // copy old platform
                        game_t *new_game = create_game(title, genre, platform);
                        if(new_game && insert_game(game_db, new_game)) {
                            printf("Updated title: %s\n", title);
                            remove_game(game_db, game_to_edit->title); // game successfully "edited", free old version
                        } else {
                            printf("Failed to edit game title.\n");
                            free_game(new_game); // free "new" game info, leave existing as-is
                            break;
                        }

                        break;
                        

                    case 1: // Change Genre
                        show_genres();
                        printf("Enter number for genre (0-Unknown, 1-RPG, etc.): ");
                        scanf("%d", &genre);
                        while(getchar() != '\n'); // Clear buffer
                        
                        //process genre change here ***********************
                        game_to_edit->genre = genre; 
                        break;

                    case 2: // Change Platform
                        show_platforms();
                        printf("Enter number platform (0-Unknwon, 1-NES, etc.): ");
                        scanf("%d", &platform);
                        while(getchar() != '\n'); // Clear buffer
                        //process platform change here ***********************
                        game_to_edit->platform = platform;
                        break;

                    case 3: // return to main
                        running_edit = false;
                        break;
                    
                    default: 
                        break;
                } 
                
                }
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
                running_main = false;
                bool save_worked = save_games(filename, game_db);
                printf("saving db worked?:%s\n", save_worked ? "true" : "false");
                break;

            case 5: // exit without saving
                printf("\nExiting without saving...\n");
                running_main = false;
                break;

            default: // don't think this can be reched?
                break;
            }
        }
    
    }

    // Free all the things
    free_table(game_db);
    free_menu(main_menu);
    free_menu(edit_menu);
  
    return;
}

