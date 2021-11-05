/***************************************************************
Name: Sydney Honyouti
Program Name: tasteTest.cpp
Due Date: 9/6/19
Program Description: This program is going to take the users
					vote of either Coke or Pepi. It will then
					calculate to see if Coke or Pepsi won. If
					it is a even vote it will output "Tie!".
***************************************************************/
#include <iostream>
using namespace std;

int main()
{
	int coke = 0, pepsi = 0;
	char preference;

	cout << "Preference? ";
	cin >> preference;

	while (preference != 'q' && preference != 'Q')
	{
		if (preference == 'p' || preference == 'P')
			pepsi++;
		else if (preference == 'c' || preference == 'C')
			coke++;
		cout << "Preference? ";
		cin >> preference;
	}

	if (pepsi > coke)
		cout << "Pepsi wins!\n";
	else if (coke > pepsi)
		cout << "Coke wins!\n";
	else if (pepsi == coke)
		cout << "TIE!";
}