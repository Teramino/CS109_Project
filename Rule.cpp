//
//  Rule.cpp
//  CS109_SRI_CommandLine
//
//  Created by Kory Brown on 3/13/17.
//  Copyright © 2017 Kory Brown. All rights reserved.
//

#include "Rule.hpp"


vector<string> Rule:: parseParams(string input)
{
    
    vector<string> param;
    string delimiter = ":-";
    size_t pos = input.find(delimiter);
    //    cout << "----------------------------------------" << endl;
    //    cout << "Key: " << input.substr(0, pos) << endl;
    pos++; // eats up delimiter :
    pos++; // eats up delimiter -
    
    delimiter = " ";
    pos++; // eats up delimiter ' '(space)
    
    string parsedInput = input.substr(pos, input.length());
    
    while ((pos = parsedInput.find(delimiter)) != string::npos)  // will loop through as many parameters except the last one
    {
        param.push_back(parsedInput.substr(0, pos));
        //        cout << "Parameter(" << count++ << "): " << param[param.size()-1] << endl;
        pos++; // eats delimiter
        parsedInput = parsedInput.substr(pos, input.length());
    }
    
    delimiter = "\n";
    pos = parsedInput.find(delimiter);
    param.push_back(parsedInput.substr(0, pos));
    //    cout << "Parameter(" << count << "): " << param[param.size()-1] << endl;
    //    cout <<"----------------------------------------"<<endl;
    
    return param;
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
