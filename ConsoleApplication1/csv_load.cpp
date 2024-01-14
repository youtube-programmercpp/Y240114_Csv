#include "csv_load.h"
#include <sal.h>

//��d���p���Ŏn�܂�Z����ǂݍ���
static bool quoted
( _Inout_ std::vector<std::vector<std::string>>& table
, _Inout_ std::istream                         & istm 
, _Out_   char                                 & ch   
)
{
	for (;;) {
		if (istm.get(ch)) {
			if (ch == '"') {
				//���̓�d���p���͉����Ӗ�����̂��́A
				//���������Ō��܂�B
				if (istm.get(ch)) {
					//���������ŐU�蕪��
					switch (ch) {
					case '"':
						//(1)��d���p������
						table.back().back().push_back('"');
						continue;
					case ',':
						//(2)�t�B�[���h�I���c���̃t�B�[���h����
						table.back().push_back({});
						return istm.get(ch).good();
					case '\n':
						//(3)�t�B�[���h�I���c���R�[�h�I���i���̃t�B�[���h�����j
						if (istm.get(ch)) {
							//���̃��R�[�h����
							table.push_back({});
							table.back().push_back({});
							return true;
						}
						else
							return false;
					default:
						//(4)�ُ�
						throw std::runtime_error(__FILE__ "(" _CRT_STRINGIZE(__LINE__) "): �\�����Ȃ���d���p��������܂����B");
					}
				}
				else
					return false;
			}
			else {
				//��d���p���ł͂Ȃ������̓Z���̓��e�ł���
				table.back().back().push_back(ch);
				continue;
			}
		}
		else {
			//��d���p�������Ă��Ȃ��̂Ƀt�@�C�����e���I����Ă��܂���
			throw std::runtime_error(__FILE__ "(" _CRT_STRINGIZE(__LINE__) "): ��d���p�������Ă��܂���B");
		}
	}
}
static bool unquoted
( _Inout_ std::vector<std::vector<std::string>>& table
, _Inout_ std::istream                         & istm 
, _Inout_ char                                 & ch   
)
{
	for (;;) {
		switch (ch) {
		case '\n':
			//���R�[�h�I��
			if (istm.get(ch)) {
				//���̃��R�[�h����
				table.push_back({});
				table.back().push_back({});
				return true;
			}
			else
				return false;
		case ',':
			//�t�B�[���h�I��
			//���̃t�B�[���h��ǉ�
			table.back().push_back({});
			return istm.get(ch).good();
		default:
			table.back().back().push_back(ch);
			if (istm.get(ch))
				continue;
			else
				return false;
		}
	}
}
std::vector<std::vector<std::string>> csv_load(std::istream& istm)
{
	char ch;
	if (istm.get(ch)) {
		//����
		std::vector<std::vector<std::string>> table;
		table.push_back({});
		table.back().push_back({});
		for (;;) {
			if (ch == '"' ? quoted(table, istm, ch) : unquoted(table, istm, ch))
				continue;
			else
				return table;
		}
	}
	else
		return {};
}
