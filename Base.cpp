//
//  Base.cpp
//  CS109_SRI_CommandLine
//
//  Created by Kory Brown on 3/13/17.
//  Copyright © 2017 Kory Brown. All rights reserved.
//

#include "Base.hpp"

Base:: Base()
{
    
}

Base:: ~Base()
{
    
}


void Base:: parseKey(string input)
{
    string delimiter = "(";
    size_t pos = 0; // position of delimiter
    string key = ""; // holds the key or fact name
    
    pos = input.find(delimiter);
    key = input.substr(0, pos); // assings string from given input up to delimiter
    
    this->key = key;
}

void Base:: parseDefition(string input)
{
    string delimiter = "(";
    string delimiter2 = ",";
    size_t pos = 0; // position of delimiter
    
    vector<string> parameters; // holds each parameter
    
    pos = input.find(delimiter); // find the
    string temp = input.substr(0, pos);
    pos++; // eats delimiter;
    
    string parsedInput = input.substr(pos, input.length());
    while ((pos = parsedInput.find(delimiter2)) != string::npos)  // will loop through as many parameters except the last one
    {
        parameters.push_back(parsedInput.substr(0, pos));
        
        pos++; // eats delimiter
        
        parsedInput = parsedInput.substr(pos, input.length());
        if (parsedInput[2] == ')')
            break;
    }
    
    // if loop breaks theres always going to be one parameter left to store
    delimiter = ")";
    pos = parsedInput.find(delimiter);
    parameters.push_back(parsedInput.substr(0, pos));
    
    def = parameters;
}

//void Base:: storeBase(string k, vector<string> d)
//{
//    key = k;
//    def = d;
//}

void Base:: setKey(string k)
{
    key = k;
}

void Base:: setDefintion(vector<string> d)
{
    def = d;
}

string Base:: getKey()
{
    return key;
}

vector<string> Base:: getDefinition()
{
    return def;
}

