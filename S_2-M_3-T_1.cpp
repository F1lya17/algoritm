/*Найдите все вхождения шаблона в строку. Длина шаблона – p, длина строки – n. Время O(n + p), доп. память – O(p).
p ≤ 30000, n ≤ 300000.
https://contest.yandex.ru/contest/37787/problems/
68779524*/

#include <iostream>
#include <vector>

using namespace std;


vector<int> z_function(string s) {
	int n = s.length();
	vector<int> z(n);
	int l = -1, r = -1;
	for (int i = 1; i < n; i++) {
		if (i <= r) {
			z[i] = min(r - i + 1, z[i - l]);
		}
		while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
			z[i]++;		    
		}
		if (i + z[i] - 1 > r) {
			l = i;
			r = i + z[i] - 1;
	    }   
	}
	return z;
}

void solve(string s, string pattern, vector<int> & z) {
    int left = 0, right = 0;
    for (int i = 0; i < s.length(); i++) {
        int k = max(0, min(right - i, z[i - left]));
        while (i + k < s.length() && pattern[k] == s[i + k] && k < pattern.length()) {
            k++;
        }
        if (i + k > right) {
            left = i;
            right = i + k;
        }
        if (k == pattern.length()) {
            cout << i << " ";
        }
    }
}

int main() {
    string pattern, s;
    cin >> pattern >> s;
    vector<int> z(s.length());
    z = z_function(pattern);
    solve(s, pattern, z);
    return 0;
}
