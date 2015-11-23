#include <stdio.h>

int n_main(int argc, const char* argv[]) {
	int T;
	scanf("%d", &T);

	for (; T--;) {
		// Load equation 1 into memory
		int n1;
		scanf("%d", &n1);
		int* eq1 = new int[n1++ + 1];
		for (int i = 0; i != n1; ++i)
			scanf("%d", eq1 + i);


		// Multiply equation 1 by equation 2
		int n, n2;
		scanf("%d", &n2);
		int* eq = new int[n = n2++ + n1]();

		for (int i = 0; i != n2; ++i) {
			int x;
			scanf("%d", &x);

			for (int j = 0; j != n1; ++j)
				eq[i + j] += (x * eq1[j]);
		}


		// Output the equation
		printf("%d\n", n - 1);
		for (int i = 0; i != n - 1; ++i)
			printf("%d ", eq[i]);

		printf("%d\n", eq[n - 1]);
	}

	return 0;
}