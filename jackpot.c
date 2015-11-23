#include <math.h>
#include <stdio.h>

static const long MAX_PERIOD = 1000000000;
#define ABS(x) (x) < 0 ? -(x) : (x)

long gcd(long a, long b) {
	if (!a) return b;
	return gcd(b % a, a);
}

long lcm(long a, long b) {
	return ABS(a * b) / gcd(b, a);
}

int j_main(int argc, const char* argv[]) {
	int n;
	scanf("%d", &n);
	char line[1024];

	while (n--) {
		long w, period = 1;
		scanf("%ld", &w);

		while (w--) {
			int b;
			scanf("%d", &b);

			if (period <= MAX_PERIOD)
				period = lcm(period, b);

			else {
				scanf("%[^\n]", line);			// Read the rest of the line
				break;
			}
		}

		if (period <= MAX_PERIOD)
			printf("%ld\n", period);

		else
			printf("More than a billion.\n");
	}

	return 0;
}