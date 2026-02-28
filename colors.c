#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "colors.h"


// Genre color lookup table
static const char* genre_colors[] = {
    COLOR_UNKNOWN,
    COLOR_RPG,
    COLOR_PUZZLE,
    COLOR_SPORTS,
    COLOR_ROGUE,
    COLOR_MUSIC,
    COLOR_PLATFORMER,
    COLOR_FPS,
    COLOR_STRAT,
};

// Platform color lookup table
static const char* platform_colors[] = {
    COLOR_UNKNOWN,
    COLOR_NES,
    COLOR_SNES,
    COLOR_N64,
    COLOR_GC,
    COLOR_WII,
    COLOR_WIIU,
    COLOR_SWITCH,
    COLOR_GB,
    COLOR_GBC,
    COLOR_VBOY,
    COLOR_GBA,
    COLOR_DS,
    COLOR_DSI,
    COLOR_3DS,
    COLOR_PS1,
    COLOR_PS2,
    COLOR_PS3,
    COLOR_PS4,
    COLOR_PS5,
    COLOR_PSP,
    COLOR_VITA,
    COLOR_XBOX,
    COLOR_360,
    COLOR_ONE,
    COLOR_SERIES,
    COLOR_GENESIS,
    COLOR_SEGACD,
    COLOR_32X,
    COLOR_SATURN,
    COLOR_DC,

};

const char* get_genre_color(genre_t genre) {
    if (genre >= 0 && genre < sizeof(genre_colors)/sizeof(genre_colors[0])){
        return genre_colors[genre];
    }
    return COLOR_WHITE; // Default
}

const char* get_platform_color(platform_t platform) { 
    if (platform >= 0 && platform < sizeof(platform_colors)/sizeof(platform_colors[0])){
        return platform_colors[platform];
    }
    return COLOR_WHITE; // Default
}
