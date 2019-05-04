#include "HashSet.h"
#include "IntegerHashes.h"
#include "StringHashes.h"
#include <string>
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
        id ++; 
    }
    *slots[id] = value; //insertion completed
    nitems ++; 
}

bool HashSet::lookup(const std::string& value)const{
    int v = (*strfn).hash(value); 
    int id =(*intfn).hash(v); 
    while(slots[id] != NULL && id < nslots){
        if(*slots[id] == value)
            return true; 
    }
    return false; //not found
}

HashSet::~HashSet(){
    delete strfn; 
    delete strfn2;
    delete intfn; 
    delete[] slots; 
}
