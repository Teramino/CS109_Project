//Transactional_Commands.cpp

#include "Transactional_Commands.hpp"
#include "Helper.hpp" // foward declaration


Transactional_Commands:: Transactional_Commands(){
    
    commandMap["FACT"] = factCommand;
    commandMap["RULE"] = ruleCommand;
    commandMap["DROP"] = dropCommand;
    commandMap["INFERENCE"] = inferenceCommand;
    commandMap["LOAD"] = loadCommand;
    commandMap["DUMP"] = dumpCommand;
    
    
//    cout << "Transactional Command initialized\n";

}

// ===================================================================================
// 	LOAD
// ===================================================================================
// 	Load facts and rules, into the KB and the RB respectively from a file. 
//
//	Input: 
//		path [IN] - string containing the filename given from the transactional
//			command.
//
// ===================================================================================
void Transactional_Commands:: loadCommand(string path){
    Helper:: instance()->LoadHelp(path);

}

// ===================================================================================
// 	DUMP
// ===================================================================================
//	Save the facts and rules saved in the runtime KB and RB into a file in a format 
//	that can be loaded later.
//
//	Input: 
//		path [IN] - string containing the filename given from the transactional
//			command.
//
// ===================================================================================
void Transactional_Commands:: dumpCommand(string path) //vector<tuple<string,vector<string>>>& base)
{
    Helper:: instance()->DumpHelp(path);
}

void Transactional_Commands:: inferenceCommand(string command)
{  
	Helper:: instance()->ParseQuery(command);
}

void Transactional_Commands:: dropCommand(string command)
{
    Helper:: instance()->dropBase(command);
}

void Transactional_Commands:: factCommand(string fact)
{
    Helper:: instance()->parseDefinition('f',fact);
}

void Transactional_Commands:: ruleCommand(string rule)
{
    Helper:: instance()->parseDefinition('r',rule);
}

typedef void (*command_operations)(string);
map<string,command_operations>& Transactional_Commands:: getMapCommand(){ return commandMap; }

vector<tuple<string,vector<string>>>& Transactional_Commands:: getFact(){ return fact; }

vector<tuple<string,vector<string>,vector<string>>>& Transactional_Commands:: getRule(){ return rule; }
