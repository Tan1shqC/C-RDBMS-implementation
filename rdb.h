#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <tuple>

using namespace std;

class Attr
{ // Base class for attributes
  // Add operators for different attribute type in derived classes
public:
    virtual bool operator==(const Attr &right) const = 0;
    virtual bool operator!=(const Attr &right) const = 0;
    virtual bool operator<(const Attr &right) const = 0;
    virtual bool operator<=(const Attr &right) const = 0;
    virtual bool operator>(const Attr &right) const = 0;
    virtual bool operator>=(const Attr &right) const = 0;
    virtual void disp() const = 0;
    virtual Attr &clone()const = 0;
    friend class Relation;
    friend class Record;
};

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