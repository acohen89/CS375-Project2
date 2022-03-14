#ifndef CONTESTANT_H
#define CONTESTANT_H

#include <string> 
#include <stdbool.h>
#include <vector>
#include <bits/stdc++.h>
#include <iostream>

using namespace std;


class Contestant {      
    public: 
        Contestant(int, int); 
        Contestant();
        friend ostream& operator<<(ostream&, const Contestant&);
        bool getInit(){return init;}
        int getId(){return id;}
        int getPoints(){return points;}
    private: 
        int points;
        int id; 
        bool init; 

};

#endif