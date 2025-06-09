#include <stdio.h>


template <typename K,typename V>
bool datum<K,V>::mixed () { 
    return color (childl) != color (childr) ;
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
        if(!addr->childr) {
            addr->childr         = new datum<K,V> ;
            addr->childr->parent = addr           ;
            write (d,addr->childr)                ;
        }
        else{ insert (d,addr->childr)      ;}
    }
    else {
        if (!addr->childl) {
            addr->childl         = new datum<K,V> ;
            addr->childl->parent = addr           ;
            write (d,addr->childl)                ;
        }
        else insert (d,addr->childl)      ;
    }
}  //no duplicate values entered into tree

// Removes the node with key k and returns 1.
// If key k is not found then remove should return 0.
// If the node with key k is not a leaf then replace k by its predecessor.
template<typename K, typename V>
int RBTree<K,V>::remove(keytype k) {
    Node<keytype, valuetype>* node = searchNode(root, k);
    Node<keytype, valuetype>* pred = predecessor(k);
    if (node == NULL) {
        return 0;
    } else {
        pred->right=node->right;
        pred->left=node->left;
        pred->parent=node->parent;
        deleteNode(node);
        return 1;
    }
}