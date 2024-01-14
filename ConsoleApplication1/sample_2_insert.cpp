#include "sample_2_insert.h"
#include <algorithm>

/*
* 2.既存のCSVファイルの途中にtableを挿入する方法
* 
* 既存のCSVファイルをtable1、table2に読み込む
* table3を用意する。
* table1の途中までをtable3にコピーする。
* table2の全内容をtable3に追加する。
* table1の残りをtable3に追加する。
*/
std::vector<std::vector<std::string>> sample_2_insert
( const std::vector<std::vector<std::string>>& table1
, const std::vector<std::vector<std::string>>& table2
)
{
	const auto size_1 = table1.size();
	const auto size_2 = table2.size();
	std::vector<std::vector<std::string>> table3(size_1 + size_2);
	const auto table1の途中 = table1.begin() + (size_1 / 2);
	auto コピー先 = std::copy(table1.begin(), table1の途中, table3.begin());
	     コピー先 = std::copy(table2.begin(), table2.end(), コピー先      );
	                std::copy(table1の途中  , table1.end(), コピー先      );
	return table3;
}
