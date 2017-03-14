//
//  Rule.cpp
//  CS109_SRI_CommandLine
//
//  Created by Kory Brown on 3/13/17.
//  Copyright © 2017 Kory Brown. All rights reserved.
//

#include "Rule.hpp"

Rule:: Rule()
{
    
}

Rule:: Rule(string k, vector<string> d, vector<string> kp)
{
    key = k;
    def = d;
    keyParam = kp;
}

Rule:: ~Rule()
{
    
}

void Rule:: parseParams(string input)
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

void Rule:: parseDefinition(string input)
{
    
    vector<string> param;
    string delimiter = ":-";
    size_t pos = input.find(delimiter);
    pos++; // eats up delimiter :
    pos++; // eats up delimiter -
    
    delimiter = " ";
    pos++; // eats up delimiter ' '(space)
    
    string parsedInput = input.substr(pos, input.length());
    while ((pos = parsedInput.find(delimiter)) != string::npos)  // will loop through as many parameters except the last one
    {
        param.push_back(parsedInput.substr(0, pos));

        pos++; // eats delimiter
        parsedInput = parsedInput.substr(pos, input.length());
    }
    
    delimiter = "\n";
    pos = parsedInput.find(delimiter);
    param.push_back(parsedInput.substr(0, pos));

    def = param;
}

void Rule:: storeBase(string k, vector<string> d, vector<string> kp)
{
    key = k;
    def = d;
    keyParam = kp;
}

void Rule:: setParam(vector<string> p)
{
    keyParam = p;
}

vector<string> Rule:: getKeyParam()
{
    return keyParam;
}
