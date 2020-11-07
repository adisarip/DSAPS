

#include "ExtSort.H"
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

ExtSort::ExtSort(string input,
                 string output,
                 int chunk)
:iFile(input)
,oFile(output)
,chunkSize(chunk)
,fileCount(0)
{
}

ExtSort::~ExtSort()
{
}


void ExtSort::sort()
{
    pSplitAndProcess();
    pMergeFiles();
}

void ExtSort::pSplitAndProcess()
{
    // read the input file till chunkSize is reached and process it
    ifstream fin;
    fin.open(iFile, ios::in);
    string value;
    int index = 0;
    fileCount = 1;

    // create an array to store numbers for merge sort
    // this dataChunk will be cleared once the numbers are sorted and flushed to a file
    ll* dataChunk = new ll[chunkSize]{};

    while (fin)
    {
        getline(fin, value, ',');
        if (index < chunkSize)
        {
            dataChunk[index++] = stoll(value);
            continue;
        }

        // perform in-place merge sort on the data array
        pMergeSort(dataChunk, 0, index-1);

        // write the sorted part-data into a file
        pWriteFile(dataChunk, chunkSize);
        memset(dataChunk, 0, chunkSize * sizeof(ll));

        fileCount++;
        index = 0;
    }

    if (index > 0)
    {
        pMergeSort(dataChunk, 0, index-1);
        pWriteFile(dataChunk, index);
        index = 0;
    }

    fin.close();
    delete[] dataChunk;
}

void ExtSort::pMergeFiles()
{
}

void ExtSort::pMergeSort(ll data[], int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        pMergeSort(data, left, mid);
        pMergeSort(data, mid+1, right);
        pMerge(data, left, mid, right);
    }
}

void ExtSort::pMerge(ll data[], int left, int mid, int right)
{
    int leftCount = mid - left + 1;
    int rightCount = right - mid;
    ll leftData[leftCount];
    ll rightData[rightCount];

    for (int i=0; i < leftCount; i++)
    {
        leftData[i] = data[leftCount + i];
    }
    for (int j=0; j < rightCount; j++)
    {
        rightData[j] = data[mid + 1];
    }

    int i = 0;
    int j = 0;
    int k = left;
    while(i < leftCount && j < rightCount)
    {
        if (leftData[i] <= rightData[j])
        {
            data[k++] = leftData[i++];
        }
        else
        {
            data[k++] = rightData[j++];
        }
    }
    while (i < leftCount)
    {
        data[k++] = leftData[i++];
    }
    while (i < rightCount)
    {
        data[k++] = rightData[j++];
    }
}

void ExtSort::pWriteFile(ll dataChunk[], int size)
{
    string filename = string("./data/") + to_string(fileCount);
    ofstream fout(filename.c_str());
    for (int i=0; i < size; i++)
    {
        if (i == size-1)
        {
            fout << dataChunk[i];
        }
        else
        {
            fout << dataChunk[i] << ",";
        }
    }
    fout.close();
}
