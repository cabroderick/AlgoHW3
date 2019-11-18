#include <string>
#include <iostream>

// Generats recursively the binary reflected Gray code of order n
// Input: A positive integer n
// Output: A list of all bit strings of length n composing the Gray code
std::string* BRGC(int n) {
	if (n == 1) { // If the length is 0, the only possible bit strings are 0 and 1
		std::string L[2] = { "0", "1" };
		return &L[0];
	}
	else {
		std::string* L1 = BRGC(n - 1);
		int size = pow(2, n); // The size of arrays L1 and L2
		std::string* L2 = (std::string*) malloc(sizeof(std::string*) * size);
		for (int i = 0; i < size; i++) {
			L2[size - i - 1] = L1[i];
			L1[i].append("0");
			L2[size - i - 1].append("1");
		}
		std::string* L = (std::string*) malloc(sizeof(std::string*) * (size * 2));
		for (int i = 0; i < size * 2; i++) { // Appends both arrays into new array
			if (i < size) { // Array L1
				L[i] = L1[i];
			}
			else { // Array L2
				L[i] = L2[i - size];
			}
		}
		free(L1);
		free(L2);
		return L;
	}
}

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
			temp[k] = Arr[j];
			sum = sum + (mid - i); // Index sum counter
			// NEW LINE RIGHT HERE
			k += 1; j += 1;
			
		}
	}

	// add elements left in the first interval
	while (i <= mid) {
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
		count += merge(nums, left, middle + 1, right);
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
	std::cout << easyInversionCount(nums2, 5) << "\n";
	std::cout << fastInversionCount(nums2, 0, 4) << "\n";
	//std::string* arr = BRGC(5);
}

// First, write function that reverses string
// Then parse initial and final string to remove whitespace and capitalization
// Finally, compare the strings to see if they are equal