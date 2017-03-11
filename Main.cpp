//Main.cpp

#include "Common.hpp"
#include "Interface.hpp"


 vector<vector<vector<string>>> retrieveFact()
{
    vector<vector<vector<string>>> blah;
    
    return blah;
}


int main() {
    
    Interface i;
    i.run();
    
    
    vector<future<vector<vector<vector<string>>>>> thread;
    
//    thread.push_back(async(<#std::launch __policy#>, <#_Fp &&__f#>, <#_Args &&__args...#>)));
    async(retrieveFact);

    
    
    return 0;
    
}
