#include "BSTree.h"
BSTree::BSTree() : root(nullptr) {

}
BSTree::~BSTree() {
    Destroy(root);
}
void BSTree::Destroy(Node * node) {
    if (node != nullptr) { // recursively go left -> right then delete node
        Destroy(node->left);
        Destroy(node->right);
        delete node;
    }
}

void BSTree::insert(const string &newString) {
    Node * newNode = new Node(newString);
    newNode->count = 1;
    // Create new node and check if root exists
    if (root == nullptr) {
        root = newNode;
    }
    // root exists, add to tree
    else {
        Node * currentNode = root;

        while (currentNode != nullptr) {
            if (newNode->data < currentNode->data) { // if the value is less than node add to left, if not right
                if (currentNode->left == nullptr) { // add to tree
                    currentNode->left = newNode;
                    currentNode = nullptr;
                }
                else { // go left
                    currentNode = currentNode->left;
                }
            }
            else if (currentNode->data == newNode->data) { // duplicate found, increment count in existing node
                currentNode->count++;
                currentNode = nullptr;
                delete newNode;
            }
            else {
                if (currentNode->right == nullptr) { // add to tree
                    currentNode->right = newNode;
                    currentNode = nullptr;
                }
                else { // go right
                    currentNode = currentNode->right;
                }
            }
        }
    }
}

void BSTree::inOrder() const {
    inOrderRecursive(root); // call recursive print
}

void BSTree::inOrderRecursive (Node * node) const {
    if (node == nullptr) { // end if empty
        return;
    }
    inOrderRecursive(node->left); // call all of left
    cout << node->data << "(" << node->count << ")" << ", "; // then print  
    inOrderRecursive(node->right); // then call all of right
}

void BSTree::preOrder() const {
    preOrderRecursive(root); // call recursive
}

void BSTree::preOrderRecursive (Node * node) const {
    if (node == nullptr) { // end if empty
        return;
    }
    cout << node->data << "(" << node->count << ")" << ", "; // print
    preOrderRecursive(node->left); // then call left
    preOrderRecursive(node->right); // and right
}

void BSTree::postOrder() const {
    postOrderRecursive(root); // call recursive
}

void BSTree::postOrderRecursive (Node * node) const {
    if (node == nullptr) { // end if empty
        return;
    }
    postOrderRecursive(node->left); // call left
    postOrderRecursive(node->right); // and right
    cout << node->data << "(" << node->count << ")" << ", "; // then print
}

Node * BSTree::getParent(Node * node) const {
   return getParentRecursive(root, node);
}

Node * BSTree::getParentRecursive(Node * subRoot, Node * node) const {
   if (subRoot == nullptr)
      return nullptr; // base case

   if (subRoot->left == node or subRoot->right == node) { // left or right equals passed node
      return subRoot;
   }

   if (node->data < subRoot->data) {
      return getParentRecursive(subRoot->left, node); // left if node is less than root
   }

   return getParentRecursive(subRoot->right, node); // otherwise right
}


void BSTree::remove(const string & key) { // call recursive function
    Node * node = searchRecursiveNode(key, root); // get node to be removed
    if (node != nullptr and node->count > 1) {
        node ->count--; // if the node has a count > 1, decrement by 1
        return;
    }
    Node * parent = getParent(node); // and its parent
    removeRecursive(parent, node);
}

void BSTree::removeRecursive(Node * parent, Node * node) {
    if (node == nullptr) // base case, passed node is null
        return;

    
    // Case 1: Internal node with 2 children
    if (node->left != nullptr and node->right != nullptr) {
        // Find successor and successor's parent
        Node * succNode = node->left;
        Node * successorParent = node;
        // replace it with rightmost node in the left substree
        while (succNode->right != nullptr) {
            successorParent = succNode;
            succNode = succNode->right;
        }
                
        // Copy the value from the successor node
        std::swap(node->data, succNode->data);
        std::swap(node->count, succNode->count);
                
        // Recursively remove successor
        removeRecursive(successorParent, succNode);
    }

    // Case 2: Root node (with 1 or 0 children)
    else if (node == root) {
        if (node->left != nullptr)
            root = node->left;
        else 
            root = node->right;
    }

    // Case 3: Internal with left child only
    else if (node->left != nullptr) {
        // Replace node with node's left child
        if (parent->left == node)
            parent->left = node->left;
        else
            parent->right = node->left;
    }

    // Case 4: leaf
    else if (node->left == nullptr and node->right == nullptr) {
        if (parent->left == node)
            parent->left = nullptr;
        else
            parent->right = nullptr;
        delete node;
    }
    else { // Case 5: Internal with no left child
        // Replace node with node's leftmost child in the right subtree
        Node * succNode = node->right;
        Node * successorParent = node;
        // replace it with rightmost node in the left substree
        while (succNode->left != nullptr) {
            successorParent = succNode;
            succNode = succNode->left;
        }
                
        // Copy the value from the successor node
        std::swap(node->data, succNode->data);
        std::swap(node->count, succNode->count);
                
        // Recursively remove successor
        removeRecursive(successorParent, succNode);
    }        
}

Node * BSTree::getMaxNode(Node * node) const {
    Node * max = node; // set max node to passed node
    while (max->right != nullptr) { // keep searching right until null
        max = max->right;
    }
    return max;
}

bool BSTree::search(const string & key) const {
    return searchRecursive(key, root); // call recursive
}

Node * BSTree::searchRecursiveNode(const string & key, Node * node) const {
    if (node != nullptr) { // make sure passed node isn't null
        if (key == node->data) // check if passed node is key
            return node;
        else if (key < node->data) // go left if key is less than current
            return searchRecursiveNode(key, node->left);
        else // go right otherwise
            return searchRecursiveNode(key, node->right);
    }
    return nullptr; // could not be found return false
}

bool BSTree::searchRecursive(const string & key, Node * node) const {
    if (node != nullptr) { // make sure passed node isn't null
        if (key == node->data) // check if passed node is key
            return true;
        else if (key < node->data) // go left if key is less than current
            return searchRecursive(key, node->left);
        else // go right otherwise
            return searchRecursive(key, node->right);
    }
    return false; // could not be found return false
}

string BSTree::largest( ) const {
    if (root == nullptr) // empty string for empty tree
        return "";
    Node * max = root; // set max node to root
    while (max->right != nullptr) { // keep searching right until null
        max = max->right;
    }
    return max->data;
}

string BSTree::smallest( ) const {
    if (root == nullptr) // empty string for empty tree
        return "";
    Node * min = root; // set min node to root

    while (min->left != nullptr) { // keep searching left until null

        min = min->left;
    }
    return min->data;
}

// get height of passed string
int BSTree::height(const string & key) const {
    Node * currentNode = searchRecursiveNode(key, root); // get node
    if (currentNode == nullptr) {
        return -1; // return -1 if node doesnt exist
    }
    return getHeight(currentNode);
}

int BSTree::getHeight(Node * node) const {
    if (node == nullptr) { // return -1 if node is null
        return -1;
    }
    int leftHeight = getHeight(node->left); // get max height of left
    int rightHeight = getHeight(node->right); // get max height of right
    return 1 + std::max(leftHeight, rightHeight);
}