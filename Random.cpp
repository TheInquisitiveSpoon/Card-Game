#include <iostream>
#include <ctime>
using namespace std;

/*
Random.cpp
This is a standalone program which provides a function called Random(int n).
Random() returns a random number in the range 0..n, with n being supplied as a parameter.
The program includes main(), which demonstrates Random() being used.
For your own program you need to copy over the Random() function, as well as
use srand(). You do not need anything else from main() excpet for srand() 
*/

// returns a random number in the range 0 .. n, inclusive
int Random(const float n)
{
	return static_cast<int>(static_cast<double> (rand()) / (RAND_MAX + 1) * (n + 1));
}

int main()
{
	// A random number generator actually produces a pseudo-random sequence of numbers.
	// This means that the random number generator will always produce the same sequence of numbers.
	// The generator needs to be "seeded" with a value. You seed the generator with the function srand().
	// If you want to create a different sequence of numbers each time then seed it with the time as follows:
	srand( static_cast<unsigned int> (time(0)) );
	// The output of time() is time_t (which is actually an int).
	// static_cast<unsigned int> merely converts the output of time() into an unsigned integer.
	for( int i = 0; i < 10; i++ )
	{
		cout << Random(6) << endl;
	}
	cout << endl;

	// However, if you seed the generator with the same value each time then it will always produce
	// the same sequence of numbers. You want this to occur with the Monopoly program.
	// The next bit of code does this:
	srand( 4 );
	for( int i = 0; i < 10; i++ )
	{
		cout << Random(6) << endl;
	}
	cout << endl << endl;

	//The following code tests some differnt values of n
	int n = 1;
	cout << "Numbers beween 0 and " << n << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << Random(n) << endl;
	}
	cout << endl;
	n = 4;
	cout << "Numbers beween 0 and " << n << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << Random(n) << endl;
	}
	cout << endl;
	n = 8;
	cout << "Numbers beween 0 and " << n << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << Random(n) << endl;
	}
	cout << endl;
	system( "pause" );
}
