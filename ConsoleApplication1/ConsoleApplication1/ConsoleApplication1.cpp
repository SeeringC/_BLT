
#include <iostream>
using namespace std;

void f(int a[])
{
	cout << (int)sizeof(a);
}

int main()
{
	int A[4];
	cout << (int)sizeof(A) << endl;
	f(A);
	
}


