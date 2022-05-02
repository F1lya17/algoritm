/*Найти в связном графе остовное дерево минимального веса. Вариант 1 с помощью алгоритма Прима
https://contest.yandex.ru/contest/36361/problems/6/
67174143*/

#include <iostream>
#include <vector>
#include <set>

using namespace std;

int Prima(int N, vector <vector<pair<int, int> > >& ways) {
    vector <int> dist(N, 1e9);
    vector <bool> visited(N);
    dist[0] = 0;
    set<pair<int, int> > S;
    S.insert({0, 0});
    int min_sum_dist = 0;
    while (!S.empty()) {
        auto [distance, v] = *S.begin();
        min_sum_dist += distance;
        S.erase(S.begin());
        visited[v] = 1;
        for (auto [u, cost] : ways[v]) {
            if (dist[u] > cost && !visited[u]) {
                S.erase({dist[u], u});
                dist[u] = cost;
                S.insert({dist[u], u});
            }
        }
    }
    return min_sum_dist;
}


int main()
{
    int N, M;
    cin >> N >> M;
    vector <vector<pair<int, int> > > ways(N);
    for (int i = 0; i < M; i++) {
        int ver1, ver2, cost;
        cin >> ver1 >> ver2 >> cost;
        ver1--;
        ver2--;
        ways[ver1].push_back({ver2, cost});
        ways[ver2].push_back({ver1, cost});
    }
    cout << Prima(N, ways);
    return 0;
}
