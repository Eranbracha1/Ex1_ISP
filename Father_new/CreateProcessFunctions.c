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
		printf("Memory allocating for son command string failed.");
		//return BAD_STATUS;
		return 1;
	}
	sprintf_s(command, size_of_command, "Son.exe %s %s %s",
		argv[1], offset_string, argv[2]);


	TCHAR* commandt = (TCHAR*)malloc(size_of_command * sizeof(TCHAR*));
	if (commandt == NULL) {
		printf("Memory allocating for son commandt string failed.");
		//return BAD_STATUS;
		return 1;
	}
	swprintf(commandt, size_of_command, L"%hs", command);

			/*  Start the child process. */
	retVal = CreateProcessSimple(commandt, &procinfo);

	if (retVal == 0)
	{
		printf("Process Creation Failed!\n");
		return;
	}

	waitcode = WaitForSingleObject(
		procinfo.hProcess,
		TIMEOUT_IN_MILLISECONDS); /* Waiting 5 secs for the process to end */

	printf("WaitForSingleObject output: ");
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
		TerminateProcess(
			procinfo.hProcess,
			BRUTAL_TERMINATION_CODE); /* Terminating process with an exit code of 55h */
			Sleep(10); /* Waiting a few milliseconds for the process to terminate,
						note the above command may also fail, so another WaitForSingleObject is required.
						We skip this for brevity */
	}

	GetExitCodeProcess(procinfo.hProcess, &exitcode);

	printf("The exit code for the process is 0x%x\n", exitcode);

	/* Note: process is still being tracked by OS until we release handles */
	if (command != NULL)
		free(command);
	if (commandt != NULL)
		free(commandt);
	CloseHandle(procinfo.hProcess); /* Closing the handle to the process */
	CloseHandle(procinfo.hThread); /* Closing the handle to the main thread of the process */
}
//GAVRIZ

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
		// Failed to open/create file
		return 2;
	}
	return hFile;

}