/*В дощечке в один ряд вбиты гвоздики. Любые два гвоздика можно соединить ниточкой. 
Требуется соединить некоторые пары гвоздиков ниточками так, чтобы к каждому гвоздику была привязана хотя бы одна ниточка, а суммарная длина всех ниточек была минимальна.
https://contest.yandex.ru/contest/35212/problems/3_3/
65537791*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    int N;
    cin >> N;
    vector <int> coordinates(N);
    for (int i = 0; i < N; i++) {
        cin >> coordinates[i];   
    }
	sort(coordinates.begin(), coordinates.end());
    vector <int> dist(N + 1);
    dist[1] = 1e6;
    for (int i = 2; i <= N; i++) {
        dist[i] = min(dist[i - 1], dist[i - 2]) + (coordinates[i - 1] - coordinates[i - 2]);
    }
    cout << dist[N];
}
