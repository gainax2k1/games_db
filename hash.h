#pragma once // compiler directive to only include once, even if included elsewhere
#include <stddef.h>
#include <stdbool.h>
#include "game.h"  // double check if actually neccessary, but it should be

typedef struct Hash_Node { // node for linked list
    game_t *game; 
    struct Hash_Node *next; // pointer to next node in list
} hash_node_t;

typedef struct Hash_Table {
    hash_node_t **buckets; // array of pointers to linked lists
    size_t size; // number of buckets
    size_t count; // number of games stored
} hash_table_t;

// Create a new hash table with the given number of buckets
// use calloc (size, sizeof(hash_node_t)
hash_table_t *create_table(size_t size); // done

// Calculate a hash value for a string
// "done", uses djb2 alg
size_t hash(const char *str, hash_table_t *table); // done

// Insert a game into the hash table
// Returns 1 if successful, 0 if failed
bool insert_game(hash_table_t *table, game_t *game); //done

// Find a game in the hash table by title
// #include <ctype.h>   /* For tolower */ set find game to effectively ignore case
// Returns the game if found, NULL if not found  // use strcmp(), strstr() for string in  a string, strcasestr() (ignores case)
game_t *find_game(hash_table_t *table, char *title); // done for exact match only to start

// Remove a game from the hash table by title
// Returns the removed game if found, NULL if not found
bool remove_game(hash_table_t *table, char *title); //done for now

// Free all memory associated with the hash table
// Note: This also frees all games in the table free game, then node, then bucket, then hash.
void free_table(hash_table_t *table); // done for noww;

// Print all games in the hash table 
// initally, will be in "random" order, eventually store into temporary array, than use various
// sorts for however i wish to display it. also, probably some way to stop listing as screen fills up?
// uses helper function get_games_list(table_t* table) to get an array of the games, usorted.

void print_table(hash_table_t *table); //done for now

void resize_hash(hash_table_t *ht); // resizes the hash (both ways? starting with enlarge)



/* TO-DO:

1) shrink hash at .2 utilization? low priorty to implement.
2) Add options to print table, as sort table functions (by title, genre, etc)
4) Add user i/o: adding, removing, finding, etc...


*/