#include "sample_3_utf8_csv_load.h"
#include "convert_table.h"
#include "csv_load.h"
#include "bom_utf8.h"
#include <algorithm>
#include <new>
#include <Windows.h>

/*
* 3.CSVファイルに日本語が含まれる場合の処理方法
*
* シフトJISであれば何も考えなくて良い
* 日本語以外との共存を考えるとUTF-8にしておきたい
* BOM付きとBOM無しとがある
*/
std::vector<std::vector<std::wstring>> sample_3_utf8_csv_load(std::istream& istm)
{
	char bom_buf[sizeof bom_utf8];
	if (istm.read(bom_buf, sizeof bom_buf) && memcmp(bom_buf, bom_utf8, sizeof bom_utf8) == 0)
		return convert_table<wchar_t>(csv_load(istm), CP_UTF8);
	else {
		istm.clear();
		istm.seekg(0);
		return convert_table<wchar_t>(csv_load(istm), CP_UTF8);
	}
}
