#include <stdint.h>
    
enum {RED,BLACK,DBL_BLK} ;

template <typename keytype,typename valuetype>
struct datum {
    datum*    parent = 0 ;
    datum*    childl = 0 ;
    datum*    childr = 0 ;

    keytype   k             ;
    valuetype v             ;
    uint8_t   c     = RED   ;
    
    bool mixed         () ;
    bool red_offspring () ;
    //DON'T CALL THESE ON ROOT
    bool    leftchild  () { return this == parent->childl ; }//I am a leftchild or
    bool    rightchild () { return this == parent->childr ; }//I am a rightchild

    bool    uniparent  ()          { return (childl && !childr) || (childr && !childl) || (!childl && !childr) ; }
    bool    notparent  ()          { return (!childl && !childr)         ; }
    bool    parentof   (datum* nd) { return nd == childl || nd == childr ; }

    datum** childplace () { return leftchild () ? &parent->childl : &parent->childr ; }

    datum*  singular_child  ()            { return childl ? childl : childr         ; } //MY singular child
    datum*  sibling         (datum* chld) { return childl == chld ? childr : childl ; }
    datum*  successor       () ;
    
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


    datum<keytype,valuetype>* search_ptr(keytype k) ;
    valuetype*                search    (keytype k) {
        auto dp = search_ptr (k) ;
        if (dp) return &dp->v    ;
        else    return 0         ;
    }
    void                      rot_l (datum<keytype,valuetype>* addr) ;
    void                      rot_r (datum<keytype,valuetype>* addr) ;
    void                      write (datum<keytype,valuetype> d,datum<keytype,valuetype>* addr) ;
    void                      insert(datum<keytype,valuetype> d,datum<keytype,valuetype>* addr) ;
    void                      insert(keytype k, valuetype v)          {
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


    void correct_blackblack(datum<keytype,valuetype>* node,datum<keytype,valuetype>* parent) ;
    void remove(datum<keytype,valuetype>* addr) ;
    int  remove(keytype k) {
        auto dp = search_ptr (k) ;
        if (dp) { remove (dp)    ; return 1 ; }
        else return 0 ;
    }


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
datum<int,int> dels   []  = {
6
} ;
datum<int,int> init[]     = {
1,9
} ;
datum<int,int> inserts[]  = {
4,28,6,77,-19,100,-27,98
} ;
#include <stdio.h>


template <typename K,typename V>
bool datum<K,V>::mixed () { 
    return color (childl) != color (childr) ;
}
template <typename K,typename V>
bool datum<K,V>::red_offspring () { 
    return color (childl) == RED || color (childr) == RED ;
}

template <typename K,typename V>
datum<K,V>* datum<K,V>::successor  () {
    auto rc           = childr ;
    datum<K,V>* ldesc          ;
    if (rc) {
        ldesc = rc ;
        while (ldesc->childl) ldesc = ldesc->childl ;//go all the way down
        return ldesc                                ;//might just return rc in some cases
    }
    else return 0 ;
}

template <typename K,typename V>
void print (datum<K,V>* d) {
    //testing with ints for now
    if (!d)
         printf (" ---- "  ) ;
    else {
        if (d->c == RED)
            printf ("[%4d]",d->k) ;
        else
            //let's test with ints up to something like -999 for now
            printf (" %4d " ,d->k) ;
    }
}

template <typename K,typename V>
int RBTree<K,V>::levels (datum<K,V>* addr) {
    //(expressive index concept still used even though tree
    // is memory-managed such as to support rotations)
    //0  1 2   3  4  5  6    7   8   9   10  11  12  13  14
    //* [L R] [LL LR RL RR] [LLL LLR LRL LRR RLL RLR RRL RRR]
    //*  0 0   1  1  2  2    3   3   4   4   5   5   6   6
    
    //for any node, the child  is it's own index * 2 + 1
    //for any node, the parent it's (index - 1) /2
    int l_levels  = 0 ;
    int r_levels  = 0 ;

    
    auto childl = addr->childl ;
    auto childr = addr->childr ;

    if (childl) l_levels = levels (childl) ;
    if (childr) r_levels = levels (childr) ;
    
    //return (1 +), for this current node
    return (l_levels > r_levels) ? 1 + l_levels : 1 + r_levels ;
}


template <typename K,typename V>
datum<K,V>*  RBTree<K,V>::find (int seek_index,int expressive_index,datum<K,V>* r) {
    datum<K,V>* find_l ;
    datum<K,V>* find_r ;
    
    if (!r)                             return 0 ;
    if (expressive_index == seek_index) return r ;
    
    int  childl_index = expressive_index * 2 + 1 ;
    int  childr_index = childl_index + 1         ;
    
    find_l = find (seek_index,childl_index,r->childl) ;
    find_r = find (seek_index,childr_index,r->childr) ;
    
    return (find_l) ? find_l : find_r ;
}




template <typename K,typename V>
void RBTree<K,V>::print () {
    int max_levels = levels (root) ;
    int jmp        = 1             ;//1 2 4 8
    int offset     = 0             ;
    
    for (int l = 0;l < max_levels;l ++) {
        int p_break = 0         ;

        for (int n = 0;n < jmp;n ++) { //the jump can be re-used to say the size of current branch
            if (p_break == 0)
                printf ("%3d| ",offset+n) ;

            //symbolic parent number
            auto parent = ((offset+n)- 1) /2    ;
            if (n % 2 ==0)
                 printf ("%2dL",parent) ;
            else printf ("%2dR",parent) ;

            auto ptr = find (offset+n) ;
            ::print (ptr)              ;

            p_break ++                        ;
            if (p_break == 4)   printf ("  ") ;
            if (p_break == 8) { printf ("\n") ; p_break = 0   ; }
        }
        printf ("\n") ;
        printf ("\n") ;
        printf ("____________ \n") ;
        
        offset = offset + jmp ;//jump to each next level
        jmp    = jmp << 1     ;
    }
}

template <typename K,typename V>
void    RBTree<K,V>::rot_r (datum<K,V>* addr) {
    datum<K,V>** parchild_place                                             ;
    auto par       = addr->parent                                           ;
    if (addr == root)
         parchild_place = &root ;
    else parchild_place = (par->childr == addr) ? &(par->childr) : &(par->childl) ;
    
    addr->childl->parent      = par          ;
    *(parchild_place)         = addr->childl ;

    
    //might be reattaching a ghost child, which would have no memory
    //in such case
    if (addr->childl->childr)
        addr->childl->childr->parent = addr ;
    addr->childl                 = addr->childl->childr ;//left child is saved, so we can reassign it now

    //almost there, one more attachment to do
    //referencing from parent-childplace because that's
    //where we saved the original childl to
    addr->parent                = *(parchild_place)    ;
    (*(parchild_place))->childr = addr                 ;
}
template <typename K,typename V>
datum<K,V>* RBTree<K,V>::search_ptr (K key) {
    auto rt = root ;
    while (rt) {
        if (rt->k == key) break       ;
        auto diff = key - rt->k       ;
        if (diff > 0) rt = rt->childr ;
        else          rt = rt->childl ;
    }
    //automatically returns 0 when not found
    return rt ;
}


template <typename K,typename V>
void    RBTree<K,V>::rot_l (datum<K,V>* addr) {
    datum<K,V>** parchild_place                                             ;
    auto par       = addr->parent                                           ;
    if (addr == root)
         parchild_place = &root ;
    else parchild_place = (par->childr == addr) ? &(par->childr) : &(par->childl) ;
    
    addr->childr->parent      = par                  ;
    *(parchild_place)         = addr->childr         ;

    if (addr->childr->childl)
        addr->childr->childl->parent = addr             ;
    addr->childr                 = addr->childr->childl ;//left child is saved, so we can reassign it now
    //almost there, one more attachment to do
    //referencing from parent-childplace because that's
    //where we saved the original childl to

    addr->parent                = *(parchild_place) ;
    (*(parchild_place))->childl = addr              ;
}

//dual purpose in this function to further correct the tree
template <typename K,typename V>
void    RBTree<K,V>::write (datum<K,V> d,datum<K,V>* addr) {
    (*addr).k     = d.k ;
    (*addr).v     = d.v ;
    (*addr).c     = RED ;
    
    //will always be the last thing to do
    //if it's just a first-time insert of the
    //root
    if (addr == root)
        (*addr).c = BLACK ;
    else if (addr->parent->c == RED) {
        auto gp = addr->parent->parent ;
        if  (gp->mixed ()) { 
            //mixed children condition just involves rotations to correct
            bool redo ;
            do {
                redo = false ;
                //LL
                if      (color (gp->childr) == BLACK && addr->leftchild ()) {
                    rot_r (gp)            ;
                    //gp is now the p
                    //addr->parent->parent would change, but because
                    //we saved it, we're already good
                    auto p_color    = addr->parent->c ;
                    addr->parent->c = gp->c           ;
                    gp->c           = p_color         ;
                }
                //RR
                else if (color (gp->childl) == BLACK && addr->rightchild ()) {
                    rot_l (gp)            ;
                    //gp is now the p
                    //addr->parent->parent would change, but because
                    //we saved it, we're already good
                    auto p_color    = addr->parent->c ;
                    addr->parent->c = gp->c           ;
                    gp->c           = p_color         ;
                }
                //LR case (transform to LL case then redo)
                else if (color (gp->childr) == BLACK && addr->rightchild ()) {
                    auto new_grandchild = addr->parent ;
                    rot_l (addr->parent)               ;
                    addr = new_grandchild              ;
                    redo = true                        ;
                }
                //RL case
                else {
                    auto new_grandchild = addr->parent ;
                    rot_r (addr->parent)               ;
                    addr = new_grandchild              ;
                    redo = true                        ;
                }
            }
            while (redo) ;
        }
        else { //recolour loop
            bool done ;
            do {
                done = true ;
                gp->childl->c = BLACK ;
                gp->childr->c = BLACK ;
                if (gp == root) {//leave alone
                }
                else { //all the way up tree
                    gp->c = RED                ;
                    if (gp->parent == root) {
                        //seems like you could have the first 2 levels black, or black,red
                    }
                    else {
                        gp   = gp->parent->parent ;
                        done = false              ;
                    }
                }
            }
            while (!done) ;
        }
    }
}


template <typename K,typename V>
void    RBTree<K,V>::insert(datum<K,V> d,datum<K,V>* addr) {
    auto diff = d.k - (*addr).k ;

    if (diff > 0) {
        //make sure that original parent has updated information
        if (!addr->childr) {
            addr->childr         = new datum<K,V> ;
            addr->childr->parent = addr           ;
            write (d,addr->childr)                ;
        }
        else insert (d,addr->childr)      ;
    }
    else {
        if (!addr->childl) {
            addr->childl         = new datum<K,V> ;
            addr->childl->parent = addr           ;
            write (d,addr->childl)                ;
        }
        else insert (d,addr->childl)      ;
    }
}

template <typename K,typename V>
void RBTree<K,V>::correct_blackblack(datum<K,V>* node,datum<K,V>* parent) {
    //node is considered as double-black, it may also be
    //the root in which case we just stop
    if (node == root) { } //just say it's single black again and return
    else {
        //call from parent so we don't try to deref a null pointer
        auto sib = parent->sibling (node) ;

        if (color (sib) == BLACK) {
            //not the root and sib is black
            if (sib->red_offspring ()) {
                bool redo ;
                do {
                    redo = false ;
                    //LL
                    if      (sib == parent->childl && color (sib->childl) == RED) {
                        //rotation with ONE recolor
                        rot_r (parent) ;
                        //already saved the sibling, the nephew becomes the new sibling
                        //for the node address we started at
                        //sib->childl->c = BLACK ; //should we do this or not ?

                        sib->childl->c = color (sib->childr) ; //seems like this is what they really meant ?
                        //we now say we're done, black-black is gone
                    }
                    //RR
                    else if (sib == parent->childr && color (sib->childr) == RED) {
                        //rotation with ONE recolor
                        rot_l (parent) ;
                        //already saved the sibling, the nephew becomes the new sibling
                        //for the node address we started at
                        //sib->childr->c = BLACK ; //should we do this ?

                        sib->childr->c = color (sib->childl) ; //seems like this is what they really meant ?
                        //we now say we're done, black-black is gone
                    }

                    //LR
                    else if (sib == parent->childl && color (sib->childr) == RED) {
                        rot_l (sib)           ;
                        sib  = parent->childl ;//we get a new sibling
                        sib->c         = BLACK ;//the new sibling after rotation
                        sib->childl->c = RED   ;//always will be the old sibling, which ~was black
                        redo = true           ;
                    }
                    //RL
                    else if (sib == parent->childr && color (sib->childl) == RED) {
                        rot_r (sib)            ;
                        sib  = parent->childr  ;//we get a new sibling
                        sib->c         = BLACK ;//the new sibling after rotation
                        sib->childr->c = RED   ;//always will be the old sibling, which ~was black
                        redo = true            ;
                    }
                }
                while (redo) ;
            }
            else {
                //only black children
                //recolor sibling red, that's it
                sib->c = RED ;
                //say that node is no longer double-black but parent *might* be
                if (parent->c == RED)
                     parent->c = BLACK ; //and you're done
                else correct_blackblack (parent,parent->parent) ;
            }
        }
        else {//sibling is red, convert to black sibling
            if (sib == parent->childl)
                 rot_r (parent) ;
            else rot_l (parent) ;
            
            parent->c = RED   ;//copied pointers refer to original values
            sib->c    = BLACK ;
            if (!sib->parentof (node)) throw "will never happen :)" ;
            //redo the black sibling case
            correct_blackblack (node,sib) ;//sib is the new parent, node's parent will now point to sib
        }
    }
}

template <typename K,typename V>
void RBTree<K,V>::remove(datum<K,V>* node) {
    //step 1, only remove on uni-parents
    if (node->uniparent()) {
        //where you wanna be
        if (node == root) {
            if (root->notparent()) { delete root ; root = 0    ; }
            else {
                auto chld = root->singular_child () ;
                delete root                         ;
                root    = chld                      ;
                root->c = BLACK                     ;
            }
        }
        else {
            auto orig_child  = node->singular_child () ;
            auto orig_parent = node->parent            ;
            auto node_c      = node->c                 ;
            auto chld_c      = color (orig_child )     ;//so if it's null

            auto childplace = node->childplace () ;
            if (orig_child) //might be NULL child
                orig_child->parent = node->parent ;
            *(childplace) = node->singular_child () ;
            //now node is out of the tree, dangling in the void memoryspace wind
            delete node ;
            //finished with normal BST delete
            if (node_c != chld_c) {
                if (orig_child)
                    orig_child->c = BLACK ; //if it was red, make it black
                //else it's already BLACk
            }
            else {
                //still wanna do this
                //must pass in parent as well in case it's actually a null
                //child, still need information about the tree
                correct_blackblack (orig_child,orig_parent) ;
            }
        }
    }
    else {
        //swap with successor and retry
        auto succ = node->successor () ;
        node->k   = succ->k            ;
        node->v   = succ->v            ;
        remove (succ)                  ;//successor will always be itself a uniparent
    }
}
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
