# MultiThreaded Sort Benchmark

### Description
This project demonstrates a multi-threaded bubble sort algorithm in C++, designed to sort up to 1,000,000 numbers using 16 threads. It benchmarks the custom sorting algorithm against the system’s built-in sort using a shell script optimized for macOS.

### Files Included
- **`mysort.cpp`** – Multi-threaded bubble sort implementation.
- **`generate.cpp`** – Random number generator.
- **`sortrace.sh`** – Benchmark automation script.
- **`numbers.dat`** – Randomly generated input data.
- **`sortrace.log`** -Output of program

---

### How to Run

1. **Grant Execute Permission to the Script**

   chmod +x sortrace.sh
2. **Compile the random number generator**

   g++ generate.cpp -o generate
3. **Compile the multi-threaded sort program**

   g++ mysort.cpp -o mysort -pthread
4. **Run the Benchmark Script**

   ./sortrace.sh >> sortrace.log &
5. **Monitor the Log File**

   tail -f sortrace.log

## Requirements 

macOS (or Linux with minor adjustments) 

g++ compiler supporting C++11 or newer 

Sufficient RAM for sorting large data sets (1,000,000 integers)




