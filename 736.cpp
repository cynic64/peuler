#include <vector>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <unordered_map>
#include <cstdint>

// Returns 0 for no path to equality from p of length n, or the final
uint64_t paths_to_equality(uint64_t a, uint64_t b, int n);

int main() {
	for (auto n = 1; n < 20 ; n += 1) {
		printf("%d\n", n);

		auto x = paths_to_equality(46, 180, n);
		if (x) printf("Final: %lu\n", x);
	}
}

inline uint64_t key(uint64_t a, uint64_t b) {
	return (uint64_t) a << 32 | b;
}

uint64_t paths_to_equality(uint64_t a, uint64_t b, int n) {
	if (a > 8000000000000000000 || b > 8000000000000000000) printf("big!\n");
	uint64_t ans;
	if (n < 1) return 0;
	if (a == b && n != 1) return 0;
	if (a == b && n == 1) return a;

	auto rr = 0, rs = 0, sr = 0, ss = 0;

	// No point doing any r's if b > 2^(n+1)a
	if (b < (2 << (n+1)) * a) {
		rr = paths_to_equality(a+2, 4*b, n-1);
		rs = paths_to_equality(2*a+1, 2*b+2, n-1);
	}

	if (a < (2 << (n+1)) * b) {
		sr = paths_to_equality(2*a+2, 2*b+1, n-1);
		ss = paths_to_equality(4*a, b+2, n-1);
	}

	return std::max({rr, rs, sr, ss});
}
