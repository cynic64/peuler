#include <vector>
#include <iostream>
#include <stdexcept>

struct Point {
	int a;
	int b;

	Point r() {
		return {a+1, 2*b};
	}
	
	Point s() {
		return {2*a, b+1};
	}
};

typedef std::vector<Point> Path;

// Returns all path to equality of length n
std::vector<Path> paths_to_equality(Point p, int n);

int main() {
	for (auto n = 1; ; n += 2) {
		printf("%d\n", n);
		auto paths = paths_to_equality({45, 90}, n);
		if (paths.size()) {
			for (auto path : paths) {
				for (auto point : path) printf("(%d, %d) ", point.a, point.b);
				printf("\n");
			}
			break;
		}
	}
}

std::vector<Path> paths_to_equality(Point p, int n) {
	if (n < 1) return {};
	if (p.a == p.b && n != 1) return {};
	if (p.a == p.b && n == 1) return {{p}};

	auto sub_paths = paths_to_equality(p.r(), n-1);
	auto s_paths = paths_to_equality(p.s(), n-1);
	sub_paths.insert(sub_paths.end(), s_paths.begin(), s_paths.end());

	std::vector<Path> out;
	for (auto path : sub_paths) {
		path.insert(path.begin(), p);
		out.push_back(path);
	}

	return out;
}
