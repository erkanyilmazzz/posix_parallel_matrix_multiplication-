/**
 *  Author :Erkan Yılmaz 
 *  NO:161044044
 *  Date:19/04/2020
*/
#include"arg.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<ctype.h>
#include<getopt.h>


int argHandler(int __argc,char ** __argv,char ** _inputPath, char ** _outputPath,int * _time){
    int option;
    int iflag=0,oflag=0,tflag=0;
    int outputlen;
    int inputlen;
    
    while((option=getopt(__argc,__argv,"i1: i2: n:"))!=-1){
        //printf("option is %d\n",option);
        switch (option)
        {
        case 105:
            break;
        case 49:
            ++iflag;
            inputlen=strlen(optarg);
            if(NULL==(*_inputPath=malloc(sizeof(char)*inputlen))){
               perror("malloc");
            exit(-1);
            }    
            strcpy(*_inputPath,optarg);
            //printf("i:::::%s\n",*_inputPath);
            break;
        case 50:
          ++oflag;
            outputlen=strlen(optarg);
            if(NULL==(*_outputPath=malloc(sizeof(char)*outputlen))){
                perror("malloc");
                exit(-1);
            }
            strcpy(*_outputPath,optarg);
            //printf("i:::::%s\n",*_outputPath);
            break;
        break;
        
        case 110:
            ++tflag;
            *_time=atoi(optarg);
            if(*_time<=0){
                return ARG_NOT_IN_RANGE_ERROR;
            }
        //printf("t:::::%d\n",*_time);
        break;
           
        default:
            break;
        }
     
    }
        
   

   printf("i1 %d i2 %d n %d\n",iflag,oflag,tflag);
      if(iflag==0|oflag==0|tflag==0){
        return USAGE_ERROR;
      }



    return 0;
}

