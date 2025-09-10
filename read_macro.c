#include "macro.h"



int read_macro(char * name , function * func   )
{
	
	

	int empty=0;
	int isnotempty=0;

	char line[82]={'\0'};
	int i=0;
	char first_word[82]={'\0'};
	char second_word[82]={'\0'};
	int num_of_line=0;
	FILE * macro;
	FILE * original=open_file(name , ".as" , READ);/*open the original file .as*/
	CHECK_NULL(original);
	macro=open_file("TEMP" , ".txt" , EDIT);/*open the macro file .txt*/
	CHECK_NULL(macro);
	while (fgets(line, sizeof(line), original) != NULL)
	{
		num_of_line++;
		if(strlen(line)>81)/*check if the line to long*/
		{
			fprintf(stderr,"the line %d:  %s is too long",num_of_line, line);
			/*****************REMOVE TEMP*****************/
			fclose(macro);
			if (remove("TEMP.txt") != 0)
			{
				fprintf(stderr ,"A machine error occurred while deleting the file TEMP.ent. The file has probably been moved or changed.\n");
				return ERROR;
			}
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
		sscanf(line , "%s %s", first_word, second_word);/*take the first word*/
		if(strcmp(first_word,"mcro")==0)/*this is a macro*/
		{
			for(; i<16; i++)/*the macro is not a function*/
			{
				if(strcmp(second_word,func[i].name)==0)
				{
					fprintf(stderr ,"in line %d the name of the macro is a function:%s \n",num_of_line, func[i].name);
					/*****************REMOVE TEMP*****************/
					fclose(macro);
					if (remove("TEMP.txt") != 0)
					{
						fprintf(stderr ,"A machine error occurred while deleting the file TEMP.ent. The file has probably been moved or changed.\n");
						return ERROR;
					}
					return 1;
				}	
			}
			if(strcmp(second_word,"data")==0 || strcmp(second_word,"mat")==0 || strcmp(second_word,"string")==0 || strcmp(second_word,"extern")==0 || strcmp(second_word,"entry")==0 || strcmp(second_word,".data")==0 || strcmp(second_word,".mat")==0 || strcmp(second_word,".string")==0 || strcmp(second_word,".extern")==0 || strcmp(second_word,".entry")==0 )
			{
				fprintf(stderr,"Error in the line: %d. The macro is save word name: %s \n",num_of_line, second_word);
				/*****************REMOVE TEMP*****************/
				fclose(macro);
				if (remove("TEMP.txt") != 0)
				{
					fprintf(stderr ,"A machine error occurred while deleting the file TEMP.ent. The file has probably been moved or changed.\n");
					return ERROR;
				}
				return 1;
			}
			fprintf(macro ,"%s \n", second_word);/*copy the macro name*/
			while(fgets(line, sizeof(line), original) != NULL)/*isnot mcroend*/
			{
				num_of_line++;
				if(strlen(line)>81)/*check if the line to long*/
				{
					fprintf(stderr,"there is too long line: \n %s", line);
					/*****************REMOVE TEMP*****************/
					fclose(macro);
					if (remove("TEMP.txt") != 0)
					{
						fprintf(stderr ,"A machine error occurred while deleting the file TEMP.ent. The file has probably been moved or changed.\n");
						return ERROR;
					}
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
				sscanf(line , "%s", first_word);
				if((strcmp(first_word,"mcroend")!=0))/**/
				{
					fprintf(macro,"%s", line);/*copy the data of the macro*/
				}
				else
				{
					break;
				}
				
			}
			if((strcmp(first_word,"mcroend")==0))/**/
			{
				fprintf(macro,"%s \n", first_word);
			}
			
		}
	}
	  
	
	return second(name, original, macro, func);

}

