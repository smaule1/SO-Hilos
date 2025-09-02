#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

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

int n,m;
int** matrix1;
int** matrix2; 
int** result;

typedef struct {   
    int i;
    int j;    
} mult_args;



int multiply_matrices(int i, int j){        
    int suma = 0;
    for(int k=0; k<m; k++){
        suma += matrix1[i][k] * matrix2[k][j];
    }
    return suma;    
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
    struct timespec start, end;
    timespec_get(&start, TIME_UTC);  
    result = gen_matrix(n, n);
       
    
    FILE* fd = fopen("xd", "w");
    int* memory = mmap((void*)0, n*n*sizeof(int), PROT_WRITE | PROT_READ, MAP_SHARED, fd->_fileno, 0);        


    for (int i=0; i<n; i++){                
        for(int j=0; j<n; j++){                                    
            if(!fork()){                
                int cell = multiply_matrices(i, j);                
                memory[i*n+j] = cell;                
                exit(0);
            }              
        }                
    }    
    
    int a;
    int pid = wait(&a);
    int i = 0;
    while(pid!=-1 && i<n*n){
        int a = memory[0];
        pid = wait(&a);
        i++;
    }
    
   
    
    timespec_get(&end, TIME_UTC);    
        
    
    
    
    //print_matrix(result, n, n);
    double end_t = (double) end.tv_sec + (double)(end.tv_nsec) / 1000000000 ;
    double start_t = (double) start.tv_sec + (double)(start.tv_nsec) / 1000000000 ;
    double diff = end_t - start_t;
    printf("diff: %fs \n", diff);

}

