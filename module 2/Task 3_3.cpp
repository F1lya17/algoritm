/*https://contest.yandex.ru/contest/30914/problems/3/
Даны неотрицательные целые числа n, k и массив целых чисел из диапазона [0..109] размера n.
Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k ∈[0..n-1] в отсортированном массиве.
Напишите нерекурсивный алгоритм.
Требования к дополнительной памяти: O(n).
Требуемое среднее время работы: O(n).
Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.
3_3. Реализуйте стратегию выбора опорного элемента “случайный элемент”. Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
58799359*/

#include <iostream>
#include <vector>
 
using namespace std;
 
 
int Partition(vector<int>& arr, int start, int end) {
    if(start == end) {
        return start;
    }
    int random = start + rand() % (end - start);
    int temprary = arr[random];
    arr[random] = arr[end];
    arr[end] = temprary;
    int pivot = arr[end];
    int i = start;
    for(int j = start; j < end; j++) {
        if(arr[j] <= pivot) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
        }
    }
    arr[end] = arr[i];
    arr[i] = pivot;
    return i;
}
 
int KStat(vector<int>& arr, int k, int start, int end) {
    while(true) {
        int pos = Partition(arr, start, end);
        if (pos < k) {
            start = pos + 1;
        } else if (pos > k) {
            end = pos - 1;
        } else {
            return arr[k];
        }
    }
}
 
int main()
{
    int n, k;
	cin >> n >> k;
	vector <int> a(n);
	for (int i = 0; i < n; i++) {
		cin >> a[i];
	}
    cout << KStat(a, k, 0, n - 1);
    return 0;
}
