#include<iostream>
#include<fstream>
#include<cstring>
#include<vector>
#include<cmath> 
#include <cfloat>
#include<thread>
#include<bits/stdc++.h>
#include<pthread.h>
#include<algorithm>


#include <string>
#include <string.h>
#include <iterator> 

#include <cstdio>
#include <sstream>
#include <cstdlib>
#include <math.h>
#include <stdexcept>

using namespace std;
using std::exception;
using std::ofstream;
using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::vector;

typedef struct{
    int label;
    float prob;
}pred_t;

vector<vector<float>> tempmat1;
vector<vector<float>> tempmat2;
vector<vector<float>> tempmat3;
int r = 0;
int numthrds = 8;

vector<vector<float>> readmatrix(string filename, int numrow, int numcol){
	
	ifstream file;
	file.open(filename);
	
	/*throwing error if file can't be opened*/
	if(file.fail()){
		cout << "Couldn't open file\n";
	}

	vector<vector<float>> vec(numrow,vector<float>(numcol,0));
	
	for(int i=0; i< numrow;i++){
		for(int j=0; j< numcol; j++){
			/*storing contents from file as a vector of vectors of floats*/
			file >> vec[i][j];
			/*decreasing count as one less line to read now*/
			
		}
	}

	/*returning the matrix*/
	return vec;
}

vector<float> inputF(string file){
    //creates a vector from the audio feature file
    string filename(file);
    vector<string> lines;
    string line;

    ifstream input_file(filename);
    if (!input_file.is_open()) {
         throw std::invalid_argument("File not found!");
    }
    getline(input_file, line);
    input_file.close();

    vector<float> v; 
    int n=line.size();
    string hh="";
    for(int i=0; i< n+1; i++){
        if(i==n || line[i]==' '){
            float hehe= std::stof(hh);
            v.push_back(hehe);
            hh="";
        }
        else{hh= hh+ line[i];}
    }
return v;
}

void* rowmult(void* arg){

	int load = tempmat3.size()/numthrds;
	int remainder = tempmat3.size()%numthrds;
	
	
	if(r == 0){
		for (int i = 0; i < remainder; i++){   
			for(int j=0; j< (int)tempmat2[0].size();j++){
				for(int k=0; k< (int)tempmat2.size(); k++){
					tempmat3[i][j] += tempmat1[i][k]*tempmat2[k][j];
				}
			}	
		}
	}
	else{
		for (int i = (r-1)*load + remainder; i < r*load + remainder; i++){   
			for(int j=0; j< (int)tempmat2[0].size();j++){
				for(int k=0; k< (int)tempmat2.size(); k++){
					tempmat3[i][j] += tempmat1[i][k]*tempmat2[k][j];
				}
			}	
		}
	}
	
	r += 1;
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
	r = 0;
	return tempmat3;
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

vector<float> probs(string s){

  vector<float> haha= inputF(s);
  
  vector<vector<float> > hehe;
  hehe.push_back(haha);

  vector<vector<float> > FC1b = readmatrix("FC1b.txt", 1 ,144);
  vector<vector<float> > FC2b = readmatrix("FC2b.txt", 1 ,144);
  vector<vector<float> > FC3b = readmatrix("FC3b.txt", 1 ,144);
  vector<vector<float> > FC4b = readmatrix("FC4b.txt", 1 ,12);
  
  vector<vector<float> > FC1w = readmatrix("FC1w.txt", 250 ,144);
  vector<vector<float> > FC2w = readmatrix("FC2w.txt", 144 ,144);
  vector<vector<float> > FC3w = readmatrix("FC3w.txt", 144,144);
  vector<vector<float> > FC4w = readmatrix("FC4w.txt", 144,12);
  
  vector<vector<float> > I1 = fullyconnectedpthread(hehe, FC1w, FC1b);
  vector<vector<float> > I2 = relu(I1);
  vector<vector<float> > I3 = fullyconnectedpthread(I2, FC2w, FC2b);
  vector<vector<float> > I4 = relu(I3);
  vector<vector<float> > I5 = fullyconnectedpthread(I4, FC3w, FC3b);
  vector<vector<float> > I6 = relu(I5);
  vector<vector<float> > I7 = fullyconnectedpthread(I6, FC4w, FC4b);
  vector<float> final = I7.at(0);
  vector<float> answer = softmax(final); 
/*
  cout<< answer.at(0) << endl;
  cout<< answer.at(1) << endl;
  cout<< answer.at(2) << endl;
  cout<< answer.at(3) << endl;
  cout<< answer.at(4) << endl;
  cout<< answer.at(5) << endl;
  cout<< answer.at(6) << endl;
  cout<< answer.at(7) << endl;
  cout<< answer.at(8) << endl;
  cout<< answer.at(9) << endl;
  cout<< answer.at(10) << endl;
  cout<< answer.at(11) << endl;
*/
  return answer;

}

pred_t* libaudioAPI(const char* audiofeatures, pred_t* pred){
	vector <float> AF = probs (string(audiofeatures));

	float max = 0;
	int pos = -1;
	for(int i = 0; i< 12; i++){
		if(AF[i] > max){
			pos = i;
			max = AF[i];
		}
	}
	
	pred[0].prob = max;
	pred[0].label = pos;
	AF[pos] = -1;
	
	max = 0;
	pos = -1;
	for(int i = 0; i< 12; i++){
		if(AF[i] > max){
			pos = i;
			max = AF[i];
		}
	}
	
	pred[1].prob = max;
	pred[1].label = pos;
	AF[pos] = -1;
	
	max = 0;
	pos = -1;
	for(int i = 0; i< 12; i++){
		if(AF[i] > max){
			pos = i;
			max = AF[i];
		}
	}
	
	pred[2].prob = max;
	pred[2].label = pos;
	
	return pred;
}



