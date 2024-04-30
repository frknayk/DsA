#include <iostream>
#include <vector>

using namespace std;

// Function to find the maximum element in a vector using divide and conquer
int findMax(const vector<int>& arr, int left, int right) {
    if (left == right) // Base case: Only one element
        return arr[left];

    // Divide the array into two halves
    int mid = left + (right - left) / 2;

    // Recursively find the maximum elements in the two halves
    int maxLeft = findMax(arr, left, mid);
    int maxRight = findMax(arr, mid + 1, right);

    // Combine the results to find the maximum element
    return max(maxLeft, maxRight);
}

int main() {
    // Example usage
    vector<int> arr = {3, 8, 1, 9, 4, 5, 7, 2};
    int n = arr.size();

    int maxElement = findMax(arr, 0, n - 1);
    cout << "Maximum element in the array: " << maxElement << endl;

    return 0;
}
