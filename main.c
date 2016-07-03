#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "bigNumber.h"

char str1[BN_MAX_SIZE + 2];
char str2[BN_MAX_SIZE + 2];

int getInput(char *str)
{
	char getc;
	char *str_index = str;
	while( (getc = getchar()) != '\n')
	{
		*str_index = getc;
		str_index++;
	}
	*str_index = '\0';
}

int main()
{ 
	while(1)
	{	
		printf("input a to add\n");
		printf("input s to sub\n");
		printf("input i to increase\n");
		printf("input d to decrease\n");
		printf("input z to check if is zero\n");
		printf("input c to compare\n");
		printf("input m to multiply\n");
		printf("input v to divide\n");
		printf("input others to exit\n");
		
		int function_index;
		char getc = getchar();
		if('a' == getc)
		{
			function_index = 1;
		}
		else if('s' == getc)
		{
			function_index = 2;
		}
		else if('i' == getc)
		{
			function_index = 3;
		}
		else if('d' == getc)
		{
			function_index = 4;
		}
		else if('z' == getc)
		{
			function_index = 5;
		}
		else if('c' == getc)
		{
			function_index = 6;
		}
		else if('m' == getc)
		{
			function_index = 7;
		}
		else if('v' == getc)
		{
			function_index = 8;
		}
		else
		{
			break;
		}
		while(getchar() != '\n');		
		printf("now input your number below\n");
		
		char *result = NULL;
		int answer = 0;
		int situation;
		
		if(1 == function_index)
		{
			getInput(str1);
			getInput(str2);			
			situation = BN_add_i(str1, str2, &result);
			printf("function return : %d\n",  situation);
			printf("result : %s\n\n", result);		
			if(BN_SUCCESS == situation)
			{
				free(result);
			}
		}
		else if(2 == function_index)
		{
			getInput(str1);
			getInput(str2);			
			situation = BN_sub_i(str1, str2, &result);
			printf("function return : %d\n",  situation);
			printf("result : %s\n\n", result);		
			if(BN_SUCCESS == situation)
			{
				free(result);
			}			
		}
		else if(3 == function_index)
		{
			getInput(str1);	
			situation = BN_increase_i(str1, &result);
			printf("function return : %d\n",  situation);
			printf("result : %s\n\n", result);		
			if(BN_SUCCESS == situation)
			{
				free(result);
			}					
		}
		else if(4 == function_index)
		{
			getInput(str1);	
			situation = BN_decrease_i(str1, &result);
			printf("function return : %d\n",  situation);
			printf("result : %s\n\n", result);		
			if(BN_SUCCESS == situation)
			{
				free(result);
			}		
		}
		else if(5 == function_index)
		{
			getInput(str1);	
			situation = BN_isZero_i(str1, &answer);
			printf("function return : %d\n",  situation);
			printf("result : %d\n\n", answer);					
		}		
		else if(6 == function_index)
		{
			getInput(str1);	
			getInput(str2);
			situation = BN_compare_i(str1, str2, &answer);
			printf("function return : %d\n",  situation);
			printf("result : %d\n\n", answer);				
		}
		else if(7 == function_index)
		{
			getInput(str1);
			getInput(str2);			
			situation = BN_mul_i(str1, str2, &result);
			printf("function return : %d\n", situation );
			printf("result : %s\n\n", result);		
			if(BN_SUCCESS == situation)
			{
				free(result);
			}			
		}
		else if(8 == function_index)
		{
			getInput(str1);
			getInput(str2);			
			char *remain;
			situation = BN_div_i(str1, str2, &result, &remain);
			printf("function return : %d\n", situation );
			printf("result : %s\n", result);
			printf("remain : %s\n\n", remain);	
			if(BN_SUCCESS == situation)
			{	
				free(result);		
				free(remain);	
			}
		}
		else
		{
		}
	}
	
	return 0;
}
