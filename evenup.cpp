#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

int eu_main(int argc, const char* argv[]) {
	int n, m;
	std::cin >> n >> m;

	std::vector<bool> trends = { true };
	bool trending_odd{ (bool)(m % 2) };
	bool start_odd{ trending_odd };

	// Create a list of the trends and whether they have a "free" card or not
	while (--n) {
		std::cin >> m;

		bool odd = m % 2;
		if (odd && !trending_odd) {
			trends.push_back(false);
			trending_odd = true;

		} else if (!odd && trending_odd) {
			trends.push_back(false);
			trending_odd = false;
		}

		trends.back() = !trends.back();
	}

	std::stack<bool> last{};
	bool curr_trend = start_odd;

	// Try to match adjacent "free" cards
	for (auto free_card : trends) {
		if (free_card) {
			if (!last.empty() && last.top() == curr_trend)
				last.pop();

			else
				last.push(curr_trend);
		}

		curr_trend = !curr_trend;
	}

	// Output number of unmatched "free" cards
	std::cout << last.size() << "\n";
	return 0;
}