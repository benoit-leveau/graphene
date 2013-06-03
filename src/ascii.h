
#ifndef __ASCII_H__
#define __ASCII_H__
#include <locale>

inline std::wstring quoteString(const std::wstring& str)
{
	return std::wstring(L"\"") + str + std::wstring(L"\"");
}

inline std::string quoteString(const std::string& str)
{
	return std::string("\"") + str + std::string("\"");
}

#ifdef WIN32
#pragma warning(push)
#pragma warning(disable:4996)
#endif // WIN32

inline std::wstring toWide(const std::string& str)
{
	std::size_t length = str.size() + 1;
	wchar_t* wTmp = new wchar_t[length];
	const std::ctype<wchar_t> & converter = std::use_facet<std::ctype<wchar_t> >(std::locale());
	converter.widen(str.c_str(), str.c_str() + length, wTmp);

	std::wstring wstr = std::wstring(wTmp);
	delete [] (wTmp);
	return wstr;
}

inline std::string toAscii(const std::wstring& str)
{
	std::size_t length = str.size() + 1;
	char* cTmp = new char[length];
	const std::ctype<wchar_t> & converter = std::use_facet<std::ctype<wchar_t> >(std::locale());
	converter.narrow(str.c_str(), str.c_str() + length, '_', cTmp);

	std::string cstr = std::string(cTmp);
	delete [] (cTmp);
	return cstr;
}

#ifdef WIN32
#pragma warning(pop)
#endif // WIN32

#endif // __ASCII_H_
