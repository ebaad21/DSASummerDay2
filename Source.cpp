#include <iostream>
using namespace std;

int main()
{
	int a, b, c;
	a = 2;
	b = 3;
	cout << "Before Swapping: " << endl;
	cout << "a = " << a << endl; 
	cout << "b = " << b << endl; 
	c = a;
	a = b;
	b = c;
	cout << "After Swapping: " << endl;
	cout << "a = " << a << endl;
	cout << "b = " << b << endl;
	return 0;
}