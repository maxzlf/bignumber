
/**
* define some symbols
* used in functions
**/
#ifdef NULL
#else
#define NULL 0
#endif

#ifdef IN
#else
#define IN
#endif

#ifdef OUT
#else
#define OUT
#endif

#ifdef INOUT
#else
#define INOUT
#endif

#ifdef bool
#else 
#define bool int
#endif

#ifdef false
#else
#define false 0
#endif


/**
*  define some values that functions will return
*  each value indicates situations of functions
**/
/***define the max size of a number string***/
#ifdef BN_MAX_SIZE 
#else
#define BN_MAX_SIZE (long)(1024*1024*32)
#endif

/***the functions works well***/
#ifdef BN_SUCCESS
#else
#define BN_SUCCESS (0l)
#endif

/***some illegal CHARACTORs found in number string***/
#ifdef BN_ILLEGAL_CHARACTOR
#else
#define BN_ILLEGAL_CHARACTOR (1l)
#endif


/***the number string ended without '\n'***/
#ifdef BN_ILLEGAL_END
#else
#define BN_ILLEGAL_END (2l)
#endif


/***the number string is empty***/
#ifdef BN_INPUT_EMPTY
#else
#define BN_INPUT_EMPTY (3l)
#endif


/***the number string is out of size***/
#ifdef BN_OUTOF_SIZE
#else
#define BN_OUTOF_SIZE (4l)
#endif

/***invalid param***/
#ifdef BN_PARAM_INVALID
#else
#define BN_PARAM_INVALID (5l)
#endif

/***diver is zero***/
#ifdef BN_ZERO_DIVER
#else
#define BN_ZERO_DIVER (6l)
#endif

/***out of MEMORY***/
#ifdef BN_NO_MEMORY
#else
#define BN_NO_MEMORY (101l)
#endif
