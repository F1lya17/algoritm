/*Дано число N ≤ 104 и последовательность целых чисел из [-231..231] длиной N. Требуется построить бинарное дерево, заданное наивным порядком вставки. Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root. Выведите элементы в порядке in-order (слева направо).
Рекурсия запрещена.
https://contest.yandex.ru/contest/32613/problems/
62722830*/

#include <iostream>
#include <stack>

using namespace std;

struct binaryNode {
    int key;
    binaryNode* left, * right;
    binaryNode() { }
    binaryNode(int key) : key(key), left(nullptr), right(nullptr) { }
};

binaryNode* Root;

void binaryInsert(binaryNode* curRoot, int x) {
    binaryNode* curPrev;
    bool side;
    while (curRoot != nullptr) {
        if (x <= curRoot->key) {
            curPrev = curRoot;
            curRoot = curRoot->left;
            side = true;
        }
        else {
            curPrev = curRoot;
            curRoot = curRoot->right;
            side = false;
        }
    }
    if (side) {
        curPrev->left = new binaryNode(x);
    }
    else {
        curPrev->right = new binaryNode(x);
    }
}

void binaryPrint(binaryNode* curRoot) {
    stack <binaryNode*> s;
    binaryNode* tmp = curRoot;
    while (tmp != nullptr || !s.empty()) {
        while (tmp != nullptr) {
            s.push(tmp);
            tmp = tmp->left;
        }
        tmp = s.top();
        s.pop();
        cout << tmp->key << " ";
        tmp = tmp->right;
    }
}

int main()
{
    int n;
    cin >> n;
    int first;
    cin >> first;
    Root = new binaryNode(first);
    for (int i = 0; i < n - 1; i++) {
        int value;
        cin >> value;
        binaryInsert(Root, value);
    }
    binaryPrint(Root);
    return 0;
}
