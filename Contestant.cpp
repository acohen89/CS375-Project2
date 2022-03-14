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
int Contestant::pointDif(bool sub, int p){
    points = sub ? points - p : points + p; 
    return points; 
}
ostream& operator<<(ostream& os, const Contestant& c)
{
    os << "Id: " << c.id << " Points: " << c.points <<  " Init: " << c.init << endl; 
    return os;
}