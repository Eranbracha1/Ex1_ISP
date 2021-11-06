#include "FatherHeader.h"


int main(int argc, char* argv[])
{
	/*
		arguments:
	   0-Son.exe        1-message_to_encrypt.txt
	   2-key.txt
	 */

	int message_to_encrypt_size = -1;
	int offset = 0;
	HANDLE message_to_encrypt_handler;

	const char* message_to_encrypt_file_name = argv[1];
	message_to_encrypt_handler = create_file_handler(message_to_encrypt_file_name);
	message_to_encrypt_size = GetFileSize(message_to_encrypt_handler, NULL);
	
	while (offset < message_to_encrypt_size) {
		CreateProcessSimpleMain(argv, offset);
		offset += 16;
	}
	
	CloseHandle(message_to_encrypt_handler);

	return 0;

}
