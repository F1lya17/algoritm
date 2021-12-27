/*Дано число N и N строк. Каждая строка содержащит команду добавления или удаления натуральных чисел, а также запрос на получение k-ой порядковой статистики. 
Команда добавления числа A задается положительным числом A, команда удаления числа A задается отрицательным числом “-A”. 
Запрос на получение k-ой порядковой статистики задается числом k. Требуемая скорость выполнения запроса - O(log n)
https://contest.yandex.ru/contest/32613/problems/3_2/
62864646*/

#include <iostream>
#include <cmath>

using namespace std;

struct Node {
    int key;
    int Val = 1;
    unsigned char height;
    Node* right;
    Node* left;
    Node(int k) { key = k; height = 1; left = right = 0; }
};

unsigned char height(Node* p) {
    if (p) {
        return p->height;
    }
    else {
        return 0;
    }
}

int Val(Node* vertex) {
    if (vertex) {
        return vertex->Val;
    }
    else {
        return 0;
    }
}

void update(Node* vertex) {
    vertex->Val = Val(vertex->left) + Val(vertex->right) + 1;
}

void updateTree(Node* curRoot) {
    if (curRoot->left != nullptr) {
        updateTree(curRoot->left);
    }
    if (curRoot->right != nullptr) {
        updateTree(curRoot->right);
    }
    update(curRoot);
}

int kStat(Node* curRoot, int x) {
    if (Val(curRoot->left) > x) {
        return kStat(curRoot->left, x);
    }
    else if (Val(curRoot->left) == x) {
        return curRoot->key;
    }
    else {
        return kStat(curRoot->right, x - Val(curRoot->left) - 1);
    }
}


int BF(Node* vertex) {
    return height(vertex->right) - height(vertex->left);
}

void OverHeight(Node* vertex) {
    unsigned char hleft = height(vertex->left);
    unsigned char hright = height(vertex->right);
    if (hleft > hright) {
        vertex->height = hleft + 1;
    }
    else {
        vertex->height = hright + 1;
    }
}

Node* RightRotation(Node* curRoot) {
    Node* temRoot = curRoot->left;
    curRoot->left = temRoot->right;
    temRoot->right = curRoot;
    OverHeight(curRoot);
    OverHeight(temRoot);
    //updateTree(curRoot);
    return temRoot;
}
Node* LeftRotation(Node* curRoot) {
    Node* temRoot = curRoot->right;
    curRoot->right = temRoot->left;
    temRoot->left = curRoot;
    OverHeight(curRoot);
    OverHeight(temRoot);
    //updateTree(curRoot);
    return temRoot;
}

Node* Balance(Node* curRoot) {
    OverHeight(curRoot);
    if (BF(curRoot) == 2) {
        if (BF(curRoot->right) < 0) {
            curRoot->right = RightRotation(curRoot->right);
        }
        return LeftRotation(curRoot);
    }
    if (BF(curRoot) == -2) {
        if (BF(curRoot->left) > 0) {
            curRoot->left = LeftRotation(curRoot->left);
        }
        return RightRotation(curRoot);
    }
    return curRoot;
}

Node* Insert(Node* curRoot, int x) {
    if (curRoot == nullptr) {
        return new Node(x);
    }
    if (x < curRoot->key) {
        curRoot->left = Insert(curRoot->left, x);
        //updateTree(curRoot);
    }
    else {
        curRoot->right = Insert(curRoot->right, x);
        //updateTree(curRoot);
    }
    return Balance(curRoot);
}

Node* SearchMin(Node* curRoot) {
    if (curRoot->left) {
        return SearchMin(curRoot->left);
    }
    else {
        return curRoot;
    }
}

Node* DeleteMin(Node* vertex) {
    if (vertex->left == nullptr) {
        return vertex->right;
    }
    vertex->left = DeleteMin(vertex->left);
    //updateTree(vertex);
    return Balance(vertex);
}

Node* Delete(Node* curRoot, int x) {
    if (curRoot == nullptr) {
        return 0;
    }
    if (x < curRoot->key) {
        curRoot->left = Delete(curRoot->left, x);
        //updateTree(curRoot);
    }
    else if (x > curRoot->key) {
        curRoot->right = Delete(curRoot->right, x);
        //updateTree(curRoot);
    }
    else {
        Node* tempRoot_1 = curRoot->left;
        Node* tempRoot_2 = curRoot->right;
        delete curRoot;
        if (tempRoot_2 == nullptr) {
            return tempRoot_1;
        }
        Node* min = SearchMin(tempRoot_2);
        min->right = DeleteMin(tempRoot_2);
        min->left = tempRoot_1;
        //update(min);
        return Balance(min);
    }
    return Balance(curRoot);
}

Node* Root;

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int value, stat;
        cin >> value >> stat;
        if (value < 0) {
            Root = Delete(Root, abs(value));
            updateTree(Root);
        }
        else {
            Root = Insert(Root, value);
            updateTree(Root);
        }
        cout << kStat(Root, stat) << " ";
    }
    return 0;
}
