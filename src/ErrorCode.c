#include "ErrorCode.h"

bool error_isSuccess(const ErrorCode code) {
    return code == ERROR_SUCCESS;
}

const char* error_getErrorMessage(const ErrorCode code) {
    switch(code) {
    case ERROR_SUCCESS:
        return "The function was complited successfully";
    case ERROR_ALLOCATING_MEMORY:
        return "Error: Couldn't allocate memory for the matrix";
    case ERROR_PARAMETER_IS_NULL:
        return "Error: At least one of the given paramter to the function is NULL";
    case ERROR_INDEX_OUT_OF_BOUNDARY:
        return "Error: At least one of the given index is out of the matrix's boundary";
    case ERROR_MATRIXES_IN_DIFFERENT_SIZES:
        return "Error: Can't add the matrixes because they are in different sizes";
    case ERROR_MATRIXES_CAN_NOT_BE_MULTIPLIED:
        return "Error: Can't multiply the matrixes because the #colsLeftMatrix != #rowsRightMatrix";
    case ERROR_MATRIX_IS_NOT_INTALIZED_WELL:
        return "Error: One or more value in a given matrix is NULL";
    case ERROR_ZERO_SIZE:
        return "Error: At least one of the sizes of a given matrix is zero";
    default://should never get in
    return "Error: unknown";
    }
}