Game Name: Maze
Name: Kevin Mesquita (20175535)
Date: 17/10/2021
Class: UCP



How To Use:
2 Ways of running the program, one that lets you see the whole map
and the other one allows you to change visability

1. To only see full map, just run 'make' in the file directory through bash
    followed by './maze <filename>' to play the Game
    (filename is name of file containing game metadata)

2. To have an obscured map, run 'make DARK=1' in the file directory through bash
    followed by './maze <filename> n' where n is how many tiles around the player is visible
    (filename is name of file containing game metadata)

The controls of the game are simple, w,a,s,d to move (^,v,>,<) around and you need to find the 
end tile 'X' and move to it to win.
There is also a snake '~' which will chase the player, if it gets to the player before the player reaches
the the goal, you lose.



Dependencies:
stdlib.h --> General C library for basic functionality
stdio.h --> General C library for input and output
string.h --> General C library for manipulating arrays
math.h --> General C library containing complex math functions

(along with their respective header files)
dataconversion.c --> converts and prints maze data
map.c --> provides metadata information about maze and objects
maze.c --> contains main which runs the program
termincal.c --> allows input to not show up on termincal
movement.c --> handles the movement of the player
snake.c --> handles the snake movement to the player
linkedlist.c --> handles saving and undoing moves
readfile.c --> handles reading in metadata from a file
