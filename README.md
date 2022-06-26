# Audio Processing Library

## Subtask 1

The file "2020CS50426.cpp" is the file that houses all the functions.  
It can be operated using the "make" from the "Makefile" as follows. 

1) Direct the terminal to the directory containing these 2 files.  
2) Type "make" to compile the file and get the executable file "yourcode.out". 
3) Then, input whatever files you may want and whatever operation you may want to perform on them.  
4) If the files are found, and the data they contain are compatible, the output file is created. If not, we exit gracefully.  

## Subtask 2

he following commands in the command line will give the desired output. 

./yourcode.out activation relu inputmatrix.txt outputmatrix.txt</br>
./yourcode.out activation tanh inputmatrix.txt outputmatrix.txt</br>
./yourcode.out pooling max inputmatrix.txt stride outputmatrix.txt</br>
./yourcode.out pooling average inputmatrix.txt stride outputmatrix.txt</br>
./yourcode.out probability softmax inputvector.txt outputvector.txt</br>
./yourcode.out probability sigmoid inputvector.txt outputvector.txt</br>

./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt</br>
./yourcode.out fullyconnected openblas inputmatrix.txt weightmatrix.txt biasmatrix.txt</br>t
./yourcode.out fullyconnected pthread inputmatrix.txt weightmatrix.txt biasmatrix.txt</br>

./alternate.out fullyconnected mkl inputmatrix.txt weightmatrix.txt biasmatrix.txt


To clear all executable files:</br>
	1) open terminal in th folder</br>
	2) make clean</br>

Errors:
	All errors are printed on the console, and exited gracefully.</br>


This part of the assignment modifies the previous part, and includes the methods of multiplication like rowmult, openblas, mkl and pthreads for the "fullyconnected" version.</br>

The mkl and openblas files were not running on our stations, so we collected the syntax from the internet and managed to the best extent we could.</br>
The graph can be generated using the load 'graphGNU.p' command from the terminal.</br>
It houses the data from the pthreads and the classic multiplication, but we could not get the data from the libraries since our systems were incompatible.</br>


The File "graph.cpp" gives the data for average and standard deviation of the classic multiplication, pthread, openblas and mkl variants.</br>

We then use this data, run a GNUplot script on it, and obtain the attached graph.</br>

## Subtask 3

This submission contains the Library files, the code that uses the library, and the trained weights and bias data for the matrices.</br>

Commands used for creating the library are commented in the makefile. Please change the path to library as per your system.</br>

To recognise a particular sample, </br>
Place the audiosamplefile in the same directory as the code.</br>
In the terminal, type "make", and the following command in the command line will give the desired output</br>

./yourcode.out audiosamplefile outputfile</br>

This should append keywords with top 3 probabilities in the "outputfile".</br>


To clear all executable files:</br>
    1) open terminal in the folder</br>
    2) make clean</br>

Errors:
    All errors are printed on the console, and exited gracefully.</br>

The fastest implementation of the previous assignment was "pthread" matric multiplication. Changes were made in fullyconnectedpthread function to incorporate flexible number of threads. To optimize efficiency and load, 8 number of threads are being used which divides the rows for execution among them.</br>


- GURARMAAN SINGH PANJETA : 2020CS50426
- KARTIK SHARMA : 2020CS10351 


