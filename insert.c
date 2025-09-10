#include "insert.h"

int insert_data(int *data_count, data ** data_ptr, char * line, int count )
{
	/*enter for data table*/
	if(*data_count==0)
		*data_ptr = (data*)malloc(sizeof(data));
	else
		*data_ptr = (data*)realloc(*data_ptr,((*data_count)+1)*sizeof(data));

    	if (*data_ptr == NULL) 
	{
        	return -1;
    	}
	strcpy((*data_ptr)[*data_count].line, line);
	(*data_ptr)[*data_count].num_line=count;
	(*data_count)++;
	return 0;
}

int insert_instruction(int * inst_count, instructions ** instructions_ptr, char * line, int count )
{
	if(*inst_count==0)
		*instructions_ptr = (instructions*)malloc(sizeof(instructions));
	else
		*instructions_ptr = (instructions*)realloc(*instructions_ptr, ((*inst_count)+1)*sizeof(instructions));
    	if (*instructions_ptr == NULL) 
	{
       		return -1;
    	}
	strcpy((*instructions_ptr)[*inst_count].line, line);
	(*instructions_ptr)[*inst_count].num_line = count;

	(*inst_count)++;
	return 0;
}

int insert_symbol(int * count_symbol, symbol ** symbol_ptr,char * name, char * first_word, int adress, int befor,int where )
{
	if(*count_symbol==0)
		*symbol_ptr = (symbol*)malloc(sizeof(symbol));
	else
		*symbol_ptr = (symbol*)realloc(*symbol_ptr,((*count_symbol)+1)*sizeof(symbol));
	if(*symbol_ptr==NULL)
	{	
		return -1;
	}
	strcpy((*symbol_ptr)[*count_symbol].name,name);
	(*symbol_ptr)[*count_symbol].adress=adress;
	(*symbol_ptr)[*count_symbol].befor = befor;



	if(strcmp(first_word,".entry")==0)
		(*symbol_ptr)[*count_symbol].where = ENTRY;
	else if(strcmp(first_word,".extern")==0)
		(*symbol_ptr)[*count_symbol].where = EXTERN;
	else
		(*symbol_ptr)[*count_symbol].where = where;
	(*count_symbol)++;
	return 0;
}
