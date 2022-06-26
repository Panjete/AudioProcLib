# COMMAND FOR COMPILING AUDIOAPI.CPP
# g++ -pthread -c -Wall -fpic audioAPI.cpp  -lgfortran -fopenmp -lm -ldl

# COMMAND FOR CREATING A SHARED DYNAMIC LIBRARY LIBAUDIOAPI FROM THE COMPILED CODE
# g++ -shared -o libaudioAPI.so audioAPI.o

# COMMAND FOR ADDING THE PATH TO LIBRARY SO THAT LIBRARY IS IDENTIFIED BY LOADER
# export LD_LIBRARY_PATH=/home/kartik/code/290:$LD_LIBRARY_PATH
# PLEASE CHANGE THE PATH TO LIBRARY DEPENDING ON THE FILE LOCATION IN YOUR SYSTEM

#g++ compiler for C++
CC = g++

all: pthread

pthread: 

	g++ -pthread -L/home/kartik/code/290 -Wall -o yourcode.out yourcode.cpp -laudioAPI
	


clean: 
	rm -rf *.out yourcode.out


