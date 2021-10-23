/*Вывести разложение натурального числа n на простые множители. Простые множители должны быть упорядочены по возрастанию и разделены пробелами. 2 ≤ n ≤ 106.
54935566
https://contest.yandex.ru/contest/29212/problems/1_2/
*/

#include <iostream>

using namespace std;

int main() {
	int n;
	cin >> n;
	int count = 0;
	for (int i = 2; i <= n; i++) {
		for (int k = 2; k < i; k++) {
			if (i % k == 0) {
				count++;
				break;
			}
		}
		if (n % i == 0) {
			cout << i << " ";
			n /= i;
			if (n % i == 0) {
				i--;
			}
		}
	}
	return 0;
}
