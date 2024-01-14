#pragma once
#include <vector>
#include <string>
template
< class target_char_type
, class source_char_type
>
std::vector<std::basic_string<target_char_type>> convert_row
( const std::vector<std::basic_string<source_char_type>>& row
, unsigned codepage
);

