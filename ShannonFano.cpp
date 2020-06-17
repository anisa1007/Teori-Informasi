#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>

using namespace std;

struct karakter {
	char x;
	int freq;
	string kode;
};

void ShannonFano(karakter *chars, int end, int start = 0, const string &cabang = "", const string &cabangpenuh = "") {
	string kode = cabangpenuh + cabang;

	
	if (start == end) {
		chars[start].kode = kode;
	    return;
	}

	int sum = 0; 
	for (int a = start; a <= end; a++)
	    sum += chars[a].freq;

	sum /= 2; 
	int i, sum2 = chars[start].freq;

	
	for (i = start + 1; abs(sum - (sum2 + chars[i].freq)) < abs(sum - sum2) && i < end; i++)
	    sum2 += chars[i].freq;

	ShannonFano(chars, i - 1, start, "0", kode);
	ShannonFano(chars, end, i, "1", kode);
}

int main() {
	string s;
	cout << "Input kata: ";
	getline(cin, s);

	karakter *chars = new karakter[s.length()]; 
	int size = 0; 

	for (int i = 0; i < s.length(); i++) {
		int j = 0;

		while (j < size && chars[j].x != s[i])
			j++;

	
		if (j == size) {
			chars[size].x = s[i];
			chars[size++].freq = 1;
		} else
			chars[j].freq++; 
	}

	bool isSorted = false;
	while (!isSorted) {
		isSorted = true;

		for (int i = 0; i < size - 1; i++) {
			if (chars[i].freq < chars[i + 1].freq) {
				karakter tmp = chars[i];
				chars[i] = chars[i + 1];
				chars[i + 1] = tmp;
				isSorted = false;
			}
		}
	}

	ShannonFano(chars, size - 1);

	cout << "+-------------------+" << endl;
	cout << "| c | frek |  kode  |" << endl;
	cout << "+---+------+--------+" << endl;
	for (int i = 0; i < size; i++)
		printf("| %c | %4d | %6s |\n", chars[i].x, chars[i].freq, chars[i].kode.c_str());
	cout << "+-------------------+" << endl;

	delete[] chars;
}
