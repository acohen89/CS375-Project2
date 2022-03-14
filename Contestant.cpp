#include "Contestant.h"

Contestant::Contestant(int i, int p){
    points = p;
    id = i;
    init = true; 
}
Contestant::Contestant(){
    init = false;
    points = INT_MAX; 
}
ostream& operator<<(ostream& os, const Contestant& c)
{
    os << "Id: " << c.id << " Points: " << c.points <<  " Init: " << c.init << endl; 
    return os;
}