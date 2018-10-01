//
//  bst.h
////jared j smith 1005002635
//g++ -o test main-bst.cpp bst.cpp -std=c++11
//./test dictionary-brit.txt dictionary.txt AliceInWonderland.txt WarAndPeace.txt ATaleOfTwoCities.txt  PrideAndPrejudice.txt

#ifndef bst_h
#define bst_h

#ifndef NULL
#define NULL 0x00
#endif


#include <string>

class BSTNode {
private:

    std::string data;
    int frequency;

    BSTNode *left;
    BSTNode *right;

public:

    BSTNode(std::string d) { data = d; frequency = 1; left = NULL; right = NULL; }
    ~BSTNode() {}

    friend class BSTree;
};


class BSTree {
private:

    BSTNode *root;

    int size;
    int count; // returns value between k1 and k2

    void destroy(BSTNode* p);

    BSTNode* find(BSTNode* node, std::string word);

    void increment_frequency(BSTNode *ptr);

    void insert(BSTNode**p, std::string word);
      //double pointer means you wanna insert at this pointed
      //if you dereference p is should never be null ptr


    void print_list(BSTNode*p, int*n);

    void print_range(std::string k1, std::string k2, BSTNode*p);


public:

    BSTree();
    ~BSTree();

    void insert(std::string word);

    void print_list(int n);

    void print_tree(int n);

    void print_range(std::string k1, std::string k2); // output all the strings in the tree lexically between the parameters

    int get_size();

    int get_count();

};


#endif
