// ArcadiaEngine.cpp - STUDENT TEMPLATE
// TODO: Implement all the functions below according to the assignment requirements


#include "ArcadiaEngine.h"
#include <algorithm>
#include <queue>
#include <numeric>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <set>

#define Table_Size 101
using namespace std;

// =========================================================
// PART A: DATA STRUCTURES (Concrete Implementations)
// =========================================================

// --- 1. PlayerTable (Double Hashing) ---

class ConcretePlayerTable : public PlayerTable {
private:
    int ids[Table_Size];
    string names[Table_Size];
    bool used[Table_Size];

    int hash1(int key) {
        long long squared = 1LL * key * key;
        string s = to_string(squared);
        int len = s.length();
        int mid = len / 2;
        int start = mid - 1;
        if (start < 0) start = 0;
        if (start + 3 > len) {
            start = len - 3;
            if (start < 0) start = 0;
        }
        string midDigits = s.substr(start, 3);
        int value = stoi(midDigits);
        return value % Table_Size;
    }

    int hash2(int key) {
        double Golden_Ratio = 0.6180339887;
        double frac = (key * Golden_Ratio) - static_cast<long long>(key * Golden_Ratio);
        int step = static_cast<int>(frac * (Table_Size - 1));
        return step + 1;
    }

    void Print_Table() const {
        const int columns = 5;
        const int rows = (Table_Size + columns - 1) / columns;
        const int cell_size = 17;

        string line_separator = "+";
        for (int c = 0; c < columns; c++) {
            line_separator += string(cell_size + 2, '-') + "+";
        }
        int total_width = line_separator.length();
        string title = "Hash Table";
        int padding_left = (total_width - 2 - title.length()) / 2;
        int padding_right = total_width - 2 - title.length() - padding_left;

        cout << "\n" << line_separator << "\n";
        cout << "|" << string(padding_left, ' ') << title << string(padding_right, ' ') << "|\n";
        cout << line_separator << "\n";

        int index = 0;
        for (int r = 0; r < rows; r++) {
            cout << "|";
            for (int c = 0; c < columns; c++) {
                string content;

                if (index < Table_Size) {
                    if (used[index]) {
                        content = names[index] + " (" + to_string(ids[index]) + ")";
                    }
                    else {
                        content = "empty";
                    }

                    if (content.length() > cell_size) {
                        content = content.substr(0, cell_size);
                    }
                }
                else {
                    content = "";
                }

                cout << " " << setw(cell_size) << left << content << " |";
                index++;
            }
            cout << "\n" << line_separator << "\n";
        }
    }

public:
    ConcretePlayerTable() {
        for (int i = 0; i < Table_Size; i++) {
            used[i] = false;
        }
    }

    void insert(int playerID, string name) override {
        int index1 = hash1(playerID);
        int index2 = hash2(playerID);

        cout << "\n=== INSERT(" << playerID << ", " << name << ") ===\n";
        cout << "hash1 = " << index1 << ", hash2 = " << index2 << "\n";

        for (int i = 0; i < Table_Size; i++) {
            int pos = (index1 + i * index2) % Table_Size;
            cout << "Probing i=" << i << ", pos=" << pos << "\n";

            if (!used[pos]) {
                cout << " => Inserted at position " << pos << "\n";
                ids[pos] = playerID;
                names[pos] = name;
                used[pos] = true;
                Print_Table();
                return;
            }

            if (ids[pos] == playerID) {
                cout << " => Updated existing key at " << pos << "\n";
                names[pos] = name;
                Print_Table();
                return;
            }
        }

        cout << "Hash Table Full.\n";
    }

    string search(int playerID) override {
        int index1 = hash1(playerID);
        int index2 = hash2(playerID);

        cout << "\n=== SEARCH(" << playerID << ") ===\n";
        cout << "hash1 = " << index1 << ", hash2 = " << index2 << "\n";

        for (int i = 0; i < Table_Size; i++) {
            int pos = (index1 + i * index2) % Table_Size;
            cout << "Probing i=" << i << ", pos=" << pos << "\n";

            if (!used[pos]) {
                // Empty slot => stop searching
                cout << " => Empty slot, NOT FOUND.\n";
                return "";
            }

            if (ids[pos] == playerID) {
                cout << " => FOUND at position " << pos << "\n";
                return names[pos];
            }
        }

        cout << " -> NOT FOUND after full table scan\n";
        return "";
    }
};

// --- 2. Leaderboard (Skip List) ---

class ConcreteLeaderboard : public Leaderboard {
private:
    // TODO: Define your skip list node structure and necessary variables
    // skip list node structure
    struct SkipListNode {
        int playerID;
        int score;
        SkipListNode** forward; // Dynamic array of forward pointers
        int level;              // Current node level

        // Olympian Performance: Allocate exactly needed pointers
        SkipListNode(int id, int sc, int lvl)
            : playerID(id), score(sc), level(lvl) {
            forward = new SkipListNode*[lvl + 1];
            for (int i = 0; i <= lvl; i++) {
                forward[i] = nullptr;
            }
        }

        ~SkipListNode() {
            delete[] forward; // Manual memory management
        }
    };
public:
    ConcreteLeaderboard() {
        // TODO: Initialize your skip list
    }

    void addScore(int playerID, int score) override {
        // TODO: Implement skip list insertion
        // Remember to maintain descending order by score
    }

    void removePlayer(int playerID) override {
        // TODO: Implement skip list deletion
    }

    vector<int> getTopN(int n) override {
        // TODO: Return top N player IDs in descending score order
        return {};
    }
};

// --- 3. AuctionTree (Red-Black Tree) ---

enum Color { red, black };

class ConcreteAuctionTree : public AuctionTree {
private:
    struct AuctionNode {
        int itemID;
        int price;
        Color color;
        AuctionNode* left;
        AuctionNode* right;
        AuctionNode* parent;

        AuctionNode(int id = 0, int p = 0)
            : itemID(id), price(p), color(black), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    AuctionNode* root;
    AuctionNode* nil; 

    void leftRotate(AuctionNode* x) {
        AuctionNode* y = x->right;
        x->right = y->left;
        if (y->left != nil) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nil) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotate(AuctionNode* x) {
        AuctionNode* y = x->left;
        x->left = y->right;
        if (y->right != nil) y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nil) root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;
        y->right = x;
        x->parent = y;
    }

    void insertFixup(AuctionNode* z) {
        while (z->parent->color == red) {
            if (z->parent == z->parent->parent->left) {
                AuctionNode* y = z->parent->parent->right;
                if (y->color == red) {
                    z->parent->color = black;
                    y->color = black;
                    z->parent->parent->color = red;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->right) {
                        z = z->parent;
                        leftRotate(z);
                    }
                    z->parent->color = black;
                    z->parent->parent->color = red;
                    rightRotate(z->parent->parent);
                }
            } else {
                AuctionNode* y = z->parent->parent->left;
                if (y->color == red) {
                    z->parent->color = black;
                    y->color = black;
                    z->parent->parent->color = red;
                    z = z->parent->parent;
                } else {
                    if (z == z->parent->left) {
                        z = z->parent;
                        rightRotate(z);
                    }
                    z->parent->color = black;
                    z->parent->parent->color = red;
                    leftRotate(z->parent->parent);
                }
            }
            if (z == root) break;
        }
        root->color = black;
    }

    void transplant(AuctionNode* u, AuctionNode* v) {
        if (u->parent == nil) root = v;
        else if (u == u->parent->left) u->parent->left = v;
        else u->parent->right = v;
        v->parent = u->parent;
    }

    AuctionNode* treeMinimum(AuctionNode* x) {
        while (x->left != nil) x = x->left;
        return x;
    }

    void deleteFixup(AuctionNode* x) {
        while (x != root && x->color == black) {
            if (x == x->parent->left) {
                AuctionNode* w = x->parent->right;
                if (w->color == red) {
                    w->color = black;
                    x->parent->color = red;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == black && w->right->color == black) {
                    w->color = red;
                    x = x->parent;
                } else {
                    if (w->right->color == black) {
                        w->left->color = black;
                        w->color = red;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = black;
                    w->right->color = black;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                AuctionNode* w = x->parent->left;
                if (w->color == red) {
                    w->color = black;
                    x->parent->color = red;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == black && w->left->color == black) {
                    w->color = red;
                    x = x->parent;
                } else {
                    if (w->left->color == black) {
                        w->right->color = black;
                        w->color = red;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = black;
                    w->left->color = black;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = black;
    }

    AuctionNode* searchNode(AuctionNode* node, int itemID) const {
        while (node != nil && itemID != node->itemID) {
            if (itemID < node->itemID) node = node->left;
            else node = node->right;
        }
        return node;
    }

    void deleteSubtree(AuctionNode* node) {
        if (node == nil) return;
        deleteSubtree(node->left);
        deleteSubtree(node->right);
        delete node;
    }
    void inorderRec(AuctionNode* node) const {
        if (node == nil) return;
        inorderRec(node->left);
        std::cout << "(" << node->itemID << ", price=" << node->price
                  << ", color=" << (node->color == red ? "R" : "B") << ") ";
        inorderRec(node->right);
    }

public:
    ConcreteAuctionTree() {
        nil = new AuctionNode();
        nil->left = nil->right = nil->parent = nil;
        nil->color = black;
        root = nil;
    }

    ~ConcreteAuctionTree() {
        deleteSubtree(root);
        delete nil;
    }

    void insertItem(int itemID, int price) override {
        AuctionNode* z = new AuctionNode(itemID, price);
        z->color = red;
        z->left = z->right = z->parent = nil;

        AuctionNode* y = nil;
        AuctionNode* x = root;
        while (x != nil) {
            y = x;
            if (z->itemID < x->itemID) x = x->left;
            else x = x->right;
        }
        z->parent = y;
        if (y == nil) root = z; 
        else if (z->itemID < y->itemID) y->left = z;
        else y->right = z;

        insertFixup(z);
    }

    void deleteItem(int itemID) override {
        AuctionNode* z = searchNode(root, itemID);
        if (z == nil) {
            return;
        }

        AuctionNode* y = z;
        Color yOriginalColor = y->color;
        AuctionNode* x = nullptr;

        if (z->left == nil) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == nil) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = treeMinimum(z->right);
            yOriginalColor = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y;
            } else {
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        delete z;

        if (yOriginalColor == black) {
            deleteFixup(x);
        }
    }

    void inorderPrint() const {
        inorderRec(root);
    }
};

// =========================================================
// PART B: INVENTORY SYSTEM (Dynamic Programming)
// =========================================================

int InventorySystem::optimizeLootSplit(int n, vector<int>& coins) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += coins[i];
    }

    int target = total / 2;

    // dp[j] = true if sum j is achievable
    vector<bool> dp(target + 1, false);
    dp[0] = true;

    for (int i = 0; i < n; i++) {
        // Traverse from right to left to avoid using same coin twice
        for (int j = target; j >= coins[i]; j--) {
            if (dp[j - coins[i]]) {
                dp[j] = true;
            }
        }
    }

    // Find the largest achievable sum <= target
    int closest = 0;
    for (int j = target; j >= 0; j--) {
        if (dp[j]) {
            closest = j;
            break;
        }
    }

    // Minimum difference = total - 2 * closest
    return total - 2 * closest;
}

int InventorySystem::maximizeCarryValue(int capacity, vector<pair<int, int>>& items) {
    const int n = items.size();

    // dp[w] = maximum value achievable with capacity w
    vector<int> dp(capacity + 1, 0);

    for (int i = 0; i < n; i++) {
        int weight = items[i].first;
        int value = items[i].second;

        // Traverse from right to left for 0/1 knapsack
        for (int w = capacity; w >= weight; w--) {
            if (dp[w - weight] + value > dp[w]) {
                dp[w] = dp[w - weight] + value;
            }
        }
    }

    return dp[capacity];
}

long long InventorySystem::countStringPossibilities(string s) {
    const int n = s.size();

    if (n == 0) return 1;

    // dp[i] = number of ways to decode s[0..i-1]
    vector<long long> dp(n + 1, 0);
    dp[0] = 1;  // Empty string has 1 way
    dp[1] = 1;  // Single character has 1 way

    for (int i = 2; i <= n; i++) {
        // Single character decoding - always possible
        dp[i] = dp[i - 1];

        // Check for "uu" or "nn" pattern at positions i-2 and i-1
        char prev = s[i - 2];
        char curr = s[i - 1];

        if ((prev == 'u' && curr == 'u') || (prev == 'n' && curr == 'n')) {
            // Can decode as single letter (w or m) OR as two letters (uu or nn)
            // Adding dp[i-2] accounts for the "decode as single letter" option
            dp[i] += dp[i - 2];
        }
    }

    return dp[n];
}

// =========================================================
// PART C: WORLD NAVIGATOR (Graphs)
// =========================================================

bool WorldNavigator::pathExists(int n, vector<vector<int>>& edges, int source, int dest) {

    if (source == dest) {
        return true;
    }

    //Build the Graph (Adjacency List)
    vector<vector<int>> adj(n);
    
    for (const auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    //BFS initialization
    queue<int> q;
    vector<bool> visited(n, false); 
    
    q.push(source);
    visited[source] = true;

    //BFS traversal
    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (current == dest) {
            return true;
        }

        for (int neighbor : adj[current]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }

    return false;
}

long long WorldNavigator::minBribeCost(int n, int m, long long goldRate, long long silverRate,
                                       vector<vector<int>>& roadData) {
   
    if (n == 1) return 0;
    if (m < n - 1) return -1;

    //struct to store edge info and the final cost
    struct Edge {
        int u, v;
        long long cost;
        
        bool operator<(const Edge& other) const {
            return cost < other.cost;
        }
    };

    vector<Edge> allEdges;
    
    // Calculate the cost for each road 
    for (const auto& road : roadData) {
        long long totalWeight = (road[2] * goldRate) + (road[3] * silverRate);
        allEdges.push_back({road[0], road[1], totalWeight});
    }

    sort(allEdges.begin(), allEdges.end());

    // Use Kruskal's algorithm with Union-Find to pick the best roads
    vector<int> parent(n);
    iota(parent.begin(), parent.end(), 0); 

    // Find the root of a set (with path compression optimization)
    auto findSet = [&](int i, auto&& findSetRef) -> int {
        if (parent[i] == i) return i;
        return parent[i] = findSetRef(parent[i], findSetRef);
    };

    long long minTotalCost = 0;
    int edgesCount = 0;

    for (const auto& edge : allEdges) {
        int rootU = findSet(edge.u, findSet);
        int rootV = findSet(edge.v, findSet);

        // If u,v are in different sets, connect them
        if (rootU != rootV) {
            parent[rootU] = rootV;
            minTotalCost += edge.cost;
            edgesCount++;
        }
    }

    // Check if successfully connected all the cities
    if (edgesCount == n - 1) {
        return minTotalCost;
    } else {
        return -1; 
    }
    return -1;
}

string WorldNavigator::sumMinDistancesBinary(int n, vector<vector<int>>& roads) {

    const long long INF = 1e18; 
    vector<vector<long long>> dist(n, vector<long long>(n, INF));

    // Distance from a city to itself is always zero
    for (int i = 0; i < n; i++) {
        dist[i][i] = 0;
    }

    // Load the initial road weights into the matrix
    for (const auto& road : roads) {
        int u = road[0];
        int v = road[1];
        int weight = road[2];

        dist[u][v] = min(dist[u][v], (long long)weight);
    }

    // Floyd-Warshall algorithm to find all-pairs shortest paths
    // Check if going through city 'k' is shorter than the direct path
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }

    // Sum up the shortest distances for every unique pair of cities
    long long totalSum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (dist[i][j] != INF) {
                totalSum += dist[i][j];
            }
        }
    }

    if (totalSum == 0) return "0";

    // Convert the total sum to a binary string 
    string binary = "";
    while (totalSum > 0) {
        binary += (totalSum % 2 == 0 ? "0" : "1");
        totalSum /= 2;
    }

    reverse(binary.begin(), binary.end());
    
    return binary;
}

// =========================================================
// PART D: SERVER KERNEL (Greedy)
// =========================================================

int ServerKernel::minIntervals(vector<char>& tasks, int n) {

    //Array to find the max frequncy 
    int counts[26] = {0}; 
    int maxFreq = 0;
    
    //Count frequencies
    for (char task : tasks) {
        int index = task - 'A'; 
        counts[index]++;
        
        if (counts[index] > maxFreq) {
            maxFreq = counts[index];
        }
    }

    //If there many chars has the same MaxFreq
    int countMaxFreq = 0;
    for (int i = 0; i < 26; i++) {
        if (counts[i] == maxFreq) {
            countMaxFreq++;
        }
    }

    //Calculate gaps
    int minLen = (maxFreq - 1) * (n + 1) + countMaxFreq;

    return max(minLen, (int)tasks.size());
}

// =========================================================
// FACTORY FUNCTIONS (Required for Testing)
// =========================================================

extern "C" {
    PlayerTable* createPlayerTable() {
        return new ConcretePlayerTable();
    }

    Leaderboard* createLeaderboard() {
        return new ConcreteLeaderboard();
    }

    AuctionTree* createAuctionTree() {
        return new ConcreteAuctionTree();
    }
}
// How to Use Player LookUp
// int main() {
//     ConcretePlayerTable table;
//
//     int choice;
//     while (true) {
//         cout << "\n===========================\n";
//         cout << "     PLAYER TABLE MENU\n";
//         cout << "===========================\n";
//         cout << "1. Add Player\n";
//         cout << "2. Search Player\n";
//         cout << "3. Exit\n";
//         cout << "Enter choice: ";
//         cin >> choice;
//
//         if (choice == 1) {
//             int id;
//             string name;
//             cout << "Enter Player ID: ";
//             cin >> id;
//             cout << "Enter Player Name: ";
//             cin >> name;
//
//             table.insert(id, name);
//         } else if (choice == 2) {
//             int id;
//             cout << "Enter Player ID to search: ";
//             cin >> id;
//
//             string result = table.search(id);
//
//             if (result.empty())
//                 cout << "Player not found.\n";
//             else
//                 cout << "Found Player: " << result << "\n";
//         }
//         else if (choice == 3) {
//             cout << "Exiting...\n";
//             break;
//         }
//         else {
//             cout << "Invalid option, try again.\n";
//         }
//     }
//     return 0;
// }
