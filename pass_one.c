#include "pass1.h"
#include "insert.h"

unsigned char count_of_lines= 0;
int error=NO;


int pass_one(char * name , FILE * macro , FILE * f ,  function * func)
{
	FILE * f_ob;
	FILE * f_ext;
	char line[82];
	char line_for_err[82];
	char line_mac[82]={'\0'};
	char macro_name[82]={'\0'};
	char copy_line[82];
	char * line_to_send;
	char first_word[82], second_word[82], third_word[82];
	int i,j;
	int ic=0,dc=0;
	int count_symbol=0, data_count = 0, inst_count = 0;
	int num_of_line;
	int is_label=0;
	int pass=1;
	int returne=0;
	int count_line_err=0;
	symbol * symbol_ptr=NULL;
	instructions * instructions_ptr=NULL;
	data * data_ptr=NULL;

	rewind(f);
/*open .ob file*/
	f_ob=open_file("TEMP", ".ob",  EDIT);

	CHECK_NULL(f_ob);
/*open .ext file*/
	f_ext=open_file("TEMP", ".ext",  EDIT);
	CHECK_NULL(f_ext);
	while(fgets(line, sizeof(line), f)!=NULL)
	{
count_of_lines++;
		count_line_err++;
		strcpy(copy_line, line);
		strcpy(line_for_err,line);
		is_label=0;
		sscanf(line, "%s %s %s", first_word,second_word, third_word);
		i=0;
		if(strcmp(second_word,".entry")==0 || strcmp(second_word,".extern")==0)/*the first word is lale, the second word is HANCHAYA- is not corect*/
		{
			fprintf(stderr, "Error in the line: %d. The second word is save word: %s \n",count_line_err,line_for_err);
			error=YES;
			continue;		
		}
		while(first_word[i]!='\0' )
		{
			j=i;
			i++;
		}
		if(first_word[j]==':')/*the first_word is lable*/
		{
			first_word[j]='\0';
			if(strcmp(first_word,"data")==0 || strcmp(first_word,"mat")==0 || strcmp(first_word,"string")==0 || strcmp(first_word,"extern")==0 || strcmp(first_word,"entry")==0 || strcmp(first_word,".data")==0 || strcmp(first_word,".mat")==0 || strcmp(first_word,".string")==0 || strcmp(first_word,".extern")==0 || strcmp(first_word,".entry")==0 )
			{
				fprintf(stderr,"Error in the line: %d. The lable is save word name: %s \n",count_line_err, line_for_err);
				error=YES;
				continue;
			}
			if(is_command(first_word, func))/* check if the first word is command*/
			{
				fprintf(stderr,"Error in the line: %d .The lable is function name: %s \n",count_line_err, line_for_err);
				error=YES;
				continue;
			}
			else if ((second_word) == NULL)
			{	
				fprintf(stderr,"Error in the line: %d .The lable is empty: %s \n",count_line_err, line_for_err);
				error=YES;
				continue;
			} 
			else if(second_word[0]=='.')/*the first word is lable, the second word is HANCHAYA*/
			{
				/*chek the lable is not in the table*/
				i=0;
				while(i < count_symbol)
				{
					if(strcmp(first_word,symbol_ptr[i].name)==0)
					{
						if(symbol_ptr[i].where==EXTERN)
						{
							fprintf(stderr , "Error in the line: %d . The label is already defined as extern. %s \n",count_line_err, line_for_err);
							error=YES;
							is_label=1;
						}
						if(symbol_ptr[i].where==ENTRY)
						{
							is_label=2;
							break;
						}
						else
						{
							fprintf(stderr , "Error in the line: %d . The label has already been defined. %s \n",count_line_err, line_for_err);
							error=YES;
							is_label=1;
						}
					}

					i++;
				}
				if(is_label==1)/*the label exsist in tabel*/
					continue;
	/****CHECK IF THE LABLE IS A MACRO*/
				rewind(macro);
				while (fgets(line_mac, sizeof(line), macro) != NULL)/*take line from the macro file .txt*/
				{
					sscanf(line_mac , "%s ", macro_name);/*take the first word*/
					if(strcmp(first_word,macro_name)==0)/*this is a macro*/
					{
						fprintf(stderr , "Error in the line: %d . The name of the label is macro. %s \n",count_line_err , line_for_err);
						error=YES;
						is_label=1;
					}
				}
				if(is_label==1)/*the label exsist in tabel*/
					continue;
				
				strtok(line," ");
				line_to_send=strtok(NULL,"\n");
				if ((line_to_send) == NULL)
				{	
					fprintf(stderr,"Error in the line: %d .The lable is empty: %s \n",count_line_err, line_for_err);
					error=YES;
					continue;
				} 
				strcpy(copy_line , line_to_send);
				num_of_line = first_line_data(line_to_send ,f_ob , pass);
				if(num_of_line==-2)
				{
					return -2;
				}
				if(num_of_line != -1)
				{
					/*enter for data table*/
					returne=insert_data(&data_count,&data_ptr,  copy_line, count_line_err );
					if(returne==-1)
					{
						fprintf(stderr, "Error in the line: %d . Memory allocation failed. %s \n",count_line_err ,line_for_err);
						error=YES;
        					return 1;
					}
					
					/*enter for symbol table*/
					if(is_label==2)/*the label in the tabel ENTRY*/
					{
						symbol_ptr[i].adress=dc;
						symbol_ptr[i].befor = DATA;
					}
					else if(insert_symbol(&count_symbol,&symbol_ptr,first_word,first_word, dc, DATA,NO_VALUE)==-1)
					{
						fprintf(stderr, "Error in the line: %d . Memory allocation failed. %s \n",count_line_err ,line_for_err);
						error=YES;
        					return 1;
					
					}
					
					dc = dc+num_of_line;

				}
				else
				{
					fprintf(stderr,"Error in the line: %d . The arguments are invalid. %s \n" , count_line_err , line_for_err);
					error=YES;
				}
				
			}
			else /*the first word is lable, the second word is PKUDA*/
			{
				/*chek the lable is not in the table*/
				i=0;
				while(i < count_symbol)
				{
					if(strcmp(first_word,symbol_ptr[i].name)==0)
					{
						if(symbol_ptr[i].where==EXTERN)
						{
							fprintf(stderr , "error the %d is an extern lable. %s \n", count_line_err , line_for_err);
							error=YES;
							is_label=1;
						}
						if(symbol_ptr[i].where==ENTRY)/*******/
						{
							is_label=2;
							break;
						}
						else
						{
							fprintf(stderr , "Error in the line: %d . The label has already been defined. %s \n", count_line_err , line_for_err);
							error=YES;
							is_label=1;
						}
					}

					i++;
				}
				if(is_label==1)/*the label exsist in tabel*/
					continue;
	/****CHECK IF THE LABLE IS A MACRO*/
				rewind(macro);
				while (fgets(line_mac, sizeof(line), macro) != NULL)/*take line from the macro file .txt*/
				{
					sscanf(line_mac , "%s ", macro_name);/*take the first word*/
					if(strcmp(first_word,macro_name)==0)/*this is a macro*/
					{
						fprintf(stderr , "error the %s is a name of a macro. \n", first_word);
						is_label=1;
						error=YES;
					}
				}
				if(is_label==1)/*the label exsist in tabel*/
					continue;

				strtok(line," ");
				line_to_send=strtok(NULL,"\n");
				if ((line_to_send) == NULL)
				{	
					fprintf(stderr,"Error in the line: %d .The lable is empty: %s \n",count_line_err, line_for_err);
					error=YES;
					continue;
				} 

				strcpy(copy_line , line_to_send);
				num_of_line = first_line(line_to_send ,  symbol_ptr ,  f_ob , f_ext, pass , func, data_ptr, count_symbol);

				/*enter for instructions table*/
				if(num_of_line==-2)
				{
					return -2;
				}
				if(num_of_line != -1)
				{
					if(insert_instruction(&inst_count, &instructions_ptr, copy_line, count_line_err )==-1)
					{
						fprintf(stderr, "Error in the line: %d . Memory allocation failed. %s\n",count_line_err , line_for_err);
						error=YES;
        					return 1;
					}
					/*enter for symbol table*/

					if(is_label==2)/*the label in the tabel ENTRY*/
					{

						symbol_ptr[i].adress=ic;
						symbol_ptr[i].befor = INSTRUCTIONS;
					}
					else if(insert_symbol ( &count_symbol ,&symbol_ptr ,first_word,first_word,ic , INSTRUCTIONS ,NO_VALUE)==-1)
					{
						fprintf(stderr, "Error in the line: %d . Memory allocation failed. %s \n",count_line_err ,line_for_err);
						error=YES;
        					return 1;
					}
					ic = ic+num_of_line;

				}
				else
				{
					fprintf(stderr,"Error in the line: %d . The arguments are invalid. %s \n" , count_line_err , line_for_err);
					error=YES;
				}
			}
		}
		
		else if(strcmp(first_word,".entry")==0 || strcmp(first_word,".extern")==0)/*the first word is entry/extern, the second word is lable*/
		{
			strtok(line," ");
			line_to_send=strtok(NULL,"\n");
			
		
			if(strcmp(line_to_send,"data")==0 || strcmp(line_to_send,"mat")==0 || strcmp(line_to_send,"string")==0 || strcmp(line_to_send,"extern")==0 || strcmp(line_to_send,"entry")==0 || strcmp(line_to_send,".data")==0 || strcmp(line_to_send,".mat")==0 || strcmp(line_to_send,".string")==0 || strcmp(line_to_send,".extern")==0 || strcmp(line_to_send,".entry")==0 )
			{
				fprintf(stderr,"Erorr: the lable is HANCHAYA name: %s \n", first_word);
				error=YES;
				continue;
			}

			/*chek the lable is not in the table*/
			i=0;
			while(i < count_symbol)
			{
				if(strcmp(line_to_send,symbol_ptr[i].name)==0)
				{
					if(symbol_ptr[i].where==EXTERN)
					{
						fprintf(stderr , "error the %s is an extern lable \n", line_to_send);
						is_label=1;
						error=YES;
					}
					if(symbol_ptr[i].where==ENTRY)/*******/
					{
						fprintf(stderr , "error the %s is an entry lable \n", line_to_send);
						is_label=1;
						error=YES;
					}
					else
					{
						is_label=2;
						break;
					}
				}
				i++;
			}
			if(is_label==1)/*the label exsist in tabel*/
				continue;

			/*enter for symbol table*/

			if(is_label==2)
			{
				symbol_ptr[count_symbol].where = ENTRY;
			}

			else if(insert_symbol ( &count_symbol ,&symbol_ptr ,second_word,first_word,NO_VALUE , NO_VALUE ,NO_VALUE)==-1)
			{
				fprintf(stderr, "Error in the line: %d . Memory allocation failed. %s\n",count_line_err ,line_for_err);
				error=YES;
        			return 1;
			}
		}		
		
		else if(strcmp(first_word,".data")==0 || strcmp(first_word,".string")==0 || strcmp(first_word,".mat")==0)/*the first word is .data/.strind/.mat*/
		{
				
			fprintf(stderr , "in line %d the HNCHAYA without lable is %s ",count_of_lines,line);
			strcpy(copy_line , line);
			num_of_line = first_line_data(line ,f_ob , pass);
			if(num_of_line==-2)
			{
				return -2;
			}
			/*enter for data table*/
			if(num_of_line != -1)
			{
				returne=insert_data(&data_count,&data_ptr,  copy_line, count_line_err );
				if(returne==-1)
				{
					fprintf(stderr, "Error in the line: %d . Memory allocation failed. %s \n",count_line_err ,line_for_err);
					error=YES;
        				return 1;
				}
				dc = dc+num_of_line;
			}
			else
			{
				fprintf(stderr,"Error in the line: %d . The arguments are invalid. %s \n" , count_line_err , line_for_err);
				error=YES;
			}
		}
		else/*the line is PKUDA*/
		{
			

			strcpy(copy_line, line);
			num_of_line = first_line(line ,  symbol_ptr ,  f_ob, f_ext , pass , func, data_ptr, count_symbol);

			/*enter for instructions table*/
			if(num_of_line==-2)
			{
				return -2;
			}
			if(num_of_line != -1)
			{
				if(insert_instruction(&inst_count, &instructions_ptr, copy_line, count_line_err )==-1)
				{
					fprintf(stderr, "Error in the line: %d . Memory allocation failed. %s\n",count_line_err , line_for_err);
					error=YES;
        				return 1;
				}
				ic = ic+num_of_line;
			}
			else
			{
				fprintf(stderr,"Error in the line: %d . The arguments are invalid. %s \n" , count_line_err , line_for_err);
				error=YES;
			}
			
		}
	}

	fclose(f);
	fclose(macro);
	if (remove("TEMP.txt") != 0)
	{
		fprintf(stderr ,"A machine error occurred while deleting the file %s.txt. The file has probably been moved or changed.\n",name);
		return ERROR;
	}
/*****************************************************second time*/

	pass_two(name , symbol_ptr, data_ptr, instructions_ptr, ic,inst_count,data_count, count_symbol, func ,f_ob,f_ext);
	
	free(symbol_ptr);
	symbol_ptr = NULL;
	free(data_ptr);
	free(instructions_ptr);
return 0;
	
}




int is_command(char * str , function * func )
{
	int i;
	int is_func_name=0;
	for(i=0; i<16; i++)	/*the lable is not a function*/
	{
		if(strcmp(str,func[i].name)==0)
		{
			is_func_name=1;
			break;
		}    
	}
	if(is_func_name)
		return 1;
	return 0;
}






