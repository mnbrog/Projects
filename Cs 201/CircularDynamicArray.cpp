#include <iostream>
using namespace std;

template<typename elmtype>
class CircularDynamicArray {
    elmtype *array_; 
    int orientation;

    int map_(int logical){
      return (head_ +logical) % capacity_;
    }

    int capacity_;

public:
    int size_;
    int head_; 
    int tail_; 

    // Default Constructor. The array should be of capacity 2 and size 0.
    CircularDynamicArray() : array_(nullptr), head_(0), tail_(0), size_(0), capacity_(2), orientation(1) {
      array_ = new elmtype[2];
    }
    // For this constructor the array should be of capacity and size s.
    CircularDynamicArray(int s) : head_(0), tail_(s-1), size_(s), orientation(1) {
      int pow = 2                   ;
      while (pow < s) pow = pow * 2 ;
      array_ = new elmtype[pow]     ;
    
      capacity_ = pow ;
    }
    CircularDynamicArray(const CircularDynamicArray& cda) {
        array_ = new elmtype[16] ;
        this->operator= (cda)    ;
    }
    
    //a = b = c ;
    
    CircularDynamicArray<elmtype>& operator=(const CircularDynamicArray<elmtype>& a) {
        delete[] array_                        ;
        array_      = new elmtype[a.capacity_] ;
        capacity_   = a.capacity_              ;
        head_       = 0                        ;
        tail_       = a.size_ - 1              ;
        size_       = a.size_                  ;
        orientation = a.orientation            ;

        for (int i = 0;i < size_;i ++)
            this->array_[i] = a.array_[(head_ + i) & (capacity_-1)] ;
        return (*this) ;
    }
    
    // Destructor for the class.
    ~CircularDynamicArray() { 
        delete[] array_; 
    }

    int userMap(int logical) {

        return (orientation>0) ? map_(logical) : map_(size_ - 1 - logical);
    }
    void swap (int a,int b) {
        int phys_a,phys_b    ;
        phys_a = userMap (a) ;
        phys_b = userMap (b) ;

        elmtype tmp    = array_[phys_a] ;
        array_[phys_a] = array_[phys_b] ;
        array_[phys_b] = tmp            ;
    }
    // Traditional [] operator. Should print a message if i is out of bounds and return a reference to value of type elmtype stored in the class for this purpose.
    elmtype& operator[](int i) {
        if (i >= size_) {
            cout << "Index out of bounds" << endl;
            return array_[userMap(0)];} 
        else {
            //return array_[(head_ + i) % capacity_];
            return array_[userMap(i)];

        }
    }

    // increases the size of the array by 1 and stores v at the end of the array. Should double the capacity when the new element doesn't fit.
    void addEnd(elmtype v) {
        if (size_ == capacity_) {
            resize();
        }

        if (size_ == 0) array_[head_] = v ;
        else {
            if (orientation > 0){ tail_ = (tail_ + 1)             % capacity_ ;
                                 array_[tail_] = v ;}
            else                 {head_ = (head_ - 1 + capacity_) % capacity_ ;
                                 array_[head_] = v ;}
        }

        size_++;
    }

    // increases the size of the array by 1 and stores v at the beginning of the array. Should double the capacity when the new element doesn't fit. The new element should be the item returned at index 0.
    void addFront(elmtype v) {
        if (size_ == capacity_) {
            resize();
        }

        if (size_ == 0)
            array_[head_] = v ;
        else {
            if (orientation > 0){ head_ = (head_ - 1 + capacity_) % capacity_ ;
                                 array_[head_] = v ;}
            else                { tail_ = (tail_ + 1)             % capacity_ ;
                                 array_[tail_] = v ;}
        }

        size_++;
    }

    // reduces the size of the array by 1 at the end. Should shrink the capacity when only 25% of the array is in use after the delete.
    void delEnd() {
        if (size_ == 0) {
            cout << "Array is empty" << endl;
        } else {
            if (orientation > 0) {tail_ = (tail_ - 1 + capacity_) % capacity_ ;}
            else                 {head_ = (head_ + 1)             % capacity_ ;}
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


    void resize() {
        elmtype *temp = new elmtype[capacity_ * 2];
        for (int i = 0; i < size_; i++) {
            temp[i] = array_[(head_ + i) & (capacity_ - 1)];
        }
        head_ = 0;
        tail_ = size_ - 1;
        capacity_ *= 2;
        delete[] array_;
        array_ = temp;
    }
    //shrinks the array if cap/4
    void shrink() {
        elmtype *temp = new elmtype[capacity_/2];
        for (int i = 0; i < size_; i++) {
            temp[i] = array_[(head_ + i) % capacity_];
        }
        head_ = 0;
        tail_ = size_ - 1;
        capacity_ /= 2;
        delete[] array_;
        array_ = temp;
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
        orientation=1;
    }

    //user-logical semantics here as well
    elmtype QuickSelect(int k) {
        // Initialize left and right indices
        //   [/ / H ' ' ' T / /]
        enum {HACK_FIX=-1} ;
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
                return array_[userMap(newPivotIndex+HACK_FIX)];
            } else if (newPivotIndex > k) {
                // If the pivot index is greater than k, search the left partition
                right = newPivotIndex - 1;
            } else {
                // If the pivot index is less than k, search the right partition
                left = newPivotIndex + 1;
            }
        }

        // Return the kth element
        return array_[userMap(k+HACK_FIX)];
    }
    int Partition(int left, int right, int pivotIndex) {
        // Move the pivot element to the right of the array
        swap(pivotIndex, right);

        // Keep track of the pivot element's final position
        int storeIndex = left;

        // Compare each element to the pivot element
        for (int i = left; i < right; i++) {
            if (array_[userMap(i)] < array_[userMap(right)]) {
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



    void stableSort() {
        // Allocate a temporary array for merging
        elmtype* temp = new elmtype[size_];

        // Sort the array using the merge sort algorithm
        mergeSort(temp, 0, size_-1);

        // Free the temporary array
        delete[] temp;
    }
    //all indices are user-logical
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
    //user-logical semantics
    void merge(elmtype* temp, int left, int mid, int right) {
        // Initialize left and right indices for the subarrays
        int leftIndex = left;
        int rightIndex = mid + 1;

        // Copy the elements of the subarrays into the temporary array
        for (int i = left; i <= right; i++) {
            if (leftIndex <= mid && (rightIndex > right || array_[userMap(leftIndex)] <= array_[userMap(rightIndex)])) {
                temp[i] = array_[userMap(leftIndex)];
                leftIndex++;
            } else {
                temp[i] = array_[userMap(rightIndex)];
                rightIndex++;
            }
        }

        // Copy the elements from the temporary array back into the original array
        for (int i = left; i <= right; i++) {
            array_[userMap(i)] = temp[i];//temporary buffer can just map to user-logical address-space
        }
    }

    int linearSearch(elmtype e) {
        //   [/ / H ' ' ' T / /]
        for (int i = 0; i < size_; i++) {
            if (array_[userMap(i)] == e) {
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
            if (array_[userMap(mid)] == e) {
                return mid;
            } else if (array_[userMap(mid)] < e) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return -1;
    }

    void reverse() {
        orientation = orientation * -1;
    }

   
};


