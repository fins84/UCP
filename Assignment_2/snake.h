#ifndef SNAKE_H
#define SNAKE_H

int is_s_free(int** metadataTable, int metadataAmount, int* best_m, int x, int y);
int comp_distance(int* best_m, int* cur_m, int* player_pos);
void s_move(int** metadataTable, int metadataAmount, int x, int y);

#endif