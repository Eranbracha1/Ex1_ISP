// HardCodedData.h
#define _CRT_SECURE_NO_WARNINGS
#ifndef __HardCodedData_H__
#define __HardCodedData_H__
#define MAX_LINE_LEN 17
#define MAX_KEY_LEN 17
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>



// Constants -------------------------------------------------------------------

#define LOG__STATUS_CODE_SUCCESS ((int)(0))
#define LOG__STATUS_CODE_FAILURE ((int)(-1))

// Function Declarations -------------------------------------------------------


int main_function(LPCSTR file_name_1, int offset, LPCSTR file_name_2);
HANDLE create_file(LPCSTR p_file_name, char* mode);
void write_file(HANDLE file_handler, char* p_message);
void read_file(HANDLE file_handler, char* data_buffer);

#endif // __HardCodedData_H__
