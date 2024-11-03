#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

long comparisons = 0; // Global variable for counting comparisons

cout << "hello word";

// Insertion Sort
long insertSort(vector<int>& A) {
    comparisons = 0;
    int N = A.size();
    for (int i = 1; i < N; i++) {
        int key = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            j--;
            comparisons++;
        }
        A[j + 1] = key;
        comparisons++;
    }
    return comparisons;
}

// Quick Sort
int partition(vector<int>& A, int low, int high) {
    int pivot = A[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (A[j] < pivot) {
            i++;
            swap(A[i], A[j]);
        }
        comparisons++;
    }
    swap(A[i + 1], A[high]);
    return i + 1;
}

void quickSortRecursive(vector<int>& A, int low, int high) {
    if (low < high) {
        int pi = partition(A, low, high);
        quickSortRecursive(A, low, pi - 1);
        quickSortRecursive(A, pi + 1, high);
    }
}

long quickSort(vector<int>& A) {
    comparisons = 0;
    quickSortRecursive(A, 0, A.size() - 1);
    return comparisons;
}

// Merge Sort
void merge(vector<int>& A, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = A[left + i];
    for (int i = 0; i < n2; i++) R[i] = A[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
        comparisons++;
    }

    while (i < n1) A[k++] = L[i++];
    while (j < n2) A[k++] = R[j++];
}

void mergeSortRecursive(vector<int>& A, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortRecursive(A, left, mid);
        mergeSortRecursive(A, mid + 1, right);
        merge(A, left, mid, right);
    }
}

long mergeSort(vector<int>& A) {
    comparisons = 0;
    mergeSortRecursive(A, 0, A.size() - 1);
    return comparisons;
}