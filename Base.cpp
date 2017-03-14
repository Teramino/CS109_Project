//
//  Base.cpp
//  CS109_SRI_CommandLine
//
//  Created by Kory Brown on 3/13/17.
//  Copyright © 2017 Kory Brown. All rights reserved.
//

#include "Base.hpp"

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
