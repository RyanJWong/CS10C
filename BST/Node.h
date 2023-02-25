#ifndef __NODE_H__
#define __NODE_h__
#include <string>
using std::string;
class Node {       
    public:
        Node(string);
        Node * left;
        Node * right;
        string data;
        int count;
};
#endif