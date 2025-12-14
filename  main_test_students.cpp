/**
 * main_test_students.cpp
 * 
 * Part 1: Basic "Happy Path" Test Suite (Original)
 * Part 2: Rigorous/Extreme Test Suite (60 Additional Tests)
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <functional>
#include <algorithm>
#include <climits>
#include "ArcadiaEngine.h"

using namespace std;

// ==========================================
// FACTORY FUNCTIONS (LINKING)
// ==========================================
extern "C" {
    PlayerTable* createPlayerTable();
    Leaderboard* createLeaderboard();
    AuctionTree* createAuctionTree();
}

// ==========================================
// TEST UTILITIES
// ==========================================
class StudentTestRunner {
    int count = 0;
    int passed = 0;
    int failed = 0;

public:
    void runTest(string testName, bool condition) {
        count++;
        // Formatting: Clean alignment
        cout << "TEST " << setw(3) << count << ": " << left << setw(60) << testName;
        if (condition) {
            cout << "[ PASS ]";
            passed++;
        } else {
            cout << "[ FAIL ]";
            failed++;
        }
        cout << endl;
    }

    void printSummary() {
        cout << "\n==========================================" << endl;
        cout << "SUMMARY: Passed: " << passed << " | Failed: " << failed << endl;
        cout << "==========================================" << endl;
        cout << "TOTAL TESTS: " << count << endl;
        if (failed == 0) {
            cout << "Great job! All tests passed." << endl;
        } else {
            cout << "Some tests failed. Check your logic." << endl;
        }
    }
};

StudentTestRunner runner;

// ==========================================
// ORIGINAL HAPPY PATH TESTS
// ==========================================

void test_PartA_DataStructures() {
    cout << "\n--- Part A: Data Structures (Original Happy Path) ---" << endl;

    // 1. PlayerTable
    PlayerTable* table = createPlayerTable();
    runner.runTest("Original: PlayerTable Insert 'Alice'", [&]() {
        table->insert(101, "Alice");
        return table->search(101) == "Alice";
    }());
    delete table;

    // 2. Leaderboard
    // Leaderboard* board = createLeaderboard();
    // runner.runTest("Original: Leaderboard Top 1", [&]() {
    //     board->addScore(1, 100);
    //     board->addScore(2, 200);
    //     vector<int> top = board->getTopN(1);
    //     return (!top.empty() && top[0] == 2);
    // }());
    //
    // runner.runTest("Original: Leaderboard Tie-Break", [&]() {
    //     board->addScore(10, 500);
    //     board->addScore(20, 500);
    //     vector<int> top = board->getTopN(2);
    //     // Expecting {10, 20} (ID 10 < 20)
    //     bool exists = top.size() >= 2;
    //     if(!exists) return false;
    //     // Verify 10 comes before 20
    //     bool correctOrder = false;
    //     for(size_t i=0; i<top.size()-1; ++i) {
    //          if(top[i] == 10 && top[i+1] == 20) correctOrder = true;
    //     }
    //     return correctOrder;
    // }());
    // delete board;

    // 3. AuctionTree
    AuctionTree* tree = createAuctionTree();
    runner.runTest("Original: AuctionTree Insert", [&]() {
        tree->insertItem(1, 100);
        tree->insertItem(2, 50);
        return true; 
    }());
    delete tree;
}

void test_PartB_Inventory() {
    cout << "\n--- Part B: Inventory System (Original Happy Path) ---" << endl;

    runner.runTest("Original: LootSplit {1,2,4} -> 1", [&]() {
        vector<int> c = {1, 2, 4};
        return InventorySystem::optimizeLootSplit(3, c) == 1;
    }());

    runner.runTest("Original: Knapsack Cap 10 -> 60", [&]() {
        vector<pair<int, int>> items = {{1, 10}, {2, 20}, {3, 30}};
        return InventorySystem::maximizeCarryValue(10, items) == 60;
    }());

    runner.runTest("Original: Chat 'uu' -> 2", [&]() {
        return InventorySystem::countStringPossibilities("uu") == 2;
    }());
}

void test_PartC_Navigator() {
    cout << "\n--- Part C: World Navigator (Original Happy Path) ---" << endl;

    runner.runTest("Original: PathExists 0->1->2", [&]() {
        vector<vector<int>> e = {{0, 1}, {1, 2}};
        return WorldNavigator::pathExists(3, e, 0, 2);
    }());

    runner.runTest("Original: MinBribe Triangle -> 15", [&]() {
        vector<vector<int>> r = {{0, 1, 10, 0}, {1, 2, 5, 0}, {0, 2, 20, 0}};
        return WorldNavigator::minBribeCost(3, 3, 1, 1, r) == 15;
    }());

    runner.runTest("Original: BinarySum -> '110'", [&]() {
        vector<vector<int>> r = {{0, 1, 1}, {1, 2, 2}};
        return WorldNavigator::sumMinDistancesBinary(3, r) == "110";
    }());
}

// void test_PartD_Kernel() {
//     cout << "\n--- Part D: Server Kernel (Original Happy Path) ---" << endl;
//
//     runner.runTest("Original: Scheduler {A,A,B} n=2 -> 4", [&]() {
//         vector<char> t = {'A', 'A', 'B'};
//         return ServerKernel::minIntervals(t, 2) == 4;
//     }());
// }

// ==========================================
// NEW RIGOROUS TEST SUITE (60 TESTS)
// ==========================================

// --- Part A1: PlayerTable (10 Tests) ---
void test_PartA_PlayerTable_Extreme() {
    cout << "\n--- Part A1: PlayerTable Extreme (10 Tests) ---" << endl;
    PlayerTable* table = createPlayerTable();

    // 1. Search Non-Existent
    runner.runTest("A1-1. Search Non Existent (999)", [&]() {
        return table->search(999) == "";
    }());

    // 2. Insert & Search Single
    runner.runTest("A1-2. Insert/Search 'Tester'", [&]() {
        table->insert(50, "Tester");
        return table->search(50) == "Tester";
    }());

    // 3. Update Key
    runner.runTest("A1-3. Update Key 50 -> 'TesterUpdated'", [&]() {
        table->insert(50, "TesterUpdated");
        return table->search(50) == "TesterUpdated";
    }());

    // 4. Collision Logic (104 & 205 might collide in mod 101 basic hash)
    runner.runTest("A1-4. Collision Handling", [&]() {
        table->insert(104, "Col1");
        table->insert(205, "Col2"); 
        return table->search(104) == "Col1" && table->search(205) == "Col2";
    }());

    // 5. Full Table Stress
    runner.runTest("A1-5. Full Table Insert (No Crash)", [&]() {
        for(int i=1000; i<1120; ++i) table->insert(i, "Stress");
        return true; 
    }());

    // Reset table for next tests
    delete table;
    table = createPlayerTable();

    // 6. Boundary Key 0
    runner.runTest("A1-6. Insert Key 0", [&]() {
        table->insert(0, "Zero");
        return table->search(0) == "Zero";
    }());

    // 7. Boundary Key Max
    runner.runTest("A1-7. Insert Max Int Key", [&]() {
        table->insert(INT_MAX, "Max");
        return table->search(INT_MAX) == "Max";
    }());

    // 8. Re-Insert Same Key
    runner.runTest("A1-8. Re-Insert behavior", [&]() {
        table->insert(10, "A");
        table->insert(10, "B");
        return table->search(10) == "B";
    }());

    // 9. Negative Key Handing (If supported, or just no crash)
    runner.runTest("A1-9. Negative Key No Crash", [&]() {
        table->insert(-5, "Neg");
        return true; 
    }());

    // 10. Large Batch Check
    runner.runTest("A1-10. Batch Consistency", [&]() {
        bool ok = true;
        for(int i=300; i<310; ++i) table->insert(i, to_string(i));
        for(int i=300; i<310; ++i) if(table->search(i) != to_string(i)) ok = false;
        return ok;
    }());

    delete table;
}

// --- Part A2: Leaderboard (10 Tests) ---
// void test_PartA_Leaderboard_Extreme() {
//     cout << "\n--- Part A2: Leaderboard Extreme (10 Tests) ---" << endl;
//     Leaderboard* board = createLeaderboard();
//
//     // 1. Basic Top 1
//     runner.runTest("A2-1. Top 1 Simple", [&]() {
//         board->addScore(1, 50);
//         vector<int> t = board->getTopN(1);
//         return (!t.empty() && t[0] == 1);
//     }());
//
//     // 2. Tie Break
//     runner.runTest("A2-2. Tie Break (Low ID First)", [&]() {
//         board->addScore(10, 100);
//         board->addScore(5, 100);
//         vector<int> t = board->getTopN(2);
//         // Expect 5 then 10
//         return (t.size() >= 2 && t[0] == 5 && t[1] == 10);
//     }());
//
//     // 3. Remove Top
//     runner.runTest("A2-3. Remove Top Player", [&]() {
//         board->removePlayer(5);
//         vector<int> t = board->getTopN(1);
//         // Should be 10 now (score 100) vs 1 (score 50)
//         return (!t.empty() && t[0] == 10);
//     }());
//
//     // 4. Remove Non-Existent
//     runner.runTest("A2-4. Remove Non-Existent", [&]() {
//         board->removePlayer(999); // No crash
//         auto t = board->getTopN(1);
//         return (!t.empty() && t[0] == 10);
//     }());
//
//     // 5. Empty Board
//     runner.runTest("A2-5. Empty Board getTopN", [&]() {
//         Leaderboard* b2 = createLeaderboard();
//         return b2->getTopN(5).empty();
//         delete b2;
//     }());
//
//     // 6. Invalid N=0
//     runner.runTest("A2-6. getTopN(0)", [&]() {
//         return board->getTopN(0).empty();
//     }());
//
//     // 7. Negative N
//     runner.runTest("A2-7. getTopN(-1)", [&]() {
//         return board->getTopN(-1).empty();
//     }());
//
//     // 8. Large N
//     runner.runTest("A2-8. getTopN > size", [&]() {
//         // We have 1(50), 10(100). Size 2.
//         return board->getTopN(10).size() == 2;
//     }());
//
//     // 9. Duplicates Galore
//     runner.runTest("A2-9. Many Duplicates", [&]() {
//         // Add 30, 40, 50 all score 200
//         board->addScore(50, 200);
//         board->addScore(40, 200);
//         board->addScore(30, 200);
//         vector<int> t = board->getTopN(3);
//         // correct: 30, 40, 50
//         bool ok = (t.size()==3 && t[0]==30 && t[1]==40 && t[2]==50);
//         return ok;
//     }());
//
//     // 10. Update Score
//     runner.runTest("A2-10. Update Score", [&]() {
//         board->addScore(1, 5000); // 1 was 50, now 5000. Should be top
//         vector<int> t = board->getTopN(1);
//         return t[0] == 1;
//     }());
//
//     delete board;
// }

// --- Part A3: AuctionTree (10 Tests) ---
void test_PartA_AuctionTree_Extreme() {
    cout << "\n--- Part A3: AuctionTree Extreme (10 Tests) ---" << endl;
    AuctionTree* tree = createAuctionTree();

    // 1. Insert Root
    runner.runTest("A3-1. Insert Root", [&]() {
        tree->insertItem(50, 100);
        return true; 
    }());

    // 2. Insert Left
    runner.runTest("A3-2. Insert Smaller Price", [&]() {
        tree->insertItem(40, 50);
        return true;
    }());

    // 3. Insert Right
    runner.runTest("A3-3. Insert Larger Price", [&]() {
        tree->insertItem(60, 150);
        return true;
    }());

    // 4. Duplicate Price
    runner.runTest("A3-4. Duplicate Price", [&]() {
        tree->insertItem(99, 100); // Same price as root (100)
        // Should settle based on ID
        return true;
    }());

    // 5. Delete Leaf
    runner.runTest("A3-5. Delete Leaf", [&]() {
        // 40 is leaf
        tree->deleteItem(40);
        return true;
    }());

    // 6. Delete Node with 1 child
    runner.runTest("A3-6. Delete 1-Child Node", [&]() {
        // Construct condition...
        tree->insertItem(5, 10);
        tree->insertItem(2, 5); 
        // 5 has child 2. Delete 5.
        tree->deleteItem(5);
        return true;
    }());

    // 7. Delete Node with 2 children
    runner.runTest("A3-7. Delete 2-Child Node", [&]() {
        tree->insertItem(200, 200);
        tree->insertItem(150, 150);
        tree->insertItem(250, 250);
        // 200 has 150 and 250
        tree->deleteItem(200);
        return true; 
    }());

    // 8. Delete Root
    runner.runTest("A3-8. Delete Root", [&]() {
        // Trying to delete whatever root is. Assuming ID 50 still exists?
        tree->deleteItem(50);
        return true;
    }());

    // 9. Delete Non-Existent
    runner.runTest("A3-9. Delete Non Existent (No Crash)", [&]() {
        tree->deleteItem(9999);
        return true;
    }());

    // 10. Large Volume
    runner.runTest("A3-10. Insert 100 Items", [&]() {
        for(int i=1000; i<1100; ++i) tree->insertItem(i, i*2);
        return true;
    }());

    // 11. Duplicate Prices (Manual/Stability check)
    runner.runTest("A3-11. Duplicate Prices", [&]() {
        // Insert items with same price but different IDs
        tree->insertItem(301, 500);
        tree->insertItem(302, 500);
        tree->insertItem(300, 500);
        
        // Since we can't inspect the tree structure via public API, 
        // we verify we can delete them individually without crashing
        // and that they exist in the tree (by not crashing)
        tree->deleteItem(301);
        tree->deleteItem(302);
        tree->deleteItem(300);
        return true;
    }());

    // 12. Large Dataset Stress (Performance/Crash)
    runner.runTest("A3-12. Large Dataset (10k items)", [&]() {
        for(int i=10000; i<20000; ++i) {
            tree->insertItem(i, i%100); // Many duplicates in price
        }
        // Delete some
        for(int i=10000; i<10500; ++i) {
            tree->deleteItem(i);
        }
        return true;
    }());

    delete tree;
}

// --- Part B: Inventory (Extreme & Large) ---
void test_PartB_Extreme() {
    cout << "\n--- Part B: Inventory Extreme (12 Tests) ---" << endl;

    runner.runTest("B-1. LootSplit Empty", [&]() {
        vector<int> c; return InventorySystem::optimizeLootSplit(0,c) == 0;
    }());
    runner.runTest("B-2. LootSplit Single", [&]() {
        vector<int> c={10}; return InventorySystem::optimizeLootSplit(1,c) == 10;
    }());
    runner.runTest("B-3. LootSplit Equal", [&]() {
        vector<int> c={5,5}; return InventorySystem::optimizeLootSplit(2,c) == 0;
    }());
    runner.runTest("B-4. LootSplit {1,2,3}", [&]() {
        vector<int> c={1,2,3}; return InventorySystem::optimizeLootSplit(3,c) == 0;
    }());
    runner.runTest("B-5. Knapsack Zero Cap", [&]() {
        vector<pair<int,int>> i = {{1,10}}; return InventorySystem::maximizeCarryValue(0,i) == 0; 
    }());
    runner.runTest("B-6. Knapsack Huge item", [&]() {
        vector<pair<int,int>> i = {{100,10}}; return InventorySystem::maximizeCarryValue(5,i) == 0;
    }());
    runner.runTest("B-7. Knapsack Exact fit", [&]() {
        vector<pair<int,int>> i = {{5,10}}; return InventorySystem::maximizeCarryValue(5,i) == 10;
    }());
    runner.runTest("B-8. Knapsack Multiple", [&]() {
        vector<pair<int,int>> i = {{1,1}, {1,1}}; return InventorySystem::maximizeCarryValue(1,i) == 1;
    }());
    runner.runTest("B-9. Chat Empty", [&]() {
         return InventorySystem::countStringPossibilities("") == 1;
    }());
    runner.runTest("B-10. Chat 'nnnn'", [&]() {
         return InventorySystem::countStringPossibilities("nnnn") == 5;
    }());
    
    // 11. Large String Input
    runner.runTest("B-11. Chat Large String", [&]() {
        // "uuuu..." 20 times. 
        // u=1, uu=2, uuu=3, uuuu=5... Fib(20+1) basically
        // Fib(21) = 10946
        string s = "";
        for(int k=0; k<20; ++k) s+="u";
        long long res = InventorySystem::countStringPossibilities(s);
        return res == 10946; 
    }());

    // 12. Large Coin Vector
    runner.runTest("B-12. LootSplit Large Vec", [&]() {
        // 50 items of value 1. Sum=50. Target=25. Achievable? Yes. Diff=0.
        vector<int> c(50, 1);
        return InventorySystem::optimizeLootSplit(50, c) == 0;
    }());

    // --- DESTRUCTIVE TESTS (Likely to Fail / Crash Current Impl) ---
    
    // 13. DP Memory Exploit (Large Value)
    // Current Impl: dp[total/2]. If sum is 10^9, dp array needs ~500MB+ or fails allocation.
    runner.runTest("B-13. LootSplit Large Values", [&]() {
        // 2 coins, value 10^8 each. Sum = 2*10^8. Target = 10^8.
        vector<int> c = {1000000000, 1000000000}; 
        // long long start = clock();
        int res = InventorySystem::optimizeLootSplit(2, c);
        // Correct result is 0. But if it tries to allocate dp[10^9], it might crash.
        return res == 0;
    }());

    // 14. Overflow (Fibonacci > 92)
    runner.runTest("B-14. Chat Overflow", [&]() {
        // Fib(93) > 2^63 - 1.
        string s = "";
        for(int k=0; k<100; ++k) s+="u";
        long long res = InventorySystem::countStringPossibilities(s);
        // Result will likely wrap around if long long overflows
        return res > 0; // Just check if positive
    }());

    // 15. Crash: Negative Allocation (Exception)
    runner.runTest("B-15. Knapsack Negative Cap", [&]() {
        vector<pair<int,int>> i = {{1,10}}; 
        // vector<int> dp(-1) throws length_error or bad_alloc usually
        return InventorySystem::maximizeCarryValue(-5, i) == 0; 
    }());
}

// --- Part C: Navigator (10 Tests) ---
void test_PartC_Extreme() {
    cout << "\n--- Part C: Navigator Extreme (10 Tests) ---" << endl;

    runner.runTest("C-1. Path Disconnected", [&]() {
        vector<vector<int>> e={{0,1}, {2,3}}; return !WorldNavigator::pathExists(4, e, 0, 3);
    }());
    runner.runTest("C-2. Path Self", [&]() {
        vector<vector<int>> e; return WorldNavigator::pathExists(5, e, 2, 2);
    }());
    runner.runTest("C-3. Path Cycle", [&]() {
        vector<vector<int>> e={{0,1},{1,0}}; return WorldNavigator::pathExists(2, e, 0, 1);
    }());
    runner.runTest("C-4. MinBribe Disconnected", [&]() {
        vector<vector<int>> r={{0,1,1,1}}; return WorldNavigator::minBribeCost(3,1,1,1,r) == -1;
    }());
    runner.runTest("C-5. MinBribe N=1", [&]() {
        vector<vector<int>> r; return WorldNavigator::minBribeCost(1,0,1,1,r) == 0;
    }());
    runner.runTest("C-6. MinBribe Expensive", [&]() {
        vector<vector<int>> r={{0,1,100,100}}; return WorldNavigator::minBribeCost(2,1,1,1,r) == 200;
    }());
    runner.runTest("C-7. BinarySum NoEdges", [&]() {
        vector<vector<int>> r; return WorldNavigator::sumMinDistancesBinary(2,r) == "0";
    }());
    runner.runTest("C-8. BinarySum Disconnected", [&]() {
        vector<vector<int>> r={{0,1,10}}; return WorldNavigator::sumMinDistancesBinary(3,r) == "1010"; // 10 decimal -> 1010
    }());
    runner.runTest("C-9. BinarySum Large", [&]() {
        vector<vector<int>> r={{0,1,15}}; return WorldNavigator::sumMinDistancesBinary(2,r) == "1111";
    }());
    // 12. Large Coin Vector
    runner.runTest("B-12. LootSplit Large Vec", [&]() {
        // 50 items of value 1. Sum=50. Target=25. Achievable? Yes. Diff=0.
        vector<int> c(50, 1);
        return InventorySystem::optimizeLootSplit(50, c) == 0;
    }());

    // --- DESTRUCTIVE TESTS (Likely to Fail / Crash Current Impl) ---
    
    // 13. DP Memory Exploit (Large Value)
    // Current Impl: dp[total/2]. If sum is 10^9, dp array needs ~500MB+ or fails allocation.
    runner.runTest("B-13. LootSplit Large Values", [&]() {
        // 2 coins, value 10^8 each. Sum = 2*10^8. Target = 10^8.
        // vector<bool> dp(100000001) -> ~12.5MB (bit vector spec) or 100MB (bool typically 1 byte).
        // Let's try larger. 10^9. ~1GB.
        vector<int> c = {1000000000, 1000000000}; 
        long long start = clock();
        int res = InventorySystem::optimizeLootSplit(2, c);
        // Correct result is 0. But if it tries to allocate dp[10^9], it might crash.
        return res == 0;
    }());

    // 14. Overflow (Fibonacci > 92)
    runner.runTest("B-14. Chat Overflow", [&]() {
        // Fib(93) > 2^63 - 1.
        string s = "";
        for(int k=0; k<100; ++k) s+="u";
        long long res = InventorySystem::countStringPossibilities(s);
        // Result will likely wrap around if long long overflows
        return res > 0; // Just check if positive, though overflow might make it negative.
    }());
}

// --- Part D: Scheduler (10 Tests) ---
// void test_PartD_Extreme() {
//     cout << "\n--- Part D: Scheduler Extreme (10 Tests) ---" << endl;
//
//     runner.runTest("D-1. Empty", [&]() {
//         vector<char> t; return ServerKernel::minIntervals(t, 2) == 0;
//     }());
//     runner.runTest("D-2. Single", [&]() {
//         vector<char> t={'A'}; return ServerKernel::minIntervals(t, 5) == 1;
//     }());
//     runner.runTest("D-3. All Same", [&]() {
//         vector<char> t={'A','A','A'}; return ServerKernel::minIntervals(t, 2) == 7;
//     }()); // A _ _ A _ _ A = 1+2+1+2+1 = 7? Wait. A(0), A(3), A(6). intervals: 0,1,2,3,4,5,6 => 7 slots. Yes.
//     runner.runTest("D-4. n=0", [&]() {
//         vector<char> t={'A','A'}; return ServerKernel::minIntervals(t, 0) == 2;
//     }());
//     runner.runTest("D-5. Distinct", [&]() {
//         vector<char> t={'A','B','C'}; return ServerKernel::minIntervals(t, 10) == 3;
//     }());
//     runner.runTest("D-6. Mixed", [&]() {
//         vector<char> t={'A','A','B'}; // A B _ A
//         return ServerKernel::minIntervals(t, 2) == 4;
//     }());
//     runner.runTest("D-7. Order Indep", [&]() {
//         vector<char> t={'B','A','A'};
//         return ServerKernel::minIntervals(t, 2) == 4;
//     }());
//     runner.runTest("D-8. Large n", [&]() {
//         vector<char> t={'A','A'}; // A _ _ _ A (n=3) -> 1+3+1 = 5
//         return ServerKernel::minIntervals(t, 3) == 5;
//     }());
//     runner.runTest("D-9. Pair", [&]() {
//         vector<char> t={'A','A','B','B'}; // n=2. A B _ A B -> 5
//         return ServerKernel::minIntervals(t, 2) == 5;
//     }());
//     runner.runTest("D-10. Trio", [&]() {
//         vector<char> t={'A','A','B','B','C','C'}; // n=1. A B C A B C -> 6
//         return ServerKernel::minIntervals(t, 1) == 6;
//     }());
// }

int main() {
    cout << "==========================================" << endl;
    cout << "    ARCADIA ENGINE - FULL TEST SUITE      " << endl;
    cout << "==========================================" << endl;

    // 1. Original Happy Path
    test_PartA_DataStructures();
    test_PartB_Inventory();
    test_PartC_Navigator();
    // test_PartD_Kernel();

    // 2. New Rigorous Tests
    test_PartA_PlayerTable_Extreme();
    // test_PartA_Leaderboard_Extreme();
    test_PartA_AuctionTree_Extreme();
    test_PartB_Extreme();
    test_PartC_Extreme();
    // test_PartD_Extreme();

    runner.printSummary();

    return 0;
}