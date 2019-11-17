#include <string>
#include <iostream>

// Counts the number of inversions in an array of doubles
// nums: The array of numbers
// size: The size of the array
int easyInversionCount(double nums[], int size) {
	int sum = 0; // The number of inversions
	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			if (nums[i] > nums[j]) sum++;
		}
	}
	return sum;
}

// Merges two arrays of doubles
// l: The left index for the first
// m: The middle index for the first
// r: The right index for the second
int merge(double* Arr, int start, int mid, int end) {

	int sum = 0;
	// create a temp array
	double* temp = (double*)malloc(sizeof(double) * (end - start + 1));

	// crawlers for both intervals and for temp
	int i = start, j = mid + 1, k = 0;

	// traverse both arrays and in each iteration add smaller of both elements in temp 
	while (i <= mid && j <= end) {
		if (Arr[i] <= Arr[j]) {
			temp[k] = Arr[i];
			k += 1; i += 1;
		}
		else {
			sum++;
			temp[k] = Arr[j];
			k += 1; j += 1;
		}
	}

	// add elements left in the first interval
	while (i <= mid) {
		sum++;
		temp[k] = Arr[i];
		k += 1; i += 1;
	}

	// add elements left in the second interval 
	while (j <= end) {
		temp[k] = Arr[j];
		k += 1; j += 1;
	}

	// copy temp to original interval
	for (i = start; i <= end; i += 1) {
		Arr[i] = temp[i - start];
	}
	return sum;
}

// Counts the number of inversions in an array of doubles
// nums: The array of doubles
// left: The index of the left of the array
// right: The index of the right of the array
int fastInversionCount(double* nums, int left, int right) {
	int count = 0;
	if (left < right) {
		int middle = (left + right) / 2;
		count += fastInversionCount(nums, left, middle);
		count += fastInversionCount(nums, middle + 1, right);
		count += merge(nums, left, middle, right);
	}
	return count;
}

// Inverts a string
// in: The string to invert
std::string invertString(std::string in) {
	int length = in.length();
	char* out = (char*) malloc((length + 1) * sizeof(char));
	for (int i = 0; i < length; i++) {
		out[i] = in[length - i - 1];
	}
	out[length] = '\0';
	return out;
}

// Helper function for is Palindrome
// orig: Pointer to a charactr from the original string
// reverse: Pointer to a character from the reversed string
bool isPalindromeUtil(char* orig, char* reverse) {
	if (*orig == '\0' && *reverse == '\0') return true; // Base case
	if (tolower(*orig) == tolower(*reverse)) return isPalindromeUtil(orig + sizeof(char), reverse + sizeof(char));
	if (*orig == ' ' || std::ispunct(*orig)) return isPalindromeUtil(orig + sizeof(char), reverse);
	if (*reverse == ' ' || std::ispunct(*reverse)) return isPalindromeUtil(orig, reverse + sizeof(char));
	return false;
}

// Determines if a given string is a Palindrome
// in: The input string
bool isPalindrome(std::string in) {
	std::string reverse = invertString(in);
	return isPalindromeUtil(&in[0], &reverse[0]);
}

int main() {
	std::cout << isPalindrome("A man, a plan, a canal: Panama!");
	std::cout << "\n";
	double nums[6] = { 1, 3, 2, 4, 6, 5 };
	double nums2[5] = { 10, 9, 8, 11, 5 };
	double nums3[7] = { 38, 27, 43, 3, 9, 82, 10 };
	std::cout << easyInversionCount(nums3, 7) << "\n";
	std::cout << fastInversionCount(nums3, 0, 6) << "\n";
	for (int i = 0; i < 5; i++) {
		printf("%e ", nums2[i]);
	}
}

// First, write function that reverses string
// Then parse initial and final string to remove whitespace and capitalization
// Finally, compare the strings to see if they are equal