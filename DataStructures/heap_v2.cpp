// Max-Heap data structure in C++

#include <iostream>
#include <vector>
using namespace std;

class Heap{
    private:
        int size = -1;
        int capacity = -1;
        int* arr;

        int getLargest(int i){return i-1;}
        int getLeft(int i){return 2*i+1;}
        int getRight(int i){return 2*i+2;}
        void swap (int& a, int& b){
            int temp = a;
            a = b;
            b = temp;
        }
        void heapify(){
            int idx_start = size/2 - 1;
            for(int j=idx_start;j>=0;j--){
                int i = j;
                int largest = getLargest(j);
                int left = getLeft(j);
                int right = getRight(j);
                while(true){
                    if(left<size && arr[left]>arr[i]){
                        largest = left;
                    }
                    if(right<size && arr[right]>arr[i]){
                        largest = right;
                    }
                    if(largest != i){
                        swap(arr[i],arr[largest]);
                        i = largest;
                        left = getLeft(i);
                        right = getRight(i);
                        return;
                    }
                    else{
                        break;
                    }
                }
            }
        }

    public:
        void printArray(int* hT, int arr_size)
        {
            for (int i = 0; i < arr_size; ++i)
                cout << hT[i] << " ";
            cout << "\n";
        }



        void insert(int val){
            if(size>capacity){
                cout<<"Heap overflow. \n";
                return;
            }
            size++;
            this->heapify();
        }

        void remove(int val){
            
        }



}



int main(){

}
