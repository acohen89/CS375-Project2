using namespace std; 
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdbool.h>

#include "Contestant.h"

vector<string> stringToVector(string s){
    stringstream ss(s);
    string word;
    vector<string> stringVect; 
    while (ss >> word) {
        stringVect.push_back(word);
    }
    return stringVect;
}

int parseInput(string s){
    string ret = ""; 
    for(int i = 0; i < s.length(); i++){
        if(isdigit(s[i])){
            ret += s[i];
        }
    }
    return stoi(ret); 
}
// void findContestant(Contestant k){}
// void eliminateWeakest(){}
// void earnPoints(Contestant k, int points){}
// void losePoints(Contestant k, int points){}
// void showHandles(){}
// void showLocation(){}
// void crownWinner(){}

void findContestant(int id, Contestant contsHeap[], int loc[], int nextI){
    //TODO: does not work yet 
    if(nextI <= id || contsHeap[loc[id]].getInit() == 0){
        cout << "Contestant <" << id <<"> is not in the extended heap" << endl;
        return; 
    }
    cout << "Contestant <" << id << "> is in the extended heap with score <" << contsHeap[loc[id]].getPoints() << ">." << endl; 
}
void showContestants(Contestant *contsHeap, int arrSize){
    for(int i = 1; i < arrSize; i++){
        Contestant cur = contsHeap[i]; 
        if(cur.getInit() == 1){
            cout << "Contestant <" << cur.getId() << "> in extended heap location <" << i;
            cout << "> with score <" << cur.getPoints() << ">." << endl;
        }
            // cout << "Contestant <" << cur.getId() << "> in extended heap location <" << i;
            // cout << "> with score <" << cur.getPoints() << ">. " << cur.getInit() << endl;
    }
}

Contestant *insertContestant(int k, int score, Contestant contsHeap[], int arrSize, int *nextI, int loc[]){
    Contestant c(k, score); 
    if(contsHeap[1].getInit() == 0){
        contsHeap[1] = c;
        cout << "Contestant <" << k << "> inserted with initial score <" <<  score << ">." << endl;
        loc[k] = 1; 
        *nextI = *nextI + 1;
        return contsHeap;
    }
    if(contsHeap[arrSize].getInit() == 1){
        cout << "Contestant <" << k << "> could not be inserted because the extended heap is full." << endl;
        return contsHeap;

    }
    //TODO: see if contestant is in array
    int i =  *nextI;
    contsHeap[*nextI] = c;           
    while (i > 1 && contsHeap[i/2].getPoints() > contsHeap[i].getPoints()){ //*make sure we floor
        Contestant temp = contsHeap[i/2]; 
        contsHeap[i/2] = contsHeap[i]; 
        contsHeap[i] = temp; 
        i = i/2; 
    }
    loc[k] = i;
    *nextI = *nextI + 1;
    cout << "Contestant <" << k << "> inserted with initial score <" <<  score << ">." << endl;
    return contsHeap;
}

int getArrSize(char *argv[]){
    string line;
    ifstream file(argv[1]);
     if (file.is_open()){
        if(getline(file, line)){
            return stoi(line) + 1;
        }
    }
    file.close();
    return -1; 
}

int main(int argc, char *argv[]){
    cout << "Hello World" << endl;
    int arrSize = getArrSize(argv);
    int t = 1;
    int *nextI = &(t); 
    Contestant contsHeap[arrSize];
    int loc[arrSize]; //? Should the size of this also be the size of array? 
    string line;
    ifstream file(argv[1]);
     if (file.is_open()){
        while(getline(file, line)){
            if(sizeof(contsHeap)/sizeof(contsHeap[0]) > 0){
                vector<string> lineVector = stringToVector(line);
                cout << line << endl; 
                if(lineVector.at(0) == "insertContestant"){
                    insertContestant(parseInput(lineVector.at(1)), parseInput(lineVector.at(2)), contsHeap, arrSize, nextI, loc); 
                }else if(lineVector.at(0) == "showContestants"){
                    showContestants(contsHeap, arrSize);
                } else if(lineVector.at(0) == "findContestant"){
                    findContestant(parseInput(lineVector.at(1)), contsHeap, loc, *nextI); 
                } 
                // else if(lineVector.at(0) == "eliminateWeakest"){

                // } else if(lineVector.at(0) == "losePoints"){

                // } else if(lineVector.at(0) == "earnPoints"){

                // } else if(lineVector.at(0) == "showHandles"){

                // } else if(lineVector.at(0) == "crownWinner"){

                // } else {
                //     cout << "Error on input " << endl; 
                // }
            }
            

        }
        file.close();
        // showContestants(contsHeap, arrSize);
     }
    return 0; 
}