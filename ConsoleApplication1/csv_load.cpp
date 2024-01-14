#include "csv_load.h"
#include <sal.h>

//二重引用符で始まるセルを読み込む
static bool quoted
( _Inout_ std::vector<std::vector<std::string>>& table
, _Inout_ std::istream                         & istm 
, _Out_   char                                 & ch   
)
{
	for (;;) {
		if (istm.get(ch)) {
			if (ch == '"') {
				//この二重引用符は何を意味するのかは、
				//続く文字で決まる。
				if (istm.get(ch)) {
					//続く文字で振り分け
					switch (ch) {
					case '"':
						//(1)二重引用符自体
						table.back().back().push_back('"');
						continue;
					case ',':
						//(2)フィールド終了…次のフィールドあり
						table.back().push_back({});
						return istm.get(ch).good();
					case '\n':
						//(3)フィールド終了…レコード終了（次のフィールド無し）
						if (istm.get(ch)) {
							//次のレコードあり
							table.push_back({});
							table.back().push_back({});
							return true;
						}
						else
							return false;
					default:
						//(4)異常
						throw std::runtime_error(__FILE__ "(" _CRT_STRINGIZE(__LINE__) "): 予期しない二重引用符が現れました。");
					}
				}
				else
					return false;
			}
			else {
				//二重引用符ではない文字はセルの内容である
				table.back().back().push_back(ch);
				continue;
			}
		}
		else {
			//二重引用符が閉じていないのにファイル内容が終わってしまった
			throw std::runtime_error(__FILE__ "(" _CRT_STRINGIZE(__LINE__) "): 二重引用符が閉じていません。");
		}
	}
}
static bool unquoted
( _Inout_ std::vector<std::vector<std::string>>& table
, _Inout_ std::istream                         & istm 
, _Inout_ char                                 & ch   
)
{
	for (;;) {
		switch (ch) {
		case '\n':
			//レコード終了
			if (istm.get(ch)) {
				//次のレコードあり
				table.push_back({});
				table.back().push_back({});
				return true;
			}
			else
				return false;
		case ',':
			//フィールド終了
			//次のフィールドを追加
			table.back().push_back({});
			return istm.get(ch).good();
		default:
			table.back().back().push_back(ch);
			if (istm.get(ch))
				continue;
			else
				return false;
		}
	}
}
std::vector<std::vector<std::string>> csv_load(std::istream& istm)
{
	char ch;
	if (istm.get(ch)) {
		//成功
		std::vector<std::vector<std::string>> table;
		table.push_back({});
		table.back().push_back({});
		for (;;) {
			if (ch == '"' ? quoted(table, istm, ch) : unquoted(table, istm, ch))
				continue;
			else
				return table;
		}
	}
	else
		return {};
}
