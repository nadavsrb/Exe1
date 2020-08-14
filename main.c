#include <stdio.h>
#include "Matrix.c"

void print_matrix(PMatrix matrix);

int main() {
    //allocating memory to the PMatrix pointer.
    PMatrix *matrix = (PMatrix*) malloc(sizeof(PMatrix));
    if (matrix == NULL) {
        printf("oh no matrix == NULL\n");
        return 1;
    }

    matrix_create(matrix, 5, 5);

    print_matrix((*matrix));
    return 0;
}

void print_matrix(PMatrix matrix){
    for (int i = 0; i < (matrix->numRows); i++){

        for (int j = 0; j < (matrix->numCols); j++){
            printf("%f|", (matrix->data)[i][j]);
        }
        
         printf("\n");
    }
} 

