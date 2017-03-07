//Helper.hpp

#ifndef Helper_hpp
#define Helper_hpp

#include "Common.hpp"

class Transactional_Commands; // forward declaration

// Singleton Class
class Helper
{
    
private:
    Helper(); // constructor is private to no instances of class can be created (Singleton)
    
    Transactional_Commands* tCommands;
    static Helper * h_instance;
    
public:
    ~Helper();
    static Helper * instance();
    
    void DumpHelp(string);
    void LoadHelp(string);
    void ParseQuery(string);
    void storeBase(vector<tuple<string,vector<string>>>&,vector<string>&,string);
    //void getBase(vector<tuple<string,vector<string>>>&,string);
    void dropBase(string);
    vector<vector<string>> op(string,string,vector<string>,vector<vector<string>>,vector<vector<string>>);
    vector<vector<string>> andOperator(string,vector<string>,vector<string>,vector<vector<string>>);
    vector<vector<string>> orOperator(string,vector<string>,vector<string>);
    vector<vector<string>> vectorCondense(vector<vector<vector<string>>>);
    vector<string> singleVecCondense(vector<vector<string>>);
    void parseCommand(string);
    void parseDefinition(char,string);
    vector<string> parseRule(string);
    string parseKey(string&);
    vector<vector<string>> retrieveFact(string,string&,string&);
    tuple<string,string,vector<string>,vector<vector<string>>> retrieveRule(vector<string>,string);
    vector<string> parseParams(string&);
    vector<tuple<int,int,int,int>> paramCorr(vector<vector<string>>);
    
};

#endif
 /* 
Helper_hpp 
*/
