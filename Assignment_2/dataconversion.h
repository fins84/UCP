#ifndef DATACONVERSION_H
#define DATACONVERSION_H

void metadata_convert(int **metadataTable, int metadataAmount, int x, int y, char** gridRay, char move);
void print_converted_f(char** gridRay, int x, int y, char** argv, int argc, int** metadataTable);
void print_converted_d(char** gridRay, int x, int y, char** argv, int argc, int** metadataTable);
#endif