#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <csv.h>
#include "hash.h"
#include "game.h"

// below is all boots NEEDS TO BE REWORKED!!!! treat as pseudocode

// Structure to hold temporary field data during parsing
typedef struct {
    hash_table_t *ht; // for storing completed records
    char* fields[3];  // title, genre, platform
    int field_count; // How many fields we've seen in current record
} ParserData;

// Callback for each field
void field_callback(void *field, size_t size, void *data);

// Callback for end of record
void record_callback(int c, void *data);

// Function to load games from CSV file
bool load_games(const char* filename, hash_table_t *ht);

// Function to write a field with proper CSV escaping
void write_csv_field(FILE* fp, const char* field);

// Function to save games to CSV file
bool save_games(const char* filename, hash_table_t *ht);


/* Below is a whole bunch of assorted notes and references in case I get confused as to whats going on.
Much of this is not even being implemented now that I've switched to using csv.h


boots description of the logic:

***********
Parsing Lifecycle
Let's walk through the process:

Start parsing the CSV file

Parser encounters a field ("Super Mario Bros.")

Calls your field callback
Your callback stores it in parser_data.fields[0]
Increments parser_data.field_count to 1
Parser encounters another field ("Platformer")

Calls your field callback
Your callback stores it in parser_data.fields[1]
Increments parser_data.field_count to 2
Parser encounters another field ("NES")

Calls your field callback
Your callback stores it in parser_data.fields[2]
Increments parser_data.field_count to 3
Parser reaches end of line

Calls your record callback
Your callback creates a new Game object from the fields
Adds this Game to parser_data.hash_table
Resets parser_data.field_count to 0
Parser encounters next field of next record

Process repeats, reusing the same parser_data structure
The ParserData is like a workbench that you keep reusing 
for each record. You collect parts (fields), assemble them into a Game, 
put that Game on a shelf (hash table), then clear the workbench for the next set of parts.


*********************

+----------------+                  +------------------+
|                |  "Here's a       |                  |
|  CSV Library   |  field/record"   |  Your Code       |
|  (libcsv)      +----------------->+                  |
|                |                  |                  |
|  Handles:      |                  |  Handles:        |
|  - Parsing     |  Calls your      |  - Game objects  |
|  - Field       |  functions       |  - Hash table    |
|    detection   |                  |  - Business      |
|  - Record      |                  |    logic         |
|    detection   |                  |                  |
+----------------+                  +------------------+

CSV Library: Focuses on the syntax of CSV
Your Code: Focuses on the semantics (meaning) of the data



High-Level Description of CSV Handling Implementation
Structure Overview
The CSV handling implementation follows a callback-based event-driven approach:

Parser Initialization: We set up a csv_parser instance from libcsv
Data Collection: As the parser reads fields and records, it calls our callback functions
Data Storage: The callbacks populate our hash table with game objects
Key Components
1. Parser Data Structure
typedef struct {
    HashTable* ht;
    char* fields[3];  // title, genre, platform
    int field_count;
} ParserData;

This structure holds temporary state during parsing:

A reference to our hash table
Array to store the current record's fields
A count of how many fields we've processed in the current record
2. Callback Functions
Field Callback: Called for each field in a CSV record

Receives the field content, size, and our parser data
Stores the field in our temporary array
Increments the field counter
Record Callback: Called at the end of each record (row)

Creates a new Game object from the collected fields
Inserts the Game into the hash table
Frees the temporary field storage
Resets the field counter for the next record
3. Main Processing Function
The load_games function:

Opens the CSV file
Initializes the parser
Sets up the parser data structure
Reads chunks of the file in a loop
Passes each chunk to the CSV parser
Finalizes parsing
Cleans up resources
4. Writing Implementation
For writing:

We manually handle CSV formatting (since libcsv doesn't provide writing functions)
The write_csv_field function properly escapes fields with quotes when needed
The save_games function iterates through the hash table and writes each game as a CSV record
Flow of Execution
Initialize the parser
Begin reading the file in chunks
For each chunk, the parser finds fields and calls our field callback
When a full record is processed, the record callback is called
The record callback creates a game and adds it to our hash table
6


Boots
continue

Boots
Flow of Execution (continued)
After reading the entire file, finalize parsing to handle any incomplete records
When saving, iterate through all hash table entries
For each game object, format and write its fields as a CSV record
Properly escape any special characters in the fields according to CSV standards
The Callback Pattern Explained
The callback pattern used by libcsv is often called an "event-driven" or "SAX-style" parsing approach (similar to how XML SAX parsers work):

You provide the callbacks: These are functions that get called when specific events occur
The parser drives the process: It reads the file and calls your callbacks at appropriate times
Your callbacks take action: They process data incrementally as it's encountered
This is very memory-efficient because:

You don't need to load the entire file into memory
You process data on-the-fly as it's parsed
You can build your data structures incrementally
Error Handling Strategy
The implementation includes several layers of error handling:

File opening errors (can't find or access the file)
Parser initialization errors (problems with the CSV parser)
Parsing errors (malformed CSV data)
Field allocation errors (memory issues)
Each error condition returns false from the load_games function, allowing the caller to take appropriate action.

Customization Points
There are several places you could customize this implementation:

Change the number of fields expected per record
Add validation of field values
Skip header rows
Handle different CSV dialects (by configuring the parser)
Add logging or detailed error reporting
This event-driven, callback-based approach is ideal for processing large CSV files efficiently while maintaining a clean separation between parsing logic and application-specific data handling.




*/
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