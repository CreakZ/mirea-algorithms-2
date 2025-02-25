#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

int coinChangeBruteForce(const vector<int>& coins, int amount) {
    if (amount == 0) return 0;
    if (amount < 0) return INT_MAX;

    int minCoins = INT_MAX;

    for (int coin : coins) {
        int res = coinChangeBruteForce(coins, amount - coin);
        if (res != INT_MAX) {
            minCoins = min(minCoins, res + 1);
        }
    }

    return minCoins;
}

int coinChangeGreedy(const vector<int>& coins, int amount) {
    int count = 0;
    int n = coins.size();

    for (int i = n - 1; i >= 0; --i) {
        while (amount >= coins[i]) {
            amount -= coins[i];
            ++count;
        }
    }

    return (amount == 0) ? count : -1;
}

int main() {
    vector<int> coins = {1, 5, 10, 25};
    int amount = 63;

    int resultGreedy = coinChangeGreedy(coins, amount);
    if (resultGreedy == -1) {
        cout << "Невозможно выдать сумму (жадный алгоритм)" << endl;
    } else {
        cout << "Минимальное количество монет (жадный алгоритм): " << resultGreedy << endl;
    }

    int resultBruteForce = coinChangeBruteForce(coins, amount);
    if (resultBruteForce == INT_MAX) {
        cout << "Невозможно выдать сумму (брутфорс)" << endl;
    } else {
        cout << "Минимальное количество монет (алгоритм полного перебора): " << resultBruteForce << endl;
    }

    return 0;
}