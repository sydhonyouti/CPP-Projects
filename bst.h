#pragma once
/*
	This file contains the definition for two data types: Bst and Node
	The definition for Bst contains the prototypes of Basic Binary Search
	Tree functionality.
	PUBLIC FUNCTIONS:

	1) Constructor - create a Bst object
	2) Destructor - destroy a Bst object
	3) Empty - return true if tree is empty, false otherwise
	4) Insert - insert data into a Bst
	5) Delete - delete data from a Bst
	6) Search - search for a key value and return it's data
	7) Print - print out the data in the tree in an inorder fashion

	PRIVATE FUNCTIONS:

	1) InOrderPrint - prints out a Bst using an in-order traversal
	2) PostOrderDelete - deletes all nodes in a Bst for the destructor
*/

#include <iostream>
#include <string>
using namespace std;

struct Node
{
	string KeyField;
	double Data;
	Node* Left;
	Node* Right;
};

class Bst
{
public:
	//constructor
	Bst();
	//destructor
	~Bst();
	//check for an empty Bst
	bool Empty();
	//insert a key-data pair node, return true if worked, false otherwise
	bool Insert(string, double);
	//delete a key-data pair node, return true if worked, false otherwise
	bool Delete(string);
	//find a key and return it's associated data in a reference parameter, 
	//return true if worked, false otherwise
	bool Search(string, double&);
	//print all the key-pairs in inorder fashion - printing in sorted order
	void Print();

private:
	//helper function for public function Print (RECURSIVE)
	void InOrderPrint(Node*);
	//helper function for destructor - executes a post-order traversal to
	//delete all nodes in the tree (RECURSIVE)
	void PostOrderDelete(Node*);
	//Helper function for Delete function
	void DeleteLeaf(Node*, Node*);
	//Helper function for Delete function
	void DeleteOneChild(Node*, Node*);
	//Helper function for Delete Function
	void DeleteTwoChild(Node*,Node*);
	//pointer to root node in the Bst
	Node* Root;
};

