#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // used for tolower() in find at a later date? remove if unused

#include "hash.h"
#include "game.h"
#include "colors.h"

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

    if((table->count / table->size) >= .7){
       // printf("RESIZING THE HIZASH!!!\n");  //debugging code
        resize_hash(table);
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

    size_t game_index = hash(game->title, table); // maybe should be pointer? type is matched for function, but perhaps should be pointer. but it's an index, so should be number...right?

    // printf("successfully got game_index from hash()\n"); // debugging code

    hash_node_t *ll_node = table->buckets[game_index]; //for traversing the LL at that bucket's index
    if (game_index >= table->size) { //safety
        fprintf(stderr, "Error: game_index (%zu) out of bounds\n", game_index);
        free(new_game);
        return 0;
    }

    // printf("successfully  created ll_node pointer\n"); // debugging code
    
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

game_t *find_game(hash_table_t *table, char *title) { // find game, eventually ignoring case, currently returning full match only
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

bool remove_game(hash_table_t *table, char *title) { //removes game, if found 1= succes, 0 = fail
    if(table == NULL || title == NULL){ // safety check
        fprintf(stderr, "invalid table or title sent to remove_game()\n");
        return false;
    }
    size_t exact_match = hash(title, table);  // get's hash where game should be (exact match)

    if(table->buckets[exact_match] == NULL){ //case where game not found
        return false;
    }
    
    hash_node_t *ll_node = table->buckets[exact_match]; // pointer to traverse LL

  
    
    // printf("Checking bucket %zu...\n", exact_match); //debugging code


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
                    // printf("Adding game at index %zu\n", current_index);  // debugging code
                    games_list[current_index] = ll_node->game;
                    current_index++;
                    
                    ll_node = ll_node->next; // move on to next node
    
                } while(ll_node != NULL);
            }                
        }
    return games_list; //
}

// Comparison function for strings for qsort() in print_table()
int compare_games_by_title(const void *a, const void *b) {
    // Cast the void pointers to game_t** (pointer to pointer to game)
    game_t *game1 = *(game_t **)a;
    game_t *game2 = *(game_t **)b;
    
    // Compare the titles
    return strcmp(game1->title, game2->title);
}

void print_table(hash_table_t *table) { //initially in traversal order
    if(table == NULL){
        fprintf(stderr, "Invalid table sent to print_table()\n");
        return;
    }

    game_t **games_list = get_games_list(table); // get's the games list from the hash, don't forget to free it.
    

    if(games_list == NULL){
        fprintf(stderr, "Failed to retrieve list of games from get_games_list()\n");
        return;
    }
    // sorting by name using qsort() from stdlib.h *****************
    // table->count is number of games
    qsort(games_list, table->count, sizeof(game_t*), compare_games_by_title);
    
    
    for(size_t i = 0; i < table->count; i++){
        game_t *current_game = games_list[i];
        show_game(current_game);
        // printf("[%zu] Title: %s, Genre: %s, Platform: %s\n", i, current_game->title, current_game->genre, current_game->platform);
    
    }

    free(games_list); //remembering to free the games_list
    
    return;
}


void resize_hash(hash_table_t *ht) {
    game_t** games_array = get_games_list(ht); // getting the list of old gamess
    size_t glist_count = ht->count; // index size for games list
    size_t old_size = ht->size; // storing old size
    hash_node_t** old_buckets = ht->buckets; // Save old buckets to free later
 
    // Create a new empty hash table with larger size
    size_t new_size = old_size * 2;
    hash_node_t** new_buckets = calloc(new_size, sizeof(hash_node_t*));

    // Update hash table with new buckets and size
    ht->buckets = new_buckets;
    ht->size = new_size;
    ht->count = 0;  // Will be incremented as we add games back

    // Reinsert all games into the new, larger hash table
    for (size_t i = 0; i < glist_count; i++) {
        insert_game(ht, games_array[i]);
    }


    // First, free all the linked list nodes
    for (size_t i = 0; i < old_size; i++) {
        hash_node_t* current = old_buckets[i];
        while (current != NULL) {
            hash_node_t* next = current->next;
            free(current);  // Just free the node, not the game it points to
            current = next;
        }
    }
    free(games_array); // DON'T FORGET THIS, you silly billy!
    free(old_buckets);

    return;
}










