/* Даны два массива целых чисел одинаковой длины A[0..n-1] и B[0..n-1]. Необходимо найти первую пару индексов i0 и j0, , такую что A[i0] + B[j0] = max {A[i] + B[j], где 0 <= i < n, 0 <= j < n, i <= j}.

Время работы - O(n). n ≤ 100000.
54935432
https://contest.yandex.ru/contest/29212/problems/2_1/
*/

#include <iostream>

using namespace std;

int main() {
	int n, iA = 0, iB = 0;
    cin >> n;
    int *A = new int[n];
    int *B = new int[n];
    for (int i = 0; i < n; i++){
        cin >> A[i];
    }
    for (int i = 0; i < n; i++){
        cin >> B[i];
    }
    int mx = A[0];
    int Sum = A[0] + B[0];
    int max_index = 0;
    for (int i = 0; i < n; i++){
        if (A[i] > mx){
            mx = A[i];
            max_index = i;
        }
        if (mx + B[i] > Sum){
            iA = max_index;
            iB = i;
            Sum = mx + B[i];
        }
    }
    cout << iA << " " << iB;
    delete[] A;
    delete[] B;
    return 0;
}
