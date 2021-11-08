#include "FatherHeader.h"


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
