#include "Matrix.h"
#include <stdlib.h>

struct Matrix {
     int numRows; // number of rows
     int numCols; // number of columns
     double** data; // a pointer to an array of numCols rows that each points to numCols double; 
};

ErrorCode matrix_create(PMatrix* matrix, uint32_t height, uint32_t width) {
    //if got null
    if (matrix == NULL) {
        return  ERROR_PARAMETER_IS_NULL;
    }

    //Allocating memory for the matrix variables
    *matrix = (PMatrix) malloc(sizeof(struct Matrix));
    if ((*matrix) == NULL) {
        return ERROR_ALLOCATING_MEMORY;
    }

    //reset the matrix variables
    (*matrix)->numRows = height;
    (*matrix)->numRows = width;

    (*matrix)->data = (double**) malloc(height * sizeof(double*));
    if ((*matrix)->data == NULL) {
        return ERROR_ALLOCATING_MEMORY;
    }

    for (int i = 0; i < height; i++) {
         ((*matrix)->data)[i] = (double*) malloc(width * sizeof(double));
         if (((*matrix)->data)[i] == NULL) {
             return ERROR_ALLOCATING_MEMORY;
             }

        for (int j = 0; j < width; j++) {
        ((*matrix)->data)[i][j] = 0;
        }
    }

    return ERROR_SUCCESS;
}