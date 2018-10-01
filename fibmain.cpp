#include <cstdlib>
#include <iostream>
#include "bigint/bigint.h"
#include "fib.h"

int main(int argc, char *argv[]) {
	if (argc != 2) {
		std::cerr << "Please provide a number." << std::endl;
		exit(1);
	}
	int n = atoi(argv[1]);
	bigint b = fib(n);
	std::cout << b << std::endl;
}