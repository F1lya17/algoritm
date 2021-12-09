/*https://contest.yandex.ru/contest/30914/problems/2_2/
Группа людей называется современниками если был такой момент, когда они могли собраться вместе. Для этого в этот момент каждому из них должно было уже исполниться 18 лет, но ещё не исполниться 80 лет. Дан список Жизни Великих Людей. Необходимо получить максимальное количество современников. В день 18летия человек уже может принимать участие в собраниях, а в день 80летия и в день смерти уже не может.
Замечание. Человек мог не дожить до 18-летия, либо умереть в день 18-летия. В этих случаях принимать участие в собраниях он не мог.
57558293*/

#include <iostream>
#include<vector>

using namespace std;

struct Event {
    int day;
    int month;
    int year;
    int co;
};

bool comp(Event a, Event b) {
    if (a.year == b.year) {
        if (a.month == b.month) {
            if (a.day == b.day) {
                return a.co < b.co;
            }
            return a.day < b.day;
        }
        return a.month < b.month;
    }
    return a.year < b.year;
}

void heapify(vector <Event>& arr, int n, int i)
{
    int largest = i;   
    int l = 2*i + 1;
    int r = 2*i + 2; 
    if (l < arr.size() && comp(arr[l], arr[largest])) {
        largest = l;
    }
    if (r < arr.size() && comp(arr[r], arr[largest])) {
        largest = r;
    }
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector <Event>& arr, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i=n-1; i>=0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

int main() {
    int n;
    cin >> n;
    vector <Event> events;
    for (int i = 0; i < n; i++) {
        int sd, sm, sy, fd, fm, fy;
        cin >> sd >> sm >> sy >> fd >> fm >> fy;
        if (sy + 18 > fy) {
            continue;
        }
        else if (sy + 18 == fy && sm > fm) {
            continue;
        }
        else if (sy + 18 == fy && sm == fm && sd >= fd) {
            continue;
        }
        else {
            events.push_back({sd, sm, sy + 18, 1});
        }
        if (fy - sy > 80) {
            events.push_back({sd, sm, sy + 80, -1});
        }
        else if (fy - sy >= 80 && sm < fm) {
            events.push_back({sd, sm, sy + 80, -1});
        }
        else if (fy - sy >= 80 && sm <= fm && sd <= fd) {
            events.push_back({sd, sm, sy + 80, -1});
        }
        else {
            events.push_back({fd, fm, fy, -1});
        }
    }
    heapSort(events, n);
    int amount = 0, answer = 0;
    for (auto event : events) {
		amount += event.co;
		answer = max(answer, amount);
    }
    cout << answer;
	return 0;
}
