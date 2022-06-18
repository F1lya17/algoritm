/*Дан невзвешенный неориентированный граф. Найдите цикл минимальной длины
https://contest.yandex.ru/contest/36361/problems/2.1/
68013458*/

#include <iostream>
#include <vector>
#include <queue>
using namespace std;


int find_cycle(int N, vector<vector<int> > &adj) {
    int ans = 1e9;
    for (int i = 0; i < N; i++) {
        vector<int> dist(N, 1e9);
        vector<int> par(N);
        dist[i] = 0;
        queue<int> q;
        q.push(i);
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (int u : adj[x]) {
                if (dist[u] == 1e9) {
                    dist[u] = 1 + dist[x];
                    par[u] = x;
                    q.push(u);
                }
                else if (par[x] != u and par[u] != x)
                    ans = min(ans, dist[x] + dist[u] + 1);
            }
        }
    }
    return (ans == 1e9)? -1: ans;
}
int main()
{
    int N, M;
    cin >> N >> M;
    vector<vector<int> > adj(N);
    vector<int> marked(N, 0);
    vector<int> cycle;
    for (int i = 0; i < M; i++) {
        int vertex1, vertex2;
		cin >> vertex1 >> vertex2;
		adj[vertex1].push_back(vertex2);
		adj[vertex2].push_back(vertex1);
    }
    cout << find_cycle(N, adj);
    return 0;
}
