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

    matrix_create(matrix, 4, 5);
    printf("Created matrix:\n");
    print_matrix(*matrix);

    //copy matrix
    PMatrix *copyMatrix = (PMatrix*) malloc(sizeof(PMatrix));
    if (copyMatrix == NULL) {
        printf("oh no copyMatrix == NULL\n");
        return 1;
    }

    matrix_copy(copyMatrix, *matrix);
    printf("Copied matrix:\n");
    print_matrix(*copyMatrix);

    //the height of the copied matrix
    int cPHeight;
    int* copyMatrixHeight = &cPHeight;
    matrix_getHeight(*copyMatrix, copyMatrixHeight);
    printf("The height of the copied matrix: %d\n", cPHeight);

    //the width of the copied matrix
    int cPWidth;
    int* copyMatrixWidtht = &cPWidth;
    matrix_getHeight(*copyMatrix, copyMatrixWidtht);
    printf("The width of the copied matrix: %d\n", cPWidth);

    //changes the matrix values
    matrix_setValue(*matrix, 3, 4, (double)5 / 8);
    matrix_setValue(*copyMatrix, 1, 2, (double)78 / 812);

    printf("Created matrix:\n");
    print_matrix(*matrix);
    printf("Copied matrix:\n");
    print_matrix(*copyMatrix);

    //get matrix value
    double value;
    double* getValue = &value;
    matrix_getValue(*matrix, 3, 4, getValue);
    printf("The value of (3,4) in created matrix is: %f\n", value);
    
    //adding the matrix
    PMatrix* result = (PMatrix*) malloc(sizeof(PMatrix));
    if (result == NULL) {
        printf("oh no result == NULL\n");
        return 1;
    }

    matrix_add(result, *matrix, *copyMatrix);

    printf("The adding matrix:\n");
    print_matrix(*result);

    //Multiplying
    PMatrix *lhs = (PMatrix*) malloc(sizeof(PMatrix));
    if (lhs == NULL) {
        printf("oh no lhs == NULL\n");
        return 1;
    }

    matrix_create(lhs, 3, 1);
    matrix_setValue(*lhs, 0, 0, -7);
    matrix_setValue(*lhs, 1, 0, 5);
    matrix_setValue(*lhs, 2, 0, 3);

    printf("lhs:\n");
    print_matrix(*lhs);

    PMatrix *rhs = (PMatrix*) malloc(sizeof(PMatrix));
    if (rhs == NULL) {
        printf("oh no rhs == NULL\n");
        return 1;
    }

    matrix_create(rhs, 1, 2);
    matrix_setValue(*rhs, 0, 0, -4);
    matrix_setValue(*rhs, 0, 1, (double)2 / 5);

    printf("rhs:\n");
    print_matrix(*rhs);

    PMatrix *multMatrix = (PMatrix*) malloc(sizeof(PMatrix));
    if (multMatrix == NULL) {
        printf("oh no multMatrix == NULL\n");
        return 1;
    }

    matrix_multiplyMatrices(multMatrix, *lhs, *rhs);

    printf("multMatrix:\n");
    print_matrix(*multMatrix);

    //distroying the matrixes
    matrix_destroy(*matrix);
    matrix_destroy(*copyMatrix);
    printf("Matrixes distroyed\n");

    //free pointers
    free(matrix);
    free(copyMatrix);
    free(result);
    free(lhs);
    free(rhs);
    free(multMatrix);
    printf("PMatrixes distroyed\n");

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

