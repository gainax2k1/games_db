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


/* REFERENCE

The \033 represents the ASCII escape character (octal notation) - it tells the terminal "Hey, special command coming up!"
The [ starts the control sequence, and what follows are the parameters:

31m means "set text color to red"
32m means "set text color to green"
And so on...
These are the ANSI escape codes or VT100 escape sequences, dating back to old terminal systems. The basic color palette includes:

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
