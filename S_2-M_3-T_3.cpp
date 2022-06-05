/*Строка называется палиндромом, если она одинаково читается как слева направо, так и справа налево. Например, «abba» – палиндром, а «roman» – нет.
Для заданной строки s длины n (1 ≤ n ≤ 105) требуется подсчитать число пар (i, j), 1 ≤ i < j ≤ n, таких что подстрока s[i..j] является палиндромом.
https://contest.yandex.ru/contest/37787/problems/3/
68578148*/

#include <iostream>
#include <vector>

using namespace std;


int main() {
    string s;
    long int answer = 0;
    cin >> s;
    int n = s.length();
    vector<int> d1(n), d2(n);
    int l = 0, r = -1;
    for (int i = 0; i < n; i++) {
        int k;
        if (i > r) {
            k = 1;
        }
        else {
            k = min(d1[l + r - i], r - i + 1);
        }
        while (i + k < n && i - k > -1 && s[i + k] == s[i - k]) {
            k++;
        }
        d1[i] = k;
    	answer += k - 1;
        if (i + k - 1 > r) {
            l = i - k + 1;
            r = i + k - 1;
        }
    }
    l = 0; r = -1;
    for (int i = 0; i < n; i++) {
        int k;
        if (i > r) {
            k = 0;
        }
        else {
            k = min(d2[l + r - i + 1], r - i + 1);
        }
        while (i + k < n && i - k - 1 > - 1 && s[i + k] == s[i - k - 1]) {
            k++;
        }
        d2[i] = k;
    	answer += k;
        if (i + k - 1 > r) {
            l = i - k;
            r = i + k - 1;
        }
    }
    cout << answer;
    return 0;
}
