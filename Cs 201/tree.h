#include <stdint.h>
    
enum {RED,BLACK} ;

template <typename keytype,typename valuetype>
struct datum {
    datum*    parent = 0 ;
    datum*    childl = 0 ;
    datum*    childr = 0 ;

    keytype   k             ;
    valuetype v             ;
    uint8_t   c     = RED   ;
    
    bool mixed () ;
    //DON'T CALL THESE ON ROOT
    bool leftchild  () { return this == parent->childl ; }
    bool rightchild () { return this == parent->childr ; }
    
    datum () { }
    datum (keytype key) : k (key),v (key) { } //just for testing
    datum (keytype key,valuetype val) : k (key),v (val) { } //just for testing
} ;

template <typename keytype,typename valuetype>
inline int color (datum<keytype,valuetype>* node)  {
    if (!node) return BLACK   ;
    else     { return node->c ; }
}
//for now, let's just insist keytype supports subtraction, then that can
//give us comparison just like how it's done in assembly :)

template <typename keytype,typename valuetype>
class RBTree {
    datum<keytype,valuetype>*         root       ;
    int                               count      ;//"weight" of the tree

    public:
    RBTree() {
        root  = 0       ;
        count = 0       ;
    }


    //For this constructor the tree should be built
    //using the arrays K and V containing s items of
    void destroy (datum<keytype,valuetype>* rt) {
        if (rt) {
            auto savel = rt->childl ;
            auto saver = rt->childr ;
            delete rt               ;
            destroy (savel) ;
            destroy (saver) ;
        }
        //nothing to do
    }
    

    RBTree (keytype k[], valuetype v[], int s) {
        for (int i = 0;i < s;i ++)
            insert (k[i],v[i],root) ;
    }
    ~RBTree() {
        destroy (root) ;
    }

    datum<keytype,valuetype>* getr   () { return root ; }
    void                      print  ()                               ;
    int                       levels (datum<keytype,valuetype>* addr) ;
    
    datum<keytype,valuetype>*  find   (int seek_index) {
        //call the root 0 so that we can mathematically ask for any node
        //in the tree based on a concept of jumping to branches from powers of 
        //2
        return find (seek_index,0,root) ;
    }
    datum<keytype,valuetype>*  find    (int seek_index,int expressive_index,datum<keytype,valuetype>* root) ;


    valuetype * search(keytype k);
    void        rot_l (datum<keytype,valuetype>* addr) ;
    void        rot_r (datum<keytype,valuetype>* addr) ;
    void        write (datum<keytype,valuetype> d,datum<keytype,valuetype>* addr) ;
    void        insert(datum<keytype,valuetype> d,datum<keytype,valuetype>* addr) ;
    void        insert(keytype k, valuetype v)          {
        datum<keytype,valuetype> decoy   ;
        datum<keytype,valuetype> d (k,v) ;

        if (!root) {
            root = new datum<keytype,valuetype> ;
            write (d,root)                      ;
        }
        else insert  (d,root)                               ;//start at root
    }
    //If key k is not found then remove should
    //return 0. If the node with key k is not a leaf
    //then replace k by its predecessor.
    int  remove(keytype k); 


    //rank as in the order (1st smallest, 2nd smallest etc
    int rank(keytype k); 


    //the converse question of the rank() function, given a rank, what is the key ?
    keytype select(int pos); 

    //this must mean the next-ordered node, "successor" could be interpreted to mean
    //child but the problem with that interpreation would be that you could have 2 children
    //and the grammar is not plural.

    //(left-most descendant of the immediate-right child)
    keytype *successor(keytype k) ;


    //(right-most descendant of the immediate-left child)
    keytype *predecessor(keytype k) ; 

    //can just keep track
    int size(); 

    //parent then children
    void preorder (); 

    //means what it says
    void inorder  (); 

    //children then parent
    void postorder(); 
} ;
