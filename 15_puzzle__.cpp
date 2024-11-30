#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>

using namespace std;

const int N = 4;
const int goal[N][N] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 0}
};

struct Node {
    vector<vector<int>> board;
    int x, y, cost, level;
    Node* parent;
};

int calculateCost(vector<vector<int>>& initial) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (initial[i][j] && initial[i][j] != goal[i][j]) {
                count++;
            }
        }
    }
    return count;
}

bool isSafe(int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N);
}

void printPath(Node* root) {
    if (root == nullptr) {
        return;
    }
    printPath(root->parent);
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << root->board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

Node* newNode(vector<vector<int>>& board, int x, int y, int newX, int newY, int level, Node* parent) {
    Node* node = new Node;
    node->board = board;
    swap(node->board[x][y], node->board[newX][newY]);
    node->x = newX;
    node->y = newY;
    node->cost = calculateCost(node->board);
    node->level = level;
    node->parent = parent;
    return node;
}

struct comp {
    bool operator()(const Node* lhs, const Node* rhs) const {
        return (lhs->cost + lhs->level) > (rhs->cost + rhs->level);
    }
};

void solve(vector<vector<int>>& initial, int x, int y) {
    priority_queue<Node*, vector<Node*>, comp> pq;
    Node* root = newNode(initial, x, y, x, y, 0, nullptr);
    pq.push(root);

    while (!pq.empty()) {
        Node* min = pq.top();
        pq.pop();

        if (min->cost == 0) {
            printPath(min);
            return;
        }

        int row[] = {1, 0, -1, 0};
        int col[] = {0, -1, 0, 1};

        for (int i = 0; i < 4; i++) {
            if (isSafe(min->x + row[i], min->y + col[i])) {
                Node* child = newNode(min->board, min->x, min->y, min->x + row[i], min->y + col[i], min->level + 1, min);
                pq.push(child);
            }
        }
    }
}

int main() {
    vector<vector<int>> initial = {
        {1, 2, 3, 4},
        {5, 6, 0, 8},
        {9, 10, 7, 12},
        {13, 14, 11, 15}
    };

    int x = 1, y = 2; 
    solve(initial, x, y);

    return 0;
}
