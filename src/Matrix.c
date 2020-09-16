#include <stdlib.h>

#include "Matrix.h"

#define ERROR_IN_GET_VALUE -1

//helping method
ErrorCode check_matrix(CPMatrix matrix);
double* get_pointer_value(PMatrix matrix, uint32_t rowIndex, uint32_t colIndex);
double get_value(CPMatrix matrix, uint32_t rowIndex, uint32_t colIndex);

struct Matrix {
     uint32_t numRows; // number of rows
     uint32_t numCols; // number of columns
     double* data; // a pointer to the allocated memory of the matrix.
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

    (*matrix)->data = (double*) malloc(height * width * sizeof(double));
    if ((*matrix)->data == NULL) {
        //free the pointer to the matrix
         free(*matrix);

        return ERROR_ALLOCATING_MEMORY;
    }

    //intalizing the matrix cells
    for (uint32_t rowIndex = 0; rowIndex < height; ++rowIndex) {
        for (uint32_t colIndex = 0; colIndex < width; ++colIndex) {
            *(get_pointer_value(*matrix, rowIndex, colIndex)) = 0;
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
    for (uint32_t rowIndex = 0; rowIndex < height; ++rowIndex) {
        for (uint32_t colIndex = 0; colIndex < width; ++colIndex) {
       *(get_pointer_value(*result, rowIndex, colIndex)) = get_value(source, rowIndex, colIndex);
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

    //free the matrix located memory
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
    *(get_pointer_value(matrix, rowIndex, colIndex)) = value;

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
    *value = get_value(matrix, rowIndex, colIndex);

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
    for (uint32_t rowIndex = 0; rowIndex < height; ++rowIndex) {
        for (uint32_t colIndex = 0; colIndex < width; ++colIndex) {
            newVal = get_value(lhs, rowIndex, colIndex) + get_value(rhs, rowIndex, colIndex);

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
    for (uint32_t rowIndex = 0; rowIndex < height; ++rowIndex) {
        for (uint32_t colIndex = 0; colIndex < width; ++colIndex) {

            //intalizing the new value
            newVal = 0;

            //calculating the new value
            for (uint32_t multIndex = 0; multIndex < sharedSize; ++multIndex){
                newVal += get_value(lhs, rowIndex, multIndex) * get_value(rhs, multIndex ,colIndex);
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
    for (uint32_t rowIndex = 0; rowIndex < height; ++rowIndex) {
        for (uint32_t colIndex = 0; colIndex < width; ++colIndex) {
            //calculating the new value
            newVal = scalar * get_value(matrix, rowIndex, colIndex);

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

    return ERROR_SUCCESS;
}

/**
 * @brief Get the pointer's value, of
 * a value in the matrix.
 * 
 * ***assumes the matrix was already 
 * checked by check_matrix, (or intaized as needed),
 * and that the Indexes are in the matrix size boundry:
 * rowIndex < (matrix->numRows) && colIndex < (matrix->numCols).
 * (if not, would return NULL)
 * 
 * @param matrix the matrix (not const becuse we can
 *  change the matrix value from the pointer).
 * @param rowIndex of the value.
 * @param colIndex of the value.
 * @return double* pointer to the value.
 */
double* get_pointer_value(PMatrix matrix, uint32_t rowIndex, uint32_t colIndex) {
    //checks Matrix
    ErrorCode e = check_matrix(matrix);
    if(!error_isSuccess(e)){
        return NULL;
    }

    if (rowIndex >= (matrix->numRows) 
        || colIndex >= (matrix->numCols)) {
            return NULL;
    }

    return matrix->data + rowIndex * matrix->numRows + colIndex;
}


/**
 * @brief Get the value in the matrix.
 * 
 * ***assumes the matrix was already 
 * checked by check_matrix, (or intaized as needed),
 * and that the Indexes are in the matrix size boundry:
 * rowIndex < (matrix->numRows) && colIndex < (matrix->numCols).
 * (if not, would return ERROR_IN_GET_VALUE)
 * 
 * @param matrix the matrix.
 * @param rowIndex of the value.
 * @param colIndex of the value.
 * @return double the value.
 */
double get_value(CPMatrix matrix, uint32_t rowIndex, uint32_t colIndex) {
    //checks Matrix
    ErrorCode e = check_matrix(matrix);
    if(!error_isSuccess(e)){
        return ERROR_IN_GET_VALUE;
    }

    if (rowIndex >= (matrix->numRows) 
        || colIndex >= (matrix->numCols)) {
            return ERROR_IN_GET_VALUE;
    }

    return *(matrix->data + rowIndex * matrix->numRows + colIndex);
}