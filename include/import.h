#pragma once
#include <string>
#include <vector>

// this file for DLL import extern's (links)
#ifndef EXPORT_SAMPLE
#ifndef __unix__
#define IMPORT extern "C" __declspec(dllimport)
#else
#define IMPORT extern "C"
#endif

#define PORT IMPORT
#else 
#ifndef __unix__
#define EXPORT extern "C" __declspec(dllexport) 
#else
#define EXPORT extern "C"
#endif

#define PORT EXPORT
#endif

using namespace std;

namespace dll {
	PORT const char* sample_module_text();
	PORT std::vector<int>* sample_get_data();
	PORT char* sample_to_string(char* buffer, long value);
	PORT long sample_to_int64(const char* str);
	PORT bool sample_checkSort(vector<int>& check, bool toRight);
	PORT bool sample_checkSort2(vector<int>& check);
	PORT void sample_quickSort(vector<int>& a, const int& l, const int& r);
	PORT int sample_compare(string s1, string s2);
	
	PORT void* sample_for_8bit(char* buf, int len);
	PORT void* sample_for_16bit(void* buf, int len);
	PORT void* sample_for_32bit(void* buf, int len);
	PORT void* sample_for_64bit(void* buf, int len);
}  // namespace dll
