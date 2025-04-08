#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"
#include "colors.h"

const char* get_platform_color(platform_t platform) { // header might be wrong for my implementation
    if (platform == PLATFORM_UNKNOWN) return COLOR_UNKNOWN;
    if (platform == PLATFORM_NES) return COLOR_NES;
    if (platform == PLATFORM_SNES) return COLOR_SNES;
    if (platform == PLATFORM_N64) return COLOR_N64;
    if (platform == PLATFORM_GC) return COLOR_GC;
    if (platform == PLATFORM_WII) return COLOR_WII;
    if (platform == PLATFORM_WIIU) return COLOR_WIIU;
    if (platform == PLATFORM_SWITCH) return COLOR_SWITCH;
    if (platform == PLATFORM_SWITCH) return COLOR_SWITCH;
    if (platform == PLATFORM_GB) return COLOR_GB;
    if (platform == PLATFORM_GBC) return COLOR_GBC;
    if (platform == PLATFORM_VBOY) return COLOR_VBOY;
    if (platform == PLATFORM_GBA) return COLOR_GBA;
    if (platform == PLATFORM_DS) return COLOR_DS;
    if (platform == PLATFORM_DSI) return COLOR_DSI;
    if (platform == PLATFORM_3DS) return COLOR_3DS;
    if (platform == PLATFORM_PS1) return COLOR_PS1;
    if (platform == PLATFORM_PS2) return COLOR_PS2;
    if (platform == PLATFORM_PS3) return COLOR_PS3;
    if (platform == PLATFORM_PS4) return COLOR_PS4;
    if (platform == PLATFORM_PS5) return COLOR_PS5;
    if (platform == PLATFORM_PSP) return COLOR_PSP;
    if (platform == PLATFORM_VITA) return COLOR_VITA;
    if (platform == PLATFORM_XBOX) return COLOR_XBOX;
    if (platform == PLATFORM_360) return COLOR_360;
    if (platform == PLATFORM_ONE) return COLOR_ONE;
    if (platform == PLATFORM_SERIES) return COLOR_SERIES;
    if (platform == PLATFORM_GENESIS) return COLOR_GENESIS;
    if (platform == PLATFORM_SEGACD) return COLOR_SEGACD;
    if (platform == PLATFORM_32X) return COLOR_32X;
    if (platform == PLATFORM_SATURN) return COLOR_SATURN;
    if (platform == PLATFORM_DC) return COLOR_DC;
    
    return COLOR_WHITE;  // Default
}


const char* get_genre_color(genre_t genre) {

    if (genre == GENRE_UNKNOWN) return COLOR_UNKNOWN;
    if (genre == GENRE_RPG) return COLOR_RPG;
    if (genre == GENRE_PUZZLE) return COLOR_PUZZLE;
    if (genre == GENRE_SPORTS) return COLOR_SPORTS;
    if (genre == GENRE_ROGUE) return COLOR_ROGUE;
    if (genre == GENRE_MUSIC) return COLOR_MUSIC;
    if (genre == GENRE_PLATFORMER) return COLOR_PLATFORMER;
    if (genre == GENRE_FPS) return COLOR_FPS;
    if (genre == GENRE_STRAT) return COLOR_STRAT;

    return COLOR_WHITE;  // Default
}