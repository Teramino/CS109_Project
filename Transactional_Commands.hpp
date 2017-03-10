//Transactional_Commands.hpp


#ifndef Transactional_Commands_hpp
#define Transactional_Commands_hpp

#include "Common.hpp"


typedef void (*command_operations)(string);

class Helper; // foward declaration

class Transactional_Commands {
//    friend class Helper;
private:
    map<string, command_operations> commandMap;
    //changed it back to a non static vector due to linker errors
    vector<tuple<string,vector<string>>> fact;
    vector<tuple<string,vector<string>,vector<string>>> rule;
    
    
public:
    Transactional_Commands();
    map<string,command_operations>& getMapCommand(); // getter
    //changed it back to a non static vector due to linker errors
    vector<tuple<string,vector<string>>>& getFact(); // getter
    vector<tuple<string,vector<string>,vector<string>>>& getRule(); // getter
    
    static void loadCommand(string);
    static void dumpCommand(string);
    static void inferenceCommand(string);
    static void dropCommand(string);
    static void factCommand(string);
    static void ruleCommand(string);
	//void print();
};

#endif /* Transactional_Commands_hpp */
