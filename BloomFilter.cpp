//BloomFilter.cpp

#include "IntegerHashes.h"
#include "StringHashes.h"
#include "BloomFilter.h"
#include <iostream>
using namespace std; 

BloomFilter::BloomFilter(int k, int m, std::string strfn, std::string intfn){
	this->k = k; //k = # hashfunctions
	this->m = m; //m = # bits
	intfns = new IntegerHash*[k]; 
//	cout<<"Int hash is: "+ intfn<<endl;
//	cout << "String hash is" + strfn <<endl; 
	bits = new uint64_t[(int)m/4 + 3]; //how to determine the size of bit array;
	if(strfn == "jenkins"){
		this->strfn = new JenkinsHash(); //wrong
	}else if(strfn == "pearson"){
		this->strfn = new PearsonHash(); //wrong
	}
	
	if(intfn == "division"){
		for(int i = 0; i < k; i ++){ //how do i create a template if I want to?
			DivisionHash* dh = new DivisionHash(i, m);  
			intfns[i] = dh; 
		}
	}else if(intfn == "reciprocal"){
		for(int i = 0; i < k; i ++){
			ReciprocalHash* rh = new ReciprocalHash(i, m); 
			intfns[i] = rh; 
		} 
	}else{	
		for(int i = 0; i < k; i ++){
			SquareRootHash* srh = new SquareRootHash(i, m); 
			intfns[i] = srh; 
		}
	}

}

void BloomFilter::insert(const std::string& value){
	for(int i = 0; i < k; i++){
		int v = (*strfn).hash(value);
		int id = (*intfns[i]).hash(v); 
		bits[id/4] |= ((uint64_t)1 << (id % 4)); 
	}
}

bool BloomFilter::lookup(const std::string& value) const{
 	for(int i = 0; i < k; i++){
		int v= (*strfn).hash(value); 
		uint64_t id = (*intfns[i]).hash(v);
		uint64_t temp = (uint64_t)bits[id/4] & ((uint64_t)1 << (id % 4)); 
		if(temp != ((uint64_t)1 << (id % 4))){
//			if(temp != ((uint64_t)1 << (id %4)))
//				cout<<"false"<<endl;
//			cout<<(uint64_t)(1 << (id % 4)) <<endl;
//			cout<< bits[id/4] <<endl;  
			return false;
		} 
	}
//	cout << "true" << endl; 
	return true; 
}


BloomFilter::~BloomFilter(){
	for(int i = 0; i < k; i++){
		delete intfns[i]; 
	}
	delete[] intfns; 
	delete strfn; 	
	delete[] bits; 
}




