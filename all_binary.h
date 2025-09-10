#ifndef ALL_BINARY_H
#define ALL_BINARY_H
#include "pass1.h"
#include "insert.h"



#define SIZE_OF_MASK (sizeof(char)*8-1)




/*The function writes the label name and the base 4 address to a file with the appropriate extension (entry or exteren label).*/
int binary_ext_ent(FILE * binari_file, char * name , char * end);

/*The function writes the character it received (ic / dc) in base 4 to the top of the file with the extension ob.*/
int binary_ic_dc(char c, FILE * f);

/*The function writes the final binary encoding of the file, it receives a file full of characters (binary encoding according to the ASCII value of special characters) and writes the base 4 encoding to a file with the ob extension.*/
int binary(FILE * binari_file, FILE * base_4_file,  char * name);

#endif
