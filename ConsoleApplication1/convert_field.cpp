#include "convert_field.h"
#include <Windows.h>

template<>std::wstring convert_field
( const std::string& field
, unsigned codepage
)
{
	if (const auto cbMultiByte = field.length()) {
		if (cbMultiByte > INT_MAX)
			throw std::bad_alloc();
		else {
			std::wstring retval;
			retval.resize(cbMultiByte);
			retval.resize(MultiByteToWideChar
			( /*_In_                                     UINT   CodePage      */codepage
			, /*_In_                                     DWORD  dwFlags       */0UL
			, /*_In_NLS_string_(cbMultiByte)             LPCCH  lpMultiByteStr*/field.c_str()
			, /*_In_                                     int    cbMultiByte   */static_cast<int>(cbMultiByte)
			, /*_Out_writes_to_opt_(cchWideChar, return) LPWSTR lpWideCharStr */&retval.front()
			, /*_In_                                     int    cchWideChar   */static_cast<int>(retval.size())
			));
			return retval;
		}
	}
	else
		return {};
}
template<>std::string convert_field
( const std::wstring& field
, unsigned codepage
)
{
	if (const auto cchWideChar = field.length()) {
		if (cchWideChar > INT_MAX / 3)
			throw std::bad_alloc();
		else {
			std::string retval;
			retval.resize(3 * cchWideChar);
			retval.resize(WideCharToMultiByte
			( /*_In_                                           UINT   CodePage         */codepage
			, /*_In_                                           DWORD  dwFlags          */0UL
			, /*_In_NLS_string_(cchWideChar)                   LPCWCH lpWideCharStr    */field.c_str()
			, /*_In_                                           int    cchWideChar      */static_cast<int>(cchWideChar)
			, /*_Out_writes_bytes_to_opt_(cbMultiByte, return) LPSTR  lpMultiByteStr   */&retval.front()
			, /*_In_                                           int    cbMultiByte      */static_cast<int>(retval.size())
			, /*_In_opt_                                       LPCCH  lpDefaultChar    */nullptr
			, /*_Out_opt_                                      LPBOOL lpUsedDefaultChar*/nullptr
			));
			return retval;
		}
	}
	else
		return {};
}
