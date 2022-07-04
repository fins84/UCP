/**
 * file: maze.c
 * author: Kevin Mesquita
 * date: 2021-17-10
 * purpose: Bringing together dataconversion.c, map.c, terminal.c,
 *          movement.c, linkedlist.c, readfile.c and snake.c to create a maze game, this file has the
 *          main() function.
 * 
 * valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./maze map.txt
 */

/*Including standarl c libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Including self made functions*/
#include "map.h"
#include "dataconversion.h"
#include "movement.h"
#include "readfile.h"
#include "snake.h"
#include "linkedlist.h"


int main(int argc, char** argv){
    /*Setting up variables*/
    int** metadataTable;
    int metadataAmount, x, y, i, end_cond;
    char** gridRay;
    char move = 'w';
    char* filename = argv[1];
    l_head* movesave;
    l_node* temp, *next;
    l_data* data;
    
    end_cond = 0;

    /**
     * using conditional compilation to tell whether to read argv
     * value for certain visability in the maze (if Dark is defined)
     * 
     * if dark is not defined, using standard if(true) to print whole maze
     */


    #ifdef DARK
    if(argc == 3 && atoi(argv[2]) >= 0){
    #else
    if(argc == 2){
    #endif
        read_txt(&metadataTable, &metadataAmount, &x, &y, filename);
        sort_list(metadataTable, metadataAmount);
        /*read in and sort the metadataTable contents from a file*/

        movesave = (l_head*)malloc(sizeof(l_head));
        data = (l_data*)malloc(sizeof(l_data));
        /**
        * Creating a 2 dimensional character array
        * has +1 to bounds as for string arrays '\0' ending
        */

        input_fields(metadataTable, metadataAmount, data, 'w');
        insert_first(data, movesave);
        /*saving map data to first node of linked list*/

        gridRay = (char**)malloc((sizeof(char *)*(x)));
        for(i = 0; i<x; i++){
            gridRay[i] = (char*)malloc((sizeof(char)*(y)));
            memset(gridRay[i], 0, sizeof(char)*(y));
        }
        /*creating printable field and using memset to make sure its all clear*/

        do{
            system("clear");
            metadata_convert(metadataTable,metadataAmount, x, y, gridRay, move);
            /*clear field and update printable field (gridRay)*/

            do{
                system("clear");
                #ifdef DARK
                if(atoi(argv[2])==0){
                    print_converted_f(gridRay, x, y, argv, 1, metadataTable);
                }
                else{
                    print_converted_d(gridRay, x, y, argv, argc, metadataTable);
                }
                #else
                print_converted_f(gridRay, x, y, argv, 1, metadataTable);
                #endif
                /*printinf field based on conditional compilation on whether Dark defined and visability parameter*/

                get_move(&move);

            }while(move != 'w' && move != 'a' && move != 's' && move != 'd' && move != 'u' && movesave->n_index>1);
            /*until valid input, don't make a move*/

            if(move == 'w' || move == 'a' || move == 's' || move == 'd'){
                if(isfree(move, metadataTable, metadataAmount, x, y) == 0){
                    movement(metadataTable, metadataAmount, move);
                }
                s_move(metadataTable, metadataAmount, x, y);
                data = (l_data*)malloc(sizeof(l_data));
                input_fields(metadataTable, metadataAmount, data, move);
                add_node(data, movesave);
            } /* if move made, update player and snake positiona and save to linked list*/
            else if(move == 'u' && movesave->n_index>1){
                undo_move(metadataTable,metadataAmount, &move, movesave);
            }/*undo move if user inputs 'u'*/
            else if(move == 'u' && movesave->n_index==1){
                move = 'w';
            }/*if at first move, make sure player points up when undo pressed*/
            
            end_cond = end_cond_check(metadataTable, metadataAmount);  
            /*check if player reaches goal or snake reaches player*/

        }while(end_cond == 0);
        /*repeat until one of two end conditions happen (goal or snake get player)*/

        system("clear");
        metadata_convert(metadataTable,metadataAmount, x, y, gridRay, move);
        #ifdef DARK
        if(argv[2]==0){
            print_converted_f(gridRay, x, y, argv, 1, metadataTable);
        }
        else{
            print_converted_d(gridRay, x, y, argv, argc, metadataTable);
        }
        #else
        print_converted_f(gridRay, x, y, argv, 1, metadataTable);
        #endif
        if(end_cond == 1){printf("\nYou won!\n");}
        if(end_cond == 2){printf("\nYou Lost!\n");}
        /*print field of player in snake/goal and tell them whether they won or not*/
    }
    else{
        printf("\nInvalid number of arguments passed (argc != 2)\n");
    }
    /**
     * When DARK is defined and no argv values have been inputed 
     */


    /*free if malloced data if game has run properly*/
    #ifdef DARK
    if(argc == 3 && atoi(argv[2])>=0){
    #else
    if(argc == 2){
    #endif
        for(i = 0; i< x; i++){
            free(gridRay[i]);
        }
        free(gridRay);

        for(i = 0; i< metadataAmount; i++){
            free(metadataTable[i]);
        }
        free(metadataTable);
        /*Freeing the rows in the malloc'd arrays before freeing the column pointer*/

        temp = movesave->start;
        for(i = 0; i<movesave->n_index; i++){
            next = temp->next;
            free(temp->data);
            free(temp);
            temp = next;
        }
        free(movesave);
        /*free linked list*/
    }
    
    return 0;
}