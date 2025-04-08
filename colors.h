#ifndef COLORS_H
#define COLORS_H

// Text styles
#define STYLE_RESET "\033[0m"
#define STYLE_BOLD "\033[1m"
#define STYLE_DIM "\033[2m"
#define STYLE_ITALIC "\033[3m"
#define STYLE_UNDERLINE "\033[4m"
#define STYLE_BLINK "\033[5m"
#define STYLE_INVERSE "\033[7m"

// Basic colors (foreground)
#define COLOR_BLACK "\033[30m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"
#define COLOR_WHITE "\033[37m"

// Bright colors (foreground)
#define COLOR_BRIGHT_BLACK "\033[90m"   // Actually dark gray
#define COLOR_BRIGHT_RED "\033[91m"
#define COLOR_BRIGHT_GREEN "\033[92m"
#define COLOR_BRIGHT_YELLOW "\033[93m"
#define COLOR_BRIGHT_BLUE "\033[94m"
#define COLOR_BRIGHT_MAGENTA "\033[95m"
#define COLOR_BRIGHT_CYAN "\033[96m"
#define COLOR_BRIGHT_WHITE "\033[97m"

// Background colors
#define BG_BLACK "\033[40m"
#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN "\033[46m"
#define BG_WHITE "\033[47m"

// Console Developer color assignments:
#define COLOR_UNKNOWN   COLOR_BRIGHT_BLACK
#define COLOR_NINTENDO  COLOR_RED 
#define COLOR_SEGA      COLOR_BRIGHT_BLUE
#define COLOR_SONY      COLOR_BLUE  
#define COLOR_MICROSOFT COLOR_GREEN    
#define COLOR_ATARI     COLOR_BRIGHT_RED
#define COLOR_NEC       COLOR_YELLOW
#define COLOR_SNK       COLOR_CYAN

// Console Colors
#define COLOR_NES       COLOR_NINTENDO
#define COLOR_SNES      COLOR_NINTENDO
#define COLOR_N64       COLOR_NINTENDO
#define COLOR_GC        COLOR_NINTENDO
#define COLOR_WII       COLOR_NINTENDO
#define COLOR_WIIU      COLOR_NINTENDO
#define COLOR_SWITCH    COLOR_NINTENDO
#define COLOR_GB        COLOR_NINTENDO
#define COLOR_GBC       COLOR_NINTENDO
#define COLOR_VBOY      COLOR_NINTENDO
#define COLOR_GBA       COLOR_NINTENDO
#define COLOR_DS        COLOR_NINTENDO
#define COLOR_DSI       COLOR_NINTENDO
#define COLOR_3DS       COLOR_NINTENDO
#define COLOR_PS1       COLOR_SONY
#define COLOR_PS2       COLOR_SONY
#define COLOR_PS3       COLOR_SONY
#define COLOR_PS4       COLOR_SONY
#define COLOR_PS5       COLOR_SONY
#define COLOR_PSP       COLOR_SONY
#define COLOR_VITA      COLOR_SONY
#define COLOR_XBOX      COLOR_MICROSOFT
#define COLOR_360       COLOR_MICROSOFT
#define COLOR_ONE       COLOR_MICROSOFT
#define COLOR_SERIES    COLOR_MICROSOFT
#define COLOR_GENESIS   COLOR_SEGA
#define COLOR_SEGACD    COLOR_SEGA
#define COLOR_32X       COLOR_SEGA
#define COLOR_SATURN    COLOR_SEGA
#define COLOR_DC        COLOR_SEGA

// Genre color assignments: 
#define COLOR_RPG       COLOR_MAGENTA
#define COLOR_PUZZLE    COLOR_YELLOW   
#define COLOR_SPORTS    COLOR_CYAN
#define COLOR_ROGUE     COLOR_BRIGHT_RED
#define COLOR_MUSIC     COLOR_BLUE
#define COLOR_PLATFORMER COLOR_RED
#define COLOR_FPS       COLOR_GREEN
#define COLOR_STRAT     COLOR_BRIGHT_GREEN


#endif /* COLORS_H */
#include "game.h"

const char* get_platform_color(platform_t platform);
const char* get_genre_color(genre_t genre);


/* TREAT EVERYTHING BELOW AS PSEUDOCODE/REFERENCE!!!

The \033 represents the ASCII escape character (octal notation) - it tells the terminal "Hey, special command coming up!" The [ starts the control sequence, and what follows are the parameters:

31m means "set text color to red"
32m means "set text color to green"
And so on...
These are called ANSI escape codes or VT100 escape sequences, dating back to old terminal systems. The basic color palette includes:

Text colors (30-37):

30m: Black
31m: Red
32m: Green
33m: Yellow
34m: Blue
35m: Magenta
36m: Cyan
37m: White
Background colors (40-47):

40m-47m: Same colors as above but for backgrounds
For brightness:

Add 60 to get bright versions (90-97 for bright text colors)
Add 60 to backgrounds (100-107 for bright backgrounds)
For more advanced styling:

0m: Reset all styles
1m: Bold
4m: Underline
7m: Inverse colors
For modern terminals, you can also access 256 colors with:

\033[38;5;COLORNUMBERm  // Text color
\033[48;5;COLORNUMBERm  // Background color

Where COLORNUMBER is 0-255.

And many terminals support true color (16 million colors):

\033[38;2;R;G;Bm  // RGB text color
\033[48;2;R;G;Bm  // RGB background color
*/



/* For Menu Headings:

// Inverse (black on white) for headings
#define HEADING_STYLE "\033[7;1m"  // Inverse + Bold
#define COLOR_RESET "\033[0m"

// Usage
printf("%s MAIN MENU %s\n", HEADING_STYLE, COLOR_RESET);

For Platform-Based Coloring:

// Platform color definitions
#define COLOR_NES "\033[36m"        // Cyan
#define COLOR_SNES "\033[96m"       // Bright Cyan
#define COLOR_GENESIS "\033[34m"    // Blue
#define COLOR_PS1 "\033[35m"        // Magenta
#define COLOR_N64 "\033[32m"        // Green
// etc.

// Function to get color based on platform
const char* get_platform_color(const char* platform) {
    if (strcmp(platform, "NES") == 0) return COLOR_NES;
    if (strcmp(platform, "SNES") == 0) return COLOR_SNES;
    // etc.
    return COLOR_RESET;  // Default
}

For Genre-Based Coloring:

#define COLOR_RPG "\033[33m"         // Yellow
#define COLOR_ACTION "\033[31m"      // Red
#define COLOR_ADVENTURE "\033[32m"   // Green
#define COLOR_STRATEGY "\033[36m"    // Cyan
// etc.

// Function similar to platform colors

For displaying games with conditional coloring:

// Pseudocode for your list function
void list_games(game_t games[], int count, sort_type_t sort_type) {
    // ...sorting logic...
    
    for (int i = 0; i < count; i++) {
        const char* color;
        
        if (sort_type == SORT_BY_PLATFORM) {
            color = get_platform_color(games[i].platform);



*/

/*
// Company colors
#define COLOR_NINTENDO "\033[31m"      // Red
#define COLOR_SEGA "\033[34m"          // Blue
#define COLOR_SONY "\033[35m"          // Magenta
#define COLOR_MICROSOFT "\033[32m"     // Green
#define COLOR_ATARI "\033[33m"         // Yellow
#define COLOR_NEC "\033[36m"           // Cyan
#define COLOR_SNK "\033[91m"           // Bright Red
#define COLOR_BANDAI "\033[95m"        // Bright Magenta

// Usage example
void print_game(Game game) {
    const char* company_color = get_company_color(game.platform);
    printf("%s%s%s: %s (%d)\n", 
           company_color, 
           game.platform, 
           COLOR_RESET,
           game.title, 
           game.year);
}
*/


/*

const char* get_company_color(const char* platform) {
    // Nintendo platforms
    if (strstr("NES SNES N64 GAMECUBE WII SWITCH GAMEBOY GBA DS 3DS", platform))
        return COLOR_NINTENDO;
    
    // Sega platforms
    if (strstr("MASTER_SYSTEM GENESIS SATURN DREAMCAST GAME_GEAR", platform))
        return COLOR_SEGA;
    
    // And so on...
    
    return COLOR_RESET;  // Default if no match
}

*/
/*
Boots
Here's a simple reference for the primary ANSI terminal colors you can use:

// Basic colors (foreground)
#define COLOR_BLACK "\033[30m"
#define COLOR_RED "\033[31m"
#define COLOR_GREEN "\033[32m"
#define COLOR_YELLOW "\033[33m"
#define COLOR_BLUE "\033[34m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_CYAN "\033[36m"
#define COLOR_WHITE "\033[37m"

// Bright colors (foreground)
#define COLOR_BRIGHT_BLACK "\033[90m"   // Actually dark gray
#define COLOR_BRIGHT_RED "\033[91m"
#define COLOR_BRIGHT_GREEN "\033[92m"
#define COLOR_BRIGHT_YELLOW "\033[93m"
#define COLOR_BRIGHT_BLUE "\033[94m"
#define COLOR_BRIGHT_MAGENTA "\033[95m"
#define COLOR_BRIGHT_CYAN "\033[96m"
#define COLOR_BRIGHT_WHITE "\033[97m"

// Background colors
#define BG_BLACK "\033[40m"
#define BG_RED "\033[41m"
#define BG_GREEN "\033[42m"
#define BG_YELLOW "\033[43m"
#define BG_BLUE "\033[44m"
#define BG_MAGENTA "\033[45m"
#define BG_CYAN "\033[46m"
#define BG_WHITE "\033[47m"

// Text styles
#define STYLE_RESET "\033[0m"
#define STYLE_BOLD "\033[1m"
#define STYLE_DIM "\033[2m"
#define STYLE_ITALIC "\033[3m"
#define STYLE_UNDERLINE "\033[4m"
#define STYLE_BLINK "\033[5m"
#define STYLE_INVERSE "\033[7m"

*/