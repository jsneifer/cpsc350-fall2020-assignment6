#include <iostream>
using namespace std;

class Sort {
  public:
    Sort();
    Sort(string file);
    ~Sort();

    void quickSort(int lowIndex, int highIndex);
    int Partition(int lowIndex, int highIndex);

    void mergeSort(int i, int k);
    void Merge(int i, int j, int k);

    void selectionSort();
    void insertionSort();
    void bubbleSort();

    void runSorts(); //Runs each function and prints out times
    void setCopy(); //Sets copy equal to the unsorted array to use again
    void printCopy();
  private:
    double *unsorted;
    double *copy;
    int size;
};
