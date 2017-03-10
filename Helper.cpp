#include "Helper.hpp"
#include "Transactional_Commands.hpp" // forward declaration


Helper* Helper:: h_instance = nullptr; // used to initialized pointer

Helper:: Helper()
{
    
    tCommands = new Transactional_Commands;
}

Helper:: ~Helper()
{
    
    delete tCommands;
    delete h_instance;
}

// ===================================================================================
// Instance
// ===================================================================================
// 	Used to access functionality of Helper class. Allows only one instance(object) to be
//  created
//
//  if theres not an object type Helper created
//	else return the object
//
// ===================================================================================
Helper* Helper:: instance()
{
    
    if(!h_instance) // same as if(h_instance == NULL)
        h_instance = new Helper; // create a new object
    return h_instance;
} // this allows only ONE object to be created of this class

// ===================================================================================
// Parse Command
// ===================================================================================
// 	Used to retrieve a Fact or Rule
//
//
//
//
//
// ===================================================================================
void Helper::parseCommand(string user_input)
{
    stringstream line(user_input);  //takes the contents of user_input and copies it to a string object
    string rule_check = ":"; //creates a string with : to see if a rule is being inputted.
    
    string command = ""; //creating an empty string to hold the parsed out command
    getline(line, command,' ');  //take the contects of the input before the space (the command) and assign it to the command string.
    
    size_t ch = user_input.find(" ");  // find the location of the space in our string
    ch++; //increment size_t to account for the extra sapce.
    string rest = user_input.substr (ch);
    
    cout << "----------------------------------------" << endl;
    cout << "Command: " << command << endl;
    
    tCommands->getMapCommand()[command](rest); //calls the proper function in transactional commands
}

// ===================================================================================
// Parse Definition
// ===================================================================================
//
//
//
//
//
//
// ==================================================================================

void Helper:: parseDefinition(char function, string def)
{
    //char acts as a tag for our function so that def can go through the proper conditional branch.
    // def represents the entire string without the command.  Example being Father(Roger, John)
    if (function=='f') //
    {
        string key = parseKey(def); // parse the key part of def.  Example being Father.
        vector<string> parameters = parseParams(def); // obtain the perameters of our string.  Example being (Roger, John).
        
        cout << "Key: " << key << endl;
        for(int i=0; i < parameters.size(); i++)
        {
            cout << "Parameter(" << i << "): " << parameters[i] << endl;
        }
        
        storeBase(tCommands->getFact(), parameters, key); // send the parameters and the key to be stored
        cout << "----------------------------------------" << endl << endl;
    }
    else if (function=='r') // if our tagged string is a rule
    {
        string key = parseKey(def); // parse the key part of def.  Example being Father.
        
        vector<string> keyParam = parseParams(def);
        
        vector<string> parameters = parseRuleParam(def); // obtain the perameters of our string.  Example being (Roger, John).
        
        cout << "Key: " << key << endl;
        for(int i=0; i < parameters.size(); i++)
        {
            cout << "Parameter(" << i << "): " << parameters[i] << endl;
        }
        
        storeBase(tCommands->getRule(), parameters, key, keyParam); // send the parameters and the key to be stored
        cout << "----------------------------------------" << endl << endl;
    }
}

// ===================================================================================
// Parse Query
// ===================================================================================
//
//
//
//
//
//
// ===================================================================================
void Helper:: ParseQuery(string rest)
{
    vector<vector<string>> tempFacts;
    string key;
    string empty_string = "";
    string temp = "";
    size_t ch = rest.find(")"); // find the location of the space in our string
    temp = rest;
    
    ch++;
    rest.erase(0, ch);
    vector<string> parameters;
    
    if (rest.compare(empty_string) == 0)
    {
        //call the inference part where we only need to print
        parameters = parseParams(temp);
        key = parseKey(temp);
        auto opParams = retrieveRule(parameters,key);
        vector<vector<string>> rule = get<3>(opParams);
        
        if (rule.size() == 0)
            tempFacts = retrieveFact(key, get<2>(opParams)[0], get<2>(opParams)[1]);
        else
        {
            vector<vector<string>> factData;
            tempFacts = vectorCondense(opFunction(get<0>(opParams), get<1>(opParams), get<2>(opParams), get<3>(opParams),factData));
        }
        
        cout << "Key: " << key << endl;
        for(int i=0; i < parameters.size(); i++)
        {
            cout << "Parameter(" << i << "): " << parameters[i] << endl;
        }
        
        if (tempFacts.size() != 0)
        {
            vector<string> fact = singleVecCondense(tempFacts);
            vector<string> result = dropDuplicates(fact);
            
            cout << endl;
            cout << "=================FACTS=================\n";
            for(int i=0; i < result.size(); i++){  //prints out final vector with no duplicates.
                cout << setw(13) << "[ " << result[i] << " ]" << endl;
            }
            cout << "=======================================\n";
            cout << "----------------------------------------" << endl << endl;
        }
        else
        {
            cout << "Whoops! Inference is not defined\n\n";
        }
    }
    else
    {
        //there is an extra part of the string for inference.
        key = parseKey(temp); //parses our full string saved in temp to get key2 as Grandmother.
        
        parameters = parseParams(temp);
        size_t space = rest.find(" ");
        space++;
        string inferKey = rest.substr (space); //Obtain the acronym (GF) as our key and save it for when we store the results in the fact vector.
        
        auto opParams = retrieveRule(parameters,key);
        vector<vector<string>> rule = get<3>(opParams);
        
        if (rule.size() == 0) // rule not defined
        {
            cout << "Not defined!\n";
            tempFacts = retrieveFact(key, get<2>(opParams)[0], get<2>(opParams)[1]);
        }
        else // rule defined
        {
            cout << "Defined!\n";
            vector<vector<string>> factData;
            tempFacts = vectorCondense(opFunction(get<0>(opParams), get<1>(opParams), get<2>(opParams), get<3>(opParams),factData));
        }
        
        cout << "Key: " << key << endl;
        
        for(int i=0; i < parameters.size(); i++)
        {
            cout << "Parameter(" << i << "): " << parameters[i] << endl;
        }
        
        cout << "Saved under: " << inferKey << endl;
        
        if (tempFacts.size() != 0)
        {
            vector<string> fact = singleVecCondense(tempFacts);
            storeBase(tCommands->getFact(), fact, inferKey);
            vector<string> result = dropDuplicates(fact);
            
            cout << endl;
            cout << "=================FACTS=================\n";
            for(int i=0; i < result.size(); i++){  //prints out final vector with no duplicates.
                cout << setw(13) << "[ " << result[i] << " ]" << endl;
            }
            cout << "=======================================\n";
            cout << "----------------------------------------" << endl << endl;
        }
        else
        {
            cout << "Whoops! Inference is not defined\n\n";
        }
    }
    
}

// ===================================================================================
// Parse Key
// ===================================================================================
// 	Used to parse rest of string passed from parseCommand and other functions.
//
//
//
//
//
// ===================================================================================
string Helper:: parseKey(string &input)
{
    string delimiter = "(";
    size_t pos = 0; // position of delimiter
    string key = ""; // holds the key or fact name
    
    pos = input.find(delimiter);
    key = input.substr(0, pos); // assings string from given input up to delimiter
    
    return key;
}

// ===================================================================================
// Parse Params
// ===================================================================================
//
//
//
//
//
//
// ==================================================================================
vector<string> Helper:: parseParams(string &input)
{
    string delimiter = "(";
    string delimiter2 = ",";
    size_t pos = 0; // position of delimiter
    
    vector<string> parameters; // holds each parameter
    
    pos = input.find(delimiter); // find the
    
    string temp = input.substr(0, pos);
    
    // Print key
    //    cout << "Key: " << input.substr(0, pos) << endl;
    pos++; // eats delimiter;
    
    string parsedInput = input.substr(pos, input.length());
    
    while ((pos = parsedInput.find(delimiter2)) != string::npos)  // will loop through as many parameters except the last one
    {
        parameters.push_back(parsedInput.substr(0, pos));
        //        cout << "Parameter(" << count++ << "): " << parameters[parameters.size()-1] << endl;
        pos++; // eats delimiter
        parsedInput = parsedInput.substr(pos, input.length());
        if (parsedInput[2] == ')')
            break;
    }
    // if loop breaks theres always going to be one parameter left to store
    delimiter = ")";
    pos = parsedInput.find(delimiter);
    parameters.push_back(parsedInput.substr(0, pos));
    //    cout << "Parameter(" << count << "): " << parameters[parameters.size()-1] << endl;
    //    cout <<"----------------------------------------"<<endl;
    
    return parameters;
}

// ===================================================================================
// Parse Rule
// ===================================================================================
//
//
//
//
//
//
// ==================================================================================
vector<string> Helper:: parseRuleParam(string input)
{
    vector<string> param;
    string delimiter = ":-";
    size_t pos = input.find(delimiter);
    //    cout << "----------------------------------------" << endl;
    //    cout << "Key: " << input.substr(0, pos) << endl;
    pos++; // eats up delimiter :
    pos++; // eats up delimiter -
    
    delimiter = " ";
    pos++; // eats up delimiter ' '(space)
    
    string parsedInput = input.substr(pos, input.length());
    
    while ((pos = parsedInput.find(delimiter)) != string::npos)  // will loop through as many parameters except the last one
    {
        param.push_back(parsedInput.substr(0, pos));
        //        cout << "Parameter(" << count++ << "): " << param[param.size()-1] << endl;
        pos++; // eats delimiter
        parsedInput = parsedInput.substr(pos, input.length());
    }
    
    delimiter = "\n";
    pos = parsedInput.find(delimiter);
    param.push_back(parsedInput.substr(0, pos));
    //    cout << "Parameter(" << count << "): " << param[param.size()-1] << endl;
    //    cout <<"----------------------------------------"<<endl;
    
    return param;
}

// ===================================================================================
// StoreBaseFact
// ===================================================================================
//
//
//
//
//
//
// ==================================================================================
void Helper:: storeBase(vector< tuple< string,vector<string> > > &base, vector<string> &params, string key)
{
    tuple<string,vector<string>> fact; // tuple that has a key(fact) and vector holding relationship
    get<0>(fact) = key;
    get<1>(fact) = params;
    base.push_back(fact);
}

// ===================================================================================
// StoreBaseRule
// ===================================================================================
//
//
//
//
//
//
// ==================================================================================
void Helper:: storeBase(vector<tuple<string,vector<string>,vector<string>>> &base, vector<string> &params, string key, vector<string> keyParam)
{
    tuple<string,vector<string>,vector<string>> rule; // tuple that has a key(fact) and vector holding relationship
    get<0>(rule) = key;
    get<1>(rule) = params;
    get<2>(rule) = keyParam;
    base.push_back(rule);
}

// ===================================================================================
// Retrieve Fact
// ===================================================================================
// 	Used to retrieve a Fact
//
//
//
//
//
// ===================================================================================
vector<vector<string>> Helper:: retrieveFact(string key, string &param1, string &param2)
{
    vector<string> params;
    vector<vector<string>> relationalData;
    //    cout << key << " Fact [ ";
    
    // & in [] of lambda functions allows lambda function to acess local variables
    for_each(tCommands->getFact().begin(), tCommands->getFact().end(),[&](decltype(*tCommands->getFact().begin()) it) -> void // iterates through vector
             {
                 if (get<0>(it) == key) // checks tuple if key matches
                 {
                     if (param1[0] == '$' && param2[0] == '$') // if query is generic
                     {
                         for(int i=0; i < get<1>(it).size(); i++) // iterates through vector inside tuple
                         {
                             if (i != get<1>(it).size()-1) // printing purpose: used to add commas
                             {
                                 params.push_back(get<1>(it)[i]);
                                 //                                 cout << get<1>(it)[i] << ","; // prints an index in vector
                             }
                             else
                             {
                                 params.push_back(get<1>(it)[i]);
                                 //                                 cout << get<1>(it)[i] << " | "; // prints an index in vector
                             }
                         }
                         relationalData.push_back(params);
                         params.clear();
                     }
                     else if (param1[0] != '$' && param2[0] == '$') // if the first parameter is specific
                     {
                         
                         for(int i=0; i < get<1>(it).size(); i++) // iterates through vector inside tuple
                         {
                             if (i != get<1>(it).size()-1) // printing purpose: used to add commas
                             {
                                 params.push_back(get<1>(it)[i]);
                                 //                                 cout << get<1>(it)[i] << ","; // prints an index in vector
                             }
                             else
                             {
                                 params.push_back(get<1>(it)[i]);
                                 //                                 cout << get<1>(it)[i] << " | "; // prints an index in vector
                             }
                         }
                         if(param1.compare(params[0]) == 0)
                             relationalData.push_back(params);
                         params.clear();
                     }
                     else if (param1[0] == '$' && param2[0] != '$') // if the second parameters is specific
                     {
                         for(int i=0; i < get<1>(it).size(); i++) // iterates through vector inside tuple
                         {
                             if (i != get<1>(it).size()-1) // printing purpose: used to add commas
                             {
                                 params.push_back(get<1>(it)[i]);
                                 //                                 cout << get<1>(it)[i] << ","; // prints an index in vector
                             }
                             else
                             {
                                 params.push_back(get<1>(it)[i]);
                                 //                                 cout << get<1>(it)[i] << " | "; // prints an index in vector
                             }
                         }
                         if(param2.compare(params[1]) == 0)
                             relationalData.push_back(params);
                         params.clear();
                     }
                 }
             });
    //    cout << " ]" << endl << endl;
    
    return relationalData;
}

// ===================================================================================
// Retrieve Rule
// ===================================================================================
// 	Used to retrieve a Rule
//
//
//
//
//
// ===================================================================================
tuple<string,string,vector<string>,vector<vector<string>>> Helper:: retrieveRule(vector<string> params, string key)
{
    // PARAMS is only passed to be passed to another function, Isn't used
    
    vector<vector<string>> rule;
    vector<string> ruleTemp;
    string logicalOp;
    
    //    cout << key << " Rule ";
    // & in [] of lambda functions allows lambda function to acess local variables
    for_each(tCommands->getRule().begin(), tCommands->getRule().end(),[&](decltype(*tCommands->getRule().begin()) it) -> void // iterates through vector
             {
                 
                 if (get<0>(it) == key)
                 {
                     for(int i=0; i < get<1>(it).size(); i++)
                     {
                         if (i==0)
                         {
                             //cout << get<1>(it)[i] << ", ";
                             logicalOp = get<1>(it)[i]; // holds the operator
                             
                         }
                         else if(i <= get<1>(it).size()-2)
                         {
                             decltype(get<1>(it)[i]) fact = get<1>(it)[i]; // variable holding a fact inside rule
                             // need to parse fact name from params
                             ruleTemp.push_back(fact);
                         }
                         else
                         {
                             decltype(get<1>(it)[i]) fact = get<1>(it)[i]; // variable holding a fact inside rule
                             // need to parse fact name from params
                             ruleTemp.push_back(fact);
                             
                             rule.push_back(ruleTemp);
                             ruleTemp.clear();
                         }
                     }
                 }
             });
    return make_tuple(logicalOp, key, params,rule);
}

// ===================================================================================
// DropDuplicates
// ===================================================================================
//
//
//
//
//
//
// ===================================================================================
vector<string> Helper:: dropDuplicates(vector<string> fact)
{
    //    cout << endl << "YOU ARE IN dropDuplicates FUNCTION!!!" << endl << endl;
    vector<string> result; //holds the final vector with no duplicates
    vector<string> final_fact; //used to concatinate strings
    
    for(int i=0; i<fact.size(); i++){
        //        cout << fact[i] << " ";
        //to makes this more general, define a variable that represents the amount of arguments per Fact and mod that
        if(i%2 !=0){ //using mod so that concatinate every 2 strings together
            fact[i-1].append(" "); //put the space between two strings
            fact[i-1].append(fact[i]); //append both names together
            //            cout << "pairs: " << fact[i-1] << endl; //print out the pairs so we know it is good
            final_fact.push_back(fact[i-1]);
        }
    }
    for (int j = 0; j < final_fact.size(); j++){
        bool check = true; //set defualt value of the duplicate check to true until we find a duplicate.
        for (int k = j+1; k < final_fact.size(); k++){
            //            cout << final_fact[j]  << " and " << final_fact [k] << endl; //print all comparisons to show them and see which ones match
            if ( final_fact[j].compare(final_fact[k]) == 0){
                //cout << "these should be equal: " << final_fact[j] << final_fact[k] << endl;
                //                cout << "DUPLICATE FOUND!!!" << endl;
                check = false; //set the boolean to false so that we know that there is a duplicate present.
            }
        }
        if (check){ //if the string is unique in our vector we push it into the final vector.
            result.push_back(final_fact[j]);
        }
    }
    //    for(int i=0; i < result.size(); i++){  //prints out final vector with no duplicates.
    //        cout << "No duplicates pair: " << result[i] << endl;
    //    }
    
    return result; //returns the vector that was just printed.
}


// ===================================================================================
// Condense a Triple Vector to a Double
// ===================================================================================
//
//
//
//
//
//
// ====================================================================================
vector<vector<string>> Helper:: vectorCondense(vector<vector<vector<string>>> v)
{
    vector<vector<string>> result;
    for(int i = 0; i < v.size(); i++)
    {
        for(int param = 0; param < v[i].size(); param++)
        {
            result.push_back(v[i][param]);
        }
    }
    
    return result;
}

// ===================================================================================
// Condense a Double Vector to a Single
// ===================================================================================
//
//
//
//
//
//
// ====================================================================================
vector<string> Helper:: singleVecCondense(vector<vector<string>> v)
{
    vector<string> result;
    for(int i = 0; i < v.size(); i++)
    {
        for(int param = 0; param < v[i].size(); param++)
        {
            result.push_back(v[i][param]);
        }
    }
    
    return result;
}

// ===================================================================================
// Parameter Correleation
// ===================================================================================
//
//
//
//
//
//
// ====================================================================================
vector<tuple<int,int,int,int>> Helper:: paramCorr(vector<vector<string>> paramData)
{
    vector<tuple<int,int,int,int>> paramCord; // coordinates start from the left then applied to the rule vector immediately to the right
    // i.e Father($X,$Z) Mother($Z,$Y) Foo($X,$Y)
    // the first 2 rule targets proccessed is Father lookin for correlations in Mother
    // then moves to Mother then looks for correlations in Foo
    
    // check parameters for correlation between rule targets
    for(int i=0; i < paramData.size()-1; i++) // controls the leftmost rule target  Mother($x,$z)<-leftmost Mother($z,$y)
        for(int param = 0; param < paramData[i].size(); param++) // iterates the leftmost rule target parameters
            for(int j=0; j < paramData[i+1].size(); j++) // iterates rule target paremeters to the right of leftmost
            {
                string a = paramData[i][param]; // used for testing
                string b = paramData[i+1][j]; // used for testing
                if (paramData[i][param].compare(paramData[i+1][j]) == 0) // checks to see if param match
                {
                    //                    paramCheck.push_back(true);
                    paramCord.push_back(make_tuple(i,param,i+1,j)); // records index of the leftmost rule target and its param and the compared rule target index and its param
                }
                //                else
                //                {
                //                    paramCord.push_back(make_tuple(-1,-1,-1,-1)); // -1 represents no correlation
                //                }
                
            }
    
    return paramCord;
}

// ===================================================================================
// AND Operator
// ===================================================================================
//
//
//
//
//
//
// ====================================================================================
vector<vector<string>> Helper:: andOperator(string key, vector<string> keyParams, vector<string> rule, vector<vector<string>> facts)
{
    vector<vector<string>> paramData; // holds parameters from each individual querey ie. Mother($x,$z) Mother($z,$y)
    vector<bool> paramCheck;
    vector<tuple<int,int,int,int>> paramIndex; // tuple<vectorIndex1,param,vectorIndex2,param>
    vector<vector<string>> inferData; // holds the data to be returned
    vector<vector<string>> factData;
    bool recursion = false;
    
    for(int i=0; i < rule.size(); i++)
        paramData.push_back(parseParams(rule[i]));
    
    // finds correlation in rule targets
    paramIndex = paramCorr(paramData);
    if (paramIndex.size() == keyParams.size())
        return factData; //  params should correlated else its not an AND Inference //ASSUMED
    
    bool isGeneric = true;
    // check to see if params are specific or not
    for(int i=0; i<keyParams.size(); i++)
    {
        if (keyParams[i][0] != '$')
        {
            isGeneric = false;
            break;
        }
    }
    
    auto tempTuple = retrieveRule(keyParams, parseKey(rule[0]));
    
    // get facts of first defined rule target
    if (facts.size()== 0)
    {
        // get<3> holds defined rule
        auto tempRule = get<3>(tempTuple);
        
        // check if rule target has a defined rule
        if(tempRule.size() == 0) // theres no defined rule
        {
            factData = retrieveFact(parseKey(rule[0]),keyParams[0],keyParams[1]);
        }
        else
        {
            factData = vectorCondense(opFunction(get<0>(tempTuple), get<1>(tempTuple), keyParams, tempRule, facts));
        }
    }
    else
    {
        vector<vector<vector<string>>> tempRelData; // used to hold data from each factData defined in facts
        
        if (isGeneric) // params are generic Father($x,$y) // code being tested wont hit here jsut yet
        {
            // get<3> holds defined rule
            auto tempRule = get<3>(tempTuple);
            
            // check if rule target has a defined rule
            if(tempRule.size() == 0) // theres no defined rule
            {
                factData = retrieveFact(parseKey(rule[0]),keyParams[0],keyParams[1]);
            }
            else
            {
                factData = vectorCondense(opFunction(get<0>(tempTuple), get<1>(tempTuple), keyParams, tempRule, facts));
            }
        }
        else // params are specific Father(John,$y)
        {
            // get<3> holds defined rule
            auto tempRule = get<3>(tempTuple);
            
            // check if rule target has a defined rule
            if(tempRule.size() == 0) // theres no defined rule
            {
                for (int i=0; i<facts.size(); i++)
                {
                    if(keyParams[0][0] != '$') // left param is specific
                        tempRelData.push_back(retrieveFact(parseKey(rule[0]), facts[i][0], paramData[1][1]));
                    else // right param is specific
                        tempRelData.push_back(retrieveFact(parseKey(rule[0]),paramData[1][1],facts[i][1]));
                }
                factData = vectorCondense(tempRelData);
            }
            else // code being tested wont hit her just yet
            {
                factData = vectorCondense(opFunction(get<0>(tempTuple), get<1>(tempTuple), keyParams, tempRule, facts));
                recursion = true;
            }
        }
        
    }
    
    //this variable pulls the facts for the first rule target only; the preceding rule target may used the first rule target which will be handeled later
    
    
    // looks at 2nd rule target and on
    
    // this holds the corelation fact data from the rule target based on parameters
    vector<vector<vector<string>>> relationalData;
    vector<vector<string>> match;
    
    // retrive facts based based on if theres correlations or not between rule targets
    // ONLY WORKS for 2 params
    for (int i=0; i<factData.size(); i++)
    {
        
        tempTuple = retrieveRule(keyParams, parseKey(rule[1]));
        auto tempRule = get<3>(tempTuple);
        string generic = "$";
        
        if( tempRule.size() == 0) // if rule is not defined
        {
            // there should only be one vector contained so use index 0 to pull index to vector that has data
            // this pulls the data based on the correlation between rule targetfrom fact from each individual query in rule ie. Grandmother():- Mother() Mother()
            
            // need paramCorr to be able to be generic as far as one parmeter may not have a correlation but another does. The code isnt setup to handle that
            // may have solved this issue; needs testing
            
            // paramIndex<vectorIndex,param,vector2Index,param2>
            if(get<0>(paramIndex[0]) != -1) // when code is able to take more than one parameter than the index will change from 0 to i
            {
                // means theres a specific param to be passed
                // potential issues
                // what if both params match
                // determining which param is to suppose to go where
                
                
                // would need a different iterator for paramIndex because factData is the first param so if the second param his correlated paramIndex needs to be the same index until  all fact data has been processed
                
                if(get<1>(paramIndex[0]) == 0) // means the first param in the first vector is being used for second vector
                {
                    if(get<3>(paramIndex[0]) == 0) // place first param in the (first parm of second vector)
                        relationalData.push_back(retrieveFact(parseKey(rule[1]), factData[i][get<1>(paramIndex[0])], generic));
                    else // place first param in the (second parm of second vector)
                        relationalData.push_back(retrieveFact(parseKey(rule[1]),generic,factData[i][get<1>(paramIndex[0])]));
                }
                else if (get<1>(paramIndex[0]) == 1) // means the second param in the first vector is being used for second vector
                {
                    if(get<3>(paramIndex[0]) == 0) // place second param in the (first parm of second vector)
                        relationalData.push_back(retrieveFact(parseKey(rule[1]), factData[i][get<1>(paramIndex[0])], generic));
                    else // place second param in the (second parm of second vector)
                        relationalData.push_back(retrieveFact(parseKey(rule[1]),generic,factData[i][get<1>(paramIndex[0])]));
                }
                
                // need else cases for  different locations of param
                // code would need to be more generic b/c we cant make conditional for an infinite amount
            }
            else if (get<0>(paramIndex[0]) == -1) // means theres no correlation
            {
                // paramData doesnt matter which one u use, its just passing a generic variable
                relationalData.push_back(retrieveFact(parseKey(rule[1]),generic, generic));
            }
        }
        else // if rule is defined
        {
            recursion = true;
            //            op(string logicalOp, string key, vector<string> keyParams, vector<vector<string> > rule, vector<vector<string> > fact)
            
            if(get<0>(paramIndex[0]) != -1)
            {
                if(get<3>(paramIndex[0]) == 0) // place first param in the (first parm of second vector)
                {
                    keyParams[0] = "X";
                    
                    relationalData = opFunction(get<0>(tempTuple), get<1>(tempTuple), keyParams, tempRule, factData);
                }
                else // place first param in the (second parm of second vector)
                {
                    keyParams[1] = "X";
                    relationalData = opFunction(get<0>(tempTuple), get<1>(tempTuple), keyParams, tempRule, factData);
                }
            }
            else
                relationalData = opFunction(get<0>(tempTuple), get<1>(tempTuple), get<2>(tempTuple), tempRule, factData);
            
            break;
        }
    }
    
    // this is where the logical operator logic happens
    for(int i=0; i < relationalData.size(); i++) // iterates through data that has been returned from correlations of rule target
    { // used to iterate through relationalData and factData; there size is ALWAYS going to be equal
        vector<string> matchTemp; // temporary holds matches of current iterated vector
        vector<string>inferDataTemp; // temporary holds inference data of current iterated vector
        
        if (!recursion)
        {
            if(relationalData[i].size() != 0) // if empty break
            {
                // loop through vectors one by one finding if theres a match if theres not then that means thats the data we want
                for(int k = 0; k < relationalData[i].size(); k++)  // iterates through vectors inside of relationalData (vector<vector<string>)
                {
                    for(int j=0; j < relationalData[i][k].size(); j++) // iterates through vector's data inside of relationalData vector (string)
                    { // factData is the only variable using j index
                        // using the paremeter Index matcher to only save the data that didnt match in the paremeters
                        if(j != get<1>(paramIndex[0]))
                        {
                            inferDataTemp.push_back(factData[i][j]);
                        }
                        
                        if(j != get<3>(paramIndex[0]))
                        {
                            inferDataTemp.push_back(relationalData[i][k][j]);
                        }
                    }// end for
                    inferData.push_back(inferDataTemp);
                    inferDataTemp.clear();
                }// end for
            }// end if
        }
        else
        {
            if(relationalData[i].size() != 0) // if empty break
            {
                for(int j=0; j < factData.size(); j++) // factData is the last to be iterated because it contains on the facts that relationalData got its data from
                {
                    for(int k=0; k < relationalData[i].size(); k++)
                    {
                        if(keyParams[0][0] != '$')
                        {
                            // assuming on 2 parameters per rule target
                            if(factData[j][1].compare(relationalData[i][k][0]) == 0) // if the second param of first vector == first param of second vector
                            {
                                inferDataTemp.push_back(factData[j][0]);
                                inferDataTemp.push_back(relationalData[i][k][1]);
                            }
                        }
                    }// end for
                    if(inferDataTemp.size() != 0)
                    {
                        inferData.push_back(inferDataTemp);
                        inferDataTemp.clear();
                    }
                }
                
            }// end if
        }
    }// end for
    
    return inferData;
}

// ===================================================================================
// OP
// ===================================================================================
//
//
//
//
//
//
// ===================================================================================
vector<vector<vector<string>>> Helper:: opFunction(string logicalOp, string key,vector<string> keyParams,vector<vector<string>> rule,vector<vector<string>> fact)
{
    vector<vector<vector<string>>> data;
    for(int i=0; i < rule.size(); i++)
    {
        if(logicalOp=="AND")
            data.push_back(andOperator(key, keyParams, rule[i], fact));
        else if (logicalOp=="OR")
            data.push_back(orOperator(key, keyParams, rule[i], fact));
    }
    return data;
}

// ===================================================================================
// OR Base
// ===================================================================================
//
//
//
//
//
//
// ===================================================================================
vector<vector<string>> Helper:: orOperator(string key, vector<string> keyParams, vector<string> rule, vector<vector<string>> facts)
{
    vector<vector<string>> paramData; // holds parameters from each individual querey ie. Mother($x,$z) Mother($z,$y)
    vector<bool> paramCheck;
    vector<tuple<int,int,int,int>> paramIndex; // tuple<vectorIndex1,param,vectorIndex2,param>
    vector<vector<string>> inferData; // holds the data to be returned
    vector<vector<string>> factData;
    bool paramLeft = false;
    bool paramRight = false;
    
    for(int i=0; i < rule.size(); i++)
        paramData.push_back(parseParams(rule[i]));
    
    // finds correlations in rule target
    paramIndex = paramCorr(paramData);
    if (paramIndex.size() == keyParams.size()) // if every param matches then theres no correlation
        paramIndex.clear();
    else
    {
        if(keyParams[0] == paramData[0][0] && keyParams[1] ==  paramData[0][1])
            paramLeft = true;
        else if(keyParams[0] == paramData[1][0] && keyParams[1] ==  paramData[1][1])
            paramRight = true;
        else
        return factData; // all params should match else its not and OR Inference //ASSUMED
    }
    
    
    // this part of code doesnt do what I thought
    // keyParams needs to hold where params go on a recursion call, currently it doesnt
    bool isGeneric = true;
    // check to see if params are specific or not
    for(int i=0; i<keyParams.size(); i++)
    {
        if (keyParams[i][0] != '$')
        {
            isGeneric = false;
            break;
        }
    }
    
    vector<vector<vector<string>>> tempRelData; // used to hold data from each fact temporarily
    
    // get facts of first defined rule target
    
    auto tempTuple = retrieveRule(keyParams, parseKey(rule[0]));
    if (facts.size()== 0)
    {
        // get<3> holds defined rule
        auto tempRule = get<3>(tempTuple);
        
        // check if rule target has a defined rule
        if(tempRule.size() == 0) // theres no defined rule
        {
            // may need generic or non generic code here
            // wont need it for the test im working on now
            
            if(paramRight == false || paramLeft == true)
            factData = retrieveFact(parseKey(rule[0]),keyParams[0],keyParams[1]);
            else if(paramLeft)
             factData = retrieveFact(parseKey(rule[0]),keyParams[0],keyParams[1]);
        }
        else
        {
            factData = vectorCondense(opFunction(get<0>(tempTuple), get<1>(tempTuple), keyParams, tempRule, facts));
        }
    }
    else  // there may not be generic parameters if facts has a size greater than 0
    {
        // get<3> holds defined rule
        auto tempRule = get<3>(tempTuple);
        
        // check if rule target has a defined rule
        if(tempRule.size() == 0) // theres no defined rule
        {
            if(!isGeneric)
            {
                for (int i=0; i<facts.size(); i++)
                {
                    // under the assumption if recursion happens the second param in facts is always the value that we are looking to inference with specificly
                    // Mother($X,[$Z]) Parent([$Z],$Y) the $Z comes from the second param of the first rule target that is used in the second rule target's first param
                    tempRelData.push_back(retrieveFact(parseKey(rule[0]), facts[i][1], paramData[1][1]));
                    
                }
                
                // condense vector to fit factData and also rids and empty vector
                for(int i=0; i < tempRelData.size(); i++)
                    for(int j=0; j < tempRelData[i].size(); j++)
                    {
                        factData.push_back(tempRelData[i][j]);
                    }
            }
            else
            {
                factData = retrieveFact(parseKey(rule[0]), keyParams[0], keyParams[1]);
            }
        }
        else // code being tested wont hit her just yet
        {
            factData = vectorCondense(opFunction(get<0>(tempTuple), get<1>(tempTuple), keyParams, tempRule, facts));
        }
    }
    
    tempRelData.clear();
    
    // looks at 2nd rule target and on
    
    // this holds the corelation fact data from the rule target based on parameters
    vector<vector<string>> relationalData;
    
    // retrive facts based based on if theres correlations or not between rule targets
    
    // only works for 2 params
    if (facts.size() == 0)
    {
        tempTuple = retrieveRule(keyParams, parseKey(rule[1]));
        auto tempRule = get<3>(tempTuple);
        string generic = "$";
        
        if( tempRule.size() == 0) // if rule is not defined
        {
            relationalData = retrieveFact(parseKey(rule[1]), keyParams[0], keyParams[1]);
        }
        else // if rule is defined
        {
            //            op(string logicalOp, string key, vector<string> keyParams, vector<vector<string> > rule, vector<vector<string> > fact)
            tempRelData = opFunction(get<0>(tempTuple), get<1>(tempTuple), keyParams, tempRule, factData);
        }
    }
    else
    {
        for (int i=0; i<facts.size(); i++)
        {
            if(!isGeneric)
                tempRelData.push_back(retrieveFact(parseKey(rule[1]), facts[i][1], paramData[1][1]));
            else
                relationalData = retrieveFact(parseKey(rule[1]), keyParams[0], keyParams[1]);
        }
    }
    
    //     condense vector to fit factData and also rids and empty vector
    for(int i=0; i < tempRelData.size(); i++)
        for(int j=0; j < tempRelData[i].size(); j++)
        {
            relationalData.push_back(tempRelData[i][j]);
        }
    
    // merge data
    for(int i=0; i<factData.size(); i++)
        inferData.push_back(factData[i]);
    
    for(int i=0; i<relationalData.size(); i++)
        inferData.push_back(relationalData[i]);
    
    return inferData;
}

// ===================================================================================
// DumpHelp
// ===================================================================================
// 	Called from within the dump function of Transactional Commands.  Trying to handle
//  the dumping from within Transactional commands was not working; there would be an
//  error given you would try to call the fact vector from within dump function.  You cannot
//  a nonstatic vector from within the static dump funcion.  Making the fact vector static
//  and the getFact() function static would lead to having to create an object that would call
//  getFact() function.  Running this code would produce no errors until link time, in which
//  there would be a link error I would not entirely understand.  However, This fucntion
//  writes the contents of the fact vector to a file.  The format looks wrong on the file
//  preview, but is correct when you open the file all the way.
// ==================================================================================

//Only works for facts as of now
//Tip:  create a conditional that checks to see if the fact and rule vectors are empty.  If the vector is not empty output to a file, else do nothing.
void Helper:: DumpHelp(string path)
{
    
    const char* f = path.c_str();
    fstream file;
    file.exceptions ( fstream::failbit | fstream::badbit );
    vector<tuple<string,vector<string>>> Factbase = tCommands->getFact();
    vector<tuple<string,vector<string>,vector<string>>> Rulebase = tCommands->getRule();
    try
    {
        // open/create file
        file.open (f, ios::out);
        cout <<"Saving in to the file: " << f << endl;
        if(Factbase.size() != 0){
            for_each(Factbase.begin(), Factbase.end(),[&](decltype(*Factbase.begin()) it) -> void // iterates through vector
                     {
                         string temp = "FACT ";
                         temp.append(get<0>(it));
                         temp.append("(");
                         for(int i=0; i < get<1>(it).size(); i++)
                         {
                             if (i != get<1>(it).size()-1){
                                 temp.append(get<1>(it)[i]);
                                 temp.append(",");
                             }
                             else
                             {
                                 temp.append(get<1>(it)[i]);
                                 temp.append(")");
                             }
                         }
                         file << temp <<endl;
                     });
        }
        else
        {
            cout << "there are no facts to dump." << endl;
        }
        if(Rulebase.size() != 0)
        {
            string logicalOperater;
            for_each(Rulebase.begin(), Rulebase.end(),[&](decltype(*Rulebase.begin()) it) -> void
                     {
                         string temp = "RULE ";
                         temp.append(get<0>(it));
                         //cout << temp << endl; //this prints out the when the user dumps
                         temp.append("($");
                         temp.append(get<2>(it)[0]);
                         temp.append(",$");
                         temp.append(get<2>(it)[1]);
                         temp.append("):- ");
                         //cout << temp << endl;
                         for(int i=0; i < get<1>(it).size(); i++)
                         {
                             if (i==0)
                             {
                                 logicalOperater = get<1>(it)[i]; // holds the operator
                                 temp.append(logicalOperater + " ");
                             }
                             else if (i <= get<1>(it).size()-1)
                             {
                                 temp.append(get<1>(it)[i] + " ");
                             }
                         }
                         
                         
                         file << temp << endl;
                     });
        }
        
        
        // open/create file
        // close file
        file.close();
    }
    catch (ifstream::failure e)
    {
        cerr << "Failed to dump file\n";
    }
    cout <<"File has been saved"<<endl;
    cout << endl;
}

// ===================================================================================
// Load Help
// ===================================================================================
//
//
//
//
//
//
// ===================================================================================
void Helper:: LoadHelp(string path)
{
    const char* f = path.c_str();
    fstream file;
    // line
    string l;
    string fact_string = "FACT";
    string rule_string = "RULE";
    string inference_string = "INFERENCE";
    string drop_string = "DROP";
    string dump_string = "DUMP";
    file.exceptions ( fstream::badbit );
    
    try
    {
        // open file
        file.open (f, ios::in);
        
        while ( getline(file, l) )
        {
            //this process is the same as ParseCommand; Later we will use the method instead.
            string delimeter = " ";
            size_t pos = 0;
            string command = "";
            pos = l.find(delimeter);
            command = l.substr(0, pos);
            l.erase(0, pos + delimeter.length());
            
            if(command.compare(fact_string) == 0)
            {
                //Our string is in the example format: FACT Father(Rodger,John).
                //So we need to get the relation (Father) part of the string and set it to our key variable.
                string delimiter = "("; //Define space right after the relation (Father) ends.
                size_t pos2 = l.find("("); // Set the value of the
                string key = ""; // holds the key or fact name
                pos2 = l.find(delimiter); //set pos2 to the index where the ( is located in the string.
                key = parseKey(l); // saves the relaton part of the string as key, so it can be passed to storeBase later.
                
                vector<string> parameters;
                parameters = parseParams(l);
                storeBase(tCommands->getFact(), parameters, key);
            }
            else if (command.compare(rule_string) == 0)
            {
                string delimiter = "("; //Define space right after the relation (Father) ends.
                size_t pos2 = l.find("("); // Set the value of the
                string key = ""; // holds the key or fact name
                pos2 = l.find(delimiter); //set pos2 to the index where the ( is located in the string.
                key = parseKey(l); // saves the relaton part of the string as key, so it can be passed to storeBase later.
                vector<string> keyParam = parseParams(l);
                vector<string> params = parseRuleParam(l);
                
                storeBase(tCommands->getRule(), params, key, keyParam);
            }
            else if (command.compare(inference_string) == 0)
            {
                //do the stuff for taking an inference out of a file.
                size_t ch = l.find(" ");
                ch++;
                string rest = l.substr (ch);
                tCommands->getMapCommand()[command](rest);
            }
            else if (command.compare(drop_string) == 0)
            {
                //do the stuff for taking a drop out of the file.
                size_t ch = l.find(" ");
                ch++;
                string rest = l.substr (ch);
                tCommands->getMapCommand()[command](rest);
            }
            else if (command.compare(dump_string) == 0)
            {
                //do the stuff for taking a dump out of a file.
                size_t ch = l.find(" ");
                ch++;
                string rest = l.substr (ch);
                tCommands->getMapCommand()[command](rest);
            }
        }
        // close file
        file.close();
    }
    catch ( fstream::failure e )
    {
        cerr << "Failed to load file\n";
    }
    
    cout << endl << setw(20) << "File Loaded\n";
    cout << "----------------------------------------" << endl << endl;
    
}

// ===================================================================================
// Drop Base
// ===================================================================================
//
//
//
//
//
//
// ===================================================================================
void Helper:: dropBase(string command)
{
    int count = 0; // iterates through the for loops
    cout << "Dropping: "<< command<<endl<<endl;
    vector<int> factIndex;
    
    for(vector<tuple<string,vector<string>>>::iterator i = tCommands->getFact().begin(); i != tCommands->getFact().end(); i++) // iterates through vector
    {
        if ( command.compare(get<0>(*i)) == 0 )
        {
            factIndex.push_back(count);
        }
        count++;
    }
    
    for (int i = factIndex.size() - 1; i >= 0; --i)
    {
        count = factIndex[i];
        tCommands->getFact().erase(tCommands->getFact().begin() + count);
    }
    
    vector<int> ruleIndex;
    count = 0;
    for(vector<tuple<string,vector<string>,vector<string>>>::iterator i = tCommands->getRule().begin(); i != tCommands->getRule().end(); i++) // iterates through vector
    {
        if ( command.compare(get<0>(*i)) == 0 )
        {
            ruleIndex.push_back(count);
        }
        count++;
    }
    
    for(int i = ruleIndex.size()-1; i>=0; --i)
    {
        count = ruleIndex[i];
        tCommands->getRule().erase(tCommands->getRule().begin() + count);
    }
    
}

