/*Дано невзвешенное дерево. Расстоянием между двумя вершинами будем называть количество ребер в пути, соединяющем эти две вершины. 
Для каждой вершины определите сумму расстояний до всех остальных вершин. Время работы должно быть O(n).
https://contest.yandex.ru/contest/35212/problems/5_2/
66254204*/

#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int child_count = 0;
    int depth = 0;
    int ans = 0;
    vector <int> childs;
};

void dfs(vector <Node>& graph, int cur) {
    for(int i = 0; i < graph[cur].childs.size(); i++)
    {
        graph[graph[cur].childs[i]].depth = graph[cur].depth + 1;
        dfs(graph, graph[cur].childs[i]);
        graph[cur].child_count += graph[graph[cur].childs[i]].child_count + 1;
    }
}
 
void sum(vector <Node>& graph, int cur, int n) {
    for(int i = 0; i < graph[cur].childs.size(); i++) {
        graph[graph[cur].childs[i]].ans = graph[cur].ans + n - 2 * (graph[graph[cur].childs[i]].child_count + 1);/*при переходе к сыну, расстояние увеличивается до всех вершин, 
        но уменьшается до детей этого сына и его самого, но т.к. мы его их сначала прибавили, то нужно вычесть их 2 раза*/
        sum(graph, graph[cur].childs[i], n);
    }
}
 
void Answer(vector <Node>& graph, int n) {
    dfs(graph, 0);
    graph[0].ans = 0;
    for(int i = 1; i < n; i++) {
        graph[0].ans += graph[i].depth;
    }
    sum(graph, 0, n);
}

int main()
{
    int n;
    cin >> n;
    vector <Node> graph(n);
    for (int i = 0; i < n - 1; i++) {
        int vertex1, vertex2;
        cin >> vertex1 >> vertex2;
        graph[min(vertex1, vertex2)].childs.push_back(max(vertex1, vertex2));
    }
    Answer(graph, n);
    for (auto vertex: graph) {
        cout << vertex.ans << endl;
    }
    return 0;
}
