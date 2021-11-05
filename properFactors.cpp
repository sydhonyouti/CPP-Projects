//Author: Sydney Honyouti
//Due date: 11/1/2019
//Program: properFactors.cpp
//Program description: The program will find all the proper factors of n,
//store them in an integer array passed by reference in the parameter list,
//store the number of proper factors in an integer parameter passed by reference,
//and return the sum of all the proper factors as the function's return value.
#include <iostream>
#include <time.h>
using namespace std;

#define MAXIMUM 1000000
int Factors[MAXIMUM];
int properFactors(int, int[], int&);

int main()
{
	int q;
	int numFactors;
	int pairCount = 0;

	clock_t startClock = clock();
	for (int p = 1; p <= MAXIMUM; p++)
	{
		q = properFactors(p, Factors, numFactors);
		if (q > p)
		{
			if (properFactors(q, Factors, numFactors) == p) 
			{
				cout << "Amicable Pair: " << p << "," << q;
				cout << " (" << q << " has " << numFactors << " factors: ";
				cout << Factors[0];
				for (int i = 1; i < numFactors; i++)
				{
					cout << "," << Factors[i];
					cout << ")" << endl;
					pairCount++;
				}
			}
		}
	}
	double totalTime = (double)(clock() - startClock) / CLOCKS_PER_SEC;
	cout << "Number of amicable pairs found = " << pairCount << endl;
	cout << "Time = " << totalTime << " seconds" << endl;
}

int properFactors(int n, int factors[], int &numFactors)
{
	int k = 2, sum = 1, i = 1, factor2 = 0;
	factors[0] = 1;
	while (k * k <= n)
	{
		if (n % k == 0)
		{
			sum += k;
			factors[i] = k;
			i++;
			factor2 = n / k;
			if (factor2 != k)
			{
				sum += factor2;
				factors[i] = factor2;
				i++;
			}
		}
		k++;
	}
	numFactors = i;
	return sum;
}