The following commands in the command line will give the desired output

./yourcode.out activation relu inputmatrix.txt outputmatrix.txt
./yourcode.out activation tanh inputmatrix.txt outputmatrix.txt
./yourcode.out pooling max inputmatrix.txt stride outputmatrix.txt
./yourcode.out pooling average inputmatrix.txt stride outputmatrix.txt
./yourcode.out probability softmax inputvector.txt outputvector.txt
./yourcode.out probability sigmoid inputvector.txt outputvector.txt

./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt
./yourcode.out fullyconnected openblas inputmatrix.txt weightmatrix.txt biasmatrix.txt
./yourcode.out fullyconnected pthread inputmatrix.txt weightmatrix.txt biasmatrix.txt

./alternate.out fullyconnected mkl inputmatrix.txt weightmatrix.txt biasmatrix.txt


To clear all executable files:
	1) open terminal in th folder
	2) make clean

Errors:
	All errors are printed on the console, and exited gracefully.


This part of the assignment modifies the previous part, and includes the methods of multiplication like rowmult, openblas, mkl and pthreads for the "fullyconnected" version.

The mkl and openblas files were not running on our stations, so we collected the syntax from the internet and managed to the best extent we could.
The graph can be generated using the load 'graphGNU.p' command from the terminal.
It houses the data from the pthreads and the classic multiplication, but we could not get the data from the libraries since our systems were incompatible.


The File "graph.cpp" gives the data for average and standard deviation of the classic multiplication, pthread, openblas and mkl variants.

We then use this data, run a GNUplot script on it, and obtain the attached graph.