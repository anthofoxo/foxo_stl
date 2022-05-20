// Small utility allowing easy UTF-8 character output on windows
//
// #include <foxo/u8out.h>
//
// int main()
// {
//     foxo::u8out << u8"You have £100\n";
// }

#pragma once

#ifdef _WIN32
#	include <Windows.h>
#endif

#include <iostream>
#include <codecvt>
#include <locale>
#include <string>
#include <sstream>

namespace foxo
{
	inline void WriteUTF8(const char* string)
	{
#if defined(_WIN32)
		try
		{
			std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> convert;
			std::wstring utf16native = convert.from_bytes(string); // If an exception is thrown, the string was not formatted UTF8, std::cout will be used instead
			WriteConsoleW(GetStdHandle(STD_OUTPUT_HANDLE), utf16native.c_str(), (DWORD) utf16native.size(), nullptr, nullptr);
		}
		catch (const std::range_error&)
		{
			std::cout << string;
		}
#else // currently not implmented for other operating systems
		std::cout << string;
#endif
	}

	struct _u8out
	{
		template<class T>
		_u8out& operator<<(const T& t)
		{
			std::stringstream ss;
			ss << t;
			WriteUTF8(ss.str().c_str());
			return *this;
		}
	} static u8out;
}
