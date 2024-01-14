#include "csv_write_cell.h"
#include <cstring>

void csv_write_cell(std::ostream& ostm, const std::string& s)
{
	//���s�A��d���p���A�R���}���܂ނ��ǂ����𒲂ׂ�
	//�@���s�A��d���p���A�R���}�ȊO�ō\��������Ԃ̒���
	//�A������S�̒�
	//�����A�@ == �A �Ȃ�Ή��s�A��d���p���A�R���}�͕����񒆂̂ǂ��ɂ����݂��Ă��Ȃ�
	if (std::strcspn(s.c_str(), "\n\",") == s.length()) {
		//quote�s�v
		ostm << s;
	}
	else {
		//quote�K�v
		ostm << '"';
		for (const auto ch : s) {
			if (ch == '"')
				ostm << '"' << '"';
			else
				ostm << ch;
		}
		ostm << '"';
	}
}
