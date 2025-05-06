

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
For your save_to_csv function:
    Opening a file for writing
    Getting the list of games
    Converting each game to CSV format
    Writing to the file
    Closing the file
    Returning success/failure

And for your load_from_csv function:
    Opening the existing file (if it exists)
    Reading each line
    Parsing CSV format into game objects
    Adding each game to your hash table
    Closing the file
    Returning the populated hash table


These are solid foundations! A few questions to help you think through this:

What happens if the file doesn't exist when loading?
How will you handle errors during the reading/writing process?
Have you considered what delimiter you'll use in your CSV format?
What properties of your game objects will you need to save/restore?
*/



/* boots suggestions for self-implemeneting csv

bool save_games_to_csv(hash_table_t *table, const char *filename) {
    if (table == NULL || filename == NULL) {
        return false;
    }
    
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        fprintf(stderr, "Failed to open file for writing: %s\n", filename);
        return false;
    }
    
    // Write header row
    fprintf(file, "title,genre,platform\n");
    
    // Get all games and write them to the file
    game_t **games = get_games_list(table);
    if (games == NULL) {
        fclose(file);
        return false;
    }
    
    // Write each game to the file
    for (size_t i = 0; i < table->count; i++) {
        // Write each field, handling commas and quotes properly
        // ...
    }
    
    free(games);
    fclose(file);
    return true;
}


char* prepare_csv_field(const char* field) {
    // First, check if we need quotes at all
    bool needs_quotes = false;
    int quote_count = 0;
    
    for (int i = 0; field[i]; i++) {
        if (field[i] == ',' || field[i] == '"' || field[i] == '\n') {
            needs_quotes = true;
        }
        if (field[i] == '"') {
            quote_count++;
        }
    }
    
    if (!needs_quotes) {
        // Just return a copy of the original
        return strdup(field);
    }
    
    // Allocate space for the quoted version
    // Original + quote_count extra quotes + 2 for surrounding quotes + 1 for null
    char* quoted = malloc(strlen(field) + quote_count + 2 + 1);
    
    // Add opening quote
    int pos = 0;
    quoted[pos++] = '"';
    
    // Copy with quote doubling
    for (int i = 0; field[i]; i++) {
        quoted[pos++] = field[i];
        if (field[i] == '"') {
            // Add an extra quote
            quoted[pos++] = '"';
        }
    }
    
    // Add closing quote and null terminator
    quoted[pos++] = '"';
    quoted[pos] = '\0';
    
    return quoted;
}




// This function parses one field from a CSV line
// It updates the position pointer to the start of the next field
char* parse_csv_field(const char* line, int* position) {
    int start = *position;
    int end;
    bool in_quotes = false;
    
    // Check if field starts with quotes
    if (line[start] == '"') {
        in_quotes = true;
        start++; // Skip the opening quote
        
        // Find the closing quote (accounting for doubled quotes)
        end = start;
        while (line[end]) {
            if (line[end] == '"') {
                // Check if it's a doubled quote
                if (line[end+1] == '"') {
                    end++; // Skip one of the quotes
                } else {
                    break; // Found closing quote
                }
            }
            end++;
        }
        
        // Update position to after the closing quote and comma
        *position = end + 2;
    } else {
        // For non-quoted fields, find the next comma
        end = start;
        while (line[end] && line[end] != ',') {
            end++;
        }
        
        // Update position to after the comma
        *position = end + 1;
    }
    
    // Copy the field contents
    int length = end - start;
    char* field = malloc(length + 1);
    
    // Handle doubled quotes during copy for quoted fields
    if (in_quotes) {
        int write_pos = 0;
        for (int read_pos = start; read_pos < end; read_pos++) {
            field[write_pos++] = line[read_pos];
            // Skip the next quote if it's a doubled quote
            if (line[read_pos] == '"' && line[read_pos+1] == '"') {
                read_pos++;
            }
        }
        field[write_pos] = '\0';
    } else {
        // Simple copy for non-quoted fields
        strncpy(field, line + start, length);
        field[length] = '\0';
    }
    
    return field;
}

// Example function to parse a full CSV line
Game* parse_csv_line(const char* line) {
    int position = 0;
    
    // Parse each field
    char* title = parse_csv_field(line, &position);
    char* genre = parse_csv_field(line, &position);
    char* platform = parse_csv_field(line, &position);
    
    // Create game object
    Game* game = create_game(title, genre, platform);
    
    // Free the temporary strings
    free(title);
    free(genre);
    free(platform);
    
    return game;
}


*/