#ifndef PASS1_H
#define PASS1_H

/************OPEN FILE****************/
#define READ 1
#define WRITE 2
#define EDIT 3
/*************OPEN FILE**********************/

#define YES 1
#define NO 0
#define ERROR -1
#define ENTRY 1
#define EXTERN 0
#define DATA 1
#define INSTRUCTIONS 0
#define NO_VALUE -1
#define CHECK_NULL(word)  \
	if ((word) == NULL)       \
		return -1      

#define SEGMENTATION_FAULT(count_of_lines)	\
		if(count_of_lines>254)	\
		{	\
			fprintf(stderr, "Segmentation Fault\n");	\
			return -2;	\
		}    


#define IS_LABLE(word) \
    if(i>= strlen(word)) \
    is_lable= 1

/*symbol tabel*/
typedef struct{
	char name[82];
	int adress;
	int befor;
	int where;
	int num_line;
	}symbol;
/*instructions tabel*/
typedef struct{
	char line[82];
	int num_line;
	}instructions;
/*data tabel*/
typedef struct{
	char line[82];
	int num_line;
	}data;
/*function and binary code tabel*/
typedef struct{
	char name[6];
	unsigned char binary_name;
	} function;


extern unsigned char count_of_lines;

extern int error;

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include "all_binary.h"
#include "insert.h"
#include "check.h"
#include "macro.h"




/*The function receives the temporary file OB. In the first pass, it checks whether the DATA lines are valid, and in the second pass, it encodes them.*/
int first_line_data( char* str , FILE * f_binary , int pass);

/*The function receives the temporary file OB. In the first pass, it checks whether the lines of the instruction are valid, and in the second pass, it encodes them.*/
int first_line(char *line, symbol *symbols, FILE *f_ob, FILE * f_ext, int pass, function *func, data * data_items, int symbol_count);

/*The function checks whether the string is the name of a reserved function.*/
int is_command(char * str , function * func );


/*The function makes the first pass - fills in the symbol tables, data, and instructions. And sends for encoding in a second pass.*/
int pass_one(char * name , FILE * macro , FILE * f, function * func);


/*The function makes the second pass. Encodes the final file, and updates the symbol tables.*/
int pass_two(char * name , symbol * symbols, data * data_items, instructions * instrs, int ic , int ic_count,int dc_count ,int sy_count , function * func  ,FILE * temp_ob, FILE * temp_ext);




#endif
