#include "HashSet.h"
#include "IntegerHashes.h"
#include "StringHashes.h"
#include <string>
#include <iostream>
using namespace std;
HashSet::HashSet(){
    nitems = 0;
    nslots = 1000; 
    strfn = new PearsonHash(); 
    intfn = new ReciprocalHash(1, nslots);
    slots = new string*[nslots]();
}

void HashSet::rehash(){
    string** newslots = new string*[2*nslots]();
    for(int i = 0; i < nslots; i++){
        if(slots[i] != NULL){
//	    cout << "entered"<<endl; //print
            int v = (*strfn).hash(*slots[i]);
	    string value = *slots[i];  
            int id = (*intfn).hash(v);
            while(newslots[id]){
                id ++; 
            }
	
        newslots[id] = new string(value); //insertion completed
        }
    }
    slots = newslots; //free pointer 
    nslots *= 2;
//    cout<<nslots<<endl;  
    //delete newslots; //?? 
}

void HashSet::insert(const std::string& value){
    //rehash if oversize;  
    if(nitems == nslots) rehash(); 

    int v = (*strfn).hash(value);
    int id = (*intfn).hash(v); 
 
    while(slots[id] != NULL){
        id = (id + 1)% nslots; 
    }

    slots[id] = new string(value); //insertion completed 
    nitems ++; 
}

bool HashSet::lookup(const std::string& value)const{
    int v = (*strfn).hash(value); 
    int id =(*intfn).hash(v);   

    while(slots[id]){
	if(*slots[id] == value){
            return true;
	} 
	id = (id + 1) % nslots; //linear prob 
    }
    return false; //not found
}

HashSet::~HashSet(){
    delete strfn; 
    delete intfn;
    for(int i = 0; i < nslots; i++){
	delete slots[i]; 
    } 
    delete[] slots; 
}
