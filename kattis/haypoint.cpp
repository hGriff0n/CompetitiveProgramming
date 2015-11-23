#include <iostream>
#include <sstream>
#include <map>

int hp_main(int argc, const char* argv[]) {
	int m, n, v;
	std::cin >> m >> n;

	std::map<std::string, int> val;
	std::string input;

	while (m--) {
		std::cin >> input >> v;

		val[input] = v;
	}

	while (n--) {
		long total{};
		std::getline(std::cin, input, '.');
		std::stringstream ss{ input };

		while (ss >> input)
			total += val[input];

		std::cout << total << "\n";
	}

	return 0;
}