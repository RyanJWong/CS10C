#include "AVLTree.h"
#include <iostream>
#include <fstream>

AVLTree::AVLTree() : root(nullptr)
{
}
AVLTree::~AVLTree()
{
    Destroy(root);
}
void AVLTree::Destroy(Node *node)
{
    if (node != nullptr)
    { // recursively go left -> right then delete node
        Destroy(node->left);
        Destroy(node->right);
        delete node;
    }
}

void AVLTree::insert(const string &newString)
{
    Node *newNode = new Node(newString);
    newNode->count = 1;
    // Create new node and check if root exists
    if (root == nullptr)
    {
        root = newNode;
    }
    // root exists, add to tree
    else
    {
        Node *currentNode = root;

        while (currentNode != nullptr)
        {
            if (newNode->data < currentNode->data)
            { // if the value is less than node add to left, if not right
                if (currentNode->left == nullptr)
                { // add to tree
                    currentNode->left = newNode;
                    currentNode = nullptr;
                }
                else
                { // go left
                    currentNode = currentNode->left;
                }
            }
            else if (currentNode->data == newNode->data)
            { // duplicate found, increment count in existing node
                currentNode->count++;
                currentNode = nullptr;
                delete newNode;
                return;
            }
            else
            {
                if (currentNode->right == nullptr)
                { // add to tree
                    currentNode->right = newNode;
                    currentNode = nullptr;
                }
                else
                { // go right
                    currentNode = currentNode->right;
                }
            }
        }
    }
    // if node is not duplicate, find unbalacned node and rotate
    Node *unbalanced = findUnbalancedNode(newNode);
    if (unbalanced != nullptr)
    {
        rotate(unbalanced);
    }
}

void AVLTree::inOrder() const
{
    inOrderRecursive(root); // call recursive print
}

void AVLTree::inOrderRecursive(Node *node) const
{
    if (node == nullptr)
    { // end if empty
        return;
    }
    inOrderRecursive(node->left); // call all of left
    cout << node->data << "(" << node->count << ")"
         << ", ";                  // then print
    inOrderRecursive(node->right); // then call all of right
}

void AVLTree::preOrder() const
{
    preOrderRecursive(root); // call recursive
}

void AVLTree::preOrderRecursive(Node *node) const
{
    if (node == nullptr)
    { // end if empty
        return;
    }
    cout << node->data << "(" << node->count << ")"
         << ", ";                   // print
    preOrderRecursive(node->left);  // then call left
    preOrderRecursive(node->right); // and right
}

void AVLTree::postOrder() const
{
    postOrderRecursive(root); // call recursive
}

void AVLTree::postOrderRecursive(Node *node) const
{
    if (node == nullptr)
    { // end if empty
        return;
    }
    postOrderRecursive(node->left);  // call left
    postOrderRecursive(node->right); // and right
    cout << node->data << "(" << node->count << ")"
         << ", "; // then print
}

Node *AVLTree::getParent(Node *node)
{
    return getParentRecursive(root, node);
}

Node *AVLTree::getParentRecursive(Node *subRoot, Node *node)
{
    if (subRoot == nullptr)
        return nullptr; // base case

    if (subRoot->left == node or subRoot->right == node)
    { // left or right equals passed node
        return subRoot;
    }

    if (node->data < subRoot->data)
    {
        return getParentRecursive(subRoot->left, node); // left if node is less than root
    }

    return getParentRecursive(subRoot->right, node); // otherwise right
}

void AVLTree::remove(const string &key)
{                                                // call recursive function
    Node *node = searchRecursiveNode(key, root); // get node to be removed
    if (node != nullptr and node->count > 1)
    {
        node->count--; // if the node has a count > 1, decrement by 1
        return;
    }
    Node *parent = getParent(node); // and its parent
    removeRecursive(parent, node);
}

void AVLTree::removeRecursive(Node *parent, Node *node)
{
    if (node == nullptr) // base case, passed node is null
        return;

    // Case 1: Internal node with 2 children
    if (node->left != nullptr and node->right != nullptr)
    {
        // Find successor and successor's parent
        Node *succNode = node->left;
        Node *successorParent = node;
        // replace it with rightmost node in the left substree
        while (succNode->right != nullptr)
        {
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
    else if (node == root)
    {
        if (node->left != nullptr)
            root = node->left;
        else
            root = node->right;
    }

    // Case 3: Internal with left child only
    else if (node->left != nullptr)
    {
        // Replace node with node's left child
        if (parent->left == node)
            parent->left = node->left;
        else
            parent->right = node->left;
    }

    // Case 4: leaf
    else if (node->left == nullptr and node->right == nullptr)
    {
        if (parent->left == node)
            parent->left = nullptr;
        else
            parent->right = nullptr;
        delete node;
    }
    else
    { // Case 5: Internal with no left child
        // Replace node with node's leftmost child in the right subtree
        Node *succNode = node->right;
        Node *successorParent = node;
        // replace it with rightmost node in the left substree
        while (succNode->left != nullptr)
        {
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

Node *AVLTree::getMaxNode(Node *node) const
{
    Node *max = node; // set max node to passed node
    while (max->right != nullptr)
    { // keep searching right until null
        max = max->right;
    }
    return max;
}

bool AVLTree::search(const string &key) const
{
    return searchRecursive(key, root); // call recursive
}

Node *AVLTree::searchRecursiveNode(const string &key, Node *node) const
{
    if (node != nullptr)
    {                          // make sure passed node isn't null
        if (key == node->data) // check if passed node is key
            return node;
        else if (key < node->data) // go left if key is less than current
            return searchRecursiveNode(key, node->left);
        else // go right otherwise
            return searchRecursiveNode(key, node->right);
    }
    return nullptr; // could not be found return false
}

bool AVLTree::searchRecursive(const string &key, Node *node) const
{
    if (node != nullptr)
    {                          // make sure passed node isn't null
        if (key == node->data) // check if passed node is key
            return true;
        else if (key < node->data) // go left if key is less than current
            return searchRecursive(key, node->left);
        else // go right otherwise
            return searchRecursive(key, node->right);
    }
    return false; // could not be found return false
}

string AVLTree::largest() const
{
    if (root == nullptr) // empty string for empty tree
        return "";
    Node *max = root; // set max node to root
    while (max->right != nullptr)
    { // keep searching right until null
        max = max->right;
    }
    return max->data;
}

string AVLTree::smallest() const
{
    if (root == nullptr) // empty string for empty tree
        return "";
    Node *min = root; // set min node to root

    while (min->left != nullptr)
    { // keep searching left until null

        min = min->left;
    }
    return min->data;
}

// get height of passed string
int AVLTree::height(const string &key) const
{
    Node *currentNode = searchRecursiveNode(key, root); // get node
    if (currentNode == nullptr)
    {
        return -1; // return -1 if node doesnt exist
    }
    return getHeight(currentNode);
}

int AVLTree::getHeight(Node *node) const
{
    if (node == nullptr)
    { // return -1 if node is null
        return -1;
    }
    int leftHeight = getHeight(node->left);   // get max height of left
    int rightHeight = getHeight(node->right); // get max height of right
    return 1 + std::max(leftHeight, rightHeight);
}

void AVLTree::visualizeTree(const string &outputFilename)
{
    ofstream outFS(outputFilename.c_str());
    if (!outFS.is_open())
    {
        cout << "Error" << endl;
        return;
    }
    outFS << "digraph G {" << endl;
    visualizeTree(outFS, root);
    outFS << "}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0, outputFilename.size() - 4) + ".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}

void AVLTree::visualizeTree(ofstream &outFS, Node *node)
{
    if (node)
    {
        if (node->left)
        {
            visualizeTree(outFS, node->left);
            outFS << node->data << " -> " << node->left->data << ";" << endl;
        }

        if (node->right)
        {
            visualizeTree(outFS, node->right);
            outFS << node->data << " -> " << node->right->data << ";" << endl;
        }
    }
}

// Return the balance factor of a given node.
int AVLTree::balanceFactor(Node *node) const
{
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

void AVLTree::printBalanceFactors() const
{
    printBalanceFactorsRecursive(root); // call recursive
    cout << endl;
}

// recursivley print in order and balance
void AVLTree::printBalanceFactorsRecursive(Node *node) const
{

    if (node == nullptr)
    { // end if empty
        return;
    }
    printBalanceFactorsRecursive(node->left); // call all of left
    cout << node->data << "(" << balanceFactor(node) << ")"
         << ", ";                              // then print
    printBalanceFactorsRecursive(node->right); // then call all of right
}

// given a node, find the most unbalanced node
Node *AVLTree::findUnbalancedNode(Node *node)
{
    if (node == nullptr)
    {
        return 0;
    }

    int factor = balanceFactor(node);
    if (factor == -2 || factor == 2)
    {
        return node;
    }
    else
    {
        return findUnbalancedNode(getParent(node));
    }
}

// rotate based off 4 cases
void AVLTree::rotate(Node *node)
{

    int factor = balanceFactor(node);
    int leftFactor = balanceFactor(node->left);
    int rightFactor = balanceFactor(node->right);

    if (factor == 2)
    { // passed node is inbalanced
        if (leftFactor == 1 || rightFactor == 1)
        { // left heavier or right heavier
            rotateRight(node);
        }
        else
        {
            rotateLeft(node->left);
            rotateRight(node);
        }
    }
    else
    { // check children for inbalance
        if (leftFactor == -1 || rightFactor == -1)
        { // left or right lighter
            rotateLeft(node);
        }
        else
        {
            rotateRight(node->right);
            rotateLeft(node);
        }
    }
}

//  Rotate the subtree to right at the given node and returns the new subroot.
Node *AVLTree::rotateRight(Node *node)
{
    Node *leftRightChild = node->left->right;
    Node *parent = getParent(node);
    if (parent != nullptr) // Node has parent
    {
        if (parent->left == node) // node is left child
        {
            parent->left = node->left;
        }
        else if (parent->right == node) // node is right child
        {
            parent->right = node->left;
        }
    }
    else // node is root
    {
        root = node->left;
    }
    node->left->right = node;
    node->left = leftRightChild;
    return getParent(node);
}

// Rotate the subtree to left at the given node and returns the new subroot.
Node *AVLTree::rotateLeft(Node *node)
{
    Node *rightLeftChild = node->right->left;
    Node *parent = getParent(node);
    if (parent != nullptr) // node has parent
    {
        if (parent->right == node) // node is right child
        {
            parent->right = node->right;
        }
        else if (parent->left == node) // node is left child
        {
            parent->left = node->right;
        }
    }
    else // node is root
    {
        root = node->right;
    }
    node->right->left = node;
    node->right = rightLeftChild;
    return getParent(node);
}
