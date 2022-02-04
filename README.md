# Pacenstein

## Introduction
This is a schoolproject made for Hogeschool Utrecht. With our take on this project we made a first-person PacMan game. Except instead of simply making PacMan in 2D, we did it in 3D. This was done using raycasting techniques, like the original Doom, or Wolfenstein 3D.

## Copyright notice
Lode Vandenvenne has some great explanations on raycasting, and we used their website for most of our raycasting engine. Check their website for a lot of tutorials and clear explanations.

- Lode Vandevenne's website: [lodev.org](lodev.org)
- Lode Vandevenne's raycasting tutorials: [lodev raycasting](https://lodev.org/cgtutor/raycasting.html)

## Playing the game
You can download a Windows or Linux executable by going to the release page and run it. Or you can build the source yourself.

### Building the game
Make sure the following dependencies are installed:
1. SFML (note for windows users below)
2. make
3. gcc >= 8 (MinGW-w64 works fine for both make and gcc)

If all of the above are installed you can simply run make from the project folder to build the game. An executable will be created which can also be then be ran, or you can make with the target `run` to build and run the game, the executable will still be created.

#### SFML and Windows
SFML on windows is statically linked because of issues with Path. This means that the SFML library has to be in a certain directory on your system, namely `C:\Program Files\SFML-x.x.x` where the xs are the verion numbers. Or, if you don't want this, you can run the make command as `make SFML_DIR=custom/path/to/sfml`.

## About the game
> Pac-Man (パックマン Pakkuman), formerly known as Puck Man in Japan, is the main protagonist of the Pac-Man series. He is the husband of Ms. Pac-Man, and the father of Baby Pac-Man and Jr. Pac-Man. 
> 
> The Ghosts (also known as Monsters or Ghost Monsters) are the main enemies of the Pac-Man series and have antagonized Pac-Man and all of Pac-Land in their appearances. The most notable ghosts are the four members of the Ghost Gang - Blinky, Pinky, Inky and Clyde - who have appeared throughout the series as both antagonists and protagonists.
> 
> Source: https://pacman.fandom.com/wiki/Pac-Man_Wiki

Walk through a maze, "eat" PacDots, gain points, win! This is all you can do in this game.

### Points
You start off with 3 lives and every 10000, 15000, 20000, or not at all - based on the difficulty - you will gain an extra live. Points are gained by "eating" PacDots, each of which gives 10 points. Aside from regular PacDots you will also come across PowerPellets, those give you a staggering 100 points and grant you the ability to eat the ghosts. Eating ghosts also gives points, 200 for the first, 400 for the second and then 800 and 1600 for the last two respectively. PacDots, PowerPellets, and ghosts are not the only ways to gain points, on occasion a fruit will spawn. 

#### Fruits
Fruits give bonus points and will always spawn in the center of the map. There are several different fruits worth the following points:
- 🍒 Cherry: 100 points.
- 🍓 Strawberry: 300 points
- 🍊 Orange: 500 points
- 🍎 Apple: 700 points
- 🍈 Melon: 1000 points
- Galaxian Flagship: 2000 points (for which no unicode character exists unfortunately)
- 🔔 Bell: 3000 points
- 🔑 Key: 5000 points

Upon collecting a fruit the points are awarded to the player and the fruit is added to the collection.

### Ghosts
Ghosts are the enemy. They will hunt you down and getting caught by one reduces your life by one point. If your lives run out, the game ends. Ghosts become the hunted when you eat a PowerPellet, this will cause them to turn blue and scatter. Once a ghost is eaten you get bonus points and the ghost will return to their home in the center of the map. After the PowerPellet's effect has worn off they will resume their hunt.

#### Ghost AI
Each ghost has a unique AI. Blinky - the red one - will alway directly focus on PacMan. Pinky - colored pink, who'd have guessed - targets the tile 4 spaces in front of PacMan. Inky - who's cyan - tries to keep pacman between himself and Blinky by taking the tile 2 in front of PacMan, drawing a line from Blinky to that tile, and doubling the line, the end of the line is where Inky will set it's eyes. At last, but not least, Clyde - the orange ghost - is like Blinky, he will target PacMan directly, but as soon as he comes within 8 tiles, he becomes scared and will target a corner until he is outside those 8 tiles, then he'll switch back to targeting PacMan, and so on. By combining their AI's PacMan will get closed in if he's not careful.
