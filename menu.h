#pragma once // compiler directive to only include once, even if included elsewhere
#include <stddef.h>

typedef struct Menu {
    size_t menu_size; // number of items on menu - use sizeof to update?
    char **menu_items; // array of size menu_size, each index is a menu choice
} menu_t;

menu_t *create_menu(char **menu_items, size_t num_menu_items); // new menu accepts an array of options, returns pointer to menu
void show_menu(menu_t *men); // displays formatted menu
void free_menu(menu_t *men); // frees memory for menu


/* TO-DO: 
this isn't full code, but you get the idea:
*******************************


class MenuManager:
    def __init__(self):
        self.menus = {}

    def create_menus(self):
        # Create and store all menus
        self.menus["main_menu"] = Menu(title="Main Menu", options=["Add Game", "Print Games", "Exit"])
        self.menus["add_game_menu"] = Menu(title="Add Game Menu", options=["Enter Game Name", "Enter Genre", "Back"])
        self.menus["print_menu"] = Menu(title="Print Menu", options=["Print Alphabetically", "Print by Date", "Back"])

    def show_menu(self, menu_name):
        # Dynamically display the requested menu
        if menu_name in self.menus:
            self.menus[menu_name].display()
        else:
            print(f"Menu '{menu_name}' not found!")  # Error handling

# Example 'Menu' class implementation:
class Menu:
    def __init__(self, title, options):
        self.title = title
        self.options = options

    def display(self):
        # Display the menu and return user choice
        print(f"\n{self.title}")
        for i, option in enumerate(self.options, start=1):
            print(f"{i}. {option}")


*/