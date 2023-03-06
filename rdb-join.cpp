#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <tuple>
#include <algorithm>
#include "rdb-basics.cpp"

Relation *naturaljoin(Relation *_R1, Relation *_R2, list<string> joinattr) //
{
    Relation *res;
    Relation *R1 = new Relation(*_R1);
    Relation *R2 = new Relation(*_R2);
    // find common attributes and their indices in respective relations
    map<string, int> R1_index;
    map<string, int> R2_index;
    map<string, int> R1_cnt;
    map<string, int> R2_cnt;
    vector<string> common_attributes;
    for(int i = 0; i < R1->natttr; ++i)
    {
        R1_index[R1->mapped_schema[i]] = i;
        R1_cnt[R1->mapped_schema[i]]++;
    }
    for(int i = 0; i < R2->natttr; ++i)
    {
        R2_index[R2->mapped_schema[i]] = i;
        R2_cnt[R2->mapped_schema[i]]++;
    }
    for(auto it = R2->attrnames.begin(); it != R2->attrnames.end(); ++it)
    {
        if(R1_cnt[*it] != 0)
        {
            common_attributes.push_back(*it);
            reverse(it->begin(), it->end());
        }
    }

    // construct DNFformula and filter res accordingly
    DNFformula *f = new DNFformula;
    res = cartesian_product(R1, R2);
    for(auto it1 : R1->recs)
    {
        for(auto it2 : R2->recs)
        {
            list<tuple<string, char, Attr *>> temp;
            bool x1 = true;
            for(auto i : common_attributes)
            {
                if(*it1->attrptr[R1_index[i]] == *it2->attrptr[R2_index[i]])
                {
                    temp.push_back(make_tuple(i, '=', it1->attrptr[R1_index[i]]));
                    string s = i;
                    reverse(s.begin(), s.end());
                    temp.push_back(make_tuple(s, '=', it1->attrptr[R1_index[i]]));
                }
                else{
                    x1 = false;
                    break;
                }
            }
            if(x1)
            {
                f->ops.push_back(temp);
            }
        }
    }
    res = res->Union(f);
    
    // remove the reversed colomn
    list<string> selection;
    for(auto it : res->attrnames)
    {
        bool x = true;
        for(auto it2 : common_attributes)
        {
            string s = it2;
            reverse(s.begin(), s.end());
            if (it == s)
            {
                x = false;
                break;
            }
            
        }
        if(x)
        {
            selection.push_back(it);
        }
    }

    res = res->projection(selection);

    return res;
}

using namespace std;

int main()
{
    vector<string> _attrnames1 = {"Name", "EmpId", "DeptName"};
    vector<int> _attrinds1 = {1, 2, 3};
    list<Record *> l1;
    vector<Attr *> v1 = {new stringAttribute("Harry"), new integerAttribute(3415), new stringAttribute("Finance")};
    l1.push_back(new Record(v1));
    v1 = {new stringAttribute("Sally"), new integerAttribute(2241), new stringAttribute("Sales")};
    l1.push_back(new Record(v1));
    v1 = {new stringAttribute("George"), new integerAttribute(3401), new stringAttribute("Finance")};
    l1.push_back(new Record(v1));
    v1 = {new stringAttribute("Harriet"), new integerAttribute(2202), new stringAttribute("Sales")};
    l1.push_back(new Record(v1));
    Relation R1(3, 4, _attrnames1, _attrinds1, l1);
    //R1.disp();

    vector<string> _attrnames2 = {"DeptName", "Manager"};
    vector<int> _attrinds2 = {1, 2};
    list<Record *> l2;
    vector<Attr *> v2 = {new stringAttribute("Finance"), new stringAttribute("George")};
    l2.push_back(new Record(v2));
    v2 = {new stringAttribute("Sales"), new stringAttribute("Harriet")};
    l2.push_back(new Record(v2));
    v2 = {new stringAttribute("Productions"), new stringAttribute("Charles")};
    l2.push_back(new Record(v2));
    Relation R2(2, 3, _attrnames2, _attrinds2, l2);
    //R2.disp();

    list<string> joinattr;
    Relation *R3 = naturaljoin(&R1, &R2, joinattr);
    //R3->delete_copies();
    R3->disp();

    return 0;
}