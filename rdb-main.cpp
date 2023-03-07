#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <tuple>
#include <algorithm>
#include "rdb-join.cpp"

Relation *Create_Relation()
{
    int natttr, nrecs;
    vector<string> attrnames;
    vector<int> attrinds, attribute_type;
    // cout << "Creating a relation!" << endl;
    cout << "Enter the number of attributes : ";
    cin >> natttr;

    cout << "Enter" << endl
         << "1 for String attribute." << endl
         << "2 for Integer attribute." << endl
         << "3 for Float attribute." << endl
         << "4 for Double attribute" << endl;
    for (int i = 0; i < natttr; i++)
    {
        cout << "Enter the ATTRIBUTE NAME and ATTRIBUTE TYPE and MAPPING SCHEMA to indices {1 - " << natttr << "}!! " << endl;
        string temp;
        cin >> temp;
        int type;
        cin >> type;
        int temp1;
        cin >> temp1;
        attribute_type.push_back(type);
        attrnames.push_back(temp);
        attrinds.push_back(temp1);
    }
    Relation *r = new Relation(natttr, 0, attrnames, attrinds, attribute_type);
    cout << "Enter the number of records : ";
    cin >> nrecs;
    // if the entered charater is not a number then promt the user to enter again
    // while (!(cin >> nrecs))
    // {
    // cout << "Invalid input! Enter again: ";
    // cin.clear();
    // cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // }
    for (int i = 0; i < nrecs; i++)
    {
        r->AddRecord();
    }
    return r;
}
int main()
{
    // DNF Formula;
    /*• Create a new empty table: the user can interactively enter the schema.
    • Delete an existing table with all data in it.
    • Add a record to a table.
    • Print a table in appropriate format.
    • Create a table from existing tables using the above developed operations.*/
    // using list of relations becuse it will be easier to delete a relation
    list<pair<Relation *, string>> Database;

home:
    cout << "Welcome to the Database Management System!" << endl;
    cout << "1 :: Create a Relation." << endl;
    cout << "2 :: Delete a Relation." << endl;
    cout << "3 :: Add a record to a Relation." << endl;
    cout << "4 :: Print a Relation." << endl;
    cout << "5 :: Create a Relation from existing Relations." << endl;
    cout << "6 :: View the Database." << endl;
    cout << "7 :: Exit the Database." << endl;
    int choice;
    cin >> choice;
    switch (choice)
    {
        if (choice > 7)
        {
            cout << "Invalid input! Enter again: ";
            goto home;
        }
        else
        {
        case 1:
        {
            cout << "Enter The Name of the Relation: ";
            string name;
            cin >> name;
            Relation *r = Create_Relation();
            Database.push_back(make_pair(r, name));
            cout << "Relation created successfully!" << endl;
            goto home;
        }
        case 2:
        {
            if (Database.size() != 0)
            {
                cout << "The Database contains the following Relations:" << endl;
                int i = 1;
                for (auto it = Database.begin(); it != Database.end(); it++)
                {
                    cout << (i++) << " :: " << it->second << endl;
                }
                cout << "Choose a Relation you want to delete: ";
                int num;
                cin >> num;
                auto it = Database.begin();
                for (int i = 1; i < num; i++)
                {
                    it++;
                }
                string temp = it->second;
                Database.erase(it);
                cout << "Relation \"" << temp << "\" deleted successfully!" << endl;
            }
            else
            {
                cout << "The Database is empty!" << endl;
            }
            goto home;
        }
        case 3:
        {
            if (Database.size() != 0)
            {
                cout << "The Database contains the following Relations:" << endl;
                int i = 1;
                for (auto it = Database.begin(); it != Database.end(); it++)
                {
                    cout << (i++) << " :: " << it->second << endl;
                }
                cout << "Choose a Relation you want to add a record to: ";
                int num;
                cin >> num;
                auto it = Database.begin();
                for (int i = 1; i < num; i++)
                {
                    it++;
                }
                cout << (*it).second << "!!" << endl;
                (*it).first->relation_print();
                (*it).first->AddRecord();
                cout << "Record added successfully!" << endl;
                (*it).first->relation_print();
            }
            else
            {
                cout << "The Database is empty!" << endl;
            }
            goto home;
        }
        // 4 :: Printing a Relation
        case 4:
        {
            if (Database.size() != 0)
            {
                cout << "The Database contains the following Relations:" << endl;
                int i = 1;
                for (auto it = Database.begin(); it != Database.end(); it++)
                {
                    cout << (i++) << " :: " << it->second << endl;
                }
            }
            else
            {
                cout << "The Database is empty!" << endl;
            }
            cout << "Choose a Relation you want to Print: ";
            int num;
            cin >> num;
            auto it = Database.begin();
            for (int i = 1; i < num; i++)
            {
                it++;
            }
            cout << endl;
            cout << (*it).second << "!!" << endl;
            (*it).first->relation_print();
            cout << endl;
            goto home;
        }
        case 5:
        {
            cout << "1 :: Take UNION of two Relations." << endl;
            cout << "2 :: Take DIFFERENCE of two Relations." << endl;
            cout << "3 :: Take CARTESIAN PRODUCT of two Relations." << endl;
            cout << "4 :: Take PROJECTION of a Relation." << endl;
            cout << "5 :: Take SELECTION of a Relation." << endl;
            cout << "6 :: Rename a column in a Relation." << endl;
            cout << "7 :: Take JOIN of two Relations." << endl;
            cout << "8 :: Retutn to Home." << endl;
            int temp;
            cin >> temp;
            switch (temp)
            {
            // 1 :: Take UNION of two Relations.
            case 1:
            {
                if (Database.size() >= 2)
                {
                    cout << "The Database contains the following Relations:" << endl;
                    int i = 1;
                    for (auto it = Database.begin(); it != Database.end(); it++)
                    {
                        cout << (i++) << " :: " << it->second << endl;
                    }
                    cout << "Choose two Relations you want to take UNION of: ";
                    int num1, num2;
                    cin >> num1;
                    auto it1 = Database.begin();
                    for (int i = 1; i < num1; i++)
                    {
                        it1++;
                    }
                    cin >> num2;
                    auto it2 = Database.begin();
                    for (int i = 1; i < num2; i++)
                    {
                        it2++;
                    }
                    Relation *r = Union((*it1).first, (*it2).first);
                    if (r != NULL)
                    {
                        cout << "Enter the name of the new Relation: ";
                        string name;
                        cin >> name;
                        Database.push_back(make_pair(r, name));
                        cout << "Relation created successfully!" << endl;
                    }
                    else
                    {
                        cout << "The two Relations are not compatible!" << endl;
                    }
                }
                else
                {
                    cout << "The Database contains less than 2 Relations!" << endl;
                }
                goto home;
            }
            // 2 :: Take DIFFERENCE of two Relations.
            case 2:
            {
                if (Database.size() >= 2)
                {
                    cout << "The Database contains the following Relations:" << endl;
                    int i = 1;
                    for (auto it = Database.begin(); it != Database.end(); it++)
                    {
                        cout << (i++) << " :: " << it->second << endl;
                    }
                    cout << "Choose two Relations you want to take DIFFERENCE of: ";
                    int num1, num2;
                    cin >> num1;
                    auto it1 = Database.begin();
                    for (int i = 1; i < num1; i++)
                    {
                        it1++;
                    }
                    cin >> num2;
                    auto it2 = Database.begin();
                    for (int i = 1; i < num2; i++)
                    {
                        it2++;
                    }
                    Relation *r = Difference((*it1).first, (*it2).first);
                    if (r != NULL)
                    {
                        cout << "Enter the name of the new Relation: ";
                        string name;
                        cin >> name;
                        Database.push_back(make_pair(r, name));
                        cout << "Relation created successfully!" << endl;
                    }
                    else
                    {
                        cout << "The two Relations are not compatible!" << endl;
                    }
                }
                else
                {
                    cout << "The Database contains less than 2 Relations!" << endl;
                }
                goto home;
            }
            // 3 :: Take CARTESIAN PRODUCT of two Relations.
            case 3:
            {
                if (Database.size() >= 2)
                {
                    cout << "The Database contains the following Relations:" << endl;
                    int i = 1;
                    for (auto it = Database.begin(); it != Database.end(); it++)
                    {
                        cout << (i++) << " :: " << it->second << endl;
                    }
                    cout << "Choose two Relations you want to take CARTESIAN PRODUCT of: ";
                    int num1, num2;
                    cin >> num1;
                    auto it1 = Database.begin();
                    for (int i = 1; i < num1; i++)
                    {
                        it1++;
                    }
                    cin >> num2;
                    auto it2 = Database.begin();
                    for (int i = 1; i < num2; i++)
                    {
                        it2++;
                    }
                    Relation *r = cartesian_product((*it1).first, (*it2).first);
                    if (r != NULL)
                    {
                        cout << "Enter the name of the new Relation: ";
                        string name;
                        cin >> name;
                        Database.push_back(make_pair(r, name));
                        cout << "Relation created successfully!" << endl;
                    }
                    else
                    {
                        cout << "The two Relations are not compatible!" << endl;
                    }
                }
                else
                {
                    cout << "The Database contains less than 2 Relations!" << endl;
                }
                goto home;
            }
            // 4 :: Take PROJECTION of a Relation.
            case 4:
            {
                if (Database.size() >= 1)
                {
                    cout << "The Database contains the following Relations:" << endl;
                    int i = 1;
                    for (auto it = Database.begin(); it != Database.end(); it++)
                    {
                        cout << (i++) << " :: " << it->second << endl;
                    }
                    cout << "Choose a Relation you want to take PROJECTION of: ";
                    int num1;
                    cin >> num1;
                    auto it1 = Database.begin();
                    for (int i = 1; i < num1; i++)
                    {
                        it1++;
                    }
                    cout << "Enter the attributes you want to project on! (Enter 'end' to stop)" << endl;
                    list<string> attributes;
                    // take input of attributes
                    while (true)
                    {
                        string attr;
                        cin >> attr;
                        if (attr == "end")
                        {
                            break;
                        }
                        attributes.push_back(attr);
                    }
                    Relation *r = (*it1).first->projection(attributes);
                    cout << "Enter the name of the new Relation: ";
                    string name;
                    Database.push_back(make_pair(r, name));
                    cout << "Relation created successfully!" << endl;
                }
                else
                {
                    cout << "The Database contains less than 1 Relations!" << endl;
                }
                goto home;
            }
            // 5 :: Take SELECTION of a Relation.
            case 5:
            {
                DNFformula _formula;
                if (Database.size() >= 1)
                {
                    cout << "The Database contains the following Relations:" << endl;
                    int i = 1;
                    auto it = Database.begin();
                    for (it; it != Database.end(); it++)
                    {
                        cout << (i++) << " :: " << it->second << endl;
                    }
                    cout << "Choose a Relation you want to take SELECTION of: ";
                    int num1;
                    cin >> num1;
                    auto it1 = Database.begin();
                    for (int i = 1; i < num1; i++)
                    {
                        it1++;
                    }
                    cout << "Enter how many constraints you want to apply: ";
                    int constraints;
                    cin >> constraints;
                    for (int i = 0; i < constraints; i++)
                    {
                        cout << "These are the Attribute names of the Relation " << it1->second << endl;
                        it1->first->get_attributes();
                        cout << "Enter how many comparators in a constraint: ";
                        int num;
                        cin >> num;
                        list<tuple<string, char, Attr *>> temp_list;
                        for (int i = 0; i < num; i++)
                        {
                            cout << "Enter 'STRING' - Name of Attribute, 'CHAR' - Bool Comparator operator, 'CONSTANT' - Value you want to compare with!" << endl;
                            string attr;
                            cin >> attr;
                            char _op;
                            cin >> _op;
                            map<string, int> name_type = (*it1).first->name_map_type;
                            Attr *_const;
                            if (name_type[attr] == 1)
                            {
                                string temp;
                                cin >> temp;
                                _const = new stringAttribute(temp);
                            }
                            else if (name_type[attr] == 2)
                            {
                                int temp;
                                cin >> temp;
                                _const = new integerAttribute(temp);
                            }
                            else if (name_type[attr] == 3)
                            {
                                float temp;
                                cin >> temp;
                                _const = new floatAttribute(temp);
                            }
                            tuple<string, char, Attr *> temp_comparator;
                            temp_comparator = make_tuple(attr, _op, _const);
                            cout << "Constraint Created - < " << attr << " " << _op << " " << temp << " > !!" << endl;
                            temp_list.push_back(temp_comparator);
                        }
                        _formula.ops.push_back(temp_list);
                    }
                    Relation *r = it1->first->Union(&_formula);
                    // Relation *r = B._selection((*it1).first, attr, val);
                    cout << "Enter the name of the new Relation: ";
                    string name;
                    cin >> name;
                    Database.push_back(make_pair(r, name));
                    cout << "Relation created successfully!" << endl;
                }
                else
                {
                    cout << "The Database contains less than 1 Relations!" << endl;
                }
                goto home;
            }
            // 6 :: Take RENAME of a Relation.
            case 6:
            {
                if (Database.size() >= 1)
                {
                    cout << "The Database contains the following Relations:" << endl;
                    int i = 1;
                    for (auto it = Database.begin(); it != Database.end(); it++)
                    {
                        cout << (i++) << " :: " << it->second << endl;
                    }
                    cout << "Choose a Relation you want to take RENAME of: ";
                    int num1;
                    cin >> num1;
                    auto it1 = Database.begin();
                    for (int i = 1; i < num1; i++)
                    {
                        it1++;
                    }
                    // print all the attribute names of the chosen relation for user to choose from for renaming
                    cout << "The attributes of the chosen Relation are: " << endl;
                    (*it1).first->get_attributes();
                    cout << "Enter the attribute you want to rename!" << endl;
                    string attribute;
                    cin >> attribute;
                    cout << "Enter the new name of the attribute!" << endl;
                    string new_name;
                    cin >> new_name;
                    Relation *r = (*it1).first->Difference(attribute, new_name);
                    cout << "Relation RENAMED successfully!" << endl;
                    r->relation_print();
                }
                else
                {
                    cout << "The Database contains less than 1 Relations!" << endl;
                }
                goto home;
            }
            // 7 :: Take JOIN of two Relations.
            case 7:
            {
                if (Database.size() >= 2)
                {
                    cout << "The Database contains the following Relations:" << endl;
                    int i = 1;
                    for (auto it = Database.begin(); it != Database.end(); it++)
                    {
                        cout << (i++) << " :: " << it->second << endl;
                    }
                    cout << "Choose the first Relation you want to take JOIN of: ";
                    int num1;
                    cin >> num1;
                    auto it1 = Database.begin();
                    for (int i = 1; i < num1; i++)
                    {
                        it1++;
                    }
                    cout << "Choose the second Relation you want to take JOIN of: ";
                    int num2;
                    cin >> num2;
                    auto it2 = Database.begin();
                    for (int i = 1; i < num2; i++)
                    {
                        it2++;
                    }
                    list<string> common_atteibutes;
                    for (auto it = (*it1).first->name_map_type.begin(); it != (*it1).first->name_map_type.end(); it++)
                    {
                        if ((*it2).first->name_map_type.find(it->first) != (*it2).first->name_map_type.end())
                        {
                            common_atteibutes.push_back(it->first);
                        }
                    }
                    cout << "Enter the name of the new Relation: ";
                    string name;
                    cin >> name;
                    Relation *r = naturaljoin((*it1).first, (*it2).first, common_atteibutes);
                    Database.push_back(make_pair(r, name));
                    cout << "Relation created successfully!" << endl;
                }
                else
                {
                    cout << "The Database contains less than 2 Relations!" << endl;
                }
                goto home;
            }
            // 8 :: Exiting the program
            case 8:
            {
                goto home;
            }
            }
        }
        case 6:
        {
            if (Database.size() != 0)
            {
                cout << "The Database contains the following Relations:" << endl;
                int i = 1;
                for (auto it = Database.begin(); it != Database.end(); it++)
                {
                    cout << (i++) << " :: " << it->second << endl;
                }
            }
            else
            {
                cout << "The Database is empty!" << endl;
            }
            goto home;
        }
        // 7 :: Taking JOIN of two Relations.
        case 7:
        {
            cout << "Thank you for using the Database Management System!" << endl;
            exit(0);
        }
            return 0;
        }
    }
}