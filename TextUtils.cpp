/**
 * Includes common text conversion methods.
 * All in static format for easy access.
 */

#include "TextUtils.h"

std::wstring TextUtils::s_tempResourcePath = L"";
std::wstring TextUtils::s_tempWstring = L"";
std::string TextUtils::s_tempString = "";
char* TextUtils::s_tempChar = NULL;

LPCTSTR TextUtils::CombineStrings_LPCTSTR(std::string string1, std::string string2)
{
	//std::string resourcePath = string1 + string2;

	std::stringstream ss;
	ss << string1 << string2;
	std::string resourcePath = ss.str();
	TextUtils::s_tempResourcePath = StringToWchar(resourcePath);
	return TextUtils::s_tempResourcePath.c_str();
}

LPCSTR TextUtils::CombineStrings_LPCSTR(std::string string1, std::string string2)
{
	std::stringstream ss;
	ss << string1 << string2;
	TextUtils::s_tempString = ss.str();
	return TextUtils::s_tempString.c_str();
}

std::wstring TextUtils::StringToWchar(const std::string& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

LPCWSTR TextUtils::StringToLPCWSTR(const std::string& s)
{
	TextUtils::s_tempWstring = TextUtils::StringToWchar(s);
	return TextUtils::s_tempWstring.c_str();
}

std::string TextUtils::WcharToString(const std::wstring& s)
{
	int len;
	int slength = (int)s.length() + 1;
	len = WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, 0, 0, 0, 0);
	char* buf = new char[len];
	WideCharToMultiByte(CP_ACP, 0, s.c_str(), slength, buf, len, 0, 0);

	std::string r(buf);
	delete[] buf;
	TextUtils::s_tempString = r;

	return TextUtils::s_tempString;
}

std::string TextUtils::IntToString(int iNumber)
{
	std::stringstream ss;
	ss << iNumber;
	TextUtils::s_tempString = ss.str();

	return TextUtils::s_tempString;
}

std::string TextUtils::IntToHex(int iNumber)
{
	std::stringstream ss;
	ss << std::hex << iNumber;
	TextUtils::s_tempString = ss.str();

	return TextUtils::s_tempString;
}

char* TextUtils::IntToChar(int iNumber)
{
	TextUtils::s_tempChar = NULL;
	TextUtils::s_tempChar = new char[128];
	sprintf_s(TextUtils::s_tempChar, 128, "%d", iNumber);

	return TextUtils::s_tempChar;
}