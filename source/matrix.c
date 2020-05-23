/**
 *  Author :Erkan Yılmaz 
 *  NO:161044044
 *  Date:19/04/2020
*/
#include<stdio.h>
#include<stdlib.h>

int calculate_i_j_element(int i ,int j,int **matrix1,int **matrix2,int degree_of_matrices){
//////////////////////////////////////////////////////////////////////////////////////////    
    /**argumant checking*/
    if(i>=degree_of_matrices|j>=degree_of_matrices){
        perror("outof bound ");
        exit(-1);
    }
//////////////////////////////////////////////////////////////////////////////////////////   
    /**mutiplying*/
    int sum=0;
    int k;
    for(k=0;k<degree_of_matrices;++k){
        sum+=(matrix1[i][k]*matrix2[k][j]);
    }
    return  sum;   
}

void unit_test_calculate_i_j(){
    int row=2;
    int col=2;

    int** mat = (int**)malloc(row * sizeof(int*));
    for (int index=0;index<row;++index){
        mat[index] = (int*)malloc(col * sizeof(int));
    }

    int** mat2 = (int**)malloc(row * sizeof(int*));
    for (int index=0;index<row;++index){
        mat2[index] = (int*)malloc(col * sizeof(int));
    }


    mat[0][0]=1;
    mat[0][1]=2;
    mat[1][0]=3;
    mat[1][1]=4;
    
    printf("0,0 eleman :::%d\n",mat[0][0]);
    printf("0,1 eleman :::%d\n",mat[0][1]);
    printf("1,0 eleman :::%d\n",mat[1][0]);
    printf("1,1 eleman :::%d\n",mat[1][1]);
    
    mat2[0][0]=4;
    mat2[0][1]=3;
    mat2[1][0]=2;
    mat2[1][1]=1;
    
    printf("0,0 eleman :::%d\n",mat2[0][0]);
    printf("0,1 eleman :::%d\n",mat2[0][1]);
    printf("1,0 eleman :::%d\n",mat2[1][0]);
    printf("1,1 eleman :::%d\n",mat2[1][1]);
    

    printf("0,0 ıncı eleman ::::%d\n",calculate_i_j_element(0,0,mat,mat2,2));
    printf("0,1 ıncı eleman ::::%d\n",calculate_i_j_element(0,1,mat,mat2,2));
    printf("1,0 ıncı eleman ::::%d\n",calculate_i_j_element(1,0,mat,mat2,2));
    printf("1,1 ıncı eleman ::::%d\n\n\n\n",calculate_i_j_element(1,1,mat,mat2,2));
}


void print_matrix(int ** matrix,int degree_of_matrix){
    for(int i=0;i<degree_of_matrix;++i){
        for(int j=0;j<degree_of_matrix;++j){
            printf("%6d ",matrix[i][j]);
        }
        printf("\n");
    }

}

void unit_test_print_matrix(){
    int row=2;
    int col=2;

    int** mat = (int**)malloc(row * sizeof(int*));
    for (int index=0;index<row;++index){
        mat[index] = (int*)malloc(col * sizeof(int));
    }

    int** mat2 = (int**)malloc(row * sizeof(int*));
    for (int index=0;index<row;++index){
        mat2[index] = (int*)malloc(col * sizeof(int));
    }


    mat[0][0]=1;
    mat[0][1]=2;
    mat[1][0]=3;
    mat[1][1]=4;

    print_matrix(mat,2);
    

}