#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <iterator> 
#include <sstream>
#include <math.h>
#include <stdexcept>
#include <ctime>
#include <chrono>
#include<pthread.h>

using namespace std;

vector<vector<float>> tempmat1;
vector<vector<float>> tempmat2;
vector<vector<float>> tempmat3;
int r = 0;

using std::exception;
using std::ofstream;
using std::cout; using std::cerr;
using std::endl; using std::string;
using std::ifstream; using std::vector;
using namespace std::chrono;

/*
This code writes 7 files, each containing 3 columns; n(size of matrix) , Average time and Standard Dev corresponding to that n
The files are named "ClassicMult.txt", "1Thread.txt", "2Threads.txt", "3Threads.txt", "4Threads.txt", "openblas.txt" and "MKL.txt"

Before running:
The functions below operate on vector of vectors type matrices.
If the need be, convert to and fro array of arrays by inserting the "toVectorVectors" and "toArrayArrays" blocks where.
    
The function timesForClassic outputs vector of 3 vectors, size and corresponding avg and std
The functions timesForpThread, timesForopenblas, timesForMKL are similar to timesForClassic

Please make the function call for these 3 variants compatible with your code, I have commented them in the functions here


To run: include above "#include ....." and "using std...." commands from above
        you have to include the flag "-std=c++11" to make the compiler run
*/


//this block may be used to convert an array array matrix to vector of vectors matrix, by inserting where the need be
// toVectorVectors : float mat[][]) -> vector< vector<float> > out

/*  
    int nr1 =  sizeof(mat)/sizeof(mat[0]);
    int nc1 = sizeof(mat)/(sizeof(int)*nr1);
    vector<vector <float> > out;
    for(int i=0; i<nr1; i++){
        vector<float> row;
        out.push_back(row);
        for(int j=0; j<nc1; j++){
             out.at(i).push_back(mat[i][j]);
            }
    }
*/

//this block may be used to convert a vector of vectors matrix to an array of arrays matrix, by inserting where the need be
// toArrayArrays : vector< vector<float> > mat -> float[][] out

/*
    int nr1= mat.size();
    int nc1= mat.at(0).size();
    float out[nr1][nc1];
    for(int i=0; i<nr1; i++){
        for(int j=0; j<nc1; j++){
             out[i][j]=mat.at(i).at(j);
            }
    }
*/


//generates a n x n matrix with random entries from [0,100]
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
vector< vector<float> > randMatrix(int n){   
    vector< vector<float> > out;      //out[i][j] represents ith row jth column
    srand (static_cast <unsigned> (time(0)));
    for(int i =0; i <n; i++){
        vector<float> s;
        for (int j=0; j<n; j++){
            float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            s.push_back(r*100.0);
        }
        out.push_back(s);
    }
return out;
}

vector< vector<float> > zeroMatrix(int n){   
    vector< vector<float> > out;      //out[i][j] represents ith row jth column
    for(int i =0; i <n; i++){
        vector<float> s;
        for (int j=0; j<n; j++){
            float r = 0;
            s.push_back(r);
        }
        out.push_back(s);
    }
return out;
}
//standard multiplication of matrices algorithm
vector< vector<float> > ClassicMult( vector< vector<float> > m1, vector< vector<float> > m2){
    int nr1= m1.size();
    int nc1= m1.at(0).size();
    int nr2= m2.size();
    int nc2= m2.at(0).size();
    vector<vector <float> > out;
    for(int i=0; i<nr1; i++){
        vector<float> row;
        out.push_back(row);
        for(int j=0; j<nc2; j++){
             out.at(i).push_back(0.0);
            }
    }

    for(int i=0; i<nr1; i++){
        for(int j=0; j<nc2; j++){
            for(int k=0; k<nc1; k++){
                out.at(i).at(j) += m1.at(i).at(k)*m2.at(k).at(j);
            }
        }
    }

    return out;
}

void fullyconnectedopenblas(string inmat, string wtmat, string biasmat, string outmat){
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



  

//outputs a vector of 3 vectors, the size of the matrix, the average and the standard deviation for that size
vector< vector<float> > timesForClassic(){
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    vector< vector <float> > out;
    vector <float> ns;
    vector <float> avgs;
    vector <float> stds;

    
    for(int size=1; size< 70; size++){
        float times=0;
        float timesSq=0;
        for(int i=0;i<100;i++){
            vector< vector<float> > m1= randMatrix(size);
            vector< vector<float> > m2= randMatrix(size);
            auto start = high_resolution_clock::now();
            
            vector< vector<float> > out= ClassicMult(m1, m2);

            auto end = high_resolution_clock::now();
            duration<float, std::milli> ms_float = end-start;
            times+= ms_float.count();
            timesSq+= ms_float.count()*ms_float.count();
        }
        float avgN= times/100;
        float standardDevN = sqrt(timesSq/100 - avgN*avgN);

        ns.push_back(static_cast< float >(size));
        avgs.push_back(avgN);
        stds.push_back(standardDevN);
    }
    out.push_back(ns);
    out.push_back(avgs);
    out.push_back(stds);
    return out;
}

//outputs a vector of 3 vectors, the size of the matrix, the average and the standard deviation for that size
vector< vector<float> > timesForpThread(){
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    vector< vector <float> > out;
    vector <float> ns;
    vector <float> avgs;
    vector <float> stds;

    
    for(int size=1; size< 70; size++){
        float times=0;
        float timesSq=0;
        for(int i=0;i<100;i++){
            vector< vector<float> > m1= randMatrix(size);
            vector< vector<float> > m2= randMatrix(size);
            vector< vector<float> > zero = zeroMatrix(size);
            auto start = high_resolution_clock::now();
            
            vector< vector<float> > out= fullyconnectedpthread( m1, m2, zero);
            
            auto end = high_resolution_clock::now();
            duration<float, std::milli> ms_float = end-start;
            times+= ms_float.count();
            timesSq+= ms_float.count()*ms_float.count();
        }
        float avgN= times/100;
        float standardDevN = sqrt(timesSq/100 - avgN*avgN);

        ns.push_back(static_cast< float >(size));
        avgs.push_back(avgN);
        stds.push_back(standardDevN);
    }
    out.push_back(ns);
    out.push_back(avgs);
    out.push_back(stds);
    return out;
}

//outputs a vector of 3 vectors, the size of the matrix, the average and the standard deviation for that size
vector< vector<float> > timesForopenblas(){
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    vector< vector <float> > out;
    vector <float> ns;
    vector <float> avgs;
    vector <float> stds;

    
    for(int size=1; size< 70; size++){
        float times=0;
        float timesSq=0;
        for(int i=0;i<100;i++){
            vector< vector<float> > m1= randMatrix(size);
            vector< vector<float> > m2= randMatrix(size);
            vector< vector<float> > zero= zeroMatrix(size);
            writematrix(m1, "a");
            writematrix(m2, "b");
            writematrix(zero, "c");
            auto start = high_resolution_clock::now();
            
            //fullyconnectedopenblas("a", "b", "c");
            
            auto end = high_resolution_clock::now();
            duration<float, std::milli> ms_float = end-start;
            times+= ms_float.count();
            timesSq+= ms_float.count()*ms_float.count();
        }
        float avgN= times/100;
        float standardDevN = sqrt(timesSq/100 - avgN*avgN);

        ns.push_back(static_cast< float >(size));
        avgs.push_back(avgN);
        stds.push_back(standardDevN);
    }
    out.push_back(ns);
    out.push_back(avgs);
    out.push_back(stds);
    return out;
}

//outputs a vector of 3 vectors, the size of the matrix, the average and the standard deviation for that size
vector< vector<float> > timesForMKL(){
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    vector< vector <float> > out;
    vector <float> ns;
    vector <float> avgs;
    vector <float> stds;

    
    for(int size=1; size< 70; size++){
        float times=0;
        float timesSq=0;
        for(int i=0;i<100;i++){
            vector< vector<float> > m1= randMatrix(size);
            vector< vector<float> > m2= randMatrix(size);
            auto start = high_resolution_clock::now();
            
            //vector< vector<float> > out= MKL(m1, m2);
            
            auto end = high_resolution_clock::now();
            duration<float, std::milli> ms_float = end-start;
            times+= ms_float.count();
            timesSq+= ms_float.count()*ms_float.count();
        }
        float avgN= times/100;
        float standardDevN = sqrt(timesSq/100 - avgN*avgN);

        ns.push_back(static_cast< float >(size));
        avgs.push_back(avgN);
        stds.push_back(standardDevN);
    }
    out.push_back(ns);
    out.push_back(avgs);
    out.push_back(stds);
    return out;
}


void fileCreator( string name){
    

    ofstream file;
    file.open(name ,ios::out|ios::trunc);
    if(!file){cout<<"Error in creating file!!!";}
    cout<<"File created successfully." << "\n";

    cout<< "Running Classic Multiplication Algorithm" << endl;
    vector< vector <float> > classicData = timesForClassic();

    cout<< "Running Multiplication using pthreads" << endl;
    vector< vector <float> > pThreadData = timesForpThread();

    cout<< "Running Multiplication via openblas" << endl;
    vector< vector <float> > openblasData = timesForopenblas();

    cout<< "Running Multiplication via MKL" << endl;
    vector< vector <float> > MKLData = timesForMKL();
    
    
    int n= classicData.at(0).size();

    for(int i=0; i<n; i++){file << classicData.at(0).at(i) << " " << classicData.at(1).at(i) << " " << classicData.at(2).at(i) << " " << pThreadData.at(1).at(i) << " " << pThreadData.at(2).at(i) << " " << openblasData.at(1).at(i) << " " << openblasData.at(2).at(i) << MKLData.at(1).at(i) << " " << MKLData.at(2).at(i) <<"\n";}
    file.close();

}

int main(){

    fileCreator("Data.txt");
    return 0;
}