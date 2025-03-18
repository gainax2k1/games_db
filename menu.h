#pragma once // compiler directive to only include once, even if included elsewhere
#include <stddef.h>

typedef struct Menu {
    size_t menu_size; // number of items on menu - use sizeof to update?
    char **menu_items; // array of size menu_size, each index is a menu choice
} menu_t;

menu_t *create_menu(char **menu_items, size_t num_menu_items); // new menu accepts an array of options, returns pointer to menu
void show_menu(menu_t *men); // displays formatted menu