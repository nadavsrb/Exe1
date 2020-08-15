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

ErrorCode matrix_getHeight(CPMatrix matrix, uint32_t* result){
    //if got null
    if (matrix == NULL || result == NULL) {
        return  ERROR_PARAMETER_IS_NULL;
    }

    //The height of a matrix is the num of rows she has.
    *result = matrix->numRows;

    return ERROR_SUCCESS;
}

ErrorCode matrix_getWidth(CPMatrix matrix, uint32_t* result){
    //if got null
    if (matrix == NULL || result == NULL) {
        return  ERROR_PARAMETER_IS_NULL;
    }

    //The width of a matrix is the num of colums she has.
    *result = matrix->numCols;

    return ERROR_SUCCESS;
}

ErrorCode matrix_setValue(PMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
                          double value){
    //if got null
    if (matrix == NULL) {
        return  ERROR_PARAMETER_IS_NULL;
    }

    //checks the index are in boundary
    if ((rowIndex < 0 || rowIndex >= (matrix->numRows)) 
        || (colIndex < 0 || colIndex >= (matrix->numCols))) {
        return ERROR_INDEX_OUT_OF_BOUNDAY;
    }

    //change the value of the cell
    (matrix->data)[rowIndex][colIndex] = value;

    return ERROR_SUCCESS;
}

ErrorCode matrix_getValue(CPMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
                          double* value){
    //if got null
    if (matrix == NULL) {
        return  ERROR_PARAMETER_IS_NULL;
    }

    //checks the index are in boundary
    if ((rowIndex < 0 || rowIndex >= (matrix->numRows)) 
        || (colIndex < 0 || colIndex >= (matrix->numCols))) {
        return ERROR_INDEX_OUT_OF_BOUNDAY;
    }

    //gets the value of the cell
    *value = (matrix->data)[rowIndex][colIndex];

    return ERROR_SUCCESS;
}

ErrorCode matrix_add(PMatrix* result, CPMatrix lhs, CPMatrix rhs){
    //if got null
    if (result == NULL || lhs == NULL || rhs == NULL) {
        return  ERROR_PARAMETER_IS_NULL;
    }

    //checks if can be added
    if ((lhs->numRows != rhs->numRows) || (lhs->numCols != rhs->numCols)) {
        return ERROR_MATRIX_IN_DIFFERENT_SIZE;
    }

    //var for helping programing
    int height = lhs->numRows;
    int width = lhs->numCols;

    //creates the result matrix
    ErrorCode error = matrix_create(result, height, width);
    if (!error_isSuccess(error)) {
        return error;
    }

    //adding the matrixes
    double newVal = 0;
    for (int rowIndex = 0; rowIndex < height; rowIndex++) {
        for (int colIndex = 0; colIndex < width; colIndex++) {
            newVal = (lhs->data)[rowIndex][colIndex] + (rhs->data)[rowIndex][colIndex];

            //no need to check for errors because I cared it won't be
            matrix_setValue(*result, rowIndex, colIndex, newVal);
        }
    }

    return ERROR_SUCCESS;
}