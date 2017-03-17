//Main.cpp

#include "Common.hpp"
#include "Interface.hpp"


//the main function that will call upon the program to run. 
int main() {
	
    Interface i;//create an object of interface, this will be the main hub the user will be interacting with the program
     i.run();//call upon the run function, which will start up the display and let the user go through the program until they indicate they want to quit
    
    return 0;
    
}
