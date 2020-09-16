#include <stdlib.h>

#include "Matrix.h"

//helping method
ErrorCode check_matrix(CPMatrix matrix);

struct Matrix {
     uint32_t numRows; // number of rows
     uint32_t numCols; // number of columns
     double** data; // a pointer to an array of numCols rows that each points to numCols double; 
};

ErrorCode matrix_create(PMatrix* matrix, uint32_t height, uint32_t width) {
    //if got null
    if (matrix == NULL) {
        return  ERROR_PARAMETER_IS_NULL;
    }

    //check the hight and width are positive
    if (height == 0 || width == 0){
        return ERROR_ZERO_SIZE;
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
        //free the pointer to the matrix
         free(*matrix);

        return ERROR_ALLOCATING_MEMORY;
    }

    //intalizing the matrix cells
    for (uint32_t rowIndex = 0; rowIndex < height; rowIndex++) {
         ((*matrix)->data)[rowIndex] = (double*) malloc(width * sizeof(double));
         if (((*matrix)->data)[rowIndex] == NULL) {
                 //free each row that was alocated
                for (uint32_t i = 0; i < rowIndex - 1; i++) {
                    free(((*matrix)->data)[i]);
                }

                 //free rows pointer
                free((*matrix)->data);

                //free the pointer to the matrix
                free(*matrix);

                return ERROR_ALLOCATING_MEMORY;
            }

        for (uint32_t colIndex = 0; colIndex < width; colIndex++) {
        ((*matrix)->data)[rowIndex][colIndex] = 0;
        }
    }

    return ERROR_SUCCESS;
}

ErrorCode matrix_copy(PMatrix* result, CPMatrix source) {
    //if got null
    if (result == NULL || source == NULL) {
        return  ERROR_PARAMETER_IS_NULL;
    }

    //checks Matrixe
    ErrorCode eSource = check_matrix(source);
    if(!error_isSuccess(eSource)){
        return eSource;
    }

    //var for helping programing
    uint32_t height = source->numRows;
    uint32_t width = source->numCols;

    //creates the copy matrix
    ErrorCode error = matrix_create(result, height, width);
    if (!error_isSuccess(error)) {
        return error;
    }

    //intalizing the matrix cells
    for (uint32_t rowIndex = 0; rowIndex < height; rowIndex++) {
        for (uint32_t colIndex = 0; colIndex < width; colIndex++) {
        ((*result)->data)[rowIndex][colIndex] = (source->data)[rowIndex][colIndex];
        }
    }

    return ERROR_SUCCESS;
}

void matrix_destroy(PMatrix matrix) {
    //if got null
    if (matrix == NULL) {
        return;
    }

    //checks Matrix
    ErrorCode e = check_matrix(matrix);
    if(!error_isSuccess(e)){
        return;
    }

     //var for helping programing
    uint32_t height = matrix->numRows;

    //free each row
    for (uint32_t i = 0; i < height; i++) {
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

    //checks Matrix
    ErrorCode e = check_matrix(matrix);
    if(!error_isSuccess(e)){
        return e;
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

    //checks Matrix
    ErrorCode e = check_matrix(matrix);
    if(!error_isSuccess(e)){
        return e;
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
    
    //checks Matrix
    ErrorCode e = check_matrix(matrix);
    if(!error_isSuccess(e)){
        return e;
    }

    //checks the index are in boundary
    if (rowIndex >= (matrix->numRows)
        || colIndex >= (matrix->numCols)) {
        return ERROR_INDEX_OUT_OF_BOUNDARY;
    }

    //change the value of the cell
    (matrix->data)[rowIndex][colIndex] = value;

    return ERROR_SUCCESS;
}

ErrorCode matrix_getValue(CPMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
                          double* value){
    //if got null
    if (matrix == NULL || value == NULL) {
        return  ERROR_PARAMETER_IS_NULL;
    }

    //checks Matrix
    ErrorCode e = check_matrix(matrix);
    if(!error_isSuccess(e)){
        return e;
    }

    //checks the index are in boundary
    if (rowIndex >= (matrix->numRows) 
        || colIndex >= (matrix->numCols)) {
        return ERROR_INDEX_OUT_OF_BOUNDARY;
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

    //checks Matrixes
    ErrorCode eLhs = check_matrix(lhs);
    if(!error_isSuccess(eLhs)){
        return eLhs;
    }

    ErrorCode eRhs = check_matrix(rhs);
    if(!error_isSuccess(eRhs)){
        return eRhs;
    }


    //checks if can be added
    if ((lhs->numRows != rhs->numRows) || (lhs->numCols != rhs->numCols)) {
        return ERROR_MATRIXES_IN_DIFFERENT_SIZES;
    }

    //var for helping programing
    uint32_t height = lhs->numRows;
    uint32_t width = lhs->numCols;

    //creates the result matrix
    ErrorCode error = matrix_create(result, height, width);
    if (!error_isSuccess(error)) {
        return error;
    }

    //adding the matrixes
    double newVal = 0;
    for (uint32_t rowIndex = 0; rowIndex < height; rowIndex++) {
        for (uint32_t colIndex = 0; colIndex < width; colIndex++) {
            newVal = (lhs->data)[rowIndex][colIndex] + (rhs->data)[rowIndex][colIndex];

            //no need to check for errors because I cared it won't be
            matrix_setValue(*result, rowIndex, colIndex, newVal);
        }
    }

    return ERROR_SUCCESS;
}

ErrorCode matrix_multiplyMatrices(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
    //if got null
    if (result == NULL || lhs == NULL || rhs == NULL) {
        return  ERROR_PARAMETER_IS_NULL;
    }

    //checks Matrixes
    ErrorCode eLhs = check_matrix(lhs);
    if(!error_isSuccess(eLhs)){
        return eLhs;
    }

    ErrorCode eRhs = check_matrix(rhs);
    if(!error_isSuccess(eRhs)){
        return eRhs;
    }

    //checks if can be multiply
    if (lhs->numCols != rhs->numRows) {
        return ERROR_MATRIXES_CAN_NOT_BE_MULTIPLIED;
    }

    //var for helping programing (stands for the size of result)
    uint32_t height = lhs->numRows;
    uint32_t width = rhs->numCols;

    //var for help
    uint32_t sharedSize = lhs->numCols;

    //creates the result matrix
    ErrorCode error = matrix_create(result, height, width);
    if (!error_isSuccess(error)) {
        return error;
    }

    //multipling the matrixes
    double newVal = 0;
    for (uint32_t rowIndex = 0; rowIndex < height; rowIndex++) {
        for (uint32_t colIndex = 0; colIndex < width; colIndex++) {

            //intalizing the new value
            newVal = 0;

            //calculating the new value
            for (uint32_t multIndex = 0; multIndex < sharedSize; multIndex++){
                newVal += (lhs->data)[rowIndex][multIndex] * (rhs->data)[multIndex][colIndex];
            }

            //no need to check for errors because I cared it won't be
            matrix_setValue(*result, rowIndex, colIndex, newVal);
        }
    }

    return ERROR_SUCCESS; 
}

ErrorCode matrix_multiplyWithScalar(PMatrix matrix, double scalar) {
    //if got null
    if (matrix == NULL) {
        return  ERROR_PARAMETER_IS_NULL;
    }

    //checks Matrix
    ErrorCode e = check_matrix(matrix);
    if(!error_isSuccess(e)){
        return e;
    }

    //var for helping programing (stands for the size of result)
    uint32_t height = matrix->numRows;
    uint32_t width = matrix->numCols;

    //multipling the matrixe
    double newVal = 0;
    for (uint32_t rowIndex = 0; rowIndex < height; rowIndex++) {
        for (uint32_t colIndex = 0; colIndex < width; colIndex++) {
            //calculating the new value
            newVal = scalar * (matrix->data)[rowIndex][colIndex];

            //no need to check for errors because I cared it won't be
            matrix_setValue(matrix, rowIndex, colIndex, newVal);
        }
    }

    return ERROR_SUCCESS; 
}

/**
 * @brief check if matrix is intalized right (no null in it).
 * 
 * @param matrix the matrix to check.
 * @return ErrorCode
 */
ErrorCode check_matrix(CPMatrix matrix){
    //checks if there are NULLs
    if (matrix == NULL) {
        return ERROR_MATRIX_IS_NOT_INTALIZED_WELL;
    }

    if (matrix -> data == NULL){
        return ERROR_MATRIX_IS_NOT_INTALIZED_WELL;
    }

    //check the hight and width are positive
    if (matrix->numCols == 0 || matrix->numRows == 0){
        return ERROR_ZERO_SIZE;
    }

    //You can add this check but it may cost in run time 
    //(I prefered not to add because it batter to realy on the programer
    //then cost in run time)

    // for (int i = 0; i < (matrix->numRows); i++) {
    //     if ((matrix->data)[i] == NULL){
    //         return ERROR_MATRIX_DOESNT_INTALIZED_WELL;
    //     }
    // }

    return ERROR_SUCCESS;
}