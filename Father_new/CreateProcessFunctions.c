#include "FatherHeader.h"

/**
* CreateProcessSimple uses the win32 API to create a process that runs the
* command in 'CommandLine'. it uses the win32 API function CreateProcess()
* using default values for most parameters.
*
* Accepts:
* --------
* CommandLine - a windows generic string containing the command that the new
*               process performs. ( See CreateProcess( documentation for more ).
* ProcessInfoPtr - an output parameter, used to return a PROCESS_INFORMATION
*					structure containing data about the process that was created.
*					( See CreateProcess() documentation for more ).
*
* Returns:
* --------
* the output of CreateProcess().
*/
BOOL CreateProcessSimple(TCHAR CommandLine[], PROCESS_INFORMATION *ProcessInfoPtr);
void CreateProcessSimpleMain(char** argv, int offset);
HANDLE create_file_handler(LPCSTR p_file_name);

/**
* Demonstrates win32 process creation and termination.
*/

// the father functionality. takes the files nane with specific offset, creating the commend line and activating the son
void CreateProcessSimpleMain(char** argv, int offset)
{
	char offset_string[50] ="\0";
	sprintf(offset_string, "%d", offset);
	int argv1_len = strlen(argv[1]);
	int argv2_len = strlen(argv[2]);
	
	int size_of_command = (strlen("..\\Debug\\Son.exe") + argv1_len + strlen(offset_string) + argv2_len + 4);
	PROCESS_INFORMATION procinfo;
	DWORD				waitcode;
	DWORD				exitcode;
	BOOL				retVal;
	char*				command = (char*)malloc(size_of_command * sizeof(char*));
	if (command == NULL) {
		printf("Memory allocating for son command string failed.\nclosing the program\n");
		exit(1);
	}
	sprintf_s(command, size_of_command, "..\\Debug\\Son.exe %s %s %s",
		argv[1], offset_string, argv[2]);


	TCHAR* command_t = (TCHAR*)malloc(size_of_command * sizeof(TCHAR*));
	if (command_t == NULL) {
		printf("Memory allocating for son command_t string failed.\nclosing the program\n");
		free(command);
		exit(1);
	}
	//Write formatted data to wide string
	swprintf(command_t, size_of_command, L"%hs", command);

			/*  Start the child process. */
	retVal = CreateProcessSimple(command_t, &procinfo);

	if (retVal == 0)
	{
		printf("Process Creation Failed!\nclosing program\n");
		free(command);
		free(command_t);
		exit(1);
	}

	waitcode = WaitForSingleObject(procinfo.hProcess, TIMEOUT_IN_MILLISECONDS); /* Waiting 5 secs for the process to end */

	printf("WaitForSingleObject is: ");
	switch (waitcode)
	{
	case WAIT_TIMEOUT:
		printf("WAIT_TIMEOUT\n"); break;
	case WAIT_OBJECT_0:
		printf("WAIT_OBJECT_0\n"); break;
	default:
		printf("0x%x\n", waitcode);
	}

	if (waitcode == WAIT_TIMEOUT) /* Process is still alive */
	{
		printf("Process was not terminated before timeout!\n"
			"Terminating brutally!\n");
		TerminateProcess(procinfo.hProcess, BRUTAL_TERMINATION_CODE); /* Terminating process with an exit code of 55h */
		Sleep(10);		/* Waiting a few milliseconds for the process to terminate,
						note the above command may also fail, so another WaitForSingleObject is required.
						We skip this for brevity */
	}

	GetExitCodeProcess(procinfo.hProcess, &exitcode);
	/*note that checking GetExitCodeProcess return value is in line 96*/

	if (command != NULL)
		free(command);
	if (command_t != NULL)
		free(command_t);
	CloseHandle(procinfo.hProcess); /* Closing the handle to the process */
	CloseHandle(procinfo.hThread); /* Closing the handle to the main thread of the process */


	printf("The exit code for the process is 0x%x\n", exitcode);
	if (exitcode != 0 && exitcode != 2)
	{
		printf("ERROR IN SON PROCESS\n EXITING PROGRAM");
		exit(1);
	}
}
/* this function get commandline argument TCHAR, and PROCESS INFORMATION, and creates a new process*/
BOOL CreateProcessSimple(TCHAR CommandLine[], PROCESS_INFORMATION *ProcessInfoPtr)
{
	STARTUPINFO	startinfo = { sizeof(STARTUPINFO), NULL, 0 }; /* <ISP> here we */
															  /* initialize a "Neutral" STARTUPINFO variable. Supplying this to */
															  /* CreateProcess() means we have no special interest in this parameter. */
															  /* This is equivalent to what we are doing by supplying NULL to most other */
															  /* parameters of CreateProcess(). */

	
	return CreateProcess(
		NULL,					/*  No module name (use command line). */
		CommandLine,			/*  Command line. */
		NULL,					/*  Process handle not inheritable. */
		NULL,					/*  Thread handle not inheritable. */
		FALSE,					/*  Set handle inheritance to FALSE. */
		NORMAL_PRIORITY_CLASS,	/*  creation/priority flags. */
		NULL,					/*  Use parent's environment block. */
		NULL,					/*  Use parent's starting directory. */
		&startinfo,				/*  Pointer to STARTUPINFO structure. */
		ProcessInfoPtr			/*  Pointer to PROCESS_INFORMATION structure. */
	);
}
/*a function that gets a file name and opens a handler for it, in order to check the file size*/
HANDLE create_file_handler(LPCSTR p_file_name)
{

	HANDLE hFile = CreateFileA(
		p_file_name,			// Filename
		GENERIC_READ,		// Desired access
		FILE_SHARE_READ,        // Share mode
		NULL,                   // Security attributes
		OPEN_EXISTING,            // Creates a new file, only if it doesn't already exist
		FILE_ATTRIBUTE_NORMAL,			// Flags and attributes
		NULL);                  // Template file handle

	if (hFile == INVALID_HANDLE_VALUE)
	{
		printf("INVALID HANDLE VALUE: could not create file Handle\nclosing the program \n");
		return STATUS_CODE_FAILURE;
	}
	return hFile;

}