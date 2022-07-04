/**
 * @file dataconversion.c
 * @author Kevin Mesquita
 * @brief Code for converting and printing metadata
 * @date 2021-09-11
 * 
 */

/*Including standard and self made libraries/functions*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dataconversion.h"

/**
 * @brief Gets the metadata array and converts it into a 2 dimensional array
 * of characters which represent their respective objects
 * This allows for easier printing
 * 
 * @param metadataTable (int Array[][])contains all objects and their positions
 * @param metadataAmount (int) Number of objects in metadataTable
 * @param x (int) Size in x directions of the playable field
 * @param y (int) Size in y direction of the playable field
 * @param gridRay (Char Array[][]) The 2d character array being written to
 * @param move (char) The move (w,a,s,d) the player pressed
 */
void metadata_convert(int **metadataTable, int metadataAmount, int x, int y, char** gridRay, char move){
    int i ,index1, index2;
    for(i = 0; i<(x); i++){
        memset(gridRay[i], 0, sizeof(char)*(y));
    }
    /*Sets all values in gridRay back to 0 after every turn*/

    /*Iterates through each object in metadataTable*/
    for(i = 0; i< metadataAmount; i++){
        index1 = metadataTable[i][0];
        index2 = metadataTable[i][1];
        /*Location of object*/

        if(metadataTable[i][2] == 0){
            if(move == 'w'){
                gridRay[index1][index2] = '^';}
            else if(move == 'a'){
                gridRay[index1][index2] = '<';}
            else if(move == 'd'){
                gridRay[index1][index2] = '>';}
            else if(move == 's'){
                gridRay[index1][index2] = 'V';}
            
            /*Convert object type to respective character (move)*/
        }
        else if(metadataTable[i][2] == 1){
            gridRay[index1][index2] = '~';
        } /*Snake tile set*/
        else if(metadataTable[i][2] == 3){
            gridRay[index1][index2] = 'o';
        }
        else if(metadataTable[i][2] == 2){
            gridRay[index1][index2] = 'X';
        } /*Goal tile set*/
    }
}

void print_converted_f(char** gridRay, int x, int y, char** argv, int argc, int** metadataTable){
    /*Setting up variables*/
    int i,j;

    /*Player current location*/

    /*Print field If DARK not defined or argv input is 0*/
    for(i = 0; i< x; i++ ){
        for(j = 0; j< y; j++ ){
            if(j == 0 && i == 0){printf("#");}
            else if(j == 0 && i == x-1){printf("#");}
            else if(j == y-1 && i == x-1){printf("#");}
            else if(j == y-1 && i == 0){printf("#");}
            else if((j == 0 || j == y-1) && i <= x-1){printf("|");}
            else if((i == 0 || i == x-1) && j <= y-1){printf("-");}
            else if(!gridRay[i][j]){printf(" ");}
            else{printf("%c", gridRay[i][j]);}
        }
        printf("\n");
    }
}

void print_converted_d(char** gridRay, int x, int y, char** argv, int argc, int** metadataTable){
    /*Setting up variables*/
    int i,j, minx, maxx, miny, maxy;
    int object_location[2];

    object_location[1] = metadataTable[0][0];
    object_location[0] = metadataTable[0][1];

 
    minx = object_location[1] - atoi(argv[2]);
    if(minx < 0){minx = 0;}
    maxx = object_location[1] + atoi(argv[2]);
    if(maxx >= x){maxx = x-1;}
    miny = object_location[0] - atoi(argv[2]);
    if(miny < 0){miny = 0;}
    maxy = object_location[0] + atoi(argv[2]);
    if(maxy > y){maxy = y;}
    /*Getting bound values around the character in both x and y direction*/
    /*print values withing bounds*/
    for(i = minx; i<= maxx ; i++){
        for(j = miny; j<= maxy; j++){
            if(j == 0 && i == 0){printf("#");}
            else if(j == 0 && i == x-1){printf("#");}
            else if(j == y-1 && i == x-1){printf("#");}
            else if(j == y-1 && i == 0){printf("#");}
            else if((j == 0 || j == y-1) && i <= x-1){printf("|");}
            else if((i == 0 || i == x-1) && j <= y-1){printf("-");}
            else if(!gridRay[i][j]){printf(" ");}
            else{printf("%c", gridRay[i][j]);}
        }
        printf("\n");
    }
}
