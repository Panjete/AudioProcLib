README 

This submission contains the Library files, the code that uses the library, and the trained weights and bias data for the matrices.

Commands used for creating the library are commented in the makefile. Please change the path to library as per your system.

To recognise a particular sample, 
Place the audiosamplefile in the same directory as the code.
In the terminal, type "make", and the following command in the command line will give the desired output

./yourcode.out audiosamplefile outputfile

This should append keywords with top 3 probabilities in the "outputfile".


To clear all executable files:
    1) open terminal in the folder
    2) make clean

Errors:
    All errors are printed on the console, and exited gracefully.

The fastest implementation of the previous assignment was "pthread" matric multiplication. Changes were made in fullyconnectedpthread function to incorporate flexible number of threads. To optimize efficiency and load, 8 number of threads are being used which divides the rows for execution among them.


- GURARMAAN SINGH PANJETA : 2020CS50426
- KARTIK SHARMA : 2020CS10351 
