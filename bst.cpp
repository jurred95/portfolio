//
//  bst.cpp
//
//jared j smith 1005002635

#include "bst.h"
#include <iostream>


BSTree::BSTree()
{
    root = NULL;
    size = 0;
    count = 0;
}
BSTree::~BSTree()
{
  // call destroy on the root of the tree
  destroy(root);
}
void BSTree::destroy(BSTNode* p)
{
  // **recursively** destroy the tree pointed to by p  (what traversal?)
  //postrder??? do root last
    if(p != NULL){
      destroy(p->left);
      destroy(p->right);
      delete p;// search left and right and destroy leaf
    }
}
BSTNode* BSTree::find(BSTNode* node, std::string word)
{// **recursively** search for word starting at node
// return a pointer to the target node -OR-
// the pointer where the target node should be
  if(node == NULL || node->data == word){
    return node;
  }
  else if(node->data < word){
    return find(node->right, word);
  }else{
    return find(node->left, word);
  }

}

void BSTree::increment_frequency(BSTNode* ptr)
{
  // increment the frequency at the node ptr
  ptr -> frequency++;
}
void BSTree::insert( BSTNode* *p, std::string word)
{// if the pointer p is pointing to null then
// create a new node at p
// otherwise, _insert_ word to the left or right subtree
// (**recursively**)

  if(*p == NULL){
    *p = new BSTNode(word);
    size++;

    //std::cout << "size " <<size <<std::endl;
    //double check to see if this works *p or p
  }
  else if(((*p)-> data) > word){
     insert(&((*p) ->left), word);

  }
  else if((*p)-> data < word){
    insert(&((*p) ->right), word);

  }else{
      increment_frequency(*p);
  }
}
void BSTree::insert(std::string word)
{// insert word to the root of the tree by first _finding_ the
// place to insert. If word is already in the tree, _increment_
// its frequency, otherwise _insert_ the word
//std::cout<<"before line funct"<<std::endl;

  BSTNode * find_node = find(root, word);
  //std::cout<<"before line find"<<std::endl;

  BSTNode **p = &find_node;

  if(find_node == NULL){
    insert((&root),word);

  }
  else{
    increment_frequency(find_node);

  }
}
void BSTree::print_list( BSTNode* p, int *n)
{// if p is not null,
// if we have more to print
// recursively print the left tree
// cout the data : frequency and decrement the count (n)
// print the right tree.  (what traversal?)


  if(p != NULL){
    if(*n > 0){
      print_list(p->left, n);
    std::cout
    << "Data: "
    <<p->data
    <<" "
    << "freq: "
    <<p->frequency
    <<" "
    <<std::endl;
    *n = *n -1;
      print_list(p->right, n);

  }

  }

}
void BSTree::print_list(int n)
{
  // call print_list on the root
  int *PL = &n;
  print_list(root, PL);
}
void BSTree::print_tree(int n)
{
  // call print_list on the root
  int *PL = &n;
  print_list(root,PL);

}
void BSTree::print_range( std::string k1, std::string k2, BSTNode* p)
{
  // use pseudocode from the assignment sheet..
  //std::cout << "whats the data" << ((*p)->data) <<std::endl;
  if(p==NULL){
    //std::cout <<"this bitch empty...YEET"<<std::endl;
    return;
  }
  if(p->data > k1){
    print_range(k1, k2, p->left);
  }
  if(k1 <= p->data && k2 >= p->data){
      std::cout << p->data<<  " "<< p->frequency <<  std:: endl;

      count++;

  }
  if(p->data < k2){
    print_range(k1, k2, p->right);
  }

}
void BSTree::print_range( std::string k1, std::string k2)
{
  // call print_range on the root of this tree
  count = 0;//to make sure it resets every time
  print_range(k1, k2,root);
}

int BSTree::get_size(){


  return size;
}
// and so on..

int BSTree::get_count(){

  return count;
}
