#include <iostream>
#include <sstream>
#include <unordered_map>

template <typename Container>
void erase(Container& c) {
	c.erase(begin(c), end(c));
}

template <typename Container, typename... Containers>
void erase(Container& c, Containers&... cs) {
	erase(c);
	erase(cs...);
}

int aw_main(int argc, const char* argv[]) {
	std::unordered_map<std::string, long> vars{};
	std::unordered_map<long, std::string> vals{};
	std::string line;
	
	while (std::getline(std::cin, line)) {
		std::stringstream ss{ line };
		std::string cmd, op;

		if ((ss >> cmd) && cmd == "clear")
			erase(vars, vals);

		else if (cmd == "def") {
			long val;

			ss >> cmd >> val;

			if (vars.count(cmd) > 0)
				vals.erase(vars[cmd]);

			vars[cmd] = val;
			vals[val] = cmd;

		} else {
			ss >> cmd;

			long res = vars.count(cmd) > 0 ? vars[cmd] : 0;
			bool ok = vars.count(cmd) > 0 ? true : false;

			while (ok && (ss >> op >> cmd) && op != "=")
				if (ok = ok && vars.count(cmd) > 0) {
					if (op == "+")
						res += vars[cmd];
					else
						res -= vars[cmd];
				}

			std::cout << line.substr(5) << " ";

			if (ok && vals.count(res) > 0)
				std::cout << vals[res] << "\n";

			else
				std::cout << "unknown\n";
		}
	}

	return 0;
}