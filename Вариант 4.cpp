/*Дан отсортированный массив различных целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. Для каждого элемента массива B[i] найдите минимальный индекс элемента массива A[k], ближайшего по значению к B[i].

n ≤ 110000, m ≤ 1000.
54937005
https://contest.yandex.ru/contest/29212/problems/3_4/
*/

#include <iostream>

using namespace std;

int binarySearch(const int* A, int& n, int& element) {
    int l = 0, r = n, mid;
	while (l < r - 1) {
		mid = (l + r) / 2;
		if (A[mid] >= element) {
			r = mid;
		}
		else {
			l = mid;
		}
	}
	if (r == n) {
	    return n - 1;
	}
	else {
	    return r;
	}
}
int main() {
    int n, m, ans, index;
    cin >> n;
    int* A = new int[n];
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }
    cin >> m;
    int* B = new int[m];
    for (int i = 0; i < m; i++) {
        cin >> B[i];
    }
    for (int i = 0; i < m; i++) {
        index = binarySearch(A, n, B[i]);
        if (index == 0) {
            ans = index;
        }
        else if (A[index] - B[i] >= B[i] - A[index - 1]) {
            ans = index - 1;
        }
        else {
            ans = index;
        }
        cout << ans << " ";
    }
	delete[] A;
    delete[] B;
}
