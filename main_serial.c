#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int** gen_matrix(int n, int m){    
    int** matrix = malloc(n*sizeof(int*));

    for(int i=0; i<n; i++){
        int* row = malloc(m*sizeof(int));        
        matrix[i] = row;       
    }
   
    return matrix;    
}

void random_fill_matrix(int** matrix, int n, int m){    
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){            
            int r = rand()%5+1;            
            matrix[i][j] = r;            
        }
    }     
}

void print_matrix(int** matrix, int n, int m){
    printf("\n");
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void multiply_matrices(int** result, int** matrix1, int**matrix2,int n, int m, int p){    
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            int suma = 0;
            for(int k=0; k<p; k++){
                suma += matrix1[i][k] * matrix2[k][j];
            }
            result[i][j] = suma;
        }
    }    
}


int main(int arcgc, char* argv[]){
    //SETUP
    srand(time(NULL));        
    
    //INPUT
    int n,m;    
    n = atoi(argv[1]);
    m = atoi(argv[2]);    
    // printf("Ingrese un número: ");    
    // scanf("%d", &n);
    // printf("Ingrese otro número: ");
    // scanf("%d", &m);    
    
    
    
    // GENERAR MATRICES
    int** matrix1 = gen_matrix(n, m);            
    random_fill_matrix(matrix1, n, m);
    //print_matrix(matrix1, n, m);
    int** matrix2 = gen_matrix(m, n);            
    random_fill_matrix(matrix2, m, n);
    //print_matrix(matrix2, m, n);

    // MULTIPLICACION      
    clock_t start, end;    
    int** result = gen_matrix(n, n);
        
    start = clock();
    multiply_matrices(result, matrix1, matrix2, n, n, m);
    end = clock();
    
    //print_matrix(result, n, n);
    double diff = (double) (end - start) / CLOCKS_PER_SEC;
    printf("diff: %fs \n", diff);

}