#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <tuple>

using namespace std;

class Attr;
class Record;
class Relation;

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
};

class Record
{ // storing data for each record
    vector<Attr *> attrptr;
    // methods
public:
    Record(vector<Attr *> &);
    Record(const Record &);
    void print() const;
    bool operator==(Record &);
    void join_records(Record *, Record *);
    friend class Relation;
    friend Relation *naturaljoin(Relation *, Relation *, list<string> );
};

struct DNFformula
{
    list<list<tuple<string, char, Attr *>>> ops;
};

class Relation
{                             // storing a relation
    int natttr, nrecs;        // number of attributes and records
    vector<string> attrnames; // schema
    vector<int> attrinds;     // mapping schema to indices
    list<Record *> recs;      // list of records
    vector<string> mapped_schema;
    vector<int> attribute_type;
    

    // methods
public:
    map<string, int> name_map_type;
    Relation(int , int , vector<string> &, vector<int> &, list<Record *> ); // constructor

    Relation(const Relation &); // copy constructor

    friend Relation *Union(Relation *, Relation *); // All records of both R1 and R2

    friend Relation *Difference(Relation *, Relation *); // Records in R1 but not in R2

    friend Relation *cartesian_product(Relation *, Relation *); // All possible pair of records from R1 and R2(given they don't have a common attribute)

    Relation *projection(list<string> ); // New relation with subset of columns (passes this pointer)

    Relation *Union(DNFformula *); // New relation with a subset of records matching a boolean

    //                              // expression in the attribute values in disjunctive normal form.

    Relation *Difference(string , string ); //  rename an attribute in schema

    friend Relation *naturaljoin(Relation *, Relation *, list<string> ); //

    void disp() const;
    void relation_print()const;
    void rearrange(const Relation &);
    void delete_copies();
    void AddRecord();
    Relation(int , int, vector<string> &, vector<int> &, vector<int> &);
    Relation(int , int, vector<string> &, vector<int> &, vector<int> &, list<Record *> );
    void get_attributes();
};

Relation * Union(Relation * R1, Relation * R2);                             // All records of both R1 and R2
Relation * Difference(Relation * R1, Relation * R2);                        // Records in R1 but not in R2
Relation * cartesian_product(Relation * R1, Relation * R2);                 // All possible pair of records from R1 and R2(given they don have a common attribute)
Relation * naturaljoin(Relation * R1, Relation * R2, list<string>joinattr); // 



class integerAttribute : public Attr
{
    int _data;
public:
    integerAttribute(int);
    Attr &clone()const;
    bool operator==(const Attr &right) const;
    bool operator!=(const Attr &right) const;
    bool operator<(const Attr &right) const;
    bool operator<=(const Attr &right) const;
    bool operator>(const Attr &right) const;
    bool operator>=(const Attr &right) const;
    void disp() const;
    int get_value();
};

class floatAttribute : public Attr
{
    float _data;
public:
    floatAttribute(float );
    Attr &clone()const;
    bool operator==(const Attr &right) const;
    bool operator!=(const Attr &right) const;
    bool operator<(const Attr &right) const;
    bool operator<=(const Attr &right) const;
    bool operator>(const Attr &right) const;
    bool operator>=(const Attr &right) const;
    void disp() const;
    float get_value();
};

class stringAttribute : public Attr
{
    string _data;

public:
    stringAttribute(string );
    Attr &clone()const;
    bool operator==(const Attr &right) const;
    bool operator!=(const Attr &right) const;
    bool operator<(const Attr &right) const;
    bool operator<=(const Attr &right) const;
    bool operator>(const Attr &right) const;
    bool operator>=(const Attr &right) const;
    void disp() const;
    string get_value();
};