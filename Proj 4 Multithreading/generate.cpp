// Name: Mario Robles
// Class (CECS 325-02)
// Project Name (Prog 4 – Threads)
// Due Date (10/31/2024)
//
// I certify that this program is my own original work. I did not copy any part of this program from
// any other source. I further certify that I typed each and every line of code in this program.
#include <iostream>
#include <fstream>
#include <cstdlib>  // For rand and srand
using namespace std;

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments are provided
    if (argc != 4) {
        cout << "Please enter 3 parameters: \n";
        cout << "   Parameter 1: total count of numbers you want \n";
        cout << "   Parameter 2: min value. \n";
        cout << "   Parameter 3: max value. \n";
        cout << "Example: $ generate 1000000  100000 999999\n";
        exit(EXIT_SUCCESS);
    }

    // Print the command-line arguments
    //for (int i = 0; i < argc; i++) {
        //cout << "argv[" << i << "]:" << argv[i] << endl;
    //}

    // Convert arguments to integers using stoi
    int COUNT = stoi(argv[1]);
    int MIN = stoi(argv[2]);
    int MAX = stoi(argv[3]);

    // Open the output file numbers.dat for writing
    ofstream fout("numbers.dat");
    if (!fout) {
        cout << "Error: Could not open numbers.dat for writing.\n";
        return 1;
    }

    // Seed the random number generator
    srand(time(0));

    // Generate random numbers in the range [MIN, MAX] and write them to the file
    for (int i = 0; i < COUNT; i++) {
        fout << (rand() % (MAX - MIN + 1) + MIN) << endl;
    }

    fout.close();  // Close the file
    return 0;
}
