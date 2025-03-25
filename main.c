#include <stdio.h>
#include <stdlib.h>
#include "menu.h"
#include "game.h"
#include "hash.h"

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
    size_t num_menu_items = sizeof(main_menu_opts) / sizeof(main_menu_opts[0]);

    printf("makiong menu part 2!\n");
    menu_t *main_menu = create_menu(main_menu_opts, num_menu_items);

    printf("showing menu!\n");
    show_menu(main_menu);

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

    hash_table_t *test_table = create_table(10);

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

    print_table(test_table);
    free_table(test_table);
    free_menu(main_menu);
  
    printf("seemingly successfully freed table\n");
    return;
}