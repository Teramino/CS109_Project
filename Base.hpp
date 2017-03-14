//
//  Base.hpp
//  CS109_SRI_CommandLine
//
//  Created by Kory Brown on 3/13/17.
//  Copyright © 2017 Kory Brown. All rights reserved.
//

#ifndef Base_hpp
#define Base_hpp

#include "Common.hpp"

class Base
{
protected:
    string key;
    vector<string> def;
    
public:
    Base();
    ~Base();
    
    
    virtual void parseKey(string);
    virtual void parseDefition(string input);
//    virtual void storeBase(string k, vector<string> def);
//    virtual void dropBase(string command)=0;
    
    void setKey(string);
    void setDefintion(vector<string>);
    string getKey();
    vector<string>getDefinition();
    
};


#endif /* Base_hpp */
