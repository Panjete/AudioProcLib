#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <string.h>
#include <iterator> 
#include <bits/stdc++.h> 
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



vector< vector<float> > inputm(string file){
    //creates matrix, vector(vector) form, where out.at(i).at(j) will refer to the ith row jth column
    string filename(file);
    vector<string> lines;
    string line;

    ifstream input_file(filename);
    if (!input_file.is_open()) {
        throw std::invalid_argument("File not Found!");
    }

    
    while (getline(input_file, line)){
        lines.push_back(line);
       
    }
    input_file.close();
    std::string ncol= lines.at(0);
    int numc = std::stof(ncol);
    std::string nrow= lines.at(1);
    int numr = std::stof(nrow);

    vector< vector<float> > v; 
    int n=lines.size();
    for(int i=0; i<numr; i++){
        vector<float> row;
        v.push_back(row);
    }
    for(int i =2; i< n; i++){
        int r= (i-2)%numr;
        string s= lines.at(i);
        float el = std::stof(s);
        v.at(r).push_back(el);
    }
    
    return v;
}
void outputm(vector<vector<float> > out, string outFname){
 ofstream file;
 int r= out.size();
 int c= out.at(0).size();

 file.open(outFname ,ios::out|ios::trunc);
 if(!file)
   {
       cout<<"Error in creating file!!!";
   }
    cout<<"File created successfully.";
    
    file << c << "\n";
    file << r << "\n";
    for(int j=0; j<c; j++){
        for(int i=0; i<r; i++){
        file << out.at(i).at(j) << "\n";}
    }
    file.close();
}
vector<float> inputv(string file){
    //creates vector form, where out.at(i) will refer to the ith element
    string filename(file);
    vector<string> lines;
    string line;

    ifstream input_file(filename);
    if (!input_file.is_open()) {
         throw std::invalid_argument("File not found!");
    }
    while (getline(input_file, line)){
        lines.push_back(line);
       
    }
    input_file.close();
    std::string ncol= lines.at(0);
    int numc = std::stof(ncol);

    vector<float> v; 
    int n=lines.size();
    // n= col+1
    for(int i=0; i< numc; i++){
        string s= lines.at(i+1);
        float el = std::stof(s);
        v.push_back(el);
    }
return v;
}
void outputv(vector<float> out, string outFname){
 ofstream file;
 int c= out.size();

 file.open(outFname,ios::out|ios::trunc);
 if(!file)
   {
       cout<<"Error in creating file!!!";
   }
    cout<<"File created successfully.";
    
    file << c << "\n";
    for(int j=0; j<c; j++){
        file << out.at(j) << "\n";}
    file.close();
}

void fullyconnected(string s1, string s2, string s3, string s4){
 vector< vector<float> > m1= inputm(s1);
 vector< vector<float> > m2= inputm(s2);
 vector< vector<float> > m3= inputm(s3);
 int nr1= m1.size();
 int nc1= m1.at(0).size();
 int nr2= m2.size();
 int nc2= m2.at(0).size();
 int nr3= m3.size();
 int nc3= m3.at(0).size();
 if(nr1!= nr3 || nc2!= nc3 || nc1!= nr2){throw std::invalid_argument("Matrices not compatible!");}
 // nr1=nr3; nc2=nc3; nc1=nr2

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

 for(int i=0; i<nr3; i++){
     for(int j=0; j<nc3; j++){
         out.at(i).at(j) += m3.at(i).at(j);

     }
    }
    outputm(out, s4);
}

float renu(float n){
    float m;
    if(n<=0){m=0;}
    if(n>0){m=n;}
    return m;
}
float tanhO(float n){
 
    float em = expf(n);
    float em2= em*em;
     float m= (em2-1)/(em2+1);
     return m;
}
void activation(string s1, string type, string s2){
    vector< vector<float> > m1= inputm(s1);
    int nr1= m1.size();
    int nc1= m1.at(0).size();
    vector<vector <float> > out;
    for(int i=0; i<nr1; i++){
            vector<float> row;
            out.push_back(row);
            }
    if(type=="relu"){
        for(int i=0; i<nr1; i++){
            for(int j=0; j<nc1; j++){
                 out.at(i).push_back(renu(m1.at(i).at(j)));
                 }
            }
    }
    if(type=="tanh"){
        for(int i=0; i<nr1; i++){
            for(int j=0; j<nc1; j++){
                 out.at(i).push_back(tanhO(m1.at(i).at(j)));
                 }
            }
    }
    cout << "here" << endl;
    outputm(out, s2);
}

vector<vector<float> > avgpoolcol(vector<vector<float> > mat, int stride){
    vector<vector<float> > outCompCol;
    int n= mat.size();
    
    for(int j=0; j<n; j++){ //i =row, j is column, compression of column size
        vector<float> col;
        float curr=0.0;
        for(int i=0; i<n; i++){
            curr+= mat.at(i).at(j); //i row j col
        if(((i+1)%stride)==0){curr= curr/stride;
                                col.push_back(curr);
                                curr=0.0;}
        }
        outCompCol.push_back(col);
    }
    return outCompCol; //whose [i][j] represents the ith column, jth row
}
vector<vector<float> > avgpoolrow(vector<vector<float> > mat, int stride){
    vector<vector<float> > outCompRow;
    int ncols= mat.size();
    int nrows= mat.at(0).size();
    
    for(int i=0; i<nrows; i++){ //ith column jth row, compression of rows
        vector<float> row;
        float curr=0.0;
        for(int j=0; j<ncols; j++){
            curr+= mat.at(j).at(i); 
            
        if(((j+1)%stride)==0){curr/= stride;
                                row.push_back(curr);
                                curr=0.0;}
        }
        outCompRow.push_back(row);
    }
    return outCompRow;
}
float max(float a, float b){
    float out;
    if(a<=b){out = b;}
    if(a>b){out = a;}
    return out;
}
vector<vector<float> > maxpoolcol(vector<vector<float> > mat, int stride){
    vector<vector<float> > outCompCol;
    int n= mat.size();
    
    for(int j=0; j<n; j++){ //ith column jth row, compression along rows
        vector<float> col;
        float currmax;
        for(int i=0; i<n; i++){
            if(i%stride==0){currmax= mat.at(i).at(j);}
            if(((i+1)%stride)==0){currmax=max(currmax, mat.at(i).at(j));
                                col.push_back(currmax);}
            if(i%stride!=0 && ((i+1)%stride)!=0){currmax=max(currmax, mat.at(i).at(j));}                   
        }
        outCompCol.push_back(col);
    }
    return outCompCol;
}
vector<vector<float> > maxpoolrow(vector<vector<float> > mat, int stride){
    vector<vector<float> > outCompRow;
    int ncols= mat.size();
    int nrows= mat.at(0).size();
    
    for(int i=0; i<nrows; i++){ //ith column jth row, compression of rows
        vector<float> row;
        float currmax;
        for(int j=0; j<ncols; j++){
            if(j%stride==0){currmax= mat.at(j).at(i);}
            if(((j+1)%stride)==0){currmax= max(currmax, mat.at(j).at(i));
                                row.push_back(currmax);}
            if(j%stride!=0 && ((j+1)%stride)!=0){currmax=max(currmax, mat.at(j).at(i));}                   
        }
        outCompRow.push_back(row);
    }
    return outCompRow;
}
void pool(string s1, int stride, string type, string s2){
    vector< vector<float> > m1= inputm(s1);
    int n= m1.size();
    int m= m1.at(0).size();
    if(n!= m){throw std::invalid_argument("Matrix not square!");}
    if(n%stride != 0){throw std::invalid_argument("Matrix size not divisble by stride");}
    vector<vector<float> > compressed;
    if (type=="average"){
        vector<vector<float> > compressedC= avgpoolcol(m1, stride);
        compressed= avgpoolrow(compressedC, stride);
    }
    if (type=="max"){
        vector<vector<float> > compressedCols= maxpoolcol(m1, stride);
        compressed= maxpoolrow(compressedCols, stride);
    }
    outputm(compressed, s2);
}



float sigmoid(float a){
    float b= exp(-a);
    float o= 1/(1+b);
    return o;
}
void probV(string s1, string type, string s2){
    vector<float> m1= inputv(s1);
    int nc= m1.size();
    vector<float> out;
    if(type=="sigmoid"){
        for(int i=0; i<nc; i++){
            float m=m1.at(i);
            float o= sigmoid(m);
            out.push_back(o);
        }
    }
    if(type=="softmax"){
        float sumexp=0.0;
        for(int i=0; i<nc; i++){
            float m=m1.at(i);
            float e= exp(m);
            sumexp+=e;
        }
        for(int i=0; i<nc; i++){
            float m=m1.at(i);
            float e= exp(m)/sumexp;
            out.push_back(e);
        }
    }
    outputv(out, s2);
}

vector<string> cmdinp(){
    string s;
 getline(cin, s);
 int n= s.length();
 cout << n << endl;
 vector<string> argv;
 string ss="";
 for(int i=0; i<n; i++){
     //cout<< s.substr(i,1) << endl;
     if( s[i]!= ' ' && i!= n-1){ss+=s[i];}
     if( s[i]== ' ' ){argv.push_back(ss);
                        ss="";}
     if(i==n-1){ss+=s[i];
        argv.push_back(ss);}                                  
     }
     return argv;
}




int main(int argc, char** argv)
{
 
 //./yourcode.out fullyconnected a1a.inputmatrix.txt a1a.weightmatrix.txt a1a.biasmatrix.txt output.txt

       try{
    if( argc!= 5 & argc!= 6){throw std::invalid_argument("Corrupted Argument");}
    if( strcmp(argv[0], "./yourcode.out")!=0){throw std::invalid_argument("Corrupted Argument");}
    if( strcmp(argv[1],"fullyconnected")==0){
        if(argc==6){
            string s1= argv[2];
            string s2= argv[3];
            string s3= argv[4];
            string s4= argv[5];
            fullyconnected(s1, s2, s3, s4);
        }
        if(argc!=6){throw std::invalid_argument("Corrupted Argument");}
    }
    if( strcmp(argv[1],"activation")==0){
        if(argc==5){
            string type= argv[2];
            string s1= argv[3];
            string s2= argv[4];
            if(type == "relu" || type == "tanh"){activation(s1, type, s2);}
            if(type != "relu" && type != "tanh"){throw std::invalid_argument("Corrupted Argument");}
        }
        if(argc!=5){throw std::invalid_argument("Corrupted Argument");}
    }
    if( strcmp(argv[1],"pooling")==0){
        if(argc==6){
            string type= argv[2];
            string s1= argv[3];
            string strideSTR= argv[4];
            int stride = std::stof(strideSTR);
            string s2= argv[5];
            if(type == "max" || type == "average"){pool(s1, stride, type, s2);}
            if(type != "max" && type != "average"){throw std::invalid_argument("Corrupted Argument");}
        }
        if(argc!=6){throw std::invalid_argument("Corrupted Argument");}
    }
    if( strcmp(argv[1],"probability")==0){
        if(argc==5){
            string type= argv[2];
            string s1= argv[3];
            string s2= argv[4];
            if(type == "softmax" || type == "sigmoid"){probV(s1, type, s2);}
            if(type != "softmax" && type != "sigmoid"){throw std::invalid_argument("Corrupted Argument");}
        }
        if(argc!=5){throw std::invalid_argument("Corrupted Argument");}
    }
    if( strcmp(argv[1],"fullyconnected")!=0 && strcmp(argv[1],"activation")!=0 && strcmp(argv[1],"pooling")!=0 && strcmp(argv[1],"probability")!=0){
            throw std::invalid_argument("Corrupted Argument");
    }
       } catch(std::exception& e){std::cerr << "Please enter a valid input: " << e.what() << std::endl;}
  return 0;
}



   

