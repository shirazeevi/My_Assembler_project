#include "all_binary.h"
int binary(FILE * binari_file, FILE * base_4_file,  char * name)
{
	unsigned char mask = 1 << SIZE_OF_MASK;
	char final;
	int temp1=0;
	int temp2=0;
	int sum=0;
	char c;
	int count_in_line=0;
	int count_char=0;
	int flag_end=1;
	
	rewind(	binari_file);

	while(!feof(binari_file) && flag_end)
	{

		count_in_line=0;
		count_char=0;
		while(count_in_line<3)
		{
			c = fgetc(binari_file);
			if(c==EOF)
			{
				flag_end=0;
				break;
			}
			if(c=='\n')
			{	
				break;
			}
			mask = 1 << (sizeof(char)*8-1);
			while(mask && count_char<9)
			{
				if(c&mask)
				{
					temp1=2;
				}
				mask=mask>>1;
				if(c&mask)
				{
					temp2=1;
				}
	
				sum=temp1+temp2;
				if(sum==0)
					final='a';
				if(sum==1)
					final='b';
				if(sum==2)
					final='c';
				if(sum==3)
					final='d';
				mask=mask>>1;
				temp1=0;
				temp2=0;
				if(count_char == 4)
					fprintf(base_4_file, "\t");
				fprintf(base_4_file, "%c", final);
				count_char++;
				
			}
			count_in_line++;
		}
		if(count_in_line==3)
			fprintf(base_4_file,"\n");
	
	}
	fclose(binari_file);
	fclose(base_4_file);

	return 0;
	
}
