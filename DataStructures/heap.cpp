// Max-Heap data structure in C++

#include <iostream>
#include <vector>
using namespace std;

void printArray(vector<int> &hT)
{
    for (int i = 0; i < hT.size(); ++i)
        cout << hT[i] << " ";
    cout << "\n";
}


void customSwap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void heapify(vector<int> &arr){
    // Build heap
    int arr_size = arr.size();
    int idx_start = arr_size/2-1;
    for(int j=idx_start;j>=0;j--){
        int i = j;
        // actual heapify logic
        int largest = i;
        int left = 2*i+1;
        int right = 2*i+2;
        while(true){
            if(left<arr_size && arr[i]<arr[left]) 
                largest = left;
            if(right<arr_size && arr[i]<arr[right]) 
                largest = right;
            if(i != largest){
                customSwap(arr[i],arr[largest]);
                i = largest;
                left = i*2+1;
                right = i*2+2;
            }
            else {
                break;
            }
        }
    }
}

void insert(vector<int> &arr, int val){
    arr.push_back(val);
    if(arr.size()==0){
        return;
    }
    heapify(arr);
}

void remove(vector<int> &arr, int val){
    // Search the element to be deleted
    int idx_deleted=-1;
    for(int i=0; i<arr.size(); i++){
        if(arr[i]==val){
            idx_deleted = i;
        }
    }
    if(idx_deleted==-1){
        cout<<"Item does not exist in the heap.";
        return;
    }
    int idx_last = arr.size()-1;
    customSwap(arr[idx_deleted], arr[idx_last]);
    arr.pop_back();
    heapify(arr);
}

int main() {
    std::vector<int> array = {9,1,7,8,3,4,5,15};
    printArray(array);

    heapify(array);
    printArray(array);

    insert(array, 2);
    printArray(array);

    remove(array, 4);
    printArray(array);

    return 0;
}

