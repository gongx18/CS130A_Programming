#include "HashSet.h"
#include "IntegerHashes.h"
#include "StringHashes.h"
#include <string>
#include <iostream>
using namespace std;
HashSet::HashSet(){
    nitems = 0;
    nslots = 100; 
    strfn = new PearsonHash(); 
 //   StringHash* strfn2 = new Prob(); //probing function
    intfn = new ReciprocalHash(1, nslots);
    slots = new string*[nslots];
}

void HashSet::rehash(){
    string** newslots = new string*[2*nslots];
    for(int i = 0; i < nslots; i++){
        if(slots[i] != NULL){
            int v = (*strfn).hash(*slots[i]);
	    string value = *slots[i];  
            int id = (*intfn).hash(v); 
            while(newslots[id] != NULL){
                id ++; 
            }
        *newslots[id] = value; //insertion completed
        }
    }
    slots = newslots; //free pointer 
    nslots *= 2; 
    delete newslots;  
}

void HashSet::insert(const std::string& value){
    //rehash if oversize;  
    if(nitems == nslots) rehash(); 

    int v = (*strfn).hash(value); 
    int id = (*intfn).hash(v); 
    while(slots[id] != NULL){
        id = (id + 1)% nslots; 
    }
    string* temp = new string(value);  
    slots[id] = temp; //insertion completed
    //cout << *slots[id] << endl; 
    delete temp; 
    nitems ++; 
}

bool HashSet::lookup(const std::string& value)const{
    int v = (*strfn).hash(value); 
    int id =(*intfn).hash(v); 
    while(slots[id] != NULL && id < nslots){
	if(*slots[id] == value)
            return true;
	id ++; //linear prob 
    }
    return false; //not found
}

HashSet::~HashSet(){
//    for(int i = 0; i < nslots; i++){
//	if(slots[i] != NULL)
//		cout<<*slots[i]<<endl;
//    }
    delete strfn; 
//    delete strfn2;
    delete intfn; 
    delete[] slots; 
}
