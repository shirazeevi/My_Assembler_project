#include "all_binary.h"

int binary_ic_dc(char c, FILE * f)
{
		int count_char=0;
		unsigned char mask;
		char final;
		int temp1=0;
		int temp2=0;
		int sum=0;
		int start_of_num=0;
		mask = 1 << SIZE_OF_MASK;

		while(mask )
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
			if(sum==0 && start_of_num==0)
			{
				if(count_char==3)
				{
					final='a';
					fprintf(f, "%c", final);
				}
				count_char++;
				mask=mask>>1;
				continue;
			}
			else
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
			start_of_num=1;
			fprintf(f, "%c", final);
			count_char++;
				
		}
		fputc('\t',f);

	return 0;
	
}
