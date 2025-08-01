
// Sorted and searchin element of array:
#include <iostream>
#include <vector>
#include <algorithm> // For std::sort
#include <climits>  // For INT_MIN
using namespace std;
bool linear_search(const vector<int>& nums, int target) {
    for (int num : nums) {
        if (num == target) {
            return true;
        }
    }
    return false;
}
void second_largest(const vector<int>& nums) {
    if (nums.size() < 2) {
        cout << "Invalid Input: Array must have at least 2 elements\n";
        return;
    }
    int first = INT_MIN, second = INT_MIN;
    for (int num : nums) {
        if (num > first) {
            second = first;
            first = num;
        } else if (num > second && num != first) {
            second = num;
        }
    }
    if (second == INT_MIN) {
        cout << "No second largest element (all elements may be identical)\n";
    } else {
        cout << "Second largest element (search method): " << second << "\n";
    }
}
// Function to find the second largest element using sorting
void second_largest_sort(vector<int> nums) {
    if (nums.size() < 2) {
        cout << "Invalid Input: Array must have at least 2 elements\n";
        return;
    }

    sort(nums.begin(), nums.end(), greater<int>()); // Sort in descending order
    int first = nums[0];
    for (size_t i = 1; i < nums.size(); ++i) {
        if (nums[i] != first) {
            cout << "Second largest element (sort method): " << nums[i] << "\n";
            return;
        }
    }
    cout << "No second largest element (all elements may be identical)\n";
}

// Function to display the sorted array
void sorted_array(vector<int> nums) {
    if (nums.empty()) {
        cout << "Sorted array: []\n";
        return;
    }
    sort(nums.begin(), nums.end()); // Sort in ascending order
    cout << "Sorted array: ";
    for (int num : nums) {
        cout << num << " ";
    }
    cout << "\n";
}

int main() {
    vector<int> nums;
    int n;

    // Get array size
    cout << "Enter the number of elements (at least 1): ";
    cin >> n;

    if (n < 1) {
        cout << "Invalid input: Number of elements must be positive\n";
        return 1;
    }

    // Get array elements
    cout << "Enter " << n << " integers:\n";
    for (int i = 0; i < n; ++i) {
        int num;
        cin >> num;
        nums.push_back(num);
    }

    // Display original array
    cout << "Original array: ";
    for (int num : nums) {
        cout << num << " ";
    }
    cout << "\n";
    // Display sorted array
    sorted_array(nums);
    // Find second largest using both methods
    second_largest(nums);
    second_largest_sort(nums);
    char continue_search;
    do {
        int target;
        cout << "\nEnter a number to search in the array: ";
        cin >> target;
        if (linear_search(nums, target)) {
            cout << target << " found in the array\n";
        } else {
            cout << target << " not found in the array\n";
        }
        cout << "Do you want to search another number? (y/n): ";
        cin >> continue_search;
    } while (continue_search == 'y' || continue_search == 'Y');

    return 0;
}
