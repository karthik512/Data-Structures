#include <iostream>
#include<climits>

#define MIN 1
#define MAX 2

using namespace std;

class Heap
{
    int *heapArray;
    int capacity;
    int heap_size;

public:
    Heap(int cap);
    void insertKey(int num,int type);
    void deleteKey(int i, int type);
    void decreaseKey(int i,int newVal); //Min Heap
    void increaseKey(int i,int newVal); //Max Heap
    void MinHeapify(int i); //Min Heap
    void MaxHeapify(int i); //Max Heap
    int extractMin();   //Min Heap
    int extractMax();   //Max Heap
    void HeapSort();
    void printHeap(int num);

    void swap(int *x,int*y){int temp = *x;*x = *y;*y = temp;}
    int parent(int i){ return (i-1)/2;}
    int left(int i){return 2*i+1;}
    int right(int i){return 2*i+2;}
    int getMin(){return this->heapArray[0];}
    int getMax(){return this->heapArray[0];}
};

Heap::Heap(int cap)
{
    capacity = cap;
    heap_size = 0;
    heapArray = new int[capacity];
}

/////////////////////////////////////////////////MIN HEAP OPERATIONS
void Heap::insertKey(int num,int type)
{
    if(heap_size == capacity)
        return;

    heap_size++;
    int i = heap_size - 1;
    heapArray[i] = num;

    //Insertion in MIN HEAP
    if(type == MIN)
    {
        while(i != 0 && heapArray[parent(i)] > heapArray[i])
        {
            swap(&heapArray[parent(i)],&heapArray[i]);
            i = parent(i);
        }
    }
    else //Insertion in MAX HEAP
    {
        while(i != 0 && heapArray[parent(i)] < heapArray[i])
        {
            swap(&heapArray[parent(i)],&heapArray[i]);
            i = parent(i);
        }
    }

}

int Heap::extractMin()
{
    if(heap_size == 1)
    {
        heap_size--;
        return heapArray[0];
    }
    int minimum = heapArray[0];
    heapArray[0] = heapArray[heap_size-1];
    heap_size--;
    MinHeapify(0);

    return minimum;
}

void Heap::deleteKey(int i,int type)
{
    //Deletion from MIN HEAP
    if(type == MIN)
    {
        decreaseKey(i,INT_MIN);
        extractMin();
    }
    //Deletion from MAX HEAP
    else if(type == MAX)
    {
        increaseKey(i,INT_MAX);
        extractMax();
    }

}

void Heap::MinHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int small = i;
    if(l < heap_size && heapArray[l] < heapArray[i])
        small = l;
    if(r < heap_size && heapArray[r] < heapArray[small])
        small = r;
    if(small != i)
    {
        swap(&heapArray[i],&heapArray[small]);
        MinHeapify(small);
    }
}

void Heap::decreaseKey(int i, int newValue)
{
    heapArray[i] = newValue;

    while(i != 0 && heapArray[parent(i)] > heapArray[i])
    {
        swap(&heapArray[i],&heapArray[parent(i)]);
        i = parent(i);
    }
}
//////////////////////////////////////////////////////  MIN HEAP ENDS

void Heap::MaxHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int large = i;

    if(l<heap_size && heapArray[l] > heapArray[i])
        large = l;
    if(r < heap_size && heapArray[r] > heapArray[large])
        large = r;
    if(large != i)
    {
        swap(&heapArray[i],&heapArray[large]);
        MaxHeapify(large);
    }
}

int Heap::extractMax()
{
    if(heap_size == 1)
    {
        heap_size--;
        return heapArray[0];
    }

    int maximum = heapArray[0];
    heapArray[0] = heapArray[heap_size-1];
    heap_size--;
    MaxHeapify(0);

    return maximum;
}

void Heap::increaseKey(int i, int newValue)
{
    heapArray[i] = newValue;

    while(i != 0 && heapArray[parent(i)] < heapArray[i])
    {
        swap(&heapArray[parent(i)],&heapArray[i]);
        i = parent(i);
    }
}

void Heap::HeapSort()
{
    while(heap_size > 1)
    {
        swap(&heapArray[0],&heapArray[heap_size-1]);
        --heap_size;

        MaxHeapify(0);
    }
}

void Heap::printHeap(int num)
{
    for(int i = 0;i < num;++i)
    {
        cout<<heapArray[i]<<" ";
    }
}

int main()
{
    int inp,num,index,newNum,x,k,kSmall,kLarge;
    Heap minHeap(10);
    Heap maxHeap(10);
    Heap heapSort(10);

    cout<<"Min Heap:\n";
    cout<<"\t1. Insert\n\t2. Decrease\n\t3. Delete\n\t4. Get Mininum\n\t5. Extract Min\n\t6. k smallest Numbers\n";
    cout<<"----------------------------------\nMax Heap:\n";
    cout<<"\t7. Insert\n\t8. Decrease\n\t9. Delete\n\t10. Get Maximum\n\t11. Extract Max\n\t12. k Largest Numbers\n";
    cout<<"----------------------------------\n";
    cout<<"\t13. Heap Sort\n";
    do{
        cout<<"\nEnter Choice\n";
        cin>>inp;

        switch(inp)
        {
        case 0:
            cout<<"\nExiting...\n";
            break;
        case 1:
            cout<<"\nInsert Operation\n";
            cout<<"Enter num to insert\n";
            cin>>num;
            minHeap.insertKey(num,MIN);
            cout<<"\n";
            break;
        case 2:
            cout<<"\nDecreasing...\n";
            cin>>index;
            cin>>newNum;
            minHeap.decreaseKey(index,newNum);
            break;
        case 3:
            cout<<"\nDelete Operation\n";
            cin>>index;
            minHeap.deleteKey(index,MIN);
            break;
        case 4:
            cout<<"\nMinimum Value in Min Heap "<<minHeap.getMin()<<"\n";
            break;
        case 5:
            cout<<"\nExtract Min Operation\n";
            cout<<"Deleting Min Element "<<minHeap.extractMin()<<"\n";
            break;
        case 6:
            cout<<"\nEnter K:\n";
            cin>>k;
            for(int i = 1;i<=k;++i)
            {
                kSmall = minHeap.extractMin();
                cout<<kSmall<<" ";
            }
            break;
        case 7:
            cout<<"\nInsert Operation\n";
            cout<<"Enter num to insert\n";
            cin>>num;
            maxHeap.insertKey(num,MAX);
            cout<<"\n";
            break;
        case 8:
            cout<<"\nIncreasing...\n";
            cin>>index;
            cin>>newNum;
            maxHeap.increaseKey(index,newNum);
            break;
        case 9:
            cout<<"\nDelete Operation\n";
            cin>>index;
            maxHeap.deleteKey(index,MAX);
            break;
        case 10:
            cout<<"\nMaximum Value in Max Heap "<<maxHeap.getMax()<<"\n";
            break;
        case 11:
            cout<<"\nExtract Max Operation\n";
            cout<<"Deleting Max Element "<<maxHeap.extractMax()<<"\n";
            break;
        case 12:
            cout<<"\nEnter K:\n";
            cin>>k;
            for(int i = 1;i<=k;++i)
            {
                kLarge = maxHeap.extractMax();
                cout<<kLarge<<" ";
            }
            break;
        case 13:
            cout<<"\nEnter no. of elements: ";
            cin>>num;
            cout<<"\nEnter "<<num<<" numbers: \n";
            for(int i = 0;i < num;i++)
            {
                cin>>x;
                heapSort.insertKey(x,MAX);
            }
            heapSort.HeapSort();
            heapSort.printHeap(num);
            cout<<"\n";
            break;
        default:
            cout<<"\nInvalid choice\n";
            break;
        }
    }while(inp>0);
    return 0;
}
