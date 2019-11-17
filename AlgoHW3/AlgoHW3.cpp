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
int merge(double arr[], int l, int m, int r)
{
	int sum = 0;
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	double* L = (double*)malloc(sizeof(double) * n1);
	double* R = (double*)malloc(sizeof(double) * n2);

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		sum++;
		k++;
	}

	/* Copy the remaining elements of L[], if there
	   are any */
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	   are any */
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
	return sum;
}

// Counts the number of inversions in an array of doubles
// nums: The array of doubles
// left: The index of the left of the array
// right: The index of the right of the array
int fastInversionCount(double nums[], int left, int right) {
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
	std::cout << easyInversionCount(nums, 6) << "\n";
	std::cout << fastInversionCount(nums, 0, 5);
}

// First, write function that reverses string
// Then parse initial and final string to remove whitespace and capitalization
// Finally, compare the strings to see if they are equal