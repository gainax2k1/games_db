#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // used for tolower() in find....maybe? remove if unused

#include "hash.h"
#include "game.h"

hash_table_t *create_table(size_t size) { // creating the hash
    hash_table_t *new_hash_table = (hash_table_t*) malloc (sizeof(hash_table_t));
    if(new_hash_table == NULL){ //safety check
        fprintf(stderr, "failed to allocate memory for hash table in create_table()\n");
        return NULL; 
    }

    hash_node_t **new_buckets = (hash_node_t**) calloc (size, sizeof(hash_node_t*)); 
    if(new_buckets == NULL){ //safety check
        fprintf(stderr, "failed to create buckets for hash in create_table()\n");
        free(new_hash_table); // making sure to free the memory for the hash table before returning
        return NULL;
    }
    
    new_hash_table->count = 0;
    new_hash_table->size = size;
    new_hash_table->buckets = new_buckets; //possible wrong pointer type?

    return new_hash_table;
}

size_t hash(const char *str, hash_table_t *table) { // djb2 algorithm for hashing
    if(str == NULL){ //safety check
        fprintf(stderr, "invalid str sent to hash()\n");
        return 0; // safest size_t for index to return
    }

    size_t hash = 5381; // Start with a prime number for algorithm
    int c; //for temporarily holding ascii values in character string
    
    // Iterate through each character in the string
    while ((c = *str++)) {
        // hash * 33 + c, done through bit-shifting 
        hash = ((hash << 5) + hash) + c;
    }
    
    // Ensure the hash is within bounds of our table size
    return hash % table->size; 
}

bool insert_game(hash_table_t *table, game_t *game) { // insert game into hash, return 0 if failed, 1 if success
    if(table == NULL || game == NULL){ //safety check
        fprintf(stderr, "invalid values sent to insert_game()\n");
        return 0;
    }
    printf("successfully entered insert_game()\n");

    hash_node_t *new_game = (hash_node_t*) malloc (sizeof(hash_node_t));

    if(new_game == NULL){ // safety check
        fprintf(stderr, "failed to allocate memory for new node in insert_game()\n");
        return 0;
    }
    printf("successfully created node for new game\n");

    // initiallizing values for new node
    new_game->game = game;  
    new_game->next = NULL; 

    printf("successfully initialized values for new node\n");

    // need to add case for when title already exists
    // do we return fail, or do we add duplicate?

    size_t game_index = hash(game->title, table); // maybe should be pointer? type is matched for function, but perhaps should be pointer. but it's an index, so should be number...right?

    printf("successfully got game_index from hash()\n");

    hash_node_t *ll_node = table->buckets[game_index]; //for traversing the LL at that bucket's index
    if (game_index >= table->size) { //safety
        fprintf(stderr, "Error: game_index (%zu) out of bounds\n", game_index);
        free(new_game);
        return 0;
    }

    printf("successfully  created ll_node pointer\n");
    
    if(ll_node == NULL){ //case of empty index
        table->buckets[game_index] = new_game;
        table->count++;
        return 1;
    } 
    else{ // case LL already started at index
        while(ll_node->next != NULL){ // until we reach the last node in LL
            ll_node = ll_node->next;
        }
        ll_node->next = new_game; //new_game added to LL
        table->count++;
        return 1;
    }
}

game_t *find_game(hash_table_t *table, const char *title) { // find game, eventually ignoring case, currently returning full match only
    // strcasestr(haystack, needle);  //just keeping here for reference later
    
    if(table == NULL || title == NULL){ // safety check
        fprintf(stderr, "invalid table or title sent to find_game()\n");
        return NULL;
    }

    size_t exact_match = hash(title, table); 

    if(table->buckets[exact_match] == NULL){ //case where game not found
        return NULL;
    }
    else{
        hash_node_t *ll_node = table->buckets[exact_match];
        do{
            if(!strcmp(ll_node->game->title, title)){ // case where match is found
                return ll_node->game;
            }
            ll_node = ll_node->next;
        }while(ll_node != NULL); 
        printf("Game: %s not found.\n", title);
        return NULL; // traversed through LL, no exact match found
    }
}

void free_node(hash_node_t *node){ // helper function for freeing nodes
    free_game(node->game);
    free(node);
}

bool remove_game(hash_table_t *table, const char *title) { //removes game, if found 1= succes, 0 = fail
    if(table == NULL || title == NULL){ // safety check
        fprintf(stderr, "invalid table or title sent to remove_game()\n");
        return false;
    }
    printf("Attempting to remove game with title: %s\n", title);
    size_t exact_match = hash(title, table);  // get's hash where game should be (exact match)
    printf("Hash index determined: %zu\n", exact_match);

    if(table->buckets[exact_match] == NULL){ //case where game not found
        return false;
    }
    
    hash_node_t *ll_node = table->buckets[exact_match]; // pointer to traverse LL

  
    
    printf("Checking bucket %zu...\n", exact_match);


     // Case 1: Match is the first node
     if (!strcmp(ll_node->game->title, title)) { 
        table->buckets[exact_match] = ll_node->next; // Update bucket pointer to the next node (or NULL if it was the only node in bucket)
        free_node(ll_node);           // Free the node
        table->count--;          // adjust  count of games
        return true;             // Removal successful
    }

    // Case 2: Traverse through the linked list
    hash_node_t *previous_node = ll_node;
    ll_node = ll_node->next;

    while (ll_node != NULL) {
        if (!strcmp(ll_node->game->title, title)) { // Match is found
            previous_node->next = ll_node->next;   // Bypass the current node
            free_node(ll_node);                      // Free the node
            table->count--;                       // adjust count of games
            return true;                          // Removal successful
        }
        // Step forward in the linked list
        previous_node = ll_node;
        ll_node = ll_node->next;
    }

    /* my first implementation
    if(!strcmp(ll_node->game->title, title) && ll_node->next == NULL){ // case when match is only item in bucket
        free_game(ll_node->game); // frees the game
        free(ll_node); //frees the node
        table->buckets[exact_match] = NULL; // nullify the bucket pointer
        return true;
    }
    if(!strcmp(ll_node->game->title, title)){ //case where game is first in the LL
        table->buckets[exact_match] = ll_node->next;
        free_game(ll_node->game); //frees the game
        free(ll_node); // frees the node
        return true;
    }

    hash_node_t *previous_node = ll_node; // creates follow node
    do{
        if(!strcmp(ll_node->game->title, title)){ // case where match is found
            previous_node->next = ll_node->next;
            free_game(ll_node->game); //frees the game
            free(ll_node); // frees the node
            return true; 
        }
        // ll_node wasn't exact match, going to next node in LL, tracking the previous node
        previous_node = ll_node;
        ll_node = ll_node->next;
        // might need some cajiggering here, but this is the concept
    }while(ll_node != NULL);  //
    */

    return false; //at this point, there was no exact match found to remove
}


// Note: This also frees all games in the table free game, then node, then bucket, then hash.
void free_table(hash_table_t *table) {
    if(table == NULL){ //safety check
        fprintf(stderr, "Invalid table sent to free_table()\n");
        return;
    }
    
    for(size_t i = 0; i < table->size; i++){
        if(table->buckets[i] == NULL){
            continue; // empty bucket, move on to next
        }
        else{
            hash_node_t *ll_node = table->buckets[i]; //grab first node in LL
            hash_node_t *ll_next_node = ll_node->next; //grabs next node in LL before freeing current node
                
            while(ll_node != NULL){
                ll_next_node = ll_node->next;                    
        
                free_node(ll_node);

                ll_node = ll_next_node; // move on to next node
                if (ll_node == NULL) {
                    printf("Reached end of linked list in bucket %zu\n", i);
                }

            } 
        }
            
    }
    free(table->buckets); // free the buckets
    free(table); // free the table itself

    return;  // might change function to bool to return success/fail condition
}

game_t **get_games_list(hash_table_t *table) { // traverses the hash, storing games in array to return
    if(table == NULL){ //safety
        fprintf(stderr, "Invalid table sent to get_games_list()\n");
        return NULL;
    }
    
    printf("successfully entered get_games_list()\n");

    game_t **games_list = (game_t**) calloc (table->count, sizeof(game_t*)); //allocates memory for array to hold games.
    if (games_list == NULL) { // safety
        fprintf(stderr, "Memory allocation for games_list failed!\n");
        return NULL;
    }
   
    size_t current_index = 0; // for storying games in array
    
    for(size_t i = 0; i < table->size; i++){
            if(table->buckets[i] == NULL){
                continue; // empty bucket, move on to next
            }
            else{
                hash_node_t *ll_node = table->buckets[i]; //grab first node in LL
                    
                do{ 
                    printf("Adding game at index %zu\n", current_index); 
                    games_list[current_index] = ll_node->game;
                    current_index++;
                    
                    ll_node = ll_node->next; // move on to next node
    
                } while(ll_node != NULL);
            }                
        }
    return games_list; //
}

// *** THIS IS WHERE THINGS STOP WORKING ****
void print_table(hash_table_t *table) { //initially in traversal order
    if(table == NULL){
        fprintf(stderr, "Invalid table sent to print_table()\n");
        return;
    }
    printf("successfullly entered print_table()\n");


    game_t **games_list = get_games_list(table); // might need tuning ???
    

    if(games_list == NULL){
        fprintf(stderr, "Failed to retrieve list of games from get_games_list()\n");
        return;
    }

    for(size_t i = 0; i < table->count; i++){
        game_t *current_game = games_list[i];
        show_game(current_game);
        // printf("[%zu] Title: %s, Genre: %s, Platform: %s\n", i, current_game->title, current_game->genre, current_game->platform);
    
    }

    free(games_list); // might need to free each element individually ???
    
    return;
}










