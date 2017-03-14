//
//  Parse.hpp
//  CS109_SRI_CommandLine
//
//  Created by Kory Brown on 3/13/17.
//  Copyright © 2017 Kory Brown. All rights reserved.
//

#ifndef Parse_hpp
#define Parse_hpp

#include <stdio.h>
#include "Rule.hpp"
#include "Fact.hpp"
#include "Helper.hpp"


class Parse
{
public:
    Parse();
    ~Parse();
    void ParseQuery(string);
    void parseCommand(string);
    void parseDefinition(char,string);

    
};

#endif /* Parse_hpp */
