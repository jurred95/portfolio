#include <unordered_map>
#include "bigint/bigint.h"

bigint r_fib(int n,std::unordered_map <int, bigint> &memo){
//checking to see if its of fib 0 or 1 and return base case values
	if(n == 0 || n == 1){
		return n;
	}else{
		//check the begining of the map to the end of the map to see if fib value is
		//already in memoized map 
		if(memo.find(n) == memo.end())
			memo[n] = r_fib(n-1, memo) + r_fib(n-2, memo);
		return memo[n];
	}
}


bigint fib(int n) {
	std::unordered_map<int, bigint> memo;
	return r_fib(n, memo);
}
