#include "convert_table.h"
#include "convert_row.h"
#include <algorithm>

template
< class target_char_type
, class source_char_type
> std::vector<std::vector<std::basic_string<target_char_type>>>
convert_table
( const std::vector<std::vector<std::basic_string<source_char_type>>>& table
, unsigned codepage
)
{
	std::vector<std::vector<std::basic_string<target_char_type>>> retval(table.size());
	std::transform
	( table .begin()
	, table .end  ()
	, retval.begin()
	, [codepage](const std::vector<std::basic_string<source_char_type>>& row)->std::vector<std::basic_string<target_char_type>>
		{
			return convert_row<target_char_type>(row, codepage);
		}
	);
	return retval;
}
template std::vector<std::vector<std::basic_string<wchar_t>>> convert_table(const std::vector<std::vector<std::basic_string< char  >>>& table, unsigned codepage);
template std::vector<std::vector<std::basic_string< char  >>> convert_table(const std::vector<std::vector<std::basic_string<wchar_t>>>& table, unsigned codepage);
