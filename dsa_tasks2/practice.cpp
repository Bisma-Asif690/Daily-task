#include<iostream>
using namespace std;

int fun(int n)
{
	if(n>100)
	{
		return (n-5);
	}
	else
	{
		return fun(fun(n+11));
	}
	
}


int main()
{
	int c=fun(45);
	cout<<c;
	return 0;
}