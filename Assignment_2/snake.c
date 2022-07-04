#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
/*include standard libraries*/

#include "movement.h"
/*include header file*/

/**
 * @brief check if a move is in bounds or not
 * 
 * @param metadataTable contents of all objects on field
 * @param metadataAmount number of objects on field
 * @param best_m move to check
 * @param x field size x direction
 * @param y field size y direction
 * @return int (1 if out of bounds, 0 if ind bounds)
 */
int is_s_free(int** metadataTable, int metadataAmount, int* best_m, int x, int y){
    int i, return_val;

    return_val = 1;
    /*
    check if value is in bounds, make return val = 0
    else return val = 1;
    */
   if(best_m[0] > 0 && best_m[0]<= x-1 && best_m[1]> 0 && best_m[1]<= y-1){
       return_val = 0;
   }/*if move is bounds of field*/
    for(i = 0; i< metadataAmount; i++){
        if(metadataTable[i][0] == best_m[0] && metadataTable[i][1] == best_m[1]){
            if(metadataTable[i][2] == 0){
                return_val = 0;
            }/*can move on players position*/
            else if(metadataTable[i][2] == 1 || metadataTable[i][2] == 3 || metadataTable[i][2] == 2){
                return_val = 1;
            }/*can't move on wall position*/
        }
    }
    return return_val;
}

/**
 * @brief uses distance formula to compare to coordinates distance from the player position
 * 
 * @param best_m current place the snake will move
 * @param cur_m new move to compare to best move
 * @param player_pos position of the player object
 * @return int (0 if current move is smaller, 1 if best move is smaller)
 */
int comp_distance(int* best_m, int* cur_m, int* player_pos){
    double cur_d;
    double best_d;
    int return_val;
    double val1, val2;
    /*setup variables*/

    return_val = 1;

    val1 = (double)(cur_m[0] - player_pos[0]);
    val2 = (double)(cur_m[1] - player_pos[1]);
    cur_d = sqrt(abs(val1*val1)+(val2*val2));

    val1 = (double)(best_m[0] - player_pos[0]);
    val2 = (double)(best_m[1] - player_pos[1]);
    best_d = sqrt(abs(val1*val1)+(val2*val2));

    /*distance formula (c^2 = a^2 + b^2)*/

    if(cur_d<=best_d){
        return_val = 0;
    }/*compare the two distances*/
    return return_val;
}


/**
 * @brief moves the snake closer to the player position while not moving on the goal tile and wall tiles
 * 
 * @param metadataTable contents of all objects on field
 * @param metadataAmount number of objects on field
 * @param x field size x direction
 * @param y field size y direction
 */
void s_move(int** metadataTable, int metadataAmount, int x, int y){
    int best_m[2], cur_m[2], player_pos[2], snake_pos[2], repetition[2];
    int i;
    /*setup variables*/

    snake_pos[0] = metadataTable[2][0];
    snake_pos[1] = metadataTable[2][1];
    /*get snake position*/

    cur_m[0] = metadataTable[2][0];
    cur_m[1] = metadataTable[2][1];

    best_m[0] = cur_m[0];
    best_m[1] = cur_m[1];
    /*first move is snake position (in case snake is trapped)*/
    

    player_pos[0] = metadataTable[0][0];
    player_pos[1] = metadataTable[0][1];
    /*get player position*/


    repetition[0] = cur_m[0];
    repetition[1] = cur_m[1];
    /*snake position to get tiles around it*/

    for(i = repetition[0]-1; i<=repetition[0]+1; i++){
        if(i != snake_pos[0]){
            cur_m[0] = i;
            if(is_s_free(metadataTable, metadataAmount, cur_m, x, y) == 0){
                if(comp_distance(best_m, cur_m, player_pos) == 0){
                    best_m[0] = cur_m[0];
                }
            }
        }
    }/*get tiles in the y direction +1 and -1 of snake position and check if they are closer to player
        updating best_m if so
    */
    cur_m[0] = snake_pos[0];
    for(i = repetition[1]-1; i<=repetition[1]+1; i++){
        if(i != snake_pos[1]){
            cur_m[1] = i;
            if(is_s_free(metadataTable, metadataAmount, cur_m, x, y) == 0){
                if(comp_distance(best_m, cur_m, player_pos) == 0){
                    best_m[1] = cur_m[1];
                    best_m[0] = snake_pos[0];
                }
            }
        }
    }/*get tiles in the x direction +1 and -1 of snake position and check if they are closer to player
        updating best_m if so
    */

    metadataTable[2][0] = best_m[0];
    metadataTable[2][1] = best_m[1];
    /*snake position is the best move*/
}