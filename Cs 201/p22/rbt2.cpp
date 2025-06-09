#include <stdint.h>
#include <iostream>
#include <fstream>
#include <ostream>
   
enum {RED,BLACK,DBL_BLK} ;

template <typename keytype,typename valuetype>
struct datum {
    datum*    parent = 0 ;
    datum*    childl = 0 ;
    datum*    childr = 0 ;

    keytype   k             ;//imagine std::string is here
    valuetype v             ;
    uint8_t   c     = RED   ;
    int weight_     = 1     ;
    
    bool mixed         () ;
    bool red_offspring () ;
    
    bool    leftchild  () { return this == parent->childl ; }//I am a leftchild or
    bool    rightchild () { return this == parent->childr ; }//I am a rightchild

    bool    uniparent  ()          { return (childl && !childr) || (childr && !childl) || (!childl && !childr) ; }
    bool    notparent  ()          { return (!childl && !childr)         ; }
    bool    parentof   (datum* nd) { return nd == childl || nd == childr ; }

    datum** childplace () { return leftchild () ? &parent->childl : &parent->childr ; }

    datum*  singular_child  ()            { return childl ? childl : childr         ; } //MY singular child
    datum*  sibling         (datum* chld) { return childl == chld ? childr : childl ; }
    datum*  successor       () ;
    datum*  predecessor     () ;
    
    int     weight          () ;//deprecated
    int     rank            () ;
    
    datum () : childl(nullptr),childr(nullptr){ }
    datum (keytype key) : k (key),v (key) { } //just for testing
    datum (keytype key,valuetype val) : k (key),v (val) { } //just for testing
} ;

template <typename keytype,typename valuetype>
struct chunk {
    keytype*   keys  ;
    valuetype* datas ;
    int        index ;
    int        sz    ;
    
    chunk () { }
    chunk (keytype* kz,valuetype* dz,int size,int i =0) : keys (kz),datas (dz),index (i),sz (size) { }
} ;

template <typename keytype,typename valuetype>
inline int color (datum<keytype,valuetype>* node)  {
    if (!node) return BLACK   ;
    else     { return node->c ; }
}

inline int halfi (int sz) {
    return (sz - (1 - sz % 2)) /2 ;
}

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
        //root should always be iniitialized for starting state,
        //RBTree of params skipped default ctor
        root = new datum<keytype,valuetype> ;
        if (!perfect (chunk<keytype,valuetype> (k,v,s,halfi (s)),root)) {
            destroy (root) ;
            root = 0       ;
            for (int i = 0;i < s;i ++)
                insert (k[i],v[i]) ;
        }
    }
    ~RBTree() {
        destroy (root) ;
    }

    datum<keytype,valuetype>* node  (int seek_l,int seek_o,int lvl,int order,datum<keytype,valuetype>* ref) ;
    datum<keytype,valuetype>* node  (int lvl,int order) {
        if (root) return node (lvl,order,1,0,root) ;
        else      return 0 ;
    }

    datum<keytype,valuetype>* getr   () { return root ; }
    void                      print  ()                               ;
    int                       levels () { return levels (root) ; }
    int                       levels (datum<keytype,valuetype>* addr) ;
    int                       weight () { if (root) return root->weight () ; else return 0 ; }
    
    datum<keytype,valuetype>*  find   (int seek_index) {
        //call the root 0 so can mathematically ask for any node
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
    void                      rot_l  (datum<keytype,valuetype>* addr) ;
    void                      rot_r  (datum<keytype,valuetype>* addr) ;
    void                      write  (datum<keytype,valuetype> d,datum<keytype,valuetype>* addr) ;
    void                      insert (datum<keytype,valuetype> d,datum<keytype,valuetype>* addr) ;
    void                      insert (keytype k, valuetype v)          {
        datum<keytype,valuetype> d (k,v) ;

        if (!root) {
            root = new datum<keytype,valuetype> ;
            write (d,root)                      ;
        }
        else insert  (d,root)                               ;//start at root
    }
    bool                      perfect(chunk<keytype,valuetype> ck,datum<keytype,valuetype>* addr) ;
    //If key k is not found then remove should
    //return 0. If the node with key k is not a leaf
    //then replace k by its predecessor.


    void correct_insert    (datum<keytype,valuetype>* node) ;
    void correct_blackblack(datum<keytype,valuetype>* node,datum<keytype,valuetype>* parent) ;
    void remove(datum<keytype,valuetype>* addr) ;
    int  remove(keytype k) {
        auto dp = search_ptr (k) ;
        if (dp) { remove (dp)    ; return 1 ; }
        else return 0 ;
    }

   
          
                  
    int rank (keytype k) {
        auto roots     = root ;
        int  deviation = 0    ;
        while (roots) {
            if (roots->k == k) {
                return roots->rank () + deviation  ;
            }
            else if (roots->k > k) {
                roots = roots->childl;
            }
            else {
                deviation = deviation + roots->rank ()  ;
                roots     = roots->childr               ;
            }
        }
        return 0;
    };



    //the converse question of the rank() function, given a rank, what is the key ?
    keytype select(int pos){
        auto roots=root;
        while (roots) {
            if (rank (roots->k) == pos) {
                return roots->k;
            }
            else if (rank (roots->k) > pos) {
                roots = roots->childl;
            }
            else {
                roots = roots->childr;
            }
        }
        return keytype () ;
    }; 

    //this must mean the next-ordered node, "successor" could be interpreted to mean
    //child but the problem with that interpreation would be that you could have 2 children
    //and the grammar is not plural.

    //(left-most descendant of the immediate-right child)
    keytype *successor(keytype pos){
        auto nd = search_ptr (pos)    ;
        if (!nd) return NULL          ;
        return &(nd->successor ()->k) ;
    
             #if 0
             auto roots=root;
    while (roots) {
        if (roots->k == pos) {
            roots=roots->childr;
            if(roots!=nullptr){
              roots=roots->childl;
            }
            return &roots->k;
        }
        else if (roots->k > pos) {
            roots = roots->childl;
        }
        else {
            roots = roots->childr;
        }
    }
    return NULL;   
             #endif
    };


    //(right-most descendant of the immediate-left child)
    keytype *predecessor(keytype pos){
        auto nd = search_ptr (pos) ;
        if (!nd) return NULL ;
        return &(nd->predecessor()->k) ;
    } ; 

    //can just keep track
    int size(){return count;}; 

    //parent then children
    void preorder(){
        preorder(root) ;
        cout << "\n"   ;
    }
    void postorder(){
        postorder(root);
        cout << "\n" ;
    }
    void inorder(){
        inorder(root);
        cout << "\n" ;
    }

    void preorder (datum<keytype,valuetype>* node){
     if(node != nullptr) {
        // Visit the parent node
        cout << node->k << " " ;
        // Traverse the left subtree (child)
        preorder(node->childl);
        // Traverse the right subtree (child)
        preorder(node->childr);
    }
    }; 
    int ct=0;
    //means what it says
    void inorder(datum<keytype,valuetype>* node){
      if (node != nullptr) {
        // Traverse the left subtree (child)
        inorder(node->childl);
          
         // Visit the parent node
        //print(node);
        ct++;
        //node->rank=ct;

        cout << node->k << " " ;

        // Traverse the right subtree (child)
        inorder(node->childr);
    }
    }; 
    
    //children then parent
    void postorder(datum<keytype,valuetype>* node){
      if (node != nullptr) {
        // Traverse the left subtree (child)
        postorder(node->childl);

        // Traverse the right subtree (child)
        postorder(node->childr);

        // Visit the parent node
        cout << node->v << " " ;
    }
    };
};



    

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
datum<K,V>* datum<K,V>::predecessor  () {
    auto lc           = childl ;
    datum<K,V>* rdesc          ;
    if (lc) {
        rdesc = lc ;
        while (rdesc->childr) rdesc = rdesc->childr ;//go all the way down
        return rdesc                                ;//might just return rc in some cases
    }
    else return 0 ;
}
template <typename K,typename V>
int datum<K,V>::weight  () {
    int rweight = 0 ;
    int lweight = 0 ;
    if (childr) rweight = childr->weight () ;
    if (childl) lweight = childl->weight () ;
    return 1 + lweight + rweight ;
}

template <typename K,typename V>
int datum<K,V>::rank  () {
    if (childl)
         return childl->weight () + 1 ;
    else return 1 ;
}

template <typename K,typename V>
void print (datum<K,V>* d) {
    if (!d)
         printf ("---") ;
    else {
        cout.width (3) ;
        cout << d->k   ;
    }
}

template <typename K,typename V>
int RBTree<K,V>::levels (datum<K,V>* addr) {
    
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
datum<K,V>*   RBTree<K,V>::node  (int seek_l,int seek_o,int lvl,int order,datum<K,V>* ref) {
    if (!ref) return 0 ;
    else {
        if (seek_l == lvl) {
            if (seek_o != order) return 0    ;
            else                 return ref  ;
        }
        else {
            int jump          ;
            int jump_l,jump_r ;
            int jump_x        ;

            jump = 1<<lvl ;
            
            //0
            //0             1
            //0     1       2       3
            //0 1   2 3     4 5     6 7
            
            //order*2+0 order*2+1

            jump_x = order  * 2       ;
            jump_l = jump_x + 0       ;
            jump_r = jump_x + 1       ;
            
            
            auto tryl = node (seek_l,seek_o,lvl + 1,jump_l,ref->childl) ;
            auto tryr = node (seek_l,seek_o,lvl + 1,jump_r,ref->childr) ;
            
            if (tryl) return tryl ;
            else      return tryr ;
        }
    }
}



template <typename K,typename V>
void RBTree<K,V>::print () {
    int lvls = levels () ;
    for (int l = 0;l < lvls;l ++) {
        // 1+28 60
        // 1+12 28              NNN                             NNN
        // 1+ 4 12      NNN             NNN      _      NNN             NNN
        // 1+ 0 4   NNN     NNN     NNN     NNN  _  NNN     NNN     NNN     NNN
        //      0 NNN NNN NNN NNN NNN NNN NNN NNN_NNN NNN NNN NNN NNN NNN NNN NNN

        int branch_size = (1<<l)                  ;
        int gap         = (1<<(lvls - 1 - l )) /2 ;
        //0 1   2    4    8  from the bottom
        //0 4   8    16   32
        //0 +4  +8   +16  +32
        //0 8-4 16-4 32-4 64-4
        //0 4   12   28   60
        //0 8   16   32   64
        //0 0   8    16   32
        
        bool g     = gap                            ;
        bool gd    = gap/2                          ;
        int  gap8  = gap * 8 - 4 * g + 1            ;
        int  gapd8 = (gap / 2) * 8 - 4 * gd + 2 * g ;




        for (int g = 0;g < gapd8 ;g ++)
            printf (" ") ;

        for (int i = 0;i < branch_size;i ++) {
            auto n = node (l+1,i) ;
            ::print (n) ;
            for (int g = 0;g < gap8;g ++) printf (" ") ;
        }
        printf ("\n") ;


        for (int g = 0;g < gapd8 ;g ++)
            printf (" ") ;

        for (int i = 0;i < branch_size;i ++) {
            auto n = node (l+1,i) ;
            if (color (n) == RED)
                 printf  ("***") ;
            else printf  ("   ") ;
            for (int g = 0;g < gap8;g ++) printf (" ") ;
        }
        printf ("\n") ;
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

    
   
    if (addr->childl->childr)
        addr->childl->childr->parent = addr ;
    addr->childl                 = addr->childl->childr ;

    
    addr->parent                = *(parchild_place)    ;
    (*(parchild_place))->childr = addr                 ;
}
template <typename K,typename V>
datum<K,V>* RBTree<K,V>::search_ptr (K key) {
    auto rt = root ;
    while (rt) {
        if (rt->k == key) break       ;
        auto greater = key > rt->k    ;
        if (greater)  rt = rt->childr ;
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
    addr->childr                 = addr->childr->childl ;
    

    addr->parent                = *(parchild_place) ;
    (*(parchild_place))->childl = addr              ;
}

template <typename K,typename V>
void RBTree<K,V>::correct_insert (datum<K,V>* addr) {
    //will always be the last thing to do
    //if it's just a first-time insert of the
    //root
    if (false && weight () > 9) {
        print () ;
    }
    
    if (addr == root)
        (*addr).c = BLACK ;
    else if (addr->parent->c == RED) {
        auto gp = addr->parent->parent ;
        if  (gp->mixed ()) {
            //mixed children condition just involves rotations to correct
            //LL
            if      (color (gp->childr) == BLACK && addr->leftchild ()) {
                rot_r (gp)            ;
                
                auto p_color    = addr->parent->c ;
                addr->parent->c = gp->c           ;
                gp->c           = p_color         ;
            }
            //RR
            else if (color (gp->childl) == BLACK && addr->rightchild ()) {
                rot_l (gp)            ;
                
                auto p_color    = addr->parent->c ;
                addr->parent->c = gp->c           ;
                gp->c           = p_color         ;
            }
            //LR case (transform to LL case then redo)
            else if (color (gp->childr) == BLACK && addr->rightchild ()) {
                auto new_grandchild = addr->parent ;
                rot_l (addr->parent)               ;
                correct_insert (new_grandchild) ;
            }
            //RL case
            else {
                auto new_grandchild = addr->parent ;
                rot_r (addr->parent)               ;
                correct_insert (new_grandchild) ;
            }
        }
        else { //recolour, and then retry
            gp->childl->c = BLACK ;
            gp->childr->c = BLACK ;
            gp->c         = RED   ;
            correct_insert (gp)   ;
        }
    }
}

//dual purpose in this function to further correct the tree
template <typename K,typename V>
void    RBTree<K,V>::write (datum<K,V> d,datum<K,V>* addr) {
    (*addr).k     = d.k   ;
    (*addr).v     = d.v   ;
    (*addr).c     = RED   ;
    correct_insert (addr) ;
}

template <typename K,typename V>
void    RBTree<K,V>::insert(datum<K,V> d,datum<K,V>* addr) {
    auto  greater   = d.k > (*addr).k ;
    if (greater) {
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
    
    if (node == root) { } //it's single black again and return
    else {
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
                        //for the node address started at
                        //sib->childl->c = BLACK ; 

                        sib->childl->c = color (sib->childr) ; 
                      
                    }
                    //RR
                    else if (sib == parent->childr && color (sib->childr) == RED) {
                        //rotation with ONE recolor
                        rot_l (parent) ;
                        //already saved the sibling, the nephew becomes the new sibling
                        //for the node address started at
                        //sib->childr->c = BLACK ; 

                        sib->childr->c = color (sib->childl) ; 
                    }

                    //LR
                    else if (sib == parent->childl && color (sib->childr) == RED) {
                        rot_l (sib)           ;
                        sib  = parent->childl ;
                        sib->c         = BLACK ;//the new sibling after rotation
                        sib->childl->c = RED   ;//always will be the old sibling, which was black
                        redo = true           ;
                    }
                    //RL
                    else if (sib == parent->childr && color (sib->childl) == RED) {
                        rot_r (sib)            ;
                        sib  = parent->childr  ;
                        sib->c         = BLACK ;//the new sibling after rotation
                        sib->childr->c = RED   ;//always will be the old sibling, which was black
                        redo = true            ;
                    }
                }
                while (redo) ;
            }
            else {
                //only black children
                //recolor sibling red, that's it
                sib->c = RED ;
                //node is no longer double-black but parent *might* be
                if (parent->c == RED)
                     parent->c = BLACK ; 
                else correct_blackblack (parent,parent->parent) ;
            }
        }
        else {//sibling is red, convert to black sibling
            if (sib == parent->childl)
                 rot_r (parent) ;
            else rot_l (parent) ;
            
            parent->c = RED   ;//copied pointers refer to original values
            sib->c    = BLACK ;
            //if (!sib->parentof (node)) throw "will never happen :)" ;
            //redo the black sibling case
            correct_blackblack (node,parent) ;
        }
    }
}

template <typename K,typename V>
void RBTree<K,V>::remove(datum<K,V>* node) {
    //step 1, only remove on uni-parents
    if (node->uniparent()) {
        
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
            //now node is out of the tree, dangling in the wind
            delete node ;
            //finished with normal BST delete
            if (node_c != chld_c) {
                if (orig_child)
                    orig_child->c = BLACK ; //if it was red, make it black
                //else it's already BLACk
            }
            else {
                
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

template <typename K,typename V>
bool RBTree<K,V>::perfect (chunk<K,V> ck,datum<K,V>* addr) {
    (*addr).k = ck.keys [ck.index] ;
    (*addr).v = ck.datas[ck.index] ;
    (*addr).c = BLACK              ;
    //printf ("perfect insert for index") ;
    if (ck.index > 0) { //there will be a left-tree
        chunk ckl (ck) ;
        ckl.sz       = ck.index            ;
        ckl.index    = 0 + halfi (ckl.sz)  ;
        if (ckl.keys[ckl.index] > ck.keys[ck.index]) return false ;
        addr->childl = new datum<K,V> ;
        perfect (ckl,addr->childl)    ;
    }
    if (ck.index < ck.sz - 1) { //there will be a right-tree
        chunk ckr (ck) ;
        ckr.keys  = ck.keys + ck.index + 1        ;
        ckr.datas = ck.datas + ck.index + 1        ;
        ckr.sz    = ck.sz   - (ck.index + 1)     ;
        ckr.index = 0 + halfi (ckr.sz) ;
        if (ckr.keys[ckr.index] < ck.keys[ck.index]) return false ;
        addr->childr = new datum<K,V>          ;
        perfect (ckr,addr->childr)             ;
    }
    return true ;
}
