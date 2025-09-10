/*Esti Stainhous
 id 328155429
Shira Zeevi
 id 215322462
date:06/08/2025
*/




#include "pass1.h"
int main(int argc, char *argv[])
{
	int i=1;
	
	function func[16] = {
	{ {"mov"}, 0 },
	{ {"cmp"}, 16 },
	{ {"add"}, 32 },
	{ {"sub"}, 48 },
	{ {"lea"}, 64 },
	{ {"clr"}, 80 },
	{ {"not"}, 96 },
	{ {"inc"}, 112 },
	{ {"dec"}, 128 },
	{ {"jmp"}, 144 },
	{ {"bne"}, 160 },
	{ {"jsr"}, 176 },
	{ {"red"}, 192},
	{ {"prn"}, 208 },
	{ {"rts"}, 224 },
	{ {"stop"}, 240 }
	};
	error=NO;
	if(argc==1)
	{
		fprintf(stderr ,"no args\n");
		return 1;
	}
	for(;i<argc;i++)
	{
		error=NO; 
		count_of_lines=0;
		fprintf(stderr , "ERRORS IN FILE %s.as :\n\n",argv[i]); 
		read_macro(argv[i] , func  );
		fprintf(stderr , "*******************************************************************************");
		fprintf(stderr , "\n\n");
	}
		
return 0;

}
