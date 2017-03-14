//Transactional_Commands.hpp


#ifndef Transactional_Commands_hpp
#define Transactional_Commands_hpp

#include "Common.hpp"
#include "Rule.hpp"
#include "Fact.hpp"



typedef void (*command_operations)(string);

class Helper; // foward declaration

class Transactional_Commands {
//    friend class Helper;
private:
    map<string, command_operations> commandMap;
    //changed it back to a non static vector due to linker errors
    vector<Fact*> facts;
    vector<Rule*> rules;
    
    
    
public:
    Transactional_Commands();
    ~Transactional_Commands();
    
    map<string,command_operations>& getMapCommand(); // getter
    //changed it back to a non static vector due to linker errors
    vector<Fact*>& getFacts(); // getter
    vector<Rule*>& getRules(); // getter

    
    static void loadCommand(string);
    static void dumpCommand(string);
    static void inferenceCommand(string);
    static void dropCommand(string);
    static void factCommand(string);
    static void ruleCommand(string);
    static vector<vector<vector<string>>> opFunction(string logicalOp, string key,vector<string> keyParams,vector<vector<string>> rule,vector<vector<string>> fact);

	//void print();
};

#endif /* Transactional_Commands_hpp */
