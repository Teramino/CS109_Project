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
 assumptions we made about the relations is that all relations will be 
 taking in exactly two parameters or rule targets. According to Sharath TS 
 on Piazza (https://piazza.com/class/ixbsc9b3aky5d6?cid=193) this is 
 perfectly okay. Our understanding is that "Mother" and "mother" are
 different facts and therefore all commands are case-sensitive. If there 
 is an error in syntax, we believe the command should not be processed.
 This assumption means that if a file contains any invalid syntax, it will
 not be loaded into our engine. However, our program prints an error 
 message with a line number to make it easier to spot errors in the file.
 The program accepts duplicate facts and rules and will print them into the
 dump file if they are not removed. Also, our assumption about the drop
 command is that the user may only specify a rule or fact target. This 
 will delete all instances of the rule and fact from the vectors. We made 
 this assumption because in the project pdf file (p.4) it specifies that
 the drop function takes the name of the fact or rule to be drop, but 
 does not mention or have any examples of being able to drop a specific 
 rule or fact. We made the assumption that all AND operations should have
 a correlation between its parameters and all OR operations should have 
 matching parameters. These operations will be invalid and unable to find
 a result, however, their syntax is correct so it will compute.

===========================================================================
 PROJECT DETAILS
===========================================================================

 Our SRI Engine has an interactive interface in which the user can 
 specify a file name to load or write commands into the console. From the
 console, the user has the option to type any command or type 'QUIT' to 
 exit the program. Depending on the command, the interface will inform 
 the user on the results of their instruction. If there is an error, the
 program will display the error and ask the user if they wish to continue.
 If the user wishes to quit, the interface will prompt the user whether
 they have saved their progress. If not, the program will create a file
 named quicksave.sri and will dump their current session into it.

 While brainstorming how we will implement this program, we decided on 
 using vectors throughout our program because they are dynamically allocated 
 and efficient about it. The vectors allow us to add and remove data from
 them in order to easily manipulate the rule and knowledge bases.

===========================================================================
 PHASE THREE FIXES
===========================================================================

 + AND and OR operations fixed to query correct information for generic 
   inferences.
 + Dump pushes out the correct parameters to a file and creates a file
   with a '.sri' extension instead of '.txt'.
 + AND and OR operations handle recursive calls.
 + Specific inferences will correctly fetch data.
 + UML Design updated to correctly demonstrate proper Use Case, Class,
   and Sequence diagrams.
 + Inference only returns a single instance of a fact removing all
   duplicates.
 + Program correctly stores essential information for rules and facts.
 + Program no longer saves all inferences into the Knowledge database and 
   will only do so if specified by the user.
 + Program correctly queries inferences with the same parameter.
 + UNIX-specific segmentation fault fixed for inferences with the same
   parameter.
 + Code cleaned up and output/interaction improved.
 + Queries recognize most relationships between parameters like
   ($X,$Y) AND ($Y,$Z) -> ($X,$Z)
 
===========================================================================
 MULTI-THREADING
===========================================================================

 + Fortunately, we programmed our SRI engine with AND pipelining without
   the use of threads.
 