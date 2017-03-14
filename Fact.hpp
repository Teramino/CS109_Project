//
//  Fact.hpp
//  CS109_SRI_CommandLine
//
//  Created by Kory Brown on 3/13/17.
//  Copyright © 2017 Kory Brown. All rights reserved.
//

#ifndef Fact_hpp
#define Fact_hpp

#include "Common.hpp"
#include "Base.hpp"

class Fact: public Base
{
public:
    Fact();
    Fact(string k, vector<string> d);
    ~Fact();
    
};

#endif /* Fact_hpp */
