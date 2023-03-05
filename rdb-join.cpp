#include <iostream>
#include <vector>
#include <list>
#include "rdb-basics.cpp"

Relation *naturaljoin(Relation *R1, Relation *R2, list<string> joinattr) //
{
    Relation *res;
    res = cartesian_product(R1, R2);

    //construct DNFformula and filter res accordingly

    return NULL;
}

using namespace std;

int main()
{
    

    return 0;
}