#include "csv_load.h"
#include "csv_save.h"
#include "convert_table.h"
#include "bom_utf8.h"
#include "sample_1_reverse_output.h"
#include "sample_2_insert.h"
#include "sample_3_utf8_csv_load.h"

#include <fstream>
#include <stdexcept>
#include <Windows.h>
#include <iostream>

void sample_1_reverse_output(const std::vector<std::vector<std::string>>& table, std::ostream& ostm);

void test1()
{
	if (std::ifstream input{ "input_1.csv" }) {
		if (std::ofstream output{ "output_1.csv" })
			sample_1_reverse_output(csv_load(input), output);
		else
			throw std::runtime_error(__FILE__ "(" _CRT_STRINGIZE(__LINE__) "): " __FUNCTION__ "で出力ファイルを開くことができませんでした。");
	}
	else
		throw std::runtime_error(__FILE__ "(" _CRT_STRINGIZE(__LINE__) "): " __FUNCTION__ "で入力ファイルを開くことができませんでした。");
}
void test2()
{
	if (std::ifstream input1{ "input_1.csv" }) {
		if (std::ifstream input2{ "input_2.csv" }) {
			if (std::ofstream output{ "output_2.csv" })
				csv_save(output, sample_2_insert(csv_load(input1), csv_load(input2)));
			else
				throw std::runtime_error(__FILE__ "(" _CRT_STRINGIZE(__LINE__) "): " __FUNCTION__ "で出力ファイルを開くことができませんでした。");
		}
		else
			throw std::runtime_error(__FILE__ "(" _CRT_STRINGIZE(__LINE__) "): " __FUNCTION__ "で入力ファイル2を開くことができませんでした。");

	}
	else
		throw std::runtime_error(__FILE__ "(" _CRT_STRINGIZE(__LINE__) "): " __FUNCTION__ "で入力ファイル1を開くことができませんでした。");
}
void test3()
{
	if (std::ifstream input{ "input_3.csv" }) {
		if (std::ofstream output{ "output_3.csv" })
			csv_save(output.write(bom_utf8, sizeof bom_utf8), convert_table<char>(sample_3_utf8_csv_load(input), CP_UTF8));
		else
			throw std::runtime_error(__FILE__ "(" _CRT_STRINGIZE(__LINE__) "): " __FUNCTION__ "で出力ファイルを開くことができませんでした。");
	}
	else
		throw std::runtime_error(__FILE__ "(" _CRT_STRINGIZE(__LINE__) "): " __FUNCTION__ "で入力ファイルを開くことができませんでした。");
}
int main()
{
	try {
		test1();
		test2();
		test3();
	}
	catch (const std::exception& e) {
		OutputDebugStringA(e.what());
		OutputDebugStringA("\n");
		std::cerr << e.what() << std::endl;
	}
}
