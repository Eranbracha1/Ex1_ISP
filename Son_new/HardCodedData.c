/* Description -  this file includes the Son function instansiation and decleration  */

#include "HardCodedData.h"
 

DWORD BYTES_TO_READ = 16;

/*
Function Description: creates file both for reading and for writing, gets the file name and a char* of "read" or "write"
Parameters: pointer to a file, and char
Returns: a handle
*/
HANDLE create_file(LPCSTR p_file_name, char* mode)
{
	DWORD dwDesiredAccess;
	DWORD create_mode;
	DWORD file_share_mode;
	DWORD flag_and_attrs;
	if (strcmp(mode, "read") == 0)
	{
		dwDesiredAccess = GENERIC_READ;
		file_share_mode = FILE_SHARE_READ;
		create_mode = OPEN_EXISTING;
		flag_and_attrs = FILE_ATTRIBUTE_NORMAL;
	}

	if (strcmp(mode, "write") == 0)
	{
		dwDesiredAccess = GENERIC_WRITE;
		file_share_mode = FILE_SHARE_WRITE;
		create_mode = OPEN_ALWAYS;
		flag_and_attrs = FILE_ATTRIBUTE_NORMAL;
	}

	HANDLE hFile = CreateFileA(
		p_file_name,			// Filename
		dwDesiredAccess,		// Desired access
		file_share_mode,        // Share mode
		NULL,                   // Security attributes
		create_mode,            // Creates a new file, only if it doesn't already exist
		flag_and_attrs,			// Flags and attributes
		NULL);                  // Template file handle

	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("INVALID HANDLE VALUE: could not create file Handle\n");
		exit(1);
	}
	return hFile;

}

/*
Function Description: get the file handler and a char* message, and writes it to the file
Parameters:HANDLE to a file_handler and a pinter to p_message string
Returns: void
*/
void write_file(HANDLE file_handler, char* p_message)
{
	DWORD dwBytesToWrite = (DWORD)strlen(p_message);
	DWORD dwBytesWritten = 0;
	if (FALSE == WriteFile(
		file_handler,            // Handle to the file
		p_message,				// Buffer to write
		dwBytesToWrite,					// Buffer size
		dwBytesWritten,					// Bytes written
		NULL))
		printf("could not write file\n");
		return;

}

/*
Function Description: get the file handler, a char* data buffer, and reads data from file
Parameters:HANDLE to a file_handler and a pinter to data_buffer string
Returns: void
*/
void read_file(HANDLE file_handler, char* data_buffer)
{
	int nbytesread = 0;
		if(FALSE == ReadFile(
			file_handler,
			data_buffer,
			BYTES_TO_READ,
			&nbytesread,
			NULL))
		{
			printf("could not read file\n");
			return;
			
		}
}

/*
Function Description:   the 'main' functionality will happend here.  creatying handlers to the files that are given,
						and creating a new file. encrypting the givven file with block chipper method, starting to encrypt from the given offset byte.
Parameters: 2 file pointersand offset integer
Returns:0 if socess, 1 if fails
*/
int main_function(LPCSTR file_name_1, int offset, LPCSTR file_name_2)
{
	LPCSTR encrypted_message_file_name = "Encrypted_message.txt";
	LPCSTR plaintext_file_name = file_name_1;
	LPCSTR key_file_name = file_name_2;
	char plaintext_buffer[MAX_LINE_LEN] = { '\0'};
	char key_buffer[MAX_LINE_LEN] = { 0 };
	char encrypted_message[MAX_LINE_LEN]; 
	HANDLE plaintext_file_name_handler;
	HANDLE key_file_name_handler;
	HANDLE encrypted_message_handler;
	DWORD dwBytesRead_plaintext = 0;
	DWORD dwBytesRead_key = 0;
	int plaintext_file_size = -1;

	encrypted_message_handler = create_file(encrypted_message_file_name, "write");
	plaintext_file_name_handler = create_file(plaintext_file_name, "read");
	key_file_name_handler = create_file(key_file_name, "read");

	plaintext_file_size = GetFileSize(plaintext_file_name_handler, NULL);
	if (plaintext_file_size != INVALID_FILE_SIZE)
	{
		if (offset < plaintext_file_size)
		{
			if (INVALID_SET_FILE_POINTER == SetFilePointer(plaintext_file_name_handler, offset, NULL, NULL))
		{
			CloseHandle(encrypted_message_handler);
			CloseHandle(plaintext_file_name_handler);
			CloseHandle(key_file_name_handler);
			printf("SetFilePointer of %hs returned INVALID VALUE,\n could not set file pointer returning failure", plaintext_file_name);
			return STATUS_CODE_FAILURE;
		}
			if (INVALID_SET_FILE_POINTER == SetFilePointer(encrypted_message_handler, offset, NULL, NULL))
		{
			CloseHandle(encrypted_message_handler);
			CloseHandle(plaintext_file_name_handler);
			CloseHandle(key_file_name_handler);
			printf("SetFilePointer of %hs returned INVALID VALUE,\n could not set file pointer returning failure", encrypted_message_file_name);
			return STATUS_CODE_FAILURE;
		}

			read_file(plaintext_file_name_handler, plaintext_buffer);
			read_file(key_file_name_handler, key_buffer);

			for (int k = 0; k < MAX_LINE_LEN - 1; k++) {
				encrypted_message[k] = ((char)plaintext_buffer[k] ^ (char)key_buffer[k]);
			}
			encrypted_message[MAX_LINE_LEN - 1] = '\0';
			write_file(encrypted_message_handler, encrypted_message);
		}

		else
		{
			SetEndOfFile(encrypted_message_handler);
		}

	}

	CloseHandle(encrypted_message_handler);
	CloseHandle(plaintext_file_name_handler);
	CloseHandle(key_file_name_handler);

	return STATUS_CODE_SUCCESS;
}