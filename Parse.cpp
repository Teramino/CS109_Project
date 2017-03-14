//
//  Parse.cpp
//  CS109_SRI_CommandLine
//
//  Created by Kory Brown on 3/13/17.
//  Copyright © 2017 Kory Brown. All rights reserved.
//
#include "Parse.hpp"


//void Parse:: ParseQuery(string rest)
//{
//    vector<vector<string>> tempFacts;
//    string key;
//    //Helper::instance()->retrieveRule(<#vector<string>#>, <#string#>)
//    string empty_string = "";
//    string temp = "";
//    // find the location of the space in our string
//    size_t ch = rest.find(")");
//    temp = rest;
//    
//    ch++;
//    rest.erase(0, ch);
//    vector<string> parameters;
//    
//    if (rest.compare(empty_string) == 0)
//    {
//        //call the inference part where we only need to print
//        parameters = parseParams(temp);
//        key = parseKey(temp);
//        auto opParams = retrieveRule(parameters,key);
//        vector<vector<string>> rule = get<3>(opParams);
//        
//        cout << "Key: " << key << endl;
//        for(int i=0; i < parameters.size(); i++)
//        {
//            cout << "Parameter(" << i << "): " << parameters[i] << endl;
//        }
//        
//        if (rule.size() == 0)
//            tempFacts = retrieveFact(key, get<2>(opParams)[0], get<2>(opParams)[1]);
//        else
//        {
//            vector<vector<string>> factData;
//            tempFacts = vectorCondense(opFunction(get<0>(opParams), get<1>(opParams), get<2>(opParams), get<3>(opParams),factData));
//        }
//        
//        
//        if (tempFacts.size() != 0)
//        {
//            vector<string> fact = singleVecCondense(tempFacts);
//            vector<string> result = dropDuplicates(fact);
//            
//            cout << endl;
//            cout << "=================FACTS=================\n";
//            for(int i=0; i < result.size(); i++){  //prints out final vector with no duplicates.
//                cout << setw(13) << "[ " << result[i] << " ]" << endl;
//            }
//            cout << "=======================================\n";
//            cout << "----------------------------------------" << endl << endl;
//        }
//        else
//        {
//            cout << "Whoops! Inference is not defined\n\n";
//        }
//    }
//    else
//    {
//        cout << "else\n";
//        //there is an extra part of the string for inference.
//        key = parseKey(temp); //parses our full string saved in temp to get key2 as Grandmother.
//        
//        parameters = parseParams(temp);
//        size_t space = rest.find(" ");
//        space++;
//        string inferKey = rest.substr (space); //Obtain the acronym (GF) as our key and save it for when we store the results in the fact vector.
//        
//        auto opParams = retrieveRule(parameters,key);
//        vector<vector<string>> rule = get<3>(opParams);
//        
//        cout << "Key: " << key << endl;
//        
//        for(int i=0; i < parameters.size(); i++)
//        {
//            cout << "Parameter(" << i << "): " << parameters[i] << endl;
//        }
//        
//        cout << "Saved under: " << inferKey << endl;
//        
//        
//        if (rule.size() == 0) // rule not defined
//        {
//            cout << "Not defined!\n";
//            tempFacts = retrieveFact(key, get<2>(opParams)[0], get<2>(opParams)[1]);
//        }
//        else // rule defined
//        {
//            cout << "Defined!\n";
//            vector<vector<string>> factData;
//            tempFacts = vectorCondense(opFunction(get<0>(opParams), get<1>(opParams), get<2>(opParams), get<3>(opParams),factData));
//        }
//        
//        if (tempFacts.size() != 0)
//        {
//            vector<string> fact = singleVecCondense(tempFacts);
//            storeBase(tCommands->getFact(), fact, inferKey);
//            vector<string> result = dropDuplicates(fact);
//            
//            cout << endl;
//            cout << "=================FACTS=================\n";
//            for(int i=0; i < result.size(); i++){  //prints out final vector with no duplicates.
//                cout << setw(13) << "[ " << result[i] << " ]" << endl;
//            }
//            cout << "=======================================\n";
//            cout << "----------------------------------------" << endl << endl;
//        }
//        else
//        {
//            cout << "Whoops! Inference is not defined\n\n";
//        }
//    }
//}
//
//void Parse::parseCommand(string user_input)
//{
//    // takes the contents of user_input and copies it to a string object
//    stringstream line(user_input);
//    // creates a string with : to see if a rule is being inputted
//    string rule_check = ":";
//    // creating an empty string to hold the parsed out command
//    string command = "";
//    // take the contects of the input before the space (the command) and assign it to the command string
//    getline(line, command,' ');
//    // find the location of the space in our string
//    size_t ch = user_input.find(" ");
//    // increment size_t to account for the extra sapce
//    ch++;
//    string rest = user_input.substr(ch);
//    // print to the interface the command
//    cout << "----------------------------------------" << endl;
//    cout << "Command: " << command << endl;
//    // calls the proper function in transactional commands
//    tCommands->getMapCommand()[command](rest);
//}
//
//void Parse:: parseDefinition(char function, string def)
//{
//    // char acts as a tag for our function so that def can go through the proper conditional branch
//    // def represents the entire string without the command, example being Father(Roger, John)
//    if (function=='f')
//    {
//        // parse the key part of def, example being Father
//        string key = parseKey(def);
//        // obtain the perameters of our string, example being (Roger, John)
//        vector<string> parameters = parseParams(def);
//        // print information to the interface
//        cout << "Key: " << key << endl;
//        for(int i=0; i < parameters.size(); i++)
//        {
//            cout << "Parameter(" << i << "): " << parameters[i] << endl;
//        }
//        // send the parameters and the key to be stored
//        storeBase(tCommands->getFact(),parameters,key);
//        cout << "----------------------------------------" << endl << endl;
//    }
//    // if our tagged string is a rule
//    else if (function=='r')
//    {
//        // parse the key part of def, example being Father
//        string key = parseKey(def);
//        vector<string> keyParam = parseParams(def);
//        // obtain the perameters of our string, example being (Roger, John)
//        vector<string> parameters = parseRuleParam(def);
//        // print information to the interface
//        cout << "Key: " << key << endl;
//        for(int i=0; i < parameters.size(); i++)
//        {
//            cout << "Parameter(" << i << "): " << parameters[i] << endl;
//        }
//        // send the parameters and the key to be stored
//        storeBase(tCommands->getRule(), parameters, key, keyParam);
//        cout << "----------------------------------------" << endl << endl;
//    }
//}
//
