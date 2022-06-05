/*Найти лексикографически-минимальную строку, построенную по префикс-функции, в алфавите a-z.
https://contest.yandex.ru/contest/37787/problems/2_1/
68777727*/


#include<iostream>
#include<vector>

using namespace std;


string pi_to_string(vector<int> & pi) {
    string result = "a";
    for (int i = 1; i < pi.size(); i++) {
        if (pi[i] != 0) {
            result += result[pi[i] - 1];
        } else {
            vector<bool> letters(26);
            int k = pi[i - 1];
            while (k > 0) {
                letters[result[k] - 'a'] = true;
                k = pi[k - 1];
            }
            char c = 'b';
            while (letters[c - 'a']){
                c++;
            };
            result += c;
        }
    }
    return result;
}


int main() {
    vector<int> pi;
    int item;
    while (cin >> item) {
        pi.push_back(item);
    }
    cout << pi_to_string(pi);
    return 0;
}
