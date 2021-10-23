/*Для сложения чисел используется старый компьютер. Время, затрачиваемое на нахождение суммы двух чисел равно их сумме. Таким образом для нахождения суммы чисел 1,2,3 может потребоваться разное время, в зависимости от порядка вычислений. ((1+2)+3) -> 1+2 + 3+3 = 9 ((1+3)+2) -> 1+3 + 4+2 = 10 ((2+3)+1) -> 2+3 + 5+1 = 11 Требуется написать программу, которая определяет минимальное время, достаточное для вычисления суммы заданного набора чисел. Требуемое время работы O(n*log(n)).
54525177
https://contest.yandex.ru/contest/29212/problems/6_2/
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main()
{
    priority_queue<int, vector <int>, greater <int> > q;
    int n, Time = 0;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        q.push(a);
    }
    while (!q.empty()) {
        int fine = q.top();
        q.pop();
        if (!q.empty()) {
            fine += q.top();
            q.pop();
        }
        else {
            break;
        }
        q.push(fine);
        Time += fine;
    }
    cout << Time;
    return 0;
}
