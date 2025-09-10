#include "pass1.h"



int pass_two(char * name , symbol * symbols, data * data_items, instructions * instrs,int ic, int ic_count,int dc_count ,int sy_count ,  function * func ,FILE * temp_ob, FILE * temp_ext)
{
	
	int i;
	int flag=NO;
	int check=0;
	unsigned char c_ic;/*=0|ic_count;*/
	unsigned char c_dc;/*=0|dc_count;*/
	unsigned char ic_copy=ic_count;
	unsigned char dc_copy=dc_count;
	char * file_name;
	FILE * f_ob;
	count_of_lines=100;


	file_name = (char * )malloc(strlen(name)+strlen(".ext")+1);
	if(file_name==NULL)
	{
		fprintf(stderr , "not egnouf placse \n");
		return -1;
	}
	strcpy(file_name,name);
	strcat(file_name,".ext");
	
	
	/*add 100*/
	for(i=0; i<sy_count;i++)
	{
		if(symbols[i].befor == INSTRUCTIONS)
		{
			symbols[i].adress= symbols[i].adress+100;
		}
		else if(symbols[i].befor == DATA)
		{
			symbols[i].adress= symbols[i].adress+100+ ic;
		}
	}

	/*check if all the entry label defined*/
	for(i=0; i<sy_count;i++)
	{
		if(symbols[i].where==ENTRY)
		{	
			if(symbols[i].adress==NO_VALUE)
			{
				fprintf(stderr, "ERORR. the label %s is not defined.\n",symbols[i].name);
				symbols[i].adress= 0;
				error=YES;	
			}
		}
		
	}
	i=0;




	/*Deletes the file if no EXTERNAL tags exist.*/
	i=0;
	while(i < sy_count)
	{
		if(symbols[i].where==EXTERN)
		{
			flag=YES;
			break;
		}
		i++;
	}

	
	


/************WRITE FOR TEMP.OB*/	

	for(i=0;i<ic_copy;i++)
	{
		char copy[82];
		strcpy(copy,instrs[i].line);
		check=first_line(instrs[i].line ,symbols ,temp_ob, temp_ext ,2 ,   func ,  data_items ,sy_count);
		if(check==-2)
		{
			ic_count--;
			break;
		}
		else if(check==-1)
		{
			ic_count--;
			fprintf(stderr,"ERORR. in line: %d. the llabel is not exsist. %s\n" ,instrs[i].num_line, copy);
			error=YES;
		}
	}
	if(check!=-2)
	{

		for(i=0;i<dc_copy;i++)
		{
			check=first_line_data(data_items[i].line, temp_ob, 2);
			if(check==-2)
			{
				dc_count--;
				break;
			}
		}
	}
	c_ic=0|ic_count;
	c_dc=0|dc_count;
	if(error==NO)
	{
		f_ob=open_file(name, ".ob", WRITE);
		CHECK_NULL(f_ob);
	
/*WRITE .ENT\ .EXT*/
		print_entry( name, symbols ,  sy_count );
	/*IC*/
		binary_ic_dc(c_ic, f_ob);
	
	/*DC*/	
		binary_ic_dc(c_dc, f_ob);
		fputc('\n',f_ob);

	
		binary(temp_ob, f_ob, name);
		if(flag==YES)
		{
			binary_ext_ent(temp_ext, name,".ext");
		}
	}
	fclose(temp_ext);


	/***DELETE TEMP***/
	if (remove("TEMP.ob") != 0)
	{
		fprintf(stderr ,"A machine error occurred while deleting the file TEMP.ob. The file has probably been moved or changed.\n");
		return ERROR;
	}



	if (remove("TEMP.ext") != 0)
	{
		fprintf(stderr ,"A machine error occurred while deleting the file TEMP.ext. The file has probably been moved or changed.\n");
		return ERROR;
	}
	return check;
	
}







/*check if there are ENTRY lable in the table*/
int print_entry(char * name , symbol * symbol , int sy_count)
{	
	int i=0;
	char  c=0;
	int flag=NO;
	FILE * temp_ent;
	while(i < sy_count)
	{
		if(symbol[i].where==ENTRY && symbol[i].adress!=0)
		{	
			flag=YES;
			break;
		}
		i++;
	}
	i=0;
	if(flag)/*there is an entry lable*/
	{
		/*open .ent file*/
		temp_ent=open_file("TEMP", ".ent", EDIT);
		CHECK_NULL(temp_ent);
		while(i < sy_count)
		{
			if(symbol[i].where==ENTRY && symbol[i].adress!=0)
			{
				c=0|symbol[i].adress;	
				fprintf(temp_ent,"%s", symbol[i].name);/*copy the lable*/
				fprintf(temp_ent,"\t");
				fprintf(temp_ent,"%c",c );/*copy where it was */
				fprintf(temp_ent,"\n");
			}
			i++;
		}

		binary_ext_ent(temp_ent, name,".ent");
/*****************REMOVE TEMP*****************/
		if (remove("TEMP.ent") != 0)
		{
			fprintf(stderr ,"A machine error occurred while deleting the file TEMP.ent. The file has probably been moved or changed.\n");
			return ERROR;
		}
		fclose(temp_ent);
	}
	
	return 0;


}



FILE* open_file(char * name , char * end , int type)
{
	char * file_name;
	FILE * f;
	file_name = (char * )malloc(strlen(name)+strlen(end)+1);
	if(file_name==NULL)
	{
		fprintf(stderr , "not egnouf placse \n");
		return NULL;
	}
	strcpy(file_name,name);
	strcat(file_name,end);
	*(file_name+strlen(name)+strlen(end)) = '\0';
	if(type==READ)
		f = fopen(file_name,"r+");
	if(type==WRITE)
		f = fopen(file_name,"w");
	if(type==EDIT)
		f = fopen(file_name,"w+");
	if(f==NULL)
	{
		fprintf(stderr, "no file named:%s\n",file_name);
		free(file_name);
		return NULL;
		
	}
	
	return f;
}




