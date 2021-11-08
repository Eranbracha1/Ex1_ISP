/*

Intro to System Programming - Project #1 - Son project


Gabriel sofer               Eran bracha
313589202			        312275514

project description :- this project simulating Father process that creats Son process few time,
as many as he need, to block chippering a file given with a key file.  the encrypted message  will
be writen to new file.   the whole project includes using API instructions.

*/

#include "HardCodedData.h"


/*
Function Description: main function. receives 3 files: one to encrypt, a key file and a number in string forrmat.
						checks that the correct number of parameters were given, and sending the parameters to 
						main_function func , not before converting the number string givven to integer.
Parameters: file to encrypt, key file and offset string
Returns: 0 if success, 1 if failed
*/
int main(int argc, char *argv[])
{		/*
		arguments:
	   0-Son.exe        1-<plaintext file name>.txt   
	   2-<offset>       3-<key file name>.txt
		*/
	if (argc != 4) {
		if (argc == 1 || argc == 0) {
			printf("Usage Error: no arguments was given!\nclosing the program");
		}
		else {
			printf("Usage Error:\tIncorrect number of arguments\nclosing the program");
			printf("%s <file_name>\n", argv[0]);
		}
		return STATUS_CODE_FAILURE;
	}
	const char* arg1 = argv[1];
	int offset = atoi(argv[2]);
	const char* arg3 = argv[3];
	
	//printf("status code fail %s\n status code succ %s", STATUS_CODE_FAILURE, STATUS_CODE_SUCCESS);
	return(main_function(arg1, offset, arg3));

}

