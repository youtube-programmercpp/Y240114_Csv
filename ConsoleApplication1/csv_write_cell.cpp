#include "csv_write_cell.h"
#include <cstring>

void csv_write_cell(std::ostream& ostm, const std::string& s)
{
	//改行、二重引用符、コンマを含むかどうかを調べる
	//①改行、二重引用符、コンマ以外で構成される区間の長さ
	//②文字列全体長
	//もし、① == ② ならば改行、二重引用符、コンマは文字列中のどこにも存在していない
	if (std::strcspn(s.c_str(), "\n\",") == s.length()) {
		//quote不要
		ostm << s;
	}
	else {
		//quote必要
		ostm << '"';
		for (const auto ch : s) {
			if (ch == '"')
				ostm << '"' << '"';
			else
				ostm << ch;
		}
		ostm << '"';
	}
}
