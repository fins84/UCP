/*Including standard and premade libraries*/
#include <stdlib.h>
#include <stdio.h>
#include "terminal.h"
#include "movement.h"

/**
 * @brief Get the user input (w,a,s,d) for where they want to move in the field
 * This makes use of terminal.c file so that user input is not shown on the screen
 * 
 * @param move (char) The inputed value from the user
 */
void get_move(char* move){
    /*Setting up variables*/
    char move_check;

    /*Dont print input to screen*/
    disableBuffer();
    printf("Make a move: (w/a/s/d)\n");
    scanf(" %c", &move_check);
    if(move_check == 'w' || move_check == 'a' || move_check == 's' || move_check == 'd' || move_check == 'u'){
        *move = move_check;
    }
    else{*move = ' ';}
    /* if input = (w/a/s/d) then make move equal it else make it ' '*/
    enableBuffer();
    /*Enable input to screen*/
}

/**
 * @brief Checks whether the move that the user inputed is valid and outputs a 0 for valid and 1 for invalid move
 * 
 * @param move  (char) last inputed move from player
 * @param metadataTable (int Array[][])contains all objects and their positions
 * @param metadataAmount (int) Number of objects in metadataTable
 * @param x (int) Size in x directions of the playable field
 * @param y (int) Size in y directions of the playable field
 * @return int (0 for valid, 1 for invalid)
 */
int isfree(char move, int** metadataTable, int metadataAmount, int x, int y){
    int return_val = 0;
    int i;
    if(move == 'w'){
        for(i = 2; i< metadataAmount; i++){
            /*check if any objects in the direction of 'w' of the tile*/
            if((metadataTable[0][0] - 1 == metadataTable[i][0] && metadataTable[0][1] == metadataTable[i][1]) || metadataTable[0][0]-1 == 0){
                return_val = 1;
            }
        }
    }
    else if(move == 'a'){
        for(i = 2; i< metadataAmount; i++){
            /*check if any objects in the direction of 'a' of the tile*/
            if((metadataTable[0][0] == metadataTable[i][0] && metadataTable[0][1] - 1 == metadataTable[i][1]) || metadataTable[0][1]-1 == 0){
                return_val = 1;
            }
        }
    }
    else if(move == 's'){
        for(i = 2; i< metadataAmount; i++){
            /*check if any objects in the direction of 's' of the tile*/
            if((metadataTable[0][0] + 1 == metadataTable[i][0] && metadataTable[0][1] == metadataTable[i][1]) || metadataTable[0][0]+1 == x-1){
                return_val = 1;
            }
        }
    }
    else if(move == 'd'){
        for(i = 2; i< metadataAmount; i++){
            /*check if any objects in the direction of 'd' of the tile*/
            if((metadataTable[0][0] == metadataTable[i][0] && metadataTable[0][1] + 1 == metadataTable[i][1]) || metadataTable[0][1]+1 == y-1){
                return_val = 1;
            }
        }
    }
    return return_val;
}

/**
 * @brief changes the location to of the player object to the respective location (w,a,s,d)
 * 
 * @param metadataTable (int Array[][])contains all objects and their positions
 * @param metadataAmount (int) Number of objects in metadataTable
 * @param move (char) last inputed move from player
 */
void movement(int** metadataTable, int metadataAmount, char move){
    if(move == 'w'){
        /*move one tile up*/
        metadataTable[0][0] -= 1;
    }
    else if(move == 's'){
        /*move one tile down*/
        metadataTable[0][0] += 1;
    }
    else if(move == 'a'){
        /*move one tile left*/
        metadataTable[0][1] -= 1;
    }
    else if(move == 'd'){
        /*move one tile right*/
        metadataTable[0][1] += 1;
    }
}

/**
 * @brief check if player has reached goal or snake has reached the player
 * 
 * @param metadataTable (int Array[][])contains all objects and their positions
 * @param metadataAmount (int) Number of objects in metadataTable
 * @return int (1 for goal, 2 for snake, 0 for not end)
 */
int end_cond_check(int** metadataTable, int metadataAmount){
    int return_val;
    
    return_val = 0;
    if((metadataTable[0][0] == metadataTable[1][0]) && (metadataTable[0][1] == metadataTable[1][1])){
        return_val = 1;
    }/*player reached goal*/
    else if((metadataTable[0][0] == metadataTable[2][0]) && (metadataTable[0][1] == metadataTable[2][1])){
        return_val = 2;
    }/*player reached snake*/
    return return_val;
}