#ifndef MACRO_H
#define MACRO_H



#include "pass1.h"

/*The function receives the original file and the file in which the macro content is written. And inserts the macro content during the code.*/
int second( char * name , FILE* original, FILE* macro ,function *    func);

/*The function receives the name of the original file. And copies the contents of the macros to a new file. And sends it to the function that embeds the macros in the code.*/
int read_macro(char * name , function * func  );


#endif
