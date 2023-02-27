#include "arithmeticExpression.h"
#include <iostream>
#include <cstdlib>
#include <stack>
#include <fstream>
#include <sstream>

using namespace std;

arithmeticExpression::arithmeticExpression(const string & infixExpression) : infixExpression(infixExpression) , root(nullptr) {

}

 /* Converts the infixExpression to its equivalent postfix string
       and then generates the tree and assigns the root node to the 
       root data field. The key for the first node is 'a', 'b' for the second node and so on. */
void arithmeticExpression::buildTree() {
    postfixExpression = infix_to_postfix();
    stack<TreeNode*> nodes;
    char c;
    char key = 'a';
    for(unsigned i = 0; i< postfixExpression.size();++i){
        c = postfixExpression.at(i);
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            TreeNode * right = nodes.top();
            nodes.pop();
            TreeNode * left = nodes.top();
            nodes.pop();
            TreeNode * newNode = new TreeNode(c, key);
            newNode->left = left;
            newNode->right = right;
            nodes.push(newNode); // add new node w operand w left and right children
        }
        else { // is an operand 
            nodes.push(new TreeNode(c, key)); // add to stack
        }
        key++; // increment key
    }
    root = nodes.top(); // assign root to last node left in stack
}

int arithmeticExpression::priority(char op) {
    int priority = 0;
    if(op == '('){
        priority =  3;
    }
    else if(op == '*' || op == '/'){
        priority = 2;
    }
    else if(op == '+' || op == '-'){
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix() {
    stack<char> s;
    ostringstream oss;
    char c;
    for(unsigned i = 0; i< infixExpression.size();++i){
        c = infixExpression.at(i);
        if(c == ' '){
            continue;
        }
        if(c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'){ //c is an operator
            if( c == '('){
                s.push(c);
            }
            else if(c == ')'){
                while(s.top() != '('){
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else{
                while(!s.empty() && priority(c) <= priority(s.top())){
                    if(s.top() == '('){
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else{ //c is an operand
            oss << c;
        }
    }
    while(!s.empty()){
        oss << s.top();
        s.pop();
    }
    return oss.str();
}
void arithmeticExpression::infix() {
    infix(root);
}

void arithmeticExpression::infix(TreeNode *node) {
    if (node != nullptr)
    {
        if (node->left != nullptr)
        {
            cout << '(';
        }

        infix(node->left);
        cout << node->data;
        infix(node->right);

        if (node->left != nullptr)
        {
            cout << ')';
        }
    }
}

void arithmeticExpression::prefix() {
    prefix(root);
}

void arithmeticExpression::prefix(TreeNode *node) {
    if (node != nullptr)
    {
        cout << node->data;
        prefix(node->left);
        prefix(node->right);
    }
}

void arithmeticExpression::postfix() {
    postfix(root);
}

void arithmeticExpression::postfix(TreeNode *node) {
    if (node != nullptr)
    {
        postfix(node->left);
        postfix(node->right);
        cout << node->data;
    }
}

void arithmeticExpression::visualizeTree(ofstream & outFS, TreeNode * node) {
    //Display nodes
    if (node != nullptr) {
        outFS << node->key << "[ label = " << "\"" << node->data << "\"" << " ]" <<endl;
        if (node->left) {
            outFS  << node->key <<  "->" << node->left->key << "[ label = " << "\"" << node->left->data << "\"" << " ]" << endl;
            visualizeTree(outFS, node->left);
        }
        
        if (node->right) {
            outFS  << node->key << " -> " << node->right->key << "[ label =  " << "\"" << node->right->data << "\"" << " ]" << endl;
            visualizeTree(outFS, node->right);
        }
        outFS << endl;
    }
}

void arithmeticExpression::visualizeTree(const string &outputFilename) {
    ofstream outFS(outputFilename.c_str());
    if(!outFS.is_open()){
        cout<<"Error opening "<< outputFilename<<endl;
        return;
    }
    outFS<<"digraph G {"<<endl;
    visualizeTree(outFS,root);
    outFS<<"}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0,outputFilename.size()-4)+".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}
