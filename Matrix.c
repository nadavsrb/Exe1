#include <stdlib.h>

#include "Matrix.h"
#include "ErrorCode.c"


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
    (*matrix)->numCols = width;

    (*matrix)->data = (double**) malloc(height * sizeof(double*));
    if ((*matrix)->data == NULL) {
        return ERROR_ALLOCATING_MEMORY;
    }
    
    //intalizing the matrix cells
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

ErrorCode matrix_copy(PMatrix* result, CPMatrix source) {
    //if got null
    if (result == NULL || source == NULL) {
        return  ERROR_PARAMETER_IS_NULL;
    }

    //var for helping programing
    int height = source->numRows;
    int width = source->numCols;

    //creates the copy matrix
    ErrorCode error = matrix_create(result, height, width);
    if (!error_isSuccess(error)) {
        return error;
    }

    //intalizing the matrix cells
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
        ((*result)->data)[i][j] = (source->data)[i][j];
        }
    }

    return ERROR_SUCCESS;
}

void matrix_destroy(PMatrix matrix) {
    //if matrix not poins to a matrix
    if (matrix == NULL) {
        return;
    }

     //var for helping programing
    int height = matrix->numRows;
    int width = matrix->numCols;

    //free each row
    for (int i = 0; i < height; i++) {
         free((matrix->data)[i]);
    }

    //free rows pointer
    free(matrix->data);

    //free the pointer to the matrix
    free(matrix);
}