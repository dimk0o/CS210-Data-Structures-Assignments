#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <iomanip>
using namespace std;

bool isSorted(const vector<int>& values) {
    for (int i = 1; i < values.size(); i++) {
        if (values[i - 1] > values[i])
            return false;
    }

    return true;
}

void bubbleSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;

        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                swapped = true;
            }
        }

        if (!swapped)
            break;
    }
}

void selectionSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }

        if (minIndex != i) {
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

void insertionSort(vector<int>& arr) {
    for (int i = 1; i < arr.size(); i++) {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = key;
    }
}

int partition(vector<int>& arr, int lo, int hi) {
    int pivot = arr[hi];
    int i = lo - 1;

    for (int j = lo; j < hi; j++) {
        if (arr[j] <= pivot) {
            i++;

            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[hi];
    arr[hi] = temp;

    return i + 1;
}

void quickSortRecursive(vector<int>& arr, int lo, int hi) {
    if (lo >= hi)
        return;

    int pivotIndex = partition(arr, lo, hi);

    quickSortRecursive(arr, lo, pivotIndex - 1);
    quickSortRecursive(arr, pivotIndex + 1, hi);
}

void quickSort(vector<int>& arr) {
    if (!arr.empty())
        quickSortRecursive(arr, 0, arr.size() - 1);
}

vector<int> randomInput(int size) {
    vector<int> arr;
    mt19937 generator(42 + size);
    uniform_int_distribution<int> distribution(0, size * 10);

    for (int i = 0; i < size; i++)
        arr.push_back(distribution(generator));

    return arr;
}

vector<int> sortedInput(int size) {
    vector<int> arr;

    for (int i = 0; i < size; i++)
        arr.push_back(i);

    return arr;
}

vector<int> reverseInput(int size) {
    vector<int> arr;

    for (int i = size; i > 0; i--)
        arr.push_back(i);

    return arr;
}

double benchmark(const vector<int>& original,
                 void (*sortFunction)(vector<int>&)) {
    vector<int> arr = original;

    auto start = chrono::high_resolution_clock::now();

    sortFunction(arr);

    auto end = chrono::high_resolution_clock::now();

    if (!isSorted(arr)) {
        cout << "ERROR: sort failed\n";
        return -1;
    }

    return chrono::duration<double, milli>(end - start).count();
}

void runBenchmarks(int size, const char* inputType,
                   const vector<int>& arr) {
    cout << left
         << setw(8) << size
         << setw(12) << inputType
         << setw(14) << benchmark(arr, bubbleSort)
         << setw(14) << benchmark(arr, selectionSort)
         << setw(14) << benchmark(arr, insertionSort)
         << setw(14) << benchmark(arr, quickSort)
         << "\n";
}

int main() {
    int sizes[] = {1000, 3000, 5000};

    cout << fixed << setprecision(3);

    cout << left
         << setw(8) << "Size"
         << setw(12) << "Input"
         << setw(14) << "Bubble"
         << setw(14) << "Selection"
         << setw(14) << "Insertion"
         << setw(14) << "Quick"
         << "\n";

    for (int size : sizes) {
        vector<int> random = randomInput(size);
        vector<int> sorted = sortedInput(size);
        vector<int> reversed = reverseInput(size);

        runBenchmarks(size, "Random", random);
        runBenchmarks(size, "Sorted", sorted);
        runBenchmarks(size, "Reverse", reversed);
    }

    return 0;
}