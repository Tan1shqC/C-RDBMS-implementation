#include <iostream>
#include <vector>
#include <list>

using namespace std;

class Attr;
// Base class for attributes
// Add operators for different attribute type in derived classes

class Record;
class Relation;

Relation * Union(Relation * R1, Relation * R2);                             // All records of both R1 and R2
Relation * Difference(Relation * R1, Relation * R2);                        // Records in R1 but not in R2
Relation * cartesian_product(Relation * R1, Relation * R2);                 // All possible pair of records from R1 and R2(given they don have a common attribute)
Relation * naturaljoin(Relation * R1, Relation * R2, list<string>joinattr); // 

struct DNFformula;

class integerAttribute;
class floatAttribute;
class stringAttribute;