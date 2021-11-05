/*
	This C++ file contains the implementation of the functions prototyped
	in bst.h
	1) Constructor
	2) Destructor
	3) Insert
	4) Delete
	5) Search
	6) Print
*/

/*
Author: Sydney Honyouti
Date: 12/6/20
Description: Only worked on the Delete, Search, and Destructor functions. Along with
helper functions such as, DeleteLeaf, DeleteOneChild, and DeleteTwoChild.
*/

#include "bst.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

Bst::Bst()
{
	Root = nullptr;
}

/*
Function: Bst::~Bst()
Description: This destructor called on the PostOrderDelete function to delete everything in the tree.
*/

Bst::~Bst()
{
	PostOrderDelete(Root);
}

bool Bst::Empty()
{
	return (Root == nullptr);
}

bool Bst::Insert(string Key, double Info)
{
	//Create a node and store the key-info pair, check for mem alloc error
	Node* Temp = new Node;
	if (Temp == nullptr)
		return false;

	//initialize node that will be inserted into the Bst as a leaf
	Temp->KeyField = Key;
	Temp->Data = Info;
	Temp->Left = Temp->Right = nullptr;

	//insert node
	//check empty case first, otherwise, move thru the tree efficiently
	//and insert as a leaf
	if (Empty())
	{
		Root = Temp;
	}
	else
	{
		//insertion will executed using a trailer-pointer technique
		Node* Current = Root;
		Node* Trailer = nullptr;
		//when this loop concludes, Trailer will be pointing to the
		//new node's parent, the new node will be attached to this node
		while (Current != nullptr)
		{
			//move trailer up to current because current is fixing to move
			Trailer = Current;
			//travel down correct side based on the values of the KeyField
			if (Temp->KeyField <= Current->KeyField)
			{
				Current = Current->Left;
			}
			else
			{
				Current = Current->Right;
			}
		}

		//attach the new node based on the values in KeyField
		if (Temp->KeyField <= Trailer->KeyField)
		{
			Trailer->Left = Temp;
		}
		else
		{
			Trailer->Right = Temp;
		}
	}
	//let client know the function worked
	return true;
}

void Bst::DeleteLeaf(Node* P, Node* Parent) {
	if (Parent == NULL)
		Root = NULL;
	else if (Parent->Left == P)
		Parent->Left = NULL;
	else
		Parent->Right = NULL;
	delete P;
}

void Bst::DeleteOneChild(Node* P, Node* Parent) {
	//If the One child is not NULL on the Right Side
	if (P->Right != NULL) {
		Node* Temp = P->Right;
		//Connecting the Parent Node to the Temp Node
		Parent->Left = Temp;
		Temp = Parent->Left;
		delete P;
	}
	//If the One child is not NULL on the Left Side
	else if (P->Left != NULL) {
		Node* Temp = P->Left;
		//Connecting the Parent Node to the Temp Node
		Parent->Right = Temp;
		Temp = Parent->Right;
		delete P;
	}
}

void Bst::DeleteTwoChild(Node* P, Node* Parent) {
	//taking one step left and go far right as possible
	Node* Temp = P;
	Temp = Temp->Left;
	while (Temp->Right != NULL)
	{
		Temp = Temp->Right;
	}
	//Copy the Temp into the Parent node
	P->Data = Temp->Data;
	P->KeyField = Temp->KeyField;
	//Delete Temp
	delete Temp;
}

/*
Function: Bst::Delete(string Key)
Description: This function will use same concepts as the Search function but it will find the node
that contains the Key. It will also use a Trailer node to help determine the deletion of a leaf, 
one child, or two child.
*/
bool Bst::Delete(string Key)
{
	//Using success as a marker for the do while loop
	bool success = false;
	//Using a Temp node so it does not ruin the Root node for the next Search
	Node* Current = Root;
	Node* Trailer = NULL;
	do
	{
		//Visit
		if (Current->KeyField == Key) {
			//Delete Leaf
			if (Current->Right == NULL && Current->Left == NULL)
			{
				DeleteLeaf(Current, Trailer);
				success = true;
			}
			//Delete One Child
			else if (success != true && ((Current->Right == NULL && Current->Left != NULL) || (Current->Right != NULL && Current->Left == NULL)))
			{
				DeleteOneChild(Current, Trailer);
				success = true;
			}
			else {
				DeleteTwoChild(Current, Trailer);
				success = true;
			}
		}
		//Left
		else if (Current->KeyField > Key)
		{
			Trailer = Current;
			Current = Current->Left;
		}
		//Right
		else if (Current->KeyField < Key)
		{
			Trailer = Current;
			Current = Current->Right;
		}
	} while (!success && Current != NULL);
	if (success)
		return true;
	else
		return false;
}

/*
Function:Bst::Search(string Key, double& Info)
Description: This function will use the Pre Order Traversal to search through every node
in the tree. Using a do while loop, it will first look to see if the base of the tree is the Key. 
If it is not it will proceed to check the left side of the tree by moving the Temp node to the left.
If none is found it will check the right side of the tree by moving the Temp node to the right side.
When the Root->KeyField matched the Key it will assign the boolean variable to true. Once it reaches to
the bottom of the while loop it will check if success is true and it makes sure that the Temp node is not NULL.
If success is true, Info will be assigned to data from Temp->Data. If success is not true it will return false.
*/
bool Bst::Search(string Key, double& Info)
{
	//Using success as a marker for the do while loop
	bool success = false;
	//Using a Temp node so it does not ruin the Root node for the next Search
	Node* Temp = Root;
	do
	{
		//Visit
		if (Temp->KeyField == Key) 
			success = true;
		//Left
		else if (Temp->KeyField > Key)
		{
			Temp = Temp->Left;
		}
		//Right
		else if (Temp->KeyField < Key)
		{
			Temp = Temp->Right;
		}
	} while (!success && Temp != NULL);

	//If success is true, Temp->Data will put the data inside Info so it can be returned
	if (success) {
		Info = Temp->Data;
		return true;
	}
	else
		return false;
}

void Bst::Print()
{
	InOrderPrint(Root);
}

void Bst::InOrderPrint(Node* p)
{
	//Execute an in-order traversal to print the nodes out in sorted order (LVR)
	if (p != nullptr)
	{
		InOrderPrint(p->Left);
		cout << setw(10) << left << p->KeyField << setw(6) << right << fixed
			<< setprecision(2) << p->Data << endl;
		InOrderPrint(p->Right);
	}
}
/*
Function: Bst::PostOrderDelete(Node* p)
Description: This function will go through the tree by using a Post Order Traversal.
The function will first start by down the left side of the tree. It will check to
see if it can go any futher. If not, it will go down the right side of the tree.
Once it is finished going down both sides, it will delete the node. This follows the
concept of LRV. Meaning, Left, Right, and Visit.
*/
void Bst::PostOrderDelete(Node* p)
{
	if (p != nullptr)
	{
		PostOrderDelete(p->Left);
		PostOrderDelete(p->Right);
		delete p;
	}
}