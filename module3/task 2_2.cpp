/*Дано число N < 106 и последовательность пар целых чисел из [-231, 231] длиной N. Построить декартово дерево из N узлов, характеризующихся парами чисел (Xi, Yi). 
Каждая пара чисел (Xi, Yi) определяет ключ Xi и приоритет Yi в декартовом дереве. Добавление узла в декартово дерево выполняйте второй версией алгоритма, рассказанного на лекции: 
При добавлении узла (x, y) выполняйте спуск по ключу до узла P с меньшим приоритетом. Затем разбейте найденное поддерево по ключу x так, чтобы в первом поддереве все ключи 
меньше x, а во втором больше или равны x. Получившиеся два дерева сделайте дочерними для нового узла (x, y). Новый узел вставьте на место узла P. Построить также наивное дерево 
поиска по ключам Xi. Равные ключи добавляйте в правое поддерево. Вычислить количество узлов в самом широком слое декартового дерева и количество узлов в самом широком слое 
наивного дерева поиска. Вывести их разницу. Разница может быть отрицательна.
https://contest.yandex.ru/contest/32613/problems/2_2/
62718468*/

#include <iostream>
using namespace std;

struct binaryNode {
    int key;
    binaryNode* left, * right;
    binaryNode() { }
    binaryNode(int key) : key(key), left(nullptr), right(nullptr) { }
};

binaryNode* Root;

void binaryInsert(binaryNode* curRoot, int x) {
    if (x < curRoot->key) {
        if (curRoot->left) {
            binaryInsert(curRoot->left, x);
        }
        else {
            curRoot->left = new binaryNode(x);
        }
    }
    else {
        if (curRoot->right) {
            binaryInsert(curRoot->right, x);
        }
        else {
            curRoot->right = new binaryNode(x);
        }
    }
}

int binaryHeight(binaryNode* curRoot) {
    if (curRoot == nullptr) {
        return 0;
    }
    int left = binaryHeight(curRoot->left);
    int right = binaryHeight(curRoot->right);
    return max(left, right) + 1;
}

void binaryCounter(binaryNode* curRoot, int nodeHeight, int* counter_mass) {
    counter_mass[nodeHeight]++;
    if (curRoot->left != nullptr) {
        binaryCounter(curRoot->left, nodeHeight + 1, counter_mass);
    }
    if (curRoot->right != nullptr) {
        binaryCounter(curRoot->right, nodeHeight + 1, counter_mass);
    }
}

int binaryWidth(binaryNode* curRoot) {
    int Heigh = binaryHeight(curRoot);
    int* counter_mass = new int[Heigh];
    binaryCounter(curRoot, 0, counter_mass);
    int Widt = 0;
    for (int i = 0; i < Heigh; i++) {
        Widt = max(Widt, counter_mass[i]);
    }
    return Widt;
}

struct TreapNode {
    int Key;
    int Priority;
    TreapNode* Left;
    TreapNode* Right;
    TreapNode() { }
    TreapNode(int Key, int Priority) : Key(Key), Priority(Priority), Left(nullptr), Right(nullptr) { }
};

typedef pair<TreapNode*, TreapNode*> splitPair;
splitPair treapSplit(TreapNode* curRoot, int key)
{
    if (curRoot == nullptr) {
        return {nullptr, nullptr};
    }

    if (key < curRoot->Key) {
        splitPair leftSplit = treapSplit(curRoot->Left, key);
        curRoot->Left = leftSplit.second;
        return {leftSplit.first, curRoot};
    }
    else {
        splitPair rightSplit = treapSplit(curRoot->Right, key);
        curRoot->Right = rightSplit.first;
        return {curRoot, rightSplit.second};
    }
}

void treapInsert(TreapNode*& node, int key, int priority) {
    if (node == nullptr) {
        node = new TreapNode(key, priority);
        return;
    }
    else {
        TreapNode* newTreapNode = new TreapNode(key, priority);
        TreapNode* tempNode = node;
        TreapNode* prevNode = node;
        bool bl;
        while (tempNode != nullptr && tempNode->Priority > priority) {
            prevNode = tempNode;
            if (tempNode->Key <= key) {
                tempNode = tempNode->Right;
                bl = false;
            }
            else {
                tempNode = tempNode->Left;
                bl = true;
            }
        }
        splitPair trees = treapSplit(tempNode, key);
        newTreapNode->Left = trees.first;
        newTreapNode->Right = trees.second;

        if (tempNode != prevNode)
        {
            if (key < prevNode->Key)
            {
                prevNode->Left = newTreapNode;
            }
            else
            {
                prevNode->Right = newTreapNode;
            }
        }
        if (node->Priority < priority) {
            node = newTreapNode;
            return;
        }
    }
}

int treapHeight(TreapNode* curRoot) {
    if (curRoot == nullptr) {
        return 0;
    }
    int left = treapHeight(curRoot->Left);
    int right = treapHeight(curRoot->Right);
    return max(left, right) + 1;
}

void treapCounter(TreapNode* curRoot, int nodeHeight, int* counter) {
    counter[nodeHeight]++;
    if (curRoot->Left != nullptr) {
        treapCounter(curRoot->Left, nodeHeight + 1, counter);
    }
    if (curRoot->Right != nullptr) {
        treapCounter(curRoot->Right, nodeHeight + 1, counter);
    }
}

int treapWidth(TreapNode* curRoot) {
    int Height = treapHeight(curRoot);
    int* counter = new int[Height];
    treapCounter(curRoot, 0, counter);
    int Width = 0;
    for (int i = 0; i < Height; i++) {
        Width = max(Width, counter[i]);
    }
    return Width;
}

TreapNode* root;
int main() {
    int n;
    cin >> n;
    int firstKey, firstPrior;
    cin >> firstKey >> firstPrior;
    Root = new binaryNode(firstKey);
    treapInsert(root, firstKey, firstPrior);
    for (int i = 1; i < n; i++) {
        int key, prior;
        cin >> key >> prior;
        treapInsert(root, key, prior);
        binaryInsert(Root, key);
    }
    cout << treapWidth(root) - binaryWidth(Root) << endl;
    return 0;
}
