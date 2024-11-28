#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

// Declaración de funciones
int recursive(int *rods, int n, int left, int right, int calls[]);
int memoization(int *rods, int n, int left, int right, int **memo);
int dynamic(int *rods, int n);

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
        if (method == 'D') {
            printf("%d\n", dynamic(rods, n));
        } else {
            // Imprimir tabla dinámica
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

// Implementación dinámica
int dynamic(int *rods, int n) {
    int dp[n][n];
    memset(dp, -1, sizeof(dp));

    for (int len = 1; len <= n; len++) {
        for (int i = 0; i <= n - len; i++) {
            int j = i + len - 1;
            if (i == j) dp[i][j] = 0;
            else {
                dp[i][j] = INT_MAX;
                for (int k = i; k < j; k++) {
                    int cost = rods[i] + rods[j] + dp[i][k] + dp[k + 1][j];
                    if (cost < dp[i][j]) dp[i][j] = cost;
                }
            }
        }
    }
    return dp[0][n - 1];
}
