//
//  Threading.hpp
//  109 Project
//
//  Created by Deshawn Rivers on 3/17/17.
//  Copyright © 2017 Deshawn Rivers. All rights reserved.
//

#ifndef Threading_hpp
#define Threading_hpp

#include "Common.hpp"


class Threading
{
private:
    int threadID;
    //vector<tuple<int,future<vector<vector<string>>>>> futures;
    future<vector<vector<string>>> futures;
    
    
    
public:
    future<vector<vector<string>>>& getFutures();
    Threading();
    Threading(int id);
    ~Threading();
    
    int &getID();
    
    
    
};




#endif /* Threading_hpp */


