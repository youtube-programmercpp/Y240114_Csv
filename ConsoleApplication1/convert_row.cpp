#include "convert_row.h"
#include "convert_field.h"
#include <algorithm>
template
< class target_char_type
, class source_char_type
>
std::vector<std::basic_string<target_char_type>> convert_row
( const std::vector<std::basic_string<source_char_type>>& row
, unsigned codepage
)
{
	std::vector<std::basic_string<target_char_type>> retval(row.size());
	std::transform
	( row   .begin()
	, row   .end  ()
	, retval.begin()
	, [codepage](const std::basic_string<source_char_type>& field)->std::basic_string<target_char_type>
		{
			return convert_field<target_char_type>(field, codepage);
		});
	return retval;
}
template std::vector<std::basic_string<wchar_t>> convert_row(const std::vector<std::basic_string< char  >>& row, unsigned codepage);
template std::vector<std::basic_string< char  >> convert_row(const std::vector<std::basic_string<wchar_t>>& row, unsigned codepage);
