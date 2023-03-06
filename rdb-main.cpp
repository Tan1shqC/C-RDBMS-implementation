#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <tuple>
#include <algorithm>
#include "rdb-join.cpp"

using namespace std;

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
    string_again:
        cin >> temp;
        // checking if same string in attrnames is entered twice
        for (int j = 0; j < attrnames.size(); j++)
        {
            if (attrnames[j] == temp)
            {
                cout << "Same string in attrnames is entered twice! Enter again: ";
                i--;
                goto string_again;
            }
        }
        int type;
    type_again:
        cin >> type;
        if (type > 4 || type < 1)
        {
            cout << "Invalid Attribute type! Enter again: ";
            goto type_again;
        }
        int temp1;
    temp1_again:
        cin >> temp1;
        if (temp1 > natttr || temp1 < 1)
        {
            cout << "Invalid Mapping schema! Enter again: ";
            goto temp1_again;
        }
        // checking if same integer in attrinds is entered twice
        for (int j = 0; j < attrinds.size(); j++)
        {
            if (attrinds[j] == temp1)
            {
                cout << "Same integer in attrinds is entered twice! Enter again: ";
                goto temp1_again;
            }
        }
        attribute_type.push_back(type);
        attrnames.push_back(temp);
        attrinds.push_back(temp1 - 1);
    }
    Relation *r = new Relation(natttr, attrnames, attrinds, attribute_type);
    cout << "Enter the number of records : ";
    cin >> nrecs;
    // if the entered charater is not a number then promt the user to enter again
    // while (!(cin >> nrecs))
    // {
    //     cout << "Invalid input! Enter again: ";
    //     cin.clear();
    //     cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
    cout << "7 :: Create a DNF formula." << endl;
    cout << "8 :: Exit the Database." << endl;
    int choice;
    cin >> choice;
    switch (choice)
    {
        if (choice < 1 || choice > 7)
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
            num_again:
                cin >> num;
                if (num > Database.size() || num < 1)
                {
                    cout << "Invalid input! Enter again: ";
                    goto num_again;
                }
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
            add_again:
                cin >> num;
                if (num > Database.size() || num < 1)
                {
                    cout << "Invalid input! Enter again: ";
                    goto add_again;
                }
                auto it = Database.begin();
                for (int i = 1; i < num; i++)
                {
                    it++;
                }
                cout << (*it).second << "!!" << endl;
                (*it).first->disp();
                (*it).first->AddRecord();
                cout << "Record added successfully!" << endl;
                (*it).first->disp();
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
        _add_again:
            cin >> num;
            if (num > Database.size() || num < 1)
            {
                cout << "Invalid input! Enter again: ";
                goto _add_again;
            }
            auto it = Database.begin();
            for (int i = 1; i < num; i++)
            {
                it++;
            }
            cout << endl;
            cout << (*it).second << "!!" << endl;
            (*it).first->disp();
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
            cout << "7 :: Retutn to Home." << endl;
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
                num1_again:
                    cin >> num1;
                    if (num1 > Database.size() || num1 < 1)
                    {
                        cout << "Invalid input! Enter again: ";
                        goto num1_again;
                    }
                    auto it1 = Database.begin();
                    for (int i = 1; i < num1; i++)
                    {
                        it1++;
                    }
                num2_again:
                    cin >> num2;
                    if (num2 > Database.size() || num2 < 1)
                    {
                        cout << "Invalid input! Enter again: ";
                        goto num2_again;
                    }
                    auto it2 = Database.begin();
                    for (int i = 1; i < num2; i++)
                    {
                        it2++;
                    }
                    Relation *r = Union((*it1).first, (*it2).first);
                    cout << "Enter the name of the new Relation: ";
                    string name;
                    cin >> name;
                    Database.push_back(make_pair(r, name));
                    cout << "Relation created successfully!" << endl;
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
                _num1_again:
                    cin >> num1;
                    if (num1 > Database.size() || num1 < 1)
                    {
                        cout << "Invalid input! Enter again: ";
                        goto _num1_again;
                    }
                    auto it1 = Database.begin();
                    for (int i = 1; i < num1; i++)
                    {
                        it1++;
                    }
                _num2_again:
                    cin >> num2;
                    if (num2 > Database.size() || num2 < 1)
                    {
                        cout << "Invalid input! Enter again: ";
                        goto _num2_again;
                    }
                    auto it2 = Database.begin();
                    for (int i = 1; i < num2; i++)
                    {
                        it2++;
                    }
                    Relation *r = Difference((*it1).first, (*it2).first);
                    cout << "Enter the name of the new Relation: ";
                    string name;
                    cin >> name;
                    Database.push_back(make_pair(r, name));
                    cout << "Relation created successfully!" << endl;
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
                __num1_again:
                    cin >> num1;
                    if (num1 > Database.size() || num1 < 1)
                    {
                        cout << "Invalid input! Enter again: ";
                        goto __num1_again;
                    }
                    auto it1 = Database.begin();
                    for (int i = 1; i < num1; i++)
                    {
                        it1++;
                    }
                __num2_again:
                    cin >> num2;
                    if (num2 > Database.size() || num2 < 1)
                    {
                        cout << "Invalid input! Enter again: ";
                        goto __num2_again;
                    }
                    auto it2 = Database.begin();
                    for (int i = 1; i < num2; i++)
                    {
                        it2++;
                    }
                    Relation *r = cartesian_product((*it1).first, (*it2).first);
                    cout << "Enter the name of the new Relation: ";
                    string name;
                    cin >> name;
                    Database.push_back(make_pair(r, name));
                    cout << "Relation created successfully!" << endl;
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
                ___num1_again:
                    cin >> num1;
                    if (num1 > Database.size() || num1 < 1)
                    {
                        cout << "Invalid input! Enter again: ";
                        goto ___num1_again;
                    }
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
                    Relation *r = projection((*it1).first, attributes);
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
                if (Database.size() >= 1)
                {
                    cout << "The Database contains the following Relations:" << endl;
                    int i = 1;
                    for (auto it = Database.begin(); it != Database.end(); it++)
                    {
                        cout << (i++) << " :: " << it->second << endl;
                    }
                    cout << "Choose a Relation you want to take SELECTION of: ";
                    int num1;
                ____num1_again:
                    cin >> num1;
                    if (num1 > Database.size() || num1 < 1)
                    {
                        cout << "Invalid input! Enter again: ";
                        goto ____num1_again;
                    }
                    auto it1 = Database.begin();
                    for (int i = 1; i < num1; i++)
                    {
                        it1++;
                    }
                    cout << "Enter the attribute you want to select on: ";
                    string attr;
                    cin >> attr;
                    cout << "Enter the value you want to select on: ";
                    string val;
                    cin >> val;
                    //Relation *r = projection((*it1).first, attr, val);
                    cout << "Enter the name of the new Relation: ";
                    string name;
                    cin >> name;
                    // Database.push_back(make_pair(r, name));
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
                _____num1_again:
                    cin >> num1;
                    if (num1 > Database.size() || num1 < 1)
                    {
                        cout << "Invalid input! Enter again: ";
                        goto _____num1_again;
                    }
                    auto it1 = Database.begin();
                    for (int i = 1; i < num1; i++)
                    {
                        it1++;
                    }
                    // print all the attribute names of the chosen relation for user to choose from for renaming
                    cout << "The attributes of the chosen Relation are: " << endl;
                    (*it1).first->getAttributes();
                    cout << "Enter the attribute you want to rename!" << endl;
                    string attribute;
                    cin >> attribute;
                    cout << "Enter the new name of the attribute!" << endl;
                    string new_name;
                    cin >> new_name;
                    Relation *r = (*it1).first->Difference(attribute, new_name);
                    cout << "Relation RENAMED successfully!" << endl;
                    r->disp();
                }
                else
                {
                    cout << "The Database contains less than 1 Relations!" << endl;
                }
                goto home;
            }
            // 7 :: Return to main menu.
            case 7:
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
        // 7 :: Creating a new DNF formula.
        case 7:
        {
            cout << "Enter how many constraints you want to apply: ";
            int constraints;
            cin >> constraints;
            for (int i = 0; i < constraints; i++)
            {
                cout << "Enter 'STRING' - Name of Attribute, 'TYPE' - Attribute type, 'CHAR' - Bool Comparator operator, 'CONSTANT' - Value you want to compare with!" << endl;
                cout << "Enter" << endl
                     << "1 for String attribute." << endl
                     << "2 for Integer attribute." << endl
                     << "3 for Float attribute." << endl;
                string attr;
                cin >> attr;
                int type;
            type_again:
                cin >> type;
                Attr *_const;
                if (type == 1)
                {
                    string temp;
                    cin >> temp;
                    _const = new stringAttribute(temp);
                }
                else if (type == 2)
                {
                    int temp;
                    cin >> temp;
                    _const = new integerAttribute(temp);
                }
                else if (type == 3)
                {
                    float temp;
                    cin >> temp;
                    _const = new floatAttribute(temp);
                }
                else
                {
                    cout << "Invalid input! Enter TYPE again: " << endl;
                    goto type_again;
                }
                char _op;
                cin >> _op;
                tuple<string, char, Attr *> temp_comparator;
                temp_comparator = make_tuple(attr, _op, _const);
            }

            goto home;
        }
        case 8:
        {
            cout << "Thank you for using the Database Management System!" << endl;
            exit(0);
        }
            return 0;
        }
    }
}