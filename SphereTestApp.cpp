#include <iostream>
#include "Sphere.h"
using namespace std;

int main()
{
	Sphere Sphere1;
	Sphere Sphere2(5);
	Sphere Sphere3(10);

	cout << Sphere2.Circumference() << endl;
	cout << Sphere3.Area() << endl;
	cout << Sphere1.Diameter() << endl;

	cout << Sphere1.Volume() << endl;
	cout << Sphere2.Volume() << endl;
	cout << Sphere3.Volume() << endl;

	cout << endl;
	Sphere1.SetRadius(15);
	Sphere1.DisplayStatistics();
}