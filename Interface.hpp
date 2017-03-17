//Interface.hpp

#ifndef Interface_hpp
#define Interface_hpp

#include "Common.hpp"
#include "Transactional_Commands.hpp"
#include "Helper.hpp"

class Interface{
    
public:
     void run(); 
    string start();
    string display();
    void test(char*);
    string clientInput(char*);
};

#endif /* Interface_hpp */
