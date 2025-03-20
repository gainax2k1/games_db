#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // used for tolower() in find....maybe? remove if unused

#include "hash.h"
#include "game.h"

hash_table_t *create_table(size_t size){ // creating the hash
    hash_table_t *new_hash_table = (hash_table_t*) malloc (sizeof(hash_table_t));
    if(new_hash_table == NULL){ //safety check
        fprtintf(stderr, "failed to allocate memory for hash table in create_table()\n");
        return NULL; 
    }

    hash_node_t *new_buckets = (hash_node_t*) calloc (size, sizeof(hash_node_t)); 
    if(new_buckets == NULL){ //safety check
        fprintf(stderr, "failed to create buckets for hash in create_table()\n");
        free(new_hash_table); // making sure to free the memory for the hash table before returning
        return NULL;
    }
    
    new_hash_table->count = 0;
    new_hash_table->size = size;
    new_hash_table->buckets = new_buckets;

    return new_hash_table;
}

size_t hash(const char *str, hash_table_t *table) { // djb2 algorithm for hashing
    if(str == NULL){ //safety check
        fprintf(stderr, "invalid str sent to hash()\n");
        return NULL;
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

bool insert_game(hash_table_t *table, game_t *game){ // insert game into hash, return 0 if failed, 1 if success
    if(table == NULL || game == NULL){ //safety check
        fprintf(stderr, "invalid values sent to insert_game()\n");
        return 0;
    }
    
    hash_node_t *new_game = (hash_node_t*) malloc (sizeof(hash_node_t));

    if(new_game == NULL){ // safety check
        fprintf(stderr, "failed to allocate memory for new node in insert_game()\n");
        return 0;
    }
    
    // initiallizing values for new node
    new_game->game = game;  
    new_game->next = NULL; 


    // need to add case for when title already exists
    // do we return fail, or do we add duplicate?

    size_t game_index = hash(game->title, table->size);
    hash_node_t *ll_node = table->buckets[game_index]; //for traversing the LL at that bucket's index

    if(ll_node == NULL){ //case of empty index
        ll_node = new_game;
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

game_t *find_game(hash_table_t *table, const char *title){ // find game, eventually ignoring case, currently returning full match only
    // strcasestr(haystack, needle);  //just keeping here for reference later
    
    if(table == NULL || title == NULL){ // safety check
        fprintf(stderr, "invalid table or title sent to find_game()\n");
        return NULL;
    }

    size_t exact_match = hash(title, table); 

    if(exact_match == NULL){ //case where game not found
        return NULL;
    }
    else{
        hash_node_t *ll_node = table->buckets[exact_match];
        do{
            if(!strcmp(ll_node->game->title, title)){ // case where match is found
                return ll_node;
            }
            ll_node = ll_node->next;
        }while(ll_node != NULL); 
        
        return NULL; // traversed through LL, no exact match found
    }
}

bool *remove_game(hash_table_t *table, const char *title){ //removes game, if found 1= succes, 0 = fail
    if(table == NULL || title == NULL){ // safety check
        fprintf(stderr, "invalid table or title sent to remove_game()\n");
        return NULL;
    }
    
    size_t exact_match = hash(title, table);  // get's hash where game should be (exact match)

    if(exact_match == NULL){ //case where game not found
        return NULL;
    }
    
    hash_node_t *ll_node = table->buckets[exact_match];
    if(ll_node->next == NULL){ // case when match is only item in bucket
        free_game(ll_node->game); // frees the game
        free(ll_node); //frees the node
        // may need to set table->buckets[exact_matc] = NULL ???
        return true;
    }
    else{ 
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

        return false; //at this point, there was no exact match found to remove
    }

}


// Note: This also frees all games in the table free game, then node, then bucket, then hash.
void free_table(hash_table_t *table){
    if(table == NULL){ //safety check
        fprintf(stderr, "Invalid table sent to free_table()\n");
        return;
    }
    
    for(size_t i = 0; i < table->size; i++){
        if(table->buckets[i] == NULL){
            // do i need to free(table->buckets[i]) here???
            continue; // empty bucket, move on to next
        }
        else{
            hash_node_t *ll_node = table->buckets[i]; //grab first node in LL
            hash_node_t *ll_next_node = ll_node->next; //grabs next node in LL before freeing current node
                
            do{
                ll_next_node = ll_node->next;                    
                    
                free_game(ll_node->game); // frees game portion of node
                free(ll_node); // frees node iteslf.

                ll_node = ll_next_node; // move on to next node
                

            } while(ll_node != NULL);
        }
        free(table->buckets[i]; // i think this covers all contingencies??
            
    }
    free(table->buckets); //may be unnceccesary
    free(table); // free the table itself

    return;  // might change function to bool to return success/fail condition
}


void print_table(hash_table_t *table){ //initially in traversal order
    if(table == NULL){
        fprintf(stderr, "Invalid table sent to print_table()\n");
        return;
    }
    
    game_t *list = get_games_list(table); // might need tuning ???
    
    if(list == NULL){
        fprintf(stderr, "Failed to retrieve list of games from get_games_list()\n");
        return;
    }

    for(size_t i = 0; i < table->count; i++){
        game_t *current_game = list[i];
        
        printf("[%zu] Title: %s, Genre: %s, Platform: %s\n", i, current_game->title, current_game->genre, current_game->platform);
    
    }

    free(list); // might need to free each element individually ???
    
    return;
}

game_t *get_games_list(hash_table_t *table){ // traverses the hash, storing games in array to return
    if(table == NULL){ //safety
        fprintf(stderr, "Invalid table sent to get_games_list()\n";
        return NULL;
    }
    
    game_t *games_list = (game_t*) calloc (table->count, sizeof(game)); //allocates memory for array to hold games.
    size_t current_index = 0; // for storying games in array
    
    for(size_t i = 0; i < table->size; i++){
            if(table->buckets[i] == NULL){
                continue; // empty bucket, move on to next
            }
            else{
                hash_node_t *ll_node = table->buckets[i]; //grab first node in LL
                    
                do{  
                    games_list[current_index] = ll_node->game;
                    current_index++;
                    
                    ll_node = ll_node->next; // move on to next node
    
                } while(ll_node != NULL);
            }                
        }
    return games_list; //
}








