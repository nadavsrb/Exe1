#include "ErrorCode.h"

bool error_isSuccess(ErrorCode code) {
    bool success = false;

    if (code == ERROR_SUCCESS) {
        success = true;
    }

    return success;
}

const char* error_getErrorMessage(ErrorCode code) {
    switch(code) {
    case ERROR_SUCCESS:
        return "The function was complited successfully";
    case ERROR_ALLOCATING_MEMORY:
        return "Error: Couldn't allocate memory for the matrix";
    case ERROR_PARAMETER_IS_NULL:
        return "Error: At least one of the given paramter to the function is NULL";
    case ERROR_INDEX_OUT_OF_BOUNDARY:
        return "Error: At least one of the given index is out of the matrix's boundary";
    case ERROR_MATRIX_IN_DIFFERENT_SIZE:
        return "Error: Can't add the matrixes because they are in different size";
    case ERROR_MATRIX_CANT_BE_MULTIPLY:
        return "Error: Can't multiply the matrixes because the #colsLeftMatrix != #rowsRightMatrix";
    case ERROR_MATRIX_DOESNT_INTALIZED_WELL:
        return "Error: One or more value in a given matrix is NULL";
    case ERROR_NEGATIVE_MATRIX_SIZE:
        return "Error: At least one of the sizes in a given matrix is negative";
    default:
    return "";
    }
}