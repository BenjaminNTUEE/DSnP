/****************************************************************************
  FileName     [ p2Json.cpp ]
  PackageName  [ p2 ]
  Synopsis     [ Define member functions of class Json and JsonElem ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2018-present DVLab, GIEE, NTU, Taiwan ]
****************************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "p2Json.h"

using namespace std;

// Implement member functions of class Row and Table here
bool
Json::read(const string& jsonFile)
{
   fstream file;
   file.open(jsonFile, ios::in);
   if(!file) return false;
   string input, key, value;
   getline(file, input);

   while(1)
   {
       file >> input;       //read the key
       if(input=="}") break;                //break when EOF
       else if(input==",") file >> input;   //ignore , between two elements
       //cout << input << " ";

       key = key.assign(input, 1, input.size()-2);  //ignore " that mark the key
       file >> input;       //ignore : between key and value
       //cout << input << " ";
       file >> input;       //read the value of the key
       //cout << input << endl;
       value = input;
       Json::add(key, atoi(value.c_str()));
   }
   return true; // TODO
}

void Json::add(string &k, int v)
{
    JsonElem addNew(k, v);
    _obj.push_back(addNew);
}

void Json::print()
{
    if(_obj.size()==0)
    {
        cout << "{" << endl << "}" << endl;
        return;
    }

    cout << "{" << endl;
    for(int i=0; i<_obj.size()-1; i++) cout << "  " << _obj[i] << "," << endl;
    cout << "  " << _obj[_obj.size()-1] << endl << "}" << endl;
}

void Json::sum()
{
    if(_obj.size()==0)
    {
        cout << "Error: No element found!!" << endl;
        return;
    }
    int sum_=0;
    for(int i=0; i<_obj.size(); i++) sum_ += _obj[i]._value;

    cout << "The summation of the values is: " << sum_ << "." << endl;
}

void Json::ave()
{
    if(_obj.size()==0)
    {
        cout << "Error: No element found!!" << endl;
        return;
    }
    int sum_=0.0;
    for(int i=0; i<_obj.size(); i++) sum_ += _obj[i]._value;
    double ave_ = (double)sum_ / (double)_obj.size();

    cout << "The average of the values is: " << fixed << setprecision(1) << ave_ << "." << endl;
}

void Json::max()
{
    if(_obj.size()==0)
    {
        cout << "Error: No element found!!" << endl;
        return;
    }

    int M = 0;
    for(int i=0; i<_obj.size(); i++)
        if(_obj[i]._value > _obj[M]._value) M = i;

    cout << "The maximum element is: { " << _obj[M] << " }." << endl;
}

void Json::min()
{
    if(_obj.size()==0)
    {
        cout << "Error: No element found!!" << endl;
        return;
    }

    int m = 0;
    for(int i=0; i<_obj.size(); i++)
        if(_obj[i]._value < _obj[m]._value) m = i;

    cout << "The minimum element is: { " << _obj[m] << " }." << endl;
}

ostream&
operator << (ostream& os, const JsonElem& j)
{
   return (os << "\"" << j._key << "\" : " << j._value);
}