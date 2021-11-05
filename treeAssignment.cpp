/*
	This application will test the basic functionality of a Binary Search Tree.
	1) Constructor
	2) Destructor - written by student
	3) Empty
	4) Insert
	5) Delete - written by student
	6) Search - written by student
	7) Print
*/

#include <vld.h>
#include <string>
#include <iostream>
#include "bst.h"
using namespace std;

int main()
{
	//create a binary search tree object
	Bst NameList;

	//data to store in BST
	const int COUNTOFNAMES = 8;
	string Names[] = { "MIKE", "SALLY", "FRED", "BRENDA", "PETER", "WENDY", "DONNA", "HARRY" };
	double Gpa[] = { 3.1, 2.5, 1.75, 4.0, 3.5, 2.9, 2.25, 0.85 };

	//Insert data into a BST
	for (int i = 0; i < COUNTOFNAMES; i++)
	{
		NameList.Insert(Names[i], Gpa[i]);
	}

	//Print names to verify correctness
	//The data stored in the tree sorted by the KeyField
	cout << endl << "Data stored in the Binary Search Tree using an inorder traversal..." << endl;
	NameList.Print();

	//Check Search functionality
	double StudentGpa;
	cout << endl << "Checking Search functionality..." << endl << endl;
	//Donna's gpa is 2.25
	if (NameList.Search("DONNA", StudentGpa) == true)
		cout << "DONNA has a gpa of " << StudentGpa << endl;
	//Mike's gpa is 3.1
	if (NameList.Search("MIKE", StudentGpa) == true)
		cout << "MIKE has a gpa of " << StudentGpa << endl;
	//Wendy's gpa is 2.9
	if (NameList.Search("WENDY", StudentGpa) == true)
		cout << "WENDY has a gpa of " << StudentGpa << endl;
	//should get an error message
	if (NameList.Search("FRIED", StudentGpa) == false)
		cout << "No student named FRIED" << endl;
	cout << endl;

	//Now let's check delete functionality
	cout << "Checking Delete Functionality..." << endl << endl;
	//MIKE should be deleted...two child case
	if (NameList.Delete("MIKE"))
		cout << "MIKE deleted" << endl;
	//FRED should be deleted... one child case
	if (NameList.Delete("BRENDA"))
		cout << "FRED deleted" << endl;
	//PETER should be deleted... leaf case
	if (NameList.Delete("PETER"))
		cout << "PETER deleted" << endl;
	//Should get error message... no delete, SCUD not found
	if (NameList.Delete("SCUD") == false)
		cout << "SCUD not found...no deletion" << endl;

	//What names are left?
	cout << endl << "Here are the names that are left..." << endl;
	NameList.Print();
	cout << endl;

	return 0;
}