#include "sample_3_utf8_csv_load.h"
#include "convert_table.h"
#include "csv_load.h"
#include "bom_utf8.h"
#include <algorithm>
#include <new>
#include <Windows.h>

/*
* 3.CSV�t�@�C���ɓ��{�ꂪ�܂܂��ꍇ�̏������@
*
* �V�t�gJIS�ł���Ή����l���Ȃ��ėǂ�
* ���{��ȊO�Ƃ̋������l�����UTF-8�ɂ��Ă�������
* BOM�t����BOM�����Ƃ�����
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
