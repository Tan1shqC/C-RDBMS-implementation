#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <tuple>
#include "rdb-attr.cpp"
#include "./libfort/lib/fort.hpp"
#include "./libfort/lib/fort.c"

using namespace std;

Record::Record(vector<Attr *> &_attrptr)
{
    // constructor
    for (auto it : _attrptr)
    {
        Attr &temp = it->clone();
        attrptr.push_back(&temp);
    }
}
Record::Record(const Record &r)
{
    // copy constructor
    for (auto it : r.attrptr)
    {
        Attr &temp = it->clone();
        attrptr.push_back(&temp);
    }
}
void Record::print() const
{
    for (auto x : this->attrptr)
    {
        x->disp();
    }
    cout << endl;
}
bool Record::operator==(Record &r)
{
    vector<Attr *>::iterator it = r.attrptr.begin();
    for (auto x : this->attrptr)
    {
        if (*x != **it)
        {
            return false;
        }
        else
        {
            it++;
        }
    }
    return true;
}
void Record::join_records(Record *r1, Record *r2)
{
    for (auto x : r2->attrptr)
    {
        r1->attrptr.push_back(x);
    }
}

void Relation::disp() const
{
    for (auto x : this->attrnames)
    {
        cout << x << " ";
    }
    cout << endl;
    for (auto x : recs)
    {
        x->print();
    }
}

void Relation::rearrange(const Relation &R)
{
    map<string, int> mapping1;
    int i;
    for (i = 0; i < R.natttr; ++i)
    {
        mapping1[R.attrnames[i]] = R.attrinds[i];
    }

    map<string, int> mapping2;
    for (i = 0; i < R.natttr; ++i)
    {
        mapping2[this->attrnames[i]] = this->attrinds[i];
    }

    vector<pair<int, int>> swap_indexes;
    bool y = true;
    for (auto x : R.attrnames)
    {
        swap_indexes.push_back(make_pair(mapping1[x] - 1, mapping2[x] - 1));
    }

    for (auto x : this->recs)
    {
        vector<Attr *> copy(x->attrptr);
        for (auto y : swap_indexes)
        {
            x->attrptr[y.first] = copy[y.second];
        }
    }
    this->attrinds = R.attrinds;
    this->attrnames = R.attrnames;
}
void Relation::delete_copies()
{
    for (auto x = this->recs.begin(); x != this->recs.end();)
    {
        bool z = true;
        for (auto y = this->recs.begin(); y != x; y++)
        {
            if (**y == **x)
            {
                x = this->recs.erase(x);
                z = false;
                break;
            }
        }
        if (z)
            x++;
    }
}
void Relation::AddRecord()
{
    vector<Attr *> new_record(natttr);
    int i = 0;
    for (i = 0; i < natttr; ++i)
    {
        Attr *attr;
        cout << "Enter the " << mapped_schema[i] << " value:" << endl;
        if(attribute_type[i] == 1)
        {
            string x;
            cin >> x;
            attr = new stringAttribute(x);
        }
        else if(attribute_type[i] == 2)
        {
            int x;
            cin >> x;
            attr = new integerAttribute(x);
        }
        else if(attribute_type[i] == 3)
        {
            float x;
            cin >> x;
            attr = new floatAttribute(x);
        }
        new_record[i] = attr;
    }
    Record *r = new Record(new_record);
    recs.push_back(r);
    nrecs++;
}
Relation::Relation(int _natttr, int _nrecs, vector<string> &_attrnames, vector<int> &_attrinds, vector<int> &_attribute_type) : natttr(_natttr), nrecs(_nrecs), attrnames(_attrnames), attrinds(_attrinds), attribute_type(_attribute_type), mapped_schema(_natttr)
{
    for (int i = 0; i < _natttr; ++i)
    {
        mapped_schema[_attrinds[i] - 1] = _attrnames[i];
    }
    for(int i = 0; i < _natttr; ++i)
    {
        name_map_type[mapped_schema[i]] = attribute_type[i];
    }
}

Relation::Relation(int _natttr, int _nrecs, vector<string> &_attrnames, vector<int> &_attrinds, vector<int> &_attribute_type, list<Record *> _recs) : natttr(_natttr), nrecs(_nrecs), attrnames(_attrnames), attrinds(_attrinds), attribute_type(_attribute_type), mapped_schema(_natttr)
{
    for (auto x : _recs)
    {
        recs.push_back(new Record(*x));
    }
    for (int i = 0; i < _natttr; ++i)
    {
        mapped_schema[_attrinds[i] - 1] = _attrnames[i];
    }
    for(int i = 0; i < _natttr; ++i)
    {
        name_map_type[mapped_schema[i]] = attribute_type[i];
    }
}

Relation::Relation(int _natttr, int _nrecs, vector<string> &_attrnames, vector<int> &_attrinds, list<Record *> _recs) : natttr(_natttr), nrecs(_nrecs), attrnames(_attrnames), attrinds(_attrinds), mapped_schema(_natttr)
{
    // constructor
    for (int i = 0; i < _natttr; ++i)
    {
        mapped_schema[_attrinds[i] - 1] = _attrnames[i];
    }
    for (auto x : _recs)
    {
        recs.push_back(new Record(*x));
    }
    for(int i = 0; i < _natttr; ++i)
    {
        name_map_type[mapped_schema[i]] = attribute_type[i];
    }
}

Relation::Relation(const Relation &R) : natttr(R.natttr), nrecs(R.nrecs), attrnames(R.attrnames), attrinds(R.attrinds), mapped_schema(R.natttr), attribute_type(R.attribute_type)
{
    // copy constructor
    for (int i = 0; i < R.natttr; ++i)
    {
        mapped_schema[R.attrinds[i] - 1] = R.attrnames[i];
    }
    for (auto x : R.recs)
    {
        recs.push_back(new Record(*x));
    }
    for(int i = 0; i < R.natttr; ++i)
    {
        name_map_type[mapped_schema[i]] = attribute_type[i];
    }
}

Relation *Union(Relation *R1, Relation *R2) // All records of both R1 and R2
{
    set<string> s1(R1->attrnames.begin(), R1->attrnames.end());
    set<string> s2(R2->attrnames.begin(), R2->attrnames.end());
    if (s1 == s2)
    {
        Relation *res = new Relation(*R1);
        R2->rearrange(*R1);
        for (auto x : R2->recs)
        {
            res->recs.push_back(new Record(*x));
        }
        return res;
    }
    return NULL;
}

Relation *Difference(Relation *R1, Relation *R2) // Records in R1 but not in R2
{
    set<string> s1(R1->attrnames.begin(), R1->attrnames.end());
    set<string> s2(R2->attrnames.begin(), R2->attrnames.end());
    if (s1 == s2)
    {
        Relation *res = new Relation(*R1);
        R2->rearrange(*R1);
        for (auto x = R2->recs.begin(); x != R2->recs.end(); ++x)
        {
            for (auto y = res->recs.begin(); y != res->recs.end();)
            {
                if (**x == **y)
                    y = res->recs.erase(y);
                else
                    y++;
            }
        }
        return res;
    }
    return NULL;
}

Relation *cartesian_product(Relation *R1, Relation *R2) // All possible pair of records from R1 and R2(given they don't have a common attribute)
{
    // check for distinct entries

    // create new relation
    if (1)
    {
        list<Record *> recs;
        for (auto it1 = R1->recs.begin(); it1 != R1->recs.end(); ++it1)
        {
            for (auto it2 = R2->recs.begin(); it2 != R2->recs.end(); ++it2)
            {
                Record *r1 = new Record(**it1);
                Record *r2 = new Record(**it2);
                r1->join_records(r1, r2);
                recs.push_back(r1);
            }
        }
        vector<string> attrname(R1->attrnames);
        for (auto x : R2->attrnames)
        {
            attrname.push_back(x);
        }
        vector<int> attrind(R1->attrinds);
        for (auto x : R2->attrinds)
        {
            attrind.push_back(x + R1->natttr);
        }
        vector<int> attribute_type(R1->attribute_type);
        for (auto x : R2->attribute_type)
        {
            attribute_type.push_back(x);
        }
        Relation *res = new Relation(R1->natttr + R2->natttr, R1->nrecs * R2->nrecs, attrname, attrind, attribute_type, recs);
        return res;
    }
    else
        return NULL;
}

Relation *Relation::projection(list<string> projectattrs)
{
    vector<int> del_index;
    vector<int> select_index;
    map<string, int> attr_map;
    vector<string> new_attrnames;
    vector<int> new_attrinds;
    vector<int> new_attribute_type;
    vector<Attr *> temp;
    list<Record *> new_recs;
    int count = 1;
    Relation *R = new Relation(*this);
    for (int i = 0; i < this->natttr; ++i)
    {
        attr_map[attrnames[i]] = this->attrinds[i] - 1;
    }
    for (auto x : projectattrs)
    {
        select_index.push_back(attr_map[x]);
    }
    for (int i = 0; i < this->natttr; ++i)
    {
        bool y = true;
        for (auto x : select_index)
        {
            if (i == x)
            {
                y = false;
                break;
            }
        }
        if (y)
        {
            del_index.push_back(i);
        }
    }
    for (int i = 0; i < this->natttr; ++i)
    {
        bool y = true;
        for (auto x : del_index)
        {
            if (i == x)
            {
                y = false;
                break;
            }
        }
        if (y)
        {
            new_attrnames.push_back(this->mapped_schema[i]);
            new_attrinds.push_back(count);
            new_attribute_type.push_back(this->attribute_type[i]);
            count++;
        }
    }
    R->attrinds = new_attrinds;
    R->attrnames = new_attrnames;
    R->attribute_type = new_attribute_type;
    for (auto x : R->recs)
    {
        Record *temp;
        vector<Attr *> new_attrptr;
        for (int i = 0; i < this->natttr; ++i)
        {
            bool y = true;
            for (auto x : del_index)
            {
                if (i == x)
                {
                    y = false;
                    break;
                }
            }
            if (y)
            {
                new_attrptr.push_back(x->attrptr[i]);
            }
        }
        temp = new Record(new_attrptr);
        new_recs.push_back(temp);
    }
    R->recs = new_recs;
    R->natttr = this->natttr - (int)del_index.size();
    return R;
}

Relation *Relation::Union(DNFformula *f)
{
    map<string, int> attr_map;
    for (int i = 0; i < this->natttr; ++i)
    {
        attr_map[attrnames[i]] = this->attrinds[i] - 1;
    }

    Relation *res = new Relation(*this);
    int count = 0;
    for (auto it1 = res->recs.begin(); it1 != res->recs.end();)
    {
        bool x1 = false;
        for (auto it2 : f->ops)
        {
            bool x2 = true;
            for (auto it3 : it2)
            {
                if (get<1>(it3) - 60 == 0)
                {
                    if (!(*((*it1)->attrptr[attr_map[get<0>(it3)]]) < *(get<2>(it3))))
                    {
                        x2 = false;
                        break;
                    }
                }
                else if (get<1>(it3) - 60 == 1)
                {
                    if (!(*((*it1)->attrptr[attr_map[get<0>(it3)]]) == *(get<2>(it3))))
                    {
                        x2 = false;
                        break;
                    }
                }
                else
                {
                    if (!(*((*it1)->attrptr[attr_map[get<0>(it3)]]) > *(get<2>(it3))))
                    {
                        x2 = false;
                        break;
                    }
                }
            }
            if (x2)
            {
                x1 = true;
                break;
            }
        }
        if (x1)
        {
            // select the record
            it1++;
        }
        else
        {
            // dont select the record
            it1 = this->recs.erase(it1);
            count++;
        }
    }
    res->nrecs = res->nrecs - count;
    return res;
}

Relation *Relation::Difference(string s1, string s2)
{
    for (auto it = this->attrnames.begin(); it != this->attrnames.end(); ++it)
    {
        if (*it == s1)
        {
            *it = s2;
        }
    }
    return this;
}

void Relation::get_attributes()
{
    for(int i = 0; i < natttr; i++)
    {
        cout << mapped_schema[i] << " ";
    }
    cout << endl;
}

// int main()
// {
//     vector<string> _attrnames1 = {"name", "age"};
//     vector<int> attr_type = {1, 2};
//     vector<int> _attrinds1 = {1, 2};
//     list<Record *> l1;
//     vector<Attr *> v1 = {new stringAttribute("Tanishq Choudhary"), new integerAttribute(19)};
//     l1.push_back(new Record(v1));
//     v1 = {new stringAttribute("Utsav Garg"), new integerAttribute(19)};
//     l1.push_back(new Record(v1));
//     Relation R1(2, 1, _attrnames1, _attrinds1, attr_type, l1);
//     R1.disp();

//     vector<string> _attrnames2 = {"age", "name"};
//     vector<int> _attrinds2 = {1, 2};
//     list<Record *> l2;
//     vector<Attr *> v2 = {new integerAttribute(19), new stringAttribute("Utsav Garg")};
//     l2.push_back(new Record(v2));
//     l2.push_back(new Record(v2));
//     Relation R2(2, 1, _attrnames2, _attrinds2, attr_type, l2);
//     R2.disp();

//     struct DNFformula f;
//     list<tuple<string, char, Attr *>> l3;
//     //.push_back(make_tuple("name", '=', new stringAttribute("Tanishq Choudhary")));
//     l3.push_back(make_tuple("age", '>', new integerAttribute(18)));
//     f.ops.push_back(l3);

//     Relation *R3 = R1.Union(&f);
//     R3->delete_copies();
//     R3->relation_print();

//     return 0;
// }

void Relation::relation_print()const
    {
        if (recs.empty() == true)
        {
            cout << "Relation is empty!" << endl;
            return;
        }
        fort::utf8_table table;
        table.set_border_style(FT_NICE_STYLE);
        table.column(0).set_cell_text_align(fort::text_align::center);
        table.column(2).set_cell_text_align(fort::text_align::center);

        table << fort::header;
        for (int i = 0; i < natttr; i++)
        {
            table << attrnames[i];
        }
        table << fort::endr;
        for (auto it = recs.begin(); it != recs.end(); it++)
        {
            for (int i = 0; i < natttr; i++)
            {
                if (attribute_type[i] == 2)
                {
                    table << ((integerAttribute *)((*it)->attrptr[i]))->get_value();
                    continue;
                }
                if (attribute_type[i] == 1)
                {
                    table << ((stringAttribute *)((*it)->attrptr[i]))->get_value();
                    continue;
                }
                if (attribute_type[i] == 3)
                {
                    table << ((floatAttribute *)((*it)->attrptr[i]))->get_value();
                    continue;
                }
            }
            table << fort::endr;
        }
        table << fort::endr;
        std::cout << table.to_string() << std::endl;

        // for (int i = 0; i < natttr; i++)
        // {
        //     cout << attrnames[i] << " ";
        // }
        // cout << endl;
        // for (auto it = recs.begin(); it != recs.end(); it++)
        // {
        //     (*it)->print_record();
        // }
    }