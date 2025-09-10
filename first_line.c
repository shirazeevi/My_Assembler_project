#include "pass1.h"

void remove_trailing_spaces(char *str) 
{
	int len;
	if (str == NULL)
		return;
	len = strlen(str);
	if (len == 0)
		return;

	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t' || str[len - 1] == '\n')) 
	{
		len--;
	}

	str[len] = '\0'; 
}


char * skip_leading_spaces(char *str) 
{
	while (*str == ' ' || *str == '\t') 
	{
		str++;
	}
	return str;
}



int check_0_1_2_3(char* word , unsigned char * line ,unsigned char * reg, symbol * symbol_ptr , FILE* f_binary, FILE * f_ext ,int pass , function * func, data * data_items ,int sy_count)
{
	int num=0;
	CHECK_NULL(word );
	num=check_reg(word , line, f_binary , pass);
	if(num<0)
	{
		num=check_numbers(word , line, f_binary , pass);
		if(num<0)
		{

			num=check_lable(word , line , reg ,symbol_ptr, f_binary ,f_ext , pass ,func, data_items , sy_count);
		}	
	}
	return num;
}

int check_1_2_3(char* word , unsigned char * line ,unsigned char * reg, symbol * symbol_ptr , FILE* f_binary, FILE * f_ext ,int pass, function * func, data * data_items ,int sy_count)
{
	int num=0;
	CHECK_NULL(word );
	num=check_reg(word , line , f_binary , pass);

	if(num<0)
	{

		num=check_lable(word , line ,reg , symbol_ptr , f_binary , f_ext, pass,  func,  data_items , sy_count);	
	}
	return num;
}


int check_numbers(char * num, unsigned char * line , FILE* f_binary ,int pass)
{
	int value=0;
	int flag=NO;
	if(*num != '#')
		return -1;
	num=num+1;
	if(*num == '+' || *num == '-')
	{
		if(*num == '-')
		{
			flag=YES;
		}
		num=num+1;
		
	}

	while(num  && (*num) !='\0')
	{
		if(!isdigit(*num))
		{
			return -1;
		}
		value=value*10+(*num)-'0';/*the num value*/
	
		num=num+1;
	}
	if(flag)
	{
		value=value*-1;
	}
	line[1] = (value << 6) | 0;
	line[0] = (value >>2) | 0;

	return 0;
}


int remove_spacese(char * str , int i)
{

	while(i<strlen(str) && str[i] !='\0')
	{

		if(isspace(str[i]))
		{
			i++;
		}
		else
			break;
	}
	
	return i;
}

/* checks that the argument is not a name of a func*/
int check_lable(char* word , unsigned char * line,  unsigned char * reg , symbol * symbol_ptr , FILE* f_binary, FILE * f_ext ,int pass  , function * func, data * data_items ,int sy_count)
{	
	int i=0;
	int j=0;
	char c=0;
	int is_lable=0;
	char  name_label[82];
	int reg_val;
	reg[0]=0;
	reg[1]=0;


	while(i<strlen(word)&& (word[i]!='[' && !isspace(word[i])))
	{
		name_label[i]=word[i];
		i++;
	}
		name_label[i]='\0';
	

	for(; j<16; j++)/*the lable is not a function*/
	{
		if(strcmp(name_label,func[j].name)==0)
		{
			fprintf(stderr ,"ERROR IN LINE:%d, the name of the argument is a function:%s \n" ,count_of_lines,func[j].name);
			return -1;
		}	
	}
		


	if(i==strlen(word))/*the word end*/
	{
		is_lable= 1;
	}
/*check first register*/

	if(i<strlen(word) && word[i]!='[')
	{
		is_lable= 1;
	}
	i++;
	i=remove_spacese(word ,i);

	IS_LABLE(word);
	if(i<strlen(word) && word[i]!='r')
	{
		is_lable= 1;
	}
	IS_LABLE(word);
	i++;
	if(i<strlen(word) && ( word[i]<'1' || word[i]> '8' ) )
	{
		is_lable= 1;
	}
	IS_LABLE(word);
	reg_val=word[i]-'0';
	reg[0]=reg_val;
	reg[0]=reg[0]<<4;
	

	i++;

	i=remove_spacese(word ,i);

	if(i<strlen(word) && word[i]!=']')
	{
		is_lable= 1;
	}
	IS_LABLE(word);
	i++;
/*check second register*/

	i=remove_spacese(word ,i);

	if(i<strlen(word) && word[i]!='[')
	{
		is_lable= 1;
	}
	i++;

	i=remove_spacese(word ,i);

	if(i<strlen(word) && word[i]!='r')
	{
		is_lable= 1;
	}
	IS_LABLE(word);
	i++;

	if(i<strlen(word) && ( word[i]<'1' || word[i]> '8' ) )
	{
		is_lable= 1;
	}
	IS_LABLE(word);
	reg_val=word[i]-'0';
	reg[0]=reg[0]|reg_val;
	i++;

	i=remove_spacese(word ,i);

	if(i<strlen(word) && word[i]!=']')
	{
		is_lable= 1;
	}


	if(pass==2)/*this is the second pass*/
	{
		i=0;

	/*chek the lable is not in the table*/
		while(i < sy_count)
		{
			if(is_lable)
				strcpy(name_label, word);

			if(strcmp(name_label,symbol_ptr[i].name)==0)
			{
			/********CHECK ENTRY\EXTERN****/
				if(symbol_ptr[i].where==EXTERN)
				{
					line[1]=64;
			/****WRITE TO .EXT***/
					c=0|count_of_lines;	




					fprintf(f_ext,"%s", symbol_ptr[i].name);/*copy the lable*/

					fprintf(f_ext,"\t");
					fprintf(f_ext,"%c",c );/*copy where it was */
					fprintf(f_ext,"\n");

					
				}
				else if(symbol_ptr[i].where==ENTRY)/*************************************/
				{
					line[1]=128;
					line[0]=symbol_ptr[i].adress|0;
				}
				else
				{
					line[0]=symbol_ptr[i].adress|0;
					line[1]=128;

				}
				break;
			}
			i++;
		}
		if(i ==sy_count)
		{
			error=YES;
			return -1;
		}


		
	}
	if(is_lable)
		return 1;
	return 2;/*Label addressing method*/
}

/* checks that the argument is a register*/
int check_reg(char* word ,unsigned char * line , FILE* f_binary ,int pass)
{
	int num=0;
	line[0] = 0;
	if(*word=='r')
	{
		if(isdigit(word[1]))
		{
			num=(word[1]-'0');
			if(( num<9 && 0<num)&& ((word[2])=='\0'))
			{
				line[0]=line[0]|num;


				return 3;/*register addressing method*/
			}
		}
	}
	return -1;
}



int first_line( char* str  , symbol * symbol_ptr , FILE* f_binary, FILE * f_ext ,int pass,  function * func , data * data_items ,int sy_count)
{
	int i=0;
	unsigned char line[2] ;
	unsigned char line1[2] ;
	unsigned char line2[2] ;
	unsigned char reg1[2] ;
	unsigned char reg2[2] ;
	char  first_word[81];
	char * word1;
	char * word2;
	int num1=0;
	int num2=0;
	int count=1;
	int flag=1;
	int reg2flag=0;
	line[0]=0;
	line[1]=0;
	line1[0]=0;
	line1[1]=0;
	line2[0]=0;
	line2[1]=0;
	

	sscanf(str , "%s ", first_word );/*take the first word*/
	for(; i<16; i++)/*this is a legal func*/
	{
		if(strcmp(first_word,func[i].name)==0)
		{
			break;
		}	
	}
	if(i==16)/*this is not legal func*/
		return -1;
	count =1;
	line[0] =line[0] | (func[i].binary_name);/*put the address of the func*/


	word1=strtok(str,  " "); /*skip the func name*/
	if(i==0 || i==2|| i==3 )/*1-- lable |reg |num |mat 2--lable| reg|mat*/
	{
		word1 = strtok(NULL,  ",");
		CHECK_NULL(word1); 
		word1=skip_leading_spaces(word1);
		remove_trailing_spaces(word1);
		num1=check_0_1_2_3(word1, line1 ,reg1 ,  symbol_ptr, f_binary, f_ext , pass , func,  data_items , sy_count);
/**/		if(num1==-1 && pass==2)
			return -1;
		word2=strtok(NULL,  " ");
		CHECK_NULL(word2); 

		word2=skip_leading_spaces(word2);
		remove_trailing_spaces(word2);
		num2=check_1_2_3(word2 , line2 ,reg2 ,   symbol_ptr, f_binary , f_ext, pass , func,  data_items , sy_count);
/**/		if(num2==-1 && pass==2)
			return -1;
	
		if(num1 <0 || num2< 0)
		{
			return -1;
		}
		if(num1==3 && num2==3)/*tow reg to one line*/
		{
				line1[0]=((line1[0])<<4)|0;
				line2[0]=line2[0]|line1[0];
				reg2flag=1;
			count ++;
		}
		else
			count=count+2;/*another line for each one*/
		if(num1==2)
			count++;
		if(num2==2)
			count++;
		
	}
	if(i==1 )/*1-- num|lable 2--reg|lable*/
	{
		word1 = strtok(NULL,  ",");
		CHECK_NULL(word1);
		word1=skip_leading_spaces(word1);
		remove_trailing_spaces(word1);
		num1=check_0_1_2_3(word1, line1 ,reg1 ,   symbol_ptr, f_binary , f_ext, pass , func,  data_items , sy_count);
/**/		if(num1==-1 && pass==2)
			return -1;

		word2=strtok(NULL,  " ");
		CHECK_NULL(word2);
		word2=skip_leading_spaces(word2);
		remove_trailing_spaces(word2);
		num2=check_1_2_3(word2, line2 ,reg2 ,  symbol_ptr, f_binary , f_ext , pass , func,  data_items , sy_count);
/**/		if(num2==-1 && pass==2)
			return -1;

		if(num1 <0 || num2< 0)
		{
			fprintf(stderr,"not a legal line : %s\n" ,str );
			return -1;
		}
		if(num1==3 && num2==3)
		{
			if(flag)
			{
				*line1=(*line1)<<4;
				*line2=(*line2)|(*line1);
				line2[2]='\0';
				reg2flag=1;
			}
			count ++;
		}
		else
			count=count+2;
		if(num1==2)
			count++;
		if(num2==2)
			count++;
		
	}
	if(i==4)
	{
		word1 = strtok(NULL,  ",");
		CHECK_NULL(word1);
		word1=skip_leading_spaces(word1);
		remove_trailing_spaces(word1);
		num1=check_lable(word1, line1 ,reg1 , symbol_ptr, f_binary ,f_ext , pass , func,  data_items , sy_count);
		if(num1==-1 && pass==2)
			return -1;

		word2=strtok(NULL,  " ");
		CHECK_NULL(word2);
		word2=skip_leading_spaces(word2);
		remove_trailing_spaces(word2);
		num2=check_1_2_3(word2 , line2 ,reg2 ,  symbol_ptr, f_binary, f_ext , pass , func,  data_items , sy_count);
		if(num2==-1 && pass==2)
			return -1;

		if(num1==2)
			count=count+2;
		else if(num1>=0);
			count++;
		if(num2==2)
			count=count+2;
		else if(num2>=0)
			count++;

	}
	if(i==5 || i==6 ||i==7 ||i==8 ||i==9 ||i==10 ||i==11||i==12 )/*1--reg|lable*/
	{
		word2 = strtok(NULL,  " ");
		CHECK_NULL(word2);
		word2=skip_leading_spaces(word2);
		remove_trailing_spaces(word2);
		num2=check_1_2_3(word2, line2 ,reg2 ,  symbol_ptr, f_binary , f_ext , pass , func,  data_items , sy_count);
		if(num2==-1 && pass==2)
			return -1;

		if(num2==2)
			count=count+2;	
		else if(num2>=0)
			count++;
	}
	if(i==13)/*2--lable*/
	{

		word2 = strtok(NULL,  " ");
		CHECK_NULL(word2);
		word2=skip_leading_spaces(word2);
		remove_trailing_spaces(word2);
		num2=check_0_1_2_3(word2, line2 ,reg2 ,  symbol_ptr , f_binary ,f_ext , pass , func,  data_items , sy_count);
		if(num2==-1 && pass==2)
			return -1;

		if(num2==2)
			count=count+2;	
		else if(num2>=0)
			count++;	
	}
	if(i==14 || i==15 )/*nothing*/
	{
			
	}

	if(num1==1)
	line[0]=line[0]|4;
	if(num1==2)
	line[0]=line[0]|8;
	if(num1==3)
	line[0]=line[0]|12;
	line[0]=line[0]|num2;


	word2=strtok(NULL,  "\n");
	if(is_empty(word2)!=1)/*there are chars after the end*/
		return -1;

	if(pass==2)/*print to .ob*/ 
	{
/********************************FIRST LINE OPCODE**************/

		fprintf(f_binary,"%c",count_of_lines);/*write the adress to file*/
		fwrite(line, 1, 2, f_binary);/*write the line to file*/
		fprintf(f_binary,"\n");/*write the /n to file*/
		SEGMENTATION_FAULT(count_of_lines)
		count_of_lines++;
		
/**IF THERE IS TWO REGISTERS*/
		if(reg2flag)
		{

			fprintf(f_binary,"%c",count_of_lines);/*write the adress to file*/
			fwrite(line2, 1, 2, f_binary);/*write the line to file*/
			fprintf(f_binary,"\n");/*write the /n to file*/
			SEGMENTATION_FAULT(count_of_lines)
			count_of_lines++;
		}
		else 
		{
			if(i<=4)
			{
				/*register destineion*/
				if(num1==3)
				{
					*line1=(*line1)<<4;

					fprintf(f_binary,"%c",count_of_lines);/*write the adress to file*/
					fwrite(line1, 1, 2, f_binary);/*write the line to file*/
					fprintf(f_binary,"\n");/*write the /n to file*/
					SEGMENTATION_FAULT(count_of_lines)
					count_of_lines++;
	
				}
				else
				{

					fprintf(f_binary,"%c",count_of_lines);/*write the adress to file*/
					fwrite(line1, 1, 2, f_binary);/*write the line to file*/
					fprintf(f_binary,"\n");/*write the /n to file*/
					SEGMENTATION_FAULT(count_of_lines)
					count_of_lines++;
				}
				if(num1==2)
				{

					fprintf(f_binary,"%c",count_of_lines);/*write the adress to file*/
					fwrite(reg1, 1, 2, f_binary);/*write the line to file*/
					fprintf(f_binary,"\n");/*write the /n to file*/	
					SEGMENTATION_FAULT(count_of_lines)
					count_of_lines++;
				}

				
				/*second line*/

				fprintf(f_binary,"%c",count_of_lines);/*write the adress to file*/
				fwrite(line2, 1, 2, f_binary);/*write the line to file*/
				fprintf(f_binary,"\n");/*write the /n to file*/
				SEGMENTATION_FAULT(count_of_lines)
				count_of_lines++;
				if(num2==2)
				{

					fprintf(f_binary,"%c",count_of_lines);/*write the adress to file*/
					fwrite(reg2, 1, 2, f_binary);/*write the line to file*/
					fprintf(f_binary,"\n");/*write the /n to file*/	
					SEGMENTATION_FAULT(count_of_lines)
					count_of_lines++;
				}
			}
			else if(i <14)
			{
				fprintf(f_binary,"%c",count_of_lines);/*write the adress to file*/
				fwrite(line2, 1, 2, f_binary);/*write the line to file*/
				fprintf(f_binary,"\n");/*write the /n to file*/
				SEGMENTATION_FAULT(count_of_lines)
				count_of_lines++;
				if(num2==2)
				{

					fprintf(f_binary,"%c",count_of_lines);/*write the adress to file*/
					fwrite(reg2, 1, 2, f_binary);/*write the line to file*/
					fprintf(f_binary,"\n");/*write the /n to file*/
					SEGMENTATION_FAULT(count_of_lines)	
					count_of_lines++;
				}
			}
		}

	}
	return count;
}


