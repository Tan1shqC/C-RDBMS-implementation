#include <iostream>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <tuple>
#include "rdb.h"

using namespace std;

integerAttribute::integerAttribute(int data = 0) : _data(data) {}

Attr &integerAttribute::clone() const
{
    integerAttribute *copy = new integerAttribute(*this);
    return *copy;
}

bool integerAttribute::operator==(const Attr &right) const
{
    const integerAttribute &_right = (const integerAttribute &)right;
    if (this->_data == _right._data)
        return true;
    else
        return false;
}
bool integerAttribute::operator!=(const Attr &right) const
{
    const integerAttribute &_right = (const integerAttribute &)right;
    if (this->_data != _right._data)
        return true;
    else
        return false;
}
bool integerAttribute::operator<(const Attr &right) const
{
    const integerAttribute &_right = (const integerAttribute &)right;
    if (this->_data < _right._data)
        return true;
    else
        return false;
}
bool integerAttribute::operator<=(const Attr &right) const
{
    const integerAttribute &_right = (const integerAttribute &)right;
    if (this->_data <= _right._data)
        return true;
    else
        return false;
}
bool integerAttribute::operator>(const Attr &right) const
{
    const integerAttribute &_right = (const integerAttribute &)right;
    if (this->_data > _right._data)
        return true;
    else
        return false;
}
bool integerAttribute::operator>=(const Attr &right) const
{
    const integerAttribute &_right = (const integerAttribute &)right;
    if (this->_data >= _right._data)
        return true;
    else
        return false;
}
void integerAttribute::disp() const
{
    cout << this->_data << " ";
}
int integerAttribute::get_value()
{
    return this->_data;
}

floatAttribute::floatAttribute(float data = 0) : _data(data) {}

float floatAttribute::get_value()
{
    return this->_data;
}

Attr &floatAttribute::clone() const
{
    floatAttribute *copy = new floatAttribute(*this);
    return *copy;
}

bool floatAttribute::operator==(const Attr &right) const
{
    const floatAttribute &_right = (const floatAttribute &)right;
    if (this->_data == _right._data)
        return true;
    else
        return false;
}
bool floatAttribute::operator!=(const Attr &right) const
{
    const floatAttribute &_right = (const floatAttribute &)right;
    if (this->_data != _right._data)
        return true;
    else
        return false;
}
bool floatAttribute::operator<(const Attr &right) const
{
    const floatAttribute &_right = (const floatAttribute &)right;
    if (this->_data < _right._data)
        return true;
    else
        return false;
}
bool floatAttribute::operator<=(const Attr &right) const
{
    const floatAttribute &_right = (const floatAttribute &)right;
    if (this->_data <= _right._data)
        return true;
    else
        return false;
}
bool floatAttribute::operator>(const Attr &right) const
{
    const floatAttribute &_right = (const floatAttribute &)right;
    if (this->_data > _right._data)
        return true;
    else
        return false;
}
bool floatAttribute::operator>=(const Attr &right) const
{
    const floatAttribute &_right = (const floatAttribute &)right;
    if (this->_data >= _right._data)
        return true;
    else
        return false;
}
void floatAttribute::disp() const
{
    cout << this->_data << " ";
}

stringAttribute::stringAttribute(string data = "") : _data(data) {}

string stringAttribute::get_value()
{
    return this->_data;
}

Attr &stringAttribute::clone() const
{
    stringAttribute *copy = new stringAttribute(*this);
    return *copy;
}

bool stringAttribute::operator==(const Attr &right) const
{
    const stringAttribute &_right = (const stringAttribute &)right;
    if (this->_data == _right._data)
        return true;
    else
        return false;
}
bool stringAttribute::operator!=(const Attr &right) const
{
    const stringAttribute &_right = (const stringAttribute &)right;
    if (this->_data != _right._data)
        return true;
    else
        return false;
}
bool stringAttribute::operator<(const Attr &right) const
{
    const stringAttribute &_right = (const stringAttribute &)right;
    if (this->_data < _right._data)
        return true;
    else
        return false;
}
bool stringAttribute::operator<=(const Attr &right) const
{
    const stringAttribute &_right = (const stringAttribute &)right;
    if (this->_data <= _right._data)
        return true;
    else
        return false;
}
bool stringAttribute::operator>(const Attr &right) const
{
    const stringAttribute &_right = (const stringAttribute &)right;
    if (this->_data > _right._data)
        return true;
    else
        return false;
}
bool stringAttribute::operator>=(const Attr &right) const
{
    const stringAttribute &_right = (const stringAttribute &)right;
    if (this->_data >= _right._data)
        return true;
    else
        return false;
}
void stringAttribute::disp() const
{
    cout << this->_data << " ";
}