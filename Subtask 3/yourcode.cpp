#include<iostream>
#include<fstream>
#include<cstring>
#include<vector>
#include<cmath> 
#include <cfloat>
#include<thread>
#include "audioAPI.h"
#include<bits/stdc++.h>

#include<pthread.h>

using namespace std;


int main(int argc, char** argv){

	try{
	
	pred_t TOP[3];
	TOP[0] = {0,0};
	TOP[1] = {0,0};
	TOP[2] = {0,0};
	string name[12] = {"silence","unknown","yes","no","up","down","left","right","on","off","stop","go"};
	if (argc!=3) {throw std::invalid_argument("Invalid Command typed in");}
	else if(strcmp(argv[0],"./yourcode.out")!=0){throw std::invalid_argument("Invalid Command typed in");}
	else{
	
		libaudioAPI(argv[1],TOP);
		
		ofstream file;
		file.open(argv[2], ios_base::app);
		file << argv[1] << " " << name[TOP[0].label] << " " << name[TOP[1].label] << " " << name[TOP[2].label] << " " << TOP[0].prob << " " << TOP[1].prob << " " << TOP[2].prob << "\n";  
		file.close();
	}
	
	} catch(std::exception& e){std::cerr << "Something went wrong: " << e.what() << std::endl;}
	return 0;
}
