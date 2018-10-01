#include <cstdlib>
#include <iostream>
#include "fact.h"
#include "bigint/bigint.h"

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cerr << "Please provide a number." << std::endl;
		exit(1);
	}
	int n = atoi(argv[1]);
	bigint bn = n;
	double dn = (double)n;
	int x = factorial(n);
	std::cout << n << " factorial using ints is: " << x << std::endl;
	bigint b = factorial(bn);
	std::cout << n << " factorial using bigints is: " << b << std::endl;
	double d = factorial(dn);
	std::cout << n << " factorial using doubles is: " << d << std::endl;
}