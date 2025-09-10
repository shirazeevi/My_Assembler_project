#include "pass1.h"
#include <stdio.h>
#include <stdlib.h>


/*return 1 if the lune is empty*/
int is_empty( char* line)
{
	int empty=0;
	if(line==NULL)
		return 1;
	while(line[empty]!='\n' && line[empty]!= '\0')/*skip on empty lines*/
	{
		if (!isspace(line[empty]))
		{
			return 0;
		}
		empty++;
	}
	return 1;
}


int is_num(char * num, FILE * f_binary, int pass,int size,int  is_mat,int  is_data)
{
	int flag=0;
	int count=0;
	int val;
	int is_neg=0;
	unsigned char  line[3];

	while(num!=NULL)
	{
		line[0]=0;
		line[1]=0;
		line[2]='\0';

		count++;
		SEGMENTATION_FAULT(count_of_lines);
		if(is_mat && count> size)
			return -1;
		is_neg=0;
		if(*num == '+' || *num == '-')
		{		
			if(*num == '-')
				is_neg=1;	
			num=num+1;
		}	
		if(pass==2)/*the num is valid*/
		{
			val= atoi(num);
			if(is_neg==1)
				val=val*(-1);
			line[1] = (val << 6) | 0;
			line[0] = (val >>2) | 0;

			fprintf(f_binary,"%c",count_of_lines);
			count_of_lines++;	
			fwrite(line, 1, 2, f_binary);
			fputc('\n', f_binary);

			num=strtok(NULL ,",");
			flag=0;
			continue;
		}
		while(num  && (*num) !='\0')
		{
			if(isdigit(*num))
			{
				flag=1;
			}
 			if(isspace(*num) && flag==1)
			{
				num=num+1;
				if(isdigit(*num))
					return -1;
			}
			if(  (*num) !='\0' && !isdigit(*num) && !isspace(*num))
			{
				return -1;
			}
			num=num+1;
		}
		if(flag==0)
			return -1;/*tow ,,*/
		
	num=strtok(NULL ,",");
	flag=0;
	}
	if(is_mat && count<size)
	{
		for(;count<size;count++)
		{
			line[0]=0;
			line[1]=0;
			fwrite(line, 1, 2, f_binary);
			fputc('\n', f_binary);			
		}
		
	}
	if(is_mat)
		return size;
	return count;
}


int first_line_data( char* str , FILE * f_binary, int pass)
{
	int i=0;
	char  first_word[81];
	char * word1;
	char * num;
	int num1;
	int num2;
	int count=0;
	unsigned char  line[3];


	sscanf(str , "%s ", first_word );/*take the first word*/
	word1=strtok(str,  " "); /*skip the data name*/
/***********************DATA****************************************/
	if(strcmp(first_word,".data")==0)
	{
		word1=strtok(NULL,  "\0 ");

		if(is_empty(word1))/*if there is no string */
		{
			return -1;
		}

		num=strtok(word1 ,",");
		return is_num(num, f_binary, pass,0,0,1 );
		 
	}
/*************************STRING*****************************/	
	if(strcmp(first_word ,".string")==0)
	{
		i=0;
		count =1;/*'\0'*/
		word1=strtok(NULL,  "\0"); /*skip the data name*/

		if(is_empty(word1))/*if there is no string */
		{
			return -1;
		}
		i=0;
		while(isspace(word1[i]))
		{
			i++;
		}
		if(word1[i]=='"')
			word1=word1+i+1;
		else
			return -1;/*the string doesnot begin "*/
		i=strlen(word1);
		while(word1[i]!='\"')
		{
			i--;
			if(i<=0)
				return -1;/*no closing "*/
		}
		if(pass==2 && word1[i]=='\"')
			word1[i]='\0';

		count =count +i;/*i is the rest of the str after taking off the spaces after"*/

		if(pass==2)
		{
			
			for(i=0;i<strlen(word1);i++)
			{
				line[0]=0;
				line[1]=0;
				line[2]='\0';

				line[1] = line[1] | (word1[i]<<6);
				line[0] = line[0] | (word1[i]>> 2);

				SEGMENTATION_FAULT(count_of_lines)

				fprintf(f_binary,"%c",count_of_lines);
				count_of_lines++;

				fwrite(line, 1, 2, f_binary);	
				fputc('\n', f_binary);

				if(i==strlen(word1)-1)/*the end of word*/
				{
					line[0]=0;
					line[1]=0;
					line[2]='\0';

					fprintf(f_binary,"%c",count_of_lines);
					count_of_lines++;
					SEGMENTATION_FAULT(count_of_lines)

					fwrite(line, 1, 2, f_binary);	
					fputc('\n', f_binary);

					}	
			}
		}
		return count;
	}
/*******************************MAT*************************/
	if(strcmp(first_word,".mat")==0)
	{
		int size=0;
		num1=0;
		num2=0;

		word1=strtok(NULL,  " ");
		if(is_empty(word1))/*if there is no mat */
		{
			return -1;
		}

		if(word1[0]!='['){

			return -1;
		}
		i=1;
		while (isdigit(word1[i])	)
		{
			num1=num1*10+(word1[i]-'0');
			i++;
		}

		if(word1[i]!=']')
		{

			return -1;}
		i++;

		if(word1[i]!='['){

			return -1;}
		i++;
		while (isdigit(word1[i]))
		{
			num2=num2*10+(word1[i]-'0');
			i++;
		}

		if(word1[i]!=']')
		{

			return -1;
		}
		size= num1*num2;

		word1= strtok(NULL, "]");

		num=strtok(word1 ,",");
		return is_num(num, f_binary, pass, size, 1, 0);	
	}
	return -1;
	
}


