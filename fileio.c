

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <csv.h> // sudo apt-get install libcsv-dev
#include "hash.h"
#include "game.h"



// Structure to hold temporary field data during parsing
typedef struct {
    hash_table_t *ht; // for storing completed records
    char* fields[3];  // title, genre, platform
    int field_count; // How many fields we've seen in current record
    int row;  // for tracking row index when reading CSV file
} ParserData;

// Callback for each field
void field_callback(void *field, size_t size, void *data) {
    ParserData* parser_data = (ParserData*)data;
    
    // Make sure we don't exceed our field count
    if (parser_data->field_count < 3) {
        // Allocate and copy the field data
        parser_data->fields[parser_data->field_count] = malloc(size + 1);
        memcpy(parser_data->fields[parser_data->field_count], field, size);
        parser_data->fields[parser_data->field_count][size] = '\0';
        parser_data->field_count++;
    }
}

// Callback for end of record
void record_callback(int c, void *data) {
    ParserData* parser_data = (ParserData*)data;


    // Skip header row 
    if (parser_data->row == 0) {
        // Free the fields before returning
        for (int i = 0; i < parser_data->field_count; i++) {
            free(parser_data->fields[i]);
        }
        parser_data->row++;
        // Reset field count for next record
        parser_data->field_count = 0;

        return;
    }

    // Only process records with the correct number of fields
    if (parser_data->field_count == 3) {
        // Create a new game

        game_t *new_game = create_game(
            parser_data->fields[0],                 // title
            string_to_genre(parser_data->fields[1]),       // genre as enum
            string_to_platform(parser_data->fields[2])     // platform as enum
        );

        // Insert into hash table
        insert_game(parser_data->ht, new_game);
    }
    

    // Free the fields
    for (int i = 0; i < parser_data->field_count; i++) {
        free(parser_data->fields[i]);
    }

    // Reset field count for next record
    parser_data->field_count = 0;
}

// Function to load games from CSV file
bool load_games(const char* filename, hash_table_t *ht) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return false;
    }
    
    // Initialize the CSV parser
    struct csv_parser parser;
    if (csv_init(&parser, CSV_STRICT) != 0) {
        fprintf(stderr, "Failed to initialize CSV parser\n");
        fclose(fp);
        return false;
    }
    
    // Set up our parser data
    ParserData parser_data = {
        .ht = ht,
        .field_count = 0,
        .row = 0  // Start at row 0
    };
    
    // Read and parse the file
    char buf[1024];
    size_t bytes_read;

    while ((bytes_read = fread(buf, 1, sizeof(buf), fp)) > 0) {
        if (csv_parse(&parser, buf, bytes_read, field_callback, record_callback, &parser_data) != bytes_read) {
            fprintf(stderr, "Error parsing CSV: %s\n", csv_strerror(csv_error(&parser)));
            csv_free(&parser);
            fclose(fp);
            return false;
        }
    }
    
    // Finalize parsing
    csv_fini(&parser, field_callback, record_callback, &parser_data);
    
    // Clean up
    csv_free(&parser);
    fclose(fp);
    
    return true;
}







// Function to write a field with proper CSV escaping
void write_csv_field(FILE* fp, const char* field) {
    // Check if we need to quote this field
    bool needs_quotes = false;
    for (int i = 0; field[i]; i++) {
        if (field[i] == '"' || field[i] == ',' || field[i] == '\n' || field[i] == '\r') {
            needs_quotes = true;
            break;
        }
    }
    
    if (needs_quotes) {
        // Write opening quote
        fputc('"', fp);
        
        // Write field contents, doubling any quotes
        for (int i = 0; field[i]; i++) {
            if (field[i] == '"') {
                fputs("\"\"", fp);
            } else {
                fputc(field[i], fp);
            }
        }
        
        // Write closing quote
        fputc('"', fp);
    } else {
        // Write the field without quotes
        fputs(field, fp);
    }
}

// Function to save games to CSV file
bool save_games(const char* filename, hash_table_t *ht) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        fprintf(stderr, "Error opening file for writing: %s\n", filename);
        return false;
    }
    
    fprintf(fp, "title,genre,platform\n"); // header row for CSV

    // Iterate through all games in the hash table
    for (int i = 0; i < ht->size; i++) {
        hash_node_t *item = ht->buckets[i];
        
        while (item) {
            game_t *game = (game_t*)item->game;
            
            // Write title
            write_csv_field(fp, game->title);
            fputc(',', fp);
            
            // Write genre
            write_csv_field(fp, genre_to_string(game->genre));
            fputc(',', fp);
            
            // Write platform
            
            write_csv_field(fp, platform_to_string(game->platform));
            fputc('\n', fp);
            
            item = item->next;
        }
    }
    
    fclose(fp);
    return true;
}

// below is notes/pseudo code/ ideas for manual implementing csv. 
// I have since decided to use the pre-existing csv.h, and no re-invent the wheel
// still, handy to know what is happening in the whole csv process

/*
For the save_to_csv function:
    Opening a file for writing
    Getting the list of games
    Converting each game to CSV format
    Writing to the file
    Closing the file
    Returning success/failure

For the load_from_csv function:
    Opening the existing file (if it exists)
    Reading each line
    Parsing CSV format into game objects
    Adding each game to your hash table
    Closing the file
    Returning the populated hash table
*/



*/
