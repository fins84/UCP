#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*include standard libraries*/

#include "readfile.h"
/*include header file*/


/**
 * @brief reads in the metadata File to the maze.c program
 * 
 * @param metadataTable (int**) contains the locations and types of all objects on the field
 * @param metadatAmount (int) Number of objects in metadataTable
 * @param x (int) size of the field in x direction
 * @param y (int) size of the field in  y direction
 * @param filename (char*) the name of file to read from
 */
void read_txt(int*** metadataTable, int *metadatAmount, int *x, int *y,char* filename){
    FILE* file;
    int i, read_n, szx, szy, amount;
    int** read_ray;
    /*setup variables*/


    file = fopen(filename, "r");
    if(file == NULL){
        perror("Error, file doesn't exist");
    }/*open file and check if it exists*/
    else{
        read_n = fscanf(file, "%d %d %d\n", &amount, &szx, &szy);
        *x = szx;
        *y = szy;
        *metadatAmount = amount;
        /*first line setting variables, field size, metadataAmount*/

        if(read_n == 0){
            perror("Error reading form file, not enough contents");
        }/*check if there are information on objects in field*/

        read_ray = (int**)malloc(sizeof(int*)*amount);
        for(i = 0; i< amount; i++){
            read_ray[i] = (int*)malloc(sizeof(int)*3);
        } /*setting up metadataTable array*/
        for(i = 0; i< amount; i++){
            read_n = fscanf(file, "%d %d %d\n", &read_ray[i][0], &read_ray[i][1], &read_ray[i][2]);
            if(read_n == 0){
                perror("Error reading form file, not enough contents");
            }/*set contents of file to metadataTable and check for any errors*/
        }
        *metadataTable = read_ray;
        /*output the read contents*/
        fclose(file);
    }
}

/**
 * @brief sorts metadataTable to a format usable by the maze.c program
 * 
 * @param metadataTable (int**) contains the locations and types of all objects on the field
 * @param metadataAmount (int) Number of objects in metadataTable
 */
void sort_list(int** metadataTable, int metadataAmount){
    int i;
    int* temp;
    /*setup variables*/

    for(i = 0; i<metadataAmount; i++){
        if(metadataTable[i][2] == 0){
            temp = metadataTable[0];
            metadataTable[0] = metadataTable[i];
            metadataTable[i] = temp;
        }/*player first index*/
        if(metadataTable[i][2] == 2){
            temp = metadataTable[1];
            metadataTable[1] = metadataTable[i];
            metadataTable[i] = temp;
        }/*goal second index*/
        if(metadataTable[i][2] == 1){
            temp = metadataTable[2];
            metadataTable[2] = metadataTable[i];
            metadataTable[i] = temp;
        }/*snake third index*/
    }
}