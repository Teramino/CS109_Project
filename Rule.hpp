//
//  Rule.hpp
//  CS109_SRI_CommandLine
//
//  Created by Kory Brown on 3/13/17.
//  Copyright © 2017 Kory Brown. All rights reserved.
//

#ifndef Rule_hpp
#define Rule_hpp

#include "Common.hpp"
#include "Base.hpp"

class Rule: public Base
{
private:
    vector<string> keyParam;
    
public:
    Rule();
    ~Rule();
    
    void setParam(vector<string>);
    vector<string> getParam();
    
};

#endif /* Rule_hpp */
