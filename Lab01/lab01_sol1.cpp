#include <iostream>

using namespace std; 

bool is_valid_median(int availability[], int N, int K, int mid) {
    int sum[N], greater_mid[N], max_sum, first_elements;
    // 'mid' is the threshold value for the median.

    // Initialize sum and greater_mid arrays
    sum[0] = (availability[0] >= mid) ? 1 : -1;
    greater_mid[0] = (availability[0] >= mid) ? 1 : -1;

    for (int i = 1; i < N; i++) {
        greater_mid[i] = (availability[i] >= mid) ? 1 : -1;
        sum[i] = sum[i - 1] + greater_mid[i];
    }

    for (int i = 0; i<N;i++){
        cout << sum[i];
    }
    cout<<endl;

    max_sum = sum[K - 1];
    first_elements = 0;

    for (int i = K; i < N; i++) {
        // Update 'first_elements' using min function
        first_elements = min(first_elements, sum[i - K]);
        // Update 'max_sum'
        max_sum = max(max_sum, sum[i] - first_elements);
        // If 'max_sum' becomes positive, break the loop
        if (max_sum > 0) {
            break;
        }
    }
    // Return true if there exists a subarray with median at least 'mid'
    return max_sum > 0;
}


int find_max_median(int availability[], int N, int K) {
    int l = 1, r = N + 1, temp, result = -1;
    // Binary Search on availability array
    while (l <= r) {
        temp = (l + r) / 2;
        if (is_valid_median(availability, N, K, temp)) {
            result = temp;
            l = temp + 1;
        } else {
            r = temp - 1;
        }
    }
    return result;
}

int main() {
    int N, K;
    cin >> N >> K;
    int availability[N];

    for (int i = 0; i < N; i++) {
        cin >> availability[i];
    }
    int result = find_max_median(availability, N, K);
    cout << result << endl;
    return 0;
}
