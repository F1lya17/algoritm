/*Дан ориентированный граф. Определите, какое минимальное число ребер необходимо добавить, чтобы граф стал сильносвязным. В графе возможны петли.
https://contest.yandex.ru/contest/36361/problems/3/
68014399/*

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


void topological_sort(int u, vector<int> &top_sort, vector<bool> &visited, vector<vector<int> > &g) {
    visited[u] = true;
    for (auto to : g[u]) {
        if (!visited[to]) {
            topological_sort(to, top_sort, visited, g);
        }
    }
    top_sort.push_back(u);
}
 

void dfs(int u, vector<int> &component, vector<bool> &marked, vector<int> &belong_to_component, int &component_id, vector<vector<int> > &gr) {
    component.push_back(u);
    belong_to_component[u] = component_id;
    marked[u] = 1;
    for (auto to : gr[u]) {
        if (!marked[to]) {
            dfs(to, component, marked, belong_to_component, component_id, gr);
        }
    }
}
 
int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<int> > g(n), gr(n);
    vector<int> top_sort;
    vector<bool> visited(n), marked(n);
    vector<int> belong_to_component(n);
    int component_id = 0;
    vector<int> component;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
    	if (a == b) {
    		continue;
        }
        a--;
        b--;
        g[a].push_back(b);
        gr[b].push_back(a);
    }
    for (int i = 0; i < n; i++) {
        if (!visited[i]){
            topological_sort(i, top_sort, visited, g);
        }
    }
    reverse(top_sort.begin(), top_sort.end());
    for (auto i : top_sort) {
        if (!marked[i]) {
            dfs(i, component, marked, belong_to_component, component_id, gr);
            component.clear();
            component_id++;
        }
    }
    vector<pair<bool, bool> > v(component_id);
    for (int i = 0; i < n; i++) {
        for (auto ver : g[i]) {
            if (belong_to_component[i] != belong_to_component[ver]) {
                v[belong_to_component[i]].first = true;
                v[belong_to_component[ver]].second = true;
            }
        }
    }
    int k1 = 0, k2 = 0;
    if (v.size() > 1) {
        for (auto i : v) {
            if (!i.first) {
                k1++;
            }
            if (!i.second) {
                k2++;
            }
        }
    }
    cout << max(k1, k2);
    return 0;
}
