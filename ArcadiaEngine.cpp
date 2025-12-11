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
    // Hint: You'll need nodes with multiple forward pointers

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

class ConcreteAuctionTree : public AuctionTree {
private:
    // TODO: Define your Red-Black Tree node structure
    // Hint: Each node needs: id, price, color, left, right, parent pointers

public:
    ConcreteAuctionTree() {
        // TODO: Initialize your Red-Black Tree
    }

    void insertItem(int itemID, int price) override {
        // TODO: Implement Red-Black Tree insertion
        // Remember to maintain RB-Tree properties with rotations and recoloring
    }

    void deleteItem(int itemID) override {
        // TODO: Implement Red-Black Tree deletion
        // This is complex - handle all cases carefully
    }
};

// =========================================================
// PART B: INVENTORY SYSTEM (Dynamic Programming)
// =========================================================

int InventorySystem::optimizeLootSplit(int n, vector<int>& coins) {
    // TODO: Implement partition problem using DP
    // Goal: Minimize |sum(subset1) - sum(subset2)|
    // Hint: Use subset sum DP to find closest sum to total/2
    return 0;
}

int InventorySystem::maximizeCarryValue(int capacity, vector<pair<int, int>>& items) {
    // TODO: Implement 0/1 Knapsack using DP
    // items = {weight, value} pairs
    // Return maximum value achievable within capacity
    return 0;
}

long long InventorySystem::countStringPossibilities(string s) {
    // TODO: Implement string decoding DP
    // Rules: "uu" can be decoded as "w" or "uu"
    //        "nn" can be decoded as "m" or "nn"
    // Count total possible decodings
    return 0;
}

// =========================================================
// PART C: WORLD NAVIGATOR (Graphs)
// =========================================================

bool WorldNavigator::pathExists(int n, vector<vector<int>>& edges, int source, int dest) {
    // TODO: Implement path existence check using BFS or DFS
    // edges are bidirectional
    return false;
}

long long WorldNavigator::minBribeCost(int n, int m, long long goldRate, long long silverRate,
                                       vector<vector<int>>& roadData) {
    // TODO: Implement Minimum Spanning Tree (Kruskal's or Prim's)
    // roadData[i] = {u, v, goldCost, silverCost}
    // Total cost = goldCost * goldRate + silverCost * silverRate
    // Return -1 if graph cannot be fully connected
    return -1;
}

string WorldNavigator::sumMinDistancesBinary(int n, vector<vector<int>>& roads) {
    // TODO: Implement All-Pairs Shortest Path (Floyd-Warshall)
    // Sum all shortest distances between unique pairs (i < j)
    // Return the sum as a binary string
    // Hint: Handle large numbers carefully
    return "0";
}

// =========================================================
// PART D: SERVER KERNEL (Greedy)
// =========================================================

int ServerKernel::minIntervals(vector<char>& tasks, int n) {
    // TODO: Implement task scheduler with cooling time
    // Same task must wait 'n' intervals before running again
    // Return minimum total intervals needed (including idle time)
    // Hint: Use greedy approach with frequency counting
    return 0;
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
int main() {
    ConcretePlayerTable table;

    int choice;
    while (true) {
        cout << "\n===========================\n";
        cout << "     PLAYER TABLE MENU\n";
        cout << "===========================\n";
        cout << "1. Add Player\n";
        cout << "2. Search Player\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            string name;
            cout << "Enter Player ID: ";
            cin >> id;
            cout << "Enter Player Name: ";
            cin >> name;

            table.insert(id, name);
        } else if (choice == 2) {
            int id;
            cout << "Enter Player ID to search: ";
            cin >> id;

            string result = table.search(id);

            if (result.empty())
                cout << "Player not found.\n";
            else
                cout << "Found Player: " << result << "\n";
        }
        else if (choice == 3) {
            cout << "Exiting...\n";
            break;
        }
        else {
            cout << "Invalid option, try again.\n";
        }
    }
    return 0;
}
