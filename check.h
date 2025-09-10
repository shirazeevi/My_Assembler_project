#ifndef check_H
#define check_H



/*The function removes spaces from the end of the string.*/
void remove_trailing_spaces(char *str);

/*The function removes spaces from the beginning of the string.*/
char * skip_leading_spaces(char *str);

/*The function checks whether the string is a number/register/matrix or a label and returns the addressing method.*/
int check_0_1_2_3(char* word , unsigned char  * line ,unsigned char * reg, symbol * symbol_ptr , FILE* f_binary, FILE * f_ext ,int pass ,  function * func , data * data_items ,int sy_count);

/*The function checks whether the string is a register/matrix or a label and returns the addressing method.*/
int check_1_2_3(char* word , unsigned char  * line ,unsigned char * reg, symbol * symbol_ptr , FILE* f_binary, FILE * f_ext ,int pass ,  function * func , data * data_items ,int sy_count);

/*The function checks whether the string is empty.*/
int is_empty( char* line);

/*The function checks whether the string is a number and encodes the line in characters.*/
int is_num(char * num, FILE * f_binary, int pass,int size,int  is_mat,int  is_data);

/*The function checks whether the string is a number.*/
int check_numbers(char * num ,unsigned char  * line , FILE* f_binary ,int pass);

/*The function checks whether the string is a label or a matrix and on the second pass encodes the registers.*/
int check_lable(char* word , unsigned char  * line ,unsigned char * reg, symbol * symbol_ptr , FILE* f_binary, FILE * f_ext ,int pass ,  function * func , data * data_items ,int sy_count);

/*The function skips spaces. Returns the index after skipping.*/
int remove_spacese(char * str , int i);


/*The function checks whether the string is a valid register.*/
int check_reg(char* word , unsigned char  * line , FILE* f_binary ,int pass);


/*The function receives the name of the file to open, the extension, and how to open it. And opens such a file.*/
FILE* open_file(char * name , char * end , int type);

/*The function checks if there are entry labels. If there are any, it writes to the file with the ".ent" extension where they were defined.*/
int print_entry(char * name , symbol * symbol , int sy_count );






#endif





