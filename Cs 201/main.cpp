#include <iostream>


int main (int argn,char** args) {
    using namespace std ;
    RBTree<int,int> rbt ;

    printf    ("start off -- \n") ;
    
    for (auto t : inserts) {
        rbt.insert (t.k,t.v) ;
    }
    
    rbt.print ()                   ;

    printf    ("-- end program -- \n") ;

    return 0   ;
}
