#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>
#include <string.h>

#define TIMEOUT_IN_MILLISECONDS 5000
#define BRUTAL_TERMINATION_CODE 0x55

BOOL CreateProcessSimple(TCHAR CommandLine[], PROCESS_INFORMATION* ProcessInfoPtr);
void CreateProcessSimpleMain(char** argv, int offset);
