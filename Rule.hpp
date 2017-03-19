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
    Rule(string k, vector<string> d, vector<string> kp);
    ~Rule(); 
    
    void parseParams(string);
    virtual void parseDefinition(string);
    virtual void storeBase(string,vector<string>,vector<string>);
    
<<<<<<< HEAD
   
=======
>>>>>>> 4029a5e05469b58197ad6c628e48df24fca137e4
    vector<string> getKeyParam();
    
};

#endif /* Rule_hpp */
