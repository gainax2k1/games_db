# Motivation #
This is my first independent project for my Boot.Dev course. The goal is to create a videogame database for videogame collection. I wanted to practice my memory management in C, so it utilizes a hash linked list for storage, and file I/O using the libcsv library.

This includes:
- text based interface with color
- adding/removing/editing games to the database
- sorting and searching by name
- saving to file (in .CSV)

## Quickstart
### Dependencies
- [libcsv](http://sourceforge.net/projects/libcsv/)
- on Linux, you can install with apt-get:
```bash
sudo apt-get install libcsv-dev
```

### Building
```bash
gcc main.c game.c hash.c menu.c colors.c fileio.c -o main -lcsv
```

### Running
```bash
./main
```

# 🤝 Contributing
<h2>Submit a pull request</h2>

If you'd like to contribute, please fork the repository and open a pull request to the `main` branch.


## Sample output:
- Note: The actual output in terminal will be color coded by console, genre, etc.
  
<pre>$ ./main
Loaded game database from gamesdb.csv

-----<span style="background-color:#F2F2F2"><font color="#333333"> GAME DATABASE </font></span>-----

-------<b> MAIN MENU </b>-------
[<b>0</b>] List games 
[<b>1</b>] Add videogame 
[<b>2</b>] Edit videogame 
[<b>3</b>] Remove videogame 
[<b>4</b>] Save and exit 
[<b>5</b>] Exit without saving 
<b>Enter your choice (0-5): </b>0

-------<b> GAMES LIST </b>-------

<font color="#88807C">Title:</font><font color="#D3D7CF">  Blue Dragon                         </font><font color="#88807C">Genre:</font><font color="#75507B"> RPG         </font><font color="#D3D7CF"> </font><font color="#88807C">Platform:</font><font color="#4E9A06"> XBox 360     </font><font color="#D3D7CF"> </font>
<font color="#88807C">Title:</font><font color="#D3D7CF">  Chrono Trigger                      </font><font color="#88807C">Genre:</font><font color="#75507B"> RPG         </font><font color="#D3D7CF"> </font><font color="#88807C">Platform:</font><font color="#CC0000"> SNES         </font><font color="#D3D7CF"> </font>
<font color="#88807C">Title:</font><font color="#D3D7CF">  Doom: Eternal                       </font><font color="#88807C">Genre:</font><font color="#4E9A06"> FPS         </font><font color="#D3D7CF"> </font><font color="#88807C">Platform:</font><font color="#3465A4"> PlayStation 4 </font><font color="#D3D7CF"> </font>
<font color="#88807C">Title:</font><font color="#D3D7CF">  Final Fantasy                       </font><font color="#88807C">Genre:</font><font color="#75507B"> RPG         </font><font color="#D3D7CF"> </font><font color="#88807C">Platform:</font><font color="#CC0000"> NES          </font><font color="#D3D7CF"> </font>
<font color="#88807C">Title:</font><font color="#D3D7CF">  Final Fantasy II                    </font><font color="#88807C">Genre:</font><font color="#75507B"> RPG         </font><font color="#D3D7CF"> </font><font color="#88807C">Platform:</font><font color="#CC0000"> SNES         </font><font color="#D3D7CF"> </font>
<font color="#88807C">Title:</font><font color="#D3D7CF">  Final Fantasy III                   </font><font color="#88807C">Genre:</font><font color="#75507B"> RPG         </font><font color="#D3D7CF"> </font><font color="#88807C">Platform:</font><font color="#CC0000"> SNES         </font><font color="#D3D7CF"> </font>
<font color="#88807C">Title:</font><font color="#D3D7CF">  Final Fantasy VII                   </font><font color="#88807C">Genre:</font><font color="#75507B"> RPG         </font><font color="#D3D7CF"> </font><font color="#88807C">Platform:</font><font color="#3465A4"> PlayStation 1 </font><font color="#D3D7CF"> </font>
<font color="#88807C">Title:</font><font color="#D3D7CF">  Final Fantasy VIII                  </font><font color="#88807C">Genre:</font><font color="#75507B"> RPG         </font><font color="#D3D7CF"> </font><font color="#88807C">Platform:</font><font color="#3465A4"> PlayStation 1 </font><font color="#D3D7CF"> </font>
<font color="#88807C">Title:</font><font color="#D3D7CF">  Final Fantasy X                     </font><font color="#88807C">Genre:</font><font color="#75507B"> RPG         </font><font color="#D3D7CF"> </font><font color="#88807C">Platform:</font><font color="#3465A4"> PlayStation 2 </font><font color="#D3D7CF"> </font>
<font color="#88807C">Title:</font><font color="#D3D7CF">  GOAL!                               </font><font color="#88807C">Genre:</font><font color="#06989A"> Sports      </font><font color="#D3D7CF"> </font><font color="#88807C">Platform:</font><font color="#CC0000"> SNES         </font><font color="#D3D7CF"> </font>
<font color="#88807C">Title:</font><font color="#D3D7CF">  Kirby&apos;s Air Rider                   </font><font color="#88807C">Genre:</font><font color="#06989A"> Sports      </font><font color="#D3D7CF"> </font><font color="#88807C">Platform:</font><font color="#CC0000"> GameCube     </font><font color="#D3D7CF"> </font>
<font color="#88807C">Title:</font><font color="#D3D7CF">  Lufia II: Rise of the Sinistrals    </font><font color="#88807C">Genre:</font><font color="#75507B"> RPG         </font><font color="#D3D7CF"> </font><font color="#88807C">Platform:</font><font color="#CC0000"> SNES         </font><font color="#D3D7CF"> </font>
<font color="#88807C">Title:</font><font color="#D3D7CF">  Mario Kart                          </font><font color="#88807C">Genre:</font><font color="#06989A"> Sports      </font><font color="#D3D7CF"> </font><font color="#88807C">Platform:</font><font color="#CC0000"> SNES         </font><font color="#D3D7CF"> </font>
<font color="#88807C">Title:</font><font color="#D3D7CF">  Rythm Haven                         </font><font color="#88807C">Genre:</font><font color="#3465A4"> Music/Rythm </font><font color="#D3D7CF"> </font><font color="#88807C">Platform:</font><font color="#CC0000"> Wii          </font><font color="#D3D7CF"> </font>
<font color="#88807C">Title:</font><font color="#D3D7CF">  Sonic the Hedghog                   </font><font color="#88807C">Genre:</font><font color="#CC0000"> Platformer  </font><font color="#D3D7CF"> </font><font color="#88807C">Platform:</font><font color="#48B9C7"> Genesis      </font><font color="#D3D7CF"> </font>
<font color="#88807C">Title:</font><font color="#D3D7CF">  Tecmo Superbowl                     </font><font color="#88807C">Genre:</font><font color="#06989A"> Sports      </font><font color="#D3D7CF"> </font><font color="#88807C">Platform:</font><font color="#CC0000"> SNES         </font><font color="#D3D7CF"> </font>
<font color="#88807C">Title:</font><font color="#D3D7CF">  Tetris                              </font><font color="#88807C">Genre:</font><font color="#C4A000"> Puzzle      </font><font color="#D3D7CF"> </font><font color="#88807C">Platform:</font><font color="#CC0000"> GameBoy      </font><font color="#D3D7CF"> </font>
<font color="#88807C">Title:</font><font color="#D3D7CF">  Viewtiful Joe                       </font><font color="#88807C">Genre:</font><font color="#CC0000"> Platformer  </font><font color="#D3D7CF"> </font><font color="#88807C">Platform:</font><font color="#CC0000"> GameCube     </font><font color="#D3D7CF"> </font>
<font color="#88807C">Title:</font><font color="#D3D7CF">  Xenoblade Chronicles                </font><font color="#88807C">Genre:</font><font color="#75507B"> RPG         </font><font color="#D3D7CF"> </font><font color="#88807C">Platform:</font><font color="#CC0000"> Wii          </font><font color="#D3D7CF"> </font>
<font color="#88807C">Title:</font><font color="#D3D7CF">  Xenoblade Chronicles X              </font><font color="#88807C">Genre:</font><font color="#75507B"> RPG         </font><font color="#D3D7CF"> </font><font color="#88807C">Platform:</font><font color="#CC0000"> Wii U        </font><font color="#D3D7CF"> </font>
<font color="#88807C">Title:</font><font color="#D3D7CF">  Zelda                               </font><font color="#88807C">Genre:</font><font color="#75507B"> RPG         </font><font color="#D3D7CF"> </font><font color="#88807C">Platform:</font><font color="#CC0000"> NES          </font><font color="#D3D7CF"> </font>
<font color="#88807C">Title:</font><font color="#D3D7CF">  Zelda Windraker                     </font><font color="#88807C">Genre:</font><font color="#75507B"> RPG         </font><font color="#D3D7CF"> </font><font color="#88807C">Platform:</font><font color="#CC0000"> GameCube     </font><font color="#D3D7CF"> </font>
<font color="#88807C">Title:</font><font color="#D3D7CF">  Zelda: Tears of the Kingdom         </font><font color="#88807C">Genre:</font><font color="#75507B"> RPG         </font><font color="#D3D7CF"> </font><font color="#88807C">Platform:</font><font color="#CC0000"> Switch       </font><font color="#D3D7CF"> </font>

</pre>

```bash
------- MAIN MENU -------
[0] List games 
[1] Add videogame 
[2] Edit videogame 
[3] Remove videogame 
[4] Save and exit 
[5] Exit without saving 
Enter your choice (0-5): 1

------- ADD GAME -------
Enter game title: Frequency
------- Genres -------
[0] Unknown     [1] RPG         [2] Puzzle      [3] Sports      [4] Rogue-like  
[5] Music/Rythm [6] Platformer  [7] FPS         [8] Strategy    
-----------------
Enter number for genre (0-Unknown, 1-RPG, etc.): 5
----- Platforms -----
[ 0] Unknown           [ 1] NES               [ 2] SNES              [ 3] N64               [ 4] GameCube          
[ 5] Wii               [ 6] Wii U             [ 7] Switch            [ 8] GameBoy           [ 9] GameBoy Color     
[10] Virtual Boy       [11] GameBoy Advance   [12] DS                [13] DSi               [14] 3DS               
[15] PlayStation 1     [16] PlayStation 2     [17] PlayStation 3     [18] PlayStation 4     [19] PlayStation 5     
[20] PS Portable       [21] PS Vita           [22] XBox              [23] XBox 360          [24] XBox ONE          
[25] XBox Series S/X   [26] Genesis           [27] SegaCD            [28] 32X               [29] Saturn            
[30] Dreamcast         
------------------
Enter number platform (0-Unknwon, 1-NES, etc.): 16
Added game: Frequency

------- MAIN MENU -------
[0] List games 
[1] Add videogame 
[2] Edit videogame 
[3] Remove videogame 
[4] Save and exit 
[5] Exit without saving 
Enter your choice (0-5): 
```
