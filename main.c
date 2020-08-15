#include <stdio.h>
#include "Matrix.c"

void print_matrix(PMatrix matrix);

int main() {
    //creates matrix.
    PMatrix *matrix = (PMatrix*) malloc(sizeof(PMatrix));
    if (matrix == NULL) {
        printf("oh no matrix == NULL\n");
        return 1;
    }

    matrix_create(matrix, 5, 5);
    printf("Created matrix:\n");
    print_matrix(*matrix);

    //copy matrix
    PMatrix *copyMatrix = (PMatrix*) malloc(sizeof(PMatrix));
    if (matrix == NULL) {
        printf("oh no copyMatrix == NULL\n");
        return 1;
    }

    matrix_copy(copyMatrix, *matrix);
    printf("Copied matrix:\n");
    print_matrix(*copyMatrix);

    int cPHeight;
    int* copyMatrixHeight = &cPHeight;
    matrix_getHeight(*copyMatrix, copyMatrixHeight);
    printf("The height of the copied matrix: %d\n", cPHeight);

    //distroying the matrixes
    matrix_destroy(*matrix);
    matrix_destroy(*copyMatrix);
    printf("Matrixed distroyed\n");

    //free pointers
    free(matrix);
    free(copyMatrix);
    printf("PMatrixed distroyed\n");

    return 0;
}

/**
 * @brief get matrix and print it.
 * 
 * @param matrix the matrix to print.
 */
void print_matrix(PMatrix matrix){
    for (int i = 0; i < (matrix->numRows); i++){
        for (int j = 0; j < (matrix->numCols); j++){
            printf("%f|", (matrix->data)[i][j]);
        }
        
         printf("\n");
    }
} 

