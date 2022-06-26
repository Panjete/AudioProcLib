#include<iostream>
#include<fstream>
#include<cstring>
#include<vector>
#include<cmath> 
#include <cfloat>
#include<thread>
#include "mkl.h"
#include<bits/stdc++.h>
#include<pthread.h>



/*./yescode.out fullyconnected a1a.inputmatrix.txt a1a.weightmatrix.txt a1a.biasmatrix.txt kartik.txt*/
/*./yescode.out fullyconnected mkl a1a.inputmatrix.txt a1a.weightmatrix.txt a1a.biasmatrix.txt kartik.txt*/
/*./yescode.out fullyconnected pthread a1a.inputmatrix.txt a1a.weightmatrix.txt a1a.biasmatrix.txt kartik.txt*/

using namespace std;
/*numline calculates number of line in a file*/
vector<vector<float>> tempmat1;
vector<vector<float>> tempmat2;
vector<vector<float>> tempmat3;
int r = 0;

int numline(string filename){
	int count =0;
	string line;
	ifstream file;
	file.open(filename);
	while(getline(file,line)){
	/*count is the number of lines read*/
		count ++;
	}
	/*returning count when file has no more line to read*/
	return count;
}
vector<float> readvector (string filename){
	/*Reads a vector from a file where where line contains the number of elements in the vector
	and sebsequent lines have the vector elements*/
	int count = numline(filename);
	ifstream file;
	file.open(filename);
	int len;
	/*error if file can't be opened*/
	if(file.fail()){
		cout << "Couldn't open file\n";
	}
	
	file >> len;
	count--;
	/*count = number of lines to be read
	so, after every read, decrease it by one*/
	vector<float> vec(len,0);
	
	for(int i =0; i<len; i++){
		/*reading the file and storing the content in a vector*/
		file >> vec[i];
		count--;
	}
	/*checking validity of file content*/
	if (count!=0) cout << "File content not according to rule\n";
	/*return the vector*/
	return vec;
}
vector<vector<float>> readmatrix(string filename){
	/*reads a matrix from a file as a vector of vectors
	file has numcol, numrows and then elements, column major order, in subsequent lines*/
	int count = numline(filename);
	ifstream file;
	file.open(filename);
	int numrow, numcol;
	/*throwing error if file can't be opened*/
	if(file.fail()){
		cout << "Couldn't open file\n";
	}

	file >> numcol >> numrow;
	count -= 2;
	vector<vector<float>> vec(numrow,vector<float>(numcol,0));
	for(int j=0; j< numcol;j++){
		for(int i=0; i< numrow; i++){
			/*storing contents from file as a vector of vectors of floats*/
			file >> vec[i][j];
			/*decreasing count as one less line to read now*/
			count--;
		}
	}
	/*checking validity of file content*/
	if (count!=0) cout << "File content not according to rule\n";
	/*returning the matrix*/
	return vec;
}
void writevector(vector<float> outvec, string filename){
	/*to print a vector in a file*/
	ofstream file;
	file.open(filename);
	/*opening file to write in*/
	if(file.fail()){
		cout << "Couldn't open file\n";
	}
	/*prinitng number of elements in the vector*/
	file << outvec.size() << endl;
	for(int j=0; j< (int)outvec.size(); j++){
		/*prinitng the elements of the vector*/
		file << outvec[j] << endl;
	}
}
void writematrix(vector<vector<float>> outmat, string filename){
	/*to print a matrix in a file*/
	ofstream file;
	file.open(filename);
	/*opening file to write in*/
	if(file.fail()){
		cout << "Couldn't open file\n";
	}
	/*printing number of columns*/
	file << outmat[0].size() << endl; 
	/*printing number of rows*/
	file << outmat.size() << endl;
	for(int j=0; j<  (int)outmat[0].size(); j++){
		for(int i=0; i< (int)outmat.size(); i++){
			/*printing the elements of the matrix in a column major order*/
			file << outmat[i][j] << endl;
		}
	}
}
void fullyconnectedmkl(string inmat, string wtmat, string biasmat, string outmat){
	/*reading input matrix*/
	ifstream file1;
	file1.open(inmat);
	
	int row1, col1;
	/*error if file can't be opened*/
	if(file1.fail()){
		cout << "Couldn't open file\n";
	}
	float* inmatrix= new float[row1*col1];
	
	file1 >> col1 >> row1;
	for (int i=0 ;i< col1*row1; i++){
		file1 >> inmatrix[i];
	}
	/*reading weight matrix*/
	ifstream file2;
	file2.open(wtmat);
	
	int row2, col2;
	/*error if file can't be opened*/
	if(file2.fail()){
		cout << "Couldn't open file\n";
	}
	float* wtmatrix= new float[row2*col2];
	
	file2 >> col2 >> row2;
	for (int i=0 ;i< col2*row2; i++){
		file2 >> wtmatrix[i];
	}
	/*reading bias matrix*/
	ifstream file3;
	file3.open(biasmat);
	
	int row3, col3;
	/*error if file can't be opened*/
	if(file3.fail()){
		cout << "Couldn't open file\n";
	}
	float* biasmatrix= new float[row3*col3];
	
	file3 >> col3 >> row3;
	for (int i=0 ;i< col3*row3; i++){
		file3 >> biasmatrix[i];
	}
	
	/*
	cout << row1 << col1 << endl;
	cout << row2 << col2 << endl;
	cout << row3 << col3 << endl;*/
	
	cblas_sgemm(CblasColMajor,CblasNoTrans,CblasNoTrans,row1,col2,col1,1.0,inmatrix,row1,wtmatrix,row2,1.0,biasmatrix,row3);
	
	
	
	ofstream file;
	file.open(outmat);
	
	file << col3 << endl;
	file << row3 << endl;
	for (int i=0; i<row3*col3; i++){
		file << biasmatrix[i] << endl;
	}

}

void* rowmult(void* arg){
	int i = r++;
	if(i< (int)tempmat3.size()){
		for(int j=0; j< (int)tempmat2[0].size();j++){
			for(int k=0; k< (int)tempmat2.size(); k++){
				tempmat3[i][j] += tempmat1[i][k]*tempmat2[k][j];
			}
		}
	}
}
vector<vector<float>> fullyconnectedpthread(vector<vector<float>> inmat, vector<vector<float>> wtmat, vector<vector<float>> bias){	
	/*essentially return inmat*wtmat + bias */
	/*check for any dimension mismatch*/
	if(inmat[0].size() != wtmat.size() || inmat.size() != bias.size() || wtmat[0].size() != bias[0].size()){
		cout << "Wrong Matrix Dimensions\nPlease Recheck\n";
	}
	/*row column matrix multiplication ad adding elements of bias*/
	tempmat1 = inmat;
	tempmat2 = wtmat;
	tempmat3 = bias;
	
	pthread_t thrds[bias.size()];
	
	for (int i= 0; i< (int)tempmat1.size(); ++i){
		int* c;
		pthread_create(&thrds[i],NULL,rowmult,(void*)(c));
	}
	
	for(int i=0; i< (int)inmat.size(); ++i){
		pthread_join(thrds[i],NULL);
	}	
		
	return tempmat3;
}

vector<vector<float>> fullyconnected(vector<vector<float>> inmat, vector<vector<float>> wtmat, vector<vector<float>> bias){	
	/*essentially return inmat*wtmat + bias */
	/*check for any dimension mismatch*/
	if(inmat[0].size() != wtmat.size() || inmat.size() != bias.size() || wtmat[0].size() != bias[0].size()){
		cout << "Wrong Matrix Dimensions\nPlease Recheck\n";
	}
	/*row column matrix multiplication ad adding elements of bias*/
	vector<vector<float>> out(bias.size(),vector<float>(bias[0].size(),0));
	
	for(int i = 0; i< (int)inmat.size(); i++){
		for(int j = 0; j< (int)wtmat[0].size(); j++){
			/*storing elements of bias in out and then adding matrix multiplication*/
			out[i][j] = bias[i][j];
			for(int k= 0; k< (int)wtmat.size(); k++){
				out[i][j] += inmat[i][k]*wtmat[k][j];
			}
		}
	}
	return out;
} 
vector<vector<float>> relu(vector<vector<float>> inmat){
	/*relu matrix function essentially maps relu on every element*/
	for(int j=0; j< (int)inmat[0].size();j++){
		for(int i=0; i< (int)inmat.size(); i++){
			/*i.e. replace by 0 if negative*/
			if(inmat[i][j] < 0){
				inmat[i][j]=0;
			}
		}
	}
	return inmat;
}	
float tanhyp(float x){
/*defining tanh function on 32 bit float*/
	float a = exp(2*x);
	return (a-1)/(a+1);
}
vector<vector<float>> matrixtanh(vector<vector<float>> inmat){
	/*mapping tanh on the matrix*/
	for(int j=0; j< (int)inmat[0].size();j++){
		for(int i=0; i< (int)inmat.size(); i++){
			inmat[i][j] = tanhyp(inmat[i][j]);
		}
	}
	return inmat;
}	

vector<vector<float>> avgpool(vector<vector<float>> inmat, int stride){
	vector<vector<float>> out(inmat.size()/stride,vector<float>(inmat.size()/stride,0));
	/*throw an error if matrix size is not a multiple of stride*/
	if(inmat.size()%stride != 0){
		cout << "matrix size is not a multiple of stride\n";
		return out ;
	}
	for (int i=0; i<  (int)inmat.size(); i+=stride){
		for (int j=0; j<  (int)inmat.size(); j+=stride){
			/*sum elements of every subsection*/
			for(int k=i; k<i+stride; k++){
				for (int l=j; l<j+stride; l++){
					out[i/stride][j/stride] += inmat[k][l];
				}
			} 
			/*and after summing divide by stride^2 i.e. number of elements in each subsection*/
			out[i/stride][j/stride] /= (stride*stride);
		}	
	}	
	return out;
}
vector<vector<float>> maxpool(vector<vector<float>> inmat, int stride){
	vector<vector<float>> out(inmat.size()/stride,vector<float>(inmat.size()/stride,-FLT_MAX));
	/*initializing each element of out as float_minimum and then comparing with elements from inmat*/
	/*throw an error if matrix size is not a multiple of stride*/
	if(inmat.size()%stride != 0){
		cout << "matrix size is not a multiple of stride\n";
		return out ;
	}
	for (int i=0; i<  (int)inmat.size(); i+=stride){
		for (int j=0; j<  (int)inmat.size(); j+=stride){
			/*compare with elements of subsection of inmat and replace whenever a larger element is found in inmat*/
			for(int k=i; k<i+stride; k++){
				for (int l=j; l<j+stride; l++){
					/*replace if larger*/
					if(out[i/stride][j/stride] < inmat[k][l]){
						out[i/stride][j/stride] = inmat[k][l];
					}	
				}
			} 
		}	
	}	
	return out;
}

vector<float> sigmoid(vector<float> invec){
	/*sigmoid(x) = 1/(1+exp(-x)) */
	/*mapping sigmoid on elements of vector*/
	for(int i= 0; i<  (int)invec.size(); i++){
		invec[i] = 1/(1+exp(-invec[i]));
	}
	return invec;
}
vector<float> softmax(vector<float> invec){
	/*softmax(x)= exp(x)/ sumof(exp(xi)) */
	float sum=0;
	/*summing up exponentials and mapping exp to vector*/
	for(int i= 0; i<  (int)invec.size(); i++){
		invec[i] = exp(invec[i]);
		sum += invec[i];
	}
	/*divide each element by sum which is the sum of exponentials of all elements*/
	for(int i= 0; i< (int)invec.size(); i++){
		invec[i] /= sum;
	}
	return invec;
}


int main(int argc, char** argv){
	/*branching to the case as required from input*/
	/*argc is the number of arguments and argv is a pointer to arguments*/
	if (argc == 7 && strcmp(argv[1],"fullyconnected")==0 && strcmp(argv[2],"mkl")==0){
		fullyconnectedmkl(argv[3],argv[4],argv[5],argv[6]);
		return 0;
	}
	else if (argc == 7 && strcmp(argv[1],"fullyconnected")==0 && strcmp(argv[2],"pthread")==0){
		vector<vector<float>> inmat = readmatrix(argv[3]);
		vector<vector<float>> wtmat = readmatrix(argv[4]);
		vector<vector<float>> bias = readmatrix(argv[5]);
		vector<vector<float>> outmat= fullyconnectedpthread(inmat,wtmat,bias);
		writematrix(outmat,argv[6]);
		return 0;
	}
	else if (argc == 6 && strcmp(argv[1],"fullyconnected")==0){
		vector<vector<float>> inmat = readmatrix(argv[2]);
		vector<vector<float>> wtmat = readmatrix(argv[3]);
		vector<vector<float>> bias = readmatrix(argv[4]);
		vector<vector<float>> outmat= fullyconnected(inmat,wtmat,bias);
		writematrix(outmat,argv[5]);
		return 0;
	}
	else if (argc == 5 && strcmp(argv[1],"activation")==0 && strcmp(argv[2],"relu")==0){
		vector<vector<float>> inmat = readmatrix(argv[3]);
		writematrix(relu(inmat),argv[4]);	
		return 0;
	}
	else if (argc == 5 && strcmp(argv[1],"activation")==0 && strcmp(argv[2],"tanh")==0){
		vector<vector<float>> inmat = readmatrix(argv[3]);
		writematrix(matrixtanh(inmat),argv[4]);	
		return 0;
	}
	else if (argc == 6 && strcmp(argv[1],"pooling")==0 && strcmp(argv[2],"max")==0){
		vector<vector<float>> inmat = readmatrix(argv[3]);
		int stride = stoi(argv[4]);
		writematrix(maxpool(inmat,stride),argv[5]);	
		return 0;
	}
	else if (argc == 6 && strcmp(argv[1],"pooling")==0 && strcmp(argv[2],"average")==0){
		vector<vector<float>> inmat = readmatrix(argv[3]);
		int stride = stoi(argv[4]);
		writematrix(avgpool(inmat,stride),argv[5]);	
		return 0;
	}
	else if (argc == 5 && strcmp(argv[1],"probability")==0 && strcmp(argv[2],"softmax")==0){
		vector<float> invec = readvector(argv[3]);
		writevector(softmax(invec),argv[4]);
		return 0;
	}
	else if (argc == 5 && strcmp(argv[1],"probability")==0 && strcmp(argv[2],"sigmoid")==0){
		vector<float> invec = readvector(argv[3]);
		writevector(sigmoid(invec),argv[4]);
		return 0;
	}
	else{
		/*error in cmd line if no case matched*/
		cout << "Wrong Command Line Arguments\nPlease Recheck\n" ;  
	}

	return 0;
	
}
