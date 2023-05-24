/* SOURCES
* https://learn.zybooks.com/zybook/UCRCS010CSpring2021/chapter/5/section/8
* https://learn.zybooks.com/zybook/UCRCS010CSpring2021/chapter/5/section/10
*/

#include <iostream> 
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std; 

const int CLOCKS_PER_MS = CLOCKS_PER_SEC/1000; // clock per milliseconds
const int NUMBERS_SIZE = 50000; 

/* This fct sorts the given array in the range from i to k using quicksort
method. In this fct, pivot is the midpoint element (numbers[(i+k)/2]). 
Implementation of this fct is given in section 21.5 */
void Quicksort_midpoint(int numbers[], int i, int k);
/* This fct utilizes different pivot selection technique in quicksort alg. 
The pivot is the median of the following 3 values: leftmost(numbers[i]),
midpoint(numbers[(i+k)/2]) & rightmost(numbers[k]). You should modify the 
partition fct given in section 21.5 to select the pivot using the 
median-of-three technique */
void Quicksort_medianOfThree(int numbers[], int i, int k);
/* This fct sorts the given array using InsertionSort method. Implementation
of this method is provided in section 21.3 */
void InsertionSort(int numbers[], int numbersSize);

int Partition(int numbers[], int pivot, int i, int k);
int medianPartition(int numbers[], int i, int k);

// Generates 3 similar arrays of random integers
int genRandInt(int low, int high);
void fillArrays(int arr1[], int arr2[], int arr3[]);

int main() {
  int arr1[NUMBERS_SIZE];
  int arr2[NUMBERS_SIZE];
  int arr3[NUMBERS_SIZE]; 

  fillArrays(arr1, arr2, arr3); 

  clock_t Start = clock();
  Quicksort_midpoint(arr1, 0, NUMBERS_SIZE-1);
  clock_t End = clock();
  // converts elapsed time from microseconds to milliseconds
  double elapsedTime = (double)(End - Start) / CLOCKS_PER_MS; 
  cout << "elapsed time (quicksort: midpoint): " << elapsedTime << endl; 

  Start = clock();
  InsertionSort(arr2, NUMBERS_SIZE);
  End = clock();
  elapsedTime = (double)(End - Start) / CLOCKS_PER_MS;
  cout << "elapsed time (insertion sort): " << elapsedTime << endl; 

  Start = clock();
  Quicksort_medianOfThree(arr3, 0, NUMBERS_SIZE-1);
  End = clock(); 
  elapsedTime = (double)(End - Start) / CLOCKS_PER_MS;
  cout << "elapsed time (quicksort: median of 3): " << elapsedTime << endl; 


  return 0;
}

// https://learn.zybooks.com/zybook/UCRCS010CSpring2021/chapter/5/section/10
void Quicksort_midpoint(int numbers[], int i, int k) {
  int pivotPosition;
  int midpoint = i + (k - i) / 2; 
  int pivot = numbers[midpoint];

  if (i >= k) {
    return;
  }

  pivotPosition = Partition(numbers, pivot, i, k);
  Quicksort_midpoint(numbers, i, pivotPosition);
  Quicksort_midpoint(numbers, pivotPosition + 1, k);
}

int Partition(int numbers[], int pivot, int i, int k) {
  // Pick middle element as pivot
  // int midpoint = i + (k - i) / 2;
  // int pivot = numbers[midpoint];
  bool isDone = false; 

  while (!isDone) {
    // Increment low index while numbers[i] < pivot
    while (numbers[i] < pivot) {
      ++i; 
    }

    // Decrement high index while pivot < numbers[k]
    while (pivot < numbers[k]) {
      --k; 
    }

    // If zero or one elements remain, then all numbers are partitioned.
    // Return high index
    if (i >= k) {
      isDone = true;
    }
    else {
      // Swap numbers[i] & numbers[k]
      swap(numbers[i], numbers[k]);

      // Update low and high index
      ++i; 
      --k; 
    }
  }

  // Return high index (the highest index of the low partition)
  return k; 
}

void Quicksort_medianOfThree(int numbers[], int i, int k) {
  int pivotPosition; 

  if (i >= k) {
    return;
  }

  pivotPosition = medianPartition(numbers, i, k);
  Quicksort_medianOfThree(numbers, i, pivotPosition);
  Quicksort_medianOfThree(numbers, pivotPosition + 1, k);
}

int medianPartition(int numbers[], int i, int k) {
  int left = i;
  int right = k;
  int pivot;
  int center = left + (right - left) / 2;

  if (numbers[center] < numbers[left]) {
    swap(numbers[center], numbers[left]);
  }

  if (numbers[right] < numbers[left]) {
    swap(numbers[right], numbers[left]);
  }

  if (numbers[right] < numbers[center]) {
    swap(numbers[right], numbers[center]);  
  }

  swap(numbers[center], numbers[right - 1]);

  pivot = numbers[right-1];

  return Partition(numbers, pivot, i, right - 1);
}

// https://learn.zybooks.com/zybook/UCRCS010CSpring2021/chapter/5/section/8
void InsertionSort(int numbers[], int numbersSize) {
  int i = 0; 
  int j = 0; 

  for (i = 1; i < numbersSize; ++i) {
    j = i; 
    // Insert numbers[i] into sorted part
    // Stop once numbers[i] is in correct position 
    while (j > 0 && numbers[j] < numbers[j-1]) {
      swap(numbers[j], numbers[j-1]); 
      --j; 
    }
  }
}

int genRandInt(int low, int high) {
  return low + rand() % (high - low + 1);
}

void fillArrays(int arr1[], int arr2[], int arr3[]) {
  for (int i = 0; i < NUMBERS_SIZE; ++i) {
    arr1[i] = genRandInt(0, NUMBERS_SIZE);
    arr2[i] = arr1[i];
    arr3[i] = arr1[i];
  }
}
