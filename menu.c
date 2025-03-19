//#include "assert.h" //for debugging once implemented
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h"

menu_t *create_menu(char **menu_items, size_t num_menu_items){ // new menu accepts an array of options, returns pointer to menu
    menu_t *new_menu = (menu_t*) malloc(sizeof(menu_t)); // creating the new menu_t
    if(new_menu == NULL){
        fprintf(stderr, "failed to allocate memory for new menu in create_menu\n"); // safety case for failed memory alloc
        return NULL;
    }
    new_menu->menu_size = num_menu_items; // number of elements in the array)
    new_menu->menu_items = menu_items; // assign the passed in array of menu items
    return new_menu; 
}

void show_menu(menu_t *men){ // displays formatted menu
    if(men == NULL){ //safety check
        fprintf(stderr, "invalid menu in show_menu\n");
    }
    printf("%zu is menusize \n", men->menu_size);
    for(size_t i = 0; i < men->menu_size; i++){
        printf("[%zu] %s \n", i, men->menu_items[i]);
    }
    return;
}