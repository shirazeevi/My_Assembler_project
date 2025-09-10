#include "macro.h"

int second( char * name , FILE* original, FILE* macro ,function *    func)
{
	
	char line[256]={'\0'};
	char line_mac[82]={'\0'};
	int i=0;
	int flag=0;
	int empty=0;
	FILE * final;
	int isnotempty=0;
	char first_word[82]={'\0'};
	char macro_name[82]={'\0'};
	fflush(macro);
	rewind(macro);
	rewind(original);
	final=open_file(name , ".am",EDIT);/*open the original file .am*/
	CHECK_NULL(final);
	if(final==NULL)
	{
		return 1;
	}
	while (fgets(line, sizeof(line), original) != NULL)
	{

		if(strlen(line)>81)/*check if the line to long*/
		{
			fprintf(stderr,"there is too long line: \n %s", line);
			return 1;
		}
		if(line[0]==';')/* is a Comment line skip*/
		{
			continue;
		}
		empty=0;
		isnotempty=0;
		while(line[empty]!='\n' && line[empty]!= EOF)/*skip on empty lines*/
		{
			if (!isspace(line[empty]))
			{
				isnotempty=1;
			}
			empty++;
		}
		if(isnotempty==0)
			continue;
	
		rewind(macro);
		flag=0;
		sscanf(line , "%s ", first_word );/*take the first word*/
		i=0;
		for(; i<16; i++)/*the macro is not a function*/
		{
			if(strcmp(first_word,func[i].name)==0)
			{
				fprintf(final,"%s", line);/*copy the func*/
				flag =1;/* we copyd this line*/
				break;
			}	
	
		}

		if(strcmp(first_word,"mcro")==0)/*skip macro*/
		{
			while(fgets(line, sizeof(line), original) != NULL)
			{
				sscanf(line , "%s", first_word);
				if((strcmp(first_word,"mcroend")==0))/**/
					break;
			}
			continue;
		}
		rewind(macro);
		if(flag==0)
		{
			while (fgets(line_mac, sizeof(line), macro) != NULL)
			{
				sscanf(line_mac , "%s ", macro_name);/*take the first word*/
				if(strcmp(first_word,macro_name)==0)/*this is a macro*/
				{
					flag=1;
					while(fgets(line_mac, sizeof(line_mac), macro) != NULL)/*isnot mcroend*/
					{
						sscanf(line_mac , "%s", first_word);
						if((strcmp(first_word,"mcroend")!=0))/**/
						{
							fprintf(final, "%s", line_mac);/*copy the data of the macro*/
						}
						else
						{
							break;
						}
				
					}
				}
				if (flag)
					break;
			}
			if(!flag)/*lable*/
				fprintf(final,"%s", line);

		}
	
	}
	fclose(original);
	return pass_one(name , macro ,final, func);

}




