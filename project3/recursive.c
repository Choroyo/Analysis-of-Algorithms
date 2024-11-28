#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Helper function to calculate the total length of rods in a range
int totalLength(int *rods, int start, int end) {
    int total = 0;
    for (int i = start; i <= end; i++) {
        total += rods[i];
    }
    return total;
}

// Divide-and-Conquer recursive function
int recursiveDivideAndConquer(int *rods, int start, int end, int calls[]) {
    calls[0]++; // Increment the recursive call counter

    // Base case: If there's only one rod, no cost is incurred
    if (start == end) return 0;

    int min_cost = INT_MAX;

    // Divide the rods into two parts and solve recursively
    for (int split = start; split < end; split++) {
        // Cost of welding all rods in the current range
        int left_cost = recursiveDivideAndConquer(rods, start, split, calls);
        int right_cost = recursiveDivideAndConquer(rods, split + 1, end, calls);
        int current_cost = totalLength(rods, start, end);

        // Combine the results
        int total_cost = left_cost + right_cost + current_cost;

        // Update the minimum cost
        if (total_cost < min_cost) {
            min_cost = total_cost;
        }
    }
    return min_cost;
}

int main() {
    int n;

    // Input: Number of rods
    printf("Enter the number of rods: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Number of rods must be greater than zero.\n");
        return 1;
    }

    // Allocate memory for rods array
    int *rods = (int *)malloc(n * sizeof(int));
    if (rods == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Input: Lengths of rods
    printf("Enter the lengths of the rods: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &rods[i]);
        if (rods[i] <= 0) {
            printf("Rod lengths must be positive integers.\n");
            free(rods);
            return 1;
        }
    }

    // Initialize the calls counter
    int calls[1] = {0};

    // Call the divide-and-conquer function
    int min_cost = recursiveDivideAndConquer(rods, 0, n - 1, calls);

    // Output results
    printf("Minimum galvanization cost: %d\n", min_cost);
    printf("Number of recursive calls: %d\n", calls[0]);

    // Free allocated memory
    free(rods);
    return 0;
}