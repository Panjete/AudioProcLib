#g++ compiler for C++
CC = g++

all: cblas mkl

#for cblas and all other functions except mkl matrix multiplication -- use "yourcode.out"
cblas:
	$(CC) -Wall ourcode.cpp -o yourcode.out -I /home/kartik/OpenBLAS/include -L /home/kartik/OpenBLAS/lib -lopenblas -lpthread -lgfortran -fopenmp -lm -ldl
	
#for mkl and all other functions except cblas matrix multiplication -- use "yescode.out"
mkl:
	$(CC) -Wall sadacode.cpp -o yescode.out -I /home/kartik/OpenBLAS/include -L /home/kartik/OpenBLAS/lib -lopenblas -lpthread -lgfortran -fopenmp -lm -ldl

clean: 
	rm -rf *.out yourcode.out yescode.out 


