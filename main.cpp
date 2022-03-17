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

void minHeapify(Contestant contsHeap[], int start, int arrSize){
    int left = 2*start; 
    int right = (2*start) + 1;
    int smallest = -1; 
    if(left <= arrSize && contsHeap[left].getPoints() < contsHeap[start].getPoints()){
        smallest = left;
    }else {smallest = start;}
    if (right <= arrSize && contsHeap[right].getPoints() < contsHeap[smallest].getPoints()){
        smallest = right; 
    } 
    if(smallest != start){
        Contestant temp = contsHeap[start]; 
        contsHeap[start] = contsHeap[smallest];
        contsHeap[smallest] = temp;
        minHeapify(contsHeap, smallest, arrSize); 
    }
}


bool findContestant(int id, Contestant contsHeap[], int loc[], int nextI, bool print = true){
    if(nextI >= id || contsHeap[loc[id]].getInit() == 0){
        if(print){
            cout <<  "Contestant <" << id <<"> is not in the extended heap" << endl; 
        }
        return false; 
    }
    if(print){
        cout << "Contestant <" << id << "> is in the extended heap with score <" << contsHeap[loc[id]].getPoints() << ">." << endl; 
    }
    return true;
}
// void showLocation(){}
// void crownWinner(){}

void showHandles(Contestant contsHeap[], int arrSize, int loc[]){
    for(int i = 1; i < arrSize; i++){
        Contestant cur = contsHeap[loc[i]];
        if(cur.getInit()){
            cout << "Contestant <" << cur.getId() << "> stored in extended heap location <" << i << ">." << endl; 
        }else {
            cout << "There is no Contestant <" << loc[i] << "> in the extended heap: handle[<" << i << ">] = -1." << endl; 
        }

    }
}
void earnPoints(int id, int points, Contestant contsHeap[], int arrSize, int *nextI, int loc[]){
    if(findContestant(id, contsHeap, loc, *nextI, false)){
        int i = loc[id]; 
        int newScore = contsHeap[i].pointDif(false, points);
        if((contsHeap[2*i + 1].getPoints() < contsHeap[i].getPoints() || contsHeap[2*i].getPoints() < contsHeap[i].getPoints())){
            minHeapify(contsHeap, 1, arrSize);
        }
        cout << "Contestant <" << id << ">’s score increased by <" << points << "> points to <" << newScore << ">." << endl;
    }else {
        cout << "Contestant <" << id << "> is not in the extended heap." << endl;
    }
}


void eliminateWeakest(Contestant contsHeap[], int arrSize, int *nextI){
    if(*nextI <= 1){
        cout << "No contestant can be eliminated since the extended heap is empty." << endl;
        return; 
    }
    Contestant smallest = contsHeap[1]; 
    contsHeap[1] = contsHeap[arrSize]; 
    *nextI = *nextI - 1;
    minHeapify(contsHeap, 1, arrSize);
    cout << "Contestant <" << smallest.getId() << "> with current lowest score <" << smallest.getPoints()<< "> eliminated." << endl;
    

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

void losePoints(int id, int points, Contestant contsHeap[], int arrSize, int *nextI, int loc[]){
    if(findContestant(id, contsHeap, loc, *nextI, false)){
        int i = loc[id]; 
        int newScore = contsHeap[i].pointDif(true, points);
        while(i > 1 && contsHeap[i/2].getPoints() > contsHeap[i].getPoints()){
            Contestant temp = contsHeap[i]; 
            loc[temp.getId()] = loc[contsHeap[i/2].getId()];
            loc[contsHeap[i/2].getId()] = loc[temp.getId()]; 
            contsHeap[i] = contsHeap[i/2]; 
            contsHeap[i/2] = temp; 
            i = i/2; 
        }
        cout << "Contestant <" << id << ">’s score decreased by <" << points << "> points to <" << newScore << ">." << endl;
    }else {
        cout << "Contestant <" << id << "> is not in the extended heap." << endl;
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
    if(!findContestant(k, contsHeap, loc, *nextI, false)){
        int i =  *nextI;
        contsHeap[*nextI] = c;           
        loc[k] = i;
        while (i > 1 && contsHeap[i/2].getPoints() > contsHeap[i].getPoints()){
            Contestant temp = contsHeap[i/2]; 
            int tempi = temp.getId();   
            loc[temp.getId()] = loc[contsHeap[i].getId()];
            loc[contsHeap[i].getId()] = loc[temp.getId()]; 
            contsHeap[i/2] = contsHeap[i]; 
            contsHeap[i] = temp; 
            i = i/2; 
        }
        *nextI = *nextI + 1;
        cout << "Contestant <" << k << "> inserted with initial score <" <<  score << ">." << endl;
    } else {
        cout << "Contestant <" << k << "> is already in the extended heap: cannot insert." << endl;
    }
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
                } else if(lineVector.at(0) == "showContestants"){
                    showContestants(contsHeap, arrSize);
                } else if(lineVector.at(0) == "findContestant"){
                    findContestant(parseInput(lineVector.at(1)), contsHeap, loc, *nextI); 
                } else if(lineVector.at(0) == "eliminateWeakest"){
                    eliminateWeakest(contsHeap, arrSize, nextI);
                }  else if(lineVector.at(0) == "losePoints"){
                    //TODO: upadate loc 
                    losePoints(parseInput(lineVector.at(1)), parseInput(lineVector.at(2)), contsHeap, arrSize, nextI, loc); 
                }
                 else if(lineVector.at(0) == "earnPoints"){
                    //TODO: upadate loc 
                    earnPoints(parseInput(lineVector.at(1)), parseInput(lineVector.at(2)), contsHeap, arrSize, nextI, loc); 
                } 
                else if(lineVector.at(0) == "showHandles"){
                    showHandles(contsHeap, arrSize, loc);
                } 
                // else if(lineVector.at(0) == "crownWinner"){

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