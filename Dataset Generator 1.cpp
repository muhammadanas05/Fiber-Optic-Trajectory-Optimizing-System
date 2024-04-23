//C++ Code to generate random dataset

#include <bits/stdc++.h>
#include <fstream>
#define nodes 100
#define weight 10000

using namespace std;

int main()
{
	fstream myfile;
	
	myfile.open("file.txt", ios::out);
	
	myfile << nodes << "\n";
	
	int x = 0, y = 1, z;
	do
	{
		z = rand() % weight;
	}while(z < 1000);
	
	myfile << x << " " << y << " " << z << "\n";
	
	for(int i = 0; i < nodes - 1; i++)
	{
		do
		{
			x = rand() % nodes;
			y = rand() % nodes;
		}while(x == y || x == 0 || y == 0);
		
		do
		{
			z = rand() % weight;
		}while(z < 1000);
		
		
		myfile << x << " " << y << " " << z << "\n";
	}
	
}
