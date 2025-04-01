#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "game.h"
#include "hash.h"
#include "fileio.h"

void main(){

    char *main_menu_opts[] = {
        "Add videogame",
        "Edit videogame", 
        "Remove videogame", 
        "List games", 
        "Option", 
        "another option with longer name", 
        "op1", 
        "op2", 
        "op3", 
        "op4"
    };
    // more to come included "Find videogame", "Sort videogames", and ?
    printf("making menu!\n");
    size_t num_menu_items = sizeof(main_menu_opts) / sizeof(main_menu_opts[0]); // (amount of memory to store the array of pointers) divided by (amount of memory for each pointer)

    printf("makiong menu part 2!\n");
    menu_t *main_menu = create_menu(main_menu_opts, num_menu_items);

    printf("showing menu!\n");
    show_menu(main_menu);

/* ROUGH outline plan for user input

    int running = 1;
    int choice;
    char title[100];
    int genre, platform;
    char filename[100] = "gamesdb.csv"; // Default filename
    
    // Try to load the database at startup
    if(load_games(filename, game_db)) {
        printf("Loaded game database from %s\n", filename);
    }
    
    while(running) {
        printf("\n----- GAME DATABASE -----\n");
        show_menu(main_menu);
        printf("Enter your choice (0-%zu): ", num_menu_items - 1);
        
        if(scanf("%d", &choice) != 1) {
            // Clear input buffer on invalid input
            while(getchar() != '\n');
            printf("Invalid input. Please enter a number.\n");
            continue;
        }
        
        // Clear any remaining newline in the input buffer
        while(getchar() != '\n');
        
        if(choice < 0 || choice >= num_menu_items) {
            printf("Invalid choice. Please try again.\n");
            continue;
        }
        
        switch(choice) {
            case 0: // Add videogame
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
            }
            break;
            
        case 1: // Edit videogame
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
































    /*
    printf("creating game!\n");
    game_t *test_game = create_game("Zelda", GENRE_RPG, PLATFORM_SNES);
    printf("creating game!\n");
    game_t *test_game2 = create_game("Final Fantasy II", GENRE_RPG, PLATFORM_SNES);
    printf("creating game!\n");
    game_t *test_game3 = create_game("Tetris", GENRE_PUZZLE, PLATFORM_NES);
    printf("creating game!\n");
    game_t *test_game4 = create_game("Viewtiful Joe", GENRE_PLATFORMER, PLATFORM_GC);
    printf("creating game!\n");
    game_t *test_game5 = create_game("Mario 64", GENRE_PLATFORMER, PLATFORM_N64);
    printf("creating game!\n");
*/

    hash_table_t *test_table = create_table(1);
    bool load_worked = load_games("gamesdb.csv", test_table);

    /*
    printf("adding game to hash!\n");
    if(insert_game(test_table, test_game)){
        printf("game insert worked!\n");
        }
    printf("adding game to hash!\n");
    if(insert_game(test_table, test_game2)){
        printf("game insert worked!\n");
        }
    if(insert_game(test_table, test_game3)){
        printf("game insert worked!\n");
        }
    if(insert_game(test_table, test_game4)){
        printf("game insert worked!\n");
        }
    if(insert_game(test_table, test_game5)){
        printf("game insert worked!\n");
        }
        
    printf("printing hash!\n");
    print_table(test_table);

    bool remove_worked = remove_game(test_table, "Mario 64");
    printf("remove worked? %s\n", remove_worked ? "true" : "false");
    */

    print_table(test_table);
    
    bool save_worked = save_games("gamesdb.csv", test_table);

    printf("saving db worked?:%s\n", save_worked ? "true" : "false");
    free_table(test_table);
    free_menu(main_menu);
  
    printf("seemingly successfully freed table\n");
    return;
}