#ifndef LINKEDLIST_H
#define LINKEDLIST_H

typedef struct l_node{
    void* data;
    int index;
    struct l_node* next;
    struct l_node* prev;

}l_node;

typedef struct{
    int n_index;
    l_node* start;
    l_node* end;
}l_head;

typedef struct l_data{
    int index;
    int snakepos[2], playerpos[2];
    char move;
}l_data;

void add_node(l_data* data, l_head* linked_l);
void insert_first(l_data* data, l_head* linked_l);
void input_fields(int** metadataTable, int metadataAmount, l_data* node, char move);
void undo_move(int** metadataTable, int metadataAmount, char* move,l_head* linked_l);
void* remove_last(l_head* linked_l);

#endif