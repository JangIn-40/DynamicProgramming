#include <iostream>
#include <map>
#include <string>
#include <chrono>
#include <vector>
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

// Time Complexity : O(2 * (m + n)) = O(m + n)
// Space Complexity : O(m + n)
int64_t FindWays_Memo(int m, int n, std::map<std::string, int64_t>& memo)
{
	const std::string key = std::to_string(m) + "," + std::to_string(n);

	if (memo.count(key) == 1)
	{
		return memo[key];
	}

	//const std::string rkey = std::to_string(n) + "," + std::to_string(m);
	//if (memo.count(rkey) == 1)
	//{
	//	return memo[rkey];
	//}

	// base case
	if (m <= 0 || n <= 0)
		return 0;
	if (m == 1 || n == 1)
		return 1;

	// recursive case;
	memo[key] = FindWays_Memo(m - 1, n, memo) + FindWays_Memo(m, n - 1, memo);
	return memo[key];
}

// m : sum, n : number.size()
// Time Complexity : O( 너비 ^ 높이 ) = O(n ^ m)
// Space Complexity : O(m)
bool CanAccumulation(int sum, std::vector<int> numbers)
{
	// base case
	if (sum == 0)
			return true;
	else if (sum < 0)
		return false;
	// recursive case
	else
		for (int i = 0; i < numbers.size(); ++i)
		{
			if(CanAccumulation(sum - numbers[i], numbers))
				return true;
		}
	return false;
}

// Time Complexity : O(
// Space Complexity : O(m)
bool CanAccumulation_Memo(int sum, std::vector<int> numbers, std::map<int, bool> &memo)
{
	if (memo.count(sum) == 1)
	{
		return memo[sum];
	}
	// base case
	if (sum == 0)
		return true;
	else if (sum < 0)
		return false;
	// recursive case
	else
		for (int i = 0; i < numbers.size(); ++i)
		{
			if (CanAccumulation_Memo(sum - numbers[i], numbers, memo))
			{
				memo[sum] = true;
				return memo[sum];
			}
		}

	memo[sum] = false;
	return false;
}

// Time Complexity : O(n ^ m) -> O(m * n)
// Space Complexity : O(m ^ 2) -> O(m ^ 2) 입출력 무시시 O(m)
using accum_memo = std::map<int, std::shared_ptr<std::vector<int>>>;
std::shared_ptr<std::vector<int>> HowAccumulation(int sum, std::vector<int> numbers, 
													accum_memo& memo)
{
	if (memo.count(sum) == 1)
	{
		return memo[sum];
	}

	if (sum == 0)
		return std::make_shared<std::vector<int>>();
	else if (sum < 0)
		return nullptr;
	
	for (auto &e : numbers)
	{
		auto ret = HowAccumulation(sum - e, numbers, memo);
		if (ret)
		{
			ret->push_back(e);
			memo[sum] = ret;
			return memo[sum];
		}
	}

	memo[sum] = nullptr;
	return memo[sum];
}

std::shared_ptr<std::vector<int>> OptimizeAccumulation(int sum, const std::vector<int> &numbers,
	accum_memo &memo)
{
	if (memo.count(sum) == 1)
	{
		return memo[sum];
	}

	// base case
	if (sum == 0)
	{
		return std::make_shared<std::vector<int>>();
	}
	else if (sum < 0)
	{
		return nullptr;
	}
	//recursive case
	else
	{
		std::shared_ptr<std::vector<int>> best = nullptr;
		for (auto &e : numbers)
		{
			auto ret = OptimizeAccumulation(sum - e, numbers, memo);
			if (ret != nullptr)
			{
				std::shared_ptr<std::vector<int>> temp = std::make_shared<std::vector<int>>();
				temp->resize(ret->size());
				std::copy(ret->begin(), ret->end(), temp->begin());
				temp->push_back(e);

				//ret->push_back(e);	
				if (best == nullptr || temp->size() < best->size())
				{
					best = temp;
				}
			}
			
		}

		memo[sum] = best;
		return memo[sum];
	}
}

void Print(std::shared_ptr<std::vector<int>> result)
{
	if (result)
	{
		std::cout << "{ ";
		for (const auto &e : *result)
		{
			std::cout << e << " ";
		}
		std::cout << " }" << std::endl;
	}
	else
	{
		std::cout << "nullptr" << std::endl;
	}
}

int main()
{
	//for (int i = 1; i < 50; ++i)
	//{
	//	std::map<int, int64_t> m;
	//	std::cout << Fibonacci_Memo(i, m) << " ";
	//}
	//std::cout << std::endl;

	//for (int i = 1; i < 5; ++i)
	//{
	//	std::cout << FindWays(i, i) << " ";
	//}

	//std::map<std::string, int64_t> memo;
	//std::cout << FindWays_Memo(30, 30, memo) << std::endl;

	//std::cout << std::boolalpha;
	//std::cout << CanAccumulation(8, { 3, 2, 5 });
	//std::cout << CanAccumulation(900, { 7, 14});

	//std::map<int, bool> memo;
	//std::cout << CanAccumulation_Memo(8, { 3, 2, 5 }, memo) << std::endl;;
	//memo.clear();
	//std::cout << CanAccumulation_Memo(900, { 7, 14 }, memo);

	//accum_memo m;
	//Print(HowAccumulation(8, { 2, 3, 5 }, m));
	//m.clear();
	//Print(HowAccumulation(8, { 5, 6 }, m));
	//m.clear();
	//Print(HowAccumulation(8, { 3, 5, 2 }, m));

	accum_memo m;
	Print(OptimizeAccumulation(8, { 2, 3, 5 }, m));
	m.clear();
	Print(OptimizeAccumulation(8, { 5, 6 }, m));
	m.clear();
	Print(OptimizeAccumulation(7, { 1, 3, 4, 5 }, m));
	m.clear();
	Print(OptimizeAccumulation(900, { 7, 14 }, m));

}