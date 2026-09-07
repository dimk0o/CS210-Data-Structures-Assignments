#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>

using namespace std;

pair<int, int> twoSumBruteForce(const vector<int>& nums, int target) { // O(n^2) because of the nested loops

	for (int i = 0; i < nums.size() - 1; i++) {
		for (int j = i + 1; j < nums.size(); j++) { // start after i so I don't check the same pair twice
			if (nums[i] + nums[j] == target)
				return {i, j}; // return when I find the pair
		}
	}

	return {-1, -1};
}

pair<int, int> twoSumHash(const vector<int>& nums, int target) { // here should be O(n)
	unordered_map<int, int> seen; // stores number -> index

	for (int i = 0; i < nums.size(); i++) {
		int missing_num = target - nums[i]; // number that is missing to reach the target

		if (seen.find(missing_num) != seen.end())
			return {seen[missing_num], i}; // complement was already found

		seen[nums[i]] = i; // save current number and its index
	}

	return {-1, -1};
}

void test(const vector<int>& nums, int target) {
	pair<int, int> brute = twoSumBruteForce(nums, target);
	pair<int, int> hash = twoSumHash(nums, target);

	bool bruteValid = brute.first != -1 && // .first gets the first element of pair
	                  brute.second != -1 &&
	                  nums[brute.first] + nums[brute.second] == target;

	bool hashValid = hash.first != -1 &&
	                 hash.second != -1 &&
	                 nums[hash.first] + nums[hash.second] == target;

	cout << "Target: " << target << endl;

	cout << "Brute Force: "
	     << "indices (" << brute.first << ", " << brute.second << "), "
	     << "values (" << nums[brute.first] << ", " << nums[brute.second] << "), "
	     << "valid: " << (bruteValid ? "Yes" : "No") << endl;

	cout << "Hash Table: "
	     << "indices (" << hash.first << ", " << hash.second << "), "
	     << "values (" << nums[hash.first] << ", " << nums[hash.second] << "), "
	     << "valid: " << (hashValid ? "Yes" : "No") << endl;

	cout << "----------------------------------------" << endl;
}

int main() {
	test({15, 4, 18, 8, 19, 22, 24, 59, 59, 20, 18, 12, 36, 42, 9}, 24); // vector from assignment
	test({6, 14, 3, 21}, 20);
	test({10, 5, 13, 2}, 15);
	test({8, 8, 1, 20}, 16);
	test({-7, 12, 4, 9}, 5);

	return 0;
}