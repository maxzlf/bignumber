
#include "common_file.h"

int BN_add_i(IN char *p_addee_c, IN char *p_adder_c, OUT char **pp_pointToResult_c);
int BN_sub_i(IN char *p_subee_c, IN char *p_suber_c, OUT char **pp_pointToResult_c);
int BN_increase_i(IN char *p_numStr_c, OUT char **pp_pointToResult_c);
int BN_decrease_i(IN char *p_numStr_c, OUT char **pp_pointToResult_c);
int BN_mul_i(IN char *p_mulee_c, IN char *p_muler_c, OUT char **pp_pointToResult_c);
int BN_div_i(IN char *p_divee_c, IN char *p_diver_c, OUT char **pp_pointToResult_c, OUT char **pp_pointToRem_c);
int BN_isZero_i(IN char *p_numStr_c, OUT int *p_result_i);
int BN_compare_i(IN char *p_numStr1_c, IN char *p_numStr2_c, OUT int *p_result_i);

