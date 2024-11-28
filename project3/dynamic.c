#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Dynamic Programming Implementation
int dynamic(int *rods, int n, int **dp) {
    // Calculate prefix sum for efficient range sum calculation
    int prefix_sum[n];
    prefix_sum[0] = rods[0];
    for (int i = 1; i < n; i++) {
        prefix_sum[i] = prefix_sum[i - 1] + rods[i];
    }

    // Initialize dp table to -1 for all cells except the diagonal
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                dp[i][j] = 0;  // Cost of a single rod is 0
            } else {
                dp[i][j] = -1; // Default value for uncomputed cells
            }
        }
    }

    // Fill the dp table for valid ranges
    for (int len = 2; len <= n; len++) {  // len is the subproblem size (start from 2 rods)
        for (int i = 0; i <= n - len; i++) {  // i is the starting rod index
            int j = i + len - 1;  // j is the ending rod index for the current subproblem

            dp[i][j] = INT_MAX;  // Initialize to a large number for comparison
            int rod_sum = (i == 0) ? prefix_sum[j] : (prefix_sum[j] - prefix_sum[i - 1]);

            for (int k = i; k < j; k++) {  // k is the point of division
                int cost = dp[i][k] + dp[k + 1][j];
                int total_cost = cost + rod_sum;

                if (total_cost < dp[i][j]) {
                    dp[i][j] = total_cost;  // Store the minimum cost
                }
            }
        }
    }

    // Ensure uncomputed cells remain -1
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (j < i || dp[i][j] == INT_MAX) {
                dp[i][j] = -1;
            }
        }
    }

    return dp[0][n - 1];  // The result for welding all rods from 0 to n-1
}

int main() {
    // Input buffer
    int n;
    printf("Enter the number of rods: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid input. Number of rods must be greater than 0.\n");
        return 1;
    }

    // Read rods
    int *rods = (int *)malloc(n * sizeof(int));
    printf("Enter the lengths of the rods: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &rods[i]);
    }

    // Allocate memory for the dp table
    int **dp = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        dp[i] = (int *)malloc(n * sizeof(int));
    }

    // Calculate the result using dynamic programming
    int result = dynamic(rods, n, dp);

    // Output the result
    printf("\nDynamic Programming Table:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", dp[i][j]);
        }
        printf("\n");
    }

    printf("\nMinimum cost to weld all rods: %d\n", result);

    // Free memory
    free(rods);
    for (int i = 0; i < n; i++) {
        free(dp[i]);
    }
    free(dp);

    return 0;
}
