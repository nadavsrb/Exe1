/** 
 * Hello! This is a testing file for libmatrix.so
 * Whenever a function isn't working well, this program will print you the location of the problem.
 * 
 * How do we use it? Create a .so file with Matrix.c and ErrorCode.c and place it inside the "matrix" folder.
 *                   Build, Run and there you go!
 * 
 * Creator: tseela (THE QUEEN!!!)
 * For more information contact me: tseelagamzo@gmail.com
 * 
 * I'm kidding, don't send me e-mails...
 * 
 * Good Luck!
 * */


#include "Matrix.h"
#include "ErrorCode.h"

#include <stdio.h>

typedef enum {
    // No error
    FLAG_SUCCESS = 0,
    // sizes does not match
    FLAG_SIZES = 2,
    // an error accured
    FLAG_ERROR = 3,
    // matrices not equal
    FLAG_NOT_EQUAL = 4
} Flag;

Flag initialize_matrix(const PMatrix matrix, const uint32_t height, const uint32_t width) {
    ErrorCode result;
    for (uint32_t i = 0; i < height; ++i) {
        for (uint32_t j = 0; j < width; ++j) {
            result = matrix_setValue(matrix, i, j, i*j);
            if (!error_isSuccess(result)) {
                printf("Error matrix_setValue: %s\n", error_getErrorMessage(result));
                return FLAG_ERROR;
            }
        }
    }
    return FLAG_SUCCESS;
}

Flag isEqual(CPMatrix m1, CPMatrix m2) {
    uint32_t height1, height2, width1, width2;
    double n1, n2;
    ErrorCode ec1, ec2, ec3, ec4;
    ec1 = matrix_getHeight(m1, &height1);
    ec2 = matrix_getHeight(m2, &height2);
    ec3 = matrix_getWidth(m1, &width1);
    ec4 = matrix_getWidth(m2, &width2);
    if (ec1 || ec2 || ec3 || ec4) {
        printf("%s \n %s \n %s \n %s \n", error_getErrorMessage(ec1), error_getErrorMessage(ec2), error_getErrorMessage(ec3),
            error_getErrorMessage(ec4));
        return FLAG_ERROR;
    }
    if (height1 != height2 || width2 != width1)
        return FLAG_SIZES;
    for (uint32_t i = 0; i < height1; i++) {
        for (uint32_t j = 0; j < height1; j++) {
            ec1 = matrix_getValue(m1, i, j, &n1);
            ec2 = matrix_getValue(m1, i, j, &n2);
            if (ec1 || ec2) {
                printf("%s \n %s \n", error_getErrorMessage(ec1), error_getErrorMessage(ec2));
                return FLAG_ERROR;
            }
            if (n1 != n2)
                return FLAG_NOT_EQUAL;
        }
    }
    return FLAG_SUCCESS;
}

int main() {
    ErrorCode ec;
    PMatrix m1, m2, m3, m4, m5;
    uint32_t num1;
    double num;


    // checking create

    // #CHECK 1.1
    ec = matrix_create(&m1, 3, 3);
    if (ec) {
        printf("CHECK #1.1 | Error in matrix_create: %s \n\n STOPPING TEST", error_getErrorMessage(ec));
        return 0;
    }
    matrix_destroy(m1);
    printf("CHECK #1.1 WAS SUCCESSFUL");
    printf("\n");

    // #CHECK 1.2
    ec = matrix_create(&m2, 1, 1);
    if (ec) {
        printf("CHECK #1.2 | Error in matrix_create: %s \n\n STOPPING TEST", error_getErrorMessage(ec));
        return 0;
    }
    matrix_destroy(m2);
    printf("CHECK #1.2 WAS SUCCESSFUL");
    printf("\n");
    
    // #CHECK 1.3
    ec = matrix_create(&m2, 1, 0);
    if (ec) {
        printf("CHECK 1.3 : Supposed to print an error massage because I tried to create a matrix sized 1x0 \n Error massage: %s ", 
            error_getErrorMessage(ec));
    } else
        printf("CHECK #1.3 : Error in matrix_create. You need to make sure that the height and width of the matrix both aren't 0.");
    printf("\n");
    
    // #CHECK 1.4
    ec = matrix_create(&m2, 0, 9);
    if (ec) {
        printf("CHECK 1.4 : Supposed to print an error massage because I tried to create a matrix sized 0x9 \n Error massage: %s ", 
            error_getErrorMessage(ec));
    } else
        printf("CHECK #1.4 : Error in matrix_create. You need to make sure that the height and width of the matrix both aren't 0.");
    printf("\n");
    
    // #CHECK 1.5
    ec = matrix_create(&m1, 2, 3);
    if (ec) {
        printf("CHECK #1.5 | Error in matrix_create: %s \n\n STOPPING TEST", error_getErrorMessage(ec));
        return 0;
    }
    printf("CHECK #1.5 WAS SUCCESSFUL");
    printf("\n");

    printf("Finished testing matrix_create.\n\n");

    initialize_matrix(m1, 2, 3);
    matrix_create(&m4, 7, 9);
    initialize_matrix(m4, 7, 9);

    // checking copy
    
    // #CHECK 2.1
    ec = matrix_copy(&m2, m1);
    if (ec)
        printf("CHECK #2.1.1 | Error in matrix_copy: %s", error_getErrorMessage(ec));
    else if (isEqual(m1, m2) == FLAG_NOT_EQUAL)
        printf("CHECK #2.1.2 | Fix matrix_copy. It didn't copy the matrix...");
    else if (isEqual(m1, m2) == FLAG_SIZES)
        printf("CHECK #2.1.3 | Fix matrix_copy. The new matrix and the old one aren't in the same size,");
    else if (m1 == m2)
        printf("CHECK #2.1.4 | Fix matrix_copy. You didn't create a DEEP copy...");
    else
        printf("CHECK #2.1.5 WAS SUCCESSFUL");
    matrix_destroy(m2);
    printf("\n");
    
    // #CHECK 2.2
    ec = matrix_copy(&m3, NULL);
    if (!ec)
        printf("CHECK #2.2 | Error in matrix_copy. Gave the function a NULL pointer as a matrix and the function didn't sent an error. \nReally????");
    else
        printf("CHECK #2.2 : Supposed to print an error massage because I tried to copy NULL \n Error massage: %s", error_getErrorMessage(ec));
    printf("\n");


    // #CHECK 2.3
    ec = matrix_copy(&m3, m4);
    if (ec)
        printf("CHECK #2.3.1 | Error in matrix_copy: %s", error_getErrorMessage(ec));
    else if (isEqual(m1, m2) == FLAG_NOT_EQUAL)
        printf("CHECK #2.3.2 | Fix matrix_copy. It didn't copy the matrix...");
    else if (isEqual(m1, m2) == FLAG_SIZES)
        printf("CHECK #2.3.3 | Fix matrix_copy. The new matrix and the old one aren't in the same size,");
    else if (m1 == m2)
        printf("CHECK #2.3.4 | Fix matrix_copy. You didn't create a DEEP copy...");
    else
        printf("CHECK #2.3.5 WAS SUCCESSFUL");
    matrix_destroy(m3);
    matrix_destroy(m4);
    printf("\n");

    printf("Finished testing matrix_copy.\n\n");


    // checking matrix_getHeight & matrix_getWidth

    // #CHECK 3.1
    ec = matrix_getHeight(m1, &num1);
    if (ec)
        printf("CHECK #3.1.1 | Error in matrix_getHeight: %s", error_getErrorMessage(ec));
    else if (num1 != 2)
        printf("CHECK #3.1.2 | Fix matrix_getHeight.");
    else
        printf("CHECK #3.1.3 WAS SUCCESSFUL");
    printf("\n");

    // #CHECK 3.2
    ec = matrix_getWidth(m1, &num1);
    if (ec)
        printf("CHECK #3.2.1 | Error in matrix_getWidth: %s", error_getErrorMessage(ec));
    else if (num1 != 3)
        printf("CHECK #3.2.2 | Fix matrix_getWidth.");
    else
        printf("CHECK #3.2.3 WAS SUCCESSFUL");
    printf("\n");

    // #CHECK 3.3
    ec = matrix_getWidth(NULL, &num1);
    if (ec)
        printf("CHECK #3.3 | Supposed to print an error massage because I tried to get the width of NULL \n Error massage: %s ", 
            error_getErrorMessage(ec));
    else
        printf("CHECK #3.3 | Fix matrix_getWidth. You need to check if the given matrix is NULL");
    printf("\n");

    // #CHECK 3.4
    ec = matrix_getHeight(NULL, &num1);
    if (ec)
        printf("CHECK #3.4 | Supposed to print an error massage because I tried to get the height of NULL \n Error massage: %s ", 
            error_getErrorMessage(ec));
    else
        printf("CHECK #3.4 | Fix matrix_getHeight. You need to check if the given matrix is NULL");
    printf("\n");

    printf("Finished testing matrix_getHeight & matrix_getWidth.\n\n");


    // checking matrix_getValue & matrix_setValue

    // #CHECK 4.1
    ec = matrix_getValue(m1, 1, 2, &num);
    if (ec)
        printf("CHECK #4.1.1 | Error in matrix_getValue: %s", error_getErrorMessage(ec));
    else if (num != 2)
        printf("CHECK #4.1.2 | Fix matrix_getValue. Expected to recive 2 but recieved %f.", num);
    else
        printf("CHECK #4.1.3 WAS SUCCESSFUL");
    printf("\n");

    // #CHECK 4.2
    ec = matrix_getValue(NULL, 1, 2, &num);
    if (ec)
        printf("CHECK #4.2 | Supposed to print an error massage because I tried to get the value from NULL matrix \n Error massage: %s ", 
            error_getErrorMessage(ec));
    else
        printf("CHECK #4.2 | Fix matrix_getValue. You need to check if the given matrix is NULL");
    printf("\n");

    // #CHECK 4.3
    ec = matrix_getValue(m1, 2, 2, &num);
    if (ec)
        printf("CHECK #4.3 | Supposed to print an error massage because I tried to reach place [2][2] in 2x3 array (max cell is [1][2]) \n Error massage: %s ", 
            error_getErrorMessage(ec));
    else
        printf("CHECK #4.3 | Fix matrix_getValue. You need to check if the row and col exists in the given matrix");
    printf("\n");

    // #CHECK 4.4
    ec = matrix_getValue(m1, 1, 3, &num);
    if (ec)
        printf("CHECK #4.4 | Supposed to print an error massage because I tried to reach place [1][3] in 2x3 array (max cell is [1][2]) \n Error massage: %s ", 
            error_getErrorMessage(ec));
    else
        printf("CHECK #4.4 | Fix matrix_getValue. You need to check if the row and col exists in the given matrix");
    printf("\n");

    // #CHECK 4.5
    ec = matrix_getValue(m1, 1, 1, NULL);
    if (ec)
        printf("CHECK #4.5 | Supposed to print an error massage because I tried to get a number into NULL pointer \n Error massage: %s ", 
            error_getErrorMessage(ec));
    else
        printf("CHECK #4.5 | Fix matrix_getValue. You need to check if the variable is a NULL pointer");
    printf("\n");

    // #CHECK 4.6
    ec = matrix_setValue(m1, 1, 1, -9.5);
    matrix_getValue(m1, 1, 1, &num);
    if (ec)
        printf("CHECK #4.6.1 | Error in matrix_setValue: %s", error_getErrorMessage(ec));
    else if (num != -9.5)
        printf("CHECK #4.6.2 | Fix matrix_setValue.");
    else
        printf("CHECK #4.6.3 WAS SUCCESSFUL");
    printf("\n");

    // #CHECK 4.7
    ec = matrix_setValue(NULL, 1, 2, 9);
    if (ec)
        printf("CHECK #4.7 | Supposed to print an error massage because I tried to set the value of NULL matrix \n Error massage: %s ", 
            error_getErrorMessage(ec));
    else
        printf("CHECK #4.7 | Fix matrix_setValue. You need to check if the given matrix is NULL");
    printf("\n");

    // #CHECK 4.8
    ec = matrix_setValue(m1, 2, 2, 9);
    if (ec)
        printf("CHECK #4.8 | Supposed to print an error massage because I tried to reach place [2][2] in 2x3 array (max cell is [1][2]) \n Error massage: %s ", 
            error_getErrorMessage(ec));
    else
        printf("CHECK #4.8 | Fix matrix_setValue. You need to check if the row and col exists in the given matrix");
    printf("\n");

    // #CHECK 4.9
    ec = matrix_setValue(m1, 1, 3, 9);
    if (ec)
        printf("CHECK #4.9 | Supposed to print an error massage because I tried to reach place [1][3] in 2x3 array (max cell is [1][2]) \n Error massage: %s ", 
            error_getErrorMessage(ec));
    else
        printf("CHECK #4.9 | Fix matrix_setValue. You need to check if the row and col exists in the given matrix");
    printf("\n");

    printf("Finished checking matrix_setValue & matrix_getValue.\n\n");


    matrix_create(&m1, 3, 4);
    matrix_create(&m2, 3, 4);
    initialize_matrix(m1, 3, 4);
    initialize_matrix(m2, 3, 4);
    matrix_create(&m3, 3, 4);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 4; j++) {
            matrix_getValue(m2, i, j, &num);
            matrix_setValue(m3, i, j, 2 * num);
        }
    }


    // checking matrix_add

    // #CHECK 5.1
    ec = matrix_add(&m4, m1, m2);
    if (ec)
        printf("CHECK #5.1.1 | Error in matrix_add: %s", error_getErrorMessage(ec));
    else if (isEqual(m3, m4) == FLAG_NOT_EQUAL)
        printf("CHECK #5.1.2 | Fix matrix_add. It didn't add the matrices...");
    else if (isEqual(m3, m4) == FLAG_SIZES)
        printf("CHECK #5.1.3 | Fix matrix_add. The new matrix and the old ones aren't in the same size.");
    else if (m4 == m2 || m4 == m1)
        printf("CHECK #5.1.4 | Fix matrix_add. Why did you use one of the old matrices to create the new one?!? Don't be stupid...");
    else
        printf("CHECK #5.1.5 WAS SUCCESSFUL");
    matrix_destroy(m4);
    printf("\n");

    // #CHECK 5.2
    ec = matrix_add(&m4, NULL, m2);
    if (ec)
        printf("CHECK #5.2 | Supposed to print an error massage because I tried to add a NULL matrix.\nError massage: %s", error_getErrorMessage(ec));
    else
        printf("CHECK #5.2 | Fix matrix_add. You need to check if lhs equals to NULL.");
    printf("\n");

    // #CHECK 5.3
    ec = matrix_add(&m4, m2, NULL);
    if (ec)
        printf("CHECK #5.3 | Supposed to print an error massage because I tried to add a NULL matrix.\nError massage: %s", error_getErrorMessage(ec));
    else
        printf("CHECK #5.3 | Fix matrix_add. You need to check if rhs equals to NULL.");
    printf("\n");

    // #CHECK 5.4
    ec = matrix_add(&m4, NULL, NULL);
    if (ec)
        printf("CHECK #5.4 | Supposed to print an error massage because I tried to add a NULL matrices.\nError massage: %s", error_getErrorMessage(ec));
    else
        printf("CHECK #5.4 | Fix matrix_add. You need to check if lhs & rhs equal to NULL.");
    printf("\n");

    m4 = NULL;

    // #CHECK 5.5
    ec = matrix_add(&m4, m1, m2);
    if (ec)
        printf("CHECK #5.5.1 | Error in matrix_add (or matrix_create?!?): %s\nI gave the function a pointer to NULL for the result but it shouldn't cause an error because when you creat the new matrix (the result) you allocate the pointer and the struct.", error_getErrorMessage(ec));
    else if (isEqual(m3, m4) == FLAG_NOT_EQUAL)
        printf("CHECK #5.5.2 | Fix matrix_add. It didn't add the matrices...");
    else if (isEqual(m3, m4) == FLAG_SIZES)
        printf("CHECK #5.5.3 | Fix matrix_add. The new matrix and the old ones aren't in the same size.");
    else if (m4 == m2 || m4 == m1)
        printf("CHECK #5.5.4 | Fix matrix_add. Why did you use one of the old matrices to create the new one?!? Don't be stupid...");
    else
        printf("CHECK #5.5.5 WAS SUCCESSFUL");
    matrix_destroy(m4);
    matrix_destroy(m2);
    printf("\n");

    matrix_create(&m4, 1, 1);

    // #CHECK 5.6
    ec = matrix_add(&m2, m4, m1);
    if (ec)
        printf("CHECK #5.6 | Supposed to print an error massage because I tried to add matrices in different sizes.\nError massage: %s", error_getErrorMessage(ec));
    else
        printf("CHECK #5.6 | Fix matrix_add. You need to make sure that the matrices are in the same size.");
    printf("\n");
    matrix_destroy(m4);

    printf("Finished checking matrix_add.\n\n");


    m5 = m1;


    // checking matrix_multiplyWithScalar

    // #CHECK 6.1
    ec = matrix_multiplyWithScalar(m1, 2);
    if (ec)
        printf("CHECK #6.1.1 | Error in matrix_add (or matrix_create?!?): %s\nI gave the function a pointer to NULL for the result but it shouldn't cause an error because when you creat the new matrix (the result) you allocate the pointer and the struct.", error_getErrorMessage(ec));
    else if (isEqual(m3, m1) == FLAG_NOT_EQUAL)
        printf("CHECK #6.1.2 | Fix matrix_multiplyWithScalar. It didn't add the matrices...");
    else if (isEqual(m3, m1) == FLAG_SIZES)
        printf("CHECK #6.1.3 | Fix matrix_multiplyWithScalar. The new matrix and the old one aren't in the same size.");
    else if (m1 != m5)
        printf("CHECK #6.1.4 | Fix matrix_multiplyWithScalar. Why didn't you use one of the old matrix?? You have no reason to create a new one?!? Don't be stupid...");
    else
        printf("CHECK #6.1.5 WAS SUCCESSFUL");
    printf("\n");

    // #CHECK 6.2
    ec = matrix_multiplyWithScalar(NULL, -1);
    if (ec)
        printf("CHECK #6.2 | Supposed to print an error massage because I tried to multiply a NULL matrix with scalar.\nError massage: %s", error_getErrorMessage(ec));
    else
        printf("CHECK #6.2 | Fix matrix_multiplyWithScalar. You need to make sure that the matrix isn't NULL.");
    printf("\n");

    printf("Finished checking matrix_multiplayWithScalar.\n\n");


    matrix_destroy(m1);
    matrix_destroy(m3);
    matrix_create(&m1, 3, 2);
    matrix_create(&m2, 2, 3);
    matrix_create(&m3, 3, 3);
    matrix_create(&m4, 3, 2);
    initialize_matrix(m1, 3, 2);
    initialize_matrix(m2, 2, 3);
    initialize_matrix(m3, 3, 3);


    // checking matrix_multiplyMatrices

    // #CHECK 7.1
    ec = matrix_multiplyMatrices(&m5, m4, m1);
    if (ec)
        printf("CHECK #7.1 | Supposed to print an error massage because I tried to multiply matrices sized 3x2 & 3x2.\nError massage: %s", error_getErrorMessage(ec));
    else
        printf("CHECK #7.1 | Fix matrix_multiplyWithScalar. You need to make sure that the matrix isn't NULL.");
    matrix_destroy(m4);
    printf("\n");

    // #CHECK 7.2
    ec = matrix_multiplyMatrices(&m5, NULL, m1);
    if (ec)
        printf("CHECK #7.1 | Supposed to print an error massage because I tried to multiply NULL matrix.\nError massage: %s", error_getErrorMessage(ec));
    else
        printf("CHECK #7.1 | Fix matrix_multiplyMatrices. You need to make sure that the matrix isn't NULL.");
    printf("\n");

    // #CHECK 7.3
    ec = matrix_multiplyMatrices(&m5, m1, NULL);
    if (ec)
        printf("CHECK #7.1 | Supposed to print an error massage because I tried to multiply NULL matrix.\nError massage: %s", error_getErrorMessage(ec));
    else
        printf("CHECK #7.1 | Fix matrix_multiplyMatrices. You need to make sure that the matrix isn't NULL.");
    printf("\n");

    m5 = NULL;

    // #CHECK 7.4
    ec = matrix_multiplyMatrices(&m5, m1, m2);
    if (ec)
        printf("CHECK #5.5.1 | Error in matrix_multiplyMatrices (or matrix_create?!?): %s\nI gave the function a pointer to NULL for the result but it shouldn't cause an error because when you creat the new matrix (the result) you allocate the pointer and the struct.", error_getErrorMessage(ec));
    else if (isEqual(m5, m3) == FLAG_NOT_EQUAL)
        printf("CHECK #5.5.2 | Fix matrix_multiplyMatrices. It didn't multiply the matrices...");
    else if (isEqual(m5, m3) == FLAG_SIZES)
        printf("CHECK #5.5.3 | Fix matrix_multiplyMatrices. The new matrix isn't in the right size.");
    else if (m5 == m2 || m5 == m1)
        printf("CHECK #5.5.4 | Fix matrix_multiplyMatrices. Why did you use one of the old matrices to create the new one?!? Don't be stupid...");
    else
        printf("CHECK #5.5.5 WAS SUCCESSFUL");   
    printf("\n");

    printf("Finished checking matrix_multiplyMatrices.\n\n");


    matrix_destroy(m1);
    matrix_destroy(m2);
    matrix_destroy(m3);
    matrix_destroy(m5);


    // checking matrix_destroy (last check)

    // #CHECK 8
    printf("If the program will crash here note that you need to make sure that the given matrix isn't NULL in matrix_destroy.\n");
    matrix_destroy(NULL);

    printf("Finished checking matrix_destroy.\n\n");



    printf("Test ended. Hope you get A+ !!   (;");

    return 0;
}