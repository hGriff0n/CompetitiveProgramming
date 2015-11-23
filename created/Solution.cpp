#include <sstream>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <set>
#include <map>

template <typename T>
auto read() {
	size_t N;
	std::cin >> N;

	std::vector<std::pair<T, std::set<T>>> ret{};

	while (N--) {
		T c, cc;
		std::string input;
		std::set<T> tmp{};

		std::getline((std::cin >> c), input);

		std::stringstream ss{ input };
		while (ss >> cc) tmp.emplace(cc);

		tmp.emplace(c);
		ret.emplace_back(std::make_pair(c, tmp));
	}

	return ret;
}

template <typename T>
auto readExpenses() {
	std::vector<T> cost{};
	size_t C{};

	std::cin >> C;

	while (C--) {
		std::string color{};
		int price{};

		std::cin >> color >> price;
		cost.emplace_back(price);
	}

	std::sort(begin(cost), end(cost));
	return cost;
}

template <typename C, typename T>
auto color(std::vector<std::pair<T, std::set<T>>>&& g) {							// Unfortunate type dependency between color and read
	using namespace std;

	// Sort the graph in order of vertex degree
	sort(begin(g), end(g), [](auto& p1, auto& p2) { return p1.second.size() > p2.second.size(); });

	// Create the set of all vertices
	set<T> vertices{};
	transform(begin(g), end(g), inserter(vertices, begin(vertices)), [](auto& p) { return p.first; });

	// Initialize algorithm variables
	map<T, C> color{};
	int curr_color{};
	auto x = begin(g);

	// Color the graph
	while (x != end(g)) {
		color[x->first] = ++curr_color;

		// Get the set of non-neighbors of x
		vector<T> non_neighbors{};
		set_difference(begin(vertices), end(vertices), begin(x->second), end(x->second), back_inserter(non_neighbors));

		// Sort to match graph ordering (set's sorting is "nautral", ie. std::less<char>)
		sort(begin(non_neighbors), end(non_neighbors), [&g](const auto& t1, const auto& t2) {
			return std::find_if(std::find_if(begin(g), end(g), [&t1](auto& p) { return p.first == t1; }), end(g), [&t2](auto& p) { return p.first == t2; }) != end(g);
		});

		// Try to color vertices the same as x
		auto y = begin(non_neighbors);
		while (true) {

			// Find a neighbor that won't violate Graph Coloring
			y = find_if(y, end(non_neighbors),
				[&color, &g, curr_color](auto& p1) {
				if (color[p1]) return false;

				auto neighbors = find_if(begin(g), end(g), [&p1](auto& p) { return p.first == p1; });
				for (auto n : neighbors->second)
					if (color[n] == curr_color)
						return false;

				return true;
			});

			if (y == end(non_neighbors)) break;
			color[*y] = curr_color;
		}

		x = find_if(x, end(g), [&color](auto& p1) { return !color[p1.first]; });
	}

	return color;
}

template <class Graph, class Vec>
int write(std::string& name, int paid, const Vec& v, Graph&& color) {
	std::vector<int> num(v.size());
	std::replace(begin(name), end(name), '-', ' ');

	// Count the number of each color
	for (auto node : color) num[node.second]++;

	// Match the most frequent color to the cheapest paint
	std::sort(begin(num), end(num), [](auto& n1, auto& n2) { return n1 > n2; });

	// Determine the cost of the painting
	int cost{}, i{};
	do {
		cost += num[i] * v[i];
	} while (num[++i]);

	std::cout << name << ": " << (paid > cost ? "profit" : paid < cost ? "loss" : "even") << "\n";
	return paid - cost;
}

//#include <chrono>			// For timing testing only
int main(int argc, const char* argv[]) {
	//auto start = std::chrono::steady_clock::now();
	using d_type = char;							// d_type = type of read data

	int N{};
	auto cost = readExpenses<int>();

	while (std::cin >> N) {
		std::string name{};
		int profit{}, price{};

		while (N--) {
			std::cin >> name >> price;
			profit += write(name, price, cost, color<int>(read<d_type>()));
		}
		
		std::cout << "Profit: " << (profit >= 0 ? "+" : "") << profit << "\n";
	}
	
	//std::cout << "Execution Time: " << std::chrono::duration<double>(std::chrono::steady_clock::now() - start).count() << "\n";
	//_sleep(10000);
}
