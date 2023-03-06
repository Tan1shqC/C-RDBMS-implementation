#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <tuple>
#include "rdb.h"

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

class integerAttribute : public Attr
{
    int _data;

public:
    integerAttribute(int data = 0) : _data(data) {}

    Attr &clone()const
    {
        integerAttribute *copy = new integerAttribute(*this);
        return *copy;
    }

    bool operator==(const Attr &right) const
    {
        const integerAttribute &_right = (const integerAttribute &)right;
        if (this->_data == _right._data)
            return true;
        else
            return false;
    }
    bool operator!=(const Attr &right) const
    {
        const integerAttribute &_right = (const integerAttribute &)right;
        if (this->_data != _right._data)
            return true;
        else
            return false;
    }
    bool operator<(const Attr &right) const
    {
        const integerAttribute &_right = (const integerAttribute &)right;
        if (this->_data < _right._data)
            return true;
        else
            return false;
    }
    bool operator<=(const Attr &right) const
    {
        const integerAttribute &_right = (const integerAttribute &)right;
        if (this->_data <= _right._data)
            return true;
        else
            return false;
    }
    bool operator>(const Attr &right) const
    {
        const integerAttribute &_right = (const integerAttribute &)right;
        if (this->_data > _right._data)
            return true;
        else
            return false;
    }
    bool operator>=(const Attr &right) const
    {
        const integerAttribute &_right = (const integerAttribute &)right;
        if (this->_data >= _right._data)
            return true;
        else
            return false;
    }
    void disp() const
    {
        cout << this->_data << " ";
    }
};
class floatAttribute : public Attr
{
    float _data;

public:
    floatAttribute(float data = 0) : _data(data) {}

    Attr &clone()const
    {
        floatAttribute *copy = new floatAttribute(*this);
        return *copy;
    }

    bool operator==(const Attr &right) const
    {
        const floatAttribute &_right = (const floatAttribute &)right;
        if (this->_data == _right._data)
            return true;
        else
            return false;
    }
    bool operator!=(const Attr &right) const
    {
        const floatAttribute &_right = (const floatAttribute &)right;
        if (this->_data != _right._data)
            return true;
        else
            return false;
    }
    bool operator<(const Attr &right) const
    {
        const floatAttribute &_right = (const floatAttribute &)right;
        if (this->_data < _right._data)
            return true;
        else
            return false;
    }
    bool operator<=(const Attr &right) const
    {
        const floatAttribute &_right = (const floatAttribute &)right;
        if (this->_data <= _right._data)
            return true;
        else
            return false;
    }
    bool operator>(const Attr &right) const
    {
        const floatAttribute &_right = (const floatAttribute &)right;
        if (this->_data > _right._data)
            return true;
        else
            return false;
    }
    bool operator>=(const Attr &right) const
    {
        const floatAttribute &_right = (const floatAttribute &)right;
        if (this->_data >= _right._data)
            return true;
        else
            return false;
    }
    void disp() const
    {
        cout << this->_data << " ";
    }
};
class stringAttribute : public Attr
{
    string _data;

public:
    stringAttribute(string data = "") : _data(data) {}

    Attr &clone()const
    {
        stringAttribute *copy = new stringAttribute(*this);
        return *copy;
    }

    bool operator==(const Attr &right) const
    {
        const stringAttribute &_right = (const stringAttribute &)right;
        if (this->_data == _right._data)
            return true;
        else
            return false;
    }
    bool operator!=(const Attr &right) const
    {
        const stringAttribute &_right = (const stringAttribute &)right;
        if (this->_data != _right._data)
            return true;
        else
            return false;
    }
    bool operator<(const Attr &right) const
    {
        const stringAttribute &_right = (const stringAttribute &)right;
        if (this->_data < _right._data)
            return true;
        else
            return false;
    }
    bool operator<=(const Attr &right) const
    {
        const stringAttribute &_right = (const stringAttribute &)right;
        if (this->_data <= _right._data)
            return true;
        else
            return false;
    }
    bool operator>(const Attr &right) const
    {
        const stringAttribute &_right = (const stringAttribute &)right;
        if (this->_data > _right._data)
            return true;
        else
            return false;
    }
    bool operator>=(const Attr &right) const
    {
        const stringAttribute &_right = (const stringAttribute &)right;
        if (this->_data >= _right._data)
            return true;
        else
            return false;
    }
    void disp() const
    {
        cout << this->_data << " ";
    }
};

// int main()
// {
//     Attr *p;
//     Attr *q;
//     p = new integerAttribute(2);
//     q = new integerAttribute(3);
//     Attr *s;
//     Attr *r;
//     r = &(p->clone());
//     s = &(q->clone());
//     cout << (r < s) << endl;
//     return 0;
// }