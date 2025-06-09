#include <iostream>
#include <algorithm>

template <typename keytype, typename valuetype>
class RBTree {
  enum Color {RED, BLACK};
  
  struct Node {
    keytype key;
    valuetype value;
    Color color;
    Node *left, *right, *parent;
    
    Node(keytype k, valuetype v, Color c, Node *l, Node *r, Node *p)
      : key(k), value(v), color(c), left(l), right(r), parent(p) {}
  };
  
  Node *root;

public:
  RBTree() : root(nullptr) {}
  
  RBTree(keytype k[], valuetype v[], int s) {
    root = buildTree(k, v, 0, s - 1, nullptr);
  }
  
  ~RBTree() {
    destroyTree(root);
  }
  
  void insert(keytype k, valuetype v) {
    Node *z = new Node(k, v, RED, nullptr, nullptr, nullptr);
    Node *y = nullptr;
    Node *x = root;
    
    while (x != nullptr) {
      y = x;
      if (z->key < x->key) {
        x = x->left;
      } else {
        x = x->right;
      }
    }
    
    z->parent = y;
    if (y == nullptr) {
      root = z;
    } else if (z->key < y->key) {
      y->left = z;
    } else {
      y->right = z;
    }
    
    insertFixup(z);
  }
  
  void printInorder() {
    printInorder(root);
    std::cout << std::endl;
  }

private:
  Node *buildTree(keytype k[], valuetype v[], int start, int end, Node *parent) {
    if (start > end) {
      return nullptr;
    }
    
    int mid = (start + end) / 2;
    Node *node = new Node(k[mid], v[mid], BLACK, nullptr, nullptr, parent);
    
    node->left = buildTree(k, v, start, mid - 1, node);
    node->right = buildTree(k, v, mid + 1, end, node);
    
    return node;
  }
  
  void destroyTree(Node *node) {
    if (node != nullptr) {
      destroyTree(node->left);
      destroyTree(node->right);
      delete node;
    }
  }
  
  void printInorder(Node *node) {
    if (node != nullptr) {
      printInorder(node->left);
      std::cout << node->key << " ";
      printInorder(node->right);
    }
  }
  
  void leftRotate(Node *x) {
    Node *y = x->right;
    x->right = y->left;
    if (y->left != nullptr) {
      y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == nullptr) {
      root = y;
    } else if (x == x->parent->left) {
      x->parent->left = y;
    } else {
      x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
  }
  
  void rightRotate(Node *y) {
    Node *x = y->left;
    y->left = x->right;
    if (x->right != nullptr) {
      x->right->parent = y;
    }}
   
// Traditional search. Should return a pointer to the valuetype stored with the key.
// If the key is not stored in the tree then the function should return NULL.
template<typename keytype, typename valuetype>
valuetype* RBTree<keytype, valuetype>::search(keytype k) {
    Node<keytype, valuetype>* node = searchNode(root, k);
    if (node == NULL) {
        return NULL;
    } else {
        return &node->value;
    }
}

// Inserts the node with key k and value v into the tree.
template<typename keytype, typename valuetype>
void RBTree<keytype, valuetype>::insert(keytype k, valuetype v) {
    Node<keytype, valuetype>* z = new Node<keytype, valuetype>(k, v);
    insertNode(z);
}

// Removes the node with key k and returns 1.
// If key k is not found then remove should return 0.
// If the node with key k is not a leaf then replace k by its predecessor.
template<typename keytype, typename valuetype>
int RBTree<keytype, valuetype>::remove(keytype k) {
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

// Returns the rank of the key k in the tree.
// Returns 0 if the key k is not found. The smallest item in the tree is rank 1.
template<typename keytype, typename valuetype>
int RBTree<keytype, valuetype>::rank(keytype k) {
    return getRank(root, k);
}

keytype RBTree<keytype, valuetype>::select(int pos) {
    if (pos < 1 || pos > size) {
        throw std::out_of_range("Invalid position for select");
    }
    RBNode<keytype, valuetype>* node = selectNode(root, pos);
    return node->key;
}

RBNode<keytype, valuetype>* RBTree<keytype, valuetype>::selectNode(RBNode<keytype, valuetype>* node, int pos) {
    int r = node->left ? node->left->size : 0;
    if (pos == r + 1) {
        return node;
    } else if (pos <= r) {
        return selectNode(node->left, pos);
    } else {
        return selectNode(node->right, pos - r - 1);
    }
}

keytype* RBTree<keytype, valuetype>::successor(keytype k) {
    RBNode<keytype, valuetype>* node = searchNode(root, k);
    if (node == NULL) {
        return NULL;
    } else if (node->right != NULL) {
        return &(treeMin(node->right)->key);
    } else {
        RBNode<keytype, valuetype>* parent = node->parent;
        while (parent != NULL && node == parent->right) {
            node = parent;
            parent = parent->parent;
        }
        if (parent == NULL) {
            return NULL;
        } else {
            return &(parent->key);
        }
    }
}

keytype* RBTree<keytype, valuetype>::predecessor(keytype k) {
    RBNode<keytype, valuetype>* node = searchNode(root, k);
    if (node == NULL) {
        return NULL;
    } else if (node->left != NULL) {
        return &(treeMax(node->left)->key);
    } else {
        RBNode<keytype, valuetype>* parent = node->parent;
        while (parent != NULL && node == parent->left) {
            node = parent;
            parent = parent->parent;
        }
        if (parent == NULL) {
            return NULL;
        } else {
            return &(parent->key);
        }
    }
}
// Returns the number of nodes in the tree
int size() {
    return count;
}

// Prints the keys of the tree in preorder traversal
void preorder(Node *node) {
    if (node == NULL) {
        return;
    }

    cout << node->key << " ";
    preorder(node->left);
    preorder(node->right);
}

// Helper function for inorder traversal
void inorderHelper(Node<KeyType, ValueType>* node)
{
    if (node == nullptr) return;
    inorderHelper(node->left);
    cout << node->key << " ";
    inorderHelper(node->right);
}

// Inorder traversal
void inorder()
{
    inorderHelper(root);
    cout << endl;
}

// Helper function for postorder traversal
void postorderHelper(Node<KeyType, ValueType>* node)
{
    if (node == nullptr) return;
    postorderHelper(node->left);
    postorderHelper(node->right);
    cout << node->key << " ";
}

// Postorder traversal
void postorder()
{
    postorderHelper(root);
    cout << endl;
}
  }