//Interface.cpp

#include "Interface.hpp"

bool Valid_FACT_Input(string fact_defenition, bool& user_mess_up)//Checks to see if the fact has the opening and closing parentheses, that's
//the ONLY check it does, for the synthax  of the fact, not the content
{
	stack <char> syntax_check; //pushes the open parentheses and closed parentheses onto the stack, cause there should be only two
	//one pair of parantheses in a fact

	int i = 0;

	while (fact_defenition[i] != '(')//Check before the parentheses that the relationship name is only captial or lowercase letters,
		//no whitespaces or symbols
	{
		if (isalpha(fact_defenition[i]) == 0)
		{
			cout << "Your input for -> " + fact_defenition + " is incorrect" << endl;
			cout << "The relationship name must be only alphabets, no spaces or symbols, followed by a open parantheses" << endl;
			cout << "Example: 'Father('" << endl << endl;
			user_mess_up = true;
			return false;
		}
		++i;
	}

	for (char& c : fact_defenition)//loop through the string char by char, and only push when encoutering a parentheses
	{
		if (c == '(' || c == ')')
		{
			syntax_check.push(c);
		}
	}


	if (syntax_check.size() == 2 && syntax_check.top() == ')') //if the stack size is two, indiciating there are two parantheses,
		//and the last thing to be pushed is the closing parentheses, that indicates the strings format was in the proper sythax
	{
		return true;
	}
	else
	{
		cout << "Your syntax -> "+ fact_defenition+ " is incorrect" << endl;
		cout << "Proper syntax: FACT [key](how many parameters you want seperated by commas)" << endl;
		cout << "Example: FACT Father(Roger,John,You)" << endl << endl;
		user_mess_up = true;
		return false;
	}
}

bool Valid_RULE_Input(string rule_defenition, bool& user_mess_up)//Makes sure the RULE sythax is correct
{
	stack<char> Rule_syntax; //Gonna be pushing '(' and '$', and they only get popped when there is a closed parentheses or the
	//proper rules for '$' were followed

	bool is_token_and_proper_operator_there = false;//look to see if the token is there, and the correct operator is there after the token

	size_t looking_for_specific_char; //looks to see if the ":-" followed by the AND or OR logical operator is there

	int check_if_next_char_valid = 0; //keeps track of the '$' symbol, and if the next char after that token are valid
	int content_in_array = 0;//checks to see how many char are actually in the array

	for (char& c : rule_defenition)//counts how many char are in the array, until it hits the null char or new line char
	{
		++content_in_array;
	}

	int i = 0;

	while (rule_defenition[i] != '(')//Check before the parentheses that the relationship name is only captial or lowercase letters,
		//no whitespaces or symbols
	{
		if (isalpha(rule_defenition[i]) == 0)
		{
			cout << "Your input for -> " + rule_defenition + " is incorrect" << endl;
			cout << "The relationship name must be only alphabets, no spaces or symbols, followed by a open parentheses" << endl;
			cout << "Example: 'Father('" << endl << endl;
			user_mess_up = true;
			return false;
		}
		++i;
	}

	for (int j = 0; j < content_in_array; ++j)//goes through the array and pushes and pops the '(' and '$' char if certain criterias
		//are meet
	{
		if (rule_defenition[j] == '(') Rule_syntax.push(rule_defenition[j]);//if open parantheses, push it onto the stack 
		if (rule_defenition[j] == '$')
		{
			Rule_syntax.push(rule_defenition[j]);//if it's a dollar sign, push it onto the stack
			if (isupper(rule_defenition[j + 1]) != 0 && isalpha(rule_defenition[j + 1]) != 0)//if the next char after '$' is one
				//alphabet and it is uppercase, it is a valid char to have after '$'
			{
				++check_if_next_char_valid;
			}
			else
			{
				cout << "Your syntax for -> " + rule_defenition + " is incorrect" << endl;
				cout << "All RULE parameters must  ONE uppercase character, and also have a $ symbol" << endl;
				cout << "Example: Parent($X,$Y)" << endl;
				user_mess_up = true;
				return false;
			}
		}

		if (check_if_next_char_valid != 0 && (rule_defenition[j + 2] == ',' || rule_defenition[j + 2] == ')'))
			//if the char after '$' is valid, and the next NEXT char after that is a comma or a closing parentheses, that indicates
			//there is only one char after '$', that follows the proper criterias, so pop of the '$' and set the counter back to 0
		{
			--check_if_next_char_valid;
			Rule_syntax.pop();
		}

		if (rule_defenition[j] == ')')//if you see a closing parentheses, indicates that it closing the open parentheses that came
			//before it, and the open parentheses is still in the stack, so pop it
		{
			Rule_syntax.pop();
		}
	}

	looking_for_specific_char = rule_defenition.find(":- OR");//See if the user typed in ":- OR", if not, check for AND

	if (looking_for_specific_char != rule_defenition.npos)
	{
		is_token_and_proper_operator_there = true;
	}

	if (is_token_and_proper_operator_there == false)//If it can't find the OR one, look with AND with the same notation ":- AND"
	{
		looking_for_specific_char = rule_defenition.find(":- AND");

		if (looking_for_specific_char != rule_defenition.npos)
		{
			is_token_and_proper_operator_there = true;
		}
	}


	//If there's nothing in the stack, if the counter is zero and the token was properly typed, then the RULE sythax is passed
	if (Rule_syntax.size() == 0 && check_if_next_char_valid == 0 && is_token_and_proper_operator_there == true)
	{
		return true;
	}
	else
	{
		cout << "Your syntax for -> " + rule_defenition + " is wrong" << endl;
		cout << "A proper example would be: RULE Parent($X,$Y) :- AND Father($X,$Y) Mother($X,$Y)" << endl;
		cout << "Please have a space before the ':-'  token, and after it followed by the logical operator (OR/AND), space, and the rest of the rule"
			<< endl << endl;
		user_mess_up = true;
		return false;
	}
}

bool Valid_INFERENCE_Input(string inference_defenition, bool& user_mess_up)
{
	stack<char> Rule_syntax; //Gonna be pushing '(' and '$', and they only get popped when there is a closed parentheses or the
	//proper rules for '$' were followed

	int check_if_next_char_valid = 0; //keeps track of the '$' symbol, and if the next char after that token are valid
	int content_in_array = 0;//checks to see how many char are actually in the array

	for (char& c : inference_defenition)//counts how many char are in the array, until it hits the null char or new line char
	{
		++content_in_array;
	}

	int i = 0;

	while (inference_defenition[i] != '(')//Check before the parentheses that the relationship name is only captial or lowercase letters,
		//no whitespaces or symbols
	{
		if (isalpha(inference_defenition[i]) == 0)
		{
			cout << "The relationship name must be only alphabets, no spaces or symbols, followed by a '('" << endl;
			cout << "Example: 'GrandFather('" << endl;
			user_mess_up = true;
			return false;
		}
		++i;
	}

	for (int j = 0; j < content_in_array; ++j)//goes through the array and pushes and pops the '(' and '$' char if certain criterias
		//are meet
	{
		if (inference_defenition[j] == '(') Rule_syntax.push(inference_defenition[j]);
		if (inference_defenition[j] == '$')
		{
			Rule_syntax.push(inference_defenition[j]);
			if (isupper(inference_defenition[j + 1]) != 0 && isalpha(inference_defenition[j + 1]) != 0)//if the next char after '$' is one
				//alphabet and it is uppercase, it is a valid char to have after '$'
			{
				++check_if_next_char_valid;
			}
			else
			{
				cout << "All INFERENCE parameters must have a $ symbol followed by ONE uppercase character" << endl;
				cout << "Example: GrandFather($X,$Y) or GrandFather($X,$Y) GF" << endl;
				cout << "Proceeding to the quit option" << endl << endl;
				user_mess_up = true;
				return false;
			}
		}

		if (check_if_next_char_valid != 0 && (inference_defenition[j + 2] == ',' || inference_defenition[j + 2] == ')'))
			//if the char after '$' is valid, and the next NEXT char after that is a comma or a closing parentheses, that indicates
			//there is only one char after '$', that follows the proper criterias, so pop of the '$' and set the counter back to 0
		{
			--check_if_next_char_valid;
			Rule_syntax.pop();
		}

		if (inference_defenition[j] == ')')//if you see a closing parentheses, indicates that it closing the open parentheses that came
			//before it, and the open parentheses is still in the stack, so pop it
		{
			Rule_syntax.pop();
		}
	}


	//If there's nothing in the stack, if the counter is zero, then the RULE sythax is passed
	if (Rule_syntax.size() == 0 && check_if_next_char_valid == 0)
	{
		return true;
	}
	else
	{
		user_mess_up = true;
		return false;
	}
}

bool Valid_DROP_Input(string drop_defenition, bool& user_mess_up)
{
	for(int i = 0;i< drop_defenition.length(); ++i) //loop through the string char by char, and only fails if there is a char that's not a letter
	{

		if (isalpha(drop_defenition[i]) == 0)
		{
			cout << "The DROP name must only be alphabets, no spaces or symbols before or after the name" << endl;
			cout << "Example: 'DROP Father' " << endl;
			user_mess_up = true;
			return false;
		}
	}

	return true;

}

bool Valid_DUMP_Input(string dump_defenition, bool& user_mess_up)
{

	size_t looking_for_specific_file_ending = dump_defenition.find(".sri");//look to see if the file name typed in ends with a ".sri"

	if (looking_for_specific_file_ending != dump_defenition.npos)//if there is a ".sri", then the file is named properly 
	{
		return true;
	}
	else
	{
		cout << "Name your file whatever you would like, however it must end with '.sri'" << endl;
		cout << "Example 'Output_file.sri'" << endl;
		user_mess_up = true;
		return false;
	}
}

bool Valid_LOAD_Input(string fileName, bool& user_mess_up)
{
	int count = 0;//used to count which line within the file we're at
	bool syntax_correct = false; //a flag that indicates true if the syntax is correct, false if it's not


    size_t looking_for_specific_file_ending = fileName.find(".sri");//check to see if the user tried to load a file that's not ".sri"

    if (looking_for_specific_file_ending == fileName.npos)
    {
        cout << "Name your file whatever you would like, however it must end with '.sri'" << endl;
        cout << "Example 'Output_file.sri'" << endl;
        user_mess_up = true;
        return false;

    }

    const char* f = fileName.c_str();
	fstream file;
	// line
	string line;
	file.exceptions(fstream::badbit);
	try
	{
		// open file
		file.open(f, ios::in);
		if(!file)//If the file doesn't exist, stop the program
		{
			cout<<"The file doesn't exist"<<endl;
			cout<<"Please type everything correctly for the file to be loaded"<<endl<<endl;
			return false;
		}
		while (getline(file, line))//run while there is a line in the file
		{
			if ( line == "")//if the line is a blank line, means nothing is there, exit out of the loop. 
				//Meant to pervent the while loop from going one more than it's suppose to
				break;
			++count;

			string delimeter = " ";//break the line into two parts, the first part is the command
			//the rest is the content of the command
			size_t pos = 0;
			string command = " ";
			pos = line.find(delimeter);
			command = line.substr(0, pos);
			line.erase(0, pos + delimeter.length());
			string rest = line;

			for (int i = 0; i < (int)command.size(); ++i) //captalizes all the words in the first part
			{
				command[i] = toupper(command[i]);

			}

			if (command == "FACT"){//depending on if it's a rule or a fact, call the proper syntax 
				syntax_correct = Valid_FACT_Input(rest, user_mess_up);
			}
			else if (command == "RULE"){
				syntax_correct = Valid_RULE_Input(rest, user_mess_up);
			}
            else
            {
                cout << "INVALID Command Syntax\n";
                cout << "The file can only contain RULE and FACT, nothing else" << endl;
                syntax_correct = false;
            }



			if (syntax_correct == false){
				cout << "One of the lines wasn't typed properly, please go back and fix that line in that file" << endl;
				cout << "That line is :" << command + " " + rest << "at line: "<< count << endl << endl;
				return false;
			}
		}
	}
	catch (fstream::failure e) {
		cerr << "Failed to load file\n" << endl;
	}

	return true;//returns true, indicating the file contains only FACT and RULE with proper syntax 
}

bool Quit_Session(char answer)//Ask the user if they want to end the program, if they say yes, ask if they have saved: Yes = Quit, No = DUMP, then quit
//if the user says no instead, ask them how many times they want the program to loop through until being asked to quit again
{
	cout << "Do you want to continue? Y for YES, N for NO: ";
	cin >> answer;
	cout << '\n';

	answer = toupper(answer); //Captilize the input incase they type a lowercase char

	if (answer == 'N')//if they say no, check to make sure they saved before they exit
	{
		cout << "Have you saved your session? Y for yes, N for no: ";

		cin >> answer;
		cout << '\n';
		answer = toupper(answer);

		if (answer == 'Y')
		{
			return true;
		}
		else
		{
			Helper::instance()->parseCommand("DUMP quicksave.sri");
			cout << "Your session has been saved" << endl << "Goodbye" << endl;
			return true;
		}
	}

	return false;//user indicates they want the program to continue running 
}



string Interface::start(void)
{
	return "Welcome to the Simple Rule-Base Inference Engine or SRI for short";
}

string Interface::display(void)
{
	return "Please enter one of the six commands with their proper content:\n=======================================\n-FACT(store in a fact)\n-RULE(store in a rule)\n-LOAD(load in a file)\n-INFERENCE(issue a query)\n-DUMP(download all facts and rule into a file)\n-DROP(remove a fact or rule)\n-QUIT(end the session)\n=======================================\n\nEnter here: ";
}


string Interface::clientInput(char* input)
{

	// char UserInput[200];//Stores what the user inputs into the stream, can take spaces 
	string string_version_UserInput;//convert what the user typed in the stream into a string to be able to work on it

	string first_part_of_command = " ";//Stores the first part of the command, the type of command itself
	string second_part_of_command;//Stores the second part of the command, the defenition of the command
	//int counter_of_char = 0; //counter to keep track of how many characters the user inputed into the array

	//char endsession = '\0'; //Checks if the user wants to exit the program or not
	bool error_commited = false;//checks to see if an error is commited at all or not
	//bool program_looping = true;//keeps the while loop going as long as the user doesn't indicate they want to quit
	//bool first_half_error_commited = false;//Has the user commited an error by miscalling a certain command?
	bool second_half_error_commited = false;

	string all_commands[6] = { "FACT", "RULE", "DROP", "INFERENCE", "LOAD", "DUMP" };//All the commands the user can type in

	string_version_UserInput = input;//convert what char the user typed in into a string 

		//if the user indicates they want to quit, with three different variations of how they can type in quit, the program ends 
		if(string_version_UserInput.compare("QUIT")==0 || string_version_UserInput.compare("Quit")==0 || string_version_UserInput.compare("quit") ==0)
		{
			return "Goodbye";
		}

		string delimeter = " ";//break the line into two parts, the first part is the command
			//the rest is the content of the command
		size_t pos = 0;
		pos = string_version_UserInput.find(delimeter);
		first_part_of_command = string_version_UserInput.substr(0, pos);
		string_version_UserInput.erase(0, pos + delimeter.length());
		second_part_of_command = string_version_UserInput;

		for (int i = 0; i < (int)first_part_of_command.size(); ++i) //captalizes all the words in the first part
		{
			first_part_of_command[i] = toupper(first_part_of_command[i]);
		}

		for (int i = 0; i <= 6; ++i)//checks if the first word matches any command, if not, proceed to the quit menu
		{
			if (i == 6)//If you get to six, you are outside the size of the array, indicating you didn't type in one of the commands properly 
			{
				return "Error: You need to type in one of those six commands in all capital and proper spelling\n";
//				first_half_error_commited = true;
//				error_commited = true;
				//break;
			}

			if (first_part_of_command.compare(all_commands[i]) == 0)//if the user input for the first part matches the command, continue on
			{
				break;
			}
		}

		//depending on which command is called, call the proper syntax check 
		if (first_part_of_command == "FACT")
		{
			if (Valid_FACT_Input(second_part_of_command, error_commited) == false)
			{
				second_half_error_commited = true;
			}
		}
		else if (first_part_of_command == "RULE")
		{
			if (Valid_RULE_Input(second_part_of_command, error_commited) == false)
			{
				second_half_error_commited = true;
			}
		}
		else if (first_part_of_command == "INFERENCE")
		{
			if (Valid_INFERENCE_Input(second_part_of_command, error_commited) == false)
			{
				second_half_error_commited = true;
			}
		}
		else if (first_part_of_command == "DROP")
		{
			if (Valid_DROP_Input(second_part_of_command, error_commited) == false)
			{
				second_half_error_commited = true;
			}
		}
		else if (first_part_of_command == "DUMP")
		{
			if (Valid_DUMP_Input(second_part_of_command, error_commited) == false)
			{
				second_half_error_commited = true;
			}
		}
		else if (first_part_of_command == "LOAD")
		{
			if (Valid_LOAD_Input(second_part_of_command, error_commited) == false)
			{
				second_half_error_commited = true;
			}
		}

		if (/*!first_half_error_commited && */!second_half_error_commited)//If there are no errors in the input, pass it into the function
		{
			string total_command = first_part_of_command + " " + second_part_of_command;
			Helper::instance()->parseCommand(total_command);
		}

		// if (error_commited == true)//Time to exit
		// {
		// 	if (Quit_Session(endsession))
		// 	{
		// 		return;
		// 	}
  //          else
  //          {
  //              error_commited = false;
  //          }
		// }
		// cin.ignore(1, '\n');
	return Helper::instance()->getString();

}







// void Interface::run()
// {
// 	char UserInput[200];//Stores what the user inputs into the stream, can take spaces
// 	string string_version_UserInput;//convert what the user typed in the stream into a string to be able to work on it
//
// 	string first_part_of_command = " ";//Stores the first part of the command, the type of command itself
// 	string second_part_of_command;//Stores the second part of the command, the defenition of the command
// 	int counter_of_char = 0; //counter to keep track of how many characters the user inputed into the array
//
// 	char endsession = '\0'; //Checks if the user wants to exit the program or not
// 	bool error_commited = false;//checks to see if an error is commited at all or not
// 	bool program_looping = true;//keeps the while loop going as long as the user doesn't indicate they want to quit
//
// 	string all_commands[6] = { "FACT", "RULE", "DROP", "INFERENCE", "LOAD", "DUMP" };//All the commands the user can type in
//
// 	cout << "Welcome to the Simple Rule-Base Inference Engine or SRI for short" << endl << endl;
//
// 	while (program_looping == true)// This loop keeps the program running until the user indicates they want to exit out
// 	{
//
// 		bool first_half_error_commited = false;//Has the user commited an error by miscalling a certain command?
// 		bool second_half_error_commited = false;//Has the user commited an error by having the wrong syntax
//
// 		cout << "Please enter one of the six commands with their proper content=>" << endl << "	-(1)FACT(store in a fact)"<< endl << "	-(2)RULE(store in a rule)"
// 			<< endl << "	-(3)LOAD(load in a file)" << endl << "	-(4)INFERENCE(issue a query)" << endl
// 			<< "	-(5)DUMP(download all facts and rule into a file)" << endl <<"	-(6)DROP(remove a fact or rule)" << endl << "	-QUIT(end the session)"
// 			<< endl <<"Enter here: ";
//
// 		cin.get(UserInput, sizeof(UserInput) - 1, '\n');//get char for input stream until either the array is full
// 		//or the new line char is encountered
// 		cin.clear();
// 		cout << endl;
//
// 		string_version_UserInput = UserInput;//convert what char the user typed in into a string
//
// 		//if the user indicates they want to quit, with three different variations of how they can type in quit, the program ends
// 		if(string_version_UserInput.compare("QUIT")==0 || string_version_UserInput.compare("Quit")==0 || string_version_UserInput.compare("quit") ==0)
// 		{
// 			cout << "Goodbye" << endl;
// 			break;
// 		}
//
// 		string delimeter = " ";//break the line into two parts, the first part is the command
// 			//the rest is the content of the command
// 		size_t pos = 0;
// 		pos = string_version_UserInput.find(delimeter);
// 		first_part_of_command = string_version_UserInput.substr(0, pos);
// 		string_version_UserInput.erase(0, pos + delimeter.length());
// 		second_part_of_command = string_version_UserInput;
//
// 		for (int i = 0; i < (int)first_part_of_command.size(); ++i) //captalizes all the words in the first part
// 		{
// 			first_part_of_command[i] = toupper(first_part_of_command[i]);
// 		}
//
// 		for (int i = 0; i <= 6; ++i)//checks if the first word matches any command, if not, proceed to the quit menu
// 		{
// 			if (i == 6)//If you get to six, you are outside the size of the array, indicating you didn't type in one of the commands properly
// 			{
// 				cout << "Error: You need to type in one of those six commands in all capital and proper spelling" << endl;
// 				cout << "Proceeding to the quit option" << endl;
// 				first_half_error_commited = true;
// 				error_commited = true;
// 				break;
// 			}
//
// 			if (first_part_of_command.compare(all_commands[i]) == 0)//if the user input for the first part matches the command, continue on
// 			{
// 				break;
// 			}
// 		}
//
// 		//depending on which command is called, call the proper syntax check
// 		if (first_part_of_command == "FACT")
// 		{
// 			if (Valid_FACT_Input(second_part_of_command, error_commited) == false)
// 			{
// 				second_half_error_commited = true;
// 			}
// 		}
// 		else if (first_part_of_command == "RULE")
// 		{
// 			if (Valid_RULE_Input(second_part_of_command, error_commited) == false)
// 			{
// 				second_half_error_commited = true;
// 			}
// 		}
// 		else if (first_part_of_command == "INFERENCE")
// 		{
// 			if (Valid_INFERENCE_Input(second_part_of_command, error_commited) == false)
// 			{
// 				second_half_error_commited = true;
// 			}
// 		}
// 		else if (first_part_of_command == "DROP")
// 		{
// 			if (Valid_DROP_Input(second_part_of_command, error_commited) == false)
// 			{
// 				second_half_error_commited = true;
// 			}
// 		}
// 		else if (first_part_of_command == "DUMP")
// 		{
// 			if (Valid_DUMP_Input(second_part_of_command, error_commited) == false)
// 			{
// 				second_half_error_commited = true;
// 			}
// 		}
// 		else if (first_part_of_command == "LOAD")
// 		{
// 			if (Valid_LOAD_Input(second_part_of_command, error_commited) == false)
// 			{
// 				second_half_error_commited = true;
// 			}
// 		}
//
// 		if (!first_half_error_commited && !second_half_error_commited)//If there are no errors in the input, pass it into the function
// 		{
// 			string total_command = first_part_of_command + " " + second_part_of_command;
// 			Helper::instance()->parseCommand(total_command);
// 		}
//
// 		if (error_commited == true)//Time to exit
// 		{
// 			if (Quit_Session(endsession))
// 			{
// 				program_looping = false;
// 			}
//            else
//            {
//                error_commited = false;
//            }
// 		}
//
// 		cin.ignore(1, '\n');
// 	}
// }

// void Interface::run()
// {
// 	// char UserInput[200];//Stores what the user inputs into the stream, can take spaces 
// 	// string string_version_UserInput;//convert what the user typed in the stream into a string to be able to work on it
//
// 	// string first_part_of_command = " ";//Stores the first part of the command, the type of command itself
// 	// string second_part_of_command;//Stores the second part of the command, the defenition of the command
// 	// int counter_of_char = 0; //counter to keep track of how many characters the user inputed into the array
//
// 	// char endsession = '\0'; //Checks if the user wants to exit the program or not 
// 	// bool error_commited = false;//checks to see if an error is commited at all or not
// 	// bool program_looping = true;//keeps the while loop going as long as the user doesn't indicate they want to quit
//
// 	// string all_commands[6] = { "FACT", "RULE", "DROP", "INFERENCE", "LOAD", "DUMP" };//All the commands the user can type in
//
// 	// cout << "Welcome to the Simple Rule-Base Inference Engine or SRI for short" << endl << endl;
// 	start();
// 	while (program_looping == true)// This loop keeps the program running until the user indicates they want to exit out
// 	{
//
// 		bool first_half_error_commited = false;//Has the user commited an error by miscalling a certain command?
// 		bool second_half_error_commited = false;//Has the user commited an error by having the wrong syntax
// 		display();
// 		// cout << "Please enter one of the six commands with their proper content=>" << endl << "	-(1)FACT(store in a fact)"<< endl << "	-(2)RULE(store in a rule)"
// 		// 	<< endl << "	-(3)LOAD(load in a file)" << endl << "	-(4)INFERENCE(issue a query)" << endl
// 		// 	<< "	-(5)DUMP(download all facts and rule into a file)" << endl <<"	-(6)DROP(remove a fact or rule)" << endl << "	-QUIT(end the session)"
// 		// 	<< endl <<"Enter here: ";
//
// 		cin.get(UserInput, sizeof(UserInput) - 1, '\n');//get char for input stream until either the array is full
// 		//or the new line char is encountered
// 		cin.clear();
// 		cout << endl;
//
// 		string_version_UserInput = UserInput;//convert what char the user typed in into a string 
//
// 		//if the user indicates they want to quit, with three different variations of how they can type in quit, the program ends 
// 		if(string_version_UserInput.compare("QUIT")==0 || string_version_UserInput.compare("Quit")==0 || string_version_UserInput.compare("quit") ==0)
// 		{
// 			cout << "Goodbye" << endl;
// 			break;
// 		}
//
// 		string delimeter = " ";//break the line into two parts, the first part is the command
// 			//the rest is the content of the command
// 		size_t pos = 0;
// 		pos = string_version_UserInput.find(delimeter);
// 		first_part_of_command = string_version_UserInput.substr(0, pos);
// 		string_version_UserInput.erase(0, pos + delimeter.length());
// 		second_part_of_command = string_version_UserInput;
//
// 		for (int i = 0; i < (int)first_part_of_command.size(); ++i) //captalizes all the words in the first part
// 		{
// 			first_part_of_command[i] = toupper(first_part_of_command[i]);
// 		}
//
// 		for (int i = 0; i <= 6; ++i)//checks if the first word matches any command, if not, proceed to the quit menu
// 		{
// 			if (i == 6)//If you get to six, you are outside the size of the array, indicating you didn't type in one of the commands properly 
// 			{
// 				cout << "Error: You need to type in one of those six commands in all capital and proper spelling" << endl;
// 				cout << "Proceeding to the quit option" << endl;
// 				first_half_error_commited = true;
// 				error_commited = true;
// 				break;
// 			}
//
// 			if (first_part_of_command.compare(all_commands[i]) == 0)//if the user input for the first part matches the command, continue on
// 			{
// 				break;
// 			}
// 		}
//
// 		//depending on which command is called, call the proper syntax check 
// 		if (first_part_of_command == "FACT")
// 		{
// 			if (Valid_FACT_Input(second_part_of_command, error_commited) == false)
// 			{
// 				second_half_error_commited = true;
// 			}
// 		}
// 		else if (first_part_of_command == "RULE")
// 		{
// 			if (Valid_RULE_Input(second_part_of_command, error_commited) == false)
// 			{
// 				second_half_error_commited = true;
// 			}
// 		}
// 		else if (first_part_of_command == "INFERENCE")
// 		{
// 			if (Valid_INFERENCE_Input(second_part_of_command, error_commited) == false)
// 			{
// 				second_half_error_commited = true;
// 			}
// 		}
// 		else if (first_part_of_command == "DROP")
// 		{
// 			if (Valid_DROP_Input(second_part_of_command, error_commited) == false)
// 			{
// 				second_half_error_commited = true;
// 			}
// 		}
// 		else if (first_part_of_command == "DUMP")
// 		{
// 			if (Valid_DUMP_Input(second_part_of_command, error_commited) == false)
// 			{
// 				second_half_error_commited = true;
// 			}
// 		}
// 		else if (first_part_of_command == "LOAD")
// 		{
// 			if (Valid_LOAD_Input(second_part_of_command, error_commited) == false)
// 			{
// 				second_half_error_commited = true;
// 			}
// 		}
//
// 		if (!first_half_error_commited && !second_half_error_commited)//If there are no errors in the input, pass it into the function
// 		{
// 			string total_command = first_part_of_command + " " + second_part_of_command;
// 			Helper::instance()->parseCommand(total_command);
// 		}
//
// 		if (error_commited == true)//Time to exit
// 		{
// 			if (Quit_Session(endsession))
// 			{
// 				program_looping = false;
// 			}
//            else
//            {
//                error_commited = false;
//            }
// 		}
//
// 		cin.ignore(1, '\n');
// 	}
// }





// void Interface:: run()
// {
//     // Danielle Testing GrandMother($X,$X)
// //    Helper::instance()->parseCommand("FACT Father(Jeff,Danielle)");
// //    Helper::instance()->parseCommand("FACT Mother(Sandy,Danielle)");
// //    Helper::instance()->parseCommand("FACT Father(Nick,Jeff)");
// //    Helper::instance()->parseCommand("FACT Mother(Judy,Jeff)");
// //    Helper::instance()->parseCommand("FACT Father(Paul,Sandy)");
// //    Helper::instance()->parseCommand("FACT Mother(Lianne,Sandy)");
// //    Helper::instance()->parseCommand("RULE Parent($X,$Y):- OR Father($X,$Y) Mother($X,$Y)");
// //    Helper::instance()->parseCommand("RULE GrandFather($X,$Y):- AND Father($X,$Z) Parent($Z,$Y)");
// //    Helper::instance()->parseCommand("RULE GrandMother($X,$Y):- AND Mother($X,$Z) Mother($Z,$Y)");
// //    Helper::instance()->parseCommand("RULE GrandMother($X,$Y):- AND Mother($X,$Z) Father($Z,$Y)");
// //    Helper::instance()->parseCommand("FACT Mother(Annie,Annie)");
// ////    Helper::instance()->parseCommand("INFERENCE GrandMother($X,$X)");
// ////    Helper::instance()->parseCommand("INFERENCE Mother($X,$X)");
// //    
// ////    Helper::instance()->parseCommand("RULE Parent($X,$Y):- OR Father($X,$Y) Mother($A,$B)"); // works
// ////        Helper::instance()->parseCommand("RULE Parent($X,$Y):- OR Father($A,$B) Mother($X,$Y)"); // works
// //    Helper::instance()->parseCommand("INFERENCE Parent($X,$Y)"); // this works under the ASSUMPTION the parameters defined are the same being entered // READ ME
//    
//     // Helper::instance()->parseCommand("LOAD output.txt");
//    
////      Helper::instance()->parseCommand("FACT FATHER(Jeff,Danielle)");
//////      Helper::instance()->parseCommand("FACT MOTHER(Sandy,Danielle)");
////      Helper::instance()->parseCommand("FACT FATHER(Nick,Jeff)");
////      Helper::instance()->parseCommand("FACT MOTHER(Judy,Jeff)");
////      Helper::instance()->parseCommand("FACT FATHER(Paul,Sandy)");
//////      Helper::instance()->parseCommand("FACT MOTHER(Lianne,Sandy)");
////      Helper::instance()->parseCommand("RULE PARENT($X,$Y):- OR FATHER($X,$Y) MOTHER($X,$Y)");
////      Helper::instance()->parseCommand("RULE GrandFather($X,$Y):- OR FATHER($X,$Y) PARENT($X,$Y)");
////     Helper::instance()->parseCommand("RULE Fathers($X,$Y):- OR FATHER($X,$Y) FATHER($X,$Y) FATHER($X,$Y)");
////      Helper::instance()->parseCommand("RULE GF($X,$Z):- OR FATHER($X,$Y) MOTHER($Z,$Y)");
////      Helper::instance()->parseCommand("RULE GM($X,$Y):- AND MOTHER($X,$Z) MOTHER($Z,$Y)");
////      Helper::instance()->parseCommand("RULE GM($X,$Y):- AND MOTHER($X,$Z) FATHER($Z,$Y)");
//     
////     Helper::instance()->parseCommand("FACT MOTHER(Lianne,Sandy)");
////     Helper::instance()->parseCommand("FACT MOTHER(Sandy,Danielle)");
////     Helper::instance()->parseCommand("FACT MOTHER(Danielle,Bill)");
////     Helper::instance()->parseCommand("RULE GreatGrandMother($V,$Z):- AND MOTHER($V,$W) MOTHER($W,$X) MOTHER($X,$Z)");
//     
////          Helper::instance()->parseCommand("INFERENCE GM($X,Danielle)");
////     Helper::instance()->parseCommand("INFERENCE GM(Lianne,$Y)");
//     
////     Helper::instance()->parseCommand("INFERENCE GreatGrandMother($V,$Z)");
////     Helper::instance()->parseCommand("INFERENCE GM($X,$Y)");
////      Helper::instance()->parseCommand("INFERENCE GrandFather($X,$Y) GF");
////     Helper::instance()->parseCommand("INFERENCE Fathers($X,$Y)");
//     Helper::instance()->parseCommand("LOAD code_breaker.sri");
//     
//      Helper::instance()->parseCommand("INFERENCE STAAAR($W,$Z)");
//Helper::instance()->parseCommand("INFERENCE SYSTEMTWO($X,$Y)");
//     
////      Helper::instance()->parseCommand("DUMP output2.txt");
//
//    
//    
// //    Helper::instance()->parseCommand("INFERENCE GF($X,$Z)");
// //    Helper::instance()->parseCommand("INFERENCE PARENT($X,$Y)");
//     //Helper::instance()->parseCommand("INFERENCE MOTHER($X,$Y) M");
//    
// //    Helper::instance()->parseCommand("INFERENCE GrandMother($A,$B)");
//    
//     //	Helper::instance()->parseCommand("FACT Father(Jeff,Danielle)");
//     //	Helper::instance()->parseCommand("FACT Mother(Sandy,Danielle)");
//     //	Helper::instance()->parseCommand("FACT Father(Nick,Jeff)");
//     //	Helper::instance()->parseCommand("FACT Mother(Judy,Jeff)");
//     //	Helper::instance()->parseCommand("FACT Father(Paul,Sandy)");
//     //	Helper::instance()->parseCommand("FACT Mother(Lianne,Sandy)");
//     //	Helper::instance()->parseCommand("RULE Parent($X,$Y):- OR Father($X,$Y) Mother($X,$Y)");
//     //	Helper::instance()->parseCommand("RULE GrandFather($X,$Y):- AND Father($X,$Z) Parent($Z,$Y)");
//     //	Helper::instance()->parseCommand("RULE GrandMother($X,$Y):- AND Mother($X,$Z) Mother($Z,$Y)");
//     //	Helper::instance()->parseCommand("RULE GrandMother($X,$Y):- AND Father($X,$Z) Mother($Z,$Y)");
//     //	Helper::instance()->parseCommand("FACT Mother(Annie,Annie");
//     //	Helper::instance()->parseCommand("INFERENCE GrandMother($X,$X)");
//     //
//     //    Helper::instance()->parseCommand("FACT Father(Roger,John)");
//     //    //    Helper::instance()->parseCommand("FACT Mother(Marry,John)");
//     //    Helper::instance()->parseCommand("FACT Mother(Marry,Bill)");
//     //    Helper::instance()->parseCommand("FACT Father(Albert,Marry)");
//     //    Helper::instance()->parseCommand("FACT Father(Albert,Roger)");
//     //    Helper::instance()->parseCommand("FACT Father(Roger,Albert)");
//     //    Helper::instance()->parseCommand("FACT Mother(Marry,Albert)");
//     //    //    Helper::instance()->parseCommand("FACT Mother(Margret,Robert)");
//     //    Helper::instance()->parseCommand("FACT Mother(Nancy,Margret)");
//     //    //            Helper::instance()->parseCommand("FACT Mother(Nancy,Roger)");
//     //    Helper::instance()->parseCommand("FACT Mother(Margret,Bob)");
//     //    Helper::instance()->parseCommand("FACT Mother(Margret,Allen)");
//     //    Helper::instance()->parseCommand("FACT Mother(Margret,Marry)");
//     //    Helper::instance()->parseCommand("FACT Mother(Annie,Annie)");
//     //
//     //
//     //    //    Helper::instance()->parseCommand("FACT Father(Roger,Albert)");
//     //    //    Helper::instance()->parseCommand("FACT Father(Allen,Margret, Alliosn, Joe, Jim)");
//     //    //Helper::instance()->parseCommand("INFERENCE Father($X,$Y)");
//     //    //    Helper::instance()->parseCommand("LOAD output.txt");
//     //    //    Helper::instance()->parseCommand("DUMP output2.txt");
//     //
//     //
//     //    Helper::instance()->parseCommand("RULE Parent($X,$Y):- OR Father($X,$Y) Mother($X,$Y)");
//     //    //            Helper::instance()->parseCommand("RULE GrandMother($X,$Y):- AND Mother($X,$Z) Mother($Z,$Y)"); // works
//     //                Helper::instance()->parseCommand("RULE GrandMother($X,$Y):- AND Mother($X,$Z) Father($Z,$Y)"); // works
//     //    //    Helper::instance()->parseCommand("RULE GrandFather($X,$Y):- AND Father($X,$Z) Parent($Z,$Y)"); // works
//     //    //    Helper::instance()->parseCommand("RULE GrandMother($X,$Y):- OR Mother($X,$Y) Parent($X,$Y)"); // works
//     //    Helper::instance()->parseCommand("RULE GrandMother($X,$Y):- AND Mother($X,$Z) Mother($Z,$Y)"); // works
//     //    //            Helper::instance()->parseCommand("RULE GrandMother($X,$Y):- AND Mother($X,$Z) Father($Z,$Y)");
//     //    //    Helper::instance()->parseCommand("RULE GrandFather($X,$Y):- AND Father($X,$Z) Parent($Z,$Y)"); // works
//     //    //    Helper::instance()->parseCommand("INFERENCE GrandMother($X,$Y) GF");
//     //    //            Helper::instance()->parseCommand("INFERENCE Parent($X,$Y)");
//     ////                     Helper::instance()->parseCommand("INFERENCE Parent($X,Marry)");
//     //    //                 Helper::instance()->parseCommand("INFERENCE Parent(Albert,$Y)");
//     //    //        Helper::instance()->parseCommand("INFERENCE Father($X,$Y)");
//     //    //            Helper::instance()->parseCommand("INFERENCE Mother($X,$Y)");
//     ////                 Helper::instance()->parseCommand("INFERENCE GrandMother($X,$X)");
//     //    //                  Helper::instance()->parseCommand("INFERENCE GrandMother(Marry,$Y)");
//     //    Helper::instance()->parseCommand("INFERENCE GrandMother($X,Marry)");
//     //    //                  Helper::instance()->parseCommand("INFERENCE GrandMother($X,$Y)");
//     //    //    Helper::instance()->parseCommand("INFERENCE GrandFather($X,$Y)");
//     //    //      Helper::instance()->parseCommand("DUMP output2.txt");
//    
// }
