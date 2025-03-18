#include <stdio.h>
#include <stdlib.h>
#include "menu.h"

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
    size_t num_menu_items = sizeof(main_menu_opts) / sizeof(main_menu_opts[0]);
    menu_t *main_menu = create_menu(main_menu_opts, num_menu_items);

    show_menu(main_menu);



    return;
}