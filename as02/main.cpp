#include <iostream>
#include <vector>
using namespace std;

int iterativeBinarySearch(const vector<int>& arr, int target, int& comparisons) {
    int lo = 0; // low bound
    int hi = arr.size() - 1; //high bound
    comparisons = 0; // init comp counter

    while (lo <= hi) {
        int mid = lo + (hi - lo) / 2;
        comparisons++;

        if (arr[mid] == target)
            return mid;

        if (arr[mid] < target)
            lo = mid + 1;
        else
            hi = mid - 1;
    }

    return -1;
}

int recursiveBinarySearch(const vector<int>& arr, int target,
                          int lo, int hi, int& comparisons) {
    if (lo > hi) // base case 
        return -1;

    int mid = lo + (hi - lo) / 2;
    comparisons++;

    if (arr[mid] == target) // also a base case
        return mid;

    if (arr[mid] < target)
        return recursiveBinarySearch(arr, target, mid + 1, hi, comparisons); // recursive case

    return recursiveBinarySearch(arr, target, lo, mid - 1, comparisons); // also recursive case 
}

int linearSearch(const vector<int>& arr, int target, int& comparisons) {
    comparisons = 0;

    for (int i = 0; i < arr.size(); i++) {
        comparisons++;

        if (arr[i] == target)
            return i;
    }

    return -1;
}

void testFunc(const vector<int>& arr, int target) {
    int comparisons = 0;
    int index;

    cout << "Target: " << target << "\n";

    index = iterativeBinarySearch(arr, target, comparisons);
    cout << "Iterative: index = " << index
         << ", comparisons = " << comparisons << "\n";

    comparisons = 0;
    index = recursiveBinarySearch(arr, target, 0, arr.size() - 1, comparisons);
    cout << "Recursive: index = " << index
         << ", comparisons = " << comparisons << "\n";

    index = linearSearch(arr, target, comparisons);
    cout << "Linear: index = " << index
         << ", comparisons = " << comparisons << "\n\n";
}

int main() {
    vector<int> arr = {3, 7, 11, 18, 24, 31, 42, 56, 63, 75, 88, 91, 104, 120, 135};

    testFunc(arr, 3);
    testFunc(arr, 135);
    testFunc(arr, 56);
    testFunc(arr, -5); // testing how many steps the algorithm will do if the number doesn't exist in vector


    return 0;
}