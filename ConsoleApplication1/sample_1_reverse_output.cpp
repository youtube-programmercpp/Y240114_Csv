#include "sample_1_reverse_output.h"
#include "csv_write_cell.h"
#include <algorithm>

//1.CSV�t�@�C���o�͂���ۂ�table�̍Ōォ��o�͂�����@
// �`�����̌��`
// (1) end ���� begin �Ɍ������ď�������
// (2) reverse iterator ... rbegin, rend ���g��
//
// �w�K�̏��ԂƂ��Ă�(1)���ǂ�
// �`���R�`
// begin �� end �𐳂����������Ă���΂��ꂾ���ŋt���̏�����������B�i��{�m���ŏo����j
// reverse iterator �͒ǉ��̒m�����K�v�ƂȂ�B�Ȃ����A���̒m���͋t����p�B
//  
// �������Areverse iterator ��p����ƋL�q���ȑf�������̂ŊJ����E�ێ��͗L���B
// �]�͂̂���l�� reverse iterator �̎g������g�ɕt����Ɨǂ��B
// �i��b�m��������� reverse iterator�̕׋��͖w�Ǖs�v�B�����ɕ�����͂��B�j

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
