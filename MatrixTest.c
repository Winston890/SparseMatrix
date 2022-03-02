#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"Matrix.h"

int main(){
    Matrix A = newMatrix(3);
    changeEntry(A, 1, 1, 4);
    changeEntry(A, 1, 2, 2);
    changeEntry(A, 1, 3, 0);
    changeEntry(A, 2, 1, 2);
    changeEntry(A, 3, 1, 0);
    changeEntry(A, 2, 2, 2);
    changeEntry(A, 3, 3, 0);
    printMatrix(stdout, A);
    printf("NNZ is: %d", NNZ(A));
    Matrix C = copy(A);
    Matrix T = transpose(A);
    printMatrix(stdout, C);
    printMatrix(stdout, T);
    Matrix S = sum(T, A);
    Matrix D = diff(T, A);
    Matrix M = scalarMult(2, A);
    printMatrix(stdout, S);
    printMatrix(stdout, D);
    printMatrix(stdout, M);
    printMatrix(stdout, A);
    makeZero(A);
    freeMatrix(&A);
    freeMatrix(&C);
    freeMatrix(&T);
    freeMatrix(&S);
    freeMatrix(&D);
    freeMatrix(&M);
    return 0;
}
