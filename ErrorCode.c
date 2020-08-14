#include "ErrorCode.h"

bool error_isSuccess(ErrorCode code) {
    bool success = false;

    if (code == ERROR_SUCCESS) {
        success = true;
    }

    return success;
}