cmake_minimum_required(VERSION 3.0.0)
project(ex1 VERSION 0.1.0)

set(C_STANDARD C99)
add_library(matrix SHARED src/ErrorCode.c src/Matrix.c)
add_compile_options(-Wall -Wextra -pedantic -Werror)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})

