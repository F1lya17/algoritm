/*https://contest.yandex.ru/contest/30914/problems/4_2/
Дана последовательность целых чисел a1...an и натуральное число k, такое что для любых i, j: если j >= i + k, то a[i] <= a[j]. Требуется отсортировать последовательность. 
Последовательность может быть очень длинной. Время работы O(n * log(k)). Доп. память O(k). Использовать слияние.
59139063*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void merge_sort(int l, int r, vector<int> &a) {
	if (r != l + 1) {
		int mid = (l + r) / 2;
		merge_sort(l, mid, a);
		merge_sort(mid, r, a);
		vector <int> b;
		int index1 = l, index2 = mid;
		while(index1 < mid && index2 < r) {
			if (a[index1] < a[index2]) {
				b.push_back(a[index1]);
				index1++;
			}
			else {
				b.push_back(a[index2]);
				index2++;
			}
		}
		while (index1 < mid) {
			b.push_back(a[index1]);
			index1++;
		}
		while (index2 < r) {
			b.push_back(a[index2]);
			index2++;
		}
		for (int i = l; i < r; i++) {
			a[i] = b[i - l];
		}
	}
}
void sorting(int n, int k) {
	vector <int> arr;
	for (int i = 0; i < k; i++) {
		int x;
		cin >> x;
		arr.push_back(x);
	}
	int len2;
	for (int i = 0; i + k < n; i += k) {
		len2 = min(n - i - k, k);
		for (int j = 0; j < len2; j++) {
			int y;
			cin >> y;
			arr.push_back(y);
		}
		merge_sort(0, k + len2, arr);
		for (int i = 0; i < k; i++) {
			cout << arr[0] << ' ';
			arr.erase(arr.begin());
		}
	}
	for (auto i : arr) {
	cout << i << ' ';
	}
}
int main() {
	int n, k;
	cin >> n >> k;
	sorting(n, k);
	return 0;
}
