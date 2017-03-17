//
//  Threading.cpp
//  109 Project
//
//  Created by Deshawn Rivers on 3/17/17.
//  Copyright © 2017 Deshawn Rivers. All rights reserved.
//

#include "Threading.hpp"

future<vector<vector<string>>>& Threading:: getFutures()
{
    return futures;
}

int& Threading :: getID()
{
    return threadID;
}

Threading::Threading(int id)
{
    threadID = id;
}
