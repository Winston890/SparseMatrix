#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 2
# all					 makes all
# make                   makes all
# make MatrixTest        makes MatrixTest
# make Sparse            makes Sparse
# make clean             removes all binaries
#------------------------------------------------------------------------------

all: Sparse MatrixTest


Sparse : Sparse.o List.o Matrix.o
	gcc -std=c17 -Wall -o Sparse Sparse.o Matrix.o List.o

Sparse.o : Sparse.c List.h Matrix.h
	gcc -std=c17 -Wall -c Sparse.c

MatrixTest : MatrixTest.o List.o Matrix.o
	gcc -std=c17 -Wall -o MatrixTest MatrixTest.o Matrix.o List.o

MatrixTest.o : MatrixTest.c List.h Matrix.h
	gcc -std=c17 -Wall -c MatrixTest.c

List.o : List.c List.h
	gcc -std=c17 -Wall -c List.c

Matrix.o : Matrix.c Matrix.h
	gcc -std=c17 -Wall -c Matrix.c

clean :
	rm -f List.o Sparse Sparse.o MatrixTest.o MatrixTest Matrix.o


