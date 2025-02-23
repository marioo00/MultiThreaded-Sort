// Name: Mario Robles
// Class (CECS 325-02)
// Project Name (Prog 4 – Threads)
// 
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.
#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx; 
long long globalSwapCount = 0; // Global variable to track total swaps
int* numbers; // Pointer for dynamically allocated array


void bubble(int* arr, int size, int threadID); // Bubble sort for each section
void mergeSections(int* arr, int start, int mid, int end); // Merging sorted sections

int main(int argc, char* argv[]) {
    // Handle command-line arguments
    if (argc < 3) {
        cerr << "Error: Provide input file and output file.\n";
        exit(EXIT_FAILURE);
    }

    string inputFile = argv[1];
    string outputFile = argv[2];
    int numElements = (argc == 4 && string(argv[3]) == "-test") ? 10000 : 1000000;

    // Allocate memory for the array
    numbers = new int[numElements];

    // Open and read numbers from input file
    ifstream inFile(inputFile);
    if (!inFile) {
        cerr << "Error: Cannot open file " << inputFile << endl;
        delete[] numbers;
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < numElements; ++i) {
        inFile >> numbers[i];
    }
    inFile.close();

    // Create threads for sorting sections
    const int threadSize = 16;
    int elementsPerThread = numElements / threadSize;
    thread threads[threadSize];
    for (int i = 0; i < threadSize; ++i) {
        int begin = i * elementsPerThread;
        threads[i] = thread(bubble, numbers + begin, elementsPerThread, i);
    }

    // Join threads
    for (int i = 0; i < threadSize; ++i) {
        threads[i].join();
    }

    // Merge sorted sections 
    int currentSections = threadSize;
    int sectionSize = elementsPerThread;
    while (currentSections > 1) {
        for (int i = 0; i < currentSections / 2; ++i) {
            int start = i * sectionSize * 2;
            int mid = start + sectionSize - 1;
            int end = (i == (currentSections / 2 - 1)) ? numElements - 1 : start + sectionSize * 2 - 1;
            mergeSections(numbers, start, mid, end);
        }
        currentSections /= 2;
        sectionSize *= 2;
    }

    // Write sorted array to output file
    ofstream outFile(outputFile);
    if (!outFile) {
        cerr << "Error: Cannot open file " << outputFile << endl;
        delete[] numbers;
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < numElements; ++i) {
        outFile << numbers[i] << "\n";
    }
    outFile.close();

    // Print the total swap count to match the expected format
    cout << "Total Swaps: " << globalSwapCount << endl;

    delete[] numbers;

    return 0;
}

// Bubble sort function for each thread to sort a section of the array
void bubble(int* arr, int size, int threadID) {
    int localSwapCount = 0;

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                localSwapCount++;
            }
        }
    }

    // Lock mutex and update the global swap count
    lock_guard<mutex> guard(mtx);
    globalSwapCount += localSwapCount;
    cout << "Process " << threadID << " swap count: " << localSwapCount << endl << flush;
}

// Function to merge two sorted sections of the array
void mergeSections(int* arr, int start, int mid, int end) {
    int n1 = mid - start + 1;
    int n2 = end - mid;

    // Temporary arrays to hold the two halves
    int* left = new int[n1];
    int* right = new int[n2];

    // Copy data to temporary arrays
    for (int i = 0; i < n1; ++i) left[i] = arr[start + i];
    for (int i = 0; i < n2; ++i) right[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = start;

    // Merge the temp arrays back into arr
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }

    // Copy any remaining elements of left[]
    while (i < n1) {
        arr[k++] = left[i++];
    }

    // Copy any remaining elements of right[]
    while (j < n2) {
        arr[k++] = right[j++];
    }

    // Free temporary arrays
    delete[] left;
    delete[] right;
}
