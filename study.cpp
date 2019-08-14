/*
 * study.cpp
 *
 *  Created on: 2019年8月14日
 *      Author: kmp
 */
#include "study.h"

#include <regex>

void example_regex() {
	// 简单正则表达式匹配
	std::string fnames[] = { "foo.txt", "bar.txt", "baz.dat", "zoidberg" };
	std::regex txt_regex("[a-z]+\\.txt");
	for (const auto &fname : fnames) {
		std::cout << fname << ": " << std::regex_match(fname, txt_regex)
				<< '\n';
	}
	// 提取子匹配
	std::regex base_regex("([a-z]+)\\.txt");
	std::smatch base_match;
	for (const auto &fname : fnames) {
		if (std::regex_match(fname, base_match, base_regex)) {
			// 首个 sub_match 是整个字符串；下个
			// sub_match 是首个有括号表达式。
			if (base_match.size() == 2) {
				std::ssub_match base_sub_match = base_match[1];
				std::string base = base_sub_match.str();
				std::cout << fname << " has a base of " << base << '\n';
			}
		}
	}
	// 提取几个子匹配
	std::regex pieces_regex("([a-z]+)\\.([a-z]+)");
	std::smatch pieces_match;
	for (const auto &fname : fnames) {
		if (std::regex_match(fname, pieces_match, pieces_regex)) {
			std::cout << fname << '\n';
			for (size_t i = 0; i < pieces_match.size(); ++i) {
				std::ssub_match sub_match = pieces_match[i];
				std::string piece = sub_match.str();
				std::cout << "  submatch " << i << ": " << piece << '\n';
			}
		}
	}
}

void orgin_string() {
	//下面第二行是键盘按下的回车产生的换行，它会被如实地转为\n和一个换行

    cout<<R"(asdsd "\ \n
发的")"<<endl;
	//如果需要包含"(或)",需要像这样:"123( )123",即在引号和括号间添加任意一般字符(某些字符不行),
    //aa ,=*,以及上面的123 等等
    cout<<R"aa(""sad发斯蒂\\\芬"()")aa"<<endl;
}
