#include "sample_1_reverse_output.h"
#include "csv_write_cell.h"
#include <algorithm>

//1.CSVファイル出力する際にtableの最後から出力する方法
// ～方式の候補～
// (1) end から begin に向かって処理する
// (2) reverse iterator ... rbegin, rend を使う
//
// 学習の順番としては(1)が良い
// ～理由～
// begin と end を正しく理解していればそれだけで逆順の処理が書ける。（基本知識で出来る）
// reverse iterator は追加の知識が必要となる。なおかつ、その知識は逆順専用。
//  
// ただし、reverse iterator を用いると記述が簡素化されるので開発上・保守上は有利。
// 余力のある人は reverse iterator の使い方を身に付けると良い。
// （基礎知識があると reverse iteratorの勉強は殆ど不要。すぐに分かるはず。）

void sample_1_reverse_output(const std::vector<std::vector<std::string>>& table, std::ostream& ostm)
{
	for (auto row = table.end();;) {
		if (row == table.begin())
			break;
		else {
			--row;
			auto column = row->begin();
			if (column != row->end()) {
				csv_write_cell(ostm, *column);
				while (++column != row->end())
					csv_write_cell(ostm << ',', *column);
			}
			ostm << '\n';
		}
	}
}
