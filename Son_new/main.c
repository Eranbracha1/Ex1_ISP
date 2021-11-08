#include "HardCodedData.h"


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

