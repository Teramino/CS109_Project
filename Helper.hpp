//Helper.hpp

#ifndef Helper_hpp
#define Helper_hpp

#include "Common.hpp"
#include "Rule.hpp"
#include "Fact.hpp"
#include "Threading.hpp"

class Transactional_Commands; // forward declaration

// Singleton Class
class Helper
{
    
    typedef vector<vector<string>> (Helper::*func)(string,string&,string&);
private:
    Helper(); // constructor is private to no instances of class can be created (Singleton)
    
    Transactional_Commands* tCommands;
    static Helper * h_instance;
    
    // for threading
   // int threadCount = 0;
    int threadID = 0;
    //vector<future<vector<vector<string>>>> futures;
   // vector<tuple<int,future<vector<vector<string>>>>> futures;
    string result_string; // result for server
    vector<Threading*> threadvec;
    
public:
    ~Helper();
    static Helper * instance();
    //int threadCount;
    
    string getString(); // returns string to interface to be sent to server/client socket
    void DumpHelp(string);
    void LoadHelp(string);
    void ParseQuery(string);
    void dropBase(string);
    vector<vector<vector<string>>> opFunction(string,string,vector<string>,vector<vector<string>>,vector<vector<string>>);
    vector<vector<string>> andOperator(string,vector<string>,vector<string>,vector<vector<string>>);
    vector<vector<string>> orOperator(string,vector<string>,vector<string>, vector<vector<string>>);
    vector<vector<string>> vectorCondense(vector<vector<vector<string>>>);
    vector<string> singleVecCondense(vector<vector<string>>);
    void parseCommand(string);
    void parseDeligate(char,string);
    vector<vector<string>> retrieveFact(string,string&,string&);
    tuple<string,string,vector<string>,vector<vector<string>>> retrieveRule(vector<string>,string);
    vector<tuple<int,int,int,int>> paramCorr(vector<vector<string>>);
    vector<vector<string>> dropDuplicates(vector<string>);
    
};

#endif
 /* 
Helper_hpp 
*/
