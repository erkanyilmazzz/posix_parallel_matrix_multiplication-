/**
 *  Author :Erkan Yılmaz 
 *  NO:161044044
 *  Date:19/04/2020
*/
#include<stdio.h>
#include<stdlib.h>
#include"arg.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<signal.h>
#include"matrix.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<math.h>

int *part1=NULL;
int *part2=NULL;
int *part3=NULL;
int *part4=NULL;
int p2=0,p3=0,p4=0,p5=0;

void handler(int sig){
    if(part1!=NULL){
        free(part1);
        part1=NULL;
    }
    if(part2!=NULL){
        free(part2);
        part2=NULL;
    }
    if(part3!=NULL){
        free(part3);
        part3=NULL;
    }
    if(part4!=NULL){
        free(part4);
        part4=NULL;
    }
    kill(1,p2);
    kill(1,p3);
    kill(1,p4);
    kill(1,p5);
    kill(1,getpid());
    exit(-1);
}

int main(int argc,char ** argv){
    //unit_test_calculate_i_j();
    //unit_test_print_matrix();
/////////////////////////////////////////////////////////////
/**handle signal*/   
    signal(2,handler);
/////////////////////////////////////////////////////////////
/**argument operation*/
    char *inputPath1;
    char *inputPath2;
    int  n;
    /*checking and setting arguments*/
    int errno=argHandler(argc,argv,&inputPath1,&inputPath2,&n);    
    if(USAGE_ERROR==errno){
        printf("usage:::: ./programA -i1 <<inputPath1>> -i2 <<inputPath2>> -n <<n>>\n");
        exit(EXIT_FAILURE);
    }else if(ARG_NOT_IN_RANGE_ERROR==errno){
        printf("n has to be positive \n");////-----------------------------------------    
        exit(EXIT_FAILURE);
    }else if(INVALID_PATH_ERROR==errno){
        printf("invalid path\n"); //   
        exit(EXIT_FAILURE);
    }
    printf("intput:%s \noutput:%s \nn:%d\n",inputPath1,inputPath2,n);
/////////////////////////////////////////////////////////////
/**opening files*/
int input_1;
int input_2;
input_1=open(inputPath1,O_RDWR|O_SYNC,0666);
input_2=open(inputPath2,O_RDWR|O_SYNC,0666);;
if(input_1<0){//O_RDWR
    perror("file");
    exit(-1);
}
if(input_2<0){
    perror("file");
    exit(-1);
}
////////////////////////////////////////////////////////////
/*alocate matrices*/
int row=pow(2,n);
int col=pow(2,n);
int** mat1 = (int**)malloc(row * sizeof(int*));
for (int index=0;index<row;++index){
    mat1[index] = (int*)malloc(col * sizeof(int));
}
int** mat2 = (int**)malloc(row * sizeof(int*));
for (int index=0;index<row;++index){
    mat2[index] = (int*)malloc(col * sizeof(int));
}
int** res = (int**)malloc(row * sizeof(int*));
for (int index=0;index<row;++index){
    res[index] = (int*)malloc(col * sizeof(int));
}
/////////////////////////////////////////////////////////////
/**read and writing in to matrices*/
char reading_buf;
int k=0;
int i=0,j=0;
while(k<row*col && (read(input_1,&reading_buf,1))==1){
    if(j!=row){
        mat1[j][i]=(int )reading_buf;
        ++j;
    }if(j==row){
        j=0;
        i++;
    }   
++k;    
}
k=0;
i=0,j=0;
while(k<row*col && (read(input_2,&reading_buf,1))==1){
    if(j!=row){
        mat2[j][i]=(int )reading_buf;
        ++j;
    }if(j==row){
        j=0;
        i++;
    }   
++k;    
}
/////////////////////////////////////////////////////////////
/**printing matrices*/
print_matrix(mat1,row);
printf("---------------------------------------------\n");
print_matrix(mat2,row);
/**genarete pipe fds and pids*/
    int pipe1[2];
    int pipe2[2];
    int pipe3[2];
    int pipe4[2];
////////////////////////////////////////////////////
/**create pipe1 and rename pipe start and end*/
    if(pipe(pipe1)<0){
        perror("pipe");
        exit(-1);
    }
    int pipe_read=pipe1[0];
    int pipe_write=pipe1[1];
////////////////////////////////////////////////////    
/**create pipe2 and rename pipe start and end*/
    if(pipe(pipe2)<0){
        perror("pipe");
        exit(-1);
    }
    int pipe_read_2=pipe2[0];
    int pipe_write_2=pipe2[1];
////////////////////////////////////////////////////
/**create pipe3 and rename pipe start and end*/
    if(pipe(pipe3)<0){
        perror("pipe");
        exit(-1);
    }
    int pipe_read_3=pipe3[0];
    int pipe_write_3=pipe3[1];
/////////////////////////////////////////////////////
/**create pipe4 and rename pipe start and end*/
    if(pipe(pipe4)<0){
        perror("pipe");
        exit(-1);
    }
    int pipe_read_4=pipe4[0];
    int pipe_write_4=pipe4[1];
/////////////////////////////////////////////////////
////////////////////////////////////////////////////
/**fork process*/
    p2=fork();
    if(p2<0){
        perror("fork");
        exit(-1);
    }
    if(p2==0){    signal(2,handler);
        /**child process*/
        char str[20];
        close(pipe_read);
        if(n>=2){
        int *part1=malloc(sizeof(int)*row*pow(2,n-2));
        int counter=0;
            for(i=0;i<pow(2,n-2);++i){
                for(j=0;j<row;++j){
                    part1[counter]=calculate_i_j_element(i,j,mat1,mat2,row);
                    counter++;
                }
            }
        write(pipe_write,part1,sizeof(int)*row*pow(2,n-2));
        free(part1);//
        close(pipe_write);
        }
        if(n==1){
        int *part1=malloc(sizeof(int));
        int counter=0;
            part1[0]=calculate_i_j_element(0,0,mat1,mat2,2);
            write(pipe_write,part1,sizeof(int));
            free(part1);//
            part1=NULL;//
        close(pipe_write);
        }
        
        exit(0);
    }
//////////////////////////////////////////////////////
/**fork process*/
    p3=fork();
    if(p3<0){
        perror("fork");
        exit(-1);
    }
    if(p3==0){    signal(2,handler);
        /**child process*/
        int *part2=malloc(sizeof(int)*row*pow(2,n-2));
        int counter=0;
        if(n>=2){
            for(i=pow(2,n-2);i<2*pow(2,n-2);++i){
                for(j=0;j<row;++j){
                    part2[counter]=calculate_i_j_element(i,j,mat1,mat2,row);
                    counter++;
                }
            }
        }
        write(pipe_write_2,part2,sizeof(int)*row*pow(2,n-2));
        free(part2);//
        part2=NULL;
        close(pipe_write_2);
        exit(0);
    }    
////////////////////////////////////////////////////////
/**fork process*/
    p4=fork();
    if(p4<0){
        perror("fork");
        exit(-1);
    }
    if(p4==0){    signal(2,handler);
        /**child process*/
        int *part3=malloc(sizeof(int)*row*pow(2,n-2));
        int counter=0;
        if(n>=2){
            for(i=2*pow(2,n-2);i<3*pow(2,n-2);++i){
                for(j=0;j<row;++j){
                    part3[counter]=calculate_i_j_element(i,j,mat1,mat2,row);
                    counter++;
                }
            }
        }
        write(pipe_write_3,part3,sizeof(int)*row*pow(2,n-2));
        free(part3);//
        part3=NULL;
        close(pipe_write_3);
        exit(0);
    }        
////////////////////////////////////////////////////////
/**fork process*/
    p5=fork();
    if(p5<0){
        perror("fork");
        exit(-1);
    }
    if(p5==0){    signal(2,handler);
        /**child process*/
        int *part4=malloc(sizeof(int)*row*pow(2,n-2));
        int counter=0;
        if(n>=2){
            for(i=3*pow(2,n-2);i<4*pow(2,n-2);++i){
                for(j=0;j<row;++j){
                    part4[counter]=calculate_i_j_element(i,j,mat1,mat2,row);
                    counter++;
                }
            }
        }
        write(pipe_write_4,part4,sizeof(int)*row*pow(2,n-2));
        free(part4);//
        part4=NULL;
        close(pipe_write_4);
        exit(0);
    }    
////////////////////////////////////////////////////////
/*parent process*/        
////////////////////////////////////////////////////////
///////////////////////////////////////////////////////
/**close wriding end in parent*/
        close(pipe_write);
        close(pipe_write_2);
        close(pipe_write_3);
        close(pipe_write_4);
///////////////////////////////////////////////////////
//////////////////////////////////////////////////////
        int counter=0;            
          int read_byte=0;
        if(n>=2){
            int * part1=malloc(sizeof(int )*row*pow(2,n-2));
            read_byte=(int)read(pipe_read,part1,sizeof(int )*row*pow(2,n-2));
            if(read_byte!=sizeof(int )*row*pow(2,n-2)){
                perror("read");
                exit(-1);
            }
            //printf("read returns %d\n",(int)read(pipe_read,part1,sizeof(int )*row*pow(2,n-2)));;
            for(i=0;i<pow(2,n-2);i++){
                for(j=0;j<row;++j){
                    res[i][j]=part1[counter];
                    counter++;
                }
            }
            free(part1);//
            part1=NULL;
        }if(n==1){
            int *part1=malloc(sizeof(int));
            read(pipe_read,part1,1);
            res[0][0]=*part1;
            free(part1);//
            part1=NULL;
        }

        close(pipe_read);
//////////////////////////////////////////////////
        int * part2=malloc(sizeof(int )*row*pow(2,n-2));
        read_byte=0;
        read_byte=(int)read(pipe_read_2,part2,sizeof(int )*row*pow(2,n-2));
        if(read_byte!=sizeof(int )*row*pow(2,n-2)){
            perror("read");
            exit(-1);
        }
        //printf("read returns %d\n",(int)read(pipe_read_2,part2,sizeof(int )*row*pow(2,n-2)));;
        counter=0;
        for(i=pow(2,n-2);i<2*pow(2,n-2);i++){
            for(j=0;j<row;++j){
                res[i][j]=part2[counter];
                counter++;
            }
        }
        free(part2);//
        part2=NULL;
        close(pipe_read_2);
/////////////////////////////////////////////////    
        int * part3=malloc(sizeof(int )*row*pow(2,n-2));
        read_byte=0;
        read_byte=(int)read(pipe_read_3,part3,sizeof(int )*row*pow(2,n-2));
        if(read_byte!=sizeof(int )*row*pow(2,n-2)){
            perror("read");
            exit(-1);
        }
        //printf("read returns %d\n",(int)read(pipe_read_3,part3,sizeof(int )*row*pow(2,n-2)));;
        counter=0;
        for(i=2*pow(2,n-2);i<3*pow(2,n-2);i++){
            for(j=0;j<row;++j){
                res[i][j]=part3[counter];
                counter++;
            }
        }
        free(part3);//
        part3=NULL;
        close(pipe_read_3);
////////////////////////////////////////////////////
        int * part4=malloc(sizeof(int )*row*pow(2,n-2));
        read_byte=0;
        read_byte=(int)read(pipe_read_4,part4,sizeof(int )*row*pow(2,n-2));
        if(read_byte!=sizeof(int )*row*pow(2,n-2)){
            perror("read");
            exit(-1);
        }
        //printf("read returns %d\n",(int)read(pipe_read_4,part4,sizeof(int )*row*pow(2,n-2)));;
        counter=0;
        for(i=3*pow(2,n-2);i<4*pow(2,n-2);i++){
            for(j=0;j<row;++j){
                res[i][j]=part4[counter];
                counter++;
            }
        }
        free(part4);//        
        part4=NULL;
        close(pipe_read_4);
         if(n==1){
            for(i=0;i<=n;++i){
                for(j=0;j<=n;++j){
                    res[i][j]=calculate_i_j_element(i,j,mat1,mat2,row);
                }
            }
        }


////////////////////////////////////////////////////
    printf("program is done \n");
    printf("-----------------------------------------------------\n");
    print_matrix(res,row);
///////////////////////////////////////////////////////////
/**free matrices*/
for (int index=0;index<row;++index){
    free(mat1[index]) ;
}
free(mat1);
for (int index=0;index<row;++index){
    free(mat2[index]) ;
}
free(mat2);

for (int index=0;index<row;++index){
    free(res[index]) ;
}
free(res);
//////////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/**free */    
    close(input_1);
    close(input_2);

    free(inputPath1);
    inputPath1=NULL;
    free(inputPath2);
    inputPath2=NULL;
    return 0;
}