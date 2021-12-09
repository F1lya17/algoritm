/*https://contest.yandex.ru/contest/30914/problems/1_3/
Задано N точек на плоскости. Указать (N-1)-звенную несамопересекающуюся замкнутую ломаную, проходящую через все эти точки.
Предполагается, что никакие три точки не лежат на одной прямой.
Стройте ломаную от точки, имеющей наименьшую координату x. Если таких точек несколько, то используйте точку с наименьшей координатой y. Точки на ломаной расположите в порядке убывания углов лучей от начальной точки до всех остальных точек.
Для сортировки точек реализуйте алгоритм сортировки вставками.
59008573*/

#include <iostream>
#include <vector>
using namespace std;

struct Point {
    double x, y, corner;
};

void cornerSort(vector<Point>& arr, int n)
{
    for (int i = 2; i < n; i++) {
        int j = i - 1;
        double tmp = arr[i].corner;
        double tmp1 = arr[i].x;
        double tmp2 = arr[i].y;
        for (; j >= 1 && arr[j].corner < tmp; j--) {
            arr[j + 1].corner = arr[j].corner;
            arr[j + 1].x = arr[j].x;
            arr[j + 1].y = arr[j].y;
        }
        arr[j + 1].corner = tmp;
        arr[j + 1].x = tmp1;
        arr[j + 1].y = tmp2;
    }
}

void insertionSort(vector<Point>& arr, int n) {
    for (int i = 1; i < n; i++) {
        int tmp1 = arr[i].x;
        int tmp2 = arr[i].y;
        int j = i - 1;
        for(;j >= 0 && tmp1 <= arr[j].x; j--) {
            if (tmp1 < arr[j].x) {
                arr[j + 1] = arr[j];
                arr[j].x = tmp1;
                arr[j].y = tmp2;
            }
            else if (tmp2 < arr[j].y) {
                arr[j + 1] = arr[j];
                arr[j].x = tmp1;
                arr[j].y = tmp2;
            }
        }
    }
}

void findCorner(vector<Point>& arr, int n)
{
    for (int i = 1; i < n; i++) {
        if (arr[i].x != arr[0].x) {
            arr[i].corner = ((arr[i].y - arr[0].y) / (arr[i].x - arr[0].x));
        }
        else {
            arr[i].corner = 10000;
        }
    }
}

int main() {
    int n;
    cin >> n;
    vector <Point> arr;
    for (int i = 0; i < n; i++) {
        double x, y;
        cin >> x >> y;
        arr.push_back({x, y, 0});
    }
    insertionSort(arr, n);
    findCorner(arr, n);
    cornerSort(arr, n);
    for (auto i : arr) {
        cout << i.x << " " << i.y << endl;
    }
    return 0;
}
