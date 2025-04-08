/**
 * Includes common text conversion methods.
 * All in static format for easy access.
 */

#pragma once

#include <iostream>
#include <sstream>

// include all windows specific stuff
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

class TextUtils
{
public:

	static LPCTSTR CombineStrings_LPCTSTR(std::string string1, std::string string2);
	static LPCSTR CombineStrings_LPCSTR(std::string string1, std::string string2);

	static std::wstring StringToWchar(const std::string& s);
	static LPCWSTR StringToLPCWSTR(const std::string& s);

	static std::string WcharToString(const std::wstring& s);

	static std::string IntToString(int iNumber);
	static std::string IntToHex(int iNumber);
	static char* IntToChar(int iNumber);

private:

	static std::wstring s_tempResourcePath;

	static std::wstring s_tempWstring;
	static std::string s_tempString;
	static char* s_tempChar;
};