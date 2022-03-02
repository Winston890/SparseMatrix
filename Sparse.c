// Winston Yi
// wyi10

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include"Matrix.h"


int main(int argc, char * argv[]){

    FILE *in, *out;

     // check command line for correct number of arguments
    if( argc != 3 ){
       printf("Usage: %s <input file> <output file>\n", argv[0]);
       exit(1);
    }

     // open files for reading and writing 
    in = fopen(argv[1], "r");
    if( in==NULL ){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    out = fopen(argv[2], "w");
    if( out==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }       
    
    // Make Matrices

    int n = 0;
    fscanf(in, "%d", &n);
    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);
    int NNZ_A = 0;
    int NNZ_B = 0;
    fscanf(in, "%d", &NNZ_A);
    fscanf(in, "%d", &NNZ_B);

    int row, col = 0;
    double val = 0;
    while (NNZ_A > 0) {
        fscanf(in, "%d", &row);
        fscanf(in, "%d", &col);
        fscanf(in, "%lf", &val);
        changeEntry(A, row, col, val);
        NNZ_A -= 1;
    } 
    
    while (NNZ_B > 0) {
        fscanf(in, "%d", &row);
        fscanf(in, "%d", &col);
        fscanf(in, "%lf", &val);
        changeEntry(B, row, col, val);
        NNZ_B -= 1;
    }
    Matrix scalar = scalarMult(1.5, A);
    Matrix addAB = sum(A, B);
    Matrix addAA = sum(A, A);
    Matrix minusBA = diff(B, A);
    Matrix minusAA = diff(A, A);
    Matrix T = transpose(A);
    Matrix multAB = product(A, B);
    Matrix multBB = product(B, B);

    // Print Matrices

    fprintf(out, "A has %d non-zero entries:\n", NNZ(A));
    printMatrix(out, A);
    fprintf(out, "\n");    
    fprintf(out, "B has %d non-zero entries:\n", NNZ(B));
    printMatrix(out, B);

    fprintf(out, "\n");    
    fprintf(out, "(1.5)*A =\n");
    printMatrix(out, scalar);

    fprintf(out, "\n");    
    fprintf(out, "A+B =\n");
    printMatrix(out, addAB);
    
    fprintf(out, "\n");    
    fprintf(out, "A+A =\n");
    printMatrix(out, addAA);
    
    fprintf(out, "\n");    
    fprintf(out, "B-A =\n");
    printMatrix(out, minusBA);
    
    fprintf(out, "\n");    
    fprintf(out, "A-A =\n");
    printMatrix(out, minusAA);

    fprintf(out, "\n");    
    fprintf(out, "Transpose(A) =\n");
    printMatrix(out, T);
    
    fprintf(out, "\n");    
    fprintf(out, "A*B =\n");
    printMatrix(out, multAB);

    fprintf(out, "\n");    
    fprintf(out, "B*B =\n");
    printMatrix(out, multBB);
    fprintf(out, "\n");    

    // Free Matrices
    
    freeMatrix(&A);
    freeMatrix(&B);
    freeMatrix(&scalar);
    freeMatrix(&addAB);
    freeMatrix(&addAA);
    freeMatrix(&minusBA);
    freeMatrix(&minusAA);
    freeMatrix(&T);
    freeMatrix(&multAB);
    freeMatrix(&multBB);
    fclose(in);
    fclose(out);
    return 0;
}

