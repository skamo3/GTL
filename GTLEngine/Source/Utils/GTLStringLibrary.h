#pragma once

#include <string>
#include <locale>
#include <codecvt>

class UGTLStringLibrary
{
public:
	static wstring StringToWString(const string& str)
	{
		wstring_convert<codecvt_utf8<wchar_t>> converter;
		return converter.from_bytes(str);
	}

	/*static string WStringToString(const string& wstr)
	{
	}*/

};