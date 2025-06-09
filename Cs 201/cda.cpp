#include <iostream>
#include <ostream>
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
    CircularDynamicArray(int s) : array_(new elmtype[s]), head_(0), tail_(s-1), size_(s), capacity_(s), orientation(1) {
      array_ = new elmtype[s];
    }

    // Destructor for the class.
    ~CircularDynamicArray() { delete[] array_; }

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

    //resize array if cap=size
       void resize() {
        elmtype *temp = new elmtype[capacity_ * 2];
        for (int i = 0; i < size_; i++) {
            temp[i] = array_[(head_ + i) % capacity_];
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
                return array_[userMap(newPivotIndex)];
            } else if (newPivotIndex > k) {
                // If the pivot index is greater than k, search the left partition
                right = newPivotIndex - 1;
            } else {
                // If the pivot index is less than k, search the right partition
                left = newPivotIndex + 1;
            }
        }

        // Return the kth element
        return array_[userMap(k)];
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

    //int partition(elmtype* array, int left, int right, int pivotIndex) {
    //    // move pivot element to the right of the array
    //    swap(pivotIndex, right);

    //    // keep track of pivot element's final position
    //    int storeIndex = left;

    //    // compare each element to the pivot element
    //    for (int i = left; i < right; i++) {
    //        if (array[userMap(i)] < array[userMap(right)]) {
    //            // if the element is less than the pivot element, swap it with the element at store index
    //            swap(i, storeIndex);
    //            storeIndex++;
    //        }
    //    }

    //    // move pivot element to its final position
    //    swap(storeIndex, right);

    //    // return pivot element's final position
    //    return storeIndex;
    //}


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

    void  print();
    void  printUserLogical () {
        printf ("(") ;
        for (int i = 0;i < size_;i ++) {
            elmtype v = (*this)[i] ;
            printf ("%d ",v)       ;
        }
        printf (")\n") ;
    }
    // NEED copy operator  cdma = cdab
};

//---------debugfunc--------

//DEBUG FUNCTIONS ----------------------
template<typename elmtype>
void CircularDynamicArray<elmtype>::print () {
    //HD TL SZ CAP : 10 19 10 ...
    //['12  '134 '1   T0 .0 .0 .0 .0 .0 .0 H9 '3 '4 '5 '6 '4]
    //[H3 '3 '4 '5 T9 .0 .0]
    
    //this test function
    printf ("{MHD MTL} SZ CAP +OR: {%d %d} %d %d %+d\n",head_,tail_,size_,capacity_,orientation) ;
    cout << "["  ;
    if (capacity_ > 16) {
    }
    else {
        for (int physical = 0;physical < capacity_;physical ++) {//going past size here, this is a debug function
            //X X T . . H
            //1 2 3 4 5 0

            //1 H T . . .
            //5 0 1 2 3 4
            //int logical = ((capacity_ + physical) - head_) % capacity_ ;
            int logical = ((physical - head_) + capacity_) % capacity_ ;

            if      (logical >= size_  ) cout << "/" ;
            else if (physical  == head_) cout << "H" ;
            else if (physical  == tail_) cout << "T" ;
            else                         cout << "'" ;

            //debug function only works when elmtype casts to an integer naturally
            //floats would work but truncate (3.4 => 3)
            elmtype v = array_[physical] ;
            printf ("%-4d",(int)(v))     ;//.print () ;
        }
        
    }
    cout << "]" << endl ;
}


int main () {
    // Test default constructor
    CircularDynamicArray<int>   cda;
    CircularDynamicArray<float> cdaf;
     CircularDynamicArray<int>   cda2;
    
    printf ("INITIAL CDA\n") ;
    cda.print    () ;
    printf ("\n\n\n") ;


    cda.addFront (33)  ;
    cda.addEnd   (1)   ;
    cda.addEnd   (12)  ;
    cda.addEnd   (69)  ;
    cda.addEnd   (2)   ;
    cda.addFront (9)   ;
    cda.addFront (-11) ;
      
    cda.delFront  ()    ;
    cda2=cda;
  cda2.stableSort();
  cda2.print();
  cda2.printUserLogical();

    cout << "an unsorted cda" << endl ;
    cda.print    () ;

    cda.stableSort () ;
    cout << "-- sorted --" << endl ;
    cda.print () ;
    
    
    cout << "print user-mapped view of array when accessed with [] operator" << endl ;
    cda.printUserLogical () ;

    cout << "-- REVERSE --" << endl ;
    cda.reverse  () ;
    cout << "print user-mapped view of array when accessed with [] operator" << endl ;
  //cda.stableSort();
    cda.printUserLogical () ;
 
  cout<<"cda:3 "<<cda.QuickSelect(3)<<endl;
  cout<<"cda:2 "<<cda.binSearch(2)<<endl;
  //cout<<"cda:2 "<<cda.linearSearch(2)<<endl;
  //cout<<cda[0]<<"   "<<cda.capacity();
  
}

#if 0
int main() {
    // Test default constructor
    CircularDynamicArray<int> cda;
      

    cout << "Capacity: " << cda.capacity() << endl;
    cout << "Size: " << cda.length() << endl;

    // Test addEnd and addFront
    cda.addFront(33);
    cda.print();
    cda.addEnd(1);
    // cda.addEnd(12);
    // cda.addFront(69);
    // cda.addEnd(2);
    // cda.addEnd(3);
    // cda.addFront(10);
    // cda.addFront(45);
    // cda.addFront(45);
  
      cda.print();
      cout<<"QS: 3 "<<cda.QuickSelect(3)<<endl;
      cda.stableSort();
      cda.print();
      //cda.delFront();
      //cda.delEnd();
        //cda.addFront(22);
      cda.print();
      cda.delEnd();
      cda.delFront();
      cda.delEnd();
      cda.delFront();
      cda.delEnd();
      cda.delFront();
      cda.print();
      cda.reverse();
      cda.print();
      cda.addEnd(5);
      cda.addFront(55);
      //cda.reverse();
      cda.print();
  
    // for (int i = 0; i < cda.length(); i++) {
    //     cout << cda[i] << " ";
    // }
    // cout << endl;

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
    cda.addFront(5);
    cda.addEnd(6);
    cda.addEnd(7);
    //cda.addFront(8);
      //cda.addFront(12);

    cout << "Kth smallest element: " << endl;
    cda.print();
    // Test stableSort
    cda.stableSort();// add front 
    cout << "Sorted array: "<<endl;
      cda.print();

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
    //cda.stableSort();
    cda.print();
    cda.clear();
  cout<<endl;
      cout<<endl;

    cout<<endl;

    CircularDynamicArray<char> cda_char;

cout << "Char Capacity: " << cda_char.capacity() << endl;
cout << "Char Size: " << cda_char.length() << endl;

// Test addEnd and addFront
cda_char.addFront('!');
cda_char.addFront('A');
cda_char.addEnd('L');
cda_char.addFront('Z');
cda_char.addEnd('B');
cda_char.addEnd('C');
cda_char.addFront('A');
cout << "Char Capacity: " << cda_char.capacity() << endl;
cout << "Char Size: " << cda_char.length() << endl;
cout << "Char Head: " << cda_char.head_ << endl;
cout << "Char Tail:" << cda_char.tail_ << endl;

cda_char.print();

// Test delEnd and delFront
cda_char.delEnd();
cda_char.delFront();
cout << "Capacity: " << cda_char.capacity() << endl;
cout << "Size: " << cda_char.length() << endl;
cda_char.print();

// Test clear
cda_char.clear();
cout << "Capacity: " << cda_char.capacity() << endl;
cout << "Size: " << cda_char.length() <<endl;

// Test QuickSelect
cda_char.addEnd('D');
cda_char.addEnd('E');
cda_char.addEnd('F');
cda_char.addEnd('G');
cout << "Kth smallest element: " << cda_char.QuickSelect(3) << endl;
cda_char.print();

// Test WCSelect
cda_char.addEnd('D');
cda_char.addEnd('E');
cda_char.addEnd('F');
cda_char.addEnd('G');
cda_char.addFront('H');
cout << "Kth smallest element: " << endl;
cda_char.print();

// Test stableSort
cda_char.stableSort();
cout << "Sorted array: ";
cda_char.print();

cout << endl;

// Test linearSearch
char item4 = 'E';
int index4 = cda_char.linearSearch(item);
if (index == -1) {
cout << "Item " << item4 << " not found" << endl;
} else {
cout << "Item " << item4 << " found at index " << index << endl;}
    // Test binSearch
cda_char.stableSort();
char item5 = 'E';
int index5 = cda_char.binSearch(item4);
if (index5 == -1) {
cout << "Item " << item5 << " not found" << endl;
} else {cout << "Item " << item5 << " found at index " << index5 << endl;
  cda_char.print();

    }

    // Test reverse
    cda_char.reverse();
    cout << "Reversed array: ";
    cda_char.print();

    cout << endl;
    /////////////////////////////////////////////////
    cout<<endl; 
          cout<<endl;



      cout<<endl;     
    cout<<"Double:"<<endl;
    cout<<endl;

    CircularDynamicArray<double> cda_double;

    cout << "Double Capacity: " << cda_double.capacity() << endl;
    cout << "Double Size: " << cda_double.length() << endl;

    // Test addEnd and addFront
    cda_double.addFront(0.1);
    cda_double.addFront(1.0);
    cda_double.addEnd(2.1);
    cda_double.addFront(3.0);
    cda_double.addEnd(4.1);
    cda_double.addEnd(5.1);

    cout << "Double Capacity: " << cda_double.capacity() << endl;
    cout << "Double Size: " << cda_double.length() << endl;
    cout << "Double Head: " << cda_double.head_ << endl;
    cout << "Double Tail:" << cda_double.tail_ << endl;

    cda_double.print();
    cout << endl;

    // Test delEnd and delFront
    cda_double.delEnd();
    cda_double.delFront();
    cout << "Capacity: " << cda_double.capacity() << endl;
    cout << "Size: " << cda_double.length() << endl;

    // Test clear
    cda_double.clear();
    cout << "Capacity: " << cda_double.capacity() << endl;
    cout << "Size: " << cda_double.length() <<endl;

    // Test QuickSelect
    cda_double.addEnd(6.0);
    cda_double.addEnd(7.0);
    cda_double.addEnd(8.0);
    cda_double.addEnd(9.0);
    cout << "Kth smallest element: " << cda_double.QuickSelect(3) << endl;

    // Test WCSelect
    cda_double.addEnd(6.0);
    cda_double.addEnd(7.0);
    cda_double.addEnd(8.0);
    cda_double.addEnd(9.0);
    cda_double.addFront(10.0);
    cout << "Kth smallest element: " << endl;

    // Test stableSort
    cda_double.stableSort();
    cout << "Sorted array: ";
    cda.print();
    cout << endl;

    // Test linearSearch
    double it4em = 7.0;
    int in4dex = cda_double.linearSearch(it4em);
    if (index == -1) {
    cout << "Item " << it4em << " not found" << endl;
    } else {
    cout << "Item " << it4em << " found at index " << in4dex << endl;
    }

    // Test binSearch



        
}
#endif
    

