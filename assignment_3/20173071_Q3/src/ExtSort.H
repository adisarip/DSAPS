
// Implementing External Sort Algorithm (using k-way merge sort)
// Inout File size can be huge and not fit in RAM

#ifndef EXTSORT_H
#define EXTSORT_H

#include <iostream>
#include <fstream>
using namespace std;

#define ll long long

class ExtSort
{
  public:
    ExtSort(string input, string output, int chunk);
    ~ExtSort();

    // function to perform external sort
    void sort();

  protected:
    void pSplitAndProcess();
    void pMergeFiles();
    void pMergeSort(ll data[], int left, int right);
    void pMerge(ll data[], int left, int mid, int right);
    void pWriteFile(ll* dataChunk, int size);

  private:
    string iFile;
    string oFile;
    int chunkSize;
    int fileCount;
};




#endif // EXTSORT_H
