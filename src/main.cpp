#include "word_ladder.h"

#include <iostream>

// Please note: it's not good practice to test your code via a main function that does
//  printing. Instead, you should be using your test folder. This file should only really
//  be used for more "primitive" debugging as we know that working solely with test
//  frameworks might be overwhelming for some.

// auto main() -> int {
// 	// auto const english_lexicon = word_ladder::read_lexicon("./english.txt");
// 	// auto const ladders = word_ladder::generate("fly", "sky", english_lexicon);
// 	// debug here
// 	auto const haha = word_ladder::read_lexicon("./test.txt");
// 	std::cout << haha.size();
// 	return 0;
// }

int main() {
	auto const haha = word_ladder::read_lexicon("./english.txt");
	// std::cout << haha.size() << '\n';
	auto const ladders = word_ladder::generate("atlases", "cabaret", haha);
	std::cout << ladders.size() << '\n';
	std::cout << ladders[0].size() << '\n';
	// for (auto ladder : ladders) {
	// 	for (auto word : ladder) {
	// 		std::cout << word << " ";
	// 	}
	// 	std::cout << '\n';
	// }


	// auto haha = word_ladder::read_lexicon("./test.txt");
	// std::cout << haha.size() << '\n';
	// std::string a = "port";
	// haha.erase(a);
	// std::cout << haha.size() << '\n';
	// return 0;
}
