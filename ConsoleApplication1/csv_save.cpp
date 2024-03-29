#include "csv_save.h"
#include "csv_write_cell.h"

void csv_save(std::ostream& ostm, const std::vector<std::vector<std::string>>& table)
{
	for (const auto& row : table) {
		auto it = row.begin();
		//先頭のセルがない場合も想定しておく
		if (it != row.end()) {
			csv_write_cell(ostm, *it);
			while (++it != row.end())
				csv_write_cell(ostm << ',', *it);
		}
		ostm << '\n';
	}
}
