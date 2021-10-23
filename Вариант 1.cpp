#include <iostream>

using namespace std;
 
class Queue {
public:
    Queue() : buffer(0), realSize(0), bufferSize(0), head(0) {}
  
    ~Queue() {
        delete[] buffer;
    }
  
    void pop_front();
    void push_back(int element);
    int get_front();
    int get_size();
 
private:
    int* buffer;
    int realSize, head, bufferSize, element;
    void increase();
};
 
int Queue::get_size() {
    return realSize;
}
 
int Queue::get_front() {
    return buffer[head];
}
void Queue::pop_front() {
    head = (head + 1) % bufferSize;;
    realSize--;
}
 
void Queue::push_back(int element) {
    if (bufferSize == realSize)
        increase();
    buffer[(realSize + head) % bufferSize] = element;
    realSize++;
}
 
void Queue::expand() {
    int newSize = max(2 * bufferSize, 1);
    int* newBuffer = new int[newSize];
    for (int i = 0; i < bufferSize; i++) {
        newBuffer[i] = buffer[(head + i) % bufferSize];
    }
    head = 0;
    delete[] buffer;
    buffer = newBuffer;
    bufferSize = newSize;
}
 
int main()
{
    Queue myQueue;
    int n = 0, a, b, front = 0;
    cin >> n;
    for (int i = 0; i < n ; i++) {
        cin >> a >> b;
        if (a == 2) {
            if (myQueue.get_size() == 0) {
                front = -1;
            }
            else {
                front = myQueue.get_front();
                myQueue.pop_front();
            }
            if (front != b ) {
                cout << "NO";
                return 0;
            }
        }
        else {
            myQueue.push_back(b);
        }
    }
    cout << "YES";
    return 0;
}
