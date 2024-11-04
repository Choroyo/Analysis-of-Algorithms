#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;

long long comparisons = 0; // Global variable for counting comparisons

// Insertion Sort
long long insertSort(vector<int>& A) {
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

void quickSortIterative(vector<int>& A, int low, int high) {
    // Use a stack to store subarray indexes
    vector<pair<int, int>> stack;
    stack.push_back({low, high});

    while (!stack.empty()) {
        pair<int, int> range = stack.back();
        stack.pop_back();
        int l = range.first, h = range.second;

        if (l < h) {
            int pi = partition(A, l, h);

            // Push smaller partition first to minimize stack usage
            if (pi - l < h - pi) {
                stack.push_back({pi + 1, h});
                stack.push_back({l, pi - 1});
            } else {
                stack.push_back({l, pi - 1});
                stack.push_back({pi + 1, h});
            }
        }
    }
}

long long quickSort(vector<int>& A) {
    comparisons = 0;
    quickSortIterative(A, 0, A.size() - 1);
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

long long mergeSort(vector<int>& A) {
    comparisons = 0;
    mergeSortRecursive(A, 0, A.size() - 1);
    return comparisons;
}

void ascend(vector<int>& A) {
    for (int i = 0; i < static_cast<int>(A.size()); i++) {
        A[i] = i + 1;
    }
}

void descend(vector<int>& A) {
    for (int i = 0; i < static_cast<int>(A.size()); i++) {
        A[i] = A.size() - i;
    }
}

void vee(vector<int>& A) {
    int mid = A.size() / 2;
    for (int i = 0; i < mid; i++) A[i] = A.size() - i * 2;
    for (int i = mid; i < static_cast<int>(A.size()); i++){ 
        A[i] = 2 * (i - mid) + 1;
    }
}

void zigzag(vector<int>& A) {
    int left = 1;
    int right = A.size();
    bool turn = true;

    for (int i = 0; i < static_cast<int>(A.size()); i++) {
        if (turn) {
           A[i] = right--; 
        } else {
            A[i] = left++;
        }
        turn = !turn;
    }
}

void randomData(vector<int>& A) {
    srand(time(0));
    for (int i = 0; i < static_cast<int>(A.size()); i++) {
        A[i] = rand() % A.size();
    }
}

// Sorting and data generation functions from previous sections...

void parseRun(int N, char dataType, char sortType) {
    vector<int> A(N);

    // Generate the data according to dataType
    if (dataType == 'A') {
        ascend(A);
    } else if (dataType == 'D') {
        descend(A);
    } else if (dataType == 'V') {
        vee(A);
    } else if (dataType == 'Z') {
        zigzag(A);
    } else if (dataType == 'R') {
        randomData(A);
    } else {
        cerr << "Invalid data type: " << dataType << endl;
        return;
    }

    // Perform the sorting and count comparisons
    long long comparisons = 0;
    if (sortType == 'I') {
        comparisons = insertSort(A);
    } else if (sortType == 'Q') {
        comparisons = quickSort(A);
    } else if (sortType == 'M') {
        comparisons = mergeSort(A);
    } else {
        cerr << "Invalid sort type: " << sortType << endl;
        return;
    }
    // Output the result
    cout << N << " " << dataType << " " << sortType << " " << comparisons << endl << flush;

}



int main(int argc, char* argv[]) {
    
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <controlfile.txt>" << endl;
        return 1;
    }

    string controlFile = argv[1];
    ifstream file(controlFile);
    
    if (!file.is_open()) {
        cerr << "Error opening control file: " << controlFile << endl;
        return 1;
    }

    int numRuns;
    if(!(file >> numRuns) || numRuns <= 0) {
        cerr << "Invalid or missing of runs in control file." << endl;
        return 1;
    }

    for (int i = 0; i < numRuns; ++i) {
        int N;
        char dataType, sortType;

        if (!(file >> N >> dataType >> sortType)){
            cerr << "Error reading run specifications in control file." << (i + 2) << endl;
            return 1;
        }

         if (N <= 0) { // Validate data size
            cerr << "Invalid data size (N) on line " << (i + 2) << ". Expected positive integer." << endl;
            return 1;
        }

        if (dataType != 'A' && dataType != 'D' && dataType != 'V' && dataType != 'Z' && dataType != 'R') {
            cerr << "Invalid data type on line " << (i + 2) << ". Expected 'A', 'D', 'V', 'Z', or 'R'." << endl;
            return 1;
        }

        if (sortType != 'M' && sortType != 'Q' && sortType != 'I') {
            cerr << "Invalid sort type on line " << (i + 2) << ". Expected 'M', 'Q', or 'I'." << endl;
            return 1;
        }

        // Parse each run as per the specifications
        auto start = std::chrono::high_resolution_clock::now();
        parseRun(N, dataType, sortType);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        cout << "Run time: " << duration.count() << " seconds" << endl;
    }
    
    file.close();

    return 0;
}