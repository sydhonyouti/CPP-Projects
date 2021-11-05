/*
Program Name: baseConverter.cpp
Description: This program will run a base converter between two numbers. It is
			 assumed that the base number is from (2-16). However, the decimalNumber
			 is limited to how big the number can be. It can only be up to 1,000,000,000.
			 This program will also be using recursion inside the baseConverter function.
Author: Sydney Honyouti
*/

#include <iostream>
#include <fstream>
using namespace std;

/*
Function: void baseConverter
Description: This function will grab decimalNumber and base from the int main(). It will first
			 take the mod of the two varibles, assign it to the new modNumber variable. Then
			 divide and reassign it with the decimalNumber variable. It then calls the recursion
			 function of baseConverter, this is where we "unwind" the funnction. When we unwind
			 the function, this gives us the output. It can either output the numbers between 
			 0 through 9, or it can output A through B. It depends on what the modNumber is.
*/
void baseConverter(int decimalNumber, int base) {
	int modNumber;
	//if the decimal number is zero, we don't want it to continue through the function
	//because it will always be zero
	if (decimalNumber == 0)
		return;
	modNumber = decimalNumber % base;
	decimalNumber /= base;
	if (modNumber < 0)
		decimalNumber += 1;
	baseConverter(decimalNumber, base);
	//if modNumber is in the range between 10 through 15
	if (modNumber <= 15 && modNumber >= 10)
	{
		switch (modNumber)
		{
		case 10:
			cout << "A";
			break;
		case 11:
			cout << "B";
			break;
		case 12:
			cout << "C";
			break;
		case 13:
			cout << "D";
			break;
		case 14:
			cout << "E";
			break;
		case 15:
			cout << "F";
			break;
		default:
			break;
		}
	}
	else
		cout << modNumber;	
}

int main() {
	ifstream fin("numbers.txt");
	int decimalNumber, base;
	fin >> decimalNumber >> base;
	//decimal verification for the first numbers in the text file
	if (decimalNumber <= 1000000000 && decimalNumber >= 0) {
		//This will keep running until decimalNumber is a negative number
		while (decimalNumber > -1) {
			//If decimalNumber is 0
			if (decimalNumber == 0) {
				cout << decimalNumber << " in base " << base << " is 0\n";
				fin >> decimalNumber >> base;
			}
			//if decimalNumber fits in the number range
			else if (decimalNumber <= 1000000000 && decimalNumber >= 0) {
				cout << decimalNumber << " in base " << base << " is ";
				baseConverter(decimalNumber, base);
				cout << endl;
				fin >> decimalNumber >> base;
			}
			//if decimalNumber is too high
			else {
				cout << "Decimal number too large for this program\n";
				fin >> decimalNumber >> base;
			}
		}
	}
	fin.close();
	return 0;
}