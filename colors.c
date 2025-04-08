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

/*
old, innefecient implemenation:


const char* get_COLOR_color(COLOR_t platform) { // header might be wrong for my implementation
    if (platform == COLOR_UNKNOWN) return COLOR_UNKNOWN;
    if (platform == COLOR_NES) return COLOR_NES;
    if (platform == COLOR_SNES) return COLOR_SNES;
    if (platform == COLOR_N64) return COLOR_N64;
    if (platform == COLOR_GC) return COLOR_GC;
    if (platform == COLOR_WII) return COLOR_WII;
    if (platform == COLOR_WIIU) return COLOR_WIIU;
    if (platform == COLOR_SWITCH) return COLOR_SWITCH;
    if (platform == COLOR_GB) return COLOR_GB;
    if (platform == COLOR_GBC) return COLOR_GBC;
    if (platform == COLOR_VBOY) return COLOR_VBOY;
    if (platform == COLOR_GBA) return COLOR_GBA;
    if (platform == COLOR_DS) return COLOR_DS;
    if (platform == COLOR_DSI) return COLOR_DSI;
    if (platform == COLOR_3DS) return COLOR_3DS;
    if (platform == COLOR_PS1) return COLOR_PS1;
    if (platform == COLOR_PS2) return COLOR_PS2;
    if (platform == COLOR_PS3) return COLOR_PS3;
    if (platform == COLOR_PS4) return COLOR_PS4;
    if (platform == COLOR_PS5) return COLOR_PS5;
    if (platform == COLOR_PSP) return COLOR_PSP;
    if (platform == COLOR_VITA) return COLOR_VITA;
    if (platform == COLOR_XBOX) return COLOR_XBOX;
    if (platform == COLOR_360) return COLOR_360;
    if (platform == COLOR_ONE) return COLOR_ONE;
    if (platform == COLOR_SERIES) return COLOR_SERIES;
    if (platform == COLOR_GENESIS) return COLOR_GENESIS;
    if (platform == COLOR_SEGACD) return COLOR_SEGACD;
    if (platform == COLOR_32X) return COLOR_32X;
    if (platform == COLOR_SATURN) return COLOR_SATURN;
    if (platform == COLOR_DC) return COLOR_DC;
    
    return COLOR_WHITE;  // Default
}


const char* get_COLOR_color(COLOR_t genre) {

    if (genre == COLOR_UNKNOWN) return COLOR_UNKNOWN;
    if (genre == COLOR_RPG) return COLOR_RPG;
    if (genre == COLOR_PUZZLE) return COLOR_PUZZLE;
    if (genre == COLOR_SPORTS) return COLOR_SPORTS;
    if (genre == COLOR_ROGUE) return COLOR_ROGUE;
    if (genre == COLOR_MUSIC) return COLOR_MUSIC;
    if (genre == COLOR_PLATFORMER) return COLOR_PLATFORMER;
    if (genre == COLOR_FPS) return COLOR_FPS;
    if (genre == COLOR_STRAT) return COLOR_STRAT;

    return COLOR_WHITE;  // Default
}
*/
