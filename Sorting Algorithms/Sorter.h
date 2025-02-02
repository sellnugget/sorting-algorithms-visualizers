#pragma once
#include <vector>
#include <functional>
#include <chrono>
#include <thread>
template<typename type>
class Sorter {

public:
    int currentSelection;
    std::vector<type> array;
    std::function<bool(type, type)> Compare;
    void SortThread(std::function<bool(type, type)> compare);
    int LagSkips = 1;
  

private:

    int LagCounter = 0;
    void Lag(int index);
    type ReadArray(int index);
    void WriteArray(int index, type value);
    void InsertArray(int index, type value);
    void EraseArray(int index);
    void SwapIndex(int a, int b);
    int ArraySize();
    void BubbleSort();
    void QuickSort();
    void SelectionSort();
    void InsertionSort();
    void Merge(int start, int end);
    void MergeSort();
};

template<typename type>
void Sorter<type>::SortThread(std::function<bool(type, type)> compare)
{
    Compare = compare;
    std::function<void()> func = [this]() {this->InsertionSort(); };
    std::thread current(func);
    current.detach();
}
template<typename type>
void Sorter<type>::BubbleSort()
{
    for (int i = 0; i < ArraySize(); i++) {
        for (int j = i; j < ArraySize(); j++) {


            type valueA = ReadArray(i);
            type valueB = ReadArray(j);
            if (Compare(valueA, valueB)) {
                SwapIndex(i, j);
            }
        }
    }
    while (true) {

    }
}
template<typename type>
inline void Sorter<type>::Lag(int index)
{
 
    currentSelection = index;
 
    if (LagCounter == LagSkips) {
        std::this_thread::sleep_for(std::chrono::microseconds(1));
        LagCounter = 0;
    }
    else {
        LagCounter++;
    }
  
}
template<typename type>
type Sorter<type>::ReadArray(int index)
{
    Lag(index);
    if (index >= ArraySize()) {
        throw;
    }
    return array[index];
}
template<typename type>
void Sorter<type>::WriteArray(int index, type value)
{
    Lag(index);
    if (index >= ArraySize()) {
        throw;
    }
    array[index] = value;
}
template<typename type>
void Sorter<type>::InsertArray(int index, type value)
{
    Lag(index);
    if (index >= ArraySize()) {
        throw;
    }
    array.insert(array.begin() + index, value);
}
template<typename type>
void Sorter<type>::EraseArray(int index)
{
    Lag(index);
    if (index >= ArraySize()) {
        throw;
    }
    array.erase(array.begin() + index);
}
template<typename type>
void Sorter<type>::SwapIndex(int a, int b)
{
    if (a >= ArraySize() || b >= ArraySize()) {
        throw;
    }
    type valueA = ReadArray(a);
    type valueB = ReadArray(b);
    WriteArray(a, valueB);
    WriteArray(b, valueA);
}
template<typename type>
int Sorter<type>::ArraySize()
{
    return array.size();
}
template<typename type>
void Sorter<type>::SelectionSort() {

    int smallestItem;
    for (int FirstUnsorted = 0; FirstUnsorted < ArraySize(); FirstUnsorted++) {

        smallestItem = FirstUnsorted;
        for (int i = FirstUnsorted; i < ArraySize(); i++) {
            if (!Compare(ReadArray(i), ReadArray(smallestItem))) {
                smallestItem = i;
            }
        }
        type unsorted = ReadArray(FirstUnsorted);

        WriteArray(FirstUnsorted, ReadArray(smallestItem));
        WriteArray(smallestItem, unsorted);
    }
}
template<typename type>
void Sorter<type>::InsertionSort() {

    for (int i = 1; i < ArraySize(); i++) {

        for (int j = 0; j < i; j++) {

            if (!Compare(ReadArray(i), ReadArray(j))) {
                InsertArray(j, ReadArray(i));
                EraseArray(i + 1);
                break;
            }
        }
    }
}




/*

template<typename type>
void Sorter<type>::MergeSort() {

    if (ArraySize() <= 1) {
        return;
    }
    std::vector< leftsize = ArraySize() / 2;
    int rightsize = ArraySize() / 2 + ArraySize() % 2;
    if (list.size() / 2 > 1) {
        Merge(0, leftsize);
        Merge(ArraySize() / 2 + 1, rightsize);
    }

    int j = 0;
    int k = 0;
    int index = 0;
    while (index < ArraySize()) {

        if (k >= right.size()) {
            list[index] = left[j];
            index++;
            j++;
        }
        else if (j >= left.size()) {
            list[index] = right[k];
            k++;
            index++;
        }
        else if (compare(left[j], right[k])) {
            list[index] = left[j];
            index++;
            j++;
        }
        else {
            list[index] = right[k];
            k++;
            index++;
        }
    }


}





*/
