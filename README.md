# Audio Processing Library
**Objective Accomplished**- Created an Audio Processing Library (API), called via cpp, that classifies sounds across 12 keywords. The functions used for the implementation of DNN inferencing were optimised and improved across various stages, and the results were neatly compiled. The library is easy to execute with help of the "makefile" framework , and thorough error handling and graceful exiting was incorporated. 

## Stage 1

**Progress** - Implemented functions and layers like a Fully Connected layer (weight and bias matrices), Non-Linear activations(Relu, Tanh), Sub-sampling techniques (MaxPool, AvgPool) , Probablility functions (Softmax, Sigmoid), etc, on matrix and vector elements that would later operate on the audio data in the DNN inferencing framework. Understanding and Linking the concept of a Makefile. Thorough error handling and graceful exiting.

The file "2020CS50426.cpp" is the file that houses all the functions.  
It can be operated using the "make" from the "Makefile" as follows. 

1) Direct the terminal to the directory containing these 2 files.  
2) Type "make" to compile the file and get the executable file "yourcode.out". 
3) Then, the following commands will give the desired outcomes.  

./yourcode.out activation relu inputmatrix.txt outputmatrix.txt</br>
./yourcode.out activation tanh inputmatrix.txt outputmatrix.txt</br>
./yourcode.out pooling max inputmatrix.txt stride outputmatrix.txt</br>
./yourcode.out pooling average inputmatrix.txt stride outputmatrix.txt</br>
./yourcode.out probability softmax inputvector.txt outputvector.txt</br>
./yourcode.out probability sigmoid inputvector.txt outputvector.txt</br>

4) If the files are found, and the data they contain are compatible, the output file is created. If not, we exit gracefully.  

## Stage 2

**Progress** - Accelerated matrix multiplication speed for the fully connected layer, using Linear algebra libraries and Multithreading via pthreads. Measured the mean and standard deviation of latencies of the different implementations, and compiled the results neatly via GNUplot boxplot and error bars.

In addition to the commands from Stage I, The following commands in the command line will give the desired output. 

./yourcode.out fullyconnected inputmatrix.txt weightmatrix.txt biasmatrix.txt</br>
./yourcode.out fullyconnected openblas inputmatrix.txt weightmatrix.txt biasmatrix.txt</br>t
./yourcode.out fullyconnected pthread inputmatrix.txt weightmatrix.txt biasmatrix.txt</br>
./alternate.out fullyconnected mkl inputmatrix.txt weightmatrix.txt biasmatrix.txt

The File "graph.cpp" gives the data for average and standard deviation of the classic multiplication, pthread, openblas and mkl variants.</br>
The graph can be generated using the load  command from the terminal.</br>

We then use this data, run the GNUplot script 'graphGNU.p' on it, and obtain the attached graph.</br>

## Subtask 3

**Progress** - Implemented a Deep Neural Network (DNN) inference for classifying across 12 audio keywords. [1x250] Input features for each 1 second audio sample were provided. The DNN comprises of the most efficient implementations of the following functions, stitched together in the following order -> FC1 [250x144] -> RELU -> FC2 [144x144] -> RELU -> FC3 [144X144] -> RELU -> FC4 [144x12] -> softmax. Given feature vector of a 1 second audio clip, the API (called via cpp) returns the top 3 keywords with highest softmax probabilities.  

This submission contains the Library files, the code that uses the library, and the pre-trained weights and bias data for the matrices.</br>

Commands used for creating the library are commented in the makefile. Please change the path to library as per your system.</br>

To recognise a particular sample, </br>
Place the audiosamplefile in the same directory as the code.</br>
In the terminal, type "make", and the following command in the command line will give the desired output</br>

./yourcode.out audiosamplefile outputfile</br>

This will append keywords with top 3 probabilities in the "outputfile".</br>

The fastest implementation of the previous assignment was "pthread" matric multiplication. Changes were made in fullyconnectedpthread function to incorporate flexible number of threads. To optimize efficiency and load distribution, 8 number of threads were used which divides the rows for execution of operations amongst them.</br>


## A Group Project by- 
- GURARMAAN SINGH PANJETA
- KARTIK SHARMA


