#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>


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

typedef struct {
    int i;
    int j;
} mult_args;

int n,m;
int** matrix1;
int** matrix2; 
int** result;

void* multiply_matrices(void* v_arg){    
    mult_args* arg = (mult_args*) v_arg;
       
    int suma = 0;
    for(int k=0; k<m; k++){
        suma += matrix1[arg->i][k] * matrix2[k][arg->j];
    }
    result[arg->i][arg->j] = suma;                
}


int main(int arcgc, char* argv[]){
    //SETUP
    srand(time(NULL));        
    
    //INPUT    
    n = atoi(argv[1]);
    m = atoi(argv[2]);    
    // printf("Ingrese un número: ");    
    // scanf("%d", &n);
    // printf("Ingrese otro número: ");
    // scanf("%d", &m);    
    
    
    
    // GENERAR MATRICES
    matrix1 = gen_matrix(n, m);            
    random_fill_matrix(matrix1, n, m);
    //print_matrix(matrix1, n, m);
    matrix2 = gen_matrix(m, n);            
    random_fill_matrix(matrix2, m, n);
    //print_matrix(matrix2, m, n);

    // MULTIPLICACION        
    result = gen_matrix(n, n);
    pthread_t* tid = malloc(n*n*sizeof(pthread_t));        

    struct timespec start, end;
    timespec_get(&start, TIME_UTC);    

    int k = 0;    
    for (int t = 0; t < n*n; t++){        
        mult_args* args = malloc(sizeof(mult_args));
        args->i = t/n;
        args->j = t%n;
        pthread_create(&tid[t], NULL, (void *) multiply_matrices, (void *) args);        
        
        if(t%500000==0 && t!=0){
            while(k<=t){
               pthread_join(tid[k], NULL);
               k++;               
            }                                 
        }        
    }

    while(k<n*n){
        pthread_join(tid[k], NULL);
        k++;
    }

    
    timespec_get(&end, TIME_UTC);    
        

    //print_matrix(result, n, n);
    double end_t = (double) end.tv_sec + (double)(end.tv_nsec) / 1000000000 ;
    double start_t = (double) start.tv_sec + (double)(start.tv_nsec) / 1000000000 ;
    double diff = end_t - start_t;
    printf("diff: %fs \n", diff);

}