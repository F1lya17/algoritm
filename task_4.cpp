/*Требуется отыскать самый короткий маршрут между городами. Из города может выходить дорога, которая возвращается в этот же город.
Требуемое время работы O((N + M)log N), где N – количество городов, M – известных дорог между ними.
N ≤ 10000, M ≤ 250000.
Длина каждой дороги ≤ 10000.
https://contest.yandex.ru/contest/36361/problems/4/
67763190*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int Dijkstra(int N, int city1, int city2, vector <vector<pair<int, int> > >& ways) {
    vector <int> sum_time(N, 1e9);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int> > > Q;
    Q.push({0, city1});
    sum_time[city1] = 0;
    while (!Q.empty()) {
        auto [t, u] = Q.top();
        Q.pop();
        for (auto [i, Time] : ways[u]) {
            if (sum_time[i] > t + Time) {
                sum_time[i] = t + Time;
                Q.push({sum_time[i], i});
            }
        }
    }
    return sum_time[city2];
}


int main()
{
    int N, M, city1, city2;
    cin >> N >> M;
    vector <vector<pair<int, int> > > ways(N);
    for (int i = 0; i < M; i++) {
        int town1, town2, Time;
        cin >> town1 >> town2 >> Time;
        ways[town1].push_back({town2, Time});
        ways[town2].push_back({town1, Time});
    }
    cin >> city1 >> city2;
    cout << Dijkstra(N, city1, city2,  ways);
    return 0;
}
