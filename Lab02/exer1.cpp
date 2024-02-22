#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N, K;

    // Read Input
    cin >> N >> K;
    int prices[N];
    for (int i = 0; i < N; ++i) {
        cin >> prices[i];
    }
    // 2 dimensional array for profit 
    vector<vector<int>> profit(K+1, vector<int>(N, 0));
    // Extra arrays to keep track of buing and selling
    int buy[N];
    int sell[N];

    for (int k = 1; k <= K; ++k) {
        int max_diff = -prices[0];

        for (int n = 1; n < N; ++n) {
            if (profit[k][n -1] <= prices[n] + max_diff) {
                // If the profit for same number of transactions for the previous day is smaller
                // then sell the previous day and buy now
                profit[k][n] = prices[n] + max_diff;
                buy[n] = sell[n-1];
                sell[n] = n;
            } else {
                // Else, do nothing and keep the profit the same. Dont sell or buy
                profit[k][n] = profit[k][n-1];
                buy[n] = buy[n -1];
                sell[n] = sell[n-1];
            }

            max_diff = max(max_diff, profit[k-1][n] - prices[n]);
            // Compare the profit from the previous transaction and the current day's price
        }
    }

    // O(K*N)
    cout << profit[K][N-1] << endl;
    
    /*
    int k = K;
    int day = N - 1;
    while (k > 0 && day >= 0) {
        int buyDay = buy[day];
        int sellDay = sell[day];
        if (buyDay < sellDay) {
            cout << "Buy on day " << buyDay + 1 << ", Sell on day " << sellDay + 1 << endl;
        }
        --k;
        day = buyDay - 1;
    }
    */

    return 0;
}
