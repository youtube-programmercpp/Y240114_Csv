#include "sample_2_insert.h"
#include <algorithm>

/*
* 2.������CSV�t�@�C���̓r����table��}��������@
* 
* ������CSV�t�@�C����table1�Atable2�ɓǂݍ���
* table3��p�ӂ���B
* table1�̓r���܂ł�table3�ɃR�s�[����B
* table2�̑S���e��table3�ɒǉ�����B
* table1�̎c���table3�ɒǉ�����B
*/
std::vector<std::vector<std::string>> sample_2_insert
( const std::vector<std::vector<std::string>>& table1
, const std::vector<std::vector<std::string>>& table2
)
{
	const auto size_1 = table1.size();
	const auto size_2 = table2.size();
	std::vector<std::vector<std::string>> table3(size_1 + size_2);
	const auto table1�̓r�� = table1.begin() + (size_1 / 2);
	auto �R�s�[�� = std::copy(table1.begin(), table1�̓r��, table3.begin());
	     �R�s�[�� = std::copy(table2.begin(), table2.end(), �R�s�[��      );
	                std::copy(table1�̓r��  , table1.end(), �R�s�[��      );
	return table3;
}
