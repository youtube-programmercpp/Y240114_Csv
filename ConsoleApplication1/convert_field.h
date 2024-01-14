#pragma once
#include <string>
template
< class target_char_type
, class source_char_type
>
std::basic_string<target_char_type> convert_field
( const std::basic_string<source_char_type>& field
, unsigned codepage
);
