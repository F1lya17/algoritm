/*Дана строка длины n. Найти количество ее различных подстрок. Используйте суффиксный массив.
Построение суффиксного массива выполняйте за O(n log n). Вычисление количества различных подстрок выполняйте за O(n).
https://contest.yandex.ru/contest/37787/problems/5/
68806128*/

#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
 
using namespace std;
const int N = 2e5;
 
int order[N], now_suff_add, n;
 
int get_order(int pos) {
    if (pos < n) {
        return order[pos];
    }
    return -1;
}
 
bool comp(pair<int, int> a, pair<int, int> b) {
    if (a.first != b.first) {
        return a.first < b.first;
    }
    return get_order(a.second + now_suff_add) < get_order(b.second + now_suff_add);
}
 
int solve(string s) {
    n = s.length();
    int cnt[26];
    for (int i = 0; i < 26; i++) {
        cnt[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        cnt[s[i] - 'a']++;
    }
    for (int i = 1; i < 26; i++) {
        cnt[i] += cnt[i - 1];
    }
    vector<pair<int, int> > suf;
    for (int i = 0; i < n; i++) {
        order[i] = cnt[s[i] - 'a'] - 1;
        suf.push_back({order[i], i});
    }
    sort(suf.begin(), suf.end(), comp);
    now_suff_add = 1;
    while (now_suff_add <= n) {
        sort(suf.begin(), suf.end(), comp);
        for (int i = suf.size() - 2; i >= 0; i--) {
            if (get_order(suf[i].second + now_suff_add) < get_order(suf[i + 1].second + now_suff_add)) {
                suf[i].first = i;
            }
            else {
                suf[i].first = min(suf[i + 1].first, suf[i].first);
            }
        }
        for (auto [order_suf, suf_num] : suf) {
            order[suf_num] = order_suf;
        }
        now_suff_add += now_suff_add;
    }
    /*for (auto [order_suf, suf_num] : suf) {
        cout << order_suf << " " << suf_num << endl;
    }*/
    vector<int> LCP(n);
    vector<int> revOrder(n);
    for (int i = 0; i < n; i++) {
		revOrder[suf[i].second] = i;
    }
	int current = 0;
	for (int i = 0; i < n; i++) {
		int p = revOrder[i];
		if (p == n - 1) {
			current = 0;
			continue;
		}
		int q = suf[p + 1].second;
		current--;
		if (current < 0) {
		    current = 0;
		}
		while (i + current < n && q + current < n && s[i + current] == s[q + current]) {
			current++;
		}
		LCP[p] = current;
	}
	int answer = 0;
	for (int i = 0; i < n; i++) {
	    answer += n - suf[i].second - LCP[i];
	}
	return answer;
}
 
int main()
{
    string s;
    cin >> s;
    cout << solve(s);
    return 0;
}
