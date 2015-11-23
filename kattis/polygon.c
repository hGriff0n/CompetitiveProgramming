#include <stdio.h>
#include <math.h>

int p_main(int argc, const char* argv[]) {
	int n;

	while (scanf("%d", &n) && n-- > 2) {
		int x0, y0;
		scanf("%d %d", &x0, &y0);

		int x1 = x0, x2, y1 = y0, y2;
		double a = 0;

		// A = |Sum(1->n, x[i]*y[i + 1] - x[i + 1] * y[i]) / 2.|
		while (n--) {
			scanf("%d %d", &x2, &y2);

			a += (x1 * y2 - x2 * y1);

			x1 = x2;
			y1 = y2;
		}

		a += (x1 * y0 - x0 * y1);
		printf("%s %.1f\n", a < 0 ? "CW" : "CCW", fabs(a / 2));
	}

	return 0;
}