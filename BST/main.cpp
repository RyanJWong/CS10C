#include <iostream>
#include <limits>
#include "BSTree.h"

using namespace std;

void printOrders(BSTree * tree) {
  cout << "Preorder = ";
  tree->preOrder( );
  cout << endl;
  cout << "Inorder = ";
  tree->inOrder( );
  cout << endl;
  cout << "Postorder = ";
  tree->postOrder( );
  cout << endl;
}

int menu() {
  int choice = 0;
  cout << endl << "Enter menu choice: ";
  cout << endl;
  cout 
    << "1. Insert" << endl
    << "2. Remove" << endl
    << "3. Print" << endl
    << "4. Search" << endl
    << "5. Smallest" << endl
    << "6. Largest" << endl
    << "7. Height" << endl
    << "8. Quit" << endl;
  cin >> choice;
  
  // fix buffer just in case non-numeric choice entered
  // also gets rid of newline character
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  return choice;
}

void run_tests() {
  BSTree * tree = new BSTree();
  // test insert
  tree->insert("a");
  tree->insert("b");
  tree->insert("c");

  // Test search and insert
  if (!tree->search("c"))
    throw std::logic_error("Unit test failed c not found");
  if (!tree->search("a"))
    throw std::logic_error("Unit test failed a not found");
  if (!tree->search("b"))
    throw std::logic_error("Unit test failed b not found");

  // Test largest/ smallest
  if (tree->largest() != "c")
    throw std::logic_error("Unit test failed c not largest");
  if (tree->smallest() != "a")
    throw std::logic_error("Unit test failed a not smallest");

  
  // Test height
  if (tree->height("b") != 1)
    throw std::logic_error("Unit test failed b height not 1");
  if (tree->height("a") != 2)
    throw std::logic_error("Unit test failed a height not 2");
  
  // Test remove
  tree->remove("a");
  if (tree->search("a"))
    throw std::logic_error("Unit test failed a was not removed from tree");
    

}

int main( ) {
    // Pass all your tests before running the executable main
    BSTree * tree = new BSTree();

    int choice = menu();

    string entry;
  
    while (choice != 8) {
    
        if (choice == 1) {
            cout << "Enter string to insert: ";
            getline(cin, entry);
            cout << endl;
            tree->insert(entry);
        } 
        else if (choice == 2) {
            cout << "Enter string to remove: ";
            getline(cin, entry);
            tree->remove(entry);
            cout << endl;
        } 
        else if (choice == 3) {
            printOrders(tree);
        } 
        else if (choice == 4) {
            cout << "Enter string to search for: ";
            cin >> entry;
            cout << endl;
            if (tree->search(entry)) {
                cout << "Found" << endl;
            }
            else {
                cout << "Not Found" << endl;
            }
        } 
        else if (choice == 5) {
            cout << "Smallest: " << tree->smallest() << endl;
        } 
        else if (choice == 6) {
            cout << "Largest: " << tree->largest() << endl;
        } 
        else if (choice == 7) {
            cout << "Enter string: ";
            cin >> entry;
            cout << endl;
            cout << "Height of subtree rooted at " << entry << ": " << tree->height(entry) << endl;
        }
        //fix buffer just in case non-numeric choice entered
        choice = menu();
    }
    return 0;
}