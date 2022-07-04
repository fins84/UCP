#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*including standard libraries*/

#include "linkedlist.h"
/*header file include*/

/**
 * @brief adds a node to the end of the linked list and then saves data of map inside of void* data
 * 
 * @param data , struct which contains information about the map field at a given turn
 * @param linked_l , the linked list struct header
 */
void add_node(l_data* data,l_head* linked_l){
    int i, index;
    l_node* curr, *prev;
    /*setting up variables*/
    
    index = linked_l->n_index;
    curr = linked_l->start;
    

    for(i = 0; i < index -1; i++){
        curr = curr->next;
    }
    prev = curr;
    /*get last node*/

    curr->next = (l_node*)malloc(sizeof(l_node));
    /*add node to end of linked list*/
    curr = curr->next;
    curr->prev = prev;
    index++;
    linked_l ->n_index++;
    curr->data = data;
    /*add data to the new node*/
    curr->index = index;
    linked_l->end = curr;
}

/**
 * @brief sets the fields in the 'data' struct to the current field positions
 * 
 * @param metadataTable (int**) contains the locations and types of all objects on the field
 * @param metadataAmount (int) contains how many objects there are
 * @param node (l_data*) the data structure that data will be inputed into
 * @param move (char) the last move the player made
 */
void input_fields(int** metadataTable, int metadataAmount, l_data* node, char move){
    node->move = move;
    node->snakepos[0] = metadataTable[2][0];
    node->snakepos[1] = metadataTable[2][1];
    node->playerpos[0] = metadataTable[0][0];
    node->playerpos[1] = metadataTable[0][1];
    /*give all variables the current state of the field*/
}

/**
 * @brief inserts the first node into the linked list (when its empty)
 * 
 * @param data (l_data*) the data structure that data contains map contents
 * @param linked_l (l_head*) the header of the linked list
 */
void insert_first(l_data* data, l_head* linked_l){
    int n_index;
    l_node* first_node;
    /*setup variables*/

    n_index = 1;
    linked_l->n_index = n_index;
    /*update header parameter*/

    linked_l->start = (l_node*)malloc(sizeof(l_node));
    linked_l->end = linked_l->end;
    first_node = linked_l->start;
    /*add node*/


    first_node->data = data;
    first_node->index = n_index;
    /*fill out contents of first node*/
}


/**
 * @brief removes the last node of the linked list and returns the contntents of the new last node
 * 
 * @param linked_l (l_head*) header of linked list
 * @return void* returns contents of deleted node
 */
void* remove_last(l_head* linked_l){
    void* outData = linked_l->end->prev->data;
    /*contents of last node*/

    l_node* temp;
    temp = linked_l->end->prev;
    temp->next = NULL;
    /*update new last node*/

    linked_l->n_index -= 1;
    /*update number of objects in linked list*/

    free(linked_l->end->data);
    free(linked_l->end);
    /*free last node*/

    linked_l->end = temp;
    /*update last node of linked list*/

    return outData;
}


/**
 * @brief removes last node of linked list and then sets all map data of field to new end node fields
 * 
 * @param metadataTable (int**) contains the locations and types of all objects on the field
 * @param metadataAmount (int) contains how many objects there are
 * @param move (char) the last move the player made
 * @param linked_l (l_head*) header of linked list
 */
void undo_move(int** metadataTable, int metadataAmount, char* move,l_head* linked_l){
    l_data* data;
    data = remove_last(linked_l);
    /*delete last node*/

    *move = data->move;
    metadataTable[0][0] = data->playerpos[0];
    metadataTable[0][1] = data->playerpos[1];
    metadataTable[2][0] = data->snakepos[0];
    metadataTable[2][1] = data->snakepos[1];
    /*update positions of objects*/
}