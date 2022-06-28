#pragma once
#include <string>
#include <vector>

// this file for DLL import extern's (links)
#ifndef __linux__
#define IMPORT extern "C" __declspec(dllimport)
#else
#define IMPORT extern "C"
#endif

using namespace std;

namespace dll {
IMPORT const char* module_text();
IMPORT char* to_string(char* buffer, long value);
IMPORT long to_int64(const char* str);
IMPORT bool checkSort(vector<int>& check, bool toRight);
IMPORT bool checkSort2(vector<int>& check);
IMPORT void quickSort(vector<int>& a, const int& l, const int& r);
IMPORT int compare(string s1, string s2);
}  // namespace dll
