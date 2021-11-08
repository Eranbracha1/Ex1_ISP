/*

Intro to System Programming - Project #1 - Father project


Gabriel sofer               Eran bracha
313589202			        312275514

project description :- this project simulating Father process that creats Son process few time, 
as many as he need, to block chippering a file given with a key file.  the encrypted message  will 
be writen to new file.   the whole project includes using API instructions.

*/


/*
Function Description:
Parameters:
Returns:
*/



#include "FatherHeader.h"

/*
Function Description: main function. receives 2 files: one to encrypt and a key file. checks that the correct number of parameters were given, and sending 16 bytes from the file to a new process called Son
Parameters: file to encrypt, key file
Returns: 0 if success, 1 if failed
*/
int main(int argc, char* argv[])
{
	/*
		arguments:
	   0-Son.exe        1-message_to_encrypt.txt
	   2-key.txt
	 */
	if (argc != 3) {
		if (argc == 1 || argc == 0) {
			printf("Usage Error: no arguments was given!\nclosing the program\n");
		}
		else {
			printf("Usage Error:\tIncorrect number of arguments\nclosing the program");
			printf("%s <file_name>\n", argv[0]);
		}
		return STATUS_CODE_FAILURE;
	}


	int message_to_encrypt_size = -1;
	int offset = 0;
	HANDLE message_to_encrypt_handler;

	const char* message_to_encrypt_file_name = argv[1];
	message_to_encrypt_handler = create_file_handler(message_to_encrypt_file_name);
	message_to_encrypt_size = GetFileSize(message_to_encrypt_handler, NULL);
	/*Handle was used only to check file size and then closed*/
	CloseHandle(message_to_encrypt_handler);

	while (offset < message_to_encrypt_size) {
		CreateProcessSimpleMain(argv, offset);
		offset += 16;
	}
	

	return STATUS_CODE_SUCCESS;

}
