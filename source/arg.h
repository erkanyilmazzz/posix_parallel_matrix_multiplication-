#ifndef _ARGH
#define _ARGH

#define USAGE_ERROR -1
#define ARG_NOT_IN_RANGE_ERROR -2
#define INVALID_PATH_ERROR -3


/**
 * function that check  parameters are valid and set  parameters
 * if every thing is okey return EXIT_SUCCESS
 * errors:
 * if number of paramaters are wrong return USAGE_ERROR
 * if time is not in range return ARG_NOT_IN_RANGE_ERROR
 * if a path is not a valid path return INVALID_PATH_ERROR
 * if malloc can not allocate memmory it exit EXIT_FALIURE
 * 
*/
int argHandler(int __argc,char ** __argv,char ** _inputPath, char ** _ouputPath,int * _time);



#endif