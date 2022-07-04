#ifndef MOVEMENT_H
#define MOVMENT_H

void get_move(char* move);
int isfree(char move, int** metadataTable, int metadataAmount, int x, int y);
void movement(int** metadataTable, int metadataAmount, char move);
int end_cond_check(int** metadataTable, int metadataAmount);

#endif