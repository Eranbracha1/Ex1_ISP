
#include "HardCodedData.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{		/*
		arguments:
	   0-Son.exe        1-<plaintext file name>.txt   
	   2-<offset>       3-<key file name>.txt
		*/

	const char* arg1 = argv[1];
	int offset = atoi(argv[2]);
	const char* arg3 = argv[3];
	//
	////printf("%s", a);
	return(main_function(arg1, offset, arg3));
	//return(main_function("plaintext.txt",0,"key.txt"))

}

