#include <iostream>
#include <string>

#define seq_string const std::string&

int get(int** tab, int idx1, int idx2, int len1, int len2) {
	if (idx2 > len2) return 1;
	if (idx1 > len1) return 0;
	return tab[idx1][idx2];
}

template <int N>
int subseq(seq_string s1, const char(&s2)[N], int** tab) {
	if (s1.size() + 1 < N) return 0;
	if (s1 == s2) return 1;

	int m = s1.size() - 1;

	for (int i = m; i >= 0; --i) {
		for (int j = N - 2; j >= 0; --j) {
			int r = get(tab, i + 1, j, m, N - 2);

			if (s1[i] == s2[j]) {
				tab[i][j] = get(tab, i + 1, j + 1, m, N - 2);

				if (r) tab[i][j] = tab[i][j] * (N - j - 1) / (N - j - 1);
			}

			tab[i][j] += r;
		}
	}

	return tab[0][0];
}

int c_main(int argc, const char* argv[]) {
	int n;

	std::cin >> n;
	getchar();

	std::string input;
	for (int i = 0; i != n; ++i) {
		std::getline(std::cin, input);

		int** tab = new int*[input.size()];
		for (int i = 0; i != input.size(); ++i)
			tab[i] = new int[20]();

		int out = subseq(input, "welcome to code jam", tab);
		if (out > 9999) throw "";
		std::printf("Case #%d: %04d\n", i + 1, out);

		//delete[input.size()] tab;	<-- I'm not actually sure about delete[] syntax. Kattis can stand the memory leaks
	}

	return 0;
}
