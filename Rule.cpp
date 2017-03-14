//
//  Rule.cpp
//  CS109_SRI_CommandLine
//
//  Created by Kory Brown on 3/13/17.
//  Copyright © 2017 Kory Brown. All rights reserved.
//

#include "Rule.hpp"


void Rule:: setParam(vector<string> p)
{
    keyParam = p;
}

string Base:: getKey()
{
    return key;
}
