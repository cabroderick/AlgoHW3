#include <string>
#include <iostream>
#include <vector>
using namespace std;

// Collin Broderick, Praise Eteng, Siddhant Banerjee

// Generats recursively the binary reflected Gray code of order n
// Input: A positive integer n
// Output: A list of all bit strings of length n composing the Gray code
vector<string> BRGC(int n) {
	if (n == 1) { // If the length is 0, the only possible bit strings are 0 and 1
		vector<string> L = { "0", "1" };
		return L;
	}
	else {
		vector<string> L1 = BRGC(n - 1);
		vector<string> L2 (L1.rbegin(), L1.rend());
		for (int i = 0; i < L1.size(); i++) {
			L1.at(i).insert(0, "0");
			L2.at(i).insert(0, "1");
		}
		vector<string> L;
		L.insert(L.end(), L1.begin(), L1.end());
		L.insert(L.end(), L2.begin(), L2.end());
		return L;
	}
}

void graycodesarefun() {
	vector<string> L = BRGC(4);
	for (int i = 1; i < L.size(); i++) {
		bool alice = false;
		bool bob = false;
		bool chris = false;
		bool dylan = false;
		if (L.at(i)[3] == '1') alice = true;
		if (L.at(i)[2] == '1') bob = true;
		if (L.at(i)[1] == '1') chris = true;
		if (L.at(i)[0] == '1') dylan = true;
		string name = ""; // The name of the person moving
		string action = ""; // In/Out
		int a = stoi(L.at(i), nullptr, 2); // Gets base 2 version of binary representation
		int b = stoi(L.at(i - 1), nullptr, 2);
		int diff = a - b; // Difference between successive list elements
		if (diff > 0) action = "In";
		else action = "Out";
		switch (abs(diff)) {
		case(1):
			name = "Alice";
			break;
		case(2):
			name = "Bob";
			break;
		case(4):
			name = "Chris";
			break;
		case(8):
			name = "Dylan";
			break;
		}
		cout << "Index: " << i << " Gray code: " << L.at(i) << " Children: ";
		if (alice) cout << "Alice ";
		if (bob) cout << "Bob ";
		if (chris) cout << "Chris ";
		if (dylan) cout << "Dylan ";
		cout << "Action: " << name << " " << action << "\n";
	}

}

// Counts the number of inversions in an array of ints
// arr: The array of numbers
// size: The size of the array
int easyinversioncount(int arr[], int size) {
	int sum = 0; // The number of inversions
	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			if (arr[i] > arr[j]) sum++;
		}
	}
	return sum;
}

// Merges two arrays and sorts them
// arr: The array of numbers
// temp: A temporary array to store arr
// left: The left index of the left array
// mid: The left index of the right array
// right: The right index of the right array
int merge(int arr[], int temp[], int left, int mid, int right) {
	int inversions = 0;
	int i = left;
	int j = mid;
	int k = left;
	while ((i <= mid - 1) && (j <= right)) {
		if (arr[i] <= arr[j]) {
			temp[k] = arr[i];
			k++; i++;
		}
		else {
			temp[k++] = arr[j++];
			inversions += (mid - i);
		}
	}

	while (i <= mid - 1) {
		temp[k++] = arr[i++];
	}

	while (j <= right) {
		temp[k++] = arr[j++];
	}

	for (i = left; i <= right; i++) {
		arr[i] = temp[i];
	}
	return inversions;
}

// Helper function for fastInversionCount
// arr: The array of numbers
// temp: A temporary array to store arr
// left: The left index of the array to look at
// right: The right index of the array to look at
int fastinversioncount_util(int arr[], int temp[], int left, int right)
{
	int inversions = 0;
	if (right > left) {
		int mid = (right + left) / 2;
		inversions = fastinversioncount_util(arr, temp, left, mid);
		inversions += fastinversioncount_util(arr, temp, mid + 1, right);
		inversions += merge(arr, temp, left, mid + 1, right);
	}
	return inversions;
}

// Counts the number of inversions in an array of ints
// arr: The array of numbers
// size: The size of the array
int fastinversioncount(int arr[], int size)
{
	int* temp = (int*) malloc(sizeof(int) * size);
	return fastinversioncount_util(arr, temp, 0, size - 1);
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
bool palindromecheckUtil(char* orig, char* reverse) {
	if (*orig == '\0' && *reverse == '\0') return true; // Base case
	if (tolower(*orig) == tolower(*reverse)) return palindromecheckUtil(orig + sizeof(char), reverse + sizeof(char));
	if (*orig == ' ' || std::ispunct(*orig)) return palindromecheckUtil(orig + sizeof(char), reverse);
	if (*reverse == ' ' || std::ispunct(*reverse)) return palindromecheckUtil(orig, reverse + sizeof(char));
	return false;
}

// Determines if a given string is a Palindrome
// in: The input string
bool palindromecheck(std::string in) {
	std::string reverse = invertString(in);
	return palindromecheckUtil(&in[0], &reverse[0]);
}

int main() {
	std::cout << palindromecheck("A man, a plan, a canal: Panama!");
	std::cout << "\n";
	int nums[6] = { 1, 3, 2, 4, 6, 5 };
	int nums2[5] = { 10, 9, 8, 11, 5 };
	int nums3[7] = { 38, 27, 43, 3, 9, 82, 10 };
	//std::cout << easyInversionCount(nums2, 5) << "\n";
	std::cout << fastinversioncount(nums2, 5) << "\n";
	std::vector<std::string> arr = BRGC(4);
	for (int i = 0; i < arr.size(); i++) {
		cout << arr.at(i) << " ";
	}
	cout << "\n";
	graycodesarefun();
}