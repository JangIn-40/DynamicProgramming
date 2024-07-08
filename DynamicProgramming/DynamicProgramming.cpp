#include <iostream>
#include <map>

// Time Complexity : O(2^n)
// Space Complexity : O(n)
long long Fibonacci(int n)
{
	//base case
	if (n <= 2)
	{
		return 1;
	}

	// recursive case
	return Fibonacci(n - 1) + Fibonacci(n - 2);
}

// Time Complexity : O(n)
// Space Complexity : O(n + n) = O(n)
int64_t Fibonacci_Memo(int n, std::map<int, int64_t>& memo)
{
	if (memo.count(n) == 1)
	{
		return memo[n];
	}

	if (n <= 2)
	{
		return 1;
	}

	memo[n] = Fibonacci_Memo(n - 1, memo) + Fibonacci_Memo(n - 2, memo);
	return memo[n];
}

// Time Complexity : O(2 ^ (m + n))
// Space Complexity : O(m + n)
int64_t FindWays(int m, int n)
{
	// base case
	if (m <= 0 || n <= 0)
		return 0;
	if (m == 1 || n == 1)
		return 1;

	// recursive case;
	return FindWays(m - 1, n) + FindWays(m, n - 1);
}

int main()
{
	//for (int i = 1; i < 50; ++i)
	//{
	//	std::map<int, int64_t> m;
	//	std::cout << Fibonacci_Memo(i, m) << " ";
	//}
	//std::cout << std::endl;

	for (int i = 1; i < 5; ++i)
	{
		std::cout << FindWays(i, i) << " ";
	}
}