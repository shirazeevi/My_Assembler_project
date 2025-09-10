#ifndef INSETR_H
#define INSETR_H
#include "pass1.h"
#include "all_binary.h"
#include "check.h"

/*The function inserts a row into the data table. Returns -1 if there was an error in memory allocation and 0 otherwise.*/
int insert_data(int *data_count, data ** data_ptr, char * line, int count );


/*The function inserts a row into the instruction table. Returns -1 if there was an error in memory allocation and 0 otherwise.*/
int insert_instruction(int *inst_count, instructions ** instructions_ptr, char * line, int count );

/*The function inserts a row into the symbol table. Returns -1 if there was an error in memory allocation and 0 otherwise.*/
int insert_symbol(int * count_symbol, symbol ** symbol_ptr,char * name, char * first_word, int adress, int befor,int where );


#endif
