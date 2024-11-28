#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Declaración de funciones
int recursive(int *rods, int n, int left, int right, int calls[]);
int memoization(int *rods, int n, int left, int right, int **memo);
int dynamic(int *rods, int n, int **dp);

// Función principal
int main(int argc, char *argv[]) {
    char method = argv[1][0];
    int n = atoi(argv[2]);

    int *rods = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        rods[i] = atoi(argv[3 + i]);
    }

    if (method == 'R' || method == 'r') {
        int calls[1] = {0}; // Contador de llamadas recursivas
        int result = recursive(rods, n, 0, n - 1, calls);
        if (method == 'R') {
            printf("%d\n", result);
        } else {
            printf("%d\n", calls[0]);
        }

    } else if (method == 'M' || method == 'm') {
        int **memo = (int **)malloc(n * sizeof(int *));
        for (int i = 0; i < n; i++) {
            memo[i] = (int *)malloc(n * sizeof(int));
            for (int j = 0; j < n; j++) {
                memo[i][j] = -1;
            }
            memo[i][i] = 0;  // Set the diagonal elements (cost of welding a single rod) to 0
        }
        int result = memoization(rods, n, 0, n - 1, memo);
        if (method == 'M') {
            printf("%d\n", result);
        } else {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    printf("%d ", memo[i][j]);
                }
                printf("\n");
            }
        }
    } else if (method == 'D' || method == 'd') {
        // Initilize dp table 
        int **dp = (int **)malloc(n * sizeof(int *));
        for (int i = 0; i < n; i++) {
            dp[i] = (int *)malloc(n * sizeof(int));
        }

        int result = dynamic(rods, n, dp);

        if (method == 'D') {
            printf("%d\n", result);
        } else {
            // Imprimir tabla dinámica
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    printf("%d ", dp[i][j]);
                }
                printf("\n");
            }
        }
    }

    free(rods);
    return 0;
}

// Implementación recursiva
int recursive(int *rods, int n, int left, int right, int calls[]) {
    calls[0]++;
    if (left == right) return 0;

    int min_cost = INT_MAX;

    // Divide the rods into two parts and solve recursivelys (divide and conquer)
    for (int i = left; i < right; i++) {
        // Cost of welding all rods in the current range
        int left_cost = recursive(rods, n, left, i, calls);
        int right_cost = recursive(rods, n, i + 1, right, calls);
        
        // Store the current cost of the rods
        int current_cost = 0;
        for (int j = left; j <= right; j++) {
            current_cost += rods[j];
        }

        int total_cost = left_cost + right_cost + current_cost;

        if (total_cost < min_cost) {
            min_cost = total_cost;
        }
    }
    return min_cost;
}

// Implementación con memoization
int memoization(int *rods, int n, int left, int right, int **memo) {
    if (memo[left][right] != -1) return memo[left][right];
    if (left == right) return 0;

    int min_cost = INT_MAX;
    for (int i = left; i < right; i++) {
        // Cost of welding all rods into two par 
        int left_cost = memoization(rods, n, left, i, memo);
        int right_cost = memoization(rods, n, i + 1, right, memo);
              // Store the current cost of the rods
        int current_cost = 0;
        for (int j = left; j <= right; j++) {
            current_cost += rods[j];
        }

        int total_cost = left_cost + right_cost + current_cost;

        if (total_cost < min_cost) {
            min_cost = total_cost;
        }
    }
    memo[left][right] = min_cost;
    return min_cost;
}

int dynamic(int *rods, int n, int **dp) {
    
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

    // Calculate the minimum cost for all subproblems (welding rods between i and j
    for (int len = 2; len <= n; len++) {  // len is the subproblem size (start from 2 rods)
        for (int i = 0; i <= n - len; i++) {  // i is the starting rod index
            int j = i + len - 1;  // j is the ending rod index for the current subproblem
            
            dp[i][j] = INT_MAX;  // Initialize to a large number for comparison
            // Calculate the sum of rods in the range [i,j]
            int rod_sum = (i == 0) ? prefix_sum[j] : (prefix_sum[j] - prefix_sum[i - 1]);

            for (int k = i; k < j; k++) {  // k is the point of division
                // Cost is the sum of the two subproblems and the cost of welding the rods[i..k] and rods[k+1..j]
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
