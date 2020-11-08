

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <climits>
using namespace std;

#define ll long long

// A min heap node for k-way merging
struct Node
{
    int index; // array index
    ll  value; // value
};

class MinHeap
{
  public:
    MinHeap(Node a[], int n);
    ~MinHeap();
    int getLeftIndex(int level);  // get the index of left child
    int getRightIndex(int level); // get the index of right child
    Node getMinNode();            // get the next minimum node
    void replaceMinNode(Node node);        // replace the current minimum node with the next minimum from the file

  protected:
    void pHeapify(int index); // heapify the array of elements

  private:
    int size;
    Node* heap;
};

MinHeap::MinHeap(Node a[], int n)
:size(n)
,heap(a)
{
    int index = (size - 1) / 2;
    while (index >= 0)
    {
        pHeapify(index);
        index--;
    }
}

MinHeap::~MinHeap()
{
    delete[] heap;
    size = 0;
}

int  MinHeap::getLeftIndex(int level)
{
    return (2*level + 1);
}

int  MinHeap::getRightIndex(int level)
{
    return (2*level + 2);
}

Node MinHeap::getMinNode()
{
    return heap[0];
}

void MinHeap::replaceMinNode(Node node)
{
    heap[0] = node;
    pHeapify(0);
}

// Protected members definitions

void MinHeap::pHeapify(int index)
{
    int left = getLeftIndex(index);
    int right = getRightIndex(index);
    int smallest = index;

    if (left < size && heap[left].value < heap[index].value)
    {
        smallest = left;
    }
    if (right < size && heap[right].value < heap[smallest].value)
    {
        smallest = right;
    }
    if (smallest != index)
    {
        // swap the smallest node with the current index
        Node x = heap[index];
        heap[index] = heap[smallest];
        heap[smallest] = x;

        // heapify the min heap
        pHeapify(smallest);
    }
}


// Implementing External Sort Algorithm (using k-way merge sort)
// Inout File size can be huge and not fit in RAM

class ExtSort
{
  public:
    ExtSort(string input, string output, int chunk);
    ~ExtSort();

    // function to perform external sort
    void sort();
    void cleanup();

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

void ExtSort::cleanup()
{
    // clean all the temporary files created
    string cmd = "rm ./data/*.dat";
    system(cmd.c_str());
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
    fileCount = 0;
    bool inputFlag = true;

    // create an array to store numbers for merge sort
    // this dataChunk will be cleared once the numbers are sorted and flushed to a file
    ll* dataChunk = new ll[chunkSize]{};

    while (inputFlag)
    {
        int index = 0;
        while (index < chunkSize)
        {
            if (!fin.eof())
            {
                getline(fin, value, ',');
                dataChunk[index] = stoll(value);
            }
            else
            {
                inputFlag = false;
                break;
            }
            index++;
        }

        if (index > 0)
        {
            fileCount++;
            // perform merge sort on the data array
            pMergeSort(dataChunk, 0, index-1);
            // write the sorted part-data into a file
            pWriteFile(dataChunk, index);
            memset(dataChunk, 0, chunkSize * sizeof(ll));
        }
    }

    fin.close();
    delete[] dataChunk;
}

void ExtSort::pMergeFiles()
{
    ifstream fin[fileCount];
    Node* heapArray = new Node[fileCount];

    string sValue("");
    int currentIndex;
    // open the intermediate files and get the minimum element from each file to create the heap
    for (currentIndex=0; currentIndex < fileCount; currentIndex++)
    {
        string filename = string("./data/") + to_string(currentIndex+1) + string(".dat");
        fin[currentIndex].open(filename, ios::in);
        if (!fin[currentIndex].eof())
        {
            getline(fin[currentIndex], sValue, ',');
            heapArray[currentIndex].value = stoll(sValue);
            heapArray[currentIndex].index = currentIndex;
        }
        else
        {
            break;
        }
    }

    // create the min heap
    MinHeap minHeap(heapArray, currentIndex);

    ofstream fout(oFile.c_str());
    sValue = "";
    bool isFirst = true;
    // one-by-one get minimum element from min heap and replace it with the next element
    for (int eofCount=0; eofCount != currentIndex;)
    {
        Node node = minHeap.getMinNode();
        if (isFirst)
        {
            fout << node.value;
            isFirst = false;
        }
        else
        {
            fout << "," << node.value;
        }

        if (!fin[node.index].eof())
        {
            getline(fin[node.index], sValue, ',');
            node.value = stoll(sValue);
        }
        else
        {
            eofCount++;
            node.value = LLONG_MAX;
            fout.flush();
        }

        minHeap.replaceMinNode(node);
    }

    for (int i=0; i<fileCount; i++)
    {
        fin[i].close();
    }
    fout << endl;
    fout.close();
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
        leftData[i] = data[left + i];
    }
    for (int j=0; j < rightCount; j++)
    {
        rightData[j] = data[mid + 1 + j];
    }

    int i = 0, j = 0;
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

    // copy the remaining elements
    while (i < leftCount)
    {
        data[k++] = leftData[i++];
    }
    while (j < rightCount)
    {
        data[k++] = rightData[j++];
    }
}

void ExtSort::pWriteFile(ll dataChunk[], int size)
{
    string filename = string("./data/") + to_string(fileCount) + string(".dat");
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

// ================================= Driver Program =================================

void printHelp()
{
    cout << "USAGE:" << endl;
    cout << "      ./bin/esort <input_file> <output_file> [partion_size]" << endl;
    cout << "Ex:   ./bin/esort ./data/input.txt ./data/sorted_input.txt" << endl;
    cout << "Ex:   ./bin/esort ./data/input.txt ./data/sorted_input.txt 20" << endl;
    cout << "NOTE: partion_size is the maximum number of elements that each partition will have." << endl;
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        cout << "[Error] Invalid Command !!!" << endl;
        printHelp();
        return 1;
    }

    string input_file  = argv[1];
    string output_file = argv[2];
    int partion_size = (argc == 4) ? stoi(argv[3]) : 1000;
    ExtSort data(input_file, output_file, partion_size);
    data.sort();
    data.cleanup();
    return 0;
}
