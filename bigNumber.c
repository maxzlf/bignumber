/******************************************************************************\
	Big Number manipulation
\******************************************************************************/



/***include system head files***/
#include <stdlib.h>
#include <string.h>
#include <assert.h>

/***include inner head files***/
#include "bigNumber.h"


/***************************functions statements*******************************/
static int BN_add_in(IN char *addee, IN char *adder, OUT char **pointToResult);
static int BN_sub_in(IN char *subee, IN char *suber, OUT char **pointToResult);
static int BN_increase_in(IN char *number, OUT char **pointToResult);
static int BN_decrease_in(IN char *number, OUT char **pointToResult);
static int BN_mul_in(IN char *mulee, IN char *muler, OUT char **pointToResult);
static int BN_div_in(IN char *divee, IN char *diver, OUT char **pointToResult, OUT char **pointToRem);
static int BN_compare_in(IN char *numStr1, IN char *numStr2, OUT int *result);
static bool BN_hasIllegal(IN char *strNumber);
static int BN_charactorAdd(IN char addee, IN char adder, IN int carry, OUT char *result);
static int BN_charactorSub(IN char subee, IN char suber, IN int carry, OUT char *result);
static int BN_charactorMul(IN char mulee, IN char muler, IN int carry, OUT char *result);



/*******************************************************************************
*	Func Name    : BN_add_i
*	Date created : 2013-11-30 
*	Author		 : zhulinfeng
*	Description  : Add two numbers
*	----------------------------------------------------------------------------
*   Input		 : char *p_addee_c		
*				 : char *p_adder_c	 
*   ----------------------------------------------------------------------------
*   Output		 : char **pp_pointToResult_c	//store the add result
*   ----------------------------------------------------------------------------
*   Return		 : int							//error code
*   ----------------------------------------------------------------------------
*	Caution		 : 
*******************************************************************************/
int BN_add_i(IN char *p_addee_c, IN char *p_adder_c, OUT char **pp_pointToResult_c)
{
	int situation;
	char *addee;
	char *adder;
	long p_addee_c_length;
	long p_adder_c_length;
	
	/**
	*  do some necessary check
	*  check if param is NULL
	*  check if input param is empty
	*  check if input param's length is out of size
	*  check if there is illegal charactor in input param
	**/
	if( NULL == p_addee_c || NULL == p_adder_c || NULL == pp_pointToResult_c)
	{
		return BN_PARAM_INVALID;
	}
	p_addee_c_length = strlen(p_addee_c);
	p_adder_c_length = strlen(p_adder_c);	
	if(0 == p_addee_c_length || 0 == p_adder_c_length)
	{
		return BN_INPUT_EMPTY;
	}
	if(BN_MAX_SIZE < p_addee_c_length || BN_MAX_SIZE < p_adder_c_length)
	{
		return BN_OUTOF_SIZE;
	}
	if('+' == *p_addee_c || '-' == *p_addee_c)
	{
		if(1 == p_addee_c_length)
		{
			return BN_INPUT_EMPTY;
		}
		if(false != BN_hasIllegal(p_addee_c + 1))
		{
			return BN_ILLEGAL_CHARACTOR;
		}
	}
	else
	{
		if(false != BN_hasIllegal(p_addee_c))
		{
			return BN_ILLEGAL_CHARACTOR;
		}		
	}
	
	if('+' == *p_adder_c || '-' == *p_adder_c)
	{
		if(1 == p_adder_c_length)
		{
			return BN_INPUT_EMPTY;
		}
		if(false != BN_hasIllegal(p_adder_c + 1))
		{
			return BN_ILLEGAL_CHARACTOR;
		}
	}
	else
	{
		if(false != BN_hasIllegal(p_adder_c))
		{
			return BN_ILLEGAL_CHARACTOR;
		}		
	}
	
	
	/***check symbol***/
	char addee_sym;
	char adder_sym;
	if('-' == *p_addee_c)
	{
		addee_sym = '-';
		addee = p_addee_c + 1;
	}
	else if( '+' == *p_addee_c)
	{
		addee_sym = '+';
		addee = p_addee_c + 1;
	}
	else
	{
		addee_sym = '+';
		addee = p_addee_c;		
	}
	
	if('-' == *p_adder_c)
	{
		adder_sym = '-';
		adder = p_adder_c + 1;
	}
	else if( '+' == *p_adder_c)
	{
		adder_sym = '+';
		adder = p_adder_c + 1;
	}	
	else
	{
		adder_sym = '+';
		adder = p_adder_c;
	}
	
	/***calculate***/
	if( '+' == addee_sym && '+' == adder_sym)
	{
		situation = BN_add_in(addee, adder, pp_pointToResult_c);
	}
	else if( '+' == addee_sym && '-' == adder_sym)
	{
		situation = BN_sub_in(addee, adder, pp_pointToResult_c);
	}
	else if( '-' == addee_sym && '+' == adder_sym)
	{
		situation = BN_sub_in(adder, addee, pp_pointToResult_c);		
	}
	else
	{
		situation = BN_add_in(addee, adder, pp_pointToResult_c);
		if(BN_SUCCESS == situation)
		{
			**pp_pointToResult_c = '-';
		}
	}
	
	return situation;
}


/*******************************************************************************
*	Func Name    : BN_sub_i
*	Date created : 2013-11-30 
*	Author		 : zhulinfeng
*	Description  : Subtract two numbers
*	----------------------------------------------------------------------------
*   Input		 : char *p_subee_c		
*				 : char *p_suber_c	 
*   ----------------------------------------------------------------------------
*   Output		 : char **pp_pointToResult_c	//store the subtract result
*   ----------------------------------------------------------------------------
*   Return		 : int							//error code
*   ----------------------------------------------------------------------------
*	Caution		 : 
*******************************************************************************/
int BN_sub_i(IN char *p_subee_c, IN char *p_suber_c, OUT char **pp_pointToResult_c)
{
	int situation;
	char *addee;
	char *adder;
	long p_subee_c_length;
	long p_suber_c_length;
	
	/**
	*  do some necessary check
	*  check if param is NULL
	*  check if input param is empty
	*  check if input param's length is out of size
	*  check if there is illegal charactor in input param
	**/
	if( NULL == p_subee_c || NULL == p_suber_c || NULL == pp_pointToResult_c)
	{
		return BN_PARAM_INVALID;
	}
	p_subee_c_length = strlen(p_subee_c);
	p_suber_c_length = strlen(p_suber_c);	
	if(0 == p_subee_c_length || 0 == p_suber_c_length)
	{
		return BN_INPUT_EMPTY;
	}
	if(BN_MAX_SIZE < p_subee_c_length || BN_MAX_SIZE < p_suber_c_length)
	{
		return BN_OUTOF_SIZE;
	}
	if('+' == *p_subee_c || '-' == *p_subee_c)
	{
		if(1 == p_subee_c_length)
		{
			return BN_INPUT_EMPTY;
		}
		if(false != BN_hasIllegal(p_subee_c + 1))
		{
			return BN_ILLEGAL_CHARACTOR;
		}
	}
	else
	{
		if(false != BN_hasIllegal(p_subee_c))
		{
			return BN_ILLEGAL_CHARACTOR;
		}		
	}
	
	if('+' == *p_suber_c || '-' == *p_suber_c)
	{
		if(1 == p_suber_c_length)
		{
			return BN_INPUT_EMPTY;
		}
		if(false != BN_hasIllegal(p_suber_c + 1))
		{
			return BN_ILLEGAL_CHARACTOR;
		}
	}
	else
	{
		if(false != BN_hasIllegal(p_suber_c))
		{
			return BN_ILLEGAL_CHARACTOR;
		}		
	}
	
	/***check symbol***/
	char addee_sym;
	char adder_sym;
	if('-' == *p_subee_c)
	{
		addee_sym = '-';
		addee = p_subee_c + 1;
	}
	else if( '+' == *p_subee_c)
	{
		addee_sym = '+';
		addee = p_subee_c + 1;
	}
	else
	{
		addee_sym = '+';
		addee = p_subee_c;		
	}
	
	if('-' == *p_suber_c)
	{
		adder_sym = '-';
		adder = p_suber_c + 1;
	}
	else if( '+' == *p_suber_c)
	{
		adder_sym = '+';
		adder = p_suber_c + 1;
	}	
	else
	{
		adder_sym = '+';
		adder = p_suber_c;
	}
	
	/***calculate***/
	if( '+' == addee_sym && '+' == adder_sym)
	{
		situation = BN_sub_in(addee, adder, pp_pointToResult_c);
	}
	else if( '+' == addee_sym && '-' == adder_sym)
	{
		situation = BN_add_in(addee, adder, pp_pointToResult_c);
	}
	else if( '-' == addee_sym && '+' == adder_sym)
	{
		situation = BN_add_in(adder, addee, pp_pointToResult_c);	
		if(BN_SUCCESS == situation)
		{
			**pp_pointToResult_c = '-';
		}	
	}
	else
	{
		situation = BN_sub_in(adder, addee, pp_pointToResult_c);
	}
	
	return situation;
}


/*******************************************************************************
*	Func Name    : BN_increase_i
*	Date created : 2013-11-30 
*	Author		 : zhulinfeng
*	Description  : Incrase a number by one step
*	----------------------------------------------------------------------------
*   Input		 : char *p_numStr_c		
*   ----------------------------------------------------------------------------
*   Output		 : char **pp_pointToResult_c	//store the increase result
*   ----------------------------------------------------------------------------
*   Return		 : int							//error code
*   ----------------------------------------------------------------------------
*	Caution		 : 
*******************************************************************************/
int BN_increase_i(IN char *p_numStr_c, OUT char **pp_pointToResult_c)
{
	int situation;
	char *increaser;
	long p_numStr_c_length;
	
	/**
	*  do some necessary check
	*  check if param is NULL
	*  check if input param is empty
	*  check if input param's length is out of size
	*  check if there is illegal charactor in input param
	**/
	if( NULL == p_numStr_c || NULL == pp_pointToResult_c)
	{
		return BN_PARAM_INVALID;
	}
	p_numStr_c_length = strlen(p_numStr_c);
	if(0 == p_numStr_c_length)
	{
		return BN_INPUT_EMPTY;
	}
	if(BN_MAX_SIZE < p_numStr_c_length)
	{
		return BN_OUTOF_SIZE;
	}	
	if('+' == *p_numStr_c || '-' == *p_numStr_c)
	{
		if(1 == p_numStr_c_length)
		{
			return BN_INPUT_EMPTY;
		}
		if(false != BN_hasIllegal(p_numStr_c + 1))
		{
			return BN_ILLEGAL_CHARACTOR;
		}
	}
	else
	{
		if(false != BN_hasIllegal(p_numStr_c))
		{
			return BN_ILLEGAL_CHARACTOR;
		}		
	}
	
	
	/***check symbol***/
	char numStrSymbol;
	increaser = p_numStr_c;
	if( '+' == *p_numStr_c)
	{
		numStrSymbol = '+';
		increaser++;
	}
	else if('-' == *p_numStr_c)
	{
		numStrSymbol = '-';
		increaser++;
	}	
	else
	{
		numStrSymbol = '+';
	}
	
	/***calculate***/	
	if('+' == numStrSymbol)
	{
		situation = BN_increase_in(increaser, pp_pointToResult_c);
	}
	else
	{
		situation = BN_decrease_in(increaser, pp_pointToResult_c);
		if(BN_SUCCESS == situation)
		{
			if('-' == **pp_pointToResult_c)
			{
				**pp_pointToResult_c = '0';
			}
			else
			{
				**pp_pointToResult_c = '-';
			}
		}
	}
	
	return situation;
}


/*******************************************************************************
*	Func Name    : BN_decrease_i
*	Date created : 2013-11-30 
*	Author		 : zhulinfeng
*	Description  : Decrase a number by one step
*	----------------------------------------------------------------------------
*   Input		 : char *p_numStr_c		
*   ----------------------------------------------------------------------------
*   Output		 : char **pp_pointToResult_c	//store the decrase result
*   ----------------------------------------------------------------------------
*   Return		 : int							//error code
*   ----------------------------------------------------------------------------
*	Caution		 : 
*******************************************************************************/
int BN_decrease_i(IN char *p_numStr_c, OUT char **pp_pointToResult_c)
{
	int situation;
	char *decreaser;
	long p_numStr_c_length;
	
	/**
	*  do some necessary check
	*  check if param is NULL
	*  check if input param is empty
	*  check if input param's length is out of size
	*  check if there is illegal charactor in input param
	**/
	if( NULL == p_numStr_c || NULL == pp_pointToResult_c)
	{
		return BN_PARAM_INVALID;
	}
	p_numStr_c_length = strlen(p_numStr_c);
	if(0 == p_numStr_c_length)
	{
		return BN_INPUT_EMPTY;
	}
	if(BN_MAX_SIZE < p_numStr_c_length)
	{
		return BN_OUTOF_SIZE;
	}	
	if('+' == *p_numStr_c || '-' == *p_numStr_c)
	{
		if(1 == p_numStr_c_length)
		{
			return BN_INPUT_EMPTY;
		}
		if(false != BN_hasIllegal(p_numStr_c + 1))
		{
			return BN_ILLEGAL_CHARACTOR;
		}
	}
	else
	{
		if(false != BN_hasIllegal(p_numStr_c))
		{
			return BN_ILLEGAL_CHARACTOR;
		}		
	}
	
	/***check symbol***/
	char numStrSymbol;
	decreaser = p_numStr_c;
	if( '+' == *p_numStr_c)
	{
		numStrSymbol = '+';
		decreaser++;
	}
	else if('-' == *p_numStr_c)
	{
		numStrSymbol = '-';
		decreaser++;
	}	
	else
	{
		numStrSymbol = '+';
	}
	
	/***calculate***/
	
	if('+' == numStrSymbol)
	{
		situation = BN_decrease_in(decreaser, pp_pointToResult_c);
	}
	else
	{
		situation = BN_increase_in(decreaser, pp_pointToResult_c);
		if(BN_SUCCESS == situation)
		{
			**pp_pointToResult_c = '-';
		}
	}
	
	return situation;
}


/*******************************************************************************
*	Func Name    : BN_mul_i
*	Date created : 2013-11-30 
*	Author		 : zhulinfeng
*	Description  : Multiply two numbers
*	----------------------------------------------------------------------------
*   Input		 : char *p_mulee_c
*				   char *p_muler_c		
*   ----------------------------------------------------------------------------
*   Output		 : char **pp_pointToResult_c	//store the multiply result
*   ----------------------------------------------------------------------------
*   Return		 : int							//error code
*   ----------------------------------------------------------------------------
*	Caution		 : 
*******************************************************************************/
int BN_mul_i(IN char *p_mulee_c, IN char *p_muler_c, OUT char **pp_pointToResult_c)
{
	int situation;
	char *mulee;
	char *muler;
	long p_mulee_c_length;
	long p_muler_c_length;
	
	/**
	*  do some necessary check
	*  check if param is NULL
	*  check if input param is empty
	*  check if input param's length is out of size
	*  check if there is illegal charactor in input param
	**/
	if( NULL == p_mulee_c || NULL == p_muler_c || NULL == pp_pointToResult_c)
	{
		return BN_PARAM_INVALID;
	}
	p_mulee_c_length = strlen(p_mulee_c);
	p_muler_c_length = strlen(p_muler_c);	
	if(0 == p_mulee_c_length || 0 == p_muler_c_length)
	{
		return BN_INPUT_EMPTY;
	}
	if(BN_MAX_SIZE < p_mulee_c_length || BN_MAX_SIZE < p_muler_c_length)
	{
		return BN_OUTOF_SIZE;
	}
	if('+' == *p_mulee_c || '-' == *p_mulee_c)
	{
		if(1 == p_mulee_c_length)
		{
			return BN_INPUT_EMPTY;
		}
		if(false != BN_hasIllegal(p_mulee_c + 1))
		{
			return BN_ILLEGAL_CHARACTOR;
		}
	}
	else
	{
		if(false != BN_hasIllegal(p_mulee_c))
		{
			return BN_ILLEGAL_CHARACTOR;
		}		
	}
	
	if('+' == *p_muler_c || '-' == *p_muler_c)
	{
		if(1 == p_muler_c_length)
		{
			return BN_INPUT_EMPTY;
		}
		if(false != BN_hasIllegal(p_muler_c + 1))
		{
			return BN_ILLEGAL_CHARACTOR;
		}
	}
	else
	{
		if(false != BN_hasIllegal(p_muler_c))
		{
			return BN_ILLEGAL_CHARACTOR;
		}		
	}
	
	/***check symbol***/
	char mulee_sym;
	char muler_sym;
	if('-' == *p_mulee_c)
	{
		mulee_sym = '-';
		mulee = p_mulee_c + 1;
	}
	else if( '+' == *p_mulee_c)
	{
		mulee_sym = '+';
		mulee = p_mulee_c + 1;
	}
	else
	{
		mulee_sym = '+';
		mulee = p_mulee_c;		
	}
	
	if('-' == *p_muler_c)
	{
		muler_sym = '-';
		muler = p_muler_c + 1;
	}
	else if( '+' == *p_muler_c)
	{
		muler_sym = '+';
		muler = p_muler_c + 1;
	}	
	else
	{
		muler_sym = '+';
		muler = p_muler_c;
	}
	
	/***calculate***/
	situation = BN_mul_in(mulee, muler, pp_pointToResult_c);
	if(BN_SUCCESS != situation)
	{
		return situation;
	}
	if(mulee_sym == muler_sym)
	{
		**pp_pointToResult_c = '0';
	}
	else
	{
		**pp_pointToResult_c = '-';
	}
	
	return situation;
}


/*******************************************************************************
*	Func Name    : BN_div_i
*	Date created : 2013-11-30 
*	Author		 : zhulinfeng
*	Description  : Divide two numbers
*	----------------------------------------------------------------------------
*   Input		 : char *p_divee_c
*				   char *p_diver_c		
*   ----------------------------------------------------------------------------
*   Output		 : char **pp_pointToResult_c	//store the divide result
*   ----------------------------------------------------------------------------
*   Return		 : int							//error code
*   ----------------------------------------------------------------------------
*	Caution		 : 
*******************************************************************************/
int BN_div_i(IN char *p_divee_c, IN char *p_diver_c, OUT char **pp_pointToResult_c, OUT char **pp_pointToRem_c)
{
	int situation;
	char *divee;
	char *diver;
	long p_divee_c_length;
	long p_diver_c_length;
	
	/**
	*  do some necessary check
	*  check if param is NULL
	*  check if input param is empty
	*  check if input param's length is out of size
	*  check if there is illegal charactor in input param
	**/
	if( NULL == p_divee_c || NULL == p_diver_c || NULL == pp_pointToResult_c || NULL == pp_pointToRem_c)
	{
		return BN_PARAM_INVALID;
	}
	p_divee_c_length = strlen(p_divee_c);
	p_diver_c_length = strlen(p_diver_c);	
	if(0 == p_divee_c_length || 0 == p_diver_c_length)
	{
		return BN_INPUT_EMPTY;
	}
	if(BN_MAX_SIZE < p_divee_c_length || BN_MAX_SIZE < p_diver_c_length)
	{
		return BN_OUTOF_SIZE;
	}
	if('+' == *p_divee_c || '-' == *p_divee_c)
	{
		if(1 == p_divee_c_length)
		{
			return BN_INPUT_EMPTY;
		}
		if(false != BN_hasIllegal(p_divee_c + 1))
		{
			return BN_ILLEGAL_CHARACTOR;
		}
	}
	else
	{
		if(false != BN_hasIllegal(p_divee_c))
		{
			return BN_ILLEGAL_CHARACTOR;
		}		
	}
	
	if('+' == *p_diver_c || '-' == *p_diver_c)
	{
		if(1 == p_diver_c_length)
		{
			return BN_INPUT_EMPTY;
		}
		if(false != BN_hasIllegal(p_diver_c + 1))
		{
			return BN_ILLEGAL_CHARACTOR;
		}
	}
	else
	{
		if(false != BN_hasIllegal(p_diver_c))
		{
			return BN_ILLEGAL_CHARACTOR;
		}		
	}
	
	/***check symbol***/
	char divee_sym;
	char diver_sym;
	if('-' == *p_divee_c)
	{
		divee_sym = '-';
		divee = p_divee_c + 1;
	}
	else if( '+' == *p_divee_c)
	{
		divee_sym = '+';
		divee = p_divee_c + 1;
	}
	else
	{
		divee_sym = '+';
		divee = p_divee_c;		
	}
	
	if('-' == *p_diver_c)
	{
		diver_sym = '-';
		diver = p_diver_c + 1;
	}
	else if( '+' == *p_diver_c)
	{
		diver_sym = '+';
		diver = p_diver_c + 1;
	}	
	else
	{
		diver_sym = '+';
		diver = p_diver_c;
	}
	
	/***calculate***/
	situation = BN_div_in(divee, diver, pp_pointToResult_c, pp_pointToRem_c);
	if(BN_SUCCESS != situation)
	{
		return situation;
	}
	if(divee_sym == diver_sym)
	{
		**pp_pointToResult_c = '0';
		**pp_pointToRem_c = '0';
	}
	else
	{
		**pp_pointToResult_c = '-';
		**pp_pointToRem_c = '-';
	}
	
	return situation;
}


/*******************************************************************************
*	Func Name    : BN_isZero_i
*	Date created : 2013-11-30 
*	Author		 : zhulinfeng
*	Description  : Check if a number is zero
*	----------------------------------------------------------------------------
*   Input		 : char *p_numStr_c	
*   ----------------------------------------------------------------------------
*   Output		 : int *p_result_i					//store the check result
*				   =0  not zero
*				   >0  is zero
*   ----------------------------------------------------------------------------
*   Return		 : int								//error code
*   ----------------------------------------------------------------------------
*	Caution		 : 
*******************************************************************************/
int BN_isZero_i(IN char *p_numStr_c, OUT int *p_result_i)
{	
	long p_numStr_c_length;
	/**
	*  do some necessary check
	*  check if param is NULL
	*  check if input param is empty
	*  check if input param's length is out of size
	*  check if there is illegal charactor in input param
	**/
	if( NULL == p_numStr_c || NULL == p_result_i)
	{
		return BN_PARAM_INVALID;
	}
	p_numStr_c_length = strlen(p_numStr_c);
	if(0 == p_numStr_c_length)
	{
		return BN_INPUT_EMPTY;
	}
	if(BN_MAX_SIZE < p_numStr_c_length)
	{
		return BN_OUTOF_SIZE;
	}	
	if('+' == *p_numStr_c || '-' == *p_numStr_c)
	{
		if(1 == p_numStr_c_length)
		{
			return BN_INPUT_EMPTY;
		}
		if(false != BN_hasIllegal(p_numStr_c + 1))
		{
			return BN_ILLEGAL_CHARACTOR;
		}
	}
	else
	{
		if(false != BN_hasIllegal(p_numStr_c))
		{
			return BN_ILLEGAL_CHARACTOR;
		}		
	}
	
	/***move to head of number***/
	char *illegalCheckHead = p_numStr_c;
	if('+' == *p_numStr_c || '-' == *p_numStr_c)
	{
		illegalCheckHead++;
	}
	
	/***calculate***/
	int answer = 1;
	char *numStr_index = illegalCheckHead;
	while( '\0' != *numStr_index)
	{
		if( '0' != *numStr_index)
		{
			answer = 0;
			break;
		}
		numStr_index++;
	}
	*p_result_i = answer;
	
	return BN_SUCCESS;
}


/*******************************************************************************
*	Func Name    : BN_compare_i
*	Date created : 2013-11-30 
*	Author		 : zhulinfeng
*	Description  : Compare two numbers
*	----------------------------------------------------------------------------
*   Input		 : char *p_numStr1_c
*				   char *p_numStr2_c		
*   ----------------------------------------------------------------------------
*   Output		 : int *p_result_i				//store the compare result
*				   <0  numStr1 < numStr2
*				   =0  numStr1 = numStr2
*				   >0  numStr1 > numStr2
*   ----------------------------------------------------------------------------
*   Return		 : int							//error code
*   ----------------------------------------------------------------------------
*	Caution		 : 
*******************************************************************************/
int BN_compare_i(IN char *p_numStr1_c, IN char *p_numStr2_c, OUT int *p_result_i)
{
	int situation;
	char *addee;
	char *adder;
	long p_numStr1_c_length;
	long p_numStr2_c_length;
	
	/**
	*  do some necessary check
	*  check if param is NULL
	*  check if input param is empty
	*  check if input param's length is out of size
	*  check if there is illegal charactor in input param
	**/
	if( NULL == p_numStr1_c || NULL == p_numStr2_c || NULL == p_result_i)
	{
		return BN_PARAM_INVALID;
	}
	p_numStr1_c_length = strlen(p_numStr1_c);
	p_numStr2_c_length = strlen(p_numStr2_c);
	if(0 == p_numStr1_c_length || 0 == p_numStr2_c_length)
	{
		return BN_INPUT_EMPTY;
	}
	if(BN_MAX_SIZE < p_numStr1_c_length || BN_MAX_SIZE < p_numStr2_c_length)
	{
		return BN_OUTOF_SIZE;
	}	
	if('+' == *p_numStr1_c || '-' == *p_numStr1_c)
	{
		if(1 == p_numStr1_c_length)
		{
			return BN_INPUT_EMPTY;
		}
		if(false != BN_hasIllegal(p_numStr1_c + 1))
		{
			return BN_ILLEGAL_CHARACTOR;
		}
	}
	else
	{
		if(false != BN_hasIllegal(p_numStr1_c))
		{
			return BN_ILLEGAL_CHARACTOR;
		}		
	}
	if('+' == *p_numStr2_c || '-' == *p_numStr2_c)
	{
		if(1 == p_numStr2_c_length)
		{
			return BN_INPUT_EMPTY;
		}
		if(false != BN_hasIllegal(p_numStr2_c + 1))
		{
			return BN_ILLEGAL_CHARACTOR;
		}
	}
	else
	{
		if(false != BN_hasIllegal(p_numStr2_c))
		{
			return BN_ILLEGAL_CHARACTOR;
		}		
	}
	
	/***check symbol***/
	char addee_sym;
	char adder_sym;
	if('-' == *p_numStr1_c)
	{
		addee_sym = '-';
		addee = p_numStr1_c + 1;
	}
	else if( '+' == *p_numStr1_c)
	{
		addee_sym = '+';
		addee = p_numStr1_c + 1;
	}
	else
	{
		addee_sym = '+';
		addee = p_numStr1_c;		
	}
	
	if('-' == *p_numStr2_c)
	{
		adder_sym = '-';
		adder = p_numStr2_c + 1;
	}
	else if( '+' == *p_numStr2_c)
	{
		adder_sym = '+';
		adder = p_numStr2_c + 1;
	}	
	else
	{
		adder_sym = '+';
		adder = p_numStr2_c;
	}
	
	/***calculate***/
	int answer;
	if( '+' == addee_sym && '+' == adder_sym)
	{
		situation = BN_compare_in(addee, adder, &answer);
		*p_result_i = answer;
	}
	else if( '+' == addee_sym && '-' == adder_sym)
	{
		situation = BN_compare_in(addee, adder, &answer);
		if(BN_SUCCESS == situation)
		{
			int zeroResult;
			BN_isZero_i(addee, &zeroResult);
			if(0 == answer && zeroResult > 0)
			{
				*p_result_i = 0;
			}
			else
			{
				*p_result_i = 1;
			}
		}
	}
	else if( '-' == addee_sym && '+' == adder_sym)
	{
		situation = BN_compare_in(addee, adder, &answer);
		if(BN_SUCCESS == situation)
		{
			int zeroResult;
			BN_isZero_i(addee, &zeroResult);
			if(0 == answer && zeroResult > 0)
			{
				*p_result_i = 0;
			}
			else
			{
				*p_result_i = -1;
			}
		}
	}
	else
	{
		situation = BN_compare_in(adder, addee, &answer);
		*p_result_i = answer;
	}
	
	return situation;
}




/******************************************************************************\
*	Inner function, should not be used outside this file
*	You are expected to know about some tips below:
*
*	>1.All the functions here will ignore the symbol of input number(+ or -), 
*	so you should not take '+' or '-' in your input param. You must deal it 
*	outside these function yourself. The input number strings should only have 
*   charactors between '0' and '9'
*
*	>2.But these functions will put necessary symbol in result, so you should 
*	watch out.
*
*	>3.All the result number string will be put in a memory block the function
*	malloced, and the address of the memory have been put in the output param;
*	It's the user's responsibility to free the memory block when they are never
*	needed.
*
*	>4.After you have called these functions, you should check the return result
*   If the result is BN_SUCCESS, it indicates the function you called works well,
*   if not, there must be something error.
\******************************************************************************/


/*******************************************************************************
*	Func Name    : BN_add_in
*	Date created : 2013-11-29 
*	Author		 : zhulinfeng
*	Description  : Add two numbers
*	----------------------------------------------------------------------------
*   Input		 : char *addee		
*				 : char *adderer		 
*   ----------------------------------------------------------------------------
*   Output		 : char **pointToResult	//store the add result
*   ----------------------------------------------------------------------------
*   Return		 : int					//error code
*   ----------------------------------------------------------------------------
*	Caution		 : 
*******************************************************************************/
static int BN_add_in(IN char *addee, IN char *adder, OUT char **pointToResult)
{
	long length_addee;
	long length_adder;
	/**
	*  do some necessary check
	*  check if the input string is NULL
	*  check if the input string is out of size
	*  check if the input string is empty
	*  chekc if the input string has illegal charactor
	**/
	assert(NULL != addee);
	assert(NULL != adder);
	assert(NULL != pointToResult);
	length_addee = strlen(addee);
	length_adder = strlen(adder);
	assert(length_addee > 0 && length_addee <= BN_MAX_SIZE);
	assert(length_adder > 0 && length_adder <= BN_MAX_SIZE);
	
	/**
	*  ask for memory 
	*  explain of number 3
	*  1. one byte for carry
	*  2. one byte for the end '\n'
	*  3. one byte for the symbol '+' or '-'
	**/
	long malloc_size;
	if(length_addee >= length_adder)
	{
		malloc_size = length_addee + 3;
	}else
	{
		malloc_size = length_adder + 3;
	}
	*pointToResult = (char*)malloc(malloc_size * sizeof(char));
	if(NULL == *pointToResult)
	{
		return BN_NO_MEMORY;
	}
	char *tmp = *pointToResult + malloc_size - 1;
	*tmp = '\0';
	
	
	/**
	*  calculation
	*  from tail to head
	**/
	char* addee_index = addee + length_addee - 1;
	char* adder_index = adder + length_adder - 1;
	char* result_index = *pointToResult + malloc_size - 2;
	int flow = 0;
	char c_addee;
	char c_adder;
	while(addee_index >= addee || adder_index >= adder)
	{
		if(addee_index >= addee)
		{
			c_addee = *addee_index;
		}
		else
		{
			c_addee = '0';
		}
		if(adder_index >= adder)
		{
			c_adder = *adder_index;
		}
		else
		{
			c_adder = '0';
		}
		flow = BN_charactorAdd(c_addee, c_adder, flow, result_index);
		addee_index--;
		adder_index--;
		result_index--;
	}//end of while
	*result_index = (char)(flow + '0');
	result_index--;
	*result_index = '0';
	
	return BN_SUCCESS;
}


/*******************************************************************************
*	Func Name    : BN_sub_in
*	Date created : 2013-11-29 
*	Author		 : zhulinfeng
*	Description  : Subtract two numbers
*	----------------------------------------------------------------------------
*   Input		 : char *subee		
*				 : char *suber		 
*   ----------------------------------------------------------------------------
*   Output		 : char **pointToResult	//store the subtract result
*   ----------------------------------------------------------------------------
*   Return		 : int					//error code
*   ----------------------------------------------------------------------------
*	Caution		 : 
*******************************************************************************/
static int BN_sub_in(IN char *subee, IN char *suber, OUT char **pointToResult)
{
	int situation;
	/**
	*  the symbol will fill the first element of result memory block
	*  symbol = '0' : subee is bigger than suber or equal with suber
	*  symbol = '-' : subee is smaller than suber
	**/
	char symbol = '0';
		
	long length_subee;
	long length_suber;
	
	/**
	*  do some necessary check
	*  check if the input string is NULL
	*  check if the input string is out of size
	*  check if the input string is empty
	*  chekc if the input string has illegal charactor
	**/
	assert(NULL != subee);
	assert(NULL != suber);
	assert(NULL != pointToResult);
	length_subee = strlen(subee);
	length_suber = strlen(suber);
	assert(length_subee > 0 && length_subee <= BN_MAX_SIZE);
	assert(length_suber > 0 && length_suber <= BN_MAX_SIZE);
	
	
	/**
	*  compare which input number string is bigger
	*  store the bigger one in bigger
	*  store the smaller one in smaller
	*  if they are the same, then alloc a memory filled with '0' and return
	**/
	char *bigger;
	char *smaller;
	int comResult;
	situation = BN_compare_in(subee, suber, &comResult);
	if( BN_SUCCESS != situation)
	{
		return situation;
	}
	if(comResult > 0)
	{
		bigger = subee;
		smaller = suber;		
		symbol = '0';	
	}
	else if(comResult < 0)
	{
		bigger = suber;
		smaller = subee;
		symbol = '-';		
	}
	else
	{
		*pointToResult = (char*)malloc(3 * sizeof(char));
		if(NULL == *pointToResult)
		{
			return BN_NO_MEMORY;
		}	
		char *tmp = *pointToResult;
		*tmp = '0';
		*(++tmp) = '0';
		*(++tmp) = '\0';
		return BN_SUCCESS;		
	}
	
	
	/**
	*  ask for memory
	*  explain of number 2
	*  1. one byte for the end '\n'
	*  2. one byte for the symbol '+' or '-'
	**/
	long malloc_size = strlen(bigger) + 2;
	*pointToResult = (char*)malloc(malloc_size * sizeof(char));
	if(NULL == *pointToResult)
	{
		return BN_NO_MEMORY;
	}
	char *tmp = *pointToResult + malloc_size - 1;
	*tmp = '\0';	
	
	/**
	*  calculate
	*  from tail to head
	**/
	char *bigger_index = bigger + strlen(bigger) - 1;
	char *smaller_index = smaller + strlen(smaller) - 1;
	char *result_index = *pointToResult + malloc_size - 2;
	int flow = 0;
	char c_subee;
	char c_suber;
	while(bigger_index >= bigger)
	{
		c_subee = *bigger_index;
		if(smaller_index >= smaller)
		{
			c_suber = *smaller_index;
		}
		else
		{
			c_suber = '0';
		}
		flow = BN_charactorSub(c_subee, c_suber, flow, result_index);
		bigger_index--;
		smaller_index--;
		result_index--;
	}//end of while
	*result_index = symbol;
		
	return BN_SUCCESS;
}


/*******************************************************************************
*	Func Name    : BN_increase_in
*	Date created : 2013-11-29 
*	Author		 : zhulinfeng
*	Description  : Increase a number by 1 step
*	----------------------------------------------------------------------------
*   Input		 : char *number	 
*   ----------------------------------------------------------------------------
*   Output		 : char **pointToResult	//store the multiply result
*   ----------------------------------------------------------------------------
*   Return		 : int					//error code
*   ----------------------------------------------------------------------------
*	Caution		 : 
*******************************************************************************/
static int BN_increase_in(IN char *number, OUT char **pointToResult)
{
	long number_length;
	/**
	*  do some necessary check
	*  check if the input string is NULL
	*  check if the input string is out of size
	*  check if the input string is empty
	*  chekc if the input string has illegal charactor
	**/
	assert(NULL != number);
	assert(NULL != pointToResult);
	number_length = strlen(number);
	assert(number_length > 0 && number_length <= BN_MAX_SIZE);
	
	/**
	*  ask for memory
	*  explain of number 3
	*  1. one byte for carry
	*  2. one byte for the end '\n'
	*  3. one byte for the symbol '+' or '-'
	**/
	*pointToResult = (char*)malloc((number_length + 3) * sizeof(char));
	if(NULL == *pointToResult)
	{
		return BN_NO_MEMORY;
	}
	char *tmp = *pointToResult + number_length + 3 - 1;
	*tmp = '\0';		
	
	/**
	*  calculate
	*  from tail to head
	**/
	char *number_index = number + number_length - 1;
	char *result_index = *pointToResult + number_length + 3 - 2;
	char adder = '1';
	int flow = 0;
	long flag = 0;
	while(number_index >= number)
	{
		if(0 == flag || 1 == flow)
		{
			flow = BN_charactorAdd(*number_index, adder, flow, result_index);
			assert( false != isdigit(*result_index));
			if(0 == flag)
			{
				adder--;
			}
			flag++;
		}
		else
		{
			*result_index = *number_index;	
		}
			
		number_index--;
		result_index--;
	}//end of while
	*result_index = (char)(flow + '0');
	*(--result_index) = '0';
	
	return BN_SUCCESS;
}



/*******************************************************************************
*	Func Name    : BN_decrease_in
*	Date created : 2013-11-29 
*	Author		 : zhulinfeng
*	Description  : Decrease a number by one step
*	----------------------------------------------------------------------------
*   Input		 : char *number	 
*   ----------------------------------------------------------------------------
*   Output		 : char **pointToResult	//store the decreased result
*   ----------------------------------------------------------------------------
*   Return		 : int					//error code
*   ----------------------------------------------------------------------------
*	Caution		 : 
*******************************************************************************/
static int BN_decrease_in(IN char *number, OUT char **pointToResult)
{
	long number_length;
	/**
	*  do some necessary check
	*  check if the input string is NULL
	*  check if the input string is out of size
	*  check if the input string is empty
	*  chekc if the input string has illegal charactor
	**/
	assert(NULL != number);
	assert(NULL != pointToResult);
	number_length = strlen(number);
	assert(number_length > 0 && number_length <= BN_MAX_SIZE);
	
	/***compare with "000"***/
	int cmpResult;
	int cmpSituation;
	cmpSituation = BN_compare_in(number, "000", &cmpResult);
	if( BN_SUCCESS != cmpSituation )
	{
		return cmpSituation;
	}
	if(0 == cmpResult)
	{
		*pointToResult = (char*)malloc(3 * sizeof(char));
		if( NULL == *pointToResult)
		{
			return BN_NO_MEMORY;	
		}
		char *tmp = *pointToResult;
		*tmp = '-';
		*(++tmp) = '1';
		*(++tmp) = '\0';
		return BN_SUCCESS;
	}
	
	/**
	*  ask for memory
	*  explain of number 2
	*  1. one byte for the end '\n'
	*  2. one byte for the symbol '+' or '-'
	**/
	*pointToResult = (char*)malloc((number_length + 2) * sizeof(char));
	if(NULL == *pointToResult)
	{
		return BN_NO_MEMORY;
	}
	char *tmp = *pointToResult + number_length + 2 - 1;
	*tmp = '\0';		
	
	/**
	*  calculate
	*  from tail to head
	**/
	char *number_index = number + number_length - 1;
	char *result_index = *pointToResult + number_length + 2 - 2;
	char suber = '1';
	int flow = 0;
	long flag = 0;
	while(number_index >= number)
	{
		if(0 == flag || 1 == flow)
		{
			flow = BN_charactorSub(*number_index, suber, flow, result_index);
			assert( false != isdigit(*result_index));
			if(0 == flag)
			{
				suber--;
			}
			flag++;
		}
		else
		{
			*result_index = *number_index;	
		}
			
		number_index--;
		result_index--;
	}//end of while
	*result_index = (char)(flow + '0');
	
	return BN_SUCCESS;
}


/*******************************************************************************
*	Func Name    : BN_compare_in
*	Date created : 2013-11-29 
*	Author		 : zhulinfeng
*	Description  : Multiply two numbers
*	----------------------------------------------------------------------------
*   Input		 : char *mulee		
*				 : char *muler		 
*   ----------------------------------------------------------------------------
*   Output		 : char **pointToResult	//store the multiply result
*   ----------------------------------------------------------------------------
*   Return		 : int					//error code
*   ----------------------------------------------------------------------------
*	Caution		 : 
*******************************************************************************/
static int BN_mul_in(IN char *mulee, IN char *muler, OUT char **pointToResult)
{
	long mulee_length;
	long muler_length;
	
	/**
	*  do some necessary check
	*  check if the input string is NULL
	*  check if the input string is out of size
	*  check if the input string is empty
	*  chekc if the input string has illegal charactor
	**/
	assert(NULL != mulee);
	assert(NULL != muler);
	assert(NULL != pointToResult);
	mulee_length = strlen(mulee);
	muler_length = strlen(muler);
	assert(mulee_length > 0 && mulee_length <= BN_MAX_SIZE);
	assert(muler_length > 0 && muler_length <= BN_MAX_SIZE);
	
	/***ask for memory***/
	char *sum;
	char *temp_result;
	long temp_result_length = mulee_length + muler_length + 1;
	sum = (char*)malloc( 2 * sizeof(char) );
	temp_result = (char*)malloc( (temp_result_length + 1) * sizeof(char) );
	if(NULL == sum || NULL == temp_result)
	{
		return BN_NO_MEMORY;
	}
	*(temp_result + temp_result_length) = '\0';
	*sum = '0';
	*(sum+1) = '\0';
	
	/***calclate***/
	char *muler_index = muler + muler_length - 1;
	char *zeroCount = temp_result + temp_result_length - 1;
	while(muler_index >= muler)
	{
		char *temp_result_index = temp_result + temp_result_length - 1;
		char *mulee_index = mulee + mulee_length - 1;
		while(temp_result_index > zeroCount)
		{
			*temp_result_index = '0';
			temp_result_index--;
		}
		zeroCount--;
		
		int flow = 0;
		while(mulee_index >= mulee)
		{
			flow = BN_charactorMul(*mulee_index, *muler_index, flow, temp_result_index);
			mulee_index--;
			temp_result_index--;
		}
		*temp_result_index = flow  + '0';
		temp_result_index--;
		while(temp_result_index >= temp_result)
		{
			*temp_result_index = '0';
			temp_result_index--;
		}
		
		char *sum_temp;
		int situation = BN_add_in(sum, temp_result, &sum_temp);
		if(BN_SUCCESS != situation)
		{
			return situation;
		}
		free(sum);
		sum = sum_temp;
		
		muler_index--;		
	}
	
	/***short cut***/
	char *sum_head = sum;
	long actual_length = 0;
	char *sum_index;
	while( '0' == *sum_head)
	{
		sum_head++;
	}
	sum_index = sum_head;
	while('\0' != *sum_index)
	{
		actual_length++;
		sum_index++;
	}
	
	sum_index = sum_head;
	*pointToResult = (char*)malloc( (actual_length + 2) * sizeof(char) );
	if(NULL == *pointToResult)
	{
		return BN_NO_MEMORY;
	}
	char *pointToResult_index = *pointToResult;
	*pointToResult_index = '0';
	pointToResult_index++;
	while('\0' != *sum_index)
	{
		*pointToResult_index = *sum_index;
		pointToResult_index++;
		sum_index++;
	} 
	*pointToResult_index = '\0';
	
	free(sum);
	
	return BN_SUCCESS;
}


/*******************************************************************************
*	Func Name    : BN_div_in
*	Date created : 2013-11-29 
*	Author		 : zhulinfeng
*	Description  : Divide two numbers
*	----------------------------------------------------------------------------
*   Input		 : char *divee		
*				 : char *diver		 
*   ----------------------------------------------------------------------------
*   Output		 : char **pointToResult	//store the divide result
*				   char **pointToRem	//store the remain number
*   ----------------------------------------------------------------------------
*   Return		 : int					//error code
*   ----------------------------------------------------------------------------
*	Caution		 : 
*******************************************************************************/
static int BN_div_in(IN char *divee, IN char *diver, OUT char **pointToResult, OUT char **pointToRem)
{
	int situation;
	long divee_length;
	long diver_length;
	
	/**
	*  do some necessary check
	*  check if the input string is NULL
	*  check if the input string is out of size
	*  check if the input string is empty
	*  chekc if the input string has illegal charactor
	**/
	assert(NULL != divee);
	assert(NULL != diver);
	assert(NULL != pointToResult);
	assert(NULL != pointToRem);
	divee_length = strlen(divee);
	diver_length = strlen(diver);
	assert(divee_length > 0 && divee_length <= BN_MAX_SIZE);
	assert(diver_length > 0 && diver_length <= BN_MAX_SIZE);	
	
	/***check diver equals zero or not***/
	int diver_zero;
	situation = BN_compare_in(diver, "000", &diver_zero);
	if(BN_SUCCESS != situation)
	{
		return situation;
	}
	assert(diver_zero >= 0);
	if( 0 == diver_zero)
	{
		return BN_ZERO_DIVER;
	}
	
	/***check which is bigger, divee or diver***/
	int which_bigger;
	situation = BN_compare_in(divee, diver, &which_bigger);
	if(BN_SUCCESS != situation)
	{
		return situation;
	}
	if(which_bigger < 0)
	{
		*pointToRem = (char*)malloc( (divee_length + 2) * sizeof(char));
		*pointToResult = (char*)malloc( 3 * sizeof(char) );
		if(NULL == *pointToRem || NULL == *pointToResult)
		{
			return BN_NO_MEMORY;
		}
		char *rem_index = *pointToRem;
		*rem_index = '0';
		rem_index++;
		char *divee_index = divee;
		while(*divee_index != '\0')
		{
			*rem_index = *divee_index;
			rem_index++;
			divee_index++;
		}
		*rem_index = '\0';
		
		**pointToResult = '0';
		*(*pointToResult+1) = '0';
		*(*pointToResult+2) = '\0';
		
		return BN_SUCCESS;
	}
	else if(0 == which_bigger)
	{
		*pointToResult = (char*)malloc(3 * sizeof(char));
		*pointToRem = (char*)malloc( 3 * sizeof(char) );
		if(NULL == *pointToResult || NULL == *pointToRem)
		{
			return BN_NO_MEMORY;
		}
		**pointToResult = '0';
		*(*pointToResult+1) = '1';
		*(*pointToResult+2) = '\0';
		
		**pointToRem = '0';
		*(*pointToRem+1) = '0';
		*(*pointToRem+2) = '\0';
		
		return BN_SUCCESS;
	}		
	
	/***ask for memory***/
	*pointToRem = (char*)malloc( (divee_length + 2) * sizeof(char));
	*pointToResult = (char*)malloc( (divee_length + 2) * sizeof(char) );
	if(NULL == *pointToRem || NULL == *pointToResult)
	{
		return BN_NO_MEMORY;
	}
	**pointToRem = '0';
	**pointToResult = '0';
	long tmp_rem_index = 0;
	while( *(divee+tmp_rem_index) != '\0')
	{
		*(*pointToRem + tmp_rem_index + 1) = *(divee+tmp_rem_index);
		tmp_rem_index++;
	}
	*(*pointToRem + tmp_rem_index + 1) = '\0';
	
	
	/***calculate***/
	char *rem_index = *pointToRem + 2;
	char *result_index = *pointToResult + 1;
	int flag = 1;
	while(flag > 0)
	{
		if('\0' == *rem_index)
		{
			flag = 0;
		}
		char char_n = *rem_index;
		*rem_index = '\0';
		*result_index = '0';
		
		int cmp_result;
		BN_compare_in(*pointToRem, diver, &cmp_result);
		while(cmp_result >= 0)
		{
			char *rem_tail_index = rem_index - 1;
			char *diver_tail_index = diver + diver_length - 1;
			int flow = 0;
			char c_subee;
			char c_suber;
			while(rem_tail_index >= *pointToRem)
			{
				c_subee = *rem_tail_index;
				if(diver_tail_index >= diver)
				{
					c_suber = *diver_tail_index;
				}
				else
				{
					c_suber = '0';
				}
				flow = BN_charactorSub(c_subee, c_suber, flow, rem_tail_index);
				rem_tail_index--;
				diver_tail_index--;
			}
			
			BN_compare_in(*pointToRem, diver, &cmp_result);
			(*result_index)++;
		}
		
		*rem_index = char_n;
		rem_index++;
		result_index++;
	}//end of while
	
	*result_index = '\0';
	
	return BN_SUCCESS;
}

/*******************************************************************************
*	Func Name    : BN_compare_in
*	Date created : 2013-11-29 
*	Author		 : zhulinfeng
*	Description  : Compare two numbers
*	----------------------------------------------------------------------------
*   Input		 : char *numStr1		
*				 : char *numStr2		 
*   ----------------------------------------------------------------------------
*   Output		 : char *result			//store the compare result
				   >0  numStr1 > numStr2
				   =0  numStr1 = numStr2
				   <0  numStr1 < numStr2
*   ----------------------------------------------------------------------------
*   Return		 : int					//error code
*   ----------------------------------------------------------------------------
*	Caution		 : 
*******************************************************************************/
static int BN_compare_in(IN char *numStr1, IN char *numStr2, OUT int *result)
{
	int answer;
	long length_numStr1;
	long length_numStr2;
	
	/**
	*  do some necessary check
	*  check if the input string is NULL
	*  check if the input string is out of size
	*  check if the input string is empty
	*  chekc if the input string has illegal charactor
	**/
	assert(NULL != numStr1);
	assert(NULL != numStr2);
	assert(NULL != result);
	length_numStr1 = strlen(numStr1);
	length_numStr2 = strlen(numStr2);
	assert(length_numStr1 > 0 && length_numStr1 <= BN_MAX_SIZE);
	assert(length_numStr2 > 0 && length_numStr2 <= BN_MAX_SIZE);
	
	
	/**
	*  copy
	*  copy the two number strings into two bufs 
	**/
	char *str1_head = numStr1;
	char *str2_head = numStr2;
	long length_str1 = 0;
	long length_str2 = 0;
	while( '0' == *str1_head )
	{
		str1_head++;
	}
	while( '0' == *str2_head )
	{
		str2_head++;
	}
	char *str1_tmp = str1_head;
	char *str2_tmp = str2_head;
	while( '\0' != *str1_tmp )
	{
		length_str1++;
		str1_tmp++;
	}
	while( '\0' != *str2_tmp )
	{
		length_str2++;
		str2_tmp++;
	}
	char *str1 = (char*)malloc( (length_str1 + 1) * sizeof(char) );
	char *str2 = (char*)malloc( (length_str2 + 1) * sizeof(char) );
	str1_tmp = str1_head;
	str2_tmp = str2_head;
	long index = 0;
	while( '\0' != *str1_tmp )
	{
		*(str1 + index) = *str1_tmp;
		index++;
		str1_tmp++;
	}
	*(str1 + index) = '\0';
	index = 0;
	while( '\0' != *str2_tmp)
	{
		*(str2 + index) = *str2_tmp;
		index++;
		str2_tmp++;
	}
	*(str2 + index) = '\0';
	
	
	/**
	*  compare which input number string is bigger
	*  if numStr1 is bigger, then answer > 0
	*  if numStr2 is bigger, then answer < 0
	*  if they are the same, then answer = 0
	**/
	if(length_str1 > length_str2)
	{
		answer = 1;	
	}
	else if( length_str1 < length_str2)
	{
		answer = -1;
	}
	else
	{
		int compare = strcmp(str1, str2);
		if(compare > 0)
		{
			answer = 1;
		}
		else if(compare < 0)
		{
			answer = -1;
		}
		else
		{
			answer = 0;
		}
	}		
	*result = answer;
	
	/***free memory since we won't use it again***/
	free(str1);
	free(str2);
	
	return BN_SUCCESS;
}


/*******************************************************************************
*	Func Name    : BN_hasIllegal
*	Date created : 2013-11-29 
*	Author		 : zhulinfeng
*	Description  : Check if there is illegal charactor in input string
*				   Legal charactors: '0' ~ '9'	
*	----------------------------------------------------------------------------
*   Input		 : char *strNumber			 
*   ----------------------------------------------------------------------------
*   Return		 : bool					
*				   0  no illegal charactor
*				   1  has illegal charator
*   ----------------------------------------------------------------------------
*	Caution		 : 
*******************************************************************************/
static bool BN_hasIllegal(IN char *strNumber)
{
	/***check para***/
	assert( NULL != strNumber);
	assert( strlen(strNumber) > 0 );
	
	/***check illegal***/
	bool answer = 0;				
	char *index = strNumber;
	while( '\0' != *index)
	{
		if( false == isdigit(*index) )
		{
			answer = 1;
			break;
		}
		else
		{
			index ++;
		}
	}//end of while
	
	return answer;
}


/*******************************************************************************
*	Func Name    : BN_charactorAdd
*	Date created : 2013-11-29 
*	Author		 : zhulinfeng
*	Description  : Add two charactors
*	----------------------------------------------------------------------------
*   Input		 : char addee			//should between '0' and '9'
*				 : char adder			//should between '0' and '9'
*				 : int carry			//should betwenn 0 and 1		 
*   ----------------------------------------------------------------------------
*   Output		 : char *result			//store the add result
*   ----------------------------------------------------------------------------
*   Return		 : int					//overflow, 0 or 1
*   ----------------------------------------------------------------------------
*	Caution		 : 
*******************************************************************************/
static int BN_charactorAdd(IN char addee, IN char adder, IN int carry, OUT char *result)
{
	int carry_in;
	/***check para***/
	assert( false != isdigit(addee) );
	assert( false != isdigit(adder) );
	assert( 0 == carry || 1 == carry);
	assert( NULL != result);
	
	/***add***/
	int answer = addee%(int)'0' + adder%(int)'0' + carry ;
	
	/***check overflow***/;
	if(answer >= 10)
	{
		carry_in =  1;
	}else
	{
		carry_in = 0;
	}
	
	*result = (char)((answer % 10) + '0' );
	
	return carry_in;
}


/*******************************************************************************
*	Func Name    : BN_charactorSub
*	Date created : 2013-11-29 
*	Author		 : zhulinfeng
*	Description  : Subtract two charactors
*	----------------------------------------------------------------------------
*   Input		 : char subee			//should between '0' and '9'
*				 : char suber			//should between '0' and '9'
*				 : int carry			//should betwenn 0 and 1		 
*   ----------------------------------------------------------------------------
*   Output		 : char *result			//store the subtract result
*   ----------------------------------------------------------------------------
*   Return		 : int					//overflow, 0 or 1
*   ----------------------------------------------------------------------------
*	Caution		 : 
*******************************************************************************/
static int BN_charactorSub(IN char subee, IN char suber, IN int carry, OUT char *result)
{
	int carry_in = 0;

	/***check para***/
	assert( false != isdigit(subee) );
	assert( false != isdigit(suber) );
	assert( 0 == carry || 1 == carry);
	assert( NULL != result);
	
	/***sub***/
	int tmp = subee%(int)'0' - suber%(int)'0' - carry;
	if(tmp < 0)
	{
		carry_in = 1;
		tmp += 10;
	}
	else
	{
		carry_in = 0;
	}
	*result = (char)(tmp + '0');
	
	return carry_in;
}


/*******************************************************************************
*	Func Name    : BN_charactorMUL
*	Date created : 2013-11-29 
*	Author		 : zhulinfeng
*	Description  : Multiply two charactors
*	----------------------------------------------------------------------------
*   Input		 : char mulee			//should between '0' and '9'
*				 : char muler			//should between '0' and '9'
*				 : int carry			//should betwenn 0 and 8		 
*   ----------------------------------------------------------------------------
*   Output		 : char *result			//store the multiply result
*   ----------------------------------------------------------------------------
*   Return		 : int					//overflow
*   ----------------------------------------------------------------------------
*	Caution		 : 
*******************************************************************************/
static int BN_charactorMul(IN char mulee, IN char muler, IN int carry, OUT char *result)
{
	int carry_in = 0;
	
	/***check para***/
	assert( false != isdigit(mulee) );
	assert( false != isdigit(muler) );
	assert(carry >= 0 && carry <= 8);
	assert( NULL != result);
	
	/***mul***/
	int tmp = (mulee%(int)'0') * (muler%(int)'0') + carry;
	if(tmp >= 10)
	{
		carry_in = tmp / 10;
		tmp = tmp % 10;
	}
	else
	{
		carry_in = 0;
	}
	*result = (char)( tmp + '0');
	
	return carry_in;
}



