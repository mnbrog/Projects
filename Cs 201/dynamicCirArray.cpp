#include <iostream>
#include <ostream>
using namespace std;
    template<typename elmtype>
class CircularDynamicArray {
elmtype *array_; 

 
int capacity_;
public:
int size_;
int head_; 
int tail_; 
    // Default Constructor. The array should be of capacity 2 and size 0.
    CircularDynamicArray() : array_(nullptr), head_(0), tail_(0), size_(0), capacity_(2) {
      array_ = new elmtype[2];
    }

    // For this constructor the array should be of capacity and size s.
    CircularDynamicArray(int s) : array_(new elmtype[s]), head_(0), tail_(s-1), size_(s), capacity_(s) {
      array_ = new elmtype[s];
    }

    // Destructor for the class.
    ~CircularDynamicArray() { delete[] array_; }

    // Traditional [] operator. Should print a message if i is out of bounds and return a reference to value of type elmtype stored in the class for this purpose.
    elmtype& operator[](int i) {
        if (i >= size_) {
            cout << "Index out of bounds" << endl;
            return array_[0];} 
        else {
            return array_[(head_ + i) % capacity_];
        }
    }

    // increases the size of the array by 1 and stores v at the end of the array. Should double the capacity when the new element doesn't fit.
    void addEnd(elmtype v) {
        if (size_ == capacity_) {
            resize();
        }
        tail_ = (tail_ + 1) % capacity_;
        array_[tail_] = v;
        size_++;
    }

    // increases the size of the array by 1 and stores v at the beginning of the array. Should double the capacity when the new element doesn't fit. The new element should be the item returned at index 0.
    void addFront(elmtype v) {
        if (size_ == capacity_) {
            resize();
        }
        head_ = (head_ - 1 + capacity_) % capacity_;
        array_[head_] = v;
        size_++;
    }

    // reduces the size of the array by 1 at the end. Should shrink the capacity when only 25% of the array is in use after the delete.
    void delEnd() {
        if (size_ == 0) {
            std::cout << "Array is empty" << std::endl;
        } else {
            tail_ = (tail_ - 1 + capacity_) % capacity_;
            size_--;
            if (size_ < capacity_/4) {
                shrink();
            }
        }
    }

    // reduces the size of the array by 1 at the beginning of the array. Should shrink the capacity when only 25% of the array is in use after the delete.
    void delFront() {
        if (size_ == 0) {
            std::cout << "Array is empty" << std::endl;
        } else {
            head_ = (head_ + 1) % capacity_;
            size_--;
            if (size_ < capacity_/4) {
                shrink();
            }
        }}

    //resize array if cap=size
    void resize(){
      capacity_=capacity_*2;
    }
      //shrinks the array if cap/4
    void shrink(){
          capacity_=capacity_/2;
    }

       // returns the size of the array.
    int length() { return size_; }

    // returns the capacity of the array.
    int capacity() { return capacity_; }

    // Frees any space currently used and starts over with an array of capacity 2 and size 0.
    void clear() {
        delete[] array_;
        array_ = new elmtype[2];
        head_ = tail_ = size_ = 0;
        capacity_ = 2;
    }

elmtype QuickSelect(int k) {
    // Initialize left and right indices
    int left = 0;
    int right = size_ - 1;

    // Keep partitioning the array until the kth element is found
    while (left < right) {
        // Choose a random pivot index
        int pivotIndex = rand() % (right - left + 1) + left;

        // Partition the array around the pivot element
        int newPivotIndex = Partition(left, right, pivotIndex);

        // Check if the pivot index is the kth element
        if (newPivotIndex == k) {
            return array_[newPivotIndex];
        } else if (newPivotIndex > k) {
            // If the pivot index is greater than k, search the left partition
            right = newPivotIndex - 1;
        } else {
            // If the pivot index is less than k, search the right partition
            left = newPivotIndex + 1;
        }
    }

    // Return the kth element
    return array_[k];
}
int Partition(int left, int right, int pivotIndex) {
    // Move the pivot element to the right of the array
    swap(pivotIndex, right);

    // Keep track of the pivot element's final position
    int storeIndex = left;

    // Compare each element to the pivot element
    for (int i = left; i < right; i++) {
        if (array_[i] < array_[right]) {
            // If the element is less than the pivot element, swap it with the element at the store index
            swap(i, storeIndex);
            storeIndex++;
        }
    }

    // Move the pivot element to its final position
    swap(storeIndex, right);

    // Return the pivot element's final position
    return storeIndex;
}


elmtype WCSelect(int k) {
    // Create a copy of the array
    elmtype* copy = new elmtype[size_];
    for (int i = 0; i < size_; i++) {
        copy[i] = array_[i];
    }

    // Find the kth smallest element in the copy array
    int result = WCSelect(copy, 0, size_ - 1, k);

    // Free the copy array
    delete[] copy;

    // Return the kth smallest element
    return result;
}
int WCSelect(elmtype* array, int left, int right, int k) {
    // Base case: if the array has one element, return it
    if (left == right) {
        return array[left];
    }

    // Choose a pivot element at random
    int pivotIndex = rand() % (right - left + 1) + left;

    // Partition the array around the pivot element
    pivotIndex = partition(array, left, right, pivotIndex);

    // Check if the pivot index is the kth element
    if (pivotIndex == k) {
        return array[pivotIndex];
    } else if (pivotIndex > k) {
        // If the pivot index is greater than k, search the left partition
        return WCSelect(array, left, pivotIndex - 1, k);
    } else {
        // If the pivot index is less than k, search the right partition
        return WCSelect(array, pivotIndex + 1, right, k);
    }
}

int partition(elmtype* array, int left, int right, int pivotIndex) {
    // move pivot element to the right of the array
    swap(array[pivotIndex], array[right]);

    // keep track of pivot element's final position
    int storeIndex = left;

    // compare each element to the pivot element
    for (int i = left; i < right; i++) {
        if (array[i] < array[right]) {
            // if the element is less than the pivot element, swap it with the element at store index
            swap(array[i], array[storeIndex]);
            storeIndex++;
        }
    }

    // move pivot element to its final position
    swap(array[storeIndex], array[right]);

    // return pivot element's final position
    return storeIndex;
}


void stableSort() {
    // Allocate a temporary array for merging
    elmtype* temp = new elmtype[size_];

    // Sort the array using the merge sort algorithm
    mergeSort(temp, 0, size_ - 1);

    // Free the temporary array
    delete[] temp;
}
void mergeSort(elmtype* temp, int left, int right) {
    // Base case: if the subarray has one element, return
    if (left >= right) {
        return;
    }

    // Divide the array into two subarrays
    int mid = (left + right) / 2;

    // Sort the left subarray
    mergeSort(temp, left, mid);

    // Sort the right subarray
    mergeSort(temp, mid + 1, right);

    // Merge the two sorted subarrays
    merge(temp, left, mid, right);
}

void merge(elmtype* temp, int left, int mid, int right) {
    // Initialize left and right indices for the subarrays
    int leftIndex = left;
    int rightIndex = mid + 1;

    // Copy the elements of the subarrays into the temporary array
    for (int i = left; i <= right; i++) {
        if (leftIndex <= mid && (rightIndex > right || array_[leftIndex] <= array_[rightIndex])) {
            temp[i] = array_[leftIndex];
            leftIndex++;
        } else {
            temp[i] = array_[rightIndex];
            rightIndex++;
        }
    }

    // Copy the elements from the temporary array back into the original array
    for (int i = left; i <= right; i++) {
        array_[i] = temp[i];
    }
}

int linearSearch(elmtype e) {
    for (int i = 0; i < size_; i++) {
        if (array_[i] == e) {
            return i;
        }
    }
    return -1;
}

int binSearch(elmtype e) {
    int left = 0;
    int right = size_ - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (array_[mid] == e) {
            return mid;
        } else if (array_[mid] < e) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

void reverse() {
    int temp = head_;
    head_ = tail_;
    tail_ = temp;
    head_--;
    tail_++;
    if (tail_ >= capacity_) tail_ = 0;
    if (head_ < 0) head_ = capacity_ - 1;
}


    };
int main() {
    // Test default constructor
    CircularDynamicArray<int> cda;
    cout << "Capacity: " << cda.capacity() << endl;
    cout << "Size: " << cda.length() << endl;

    // Test addEnd and addFront
    cda.addEnd(0);
    cda.addEnd(2);
    cda.addEnd(3);
    cda.addFront(10);
    cda.addFront(22);

    cout << "Capacity: " << cda.capacity() << endl;
    cout << "Size: " << cda.length() << endl;
    cout << "Head: " << cda.head_ << endl;
    cout << "Tail: " << cda.tail_ << endl;
    // Test [] operator
    for (int i = 0; i < cda.length(); i++) {
        cout << cda[i] << " ";
    }
    cout << endl;

    // Test delEnd and delFront
    cda.delEnd();
    cda.delFront();
    cout << "Capacity: " << cda.capacity() << endl;
    cout << "Size: " << cda.length() << endl;

    // Test clear
    cda.clear();
    cout << "Capacity: " << cda.capacity() << endl;
    cout << "Size: " << cda.length() <<endl;

    // Test QuickSelect
    cda.addEnd(4);
    cda.addEnd(5);
    cda.addEnd(6);
    cda.addEnd(7);
    cout << "Kth smallest element: " << cda.QuickSelect(3) << endl;

    // Test WCSelect
    cda.addEnd(4);
    cda.addEnd(5);
    cda.addEnd(6);
    cda.addEnd(7);
    cout << "Kth smallest element: " << cda.WCSelect(3) << endl;

    // Test stableSort
    cda.stableSort();
    cout << "Sorted array: ";
    for (int i = 0; i < cda.length(); i++) {
        cout << cda[i] << " ";
    }
    cout << endl;

    // Test linearSearch
    int item = 5;
    int index = cda.linearSearch(item);
    if (index == -1) {
        cout << "Item " << item << " not found" << endl;
    } else {
        cout << "Item " << item << " found at index " << index << endl;}
        
            // Test binSearch
    cda.stableSort();
    int item2 = 5;
    int index2 = cda.binSearch(item);
    if (index2 == -1) {
        cout << "Item " << item2 << " not found" << endl;
    } else {
        cout << "Item " << item2 << " found at index " << index2 << endl;
    }

    // Test reverse
    cda.reverse();
    cout << "Reversed array: ";
    for (int i = 0; i < cda.length(); i++) {
        cout << cda[i] << " ";
    }
    cout << endl;


        
        }
    

