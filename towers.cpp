#include <utility>
#include <array>
#include <algorithm>
#include <stdio.h>

using namespace std;

template <typename Container, typename Pred>
auto sort(Container& c, Pred&& fn) {
	sort(begin(c), end(c), fn);
}

template <typename Container>
auto sort(Container& c) {
	sort(begin(c), end(c));
}

int tw_main(int argc, const char* argv[]) {
	int b1, b2, b3, b4, b5, b6;
	int s1, s2;

	scanf("%d %d %d %d %d %d %d %d",
		&b1, &b2, &b3, &b4, &b5, &b6, &s1, &s2);

	// Enumerate all possible combinations
	array<pair<array<int, 3>, array<int, 3>>, 10> combs = { {
		{ { b1, b2, b3 }, { b4, b5, b6 } },
		{ { b1, b2, b4 }, { b3, b5, b6 } },
		{ { b1, b2, b5 }, { b3, b4, b6 } },
		{ { b1, b2, b6 }, { b3, b4, b5 } },
		{ { b1, b3, b4 }, { b2, b5, b6 } },
		{ { b1, b3, b5 }, { b2, b4, b6 } },
		{ { b1, b3, b6 }, { b2, b4, b5 } },
		{ { b1, b4, b5 }, { b2, b3, b6 } },
		{ { b1, b4, b6 }, { b2, b3, b5 } },
		{ { b1, b5, b6 }, { b2, b3, b4 } }
	} };

	// Enumerate all possible sums (first = index of linked combination)
	array<pair<int, pair<int, int>>, 10> sums = { {
		{ 0, { b1 + b2 + b3, b4 + b5 + b6 } },
		{ 1, { b1 + b2 + b4, b3 + b5 + b6 } },
		{ 2, { b1 + b2 + b5, b3 + b4 + b6 } },
		{ 3, { b1 + b2 + b6, b3 + b4 + b5 } },
		{ 4, { b1 + b3 + b4, b2 + b5 + b6 } },
		{ 5, { b1 + b3 + b5, b2 + b4 + b6 } },
		{ 6, { b1 + b3 + b6, b2 + b4 + b5 } },
		{ 7, { b1 + b4 + b5, b2 + b3 + b6 } },
		{ 8, { b1 + b4 + b6, b2 + b3 + b5 } },
		{ 9, { b1 + b5 + b6, b2 + b3 + b4 } },
	} };

	// Sort the sums so that sums[0] is the correct answer
	sort(sums, [s1, s2](pair<int, pair<int, int>> h, pair<int, pair<int, int>> _) {
		return (h.second.first == s1 && h.second.second == s2) || (h.second.first == s2 && h.second.second == s1);
	});

	// Sort the correct combination in descending order ([2] < [1] < [0])
	int idx = sums[0].first;
	sort(combs[idx].first);
	sort(combs[idx].second);

	// If sums[0].second == { s1, s2 }
	if (sums[0].second.first == s1)
		printf("%d %d %d %d %d %d\n", combs[idx].first[2], combs[idx].first[1], combs[idx].first[0], combs[idx].second[2], combs[idx].second[1], combs[idx].second[0]);

	else
		printf("%d %d %d %d %d %d\n", combs[idx].second[2], combs[idx].second[1], combs[idx].second[0], combs[idx].first[2], combs[idx].first[1], combs[idx].first[0]);

	return 0;
}