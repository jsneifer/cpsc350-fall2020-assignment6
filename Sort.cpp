#include "Sort.h"
#include <fstream>
#include <ctime>
#include <stdlib.h>
#include <iomanip>


Sort::Sort() {
  size = 10000;
  unsorted = new double[size];
  copy = new double[size];
  for(int i = 0; i < size; ++i) {
    unsorted[i] = ((double)rand() / RAND_MAX) * 100;
  }
}

Sort::Sort(string file) {
  ifstream newFile;
  double val = 0.0;
  int index = 0;
  newFile.open(file);
  if(newFile.is_open()) {
    newFile >> size;
    unsorted = new double[size];
    copy = new double[size];
    while(newFile >> val) {
      unsorted[index] = val;
      ++index;
    }
  } else {
    cout << "\nThis not a valid input file";
    exit(1);
  }
}

Sort::~Sort() {
  delete unsorted;
  delete copy;
}


void Sort::runSorts() {
  clock_t start;
  double duration;
  cout << std::fixed;
  cout << std::setprecision(5);
  setCopy();
  cout << "\nRUNNING SORTING ALGORITHMS... " << endl;
  //printCopy();

  cout << "\nRUNNING QUICK SORT...";
  start = clock();
  quickSort(0, size - 1);
  duration = (clock() - start) / (double) CLOCKS_PER_SEC;
  cout << "\nQuick Sort: \nTook " << duration << "s" << endl;
  //cout << "Sorted List: " << endl;
  //printCopy();

  setCopy();
  cout << "\nRUNNING MERGE SORT... ";
  start = clock();
  mergeSort(0, size - 1);
  duration = (clock() - start) / (double) CLOCKS_PER_SEC;
  cout << "\nMerge Sort: \nTook " << duration << "s" << endl;
  //cout << "Sorted List: " << endl;
  //printCopy();

  setCopy();
  cout << "\nRUNNING SELECTION SORT... ";
  start = clock();
  selectionSort();
  duration = (clock() - start) / (double) CLOCKS_PER_SEC;
  cout << "\nSelection Sort: \nTook " << duration << "s" << endl;
  //cout << "Sorted List: " << endl;
  //printCopy();

  setCopy();
  cout << "\nRUNNING INSERTION SORT... ";
  start = clock();
  insertionSort();
  duration = (clock() - start) / (double) CLOCKS_PER_SEC;
  cout << "\nInsertion Sort: \nTook " << duration << "s" << endl;
  //cout << "Sorted List: " << endl;
  //printCopy();

  setCopy();
  cout << "\nRUNNING BUBBLE SORT... ";
  start = clock();
  bubbleSort();
  duration = (clock() - start) / (double) CLOCKS_PER_SEC;
  cout << "\nBubble Sort: \nTook " << duration << "s\n" << endl;
  //cout << "Sorted List: " << endl;
  //printCopy();
}

void Sort::setCopy() {
  for(int i = 0; i < size; i++) {
    copy[i] = unsorted[i];
  }
}

void Sort::printCopy() {
  cout << "[";
  for(int j = 0; j < size; ++j) {
    cout << copy[j] << ", ";
  }
  cout << "]" << endl;
}

void Sort::quickSort(int lowIndex, int highIndex) {
  if(lowIndex >= highIndex) {
    return;
  }

  int lowEndIndex = Partition(lowIndex, highIndex);

  quickSort(lowIndex, lowEndIndex);
  quickSort(lowEndIndex + 1, highIndex);
}

int Sort::Partition(int lowIndex, int highIndex) {
  int midpoint = lowIndex + (highIndex - lowIndex) / 2;
  double pivot = copy[midpoint];
  double temp = 0;

  bool done = false;
  while(!done) {
    while(copy[lowIndex] < pivot) {
      lowIndex += 1;
    }

    while(pivot < copy[highIndex]) {
      highIndex -= 1;
    }

    if(lowIndex >= highIndex) {
      done = true;
    } else {
      temp = copy[lowIndex];
      copy[lowIndex] = copy[highIndex];
      copy[highIndex] = temp;
    }
  }
  return highIndex;
}

void Sort::mergeSort(int i, int k) {
  int j = 0;

  if(i < k) {
    j = (i + k) / 2;

    mergeSort(i, j);
    mergeSort(j + 1, k);
    Merge(i, j, k);

  }
}

void Sort::Merge(int i, int j, int k) {
  int mergedSize = k - i + 1;
  int mergePos = 0;
  int leftPos = 0;
  int rightPos = 0;
  double *mergedNumbers = new double[mergedSize];

  leftPos = i;
  rightPos = j + 1;

  while(leftPos <= j && rightPos <= k) {
    if(copy[leftPos] <= copy[rightPos]) {
      mergedNumbers[mergePos] = copy[leftPos];
      ++leftPos;
    } else {
      mergedNumbers[mergePos] = copy[rightPos];
      ++rightPos;
    }
    ++mergePos;
  }

  while(leftPos <= j) {
    mergedNumbers[mergePos] = copy[leftPos];
    ++leftPos;
    ++mergePos;
  }

  while(rightPos <=k) {
    mergedNumbers[mergePos] = copy[rightPos];
    ++rightPos;
    ++mergePos;
  }

  for(mergePos = 0; mergePos < mergedSize; ++mergePos) {
    copy[i + mergePos] = mergedNumbers[mergePos];
  }
}

void Sort::selectionSort() {
  int i = 0;
  int j = 0;
  int indexSmallest = 0;
  double temp;

  for(i = 0; i < size - 1; ++i) {
    indexSmallest = i;
    for(j = i + 1; j < size; ++j) {
      if(copy[j] < copy[indexSmallest]) {
        indexSmallest = j;
      }
    }
    temp = copy[i];
    copy[i] = copy[indexSmallest];
    copy[indexSmallest] = temp;
  }
}

void Sort::insertionSort() {
  int i = 0;
  int j = 0;
  double temp = 0;

  for(i = 1; i < size; ++i) {
    j = i;
    while(j > 0 && copy[j] < copy[j - 1]) {
      temp = copy[j];
      copy[j] = copy[j - 1];
      copy[j - 1] = temp;
      --j;
    }
  }
}

void Sort::bubbleSort() {
  double temp;
  bool swapped = true;
  while(swapped) {
    swapped = false;
    for(int i = 0; i < size - 1; ++i) {
      if(copy[i] > copy[i+1]) {
        temp = copy[i];
        copy[i] = copy[i+1];
        copy[i+1] = temp;
        swapped = true;
      }
    }
  }
}
