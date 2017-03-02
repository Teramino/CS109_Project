==========================================================================
 MAKEFILE COMMANDS
==========================================================================

 make all : creates an executable
 make clean : removes object files from directory
 make wipe : removes all files from directory excluding makefile

===========================================================================
 ASSUMPTIONS
===========================================================================
 
 Throughout this project, we had to make decisions about the SRI
 functionalities where the instructions were ambiguous. One of those 
 assumptions we made about the relations is that there won't be a 
 relation taking in a multiple number of parameters. According to 
 Sharath TS on Piazza (https://piazza.com/class/ixbsc9b3aky5d6?cid=193)
 this is perfectly okay. Also, we chose to use vectors because they are 
 dynamically allocated and efficient about it. 

===========================================================================
 PROJECT DETAILS
===========================================================================
 
 Our SRI Engine has an interactive interface in which the user can 
 specify a file name to load or write commands into the console. Beware,
 if there is an error in the file, the entire file will not be processed 
 and it will print an error message. 
 Some cases for inference such as rule targets that have a rule definition
 do not function as intended.

 