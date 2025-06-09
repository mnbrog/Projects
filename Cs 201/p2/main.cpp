#include <iostream>


int main (int argn,char** args) {
    using namespace std ;
    RBTree<int,int> rbt ;

    printf ("start off -- \n") ;
    
    for (auto t : inserts) {
        rbt.insert (t.k,t.v) ;
    }
    
    rbt.print ()                  ;
    
    printf ("========== ################ ==========\n") ;
    printf ("========== ##            ## ==========\n") ;
    printf ("========== now delete nodes ==========\n") ;
    printf ("========== ##            ## ==========\n") ;
    printf ("========== ################ ==========\n") ;
    printf ("\n") ;

    for (auto d : dels) {
        rbt.remove (d.k) ;
    }

    rbt.print ()                  ;
    
    printf ("search for 101\n")    ;
    auto nd = rbt.search_ptr (101) ;
    printf ("pointer is %p\n",nd) ;   

    printf    ("-- end program -- \n") ;

    return 0   ;
}
