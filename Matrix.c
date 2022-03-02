// Winston Yi
// wyi10
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"
#include"Matrix.h"


// structs --------------------------------------------------------------------

// private Entry type
typedef struct EntryObj* Entry;

// private EntryObj type
typedef struct EntryObj{
    int col;
    double value;
} EntryObj;


// private Matrix type
typedef struct MatrixObj* Matrix;

// private MatrixObj type
typedef struct MatrixObj{
    List *lists;
    int NNZ;
    int size;
} MatrixObj;


// Constructors-Destructors ---------------------------------------------------


Entry newEntry(int col, double val) {
    Entry E = calloc(1, sizeof(EntryObj));
    E->col = col;
    E->value = val;
    return E;
}

void freeEntry(Entry* pE) {
    if(pE!=NULL && *pE!=NULL) {
        free(*pE);
        *pE = NULL;
    }
}

Matrix newMatrix(int n) {
    Matrix M = calloc(1, sizeof(MatrixObj));
    M->lists = calloc(n+1, sizeof(List));
    M->size = n;
    M->NNZ = 0;
    for (int i = 0; i <= n; i++) {
        M->lists[i] = newList();
    }
    return M;
}

void freeMatrix(Matrix* pM) {
    if(pM!=NULL && *pM!=NULL) {
        for (int i = 0; i <= size(*pM); i++) {
            moveFront((*pM)->lists[i]);
            while (index((*pM)->lists[i]) != -1) {
                Entry E = get((*pM)->lists[i]);
                freeEntry(&E);
                moveNext((*pM)->lists[i]);
            }
            freeList(&((*pM)->lists[i]));
        }
    }
    free((*pM)->lists);
    free(*pM);
    *pM = NULL;
}


    
// Access functions -----------------------------------------------------------

static int getCol(Entry E) {
    if (E==NULL) {
        printf("Null Entry");
    }
    return E->col;
}

static double getValue(Entry E) {
    if (E==NULL) {
        printf("Null Entry");
    }
    return E->value;
}

static int entryEquals(Entry A, Entry B) {
    if (A == NULL || B == NULL) {
        printf("Null Entry Equals call");
    }
    if (getCol(A) == getCol(B) && getValue(A) == getValue(B)) {
        return 1;
    }
    return 0;
}

static Entry copyEntry(Entry E) {
    if (E==NULL) {
        printf("Null Entry");
    }
    int col = getCol(E);
    int val = getValue(E);
    Entry C = newEntry(col, val);
    return C;
}
    
    
static void changeValue(Entry E, double x) {
    if (E==NULL) {
        printf("Null Entry");
    }
    E->value = x;
}

static void printEntry(FILE* out, Entry E) {
    if (E==NULL) {
        printf("Null Entry");
    }
    fprintf(out, "(%d, %0.1f) ", getCol(E), getValue(E));
}
    
int size(Matrix M) {
    if (M==NULL) {
        printf("Matrix Error: calling size() on NULL List reference\n");
     	exit(EXIT_FAILURE);
    }
    return M->size;
}


int NNZ(Matrix M) {
    if (M==NULL) {
        printf("Matrix Error: calling NNZ() on NULL List reference\n");
     	exit(EXIT_FAILURE);
    }
    return M->NNZ;
}


int equals(Matrix A, Matrix B) {
    if (A==NULL || B==NULL) {
        printf("Matrix Error: calling equals() on NULL List reference\n");
     	exit(EXIT_FAILURE);
    }

    if (size(A) != size(B) || NNZ(A) != NNZ(B)) {
        return 0;
    }
    for (int i = 1; i <= size(A); i++) {
        moveFront(A->lists[i]);
        moveFront(B->lists[i]);
        while (index(A->lists[i]) != -1 && index(B->lists[i]) != -1) {
            if (entryEquals(get(A->lists[i]), get(B->lists[i]))) {
                moveNext(A->lists[i]);
                moveNext(B->lists[i]);
            } else {
                return 0;
            }
        }
    }
    return 1; 
}

void makeZero(Matrix M) {
    if (M==NULL) {
        printf("Matrix Error: calling makezero() on NULL List reference\n");
     	exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= size(M); i++) {
        clear(M->lists[i]);
    }
    M->NNZ = 0;
}


void changeEntry(Matrix M, int i, int j, double x) {
    if (M==NULL) {
        printf("Matrix Error: calling ChangeEnrtry() on NULL List reference\n");
     	exit(EXIT_FAILURE);
    }
    
    moveFront(M->lists[i]);
    if (isEmpty(M->lists[i])) {
        if (x == 0) {
            return;
        }
        Entry E = newEntry(j, x);
        prepend(M->lists[i], E);
        M->NNZ += 1;
        return;
    } 

    while (j >= getCol(get(M->lists[i])) && index(M->lists[i]) != -1) {
        if (j == getCol(get(M->lists[i]))) {
            if (x == 0) {
                Entry D = get(M->lists[i]);
                M->NNZ -= 1;
                freeEntry(&D);
                delete(M->lists[i]);
                return;
            } else {
                changeValue(get(M->lists[i]), x);
                return;
            }
        }
        moveNext(M->lists[i]);
    }

    if (x == 0) {
        return;
    }
    Entry E = newEntry(j, x);
        
    if (index(M->lists[i]) == -1) {
        append(M->lists[i], E);
    } else if (index(M->lists[i]) == 0) {
        prepend(M->lists[i], E);
    } else {
        insertBefore(M->lists[i], E);
    }
    M->NNZ += 1;
}

Matrix copy(Matrix A) {
    if (A==NULL) {
        printf("Matrix Error: calling Copy() on NULL List reference\n");
     	exit(EXIT_FAILURE);
    }

    Matrix M = newMatrix(size(A));
    for (int i = 1; i <= size(A); i++) {
        moveFront(A->lists[i]);
        while (index(A->lists[i]) != -1) {
            Entry E = copyEntry(get(A->lists[i]));
            if (getValue(E) != 0) {
                append(M->lists[i], E);
            }
            moveNext(A->lists[i]);
        }
    }
    M->NNZ = NNZ(A);
    return M;
}

Matrix transpose(Matrix A) {
    if (A==NULL) {
        printf("Matrix Error: calling transpose() on NULL List reference\n");
     	exit(EXIT_FAILURE);
    }

    int n = size(A);
    Matrix M = newMatrix(n);
    int col = 0;
    double val = 0;
    for (int row = 1; row <= size(A); row++) {
        moveFront(A->lists[row]);
        while (index(A->lists[row]) != -1) {
            Entry E = get(A->lists[row]);
            col = getCol(E);
            val = getValue(E);
            changeEntry(M, col, row, val);
            moveNext(A->lists[row]);
        }
    }
    return M;
}


Matrix scalarMult(double x, Matrix A) {
    if (A==NULL) {
        printf("Matrix Error: calling scalarMult() on NULL List reference\n");
     	exit(EXIT_FAILURE);
    }
    if (x == 0) {
        makeZero(A);
        return A;
    }

    int n = size(A);
    Matrix M = newMatrix(n);
    int col = 0;
    double val = 0;
    for (int row = 1; row <= size(A); row++) {
        moveFront(A->lists[row]);
        while (index(A->lists[row]) != -1) {
            Entry E = get(A->lists[row]);
            col = getCol(E);
            val = getValue(E);
            val = x*val;
            changeEntry(M, row, col, val);
            moveNext(A->lists[row]);
        }
    }
    M->NNZ = NNZ(A);
    return M;
}


Matrix sum(Matrix A, Matrix B) {
    if (A==NULL || B == NULL) {
        printf("Matrix Error: calling sum() on NULL List reference\n");
     	exit(EXIT_FAILURE);
    }
    if (size(A) != size(B)) {
        printf("Wrong sizes in sum");
        exit(EXIT_FAILURE);
    }
    if (A == B) {
        Matrix S = scalarMult(2, A);
        return S;
    }

    int n = size(A);
    Matrix M = newMatrix(n);
    double val = 0;
    int col = 0;
    for (int row = 1; row <= size(A); row++) {
        if (isEmpty(A->lists[row]) && isEmpty(B->lists[row])) {
            continue;
        }
        else if (isEmpty(B->lists[row])) {
            moveFront(A->lists[row]);
            while (index(A->lists[row]) != -1) {
                Entry T = get(A->lists[row]);
                changeEntry(M, row, getCol(T), getValue(T));
                moveNext(A->lists[row]);
            }
            continue;
        } else if (isEmpty(A->lists[row])) {
            moveFront(B->lists[row]);
            while (index(B->lists[row]) != -1) {
                Entry K = get(B->lists[row]);
                changeEntry(M, row, getCol(K), getValue(K));
                moveNext(B->lists[row]);
            }
            continue;
        }
        col = 0;
        //int length_a = length(A->lists[row]);
        //int length_b = length(B->lists[row]);
        //int max_len = (length_a > length_b) ? length_a : length_b;
        moveFront(A->lists[row]); 
        moveFront(B->lists[row]); 
        while (col < n) {
            col += 1;
            if (index(A->lists[row]) != -1) {
                Entry X = get(A->lists[row]);
                if (getCol(X) == col) {
                    val += getValue(X);
                    moveNext(A->lists[row]);
                }
            }
            if (index(B->lists[row]) != -1) {
                Entry Y = get(B->lists[row]);
                if (getCol(Y) == col) {                
                    val += getValue(Y);
                    moveNext(B->lists[row]);
                }
            }
            if (val != 0) {
                changeEntry(M, row, col, val);
            }
            val = 0;
        }
    }
    return M;
}

Matrix diff(Matrix A, Matrix B) {
    if (A==NULL || B == NULL) {
        printf("Matrix Error: calling diff() on NULL List reference\n");
     	exit(EXIT_FAILURE);
    }
    if (size(A) != size(B)) {
        printf("Wrong sizes in diff");
        exit(EXIT_FAILURE);
    }
    if (A == B) {
        Matrix Z = newMatrix(size(A));
        return Z;
    }
    int n = size(A);
    Matrix M = newMatrix(n);
    int col = 0;
    double val = 0;
    for (int row = 1; row <= size(A); row++) {
        if (isEmpty(A->lists[row]) && isEmpty(B->lists[row])) {
            continue;
        }
        else if (isEmpty(B->lists[row])) {
            moveFront(A->lists[row]);
            while (index(A->lists[row]) != -1) {
                Entry T = get(A->lists[row]);
                changeEntry(M, row, getCol(T), getValue(T));
                moveNext(A->lists[row]);
            }
            continue;
        } else if (isEmpty(A->lists[row])) {
            moveFront(B->lists[row]);
            while (index(B->lists[row]) != -1) {
                Entry K = get(B->lists[row]);
                changeEntry(M, row, getCol(K), -(getValue(K)));
                moveNext(B->lists[row]);
            }
            continue;
        }
        col = 0;
        //int length_a = length(A->lists[row]);
        //int length_b = length(B->lists[row]);
        //int max_len = (length_a > length_b) ? length_a : length_b;
        moveFront(A->lists[row]); 
        moveFront(B->lists[row]); 
        while (col < n) {
            col += 1;
            if (index(A->lists[row]) != -1) {
                Entry X = get(A->lists[row]);
                if (getCol(X) == col) {
                    val += getValue(X);
                    moveNext(A->lists[row]);
                }
            }
            if (index(B->lists[row]) != -1) {
                Entry Y = get(B->lists[row]);
                if (getCol(Y) == col) {                
                    val -= getValue(Y);
                    moveNext(B->lists[row]);
                }
            }
            if (val != 0) {
                changeEntry(M, row, col, val);
            }
            val = 0;
        }
    }
    return M;
}


Matrix product(Matrix A, Matrix B) {
    if (A==NULL || B == NULL) {
        printf("Matrix Error: calling diff() on NULL List reference\n");
     	exit(EXIT_FAILURE);
    }
    if (size(A) != size(B)) {
        printf("Wrong sizes in diff");
        exit(EXIT_FAILURE);
    }
    int n = size(A);
    Matrix T = transpose(B);
    Matrix M = newMatrix(n);
    double dotProduct = 0;
    for (int row = 1; row <= size(A); row++) {
        for (int j = 1; j <= size(A); j++) {
            if (isEmpty(A->lists[row]) || isEmpty(T->lists[j])) {
                continue;
            }   
            int col = 0;
            moveFront(A->lists[row]);
            moveFront(T->lists[j]);
            //int length_a = length(A->lists[row]);
            //int length_t = length(T->lists[j]);
            //int max_len = (length_a > length_t) ? length_a : length_t;
            while (col < n) {
                col += 1;
                if (index(A->lists[row]) == -1 || index(T->lists[j]) == -1) {
                    break;
                }
                Entry X = get(A->lists[row]);
                Entry Y = get(T->lists[j]);
                if (getCol(X) == col && getCol(Y) == col) {
                    dotProduct += getValue(X) * getValue(Y);
                    moveNext(A->lists[row]);
                    moveNext(T->lists[j]);
                }
                else if (getCol(X) == col && getCol(Y) != col) {
                    moveNext(A->lists[row]);
                }
                else if (getCol(Y) == col && getCol(X) != col) {
                    moveNext(T->lists[j]);
                }
                else {
                    continue;
                }
                
            }
            if (dotProduct != 0) {
                changeEntry(M, row, j, dotProduct);
            }
            dotProduct = 0;
        }
    }
    freeMatrix(&T);
    return M;
}



// Other Functions ------------------------------------------------------------

void printMatrix(FILE *out, Matrix M){
    if(M==NULL ){
        printf("Matrix Error: calling printMatrix() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }

    if (NNZ(M) == 0) {
        return;
    }

    for (int i = 1; i <= size(M); i++) {
        if (isEmpty(M->lists[i])) {
            continue;        
        } else {
           fprintf(out, "%d: ", i);
        }
        moveFront(M->lists[i]);
        while (index(M->lists[i]) != -1) {
            printEntry(out, get(M->lists[i]));
            moveNext(M->lists[i]);
        }
        fprintf(out, "\n");
    }
}

